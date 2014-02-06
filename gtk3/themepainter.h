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

#ifndef THEMEPAINTER_H
#define THEMEPAINTER_H

#include <cairo.h>
#include <QPainter>
#include <QImage>

class QStyleOption;

class ThemePainter {
public:
  ThemePainter(cairo_t* cr, double x, double y, double width, double height, QStyleOption& opt);
  ~ThemePainter();
  
  QPainter* painter() {
    return &painter_;
  }

  QImage& buffer() {
    return buffer_;
  }
  
  cairo_t* cairo() {
    return cr_;
  }

private:
  QPainter painter_;
  QImage buffer_;
  cairo_t* cr_;
  double x_;
  double y_;
};

#endif // THEMEPAINTER_H
