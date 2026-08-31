#include <qapplication.h>
#include <qgraphicseffect.h>
#include <qpropertyanimation.h>
#include <qstringlist.h>
#include <qtimer.h>

#include "terminal.h"


namespace ScriptoApp
{
	TerminalWindow::TerminalWindow(const QString& scriptName, QWidget* parent) : QWidget(parent)
	{
		SetupUi();
		StartFadeIn([this, scriptName]{
			RunScript(scriptName);
			SetFocus();
		});
	}

	void TerminalWindow::SetupUi()
	{
		setWindowFlags(Qt::FramelessWindowHint);
		setAttribute(Qt::WA_TranslucentBackground);
		setStyleSheet("padding: 0; margin: 0;");

		setObjectName("terminal");
		setWindowTitle("Terminal");
		setFixedWidth(_width);
		setFixedHeight(_height);
		setStyleSheet("padding: 0; margin: 0;");

		// move the window to bottom right
		_screen = QGuiApplication::primaryScreen();
		QRect screenGeometry = _screen->availableGeometry();
		int rightMargin = 30;
		int bottomMargin = 50;
		int x = screenGeometry.width() - _width - rightMargin;
		int y = screenGeometry.height() - _height - bottomMargin;
		move(x, y);

		// close button
		_closeBtn = new QPushButton;
		SCRIPTO_WIDGET_INIT_OBJ(_closeBtn)
		_closeBtn->setIcon(QIcon("resources/icons/cross_filled.png"));
		_closeBtn->setFixedHeight(25);
		_closeBtn->setFixedWidth(25);
		QPoint terminalGlobalCord = this->mapToGlobal(QPoint(0, 0));
		_closeBtn->move(terminalGlobalCord.x() + this->_width - 60, terminalGlobalCord.y() + 15);
		_closeBtn->setAttribute(Qt::WA_DeleteOnClose);

		// terminal output
		_outputText = new QPlainTextEdit(this);
		_outputText->setReadOnly(true);
		_outputText->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		_outputText->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		_outputText->setMinimumHeight(155);
		_outputText->setMinimumWidth(365);
		_outputText->setProperty("styleTag", "primaryTextArea");
		_outputText->setProperty("state", "enabled");

		// terminal input
		_inputLabel = new QLabel("Input");
		_inputLabel->setProperty("styleTag", "primaryLabel");
		_inputLabel->setProperty("state", "enabled");

		_inputLineEdit = new QLineEdit(this);
		_inputLineEdit->setFixedHeight(30);
		_inputLineEdit->setMinimumWidth(310);
		_inputLineEdit->setPlaceholderText("Input Args...");
		_inputLineEdit->setProperty("styleTag", "primaryLineEdit");
		_inputLineEdit->setProperty("state", "enabled");

		QHBoxLayout* inputLayout = new QHBoxLayout;
		inputLayout->addWidget(_inputLabel);
		inputLayout->addSpacing(7);
		inputLayout->addWidget(_inputLineEdit);

		// layout
		QVBoxLayout* vlayout = new QVBoxLayout(this);
		vlayout->addWidget(_outputText);
		vlayout->addLayout(inputLayout);
		vlayout->setAlignment(_outputText, Qt::AlignCenter);
		vlayout->setAlignment(inputLayout, Qt::AlignCenter);
		vlayout->setContentsMargins(10, 10, 10, 10);
		vlayout->setSpacing(10);

		connect(_inputLineEdit, &QLineEdit::returnPressed, this, &TerminalWindow::WriteInput);
		connect(_closeBtn, &QPushButton::pressed, this, [this] {
			ShutDown();
		});;
	}

	void TerminalWindow::RunScript(const QString& scriptName)
	{
		//PrintSuccess(QString("Starting Script: %1").arg(scriptName));
		QStringList storedScripts = Scripto::GetStoredScriptsNames();
		qDebug() << storedScripts;
		if (!storedScripts.contains(scriptName))
		{
			PrintError("Script not found!");
			_closeBtn->show();
			_closeBtn->activateWindow();
			//ShutDown(5000); // after 5 sec
			return;
		}

		_processID = Scripto::RunScript(scriptName,
			[=](const QString& out) { onRunningScriptOutput(out); },
			[=](const QString& err) { onRunningScriptError(err); },
			[=](QProcess::ExitStatus status) {	onRunningScriptFinish(status); });

		if (_processID <= 0)
		{
			_processID = SCRIPTO_INVALID_PROCESS_ID;
			//ShutDown(5000); // after 5 sec
			_closeBtn->show();
			_closeBtn->activateWindow();
			return;
		}
	}

	void TerminalWindow::onRunningScriptOutput(const QString& output)
	{
		Print(output);
	}

	void TerminalWindow::onRunningScriptError(const QString& err)
	{
		PrintError(err);
		_error = true; // for now taking standard error stream as a fail in scritp execution
	}

	void TerminalWindow::onRunningScriptFinish(QProcess::ExitStatus exitsStatus)
	{
		if (_error)
		{
			PrintError("Script Exited with Errors.");
			// close button
			_closeBtn->show();
			_closeBtn->activateWindow();
		}
		else
		{
			PrintSuccess("Script Finished Successfully.\n");
			PrintLine("Window Will Close Automatically after 5 seconds...");
			QTimer::singleShot(5000, [this] { ShutDown(); }); // auto close terminal on success
		}
	}

	void TerminalWindow::Print(const QString& line, const QColor& color)
	{
		if (!_outputText)
			return;

		QTextCursor cursor = _outputText->textCursor();
		cursor.movePosition(QTextCursor::End);

		QTextCharFormat format;
		format.setForeground(color);
		format.setFontWeight(QFont::DemiBold);
		
		cursor.insertText(line, format);

		QTextBlockFormat blockFormat;
		blockFormat.setLineHeight(70, QTextBlockFormat::ProportionalHeight);

		cursor.mergeBlockFormat(blockFormat);

		_outputText->setTextCursor(cursor);
	}

	void TerminalWindow::PrintLine(const QString& line, const QColor& color)
	{
		Print(line + "\n", color);
	}

	void TerminalWindow::PrintSuccess(const QString& line)
	{
		Print(line, SUCCESS_COLOR);
	}

	void TerminalWindow::PrintError(const QString& line)
	{
		Print(line, ERROR_COLOR);
	}

	void TerminalWindow::StartFadeIn(std::function<void()> onAnimationFinished)
	{
		auto* effect = new QGraphicsOpacityEffect(this);
		setGraphicsEffect(effect);

		auto* animation = new QPropertyAnimation(effect, "opacity", this);
		animation->setDuration(300);
		animation->setStartValue(0.0);
		animation->setEndValue(1.0);
		animation->setEasingCurve(QEasingCurve::InCubic);
		show();

		connect(animation, &QPropertyAnimation::finished, this, [=] {
			onAnimationFinished();
		});
		animation->start(QAbstractAnimation::DeleteWhenStopped);
	}

	void TerminalWindow::HideFadeOut(std::function<void()> onAnimationFinished)
	{
		auto* effect = new QGraphicsOpacityEffect(this);
		setGraphicsEffect(effect);

		auto* animation = new QPropertyAnimation(effect, "opacity", this);
		animation->setDuration(300);
		animation->setStartValue(1.0);
		animation->setEndValue(0.0);
		animation->setEasingCurve(QEasingCurve::InCubic);

		connect(animation, &QPropertyAnimation::finished, this, [=] {
			onAnimationFinished();
		});
		animation->start(QAbstractAnimation::DeleteWhenStopped);
	}

	void TerminalWindow::WriteInput()
	{
		if (_processID == SCRIPTO_INVALID_PROCESS_ID)
			return;

		Scripto::WriteInputToProcess(_processID, _inputLineEdit->text());
		_inputLineEdit->clear();
	}

	void TerminalWindow::SetFocus()
	{
		_inputLineEdit->setFocus();
	}

	void TerminalWindow::ShutDown(int waitTime)
	{
		_closeBtn->close();

		if (waitTime <= 0)
		{
			HideFadeOut([this] {
				this->destroy();
			});
		}
		else
		{
			QTimer::singleShot(waitTime, [this] {
				HideFadeOut([this] {
					this->destroy();
				}); 
			});
		}
	}
}