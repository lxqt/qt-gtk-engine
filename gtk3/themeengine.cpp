/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2014  <copyright holder> <email>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "themeengine.h"
#include <QDebug>
#include <QApplication>
#include <QStyle>
#include <QPainter>
#include <QStyleOption>
#include <QImage>

ThemeEngine::ThemeEngine() {
}

ThemeEngine::~ThemeEngine() {

}

void ThemeEngine::render_line(GtkThemingEngine* engine,
                              cairo_t*          cr,
                              gdouble           x0,
                              gdouble           y0,
                              gdouble           x1,
                              gdouble           y1) {

}

void ThemeEngine::render_background(GtkThemingEngine* engine,
                                    cairo_t*          cr,
                                    gdouble           x,
                                    gdouble           y,
                                    gdouble           width,
                                    gdouble           height) {

#if 0
  const GtkWidgetPath* widgetPath = gtk_theming_engine_get_path(engine);
  GType widgetType = gtk_widget_path_get_object_type(widgetPath);
  //qDebug() << "object: " << g_type_name(widgetType);

  QStyle* style = qApp->style();
  QImage image(width, height, QImage::Format_ARGB32);
  image.fill(qApp->palette().color(QPalette::Normal, QPalette::Window));
  QPainter painter(&image);

  cairo_surface_t* surface = NULL;

  if(gtk_widget_path_is_type(widgetPath, GTK_TYPE_BUTTON)) {
    QStyleOptionButton opt;
    opt.rect = QRect(0, 0, width, height);
    opt.palette = qApp->palette();
    GtkStateFlags flag = gtk_theming_engine_get_state(engine);
    opt.state = QStyle::State_Enabled | QStyle::State_Raised; //(flag & GTK_STATE_FLAG_ACTIVE|GTK_STATE_FLAG_SELECTED) ? QStyle::State_Active : QStyle::State_None;

    if(flag & GTK_STATE_FLAG_PRELIGHT)
      opt.state |= QStyle::State_MouseOver;

    if(flag & GTK_STATE_FLAG_ACTIVE)
      opt.state |= QStyle::State_Sunken;

    // style->drawControl(QStyle::CE_PushButton, &opt, &painter);
    style->drawPrimitive(QStyle::PE_PanelButtonCommand, &opt, &painter);
    const unsigned char* data = image.constBits();
    surface = cairo_image_surface_create_for_data((unsigned char*)data, CAIRO_FORMAT_ARGB32, image.width(), image.height(), cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, image.width()));
    cairo_set_source_surface(cr, surface, 0, 0);
  }
  else if(gtk_widget_path_is_type(widgetPath, GTK_TYPE_ENTRY)) {

  }
  else if(gtk_widget_path_is_type(widgetPath, GTK_TYPE_LABEL)) {
    return;
  }
  else if(gtk_widget_path_is_type(widgetPath, GTK_TYPE_IMAGE)) {
    return;
  }
  else {
    QColor clr = qApp->palette().color(QPalette::Normal, QPalette::Window);
    cairo_set_source_rgb(cr, clr.redF(), clr.greenF(), clr.blueF());
  }

  cairo_rectangle(cr, x, y, width, height);
  cairo_paint(cr);

  if(surface)
    cairo_surface_destroy(surface);

#endif
}

void ThemeEngine::render_frame(GtkThemingEngine* engine,
                               cairo_t*          cr,
                               gdouble           x,
                               gdouble           y,
                               gdouble           width,
                               gdouble           height) {
#if 0
  cairo_save(cr);
  const GtkWidgetPath* widgetPath = gtk_theming_engine_get_path(engine);
  GType widgetType = gtk_widget_path_get_object_type(widgetPath);
  qDebug() << "object: " << g_type_name(widgetType) << x << y << width << height;
  QStyle* style = qApp->style();
  QImage image(width, height, QImage::Format_ARGB32);
  image.fill(Qt::transparent);
  QPainter painter(&image);
  cairo_surface_t* surface = NULL;
  double cx, cy, cx2, cy2;
  cairo_clip_extents(cr, &cx, &cy, &cx2, &cy2);
  qDebug() << "clip: " << cx << cy << cx2 << cy2;
  painter.setClipRect(QRectF(cx, cy, cx2 - cx, cy2 - cy));

  if(gtk_theming_engine_has_class(engine, "menuitem")) {
    QStyle::ControlElement element = QStyle::CE_MenuItem;

    if(gtk_theming_engine_has_class(engine, "menubar")) {
      element = QStyle::CE_MenuBarItem;
    }

    QStyleOptionMenuItem opt;
    opt.rect = QRect(0, 0, width, height);
    opt.palette = qApp->palette();
    GtkStateFlags flag = gtk_theming_engine_get_state(engine);
    opt.state = QStyle::State_Enabled;
    opt.state |= flag & (GTK_STATE_FLAG_PRELIGHT | GTK_STATE_FLAG_SELECTED) ? QStyle::State_Selected : QStyle::State_Enabled;
    style->drawControl(element, &opt, &painter);
    const unsigned char* data = image.constBits();
    surface = cairo_image_surface_create_for_data((unsigned char*)data, CAIRO_FORMAT_ARGB32, image.width(), image.height(), cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, image.width()));
    cairo_set_source_surface(cr, surface, 0, 0);
    qDebug() << "paint menu item";
  }

  if(surface) {
    cairo_rectangle(cr, x, y, width, height);
    cairo_fill(cr);
    cairo_surface_destroy(surface);
  }

  cairo_restore(cr);
#endif
}

void ThemeEngine::render_frame_gap(GtkThemingEngine* engine,
                                   cairo_t*          cr,
                                   gdouble           x,
                                   gdouble           y,
                                   gdouble           width,
                                   gdouble           height,
                                   GtkPositionType   gap_side,
                                   gdouble           xy0_gap,
                                   gdouble           xy1_gap) {

}

void ThemeEngine::render_extension(GtkThemingEngine* engine,
                                   cairo_t*          cr,
                                   gdouble           x,
                                   gdouble           y,
                                   gdouble           width,
                                   gdouble           height,
                                   GtkPositionType   gap_side) {

}

void ThemeEngine::render_check(GtkThemingEngine* engine,
                               cairo_t*          cr,
                               gdouble           x,
                               gdouble           y,
                               gdouble           width,
                               gdouble           height) {}
void ThemeEngine::render_option(GtkThemingEngine* engine,
                                cairo_t*          cr,
                                gdouble           x,
                                gdouble           y,
                                gdouble           width,
                                gdouble           height) {}
void ThemeEngine::render_arrow(GtkThemingEngine* engine,
                               cairo_t*          cr,
                               gdouble           angle,
                               gdouble           x,
                               gdouble           y,
                               gdouble           size) {}
void ThemeEngine::render_expander(GtkThemingEngine* engine,
                                  cairo_t*          cr,
                                  gdouble           x,
                                  gdouble           y,
                                  gdouble           width,
                                  gdouble           height) {}
void ThemeEngine::render_focus(GtkThemingEngine* engine,
                               cairo_t*          cr,
                               gdouble           x,
                               gdouble           y,
                               gdouble           width,
                               gdouble           height) {}

void ThemeEngine::render_slider(GtkThemingEngine* engine,
                                cairo_t*          cr,
                                gdouble           x,
                                gdouble           y,
                                gdouble           width,
                                gdouble           height,
                                GtkOrientation    orientation) {}
void ThemeEngine::render_handle(GtkThemingEngine* engine,
                                cairo_t*          cr,
                                gdouble           x,
                                gdouble           y,
                                gdouble           width,
                                gdouble           height) {}
void ThemeEngine::render_activity(GtkThemingEngine* engine,
                                  cairo_t*          cr,
                                  gdouble           x,
                                  gdouble           y,
                                  gdouble           width,
                                  gdouble           height) {}
