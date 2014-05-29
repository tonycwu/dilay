#ifndef DILAY_TOOL
#define DILAY_TOOL

#include "macro.hpp"

class QMouseEvent;
class QContextMenuEvent;
class ViewMainWindow;
class ViewToolOptions;
class QString;
class QWheelEvent;

class Tool {
  public:
    DECLARE_BIG3_VIRTUAL (Tool, ViewMainWindow&, QContextMenuEvent&, const QString&)

    friend class ToolUtil;

    ViewMainWindow&    mainWindow        ();
    QContextMenuEvent& menuEvent         ();
    void               updateGlWidget    ();

    void               render            ();
    void               mouseMoveEvent    (QMouseEvent&);
    void               mousePressEvent   (QMouseEvent&);
    void               mouseReleaseEvent (QMouseEvent&);
    void               wheelEvent        (QWheelEvent&);

    bool               isDraged          () const;
    bool               isHovered         () const;

  protected:
    ViewToolOptions&   toolOptions       ();

    void               drag              (bool);
    void               dragIfHovered     ();
    void               hover             (bool);
    void               hoverIfDraged     ();

  private:
    class Impl;
    Impl* impl;

    virtual void runRender            ()             {}
    virtual bool runMouseMoveEvent    (QMouseEvent&) { return false; }
    virtual bool runMousePressEvent   (QMouseEvent&) { return false; }
    virtual bool runMouseReleaseEvent (QMouseEvent&) { return false; }
    virtual bool runWheelEvent        (QWheelEvent&) { return false; }
};

#endif