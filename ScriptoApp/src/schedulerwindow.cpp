#include <qapplication.h>
#include <qdatetimeedit.h>

#include "schedulerwindow.h"

namespace ScriptoApp
{
	SchedulerWindow::SchedulerWindow(QWidget* parent) : QWidget(parent)
	{
		SetupUi();
	}

	void SchedulerWindow::SetupUi()
	{
		SCRIPTO_WIDGET_INIT

		setObjectName("Schedulerwindow");
		setWindowTitle("Scheduler");
		setFixedSize(_width, _height);
		setStyleSheet("padding: 0; margin: 0;");

		// position window
		_screen = QGuiApplication::primaryScreen();
		QRect screenGeometry = _screen->availableGeometry();
		int x = (screenGeometry.width() - 200) / 2;
		int y = 110;
		move(x, y);

		// window title
		_title = new QLabel("Scheduler");
		_title->setProperty("styleTag", "windowTitle");
		_title->setFixedHeight(30);

		// script name
		_scriptNameLabel = new QLabel("Script Name");
		_scriptNameLabel->setFixedWidth(74);
		_scriptNameLabel->setProperty("styleTag", "primaryLabel");
		_scriptNameLabel->setProperty("state", "enabled");

		_scriptNameLineEdit = new QLineEdit;
		_scriptNameLineEdit->setFixedHeight(30);
		_scriptNameLineEdit->setFixedWidth(237);
		_scriptNameLineEdit->setPlaceholderText("Enter Script Name...");
		_scriptNameLineEdit->setProperty("styleTag", "primaryLineEdit");
		_scriptNameLineEdit->setProperty("state", "enabled");

		QHBoxLayout* scriptNameLayout = new QHBoxLayout;
		scriptNameLayout->addWidget(_scriptNameLabel);
		scriptNameLayout->addWidget(_scriptNameLineEdit);
		scriptNameLayout->addSpacing(7);

		// type combo box
		_typeComboBox = new QComboBox;
		_typeComboBox->addItem("Time Period");
		_typeComboBox->addItem("Date");
		_typeComboBox->setFixedHeight(30);
		_typeComboBox->setProperty("styleTag", "primaryComboBox");
		_typeComboBox->setProperty("state", "enabled");

		// time period
		_timePeriodLabel = new QLabel("Time Period");
		_timePeriodLabel->setFixedWidth(78);
		_timePeriodLabel->setProperty("styleTag", "primaryLabel");
		_timePeriodLabel->setProperty("state", "enabled");

		_timePeriodSpinBox = new QSpinBox;
		_timePeriodSpinBox->setMinimum(1);
		_timePeriodSpinBox->setMinimumWidth(50);
		_timePeriodSpinBox->setFixedHeight(30);

		_timeUnitComboBox = new QComboBox;
		_timeUnitComboBox->addItem("Milliseconds");
		_timeUnitComboBox->addItem("Seconds");
		_timeUnitComboBox->addItem("Minitues");
		_timeUnitComboBox->addItem("Hours");
		_timeUnitComboBox->setCurrentIndex(1);
		_timeUnitComboBox->setFixedHeight(30);
		_timeUnitComboBox->setProperty("styleTag", "primaryComboBox");
		_timeUnitComboBox->setProperty("state", "enabled");

		QHBoxLayout* timePeriodLayout = new QHBoxLayout;
		timePeriodLayout->addWidget(_timePeriodLabel);
		timePeriodLayout->addWidget(_timePeriodSpinBox);
		timePeriodLayout->addWidget(_timeUnitComboBox);
		timePeriodLayout->setSpacing(7);

		// target date
		_targetDateLabel = new QLabel("Target Date");
		_targetDateLabel->setFixedWidth(78);
		_targetDateLabel->setProperty("styleTag", "primaryLabel");
		_targetDateLabel->setProperty("state", "enabled");

		_targetDateEdit = new QDateTimeEdit;
		_targetDateEdit->setFixedHeight(30);
		_targetDateEdit->setProperty("state", "enabled");

		QHBoxLayout* targetDateLayout = new QHBoxLayout;
		targetDateLayout->addWidget(_targetDateLabel);
		targetDateLayout->addWidget(_targetDateEdit);
		targetDateLayout->setSpacing(7);

		// repeat checkbox
		_repeatCheckBox = new QCheckBox("Repeat");
		_repeatCheckBox->setCheckState(Qt::Unchecked);

		// cancel & set buttons
		_setBtn = new QPushButton("Set");
		_setBtn->setProperty("styleTag", "paleGreenBtn");
		_setBtn->setProperty("state", "enabled");

		_cancelBtn = new QPushButton("Cancel");
		_cancelBtn->setProperty("styleTag", "darkRedBtn");
		_cancelBtn->setProperty("state", "enabled");

		QHBoxLayout* cancelAndSetBtnsLayout = new QHBoxLayout;
		cancelAndSetBtnsLayout->addWidget(_setBtn);
		cancelAndSetBtnsLayout->addWidget(_cancelBtn);
		cancelAndSetBtnsLayout->setSpacing(7);

		QVBoxLayout* layout = new QVBoxLayout(this);
		layout->addWidget(_title);
		layout->setAlignment(_title, Qt::AlignCenter);
		layout->addLayout(scriptNameLayout);
		layout->addWidget(_typeComboBox);
		layout->setAlignment(_typeComboBox, Qt::AlignRight);
		layout->addLayout(timePeriodLayout);
		layout->addLayout(targetDateLayout);
		layout->addLayout(cancelAndSetBtnsLayout);
		layout->setContentsMargins(15, 5, 15, 15);
		layout->setSpacing(10);

		// events
		connect(_cancelBtn, &QPushButton::pressed, this, &SchedulerWindow::onCancelButtonPressed);
		connect(_setBtn, &QPushButton::pressed, this, &SchedulerWindow::onSetButtonPressed);
	}

	void SchedulerWindow::onSetButtonPressed()
	{

	}

	void SchedulerWindow::onCancelButtonPressed()
	{
		this->hide();
		_scriptNameLineEdit->clear();
		_targetDateEdit->clear();
	}
}