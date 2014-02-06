/*
 * Utility class used to paint stuff from QPainter to cairo_t
 * Copyright (C) 2014  Hong Jen Yee (PCMan) <pcman.tw@gmail.com>
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

#include "themepainter.h"
#include <QApplication>
#include <QStyleOption>

ThemePainter::ThemePainter(cairo_t* cr, double x, double y, double width, double height, QStyleOption& opt):
  cr_(cr),
  x_(x),
  y_(y),
  buffer_(width, height, QImage::Format_ARGB32) {
  buffer_.fill(qApp->palette().color(QPalette::Normal, QPalette::Window));

  cairo_save(cr_);
  opt.rect = QRect(0, 0, width, height);
  opt.palette = qApp->palette();

  painter_.begin(&buffer_);
}

ThemePainter::~ThemePainter() {
  painter_.end();

  const unsigned char* data = buffer_.constBits();
  int stride_width = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, buffer_.width());
  cairo_surface_t* surface = cairo_image_surface_create_for_data((unsigned char*)data, CAIRO_FORMAT_ARGB32, buffer_.width(), buffer_.height(), stride_width);
  cairo_set_source_surface(cr_, surface, 0, 0);
  // cairo_paint(cr_);
  cairo_rectangle(cr_, x_, y_, buffer_.width(), buffer_.height());
  cairo_fill(cr_);
  cairo_surface_destroy(surface);

  cairo_restore(cr_);
}
