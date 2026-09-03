#include <qapplication.h>
#include <qdatetimeedit.h>

#include <scripto.h>

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
		_scriptNameLabel->setFixedWidth(78);
		_scriptNameLabel->setProperty("styleTag", "primaryLabel");
		_scriptNameLabel->setProperty("state", "enabled");

		_scriptNameLineEdit = new QLineEdit;
		_scriptNameLineEdit->setFixedHeight(30);
		_scriptNameLineEdit->setFixedWidth(237);
		_scriptNameLineEdit->setPlaceholderText("Enter Script Name...");
		_scriptNameLineEdit->setProperty("styleTag", "primaryLineEdit");
		_scriptNameLineEdit->setProperty("state", "enabled");

		_scriptNameStatusLabel = new QLabel;
		_scriptNameStatusLabel->setFixedHeight(10);
		_scriptNameStatusLabel->setStyleSheet("color: #E0E0E0; font-size: 8px; left: 78px;");

		QVBoxLayout* scriptNameLineEditLayout = new QVBoxLayout;
		scriptNameLineEditLayout->addWidget(_scriptNameLineEdit);
		scriptNameLineEditLayout->addWidget(_scriptNameStatusLabel);
		scriptNameLineEditLayout->setSpacing(7);

		QHBoxLayout* scriptNameLayout = new QHBoxLayout;
		scriptNameLayout->addWidget(_scriptNameLabel);
		scriptNameLayout->addLayout(scriptNameLineEditLayout);
		scriptNameLayout->setAlignment(_scriptNameLabel, Qt::AlignTop);
		scriptNameLayout->addSpacing(7);

		// repeat checkbox
		_repeatCheckBox = new QCheckBox("Repeat");
		_repeatCheckBox->setFixedHeight(20);
		_repeatCheckBox->setFixedWidth(78);
		_repeatCheckBox->setCheckState(Qt::Unchecked);
		_repeatCheckBox->setProperty("state", "enabled");

		_repeatsCountSpinBox = new QSpinBox;
		_repeatsCountSpinBox->setRange(-1, INT_MAX);
		_repeatsCountSpinBox->setValue(0);
		_repeatsCountSpinBox->setFixedWidth(120);
		_repeatsCountSpinBox->setFixedHeight(30);
		_repeatsCountSpinBox->setProperty("state", "disabled");
		_repeatsCountSpinBox->setEnabled(false);

		// type combo box
		_typeComboBox = new QComboBox;
		_typeComboBox->addItem("Time Period");
		_typeComboBox->addItem("Date");
		_typeComboBox->setFixedHeight(30);
		_typeComboBox->setFixedWidth(120);
		_typeComboBox->setProperty("styleTag", "primaryComboBox");
		_typeComboBox->setProperty("state", "enabled");

		QVBoxLayout* repeatsCountEditLayout = new QVBoxLayout;
		repeatsCountEditLayout->addWidget(_repeatsCountSpinBox);
		repeatsCountEditLayout->addWidget(_typeComboBox);
		repeatsCountEditLayout->setSpacing(7);


		QHBoxLayout* repeatsCountLayout = new QHBoxLayout;
		repeatsCountLayout->addWidget(_repeatCheckBox);
		repeatsCountLayout->addLayout(repeatsCountEditLayout);
		repeatsCountLayout->addSpacing(7);
		repeatsCountLayout->setAlignment(_repeatCheckBox, Qt::AlignTop);

		// time period
		_timePeriodLabel = new QLabel("Time Period");
		_timePeriodLabel->setFixedWidth(78);
		_timePeriodLabel->setProperty("styleTag", "primaryLabel");
		_timePeriodLabel->setProperty("state", "enabled");

		_timePeriodSpinBox = new QSpinBox;
		_timePeriodSpinBox->setMinimum(1);
		_timePeriodSpinBox->setRange(0, INT_MAX);
		_timePeriodSpinBox->setFixedWidth(120);
		_timePeriodSpinBox->setFixedHeight(30);
		_timePeriodSpinBox->setProperty("state", "enabled");

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
		_targetDateLabel->setProperty("state", "disabled");

		_targetDateEdit = new QDateTimeEdit;
		_targetDateEdit->setFixedHeight(30);
		_targetDateEdit->setProperty("state", "disabled");

		QHBoxLayout* targetDateLayout = new QHBoxLayout;
		targetDateLayout->addWidget(_targetDateLabel);
		targetDateLayout->addWidget(_targetDateEdit);
		targetDateLayout->setSpacing(7);
		targetDateLayout->setAlignment(_targetDateLabel, Qt::AlignBottom);

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
		layout->addLayout(repeatsCountLayout);
		layout->setAlignment(repeatsCountLayout, Qt::AlignLeft);
		layout->addLayout(timePeriodLayout);
		layout->addLayout(targetDateLayout);
		layout->addLayout(cancelAndSetBtnsLayout);
		layout->setContentsMargins(15, 5, 15, 15);
		layout->setSpacing(8);

		// scriptName auto-complete setup
		_storedScripts = new QStringListModel(Scripto::GetStoredScriptsNames());
		_completer = new QCompleter(this);
		_completer->setModel(_storedScripts);
		_completer->setCaseSensitivity(Qt::CaseInsensitive);
		_completer->setFilterMode(Qt::MatchContains);
		_completer->setCompletionMode(QCompleter::PopupCompletion);
		_scriptNameLineEdit->setCompleter(_completer);

		// events
		connect(_scriptNameLineEdit, &QLineEdit::textChanged, this, &SchedulerWindow::onScriptNameChanged);
		connect(_repeatCheckBox, &QCheckBox::checkStateChanged, this, &SchedulerWindow::onRepeatCheckBoxStateChange);
		connect(_cancelBtn, &QPushButton::pressed, this, &SchedulerWindow::onCancelButtonPressed);
		connect(_setBtn, &QPushButton::pressed, this, &SchedulerWindow::onSetButtonPressed);
		connect(_typeComboBox, &QComboBox::currentTextChanged, this, &SchedulerWindow::onTypeComboBoxCurrentIndexChanged);
		
		Scripto::setOnNewScriptAddedCallback([=](const QString& scriptName){
			int row = _storedScripts->rowCount();
			_storedScripts->insertRow(row);
			_storedScripts->setData(_storedScripts->index(row), scriptName);
			qDebug() << "Updated Stored Scripts: added '" << scriptName << "'.";
		});

		Scripto::setOnScriptRemovedCallback([=](const QString& scriptName) {
			int index = _storedScripts->stringList().indexOf(scriptName);
			if (index >= 0)
				_storedScripts->removeRow(index);
			qDebug() << "Updated Stored Scripts: removed '" << scriptName << "'.";
		});

		UpdateUiStates(false);
		UpdateSaveBtnState();
	}

	void SchedulerWindow::onScriptNameChanged(const QString& text)
	{
		QString name = text.trimmed();
		if (name.isEmpty())
		{
			_scriptNameStatusLabel->setText("Script name cannot be empty");
			_scriptNameStatusLabel->setStyleSheet("color: red;");
		}
		else if (!Scripto::GetStoredScriptsNames().contains(name))
		{
			_scriptNameStatusLabel->setText("No Stored Script with the name entered.");
			_scriptNameStatusLabel->setStyleSheet("color: red;");
		}
		else if (Scripto::GetStoredScriptsNames().contains(name))
		{
			_scriptNameStatusLabel->setText("");
		}
		UpdateSaveBtnState();
	}

	void SchedulerWindow::onRepeatCheckBoxStateChange(Qt::CheckState state)
	{
		bool checked = state == Qt::Checked;

		_repeatsCountSpinBox->setProperty("state", checked ? "enabled" : "disabled");
		_repeatsCountSpinBox->setEnabled(checked);
		RefreshStyle(_repeatsCountSpinBox);
	}

	void SchedulerWindow::onTypeComboBoxCurrentIndexChanged(const QString& text)
	{
		UpdateUiStates(text == "Date" ? true : false);
	}

	void SchedulerWindow::UpdateUiStates(bool dateSelected)
	{
		_targetDateLabel->setProperty("state", dateSelected ? "enabled" : "disabled");
		RefreshStyle(_targetDateLabel);

		_targetDateEdit->setProperty("state", dateSelected ? "enabled" : "disabled");
		_targetDateEdit->setEnabled(dateSelected);
		RefreshStyle(_targetDateEdit);

		_timePeriodLabel->setProperty("state", dateSelected ? "disabled" : "enabled");
		RefreshStyle(_timePeriodLabel);

		_timePeriodSpinBox->setProperty("state", dateSelected ? "disabled" : "enabled");
		_timePeriodSpinBox->setEnabled(!dateSelected);
		RefreshStyle(_timePeriodSpinBox);

		_timeUnitComboBox->setProperty("state", dateSelected ? "disabled" : "enabled");
		_timeUnitComboBox->setEnabled(!dateSelected);
		RefreshStyle(_timeUnitComboBox);
	}

	void SchedulerWindow::UpdateSaveBtnState()
	{
		QString scriptName = _scriptNameLineEdit->text().trimmed();
		if (Scripto::GetStoredScriptsNames().contains(scriptName))
		{
			_setBtn->setEnabled(true);
			_setBtn->setProperty("state", "enabled");
			RefreshStyle(_setBtn);
		}
		else
		{
			_setBtn->setEnabled(false);
			_setBtn->setProperty("state", "disabled");
			RefreshStyle(_setBtn);
		}
	}

	void SchedulerWindow::onSetButtonPressed()
	{
		QString scriptName = _scriptNameLineEdit->text();
		bool repeat = _repeatCheckBox->isChecked();
		int repeatsCount = _repeatsCountSpinBox->value();

		if (_typeComboBox->currentText() == "Date")
		{
			QDateTime targetDate = _targetDateEdit->dateTime();
			Scripto::ScheduleScript(scriptName, targetDate, repeat, repeatsCount, nullptr, nullptr, nullptr, nullptr);
		}
		else if (_typeComboBox->currentText() == "Time Period")
		{
			int timePeriod = _timePeriodSpinBox->value(); // in millisecondss

			int unit = _timeUnitComboBox->currentIndex();
			switch (unit)
			{
			default:
			case 0: break; // milliseconds
			case 1: timePeriod *= 1000; break; // seconds
			case 2: timePeriod *= 1000 * 60; break; // minuites
			case 3: timePeriod *= 1000 * 60 * 60; break; // hours
			}

			Scripto::ScheduleScript(scriptName, timePeriod, repeat, repeatsCount, nullptr, nullptr, nullptr, nullptr);
		}

		qDebug() << "Script Scheduled Successfully: " << scriptName;
		_scriptNameLineEdit->setText("");
		_scriptNameLineEdit->setText("");
		_repeatCheckBox->setChecked(false);
		_repeatsCountSpinBox->setValue(0);
		_timePeriodSpinBox->setValue(0);
		hide();
	}

	void SchedulerWindow::onCancelButtonPressed()
	{
		this->hide();
		_scriptNameLineEdit->clear();
		_targetDateEdit->clear();
	}

	SCRIPTO_REFRESH_STYLE_FUNC_IMPL(SchedulerWindow)
}