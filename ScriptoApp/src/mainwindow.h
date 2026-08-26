#pragma once

#include <qwidget.h>
#include <qscreen.h>
#include <qlineedit.h>
#include <qboxlayout.h>
#include <qlabel.h>
#include <qfile.h>
#include <qpainter.h>
#include <qpainterpath.h>

#include "common.h"

namespace Scripto
{

	class ScriptoMainWindow : public QWidget
	{
	public:
		ScriptoMainWindow(QWidget* parent = nullptr);

		/* called automaticalley when the object is created */
		void SetupUi();
		/* changes app theme */
		SCRIPTO_SET_THEME_FUNC_DECL

	protected:
		SCRIPTO_WIDGET_PAINT_EVENT_IMPL

	private:
		QScreen* _screen;
		QLineEdit* _searchBar;
		QLabel* _title;
		const int _width = 500;
		const int _height = 70;
	};
}