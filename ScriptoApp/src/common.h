#pragma once

#pragma once

#include <qwidget.h>
#include <qscreen.h>
#include <qlineedit.h>
#include <qboxlayout.h>
#include <qlabel.h>
#include <qfile.h>
#include <qpainter.h>
#include <qpainterpath.h>

#define SCRIPTO_WIDGET_INIT \
			setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint); \
			setAttribute(Qt::WA_TranslucentBackground); \
			setStyleSheet("padding: 0; margin: 0;");

#define SCRIPTO_WIDGET_PAINT_EVENT_IMPL \
			void paintEvent(QPaintEvent* event) override \
			{ \
				Q_UNUSED(event); \
				QColor backgroundColor(17, 17, 17); \
				int radius = 10; \
				\
				QBitmap bitmap(width(), height()); \
				bitmap.fill(backgroundColor); \
				\
				QPainter maskPainter(&bitmap); \
				maskPainter.setRenderHint(QPainter::Antialiasing); \
				\
				QPainterPath painterPath; \
				painterPath.addRoundedRect(rect(), radius, radius); \
				maskPainter.fillPath(painterPath, backgroundColor); \
				\
				setMask(bitmap); \
				\
				QPainter painter(this); \
				painter.setRenderHint(QPainter::Antialiasing); \
				painter.setBrush(backgroundColor); \
				painter.drawRoundedRect(rect(), radius, radius); \
			}

#define SCRIPTO_SET_THEME_FUNC_DECL void SetTheme(bool dark);
#define SCRIPTO_SET_THEME_FUNC_IMPL(class_name) \
			void class_name::SetTheme(bool dark) \
			{ \
				QString path = dark ? "resources/themes/dark.qss" : "resources/themes/light.qss"; \
				QFile file(path); \
				if (file.open(QFile::ReadOnly | QFile::Text)) \
					qApp->setStyleSheet(QLatin1String(file.readAll())); \
				else \
					qDebug() << "Failed to open theme file '" << path << "'"; \
			}