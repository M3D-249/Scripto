#pragma once

#include <qpushbutton.h>
#include <qlabel.h>
#include <qevent.h>
#include <qplaintextedit.h>
#include <qstringlistmodel.h>

#include "common.h"

namespace ScriptoApp
{
	// NOTE: derive from QMessageBox and do SCRIPTO_WIDGET_INIT will be better
	class ScriptoMsgBox : public QWidget
	{
		Q_OBJECT
	public:
		explicit ScriptoMsgBox(QWidget* parent = nullptr);
		void SetupUi();
		void SetMessage(const QString& msg);
		void SetTitle(const QString& title);
		void SetYesBtnText(const QString& text);
		void SetNoBtnText(const QString& text);

	signals:
		void Confirmed();

	protected:
		SCRIPTO_WIDGET_PAINT_EVENT_IMPL
		SCRIPTO_WIDGET_DRAG_IMPL(_dragOffset)

		void onNewScriptAddedCallback(const QString& name);

	private slots:
		void onYesBtnClicked();
		void onNoBtnClicked();
	private:
		int _width = 400;
		int _height = 200;
		QPoint _dragOffset;
		QStringListModel* _storedScripts;

		QLabel* _title;
		QPlainTextEdit* _msg;
		QPushButton* _yesBtn;
		QPushButton* _noBtn;
	};
}