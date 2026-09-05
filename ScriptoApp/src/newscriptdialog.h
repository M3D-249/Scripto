#pragma once

#include <qwidget.h>
#include <qdialog.h>
#include <qevent.h>
#include <qcheckbox.h>
#include <qplaintextedit.h>

#include "common.h"

namespace ScriptoApp
{
	class NewScriptDialogWindow : public QDialog
	{
	public:
		NewScriptDialogWindow(QWidget* parent = nullptr);

		/* called automaticalley when the object is created */
		void SetupUi();

	protected:
		// callbacks
		void onScriptNameChanged(const QString& newName);
		void onScriptPathChanged(const QString& text);
		void onScriptWorkingDirChanged(const QString& newName);
		void onInplaceCheckBoxStateChange(bool checked);
		void onScriptPathBrowseBtnClicked();
		void onScriptWorkingDirBrowseBtnClicked();
		void onSaveBtnClicked();
		void onCancelButtonPressed();

		void UpdateSaveBtnState();

		// helpers
		bool IsValidScriptName(const QString& path);
		bool IsValidDir(const QString& path);
		bool IsValidScriptFile(const QString& path);

		SCRIPTO_WIDGET_PAINT_EVENT_IMPL
		SCRIPTO_WIDGET_DRAG_IMPL(_dragOffset)
	private:
		SCRIPTO_REFRESH_STYLE_FUNC_DECL
		
		const int _width = 500;
		const int _height = 450;
		QPoint _dragOffset;

		// TODO: add checkbox for wether a script should start a terminal session
		// UI
		QScreen* _screen;
		QLabel* _title;
		QLabel* _scriptNameLabel;
		QLineEdit* _scriptNameLineEdit;
		QLabel* _scriptNameStatusLabel;
		QLabel* _scriptPathLabel;
		QLineEdit* _scriptPathLineEdit;
		QPushButton* _scriptPathBrowseBtn;
		QLabel* _scriptPathStatusLabel;
		QLabel* _scriptWorkingDirPathLabel;
		QLabel* _scriptWorkingDirStatusLabel;
		QLineEdit* _scriptWorkingDirLineEdit;
		QPushButton* _scriptWorkingDirBrowseBtn;
		QCheckBox* _inplaceCheckBox;
		QLabel* _scriptCodeLabel;
		QPlainTextEdit* _scriptCodeTextEdit;
		QLabel* _scriptTypeLabel;
		QComboBox* _scriptTypeComboBox;
		QPushButton* _cancelBtn;
		QPushButton* _saveBtn;
	};
}