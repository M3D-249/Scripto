#include <qpushbutton.h>
#include <qcompleter.h>
#include <qgraphicseffect.h>
#include <qpropertyanimation.h>
#include <qmessagebox.h>

#include "removescriptdialog.h"
#include "scriptomsgbox.h"

namespace ScriptoApp
{
	RemoveScriptDialog::RemoveScriptDialog(QWidget* parent) : QDialog(parent)
	{
		SetupUi();
	}

	void RemoveScriptDialog::SetupUi()
	{
		// widget setup
		SCRIPTO_WIDGET_INIT
		setObjectName("removescriptdialog");
		setWindowTitle("Remove Script Dialog");
		setFixedWidth(_width);
		setFixedHeight(_height);
		setStyleSheet("padding: 0; margin: 0;");

		// title
		_title = new QLabel("Remove Script Dialog", this);
		_title->setProperty("styleTag", "windowTitle");

		// Script Name
		_scriptNameLabel = new QLabel("Script Name");
		_scriptNameLabel->setFixedWidth(78);
		_scriptNameLabel->setProperty("styleTag", "primaryLabel");
		_scriptNameLabel->setProperty("state", "enabled");

		_scriptNameLineEdit = new QLineEdit;
		_scriptNameLineEdit->setPlaceholderText("Script To Remove...");
		_scriptNameLineEdit->setProperty("styleTag", "primaryLineEdit");
		_scriptNameLineEdit->setProperty("state", "enabled");

		QHBoxLayout* scriptNameLayout = new QHBoxLayout;
		scriptNameLayout->addWidget(_scriptNameLabel);
		scriptNameLayout->addWidget(_scriptNameLineEdit);
		scriptNameLayout->addSpacing(7);

		// remove & cancel buttons
		_removeBtn = new QPushButton("Remove");
		_removeBtn->setProperty("styleTag", "darkRedBtn");
		_removeBtn->setProperty("state", "enabled");

		_cancelBtn = new QPushButton("Cancel");
		_cancelBtn->setProperty("styleTag", "darkRedBtn");
		_cancelBtn->setProperty("state", "disabled");

		QHBoxLayout* cancelAndSaveLayout = new QHBoxLayout;
		cancelAndSaveLayout->addWidget(_removeBtn);
		cancelAndSaveLayout->addWidget(_cancelBtn);
		cancelAndSaveLayout->setSpacing(7);

		QVBoxLayout* layout = new QVBoxLayout(this);
		layout->addWidget(_title);
		layout->addLayout(scriptNameLayout);
		layout->addLayout(cancelAndSaveLayout);
		layout->setContentsMargins(15, 2, 15, 15);
		layout->setAlignment(_title, Qt::AlignCenter);

		// search bar auto-complete setup
		_storedScripts = new QStringListModel(Scripto::GetStoredScriptsNames());
		_completer = new QCompleter(this);
		_completer->setModel(_storedScripts);
		_completer->setCaseSensitivity(Qt::CaseInsensitive);
		_completer->setFilterMode(Qt::MatchContains);
		_completer->setCompletionMode(QCompleter::PopupCompletion);
		_scriptNameLineEdit->setCompleter(_completer);

		// setup slots
		connect(_removeBtn, &QPushButton::pressed, this, &RemoveScriptDialog::onRemoveBtnPressed);
		connect(_cancelBtn, &QPushButton::pressed, this, &RemoveScriptDialog::onCancelBtnPressed);
		
		int id1 = Scripto::setOnNewScriptAddedCallback(std::bind(&RemoveScriptDialog::onNewScriptAddedCallback, this, std::placeholders::_1));
		
		Scripto::setOnScriptRemovedCallback([=](const QString& scriptName) {
			int index = _storedScripts->stringList().indexOf(scriptName);
			if (index >= 0)
				_storedScripts->removeRow(index);
			qDebug() << "Updated Stored Scripts: removed '" << scriptName << "'.";
		});
	}

	void RemoveScriptDialog::onNewScriptAddedCallback(const QString& scriptName)
	{
		int row = _storedScripts->rowCount();
		_storedScripts->insertRow(row);
		_storedScripts->setData(_storedScripts->index(row), scriptName);
		qDebug() << "Updated Stored Scripts: added '" << scriptName << "'.";
	}

	void RemoveScriptDialog::onRemoveBtnPressed()
	{
		QString scriptName = _scriptNameLineEdit->text();
		QString confirmationMsg = QString("You are attempting to Remove Script with name '%1', this action is irreversible Are you sure you want to proceed?").arg(scriptName);
		//QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirm Remove", confirmationMsg, QMessageBox::Yes, QMessageBox::No,);
		
		auto box = new ScriptoMsgBox();
		box->SetMessage(confirmationMsg);
		connect(box, &ScriptoMsgBox::Confirmed, this, [=] {
			if (Scripto::RemoveScript(scriptName))
			{
				//QMessageBox::information(this, "Notification", "Script Removed Successfully.", QMessageBox::Ok);
				close();
			}
			else
				//QMessageBox::information(this, "Notification", "Failed to Remove Script!", QMessageBox::Ok);
			_scriptNameLineEdit->setText("");
		});
		box->show();
	}

	void RemoveScriptDialog::onCancelBtnPressed()
	{
		_scriptNameLineEdit->setText("");
		CloseFadeOut();
	}

	void RemoveScriptDialog::ShowFadeIn()
	{
		auto* effect = new QGraphicsOpacityEffect(this);
		setGraphicsEffect(effect);

		auto* animation = new QPropertyAnimation(effect, "opacity", this);
		animation->setDuration(200);
		animation->setStartValue(0.0);
		animation->setEndValue(1.0);
		animation->setEasingCurve(QEasingCurve::InCubic);
		animation->start(QAbstractAnimation::DeleteWhenStopped);

		show();
	}

	void RemoveScriptDialog::CloseFadeOut()
	{
		auto* effect = new QGraphicsOpacityEffect(this);
		setGraphicsEffect(effect);

		auto* animation = new QPropertyAnimation(effect, "opacity", this);
		animation->setDuration(300);
		animation->setStartValue(1.0);
		animation->setEndValue(0.0);
		animation->setEasingCurve(QEasingCurve::InCubic);

		animation->start(QAbstractAnimation::DeleteWhenStopped);
		connect(animation, &QPropertyAnimation::finished, this, [=] {
			hide();
		});
	}
}