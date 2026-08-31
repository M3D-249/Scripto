#include <qapplication.h>
#include <qcompleter.h>
#include <qshortcut.h>
#include <qgraphicseffect.h>
#include <qpropertyanimation.h>
#include <qabstractitemview.h>
#include <qhotkey.h>

#include "mainwindow.h"
#include "scripto.h"

namespace ScriptoApp
{
	ScriptoMainWindow::ScriptoMainWindow(QWidget* parent) : QWidget(parent)
	{
		SetupUi();

		auto hotkey = new QHotkey(QKeySequence("Ctrl+Shift+P"), true);
		QObject::connect(hotkey, &QHotkey::activated, [this] {
			if (isVisible())
				SetFocus();
			else
			{
				ShowFadeIn();
			}
		});
	}

	void ScriptoMainWindow::SetupUi()
	{
		SCRIPTO_WIDGET_INIT

		setObjectName("mainwindow");
		setWindowTitle("Scripto");
		setFixedWidth(_width);
		setFixedHeight(_height);
		setStyleSheet("padding: 0; margin: 0;");

		// center the window
		CenterPosition();

		// title & search bar
		_title = new QLabel("Scripto", this);
		_title->setProperty("styleTag", "windowTitle");

		_searchBar = new QLineEdit(this);
		_searchBar->setPlaceholderText("Run Script...");
		_searchBar->setProperty("styleTag", "primaryLineEdit");
		_searchBar->setProperty("state", "enabled");

		QVBoxLayout* layout = new QVBoxLayout(this);
		layout->addWidget(_title);
		layout->addWidget(_searchBar);
		layout->setContentsMargins(7, 2, 7, 7);
		layout->setAlignment(_title, Qt::AlignJustify);

		SetTheme(true);

		_storedScripts = new QStringListModel(Scripto::GetStoredScriptsNames());
		_completer = new QCompleter(this);
		_completer->setModel(_storedScripts);
		_completer->setCaseSensitivity(Qt::CaseInsensitive);
		_completer->setFilterMode(Qt::MatchContains);
		_completer->setCompletionMode(QCompleter::PopupCompletion);
		_searchBar->setCompleter(_completer);

		_newScriptDialog = new NewScriptDialogWindow;
		_scheduler = new SchedulerWindow;
		_newScriptDialog->hide();
		_scheduler->hide();

		// setup shortcuts
		_escShortcut = new QShortcut(QKeySequence(Qt::Key_Escape), this);
		_newScriptDialogShortcut = new QShortcut(QKeySequence("Ctrl+N"), this);
		_scheduleScriptShortcut = new QShortcut(QKeySequence("Ctrl+S"), this);

		connect(_searchBar, &QLineEdit::returnPressed, this, &ScriptoMainWindow::RunScript);
		connect(_escShortcut, &QShortcut::activated, this, [this] {
			this->CloseFadeOut();
			this->_searchBar->setText(""); // clear search bar
			this->_scheduler->close();
			this->_newScriptDialog->close();
		});

		connect(_newScriptDialogShortcut, &QShortcut::activated, this, [this] {
			this->_newScriptDialog->show(); // TODO: add pop in animation
		});

		connect(_scheduleScriptShortcut, &QShortcut::activated, this, [this] {
			this->_scheduler->show(); // TODO: add pop in animation
		});

		// backend callbacks
		Scripto::setOnNewScriptAddedCallback([=](const QString& scriptName) {
			onNewScriptAddedCallback(scriptName);
		});
		Scripto::setOnScriptRemovedCallback([=](const QString& scriptName) {
			onScriptRemovedCallback(scriptName);
		});
	}

	void ScriptoMainWindow::RunScript()
	{
		QString scriptName = _searchBar->text();
		TerminalWindow* terminal = new TerminalWindow(scriptName);
	}

	void ScriptoMainWindow::ShowFadeIn()
	{
		CenterPosition();

		auto* effect = new QGraphicsOpacityEffect(this);
		setGraphicsEffect(effect);

		auto* animation = new QPropertyAnimation(effect, "opacity", this);
		animation->setDuration(200);
		animation->setStartValue(0.0);
		animation->setEndValue(1.0);
		animation->setEasingCurve(QEasingCurve::InCubic);
		animation->start(QAbstractAnimation::DeleteWhenStopped);

		SetFocus();
		show();
	}

	void ScriptoMainWindow::CloseFadeOut()
	{
		auto* effect = new QGraphicsOpacityEffect(this);
		setGraphicsEffect(effect);

		auto* animation = new QPropertyAnimation(effect, "opacity", this);
		animation->setDuration(300);
		animation->setStartValue(1.0);
		animation->setEndValue(0.0);
		animation->setEasingCurve(QEasingCurve::InCubic);

		animation->start(QAbstractAnimation::DeleteWhenStopped);
		connect(animation, &QPropertyAnimation::finished, this, [=] {
			hide();
		});
	}

	void ScriptoMainWindow::onNewScriptAddedCallback(const QString& scriptName)
	{
		int row = _storedScripts->rowCount();
		_storedScripts->insertRow(row);
		_storedScripts->setData(_storedScripts->index(row), scriptName);
		qDebug() << "Updated Stored Scripts: added '" << scriptName << "'.";
	}

	void ScriptoMainWindow::onScriptRemovedCallback(const QString& scriptName)
	{
		int index = _storedScripts->stringList().indexOf(scriptName);
		if (index >= 0)
			_storedScripts->removeRow(index);
		qDebug() << "Updated Stored Scripts: removed '" << scriptName << "'.";
	}

	void ScriptoMainWindow::CenterPosition()
	{
		_screen = QGuiApplication::primaryScreen();
		QRect screenGeometry = _screen->availableGeometry();
		int x = (screenGeometry.width() - _width) / 2;
		int y = 30;
		move(x, y);
	}

	void ScriptoMainWindow::SetFocus()
	{
		_searchBar->setFocus();
	}

	SCRIPTO_SET_THEME_FUNC_IMPL(ScriptoMainWindow)
}