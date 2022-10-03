#pragma once

#include <QObject>
#include <QKeyEvent>
#include <mini3d.h>

namespace mini3d {
    class App;
    class AppEvents;
}

class InputMapping: public QObject
{
    Q_OBJECT
public:
    InputMapping();

    void reload(const mini3d::App &app);
    void dispatchKeyEvent(const QKeyEvent *event, mini3d::AppEvents &events) const;
    void dispatchMouseButtonEvent(const QMouseEvent *event, mini3d::AppEvents &events) const;
    void dispatchMousePositionEvent(float pos_x, float pos_y, mini3d::AppEvents &events) const;
    void dispatchMouseMotionEvent(float motion_x, float motion_y, mini3d::AppEvents &events) const;

private:
    struct KeyToAction {
        uint64_t action;
        Qt::Key key;
    };
    struct KeyToAxis {
        uint64_t axis;
        Qt::Key key;
        float value;
    };
    struct MouseButtonToAction {
        uint64_t action;
        Qt::MouseButton button;
    };
    struct MouseButtonToAxis {
        uint64_t axis;
        Qt::MouseButton button;
        float value;
    };
    struct MousePositionXToAxis {
        uint64_t axis;
    };
    struct MousePositionYToAxis {
        uint64_t axis;
    };
    struct MouseMotionXToAxis {
        uint64_t axis;
    };
    struct MouseMotionYToAxis {
        uint64_t axis;
    };

    enum class ActionMappingType { None, Key, MouseButton };
    struct ActionInput {
        uint64_t id;
        uint64_t group;
        std::string name;
        ActionMappingType type;
        union {
            KeyToAction key;
            MouseButtonToAction mouseButton;
            Qt::KeyboardModifier modifier;
        } map;
    };

    enum class AxisMappingType {
        None,
        Key,
        MouseButton,
        MousePositionX,
        MousePositionY,
        MouseMotionX,
        MouseMotionY
    };
    struct AxisInput {
        uint64_t id;
        uint64_t group;
        std::string name;
        AxisMappingType type;
        union {
            KeyToAxis key;
            MouseButtonToAxis mouseButton;
            MousePositionXToAxis mousePositionX;
            MousePositionYToAxis mousePositionY;
            MouseMotionXToAxis mouseMotionX;
            MouseMotionYToAxis mouseMotionY;
        } map;
    };

    struct GroupInput {
        uint64_t id;
        std::string name;
        std::vector<ActionInput> actions;
        std::vector<AxisInput> axis;
    };

    std::vector<GroupInput> m_groups;
    std::vector<ActionInput> m_actions;
    std::vector<AxisInput> m_axis;

    std::unordered_map<Qt::Key, std::vector<KeyToAction>> m_keyToAction;
    std::unordered_map<Qt::Key, std::vector<KeyToAxis>> m_keyToAxis;
    std::unordered_map<Qt::MouseButton, std::vector<MouseButtonToAction>> m_mouseButtonToAction;
    std::unordered_map<Qt::MouseButton, std::vector<MouseButtonToAxis>> m_mouseButtonToAxis;
    std::vector<MousePositionXToAxis> m_mousePositionXToAxis;
    std::vector<MousePositionYToAxis> m_mousePositionYToAxis;
    std::vector<MouseMotionXToAxis> m_mouseMotionXToAxis;
    std::vector<MouseMotionYToAxis> m_mouseMotionYToAxis;
};
