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
#include <QDebug>

ThemePainter::ThemePainter(cairo_t* cr, double x, double y, double width, double height, QStyleOption& opt):
  cr_(cr),
  x_(x),
  y_(y),
  buffer_(width, height, QImage::Format_ARGB32) {

  const unsigned char* data = buffer_.constBits();
  int stride_width = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, buffer_.width());
  surface_ = cairo_image_surface_create_for_data((unsigned char*)data, CAIRO_FORMAT_ARGB32, buffer_.width(), buffer_.height(), stride_width);

  buffer_.fill(Qt::transparent); // FIXME: is this needed?
  // NOTE: when painting rounded rectangles, QPainter uses antialiasing
  // some colors will be blended with the current content.
  // So theoratically we need to copy current content of cairo to QPainter to
  // get perfect pixel-exact rendering. This is a little bit wasteful, though.
  // FIXME: is there a better way to do this?

  // copy current content of cr to our buffer
  // Reference: http://lists.cairographics.org/archives/cairo/2007-June/010877.html
  cairo_t* cr2 = cairo_create(surface_);
  cairo_matrix_t matrix;
  cairo_get_matrix(cr, &matrix);
  cairo_set_source_surface(cr2, cairo_get_target(cr), -matrix.x0, -matrix.y0);
  cairo_paint(cr2);
  cairo_destroy(cr2);

  opt.rect = QRect(0, 0, width, height);
  opt.palette = qApp->palette();

  painter_.begin(&buffer_);
}

ThemePainter::~ThemePainter() {
  painter_.end();

  cairo_set_source_surface(cr_, surface_, x_, y_);
  // cairo_mask_surface(cr_, surface, x_, y_);
  cairo_paint(cr_);
  // cairo_rectangle(cr_, x_, y_, buffer_.width(), buffer_.height());
  // cairo_fill(cr_);
  cairo_surface_destroy(surface_);
}
