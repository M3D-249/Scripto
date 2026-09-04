#include <qapplication.h>

#include <scripto.h>
#include "mainwindow.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	Scripto::Init("Scripto", "M3D-249");
	
	ScriptoApp::ScriptoMainWindow* mainwindow = new ScriptoApp::ScriptoMainWindow;
	mainwindow->show();

	return app.exec();
}