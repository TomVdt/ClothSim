#pragma once

#include <Qt>
#include <QKeyEvent>
#include <QMouseEvent>
#include <vector>


class InputManager {
private:
    std::vector<Qt::Key> pressed;

    void addKey(int key);
    void removeKey(int key);

public:
    InputManager() {}

    void handleKeyPress(QKeyEvent* event);
    void handleKeyRelease(QKeyEvent* event);

    bool isKeyPressed(Qt::Key key) const;
};
