#pragma once

#include <qwidget.h>
#include <qscreen.h>
#include <qlineedit.h>
#include <qboxlayout.h>
#include <qlabel.h>
#include <qfile.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qpushbutton.h>
#include <qcheckbox.h>
#include <qtextedit.h>
#include <qplaintextedit.h>
#include <qcombobox.h>

#include "common.h"

namespace Scripto
{
	class NewScriptDialogWindow : public QWidget
	{
	public:
		NewScriptDialogWindow(QWidget* parent = nullptr);

		/* called automaticalley when the object is created */
		void SetupUi();
		/* changes app theme */
		SCRIPTO_SET_THEME_FUNC_DECL

		// getters
		QString scriptName() const;
		bool isInPlace() const;
		QString scriptType() const;
		QString scriptContent() const;
		QString scriptPath() const;

	protected:
		SCRIPTO_WIDGET_PAINT_EVENT_IMPL

	private:
		QScreen* _screen;
		QLabel* _title;
		QLabel* _scriptNameLabel;
		QLineEdit* _scriptNameLineEdit;
		QLabel* _scriptPathLabel;
		QLineEdit* _scriptPathLineEdit;
		QPushButton* _scriptPathBrowseBtn;
		QCheckBox* _inplaceCheckBox;
		QLabel* _scriptCodeLabel;
		QPlainTextEdit* _scriptCodeTextEdit;
		QLabel* _scriptTypeLabel;
		QComboBox* _scriptTypeComboBox;
		QPushButton* _cancelBtn;
		QPushButton* _saveBtn;
		const int _width = 500;
		const int _height = 350;
	};
}