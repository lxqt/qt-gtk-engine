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

#include "cssprovider.h"
#include <QLatin1String>
#include <QApplication>
#include <QPalette>
#include <QByteArray>
#include <QTextStream>
#include <QDebug>

GtkCssProvider* qt_css_provider_new() {
  QStyle* style = qApp->style();
  QByteArray str;
  QTextStream stream(&str);
  stream << "* {\n" <<
  "background-color:" << qApp->palette().color(QPalette::Normal, QPalette::Window).name() << ";\n" <<
  "color:" << qApp->palette().color(QPalette::Normal, QPalette::WindowText).name() << ";\n" <<
  "}\n"

  "*:insensitive {\n" <<
  "background-color:" << qApp->palette().color(QPalette::Disabled, QPalette::Window).name() << ";\n" <<
  "color:" << qApp->palette().color(QPalette::Disabled, QPalette::WindowText).name() << ";\n" <<
  "}\n"

  ".entry:selected {\n"
  "background-color:" << qApp->palette().color(QPalette::Normal, QPalette::Highlight).name() << ";\n" <<
  "color:" << qApp->palette().color(QPalette::Normal, QPalette::HighlightedText).name() << ";\n" <<
  "}\n"

  "GtkTextView," 
  "GtkTreeView {\n"
  "background-color:" << qApp->palette().color(QPalette::Normal, QPalette::Base).name() << ";\n" <<
  "color:" << qApp->palette().color(QPalette::Normal, QPalette::Text).name() << ";\n" <<
  "}\n"

  "GtkButton {\n"
  "background-color:" << qApp->palette().color(QPalette::Normal, QPalette::Button).name() << ";\n" <<
  "color:" << qApp->palette().color(QPalette::Normal, QPalette::ButtonText).name() << ";\n" <<
  "}\n"
  
  "GtkButton:prelight {\n"
  "background-color:#000000;"
  "}\n"

  "GtkTooltip {\n"
  "background-color:" << qApp->palette().color(QPalette::Normal, QPalette::ToolTipBase).name() << ";\n" <<
  "color:" << qApp->palette().color(QPalette::Normal, QPalette::ToolTipText).name() << ";\n" <<
  "}\n";

  // qDebug("%d, %s", str.length(), str.constData());
  stream.flush();

  GtkCssProvider* provider = gtk_css_provider_new();
  GError* err = NULL;
  gtk_css_provider_load_from_data(provider, str.constData(), str.length(), &err);
  if(err) {
    qDebug("Css Error: %s", err->message);
    g_error_free(err);
  }
  return provider;
}
