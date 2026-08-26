#include <qapplication.h>
#include "terminal.h"

namespace Scripto
{
	TerminalWindow::TerminalWindow(QWidget* parent) : QWidget(parent)
	{
		SetupUi();
	}

	void TerminalWindow::SetupUi()
	{
		SCRIPTO_WIDGET_INIT

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

		// terminal output
		_outputText = new QTextEdit(this);
		_outputText->setReadOnly(true);
		_outputText->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		_outputText->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		_outputText->setMinimumHeight(155);
		_outputText->setMinimumWidth(365);
		_outputText->setStyleSheet("background-color: #262626; color: #E0E0E0; border-radius: 5px; padding: 3px; font-size: 12px; ");
		
		/// TEST:
		Print("Hellow", Qt::green);
		PrintLine("Hellow", Qt::green);
		PrintLine("Hellow", Qt::red);
		PrintLine("Hellow", Qt::red);
		PrintLine("Hellow");
		PrintLine("Hellow");
		PrintLine("Hellow");
		PrintLine("Hellow");
		PrintLine("Hellow");
		PrintLine("Hellow");
		PrintLine("Hellow");
		PrintLine("Hellow");
		///

		// terminal input
		_inputLabel = new QLabel("Input");
		_inputLabel->setStyleSheet("color: #E0E0E0; font-size: 14px");

		_inputLineEdit = new QLineEdit(this);
		_inputLineEdit->setFixedHeight(30);
		_inputLineEdit->setMinimumWidth(310);
		_inputLineEdit->setPlaceholderText("Input Args...");
		_inputLineEdit->setStyleSheet("background-color: #262626; color: #E0E0E0; border-radius: 5px; padding: 3px; font-size: 14px; ");

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
		vlayout->setContentsMargins(7, 7, 7, 7);

		SetTheme(true);
	}

	SCRIPTO_SET_THEME_FUNC_IMPL(TerminalWindow)

	void TerminalWindow::Print(const QString& line, const QColor& color)
	{
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
}