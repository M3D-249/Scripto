#include <qapplication.h>

#include "mainwindow.h"

namespace Scripto
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
		_title->setStyleSheet("color: #E0E0E0; font-size: 14px");
		_searchBar = new QLineEdit(this);
		_searchBar->setFixedHeight(30);
		_searchBar->setPlaceholderText("Run Script...");
		_searchBar->setStyleSheet("background-color: #262626; color: #E0E0E0; border-radius: 5px; padding: 6px; font-size: 14px; ");

		QVBoxLayout* layout = new QVBoxLayout(this);
		layout->addWidget(_title);
		layout->addWidget(_searchBar);
		layout->setContentsMargins(7, 2, 7, 7);
		layout->setAlignment(_title, Qt::AlignJustify);

		SetTheme(true);
	}

	SCRIPTO_SET_THEME_FUNC_IMPL(ScriptoMainWindow)
}