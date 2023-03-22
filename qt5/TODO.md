# TODO

## Classes

- Very simple `main.cpp`
- Qt compilation & other boilerplate
- Event handler class `GLWidget`
  - What is its role?
    - Handle keyboard events
    - Handle mouse events
    - Handle redraw events: call render
    - Handle resize events: do resize & notify renderer (projection change)
    - Manage clock
    - *later: handle physics updates*
  - Is the "orchestrator"
- `Renderer` class (`SupportADessins`)
  - Knows how to render any specific `Drawable`
  - UNLESS double-dispatch => `Drawable`s know
- `Drawable` abstract class (`Dessinable`, `Contenu`)
  - Has vertex, (colors, texture coords) array(s)
- `Camera` class: handle 3D movement

## Who owns / has / depends on who?

`main` calls
- `GLWidget` has
  - Clock
  - `Renderer` has
    - `Camera`
    - Shader program
  - list of `Drawable`s

---
*later: `Engine` for physics*
- *physics objects*
- *integrator*
---

DOCS:
- https://code.qt.io/cgit/qt/qtbase.git/tree/examples/opengl/hellogles3/glwindow.cpp?h=5.15
- https://doc.qt.io/qt-5/qtgui-openglwindow-example.html
- https://doc.qt.io/qt-5/qopenglwidget.html
* https://stackoverflow.com/questions/33639109/qt-5-5-with-qopenglwidget-invisible-triangle-in-core-profile
* https://github.com/gongjianbo/MyTestCode/blob/master/Qt/QtExampleCube/geometryengine.cpp
- https://learnopengl.com/Getting-started/Shaders
- https://code.qt.io/cgit/qt/qtbase.git/tree/examples/opengl/hellogles3/glwindow.cpp?h=5.15
- https://code.qt.io/cgit/qt/qtbase.git/tree/examples/gui/openglwindow/main.cpp?h=5.15