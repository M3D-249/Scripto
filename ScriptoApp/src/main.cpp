#include <qapplication.h>
#include <qsharedmemory.h>
#include <qmessagebox.h>

#include <scripto.h>

#include "mainwindow.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	QSharedMemory sharedMemory("M3D_Scripto_Single_Instance");
	if (!sharedMemory.create(1))
	{
		QMessageBox::warning(
			nullptr,
			"Already Running",
			"Scripto Application is already running"
		);
		return 0;
	}

	Scripto::Init();
	ScriptoApp::ScriptoMainWindow* mainwindow = new ScriptoApp::ScriptoMainWindow;
	return app.exec();
}