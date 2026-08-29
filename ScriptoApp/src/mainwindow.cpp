#include <qapplication.h>

#include "mainwindow.h"

namespace ScriptoApp
{
	ScriptoMainWindow::ScriptoMainWindow(QWidget* parent) : QWidget(parent)
	{
		SetupUi();
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
		_screen = QGuiApplication::primaryScreen();
		QRect screenGeometry = _screen->availableGeometry();
		int x = (screenGeometry.width() - _width) / 2;
		int y = 30;
		move(x, y);

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
	}

	SCRIPTO_SET_THEME_FUNC_IMPL(ScriptoMainWindow)
}