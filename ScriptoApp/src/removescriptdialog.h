#pragma once
#include <qwidget.h>
#include <qdialog.h>
#include <qstringlistmodel.h>
#include <qevent.h>

#include <scripto.h>

#include "common.h"

namespace ScriptoApp
{

	class RemoveScriptDialog : public QDialog
	{
	public:
		RemoveScriptDialog(QWidget* parent = nullptr);

		/* called automaticalley when the object is created */
		void SetupUi();
		/* shows the window playing fade in animation */
		void ShowFadeIn();
		/* hides the window playing fade out animation */
		void CloseFadeOut();

	protected:
		SCRIPTO_WIDGET_PAINT_EVENT_IMPL
		SCRIPTO_WIDGET_DRAG_IMPL(_dragOffset)

		// slots & callbacks
		void onRemoveBtnPressed();
		void onCancelBtnPressed();
		void onNewScriptAddedCallback(const QString& scriptName);

	private:
		const int _width = 500;
		const int _height = 110;
		QPoint _dragOffset;
		QStringListModel* _storedScripts;

		// UI
		QScreen* _screen;
		QLabel* _title;
		QLabel* _scriptNameLabel;
		QLineEdit* _scriptNameLineEdit;
		QCompleter* _completer;
		QPushButton* _removeBtn;
		QPushButton* _cancelBtn;
	};
}