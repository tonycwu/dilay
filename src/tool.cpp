#include "tool.hpp"
#include "view/tool-options.hpp"
#include "view/main-window.hpp"
#include "view/gl-widget.hpp"
#include "state.hpp"

struct Tool::Impl {
  Tool*            self;
  QString          toolName;
  ViewMainWindow*  mainWindow;
  ViewToolOptions* toolOptions;

  Impl (Tool* s) 
    : self        (s) 
    , mainWindow  (nullptr)
    , toolOptions (nullptr)
  {}

  void initialize (ViewMainWindow* w, QContextMenuEvent* e) {
    this->mainWindow = w;
    this->toolOptions = new ViewToolOptions (w);
    this->toolOptions->setWindowTitle   (this->toolName);

    QObject::connect ( this->toolOptions, &ViewToolOptions::accepted
                     , [this] () { this->close (); } );

    QObject::connect ( this->toolOptions, &ViewToolOptions::rejected
                     , [this] () { this->close (); } );

    this->self->runInitialize (e);
    this->toolOptions->show ();
  }

  void render () { 
    return this->self->runRender ( ); 
  }

  void mouseMoveEvent (QMouseEvent* e) { 
    this->self->runMouseMoveEvent (e); 
  }

  void mousePressEvent (QMouseEvent* e) {
    this->self->runMousePressEvent (e);
  }

  void close () {
    this->self->runClose     ();
    this->toolOptions->close ();
    State::setTool           (nullptr);
  }
};

DELEGATE_BIG3_SELF (Tool)
GETTER    (const QString&  , Tool, toolName)
SETTER    (const QString&  , Tool, toolName)
GETTER    (ViewMainWindow* , Tool, mainWindow)
GETTER    (ViewToolOptions*, Tool, toolOptions)
DELEGATE2 (void            , Tool, initialize, ViewMainWindow*, QContextMenuEvent*)
DELEGATE  (void            , Tool, render)
DELEGATE1 (void            , Tool, mouseMoveEvent, QMouseEvent*)
DELEGATE1 (void            , Tool, mousePressEvent, QMouseEvent*)
DELEGATE  (void            , Tool, close)
