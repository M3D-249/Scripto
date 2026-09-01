#include <qapplication.h>
#include <qfiledialog.h>
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
#include <qdialog.h>

#include <scripto.h>

#include "newscriptdialog.h"
#include "common.h"

namespace ScriptoApp
{
	NewScriptDialogWindow::NewScriptDialogWindow(QWidget* parent) : QDialog(parent)
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

		_scriptNameStatusLabel = new QLabel;
		_scriptNameStatusLabel->setFixedHeight(10);
		_scriptNameStatusLabel->setStyleSheet("color: #E0E0E0; font-size: 8px; left: 78px;");

		QVBoxLayout* scritNameEditANDStatus = new QVBoxLayout;
		scritNameEditANDStatus->addWidget(_scriptNameLineEdit);
		scritNameEditANDStatus->addWidget(_scriptNameStatusLabel);
		scritNameEditANDStatus->setSpacing(0);

		QHBoxLayout* scriptNameLayout = new QHBoxLayout;
		scriptNameLayout->addWidget(_scriptNameLabel);
		scriptNameLayout->addLayout(scritNameEditANDStatus);
		scriptNameLayout->addSpacing(7);
		scriptNameLayout->setAlignment(_scriptNameLabel, Qt::AlignTop);

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

		_scriptPathStatusLabel = new QLabel;
		_scriptPathStatusLabel->setFixedHeight(10);
		_scriptPathStatusLabel->setStyleSheet("color: #E0E0E0; font-size: 8px; left: 78px;"); // TODO: make .qss styling

		QHBoxLayout* scriptPathEdit = new QHBoxLayout;
		scriptPathEdit->addWidget(_scriptPathLineEdit);
		scriptPathEdit->addWidget(_scriptPathBrowseBtn);
		scriptPathEdit->setSpacing(7);

		QVBoxLayout* scriptPathEditAndStatusLayout = new QVBoxLayout;
		scriptPathEditAndStatusLayout->addLayout(scriptPathEdit);
		scriptPathEditAndStatusLayout->addWidget(_scriptPathStatusLabel);
		scriptPathEditAndStatusLayout->setSpacing(0);

		QHBoxLayout* scriptPathLayout = new QHBoxLayout;
		scriptPathLayout->addWidget(_scriptPathLabel);
		scriptPathLayout->addLayout(scriptPathEditAndStatusLayout);
		scriptPathLayout->setSpacing(7);
		scriptPathLayout->setAlignment(_scriptPathLabel, Qt::AlignTop);

		// script working dir
		_scriptWorkingDirPathLabel = new QLabel("Working Dir");
		_scriptWorkingDirPathLabel->setFixedWidth(78);
		_scriptWorkingDirPathLabel->setProperty("styleTag", "primaryLabel");
		_scriptWorkingDirPathLabel->setProperty("state", "enabled");

		_scriptWorkingDirLineEdit = new QLineEdit;
		_scriptWorkingDirLineEdit->setFixedHeight(30);
		_scriptWorkingDirLineEdit->setMinimumWidth(280);
		_scriptWorkingDirLineEdit->setPlaceholderText("Enter Absolute Path Working Dir...");
		_scriptWorkingDirLineEdit->setProperty("styleTag", "primaryLineEdit");
		_scriptWorkingDirLineEdit->setProperty("state", "enabled");

		_scriptWorkingDirBrowseBtn = new QPushButton("Browse...");
		_scriptWorkingDirBrowseBtn->setProperty("styleTag", "paleGreenBtn");
		_scriptWorkingDirBrowseBtn->setProperty("state", "enabled");

		QHBoxLayout* scriptWorkingDirEdit = new QHBoxLayout;
		scriptWorkingDirEdit->addWidget(_scriptWorkingDirLineEdit);
		scriptWorkingDirEdit->addWidget(_scriptWorkingDirBrowseBtn);
		scriptWorkingDirEdit->setSpacing(7);

		_scriptWorkingDirStatusLabel = new QLabel(this);
		_scriptWorkingDirStatusLabel->setFixedHeight(10);
		_scriptWorkingDirStatusLabel->setStyleSheet("color: #E0E0E0; font-size: 8px; left: 78px;"); // TODO: make .qss styling

		QVBoxLayout* scriptWorkingDirAndStatusLayout = new QVBoxLayout;
		scriptWorkingDirAndStatusLayout->addLayout(scriptWorkingDirEdit);
		scriptWorkingDirAndStatusLayout->addWidget(_scriptWorkingDirStatusLabel);
		scriptWorkingDirAndStatusLayout->setSpacing(0);

		QHBoxLayout* scriptWorkingDirLayout = new QHBoxLayout;
		scriptWorkingDirLayout->addWidget(_scriptWorkingDirPathLabel);
		scriptWorkingDirLayout->addLayout(scriptWorkingDirAndStatusLayout);
		scriptWorkingDirLayout->setSpacing(7);
		scriptWorkingDirLayout->setAlignment(_scriptWorkingDirPathLabel, Qt::AlignTop);

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
		_scriptTypeLabel->setFixedWidth(85);
		_scriptTypeLabel->setProperty("styleTag", "primaryLabel");
		_scriptTypeLabel->setProperty("state", "enabled");

		_scriptTypeComboBox = new QComboBox;
		_scriptTypeComboBox->addItems(Scripto::AllowedScriptsTypes());
		_scriptTypeComboBox->setProperty("styleTag", "primaryComboBox");
		_scriptTypeComboBox->setProperty("state", "enabled");
		_scriptTypeComboBox->setMinimumWidth(50);

		QHBoxLayout* scriptTypeLayout = new QHBoxLayout;
		scriptTypeLayout->addWidget(_scriptTypeLabel);
		scriptTypeLayout->addWidget(_scriptTypeComboBox);
		scriptTypeLayout->setSpacing(0);

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

		QVBoxLayout* layout = new QVBoxLayout(this);
		layout->addWidget(_title);
		layout->addLayout(scriptNameLayout);
		layout->addLayout(scriptPathLayout);
		layout->addLayout(scriptWorkingDirLayout);
		layout->addWidget(_inplaceCheckBox);
		layout->addLayout(scriptCodeLayout);
		layout->addLayout(scriptTypeLayout);
		layout->addLayout(cancelAndSaveLayout);

		layout->setContentsMargins(20, 5, 20, 20);
		layout->setSpacing(8);
		layout->setAlignment(_title, Qt::AlignCenter);

		// disable by default
		_scriptCodeTextEdit->setEnabled(false);
		_scriptCodeTextEdit->setProperty("state", "disabled");
		_scriptCodeLabel->setProperty("state", "disabled");
		_scriptTypeLabel->setProperty("state", "disabled");
		_scriptTypeComboBox->setEnabled(false);
		_scriptTypeComboBox->setProperty("state", "disabled");

		// setup slots
		connect(_scriptNameLineEdit, &QLineEdit::textChanged, this, &NewScriptDialogWindow::onScriptNameChanged);
		connect(_scriptPathBrowseBtn, &QPushButton::pressed, this, &NewScriptDialogWindow::onScriptPathBrowseBtnClicked);
		connect(_scriptPathLineEdit, &QLineEdit::textChanged, this, &NewScriptDialogWindow::onScriptPathChanged);
		connect(_scriptWorkingDirLineEdit, &QLineEdit::textChanged, this, &NewScriptDialogWindow::onScriptWorkingDirChanged);
		connect(_scriptWorkingDirBrowseBtn, &QPushButton::pressed, this, &NewScriptDialogWindow::onScriptWorkingDirBrowseBtnClicked);
		connect(_inplaceCheckBox, &QCheckBox::checkStateChanged, this, &NewScriptDialogWindow::onInplaceCheckBoxStateChange);
		connect(_saveBtn, &QPushButton::pressed, this, &NewScriptDialogWindow::onSaveBtnClicked);
		connect(_cancelBtn, &QPushButton::pressed, this, &NewScriptDialogWindow::onCancelButtonPressed);

		UpdateSaveBtnState();
	}

	void NewScriptDialogWindow::onScriptNameChanged(const QString& newName)
	{
		QString name = newName.trimmed();
		if (name.isEmpty())
		{
			_scriptNameStatusLabel->setText("Name cannot be empty");
			_scriptNameStatusLabel->setStyleSheet("color: red;");
		}
		else if (Scripto::GetStoredScriptsNames().contains(name))
		{
			_scriptNameStatusLabel->setText("Name already exists");
			_scriptNameStatusLabel->setStyleSheet("color: red;");
		}
		else
		{
			_scriptNameStatusLabel->setText("Available");
			_scriptNameStatusLabel->setStyleSheet("color: green;");
		}
		UpdateSaveBtnState();
	}

	void NewScriptDialogWindow::onScriptPathChanged(const QString& text)
	{
		if (text.isEmpty())
		{
			_scriptPathStatusLabel->setText("Can't be empty");
			_scriptPathStatusLabel->setStyleSheet("color: red;");
		}
		else if (!QFileInfo(text).exists() || !QFileInfo(text).isFile())
		{
			_scriptPathStatusLabel->setText("File Doesn't exist.");
			_scriptPathStatusLabel->setStyleSheet("color: red;");
		}
		else
		{
			QString extention = text.mid(text.lastIndexOf("."));
			if (Scripto::AllowedScriptsTypesFileExtentions().contains(extention))
			{
				_scriptPathStatusLabel->setText("Valid");
				_scriptPathStatusLabel->setStyleSheet("color: green;");
			}
			else
			{
				QString msg = "File Type not allowed.";
				_scriptPathStatusLabel->setText(msg);
				_scriptPathStatusLabel->setStyleSheet("color: red;");
			}
		}
		UpdateSaveBtnState();
	}

	void NewScriptDialogWindow::onScriptWorkingDirChanged(const QString& text)
	{
		if (text.isEmpty())
		{
			_scriptWorkingDirStatusLabel->setText("Can't be empty. use dot --> '.' to set it to the defaut");
			_scriptWorkingDirStatusLabel->setStyleSheet("color: red;");
		}
		else if (!QFileInfo(text).exists() || !QFileInfo(text).isDir())
		{
			_scriptWorkingDirStatusLabel->setText("Directory Doesn't exist.");
			_scriptWorkingDirStatusLabel->setStyleSheet("color: red;");
		}
		else
		{
			_scriptWorkingDirStatusLabel->setText("Valid");
			_scriptWorkingDirStatusLabel->setStyleSheet("color: green;");
		}
		UpdateSaveBtnState();
	}

	void NewScriptDialogWindow::onInplaceCheckBoxStateChange(bool checked)
	{
		_scriptCodeTextEdit->setEnabled(checked);
		_scriptCodeTextEdit->setProperty("state", checked ? "enabled" : "disabled");
		RefreshStyle(_scriptCodeTextEdit);
		
		_scriptCodeLabel->setProperty("state", checked ? "enabled" : "disabled");
		RefreshStyle(_scriptCodeLabel);

		_scriptPathLabel->setProperty("state", checked ? "disabled" : "enabled");
		RefreshStyle(_scriptPathLabel);

		_scriptPathLineEdit->setEnabled(!checked);
		_scriptPathLineEdit->setProperty("state", checked ? "disabled" : "enabled");
		RefreshStyle(_scriptPathLineEdit);

		_scriptPathBrowseBtn->setEnabled(!checked);
		_scriptPathBrowseBtn->setProperty("state", checked ? "disabled" : "enabled");
		RefreshStyle(_scriptPathBrowseBtn);

		_scriptTypeLabel->setProperty("state", checked ? "enabled" : "disabled");
		RefreshStyle(_scriptTypeLabel);

		_scriptTypeComboBox->setEnabled(checked);
		_scriptTypeComboBox->setProperty("state", checked ? "enabled" : "disabled");
		RefreshStyle(_scriptTypeComboBox);
	}

	void NewScriptDialogWindow::onScriptPathBrowseBtnClicked()
	{
		QString filePath = QFileDialog::getOpenFileName(this, "Select Script File");
		if (!filePath.isEmpty())
			_scriptPathLineEdit->setText(filePath);
	}

	void NewScriptDialogWindow::onScriptWorkingDirBrowseBtnClicked()
	{
		QString filePath = QFileDialog::getExistingDirectory(this, "Select Script Working Directory");
		if (!filePath.isEmpty())
			_scriptWorkingDirLineEdit->setText(filePath);
	}

	void NewScriptDialogWindow::onSaveBtnClicked()
	{
		QString scriptName = _scriptNameLineEdit->text();
		QString workingDir = _scriptWorkingDirLineEdit->text();
		Scripto::ScriptType type = Scripto::ScriptTypeFromString(_scriptTypeComboBox->currentText());

		if (_inplaceCheckBox->isChecked())
		{
			QString code = _scriptCodeTextEdit->toPlainText();
			// add run policy or not ?
			Scripto::AddInplaceScript(scriptName, code, workingDir, type, Scripto::RunPolicy::NormalUser);
		}
		else
		{
			QString path = _scriptPathLineEdit->text();
			QString scriptFileExtention = path.mid(path.lastIndexOf("."));
			Scripto::ScriptType type = Scripto::ScriptTypeFromExtentionString(scriptFileExtention);
			// add run policy or not ?
			Scripto::AddScript(scriptName, path, workingDir, type, Scripto::RunPolicy::NormalUser);
		}

		accept();
	}

	void NewScriptDialogWindow::onCancelButtonPressed()
	{
		this->hide();
		_scriptNameLineEdit->setText("");
		_scriptPathLineEdit->setText("");
		_scriptCodeTextEdit->setPlainText("");
		_inplaceCheckBox->setCheckState(Qt::Unchecked);
	}

	void NewScriptDialogWindow::UpdateSaveBtnState()
	{
		QString scriptName = _scriptNameLineEdit->text();
		QString scriptWorkingDir = _scriptWorkingDirLineEdit->text();

		if (IsValidDir(scriptWorkingDir) && IsValidScriptName(scriptName))
		{
			if (_inplaceCheckBox->isChecked())
			{
				_saveBtn->setEnabled(true);
				_saveBtn->setProperty("state", "enabled");
				RefreshStyle(_saveBtn);
			}
			else
			{
				QString scriptPath = _scriptPathLineEdit->text();
				if (IsValidScriptFile(scriptPath))
				{
					_saveBtn->setEnabled(true);
					_saveBtn->setProperty("state", "enabled");
					RefreshStyle(_saveBtn);
				}
			}
		}
		else
		{
			_saveBtn->setEnabled(false);
			_saveBtn->setProperty("state", "disabled");
			RefreshStyle(_saveBtn);
		}
	}

	bool NewScriptDialogWindow::IsValidScriptName(const QString& name)
	{
		return !name.trimmed().isEmpty() && !Scripto::GetStoredScriptsNames().contains(name.trimmed());
	}

	bool NewScriptDialogWindow::IsValidDir(const QString& path)
	{
		return QFileInfo(path).exists() && QFileInfo(path).isDir();
	}

	bool NewScriptDialogWindow::IsValidScriptFile(const QString& path)
	{
		if (QFileInfo(path).exists() && QFileInfo(path).isFile())
		{
			QString extention = QFileInfo(path).filePath().mid(QFileInfo(path).filePath().lastIndexOf("."));
			return Scripto::AllowedScriptsTypesFileExtentions().contains(extention);
		}
		return false;
	}

	SCRIPTO_REFRESH_STYLE_FUNC_IMPL(NewScriptDialogWindow)
}