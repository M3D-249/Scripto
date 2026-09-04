#include "scriptomsgbox.h"

namespace ScriptoApp
{
ScriptoMsgBox::ScriptoMsgBox(QWidget* parent)
		: QWidget(parent)
	{
		SetupUi();
	}

	void ScriptoMsgBox::SetupUi()
	{
		// widget setup
		SCRIPTO_WIDGET_INIT
		setObjectName("scriptomsgbox");
		setWindowTitle("Scripto Msg Box");
		setFixedWidth(_width);
		setFixedHeight(_height);
		setStyleSheet("padding: 0; margin: 0;");

		// title
		_title = new QLabel("Scripto Msg Box", this);
		_title->setProperty("styleTag", "windowTitle");

		_msg = new QPlainTextEdit(this);
		_msg->setPlainText("Confirm");
		_msg->setReadOnly(true);
		_msg->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		_msg->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		_msg->setMinimumHeight(100);
		_msg->setMinimumWidth(370);
		_msg->setProperty("styleTag", "primaryTextArea");
		_msg->setProperty("state", "enabled");

		_yesBtn = new QPushButton("Confirm");
		_yesBtn->setProperty("styleTag", "darkRedBtn");
		_yesBtn->setProperty("state", "enabled");

		_noBtn = new QPushButton("Cancel");
		_noBtn->setProperty("styleTag", "darkRedBtn");
		_noBtn->setProperty("state", "disabled");

		QHBoxLayout* buttonsLayout = new QHBoxLayout;
		buttonsLayout->addWidget(_yesBtn);
		buttonsLayout->addWidget(_noBtn);
		buttonsLayout->setSpacing(10);

		QVBoxLayout* layout = new QVBoxLayout(this);
		layout->addWidget(_title);
		layout->addWidget(_msg);
		layout->addLayout(buttonsLayout);
		layout->setAlignment(_title, Qt::AlignCenter);
		layout->setAlignment(_msg, Qt::AlignCenter);
		layout->setContentsMargins(15, 5, 15, 15);
		layout->setSpacing(10);

		setAttribute(Qt::WA_DeleteOnClose);

		connect(_yesBtn, &QPushButton::pressed, this, &ScriptoMsgBox::onYesBtnClicked);
		connect(_noBtn, &QPushButton::pressed, this, &ScriptoMsgBox::onNoBtnClicked);
	}

	void ScriptoMsgBox::SetMessage(const QString& msg)
	{
		_msg->setPlainText(msg);
	}

	void ScriptoMsgBox::SetTitle(const QString& title)
	{
		_title->setText(title);
	}
	
	void ScriptoMsgBox::SetYesBtnText(const QString& text)
	{
		_yesBtn->setText(text);
	}

	void ScriptoMsgBox::SetNoBtnText(const QString& text)
	{
		_noBtn->setText(text);
	}

	void ScriptoMsgBox::onYesBtnClicked()
	{
		emit Confirmed();
		close();
	}

	void ScriptoMsgBox::onNoBtnClicked()
	{
		close();
	}
}