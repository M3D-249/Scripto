#include <qapplication.h>

#include "newscriptdialog.h"
#include "common.h"

namespace Scripto
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
		_title->setStyleSheet("color: #E0E0E0; font-size: 14px");

		// script name
		_scriptNameLabel = new QLabel("Script Name");
		_scriptNameLabel->setFixedWidth(75);
		_scriptNameLabel->setStyleSheet("color: #E0E0E0; font-size: 14px");

		_scriptNameLineEdit = new QLineEdit;
		_scriptNameLineEdit->setFixedHeight(30);
		_scriptNameLineEdit->setMinimumWidth(350);
		_scriptNameLineEdit->setPlaceholderText("Enter Script Name...");
		_scriptNameLineEdit->setStyleSheet("background-color: #262626; color: #E0E0E0; border-radius: 5px; padding: 3px; font-size: 14px; ");

		QHBoxLayout* scriptNameLayout = new QHBoxLayout;
		scriptNameLayout->addWidget(_scriptNameLabel);
		scriptNameLayout->addWidget(_scriptNameLineEdit);
		scriptNameLayout->addSpacing(7);

		// script path
		_scriptPathLabel = new QLabel("Script Path");
		_scriptPathLabel->setFixedWidth(78);
		_scriptPathLabel->setStyleSheet("color: #E0E0E0; font-size: 14px");

		_scriptPathLineEdit = new QLineEdit;
		_scriptPathLineEdit->setFixedHeight(30);
		_scriptPathLineEdit->setMinimumWidth(280);
		_scriptPathLineEdit->setPlaceholderText("Enter Absolute Path to Script...");
		_scriptPathLineEdit->setStyleSheet("background-color: #262626; color: #E0E0E0; border-radius: 5px; padding: 3px; font-size: 14px; ");

		_scriptPathBrowseBtn = new QPushButton("Browse...");
		_scriptPathBrowseBtn->setStyleSheet("background-color: #3B783B; border-radius: 5px; padding: 5px; color: #E0E0E0; font-size: 10px");
		_scriptPathBrowseBtn->setFixedHeight(30);

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
		_scriptCodeLabel->setStyleSheet("color: #E0E0E0; font-size: 14px");
		
		_scriptCodeTextEdit = new QPlainTextEdit;
		_scriptCodeTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		_scriptCodeTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		_scriptCodeTextEdit->setMinimumHeight(130);
		_scriptCodeTextEdit->setMinimumWidth(365);
		_scriptCodeTextEdit->setStyleSheet("background-color: #262626; color: #E0E0E0; border-radius: 5px; padding: 3px; font-size: 12px; ");

		QHBoxLayout* scriptCodeLayout = new QHBoxLayout;
		scriptCodeLayout->addWidget(_scriptCodeLabel);
		scriptCodeLayout->addWidget(_scriptCodeTextEdit);
		scriptCodeLayout->setAlignment(_scriptCodeLabel, Qt::AlignTop);
		scriptCodeLayout->setSpacing(7);

		// script type
		_scriptTypeLabel = new QLabel("Script Type");
		_scriptTypeLabel->setFixedWidth(78);
		_scriptTypeLabel->setStyleSheet("color: #E0E0E0; font-size: 14px");

		_scriptTypeComboBox = new QComboBox;
		_scriptTypeComboBox->addItems({ "python", "bash", "shell", "lua" });
		_scriptTypeComboBox->setStyleSheet("background-color: #262626; color: #E0E0E0; border-radius: 5px; padding: 3px; font-size: 12px; ");
		_scriptTypeComboBox->setMinimumWidth(50);


		QHBoxLayout* scriptTypeLayout = new QHBoxLayout;
		scriptTypeLayout->addWidget(_scriptTypeLabel);
		scriptTypeLayout->addWidget(_scriptTypeComboBox);
		scriptTypeLayout->setSpacing(7);

		// cancel & save buttons
		_saveBtn = new QPushButton("Save");
		_saveBtn->setStyleSheet("background-color: #3B783B; border-radius: 5px; padding: 5px; color: #E0E0E0; font-size: 14px");
		_saveBtn->setFixedHeight(30);
		_saveBtn->setFixedWidth(50);

		_cancelBtn = new QPushButton("Cancel");
		_cancelBtn->setStyleSheet("background-color: #A00303; border-radius: 5px; padding: 5px; color: #E0E0E0; font-size: 14px");
		_cancelBtn->setFixedHeight(30);
		_cancelBtn->setFixedWidth(50);

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
		layout->setSpacing(10);
		layout->setAlignment(_title, Qt::AlignCenter);

		SetTheme(true);
	}

	SCRIPTO_SET_THEME_FUNC_IMPL(NewScriptDialogWindow)
}