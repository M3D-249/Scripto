#pragma once

#include <qwidget.h>
#include <qstringlistmodel.h>

#include <scripto.h>

#include "common.h"
#include "terminal.h"
#include "newscriptdialog.h"
#include "schedulerwindow.h"
#include "removescriptdialog.h"

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
		/* run script with the name matching the one entered throw _searchBar */
		void RunScript();
		/* shows the window playing fade in animation */
		void ShowFadeIn();
		/* hides the window playing fade out animation */
		void CloseFadeOut();
		/* place the window in the center top of the screen */
		void CenterPosition();
		/* set focus to _searchBar */
		void SetFocus();

	protected:
		SCRIPTO_WIDGET_PAINT_EVENT_IMPL
		SCRIPTO_WIDGET_DRAG_IMPL(_dragOffset)

		void onNewScriptAddedCallback(const QString& name);
		void onScriptRemovedCallback(const QString& name);

	private:
		const int _width = 500;
		const int _height = 70;
		QStringListModel* _storedScripts;

		// sub windows & dialogs
		NewScriptDialogWindow* _newScriptDialog;
		SchedulerWindow* _scheduler;
		RemoveScriptDialog* _removeScriptDialog;
		// UI
		QScreen* _screen;
		QLineEdit* _searchBar;
		QCompleter* _completer;
		QLabel* _title;
		QPoint _dragOffset;

		// shortcuts
		QShortcut* _escShortcut;
		QShortcut* _newScriptDialogShortcut;
		QShortcut* _scheduleScriptShortcut;
		QShortcut* _removeScriptDialogShortcut;
	};
}