#include <Windows.h>

#include <iostream>

#include <scripto.h>

#include <qapplication.h>

#include "mainwindow.h"
#include "terminal.h"
#include "newscriptdialog.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	Scripto::Init("Scripto", "M3D-249");

	ScriptoApp::ScriptoMainWindow mainwindow;
	ScriptoApp::TerminalWindow terminal;
	ScriptoApp::NewScriptDialogWindow dialog;
	//dialog.show();
	//terminal.show();
	mainwindow.show();

	return app.exec();
}