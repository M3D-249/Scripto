#pragma once

// TODO: clean this
#include <qwidget.h>
#include <qscreen.h>
#include <qlineedit.h>
#include <qboxlayout.h>
#include <qlabel.h>
#include <qfile.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qtextedit.h>
#include <qevent.h>
#include <qplaintextedit.h>
#include <qobject.h>
#include <qprocess.h>
#include <qpushbutton.h>

#include <scripto.h>
#include "common.h"

namespace ScriptoApp
{
	class TerminalWindow : public QWidget
	{
	public:
		TerminalWindow(const QString& scriptName, QWidget* parent = nullptr);

		/* called automaticalley when the object is created */
		void SetupUi();

		/* script execution logic */
		void RunScript(const QString& name);
		void onRunningScriptOutput(const QString& output);
		void onRunningScriptError(const QString& err);
		void onRunningScriptFinish(QProcess::ExitStatus exitsStatus);

		/* doesn't append \n at the end  of text */
		void Print(const QString& line, const QColor& color = QColor(150, 150, 150));
		/* appends \n at the end of the text */
		void PrintLine(const QString& line, const QColor& color = QColor(150, 150, 150));
		void PrintSuccess(const QString& line);
		void PrintError(const QString& line);
		
		/* shows the window with fade in animation */
		void StartFadeIn(std::function<void()> onAnimationFinished);
		/* hides the window with fade out animation */
		void HideFadeOut(std::function<void()> onAnimationFinished);
		/* closes the window and deletes it after wait time in milliseconds */
		void ShutDown(int waitTime = 0);
		/* setfocus on terminal input */
		void SetFocus();
	protected:
		SCRIPTO_WIDGET_PAINT_EVENT_IMPL
		SCRIPTO_WIDGET_DRAG_IMPL(_dragOffset)
		/* writes input to the process running by the current terminal instance */
		void WriteInput();

	private:
		const QColor SUCCESS_COLOR = QColor(19, 252, 19);
		const QColor ERROR_COLOR = QColor(252, 44, 19);
		
		/* flag for when script execution faces any errors */
		bool _error = false;
		long long _processID = SCRIPTO_INVALID_PROCESS_ID;
		
		const int _width = 386;
		const int _height = 230;
		
		// UI
		QScreen* _screen;
		QPushButton* _closeBtn;
		QPlainTextEdit* _outputText;
		QLineEdit* _inputLineEdit;
		QLabel* _inputLabel;
		QPoint _dragOffset;
	};
}