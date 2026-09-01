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

/* custom paint function to draw frameless widgets with round corners */
#define SCRIPTO_WIDGET_INIT \
			setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint); \
			setAttribute(Qt::WA_TranslucentBackground); \
			setStyleSheet("padding: 0; margin: 0;");

/* takes a pointer to QWidget */
#define SCRIPTO_WIDGET_INIT_OBJ(widget) \
			widget->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint); \
			widget->setAttribute(Qt::WA_TranslucentBackground); \
			widget->setStyleSheet("padding: 0; margin: 0;");

/* custom paint function to draw frameless widgets with round corners */
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
			}\

/* alows for light/dark theme changing */
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

/* requires a memeber variable of type QPoint, pass the name of the this variable to the macro */
#define SCRIPTO_WIDGET_DRAG_IMPL(offset) \
			void mousePressEvent(QMouseEvent* e) override \
			{ \
				if (e->button() == Qt::LeftButton) \
				{ \
					offset = e->globalPosition().toPoint() - frameGeometry().topLeft(); \
					e->accept(); \
				} \
			} \
			\
			void mouseMoveEvent(QMouseEvent* e) override \
			{ \
				if (e->buttons() & Qt::LeftButton) \
				{ \
					move(e->globalPosition().toPoint() - offset); \
					e->accept(); \
				} \
			}

/* forces qt to re-evaluate all qss properties, called whenever custom properties are changed at runtime */
#define SCRIPTO_REFRESH_STYLE_FUNC_DECL void RefreshStyle(QWidget* widget);
#define SCRIPTO_REFRESH_STYLE_FUNC_IMPL(className) \
				void className::RefreshStyle(QWidget* widget) \
				{ \
					widget->style()->unpolish(widget); \
					widget->style()->polish(widget); \
					widget->update(); \
				}