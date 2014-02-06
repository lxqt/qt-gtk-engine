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

#ifndef THEMEENGINE_H
#define THEMEENGINE_H

#include <gtk/gtk.h>

class ThemeEngine {
public:
  ThemeEngine();
  ~ThemeEngine();

  void render_line(GtkThemingEngine* engine,
                          cairo_t*          cr,
                          gdouble           x0,
                          gdouble           y0,
                          gdouble           x1,
                          gdouble           y1);

  void render_background(GtkThemingEngine* engine,
                                cairo_t*          cr,
                                gdouble           x,
                                gdouble           y,
                                gdouble           width,
                                gdouble           height);

  void render_frame(GtkThemingEngine* engine,
                           cairo_t*          cr,
                           gdouble           x,
                           gdouble           y,
                           gdouble           width,
                           gdouble           height);

  void render_frame_gap(GtkThemingEngine* engine,
                               cairo_t*          cr,
                               gdouble           x,
                               gdouble           y,
                               gdouble           width,
                               gdouble           height,
                               GtkPositionType   gap_side,
                               gdouble           xy0_gap,
                               gdouble           xy1_gap);
  void render_extension(GtkThemingEngine* engine,
                               cairo_t*          cr,
                               gdouble           x,
                               gdouble           y,
                               gdouble           width,
                               gdouble           height,
                               GtkPositionType   gap_side);
  void render_check(GtkThemingEngine* engine,
                           cairo_t*          cr,
                           gdouble           x,
                           gdouble           y,
                           gdouble           width,
                           gdouble           height);
  void render_option(GtkThemingEngine* engine,
                            cairo_t*          cr,
                            gdouble           x,
                            gdouble           y,
                            gdouble           width,
                            gdouble           height);
  void render_arrow(GtkThemingEngine* engine,
                           cairo_t*          cr,
                           gdouble           angle,
                           gdouble           x,
                           gdouble           y,
                           gdouble           size);
  void render_expander(GtkThemingEngine* engine,
                              cairo_t*          cr,
                              gdouble           x,
                              gdouble           y,
                              gdouble           width,
                              gdouble           height);
  void render_focus(GtkThemingEngine* engine,
                           cairo_t*          cr,
                           gdouble           x,
                           gdouble           y,
                           gdouble           width,
                           gdouble           height);

  void render_slider(GtkThemingEngine* engine,
                            cairo_t*          cr,
                            gdouble           x,
                            gdouble           y,
                            gdouble           width,
                            gdouble           height,
                            GtkOrientation    orientation);
  void render_handle(GtkThemingEngine* engine,
                            cairo_t*          cr,
                            gdouble           x,
                            gdouble           y,
                            gdouble           width,
                            gdouble           height);
  void render_activity(GtkThemingEngine* engine,
                              cairo_t*          cr,
                              gdouble           x,
                              gdouble           y,
                              gdouble           width,
                              gdouble           height);
};

#endif // THEMEENGINE_H
