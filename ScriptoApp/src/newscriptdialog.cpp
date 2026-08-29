#include <qapplication.h>

#include "newscriptdialog.h"
#include "common.h"

namespace ScriptoApp
{
	NewScriptDialogWindow::NewScriptDialogWindow(QWidget* parent) : QWidget(parent)
	{
		SetupUi();
	}

	void NewScriptDialogWindow::SetupUi()
	{
		SCRIPTO_WIDGET_INIT

		setObjectName("newscriptdialog");
		setWindowTitle("New Script Dialog");
		setFixedSize(_width, _height);
		setStyleSheet("padding: 0; margin: 0;");
		
		// window title
		_title = new QLabel("New Script Dialog");
		_title->setProperty("styleTag", "windowTitle");

		// script name
		_scriptNameLabel = new QLabel("Script Name");
		_scriptNameLabel->setFixedWidth(78);
		_scriptNameLabel->setProperty("styleTag", "primaryLabel");
		_scriptNameLabel->setProperty("state", "enabled");

		_scriptNameLineEdit = new QLineEdit;
		_scriptNameLineEdit->setFixedHeight(30);
		_scriptNameLineEdit->setFixedWidth(375);
		_scriptNameLineEdit->setPlaceholderText("Enter Script Name...");
		_scriptNameLineEdit->setProperty("styleTag", "primaryLineEdit");
		_scriptNameLineEdit->setProperty("state", "enabled");

		QHBoxLayout* scriptNameLayout = new QHBoxLayout;
		scriptNameLayout->addWidget(_scriptNameLabel);
		scriptNameLayout->addWidget(_scriptNameLineEdit);
		scriptNameLayout->addSpacing(7);

		// script path
		_scriptPathLabel = new QLabel("Script Path");
		_scriptPathLabel->setFixedWidth(78);
		_scriptPathLabel->setProperty("styleTag", "primaryLabel");
		_scriptPathLabel->setProperty("state", "enabled");

		_scriptPathLineEdit = new QLineEdit;
		_scriptPathLineEdit->setFixedHeight(30);
		_scriptPathLineEdit->setMinimumWidth(280);
		_scriptPathLineEdit->setPlaceholderText("Enter Absolute Path to Script...");
		_scriptPathLineEdit->setProperty("styleTag", "primaryLineEdit");
		_scriptPathLineEdit->setProperty("state", "enabled");

		_scriptPathBrowseBtn = new QPushButton("Browse...");
		_scriptPathBrowseBtn->setProperty("styleTag", "paleGreenBtn");
		_scriptPathBrowseBtn->setProperty("state", "enabled");

		QHBoxLayout* scriptPathLayout = new QHBoxLayout;
		scriptPathLayout->addWidget(_scriptPathLabel);
		scriptPathLayout->addWidget(_scriptPathLineEdit);
		scriptPathLayout->addWidget(_scriptPathBrowseBtn);
		scriptPathLayout->setSpacing(7);

		// inplace script
		_inplaceCheckBox = new QCheckBox("Inplace Script");
		_inplaceCheckBox->setCheckState(Qt::Unchecked);

		// script code
		_scriptCodeLabel = new QLabel("Script Code");
		_scriptCodeLabel->setFixedWidth(78);
		_scriptCodeLabel->setProperty("styleTag", "primaryLabel");
		
		_scriptCodeTextEdit = new QPlainTextEdit;
		_scriptCodeTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		_scriptCodeTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		_scriptCodeTextEdit->setMinimumHeight(130);
		_scriptCodeTextEdit->setMinimumWidth(365);
		_scriptCodeTextEdit->setProperty("styleTag", "primaryTextArea");

		QHBoxLayout* scriptCodeLayout = new QHBoxLayout;
		scriptCodeLayout->addWidget(_scriptCodeLabel);
		scriptCodeLayout->addWidget(_scriptCodeTextEdit);
		scriptCodeLayout->setAlignment(_scriptCodeLabel, Qt::AlignTop);
		scriptCodeLayout->setSpacing(7);

		// script type
		_scriptTypeLabel = new QLabel("Script Type");
		_scriptTypeLabel->setFixedWidth(78);
		_scriptTypeLabel->setProperty("styleTag", "primaryLabel");

		_scriptTypeComboBox = new QComboBox;
		_scriptTypeComboBox->addItems({ "python", "bash", "shell", "lua" });
		_scriptTypeComboBox->setProperty("styleTag", "primaryComboBox");
		_scriptTypeComboBox->setMinimumWidth(50);

		QHBoxLayout* scriptTypeLayout = new QHBoxLayout;
		scriptTypeLayout->addWidget(_scriptTypeLabel);
		scriptTypeLayout->addWidget(_scriptTypeComboBox);
		scriptTypeLayout->setSpacing(7);

		// cancel & save buttons
		_saveBtn = new QPushButton("Save");
		_saveBtn->setProperty("styleTag", "paleGreenBtn");
		_saveBtn->setProperty("state", "enabled");

		_cancelBtn = new QPushButton("Cancel");
		_cancelBtn->setProperty("styleTag", "darkRedBtn");
		_cancelBtn->setProperty("state", "enabled");

		QHBoxLayout* cancelAndSaveLayout = new QHBoxLayout;
		cancelAndSaveLayout->addWidget(_saveBtn);
		cancelAndSaveLayout->addWidget(_cancelBtn);
		cancelAndSaveLayout->setSpacing(7);

		QHBoxLayout* BottomLayout = new QHBoxLayout;
		BottomLayout->addLayout(scriptTypeLayout);
		BottomLayout->addStretch(1);
		BottomLayout->addLayout(cancelAndSaveLayout);


		QVBoxLayout* layout = new QVBoxLayout(this);
		layout->addWidget(_title);
		layout->addLayout(scriptNameLayout);
		layout->addLayout(scriptPathLayout);
		layout->addWidget(_inplaceCheckBox);
		layout->addLayout(scriptCodeLayout);
		layout->addLayout(BottomLayout);

		layout->setContentsMargins(20, 5, 20, 20);
		layout->setSpacing(7);
		layout->setAlignment(_title, Qt::AlignCenter);

		SetTheme(true);

		// disable by default
		_scriptCodeTextEdit->setEnabled(false);
		_scriptCodeTextEdit->setProperty("state", "disabled");
		_scriptTypeComboBox->setEnabled(false);
		_scriptTypeComboBox->setProperty("state", "disabled");
		_scriptCodeLabel->setProperty("state", "disabled");
		_scriptTypeLabel->setProperty("state", "disabled");

		// events
		connect(_inplaceCheckBox, &QCheckBox::checkStateChanged, this, &NewScriptDialogWindow::onInplaceCheckBoxStateChange);
		connect(_cancelBtn, &QPushButton::pressed, this, &NewScriptDialogWindow::onCancelButtonPressed);
	}

	void NewScriptDialogWindow::onInplaceCheckBoxStateChange(bool checked)
	{
		_scriptCodeTextEdit->setEnabled(checked);
		_scriptCodeTextEdit->setProperty("state", checked ? "enabled" : "disabled");
		RefreshStyle(_scriptCodeTextEdit);
		
		_scriptTypeComboBox->setEnabled(checked);
		_scriptTypeComboBox->setProperty("state", checked ? "enabled" : "disabled");
		RefreshStyle(_scriptTypeComboBox);
		
		_scriptCodeLabel->setProperty("state", checked ? "enabled" : "disabled");
		RefreshStyle(_scriptCodeLabel);
		
		_scriptTypeLabel->setProperty("state", checked ? "enabled" : "disabled");
		RefreshStyle(_scriptTypeLabel);

		_scriptPathLabel->setProperty("state", checked ? "disabled" : "enabled");
		RefreshStyle(_scriptPathLabel);

		_scriptPathLineEdit->setEnabled(!checked);
		_scriptPathLineEdit->setProperty("state", checked ? "disabled" : "enabled");
		RefreshStyle(_scriptPathLineEdit);

		_scriptPathBrowseBtn->setEnabled(!checked);
		_scriptPathBrowseBtn->setProperty("state", checked ? "disabled" : "enabled");
		RefreshStyle(_scriptPathBrowseBtn);
	}

	void NewScriptDialogWindow::RefreshStyle(QWidget* widget)
	{
		widget->style()->unpolish(widget);
		widget->style()->polish(widget);
		widget->update();
	}

	void NewScriptDialogWindow::onCancelButtonPressed()
	{
		this->hide();
	}

	SCRIPTO_SET_THEME_FUNC_IMPL(NewScriptDialogWindow)
}