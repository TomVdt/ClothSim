#include "include/input.h"

#include <algorithm>

void InputManager::addKey(int key) {
    Qt::Key qkey((Qt::Key)key);
    if (std::find(pressed.begin(), pressed.end(), qkey) == pressed.end()) {
        pressed.push_back(qkey);
    }
}

void InputManager::removeKey(int key) {
    Qt::Key qkey((Qt::Key)key);
    for (size_t i(0); i < pressed.size(); ++i) {
        if (pressed[i] == qkey) {
            std::swap(pressed[i], pressed.back());
            pressed.pop_back();
            return;
        }
    }
}

void InputManager::handleKeyPress(QKeyEvent* event) {
    if (event->isAutoRepeat()) {
        event->ignore();
    } else {
        addKey(event->key());
    }
}

void InputManager::handleKeyRelease(QKeyEvent* event) {
    if (event->isAutoRepeat()) {
        event->ignore();
    } else {
        removeKey(event->key());
    }
}

bool InputManager::isKeyPressed(Qt::Key key) const {
    return std::find(pressed.begin(), pressed.end(), key) != pressed.end();
}
