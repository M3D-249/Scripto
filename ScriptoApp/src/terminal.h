#pragma once

#include <qwidget.h>
#include <qscreen.h>
#include <qlineedit.h>
#include <qboxlayout.h>
#include <qlabel.h>
#include <qfile.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qtextedit.h>
#include <qevent.h>
#include <qplaintextedit.h>

#include "common.h"

namespace ScriptoApp
{
	class TerminalWindow : public QWidget
	{
	public:
		TerminalWindow(QWidget* parent = nullptr);

		/* called automaticalley when the object is created */
		void SetupUi();
		/* changes app theme */
		SCRIPTO_SET_THEME_FUNC_DECL
		/* doesn't append \n at the end  of text */
		void Print(const QString& line, const QColor& color = QColor(150, 150, 150));
		/* appends \n at the end of the text */
		void PrintLine(const QString& line, const QColor& color = QColor(150, 150, 150));

	protected:
		SCRIPTO_WIDGET_PAINT_EVENT_IMPL
		SCRIPTO_WIDGET_DRAG_IMPL(_dragOffset)
	private:
		QScreen* _screen;
		QPlainTextEdit* _outputText;
		QLineEdit* _inputLineEdit;
		QLabel* _inputLabel;
		const int _width = 380;
		const int _height = 210;
		QPoint _dragOffset;
	};
}