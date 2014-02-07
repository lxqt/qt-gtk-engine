#include <gtk/gtk.h>
// #include "themeengine.h"
#include <QDebug>
#include <QApplication>
#include <QStyle>
#include <QStyleOption>
#include "themepainter.h"
#include "cssprovider.h"

typedef struct _QtEngine QtEngine;
typedef struct _QtEngineClass QtEngineClass;

struct _QtEngine {
  GtkThemingEngine parent_object;
  // ThemeEngine* theme_engine;
};

struct _QtEngineClass {
  GtkThemingEngineClass parent_class;
};

#define QT_TYPE_ENGINE     (qt_engine_get_type ())
#define QT_ENGINE(object)    (G_TYPE_CHECK_INSTANCE_CAST ((object), QT_TYPE_ENGINE, QtEngine))
#define QT_ENGINE_CLASS(klass)   (G_TYPE_CHECK_CLASS_CAST ((klass), QT_TYPE_ENGINE, QtEngineClass))
#define QT_IS_ENGINE(object)   (G_TYPE_CHECK_INSTANCE_TYPE ((object), QT_TYPE_ENGINE))
#define QT_IS_ENGINE_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), QT_TYPE_ENGINE))
#define QT_ENGINE_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), QT_TYPE_ENGINE, QtEngineClass))

GType qt_engine_get_type(void) G_GNUC_CONST;

G_DEFINE_DYNAMIC_TYPE(QtEngine, qt_engine, GTK_TYPE_THEMING_ENGINE)

static void qt_engine_init(QtEngine* engine) {
  // engine->theme_engine = new ThemeEngine();
}

static void qt_engine_finalize(GObject* obj) {
  // delete QT_ENGINE(obj)->theme_engine;
  G_OBJECT_CLASS(qt_engine_parent_class)->finalize(obj);
}

static void initStyleOptionState(QStyleOption& opt, GtkStateFlags state) {
    if(state & GTK_STATE_FLAG_INSENSITIVE)
      opt.state = QStyle::State_None;
    else
      opt.state = QStyle::State_Enabled;
    if(state & GTK_STATE_FLAG_ACTIVE)
      opt.state |= QStyle::State_Active;
    if(state & GTK_STATE_FLAG_PRELIGHT)
      opt.state |= QStyle::State_MouseOver;
    if(state & GTK_STATE_FLAG_SELECTED)
      opt.state |=  QStyle::State_Selected;
    if(state & GTK_STATE_FLAG_FOCUSED)
      opt.state |= QStyle::State_HasFocus;
}

static void render_background(GtkThemingEngine* engine,
                              cairo_t*          cr,
                              gdouble           x,
                              gdouble           y,
                              gdouble           width,
                              gdouble           height) {
  QStyle* style = qApp->style();
  GtkStateFlags state = gtk_theming_engine_get_state(engine);
  const GtkWidgetPath* widgetPath = gtk_theming_engine_get_path(engine);
  if((state & GTK_STATE_FLAG_SELECTED) &&
      gtk_theming_engine_has_class(engine, "cell")) {
    // TODO: draw selected cell
  }
  else if(gtk_theming_engine_has_class(engine, "tooltip")) {
    // TODO: draw tooltip
  }
  else if(gtk_theming_engine_has_class(engine, "cell") &&
          gtk_theming_engine_has_class(engine, "icon-view")) {
    // TODO: draw icon view item
  }
  else if((state & GTK_STATE_FLAG_PRELIGHT) &&
          // (style == CLEARLOOKS_STYLE_GLOSSY || style == CLEARLOOKS_STYLE_GUMMY) &&
          (gtk_theming_engine_has_class(engine, "check") || gtk_theming_engine_has_class(engine, "radio"))) {
    /* XXX: Don't draw any check/radiobutton bg in GLOSSY or GUMMY mode. */
  }
  else if(gtk_widget_path_is_type(widgetPath, GTK_TYPE_LABEL) || gtk_widget_path_is_type(widgetPath, GTK_TYPE_IMAGE)) {
    // transparent background!
  }
  else if(gtk_theming_engine_has_class(engine, GTK_STYLE_CLASS_SCROLLBAR)) {
    qDebug() << "scrollbar:" << x << y << width << height;
    
  }
  else {
    GTK_THEMING_ENGINE_CLASS(qt_engine_parent_class)->render_background(engine, cr, x, y, width, height);
    //QColor clr = qApp->palette().color(QPalette::Normal, QPalette::Window);
    //cairo_set_source_rgb(cr, clr.redF(), clr.greenF(), clr.blueF());
    //cairo_rectangle(cr, 0, 0, width, height);
    //cairo_fill(cr);
  }
//  QT_ENGINE(engine)->theme_engine->render_background(engine, cr, x, y, width, height);
}

static void render_frame(GtkThemingEngine* engine,
                         cairo_t*          cr,
                         gdouble           x,
                         gdouble           y,
                         gdouble           width,
                         gdouble           height) {
  
  GtkStateFlags state = gtk_theming_engine_get_state(engine);
  const GtkWidgetPath* path = gtk_theming_engine_get_path(engine);
  GtkTextDirection direction = gtk_theming_engine_get_direction(engine);
  QStyle* style = qApp->style();

  if(gtk_theming_engine_has_class(engine, GTK_STYLE_CLASS_ENTRY) &&
      !gtk_widget_path_has_parent(path, GTK_TYPE_TREE_VIEW)) {
    QStyleOptionFrame opt;
    ThemePainter p(cr, x, y, width, height, opt);
    initStyleOptionState(opt, state);
    opt.lineWidth = style->pixelMetric(QStyle::PM_DefaultFrameWidth, &opt);
    opt.midLineWidth = 0;
    style->drawPrimitive(QStyle::PE_PanelLineEdit, &opt, p.painter());
  }
  else if(gtk_theming_engine_has_class(engine, GTK_STYLE_CLASS_BUTTON) &&
          gtk_theming_engine_has_class(engine, GTK_STYLE_REGION_COLUMN_HEADER)) {
    QStyleOptionHeader opt;
    ThemePainter p(cr, x, y, width, height, opt);
    initStyleOptionState(opt, state);
    style->drawControl(QStyle::CE_HeaderSection, &opt, p.painter());
  }
  else if(gtk_theming_engine_has_class(engine, GTK_STYLE_CLASS_BUTTON)) {
    QStyleOptionButton opt;
    ThemePainter p(cr, x, y, width, height, opt);
    initStyleOptionState(opt, state);
    if(state & GTK_STATE_FLAG_ACTIVE)
      opt.state |= QStyle::State_Sunken;
    style->drawControl(QStyle::CE_PushButton, &opt, p.painter());
  }
  else if(gtk_theming_engine_has_class(engine, "spinbutton") &&
          gtk_theming_engine_has_class(engine, "button")) {
    if(state & GTK_STATE_FLAG_ACTIVE) {
      // style_functions->draw_spinbutton_down(cr, engine, x, y, width, height);
    }
  }
  else if(gtk_theming_engine_has_class(engine, "spinbutton")) {
    // style_functions->draw_spinbutton(cr, engine, x, y, width, height);
  }
  else if(gtk_widget_path_is_type(path, GTK_TYPE_SCALE) &&
          gtk_theming_engine_has_class(engine, GTK_STYLE_CLASS_TROUGH)) {
    // slider.lower = FALSE;
    // slider.fill_level = gtk_theming_engine_has_class(engine, "scale");
    // slider.horizontal = width >= height;
    // style_functions->draw_scale_trough(cr, engine, &slider, x, y, width, height);
  }
  else if(gtk_widget_path_is_type(path, GTK_TYPE_PROGRESS_BAR) &&
          gtk_theming_engine_has_class(engine, GTK_STYLE_CLASS_TROUGH)) {
    // style_functions->draw_progressbar_trough(cr, engine, x, y, width, height);
  }
  else if(gtk_widget_path_is_type(path, GTK_TYPE_SCROLLBAR) &&
          gtk_theming_engine_has_class(engine, GTK_STYLE_CLASS_TROUGH)) {
    /*
    ScrollBarParameters scrollbar;
    scrollbar.horizontal = TRUE;
    scrollbar.junction   = 0; //qt_scrollbar_get_junction (widget);
      scrollbar.horizontal = width >= height;

    style_functions->draw_scrollbar_trough(cr, engine, &scrollbar,
                                           x, y, width, height);
    */
  }
  else if(gtk_theming_engine_has_class(engine, "progressbar")) {
/*    style_functions->draw_progressbar_fill(cr, engine, &progressbar,
                                           x, y, width, height,
                                           10 - (int)(elapsed * 10.0) % 10);
*/
  }
  else if(gtk_theming_engine_has_class(engine, GTK_STYLE_CLASS_ENTRY) &&
          gtk_theming_engine_has_class(engine, GTK_STYLE_CLASS_PROGRESSBAR)) {
    /*
    style_functions->draw_entry_progress(cr, engine, &progress,
                                         x, y, width, height);
    */
  }
  else if(gtk_theming_engine_has_class(engine, GTK_STYLE_CLASS_MENUITEM)) {
    QStyleOptionMenuItem opt;
    ThemePainter p(cr, x, y, width, height, opt);
    initStyleOptionState(opt, state);
    if(state & GTK_STATE_FLAG_PRELIGHT)
      opt.state |=  QStyle::State_Selected;
    if(gtk_widget_path_has_parent(path, GTK_TYPE_MENU_BAR) && !gtk_widget_path_has_parent(path, GTK_TYPE_MENU)) {
      // menu bar item
      if(opt.state &  QStyle::State_Selected) // selected items are painted like normal menuitem
        style->drawControl(QStyle::CE_MenuItem, &opt, p.painter());
      else
        style->drawControl(QStyle::CE_MenuBarItem, &opt, p.painter());
    }
    else {
      // ordinary menu items
      style->drawControl(QStyle::CE_MenuItem, &opt, p.painter());
    }
  }
  else if(gtk_theming_engine_has_class(engine, GTK_STYLE_CLASS_MENUBAR)) {
    bool horizontal = height < 2 * width;
    QStyleOptionMenuItem opt;
    ThemePainter p(cr, x, y, width, height, opt);
    initStyleOptionState(opt, state);
    style->drawControl(QStyle::CE_MenuBarEmptyArea, &opt, p.painter());
  }
  else if(gtk_theming_engine_has_class(engine, GTK_STYLE_CLASS_SCROLLBAR)) {
    qDebug() << "scrollbar:" << x << y << width << height;
    // stepper.stepper = CL_STEPPER_UNKNOWN;
    // style_functions->draw_scrollbar_stepper(cr, engine, &scrollbar, &stepper, x, y, width, height);
  }
  else if(gtk_theming_engine_has_class(engine, GTK_STYLE_CLASS_TOOLBAR) ||
          gtk_theming_engine_has_class(engine, GTK_STYLE_CLASS_DOCK)) {
#if 0
    bool horizontal = height < 2 * width;
#endif
  }
  else if(gtk_theming_engine_has_class(engine, GTK_STYLE_CLASS_MENU)) {
    // why this does not work?
    QStyleOptionMenuItem opt;
    ThemePainter p(cr, x, y, width, height, opt);
    opt.state = QStyle::State_None;
    opt.checkType = QStyleOptionMenuItem::NotCheckable;
    opt.maxIconWidth = 0;
    opt.tabWidth = 0;
    style->drawPrimitive(QStyle::PE_PanelMenu, &opt, p.painter());
  }
  else {
    GTK_THEMING_ENGINE_CLASS(qt_engine_parent_class)->render_frame(engine, cr, x, y, width, height);
  }

//  QT_ENGINE(engine)->theme_engine->render_frame(engine, cr, x, y, width, height);
}

static void render_frame_gap(GtkThemingEngine* engine,
                             cairo_t*          cr,
                             gdouble           x,
                             gdouble           y,
                             gdouble           width,
                             gdouble           height,
                             GtkPositionType   gap_side,
                             gdouble           xy0_gap,
                             gdouble           xy1_gap) {
  cairo_save(cr);
  if(gtk_theming_engine_has_class(engine, "notebook")) {
#if 0
    CairoColor* bg_color;

    frame.gap_side  = gap_side;
    frame.gap_x     = xy0_gap;
    frame.gap_width = xy1_gap - xy0_gap;
    qt_lookup_shade(engine, 5, (GdkRGBA*) &frame.border);

    state = gtk_theming_engine_get_state(engine);

    gtk_theming_engine_get(engine, state,
                           "background-color", &bg_color,
                           "border-radius", &radius,
                           NULL);

    /* Fill the background with bg[NORMAL] */
    ge_cairo_rounded_rectangle(cr, x, y, width, height, radius,
                               qt_get_corners(engine));
    ge_cairo_set_color(cr, bg_color);
    cairo_fill(cr);

    style_functions->draw_frame(cr, engine, &frame,
                                x, y, width, height);

    gdk_rgba_free((GdkRGBA*) bg_color);
#endif
  }
  else if(gtk_theming_engine_has_class(engine, "frame")) {
    // style_functions->draw_frame(cr, engine, &frame, x, y, width, height);
  }
  else {
    GTK_THEMING_ENGINE_CLASS(qt_engine_parent_class)->render_frame_gap(engine, cr, x, y, width, height, gap_side, xy0_gap, xy1_gap);
  }
  cairo_restore(cr);
//  QT_ENGINE(engine)->theme_engine->render_frame_gap(engine, cr, x, y, width, height, gap_side, xy0_gap, xy1_gap);
}

static void render_extension(GtkThemingEngine* engine,
                             cairo_t*          cr,
                             gdouble           x,
                             gdouble           y,
                             gdouble           width,
                             gdouble           height,
                             GtkPositionType   gap_side) {
  QStyle* style = qApp->style();
  GtkStateFlags state = gtk_theming_engine_get_state(engine);
  if(gtk_theming_engine_has_region(engine, GTK_STYLE_REGION_TAB, NULL)) {
    QStyleOptionTab opt;
    ThemePainter p(cr, x, y, width, height, opt);
    opt.state = QStyle::State_Enabled;
    style->drawControl(QStyle::CE_TabBarTab, &opt, p.painter());
#if 0
    GtkStateFlags    state = gtk_theming_engine_get_state(engine);
    /* Focus color */
    if(focus_color) {
      focus.color = *focus_color;
      focus.has_color = TRUE;
      gdk_rgba_free((GdkRGBA*) focus_color);
    }
    else
      focus.color = *bg_color;
    tab.focus = focus;
    style_functions->draw_tab(cr, engine, &tab, x, y, width, height);
#endif
  }
  else {
    GTK_THEMING_ENGINE_CLASS(qt_engine_parent_class)->render_extension(engine, cr, x, y, width, height, gap_side);
  }

//  QT_ENGINE(engine)->theme_engine->render_extension(engine, cr, x, y, width, height, gap_side);
}

static void render_check(GtkThemingEngine* engine,
                         cairo_t*          cr,
                         gdouble           x,
                         gdouble           y,
                         gdouble           width,
                         gdouble           height) {
  // FIXME: why this does not work?
  QStyle* style = qApp->style();
  GtkStateFlags state = gtk_theming_engine_get_state(engine);
  bool in_cell = gtk_theming_engine_has_class(engine, GTK_STYLE_CLASS_CELL);
  bool in_menu = gtk_theming_engine_has_class(engine, GTK_STYLE_CLASS_MENU);
  QStyleOptionMenuItem opt;
  ThemePainter p(cr, x, y, width, height, opt);
  initStyleOptionState(opt, state);
  if(state & GTK_STATE_FLAG_ACTIVE)
    opt.state |= QStyle::State_On;
  else
    opt.state |= QStyle::State_Off;
  style->drawPrimitive(QStyle::PE_IndicatorCheckBox, &opt, p.painter());
  // style_functions->draw_checkbox(cr, engine, &checkbox, x, y, width, height);
}

static void render_option(GtkThemingEngine* engine,
                          cairo_t*          cr,
                          gdouble           x,
                          gdouble           y,
                          gdouble           width,
                          gdouble           height) {
  // checkbox.in_menu = gtk_theming_engine_has_class(engine, GTK_STYLE_CLASS_MENU);
  // style_functions->draw_radiobutton(cr, engine, &checkbox, x, y, width, height);
//  QT_ENGINE(engine)->theme_engine->render_option(engine, cr, x, y, width, height);
}

static void render_arrow(GtkThemingEngine* engine,
                         cairo_t*          cr,
                         gdouble           angle,
                         gdouble           x,
                         gdouble           y,
                         gdouble           size) {
  if(gtk_theming_engine_has_class(engine, "combo") &&
      !gtk_theming_engine_has_class(engine, GTK_STYLE_CLASS_ENTRY)) {
  }
  else {
  }
  // style_functions->draw_arrow(cr, engine, &arrow, x, y, size, size);
//  QT_ENGINE(engine)->theme_engine->render_arrow(engine, cr, angle, x, y, size);
}

static void render_expander(GtkThemingEngine* engine,
                            cairo_t*          cr,
                            gdouble           x,
                            gdouble           y,
                            gdouble           width,
                            gdouble           height) {
  GTK_THEMING_ENGINE_CLASS(qt_engine_parent_class)->render_expander(engine, cr, x, y, width, height);
}

static void render_focus(GtkThemingEngine* engine,
                         cairo_t*          cr,
                         gdouble           x,
                         gdouble           y,
                         gdouble           width,
                         gdouble           height) {
  GTK_THEMING_ENGINE_CLASS(qt_engine_parent_class)->render_focus(engine, cr, x, y, width, height);
}

static void render_slider(GtkThemingEngine* engine,
                          cairo_t*          cr,
                          gdouble           x,
                          gdouble           y,
                          gdouble           width,
                          gdouble           height,
                          GtkOrientation    orientation) {
  QStyle* style = qApp->style();
  GtkStateFlags state = gtk_theming_engine_get_state(engine);
  if(gtk_theming_engine_has_class(engine, GTK_STYLE_CLASS_SLIDER)) {
    qDebug() << "slider: " << QRect(x, y, width, height);
    // QStyleOptionSlider opt;
    QStyleOptionSlider opt;
    initStyleOptionState(opt, state);
    opt.orientation = width > height ? Qt::Horizontal : Qt::Vertical;
    if(opt.orientation == Qt::Vertical) {
      height += width * 2;
      y -= width;
    }
    opt.subControls = QStyle::SC_ScrollBarSlider;
    ThemePainter p(cr, x, y, width, height, opt);
    qDebug() << "adjusted:" << opt.rect;
    QRect subRect = style->subControlRect(QStyle::CC_ScrollBar, &opt, QStyle::SC_ScrollBarSlider, NULL);
    qDebug() << "subControlRect: " << subRect;
    style->drawComplexControl(QStyle::CC_ScrollBar, &opt, p.painter());
  }
  else {
    // style_functions->draw_slider_button(cr, engine, &slider, x, y, width, height);
  }
  GTK_THEMING_ENGINE_CLASS(qt_engine_parent_class)->render_slider(engine, cr, x, y, width, height, orientation);
}

static void render_handle(GtkThemingEngine* engine,
                          cairo_t*          cr,
                          gdouble           x,
                          gdouble           y,
                          gdouble           width,
                          gdouble           height) {
  if(gtk_theming_engine_has_class(engine, "dock")) {
    // style_functions->draw_handle(cr, engine, &handle, x, y, width, height);
  }
  else if(gtk_theming_engine_has_class(engine, "paned")) {
  }
  else if(gtk_theming_engine_has_class(engine, "grip")) {
  }
  else {
  }
  GTK_THEMING_ENGINE_CLASS(qt_engine_parent_class)->render_handle(engine, cr, x, y, width, height);
}

static void render_activity(GtkThemingEngine* engine,
                            cairo_t*          cr,
                            gdouble           x,
                            gdouble           y,
                            gdouble           width,
                            gdouble           height) {
//  QT_ENGINE(engine)->theme_engine->render_activity(engine, cr, x, y, width, height);
}

static void qt_engine_class_init(QtEngineClass* klass) {
  GObjectClass* object_class = G_OBJECT_CLASS(klass);
  object_class->finalize = qt_engine_finalize;

  GtkThemingEngineClass* engine_class = GTK_THEMING_ENGINE_CLASS(klass);
  engine_class->render_background = render_background;
  engine_class->render_frame = render_frame;
  engine_class->render_frame_gap = render_frame_gap;
  engine_class->render_extension = render_extension;
  engine_class->render_check = render_check;
  engine_class->render_option = render_option;
  engine_class->render_arrow = render_arrow;
  engine_class->render_expander = render_expander;
  engine_class->render_focus = render_focus;
  engine_class->render_slider = render_slider;
  engine_class->render_handle = render_handle;
  engine_class->render_activity = render_activity;
}

static void qt_engine_class_finalize(QtEngineClass* klass) {
}

static QApplication* app = NULL;
static GtkCssProvider* css_provider = NULL;

extern "C" {

  G_MODULE_EXPORT void theme_init(GTypeModule* module) {
    if(!qApp) {
      app = new QApplication(0, NULL);
    }
    css_provider = qt_css_provider_new();
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_THEME);
    qt_engine_register_type(module);
  }

  G_MODULE_EXPORT void theme_exit(void) {
    if(app)
      delete app;
    if(css_provider) {
      gtk_style_context_remove_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(css_provider));
      g_object_unref(css_provider);
      css_provider = NULL;
    }
  }

  G_MODULE_EXPORT GtkThemingEngine* create_engine(void) {
    return GTK_THEMING_ENGINE(g_object_new(QT_TYPE_ENGINE, "name", "qt-gtk-engine", NULL));
  }

}
