#pragma once

#include <qwidget.h>
#include <qscreen.h>
#include <qlineedit.h>
#include <qboxlayout.h>
#include <qlabel.h>
#include <qfile.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qevent.h>
#include <qprocess.h>
#include <qlist.h>
#include <qstringlistmodel.h>

#include <scripto.h>

#include "common.h"
#include "terminal.h"
#include "newscriptdialog.h"
#include "schedulerwindow.h"

namespace ScriptoApp
{

	class ScriptoMainWindow : public QWidget
	{
	public:
		ScriptoMainWindow(QWidget* parent = nullptr);

		/* called automaticalley when the object is created */
		void SetupUi();
		/* changes app theme */
		SCRIPTO_SET_THEME_FUNC_DECL

		void RunScript();

		void ShowFadeIn();
		void CloseFadeOut();

		void CenterPosition();

		// set focus to _search bar
		void SetFocus();
	protected:
		SCRIPTO_WIDGET_PAINT_EVENT_IMPL
		SCRIPTO_WIDGET_DRAG_IMPL(_dragOffset)

		void onNewScriptAddedCallback(const QString& name);
		void onScriptRemovedCallback(const QString& name);

	private:
		const int _width = 500;
		const int _height = 70;
		QList<TerminalWindow*> _currentlyRunningTerminals;
		QStringListModel* _storedScripts;

		NewScriptDialogWindow* _newScriptDialog;
		SchedulerWindow* _scheduler;
		
		QScreen* _screen;
		QLineEdit* _searchBar;
		QCompleter* _completer;
		QLabel* _title;
		QPoint _dragOffset;

		QShortcut* _escShortcut;
		QShortcut* _newScriptDialogShortcut;
		QShortcut* _scheduleScriptShortcut;
	};
}