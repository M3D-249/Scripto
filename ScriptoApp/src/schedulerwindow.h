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
#include <qspinbox.h>

#include "common.h"

namespace ScriptoApp
{
	class SchedulerWindow : public QWidget
	{
	public:
		SchedulerWindow(QWidget* parent = nullptr);

		/* called automaticalley when the object is created */
		void SetupUi();

	protected:
		void onCancelButtonPressed();
		void onSetButtonPressed();

		SCRIPTO_WIDGET_PAINT_EVENT_IMPL
		SCRIPTO_WIDGET_DRAG_IMPL(_dragOffset)
	private:
		SCRIPTO_REFRESH_STYLE_FUNC_DECL

		QScreen* _screen;
		QLabel* _title;
		QLabel* _scriptNameLabel;
		QLineEdit* _scriptNameLineEdit;
		QComboBox* _typeComboBox;
		QLabel* _timePeriodLabel;
		QSpinBox* _timePeriodSpinBox;
		QComboBox* _timeUnitComboBox;
		QLabel* _targetDateLabel;
		QDateTimeEdit* _targetDateEdit; // use QCalendarWidget instead
		QCheckBox* _repeatCheckBox;
		QPushButton* _cancelBtn;
		QPushButton* _setBtn;
		const int _width = 350;
		const int _height = 230;
		QPoint _dragOffset;
	};
}