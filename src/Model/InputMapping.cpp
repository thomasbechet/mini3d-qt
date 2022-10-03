#include "InputMapping.h"

#include "App.h"
#include "AppEvents.h"

InputMapping::InputMapping()
{

}

void InputMapping::reload(const mini3d::App &app)
{
    // Recover the app input database
    auto database = mini3d_input_database_read(app.handle());
    // Iterate over groups
    for (uint32_t i = 0; i < database.group_count; ++i) {
        const uint64_t id = database.groups[i];
        mini3d_input_group group;
        mini3d_input_database_get_group(app.handle(), id, &group);
        // Find existing group
        auto iterator = std::find_if(m_groups.begin(), m_groups.end(), [&] (const GroupInput &it) {
            return std::strcmp(it.name.c_str(), group.name) == 0;
        });
        // Create new group if missing
        if (iterator == m_groups.end()) {
            m_groups.emplace_back(GroupInput {
                .id=id,
                .name=std::string(group.name)
            });
        } else {
            // Update the group id
            iterator->id = id;
        }
    }

    // Iterate over actions
    mini3d_input_action action;
    for (uint32_t i = 0; i < database.action_count; i++) {
        const uint64_t id = database.actions[i];
        // Get the button
        mini3d_input_database_get_action(app.handle(), id, &action);
        // Find existing mapping
        auto iterator = std::find_if(m_actions.begin(), m_actions.end(), [&] (const ActionInput &it) {
            return std::strcmp(it.name.c_str(), action.name) == 0 && it.group == action.group;
        });
        // Insert new input if missing
        if (iterator == m_actions.end()) {
            m_actions.emplace_back(ActionInput {
               .id=id,
               .group=action.group,
               .name=std::string(action.name),
               .type=ActionMappingType::None
           });
        } else {
            // Update the action
            iterator->id = id;
        }
    }

    // Iterate over axis
    mini3d_input_axis axis;
    for (uint32_t i = 0; i < database.axis_count; i++) {
        const uint64_t id = database.axis[i];
        // Get axis
        mini3d_input_database_get_axis(app.handle(), id, &axis);
        // Find existing mapping
        auto iterator = std::find_if(m_axis.begin(), m_axis.end(), [&] (const AxisInput &it) {
            return std::strcmp(it.name.c_str(), axis.name) == 0 && it.group == axis.group;
        });
        // Insert new input if missing
        if (iterator == m_axis.end()) {
            m_axis.emplace_back(AxisInput {
                .id=id,
                .group=axis.group,
                .name=std::string(axis.name),
                .type=AxisMappingType::None
            });
        } else {
            // Update axis
            iterator->id = id;
        }
    }

    // Update key to axis mapping
    m_keyToAction.clear();
    for (auto& it : m_actions) {
        // REMOVE ME: hard code key mapping
        if (it.name == "up") {
            it.type = ActionMappingType::Key;
            it.map.key.key = Qt::Key_Z;
            it.map.key.action = it.id;
        } else if (it.name == "down") {
            it.type = ActionMappingType::Key;
            it.map.key.key = Qt::Key_S;
            it.map.key.action = it.id;
        } else if (it.name == "left") {
            it.type = ActionMappingType::Key;
            it.map.key.key = Qt::Key_Q;
            it.map.key.action = it.id;
        } else if (it.name == "right") {
            it.type = ActionMappingType::Key;
            it.map.key.key = Qt::Key_D;
            it.map.key.action = it.id;
        } else if (it.name == "toggle_layout") {
            it.type = ActionMappingType::Key;
            it.map.key.key = Qt::Key_F;
            it.map.key.action = it.id;
        }
        if (it.type == ActionMappingType::Key) {
            m_keyToAction[it.map.key.key].emplace_back(it.map.key);
        } else if (it.type == ActionMappingType::MouseButton) {
            m_mouseButtonToAction[it.map.mouseButton.button].emplace_back(it.map.mouseButton);
        }
    }

    // Update key to axis mapping
    m_keyToAxis.clear();
    for (auto &it : m_axis) {
        // REMOVE ME: hard code key mapping
        if (it.name == "move_forward") {
            it.type = AxisMappingType::Key;
            it.map.key.axis  = it.id;
            it.map.key.key   = Qt::Key_Z;
            it.map.key.value = 1.0;
        } else if (it.name == "move_backward") {
            it.type = AxisMappingType::Key;
            it.map.key.axis  = it.id;
            it.map.key.key   = Qt::Key_S;
            it.map.key.value = 1.0;
        } else if (it.name == "move_up") {
            it.type = AxisMappingType::Key;
            it.map.key.axis  = it.id;
            it.map.key.key   = Qt::Key_X;
            it.map.key.value = 1.0;
        } else if (it.name == "move_down") {
            it.type = AxisMappingType::Key;
            it.map.key.axis  = it.id;
            it.map.key.key   = Qt::Key_W;
            it.map.key.value = 1.0;
        } else if (it.name == "move_left") {
            it.type = AxisMappingType::Key;
            it.map.key.axis  = it.id;
            it.map.key.key   = Qt::Key_Q;
            it.map.key.value = 1.0;
        } else if (it.name == "move_right") {
            it.type = AxisMappingType::Key;
            it.map.key.axis  = it.id;
            it.map.key.key   = Qt::Key_D;
            it.map.key.value = 1.0;
        } else if (it.name == "cursor_x") {
            it.type = AxisMappingType::MousePositionX;
            it.map.mousePositionX.axis = it.id;
        } else if (it.name == "cursor_y") {
            it.type = AxisMappingType::MousePositionY;
            it.map.mousePositionY.axis = it.id;
        } else if (it.name == "motion_x") {
            it.type = AxisMappingType::MouseMotionX;
            it.map.mouseMotionX.axis = it.id;
        } else if (it.name == "motion_y") {
            it.type = AxisMappingType::MouseMotionY;
            it.map.mouseMotionY.axis = it.id;
        }
        if (it.type == AxisMappingType::Key) {
            m_keyToAxis[it.map.key.key].emplace_back(it.map.key);
        } else if (it.type == AxisMappingType::MouseButton) {
            m_mouseButtonToAxis[it.map.mouseButton.button].emplace_back(it.map.mouseButton);
        } else if (it.type == AxisMappingType::MousePositionX) {
            m_mousePositionXToAxis.emplace_back(it.map.mousePositionX);
        } else if (it.type == AxisMappingType::MousePositionY) {
            m_mousePositionYToAxis.emplace_back(it.map.mousePositionY);
        } else if (it.type == AxisMappingType::MouseMotionX) {
            m_mouseMotionXToAxis.emplace_back(it.map.mouseMotionX);
        } else if (it.type == AxisMappingType::MouseMotionY) {
            m_mouseMotionYToAxis.emplace_back(it.map.mouseMotionY);
        }
    }

    // Release resources
    mini3d_input_database_free(&database);
}
void InputMapping::dispatchKeyEvent(const QKeyEvent *event, mini3d::AppEvents &events) const
{
    auto key_to_action = m_keyToAction.find((Qt::Key)event->key());
    if (key_to_action != m_keyToAction.end()) {
        auto state = (event->type() == QEvent::KeyPress) ? MINI3D_ACTION_STATE_PRESSED : MINI3D_ACTION_STATE_RELEASED;
        for (auto &it : key_to_action->second) {
            events.pushInputAction(it.action, state);
        }
    }
    auto key_to_axis = m_keyToAxis.find((Qt::Key)event->key());
    if (key_to_axis != m_keyToAxis.end()) {
        for (auto &it : key_to_axis->second) {
            auto value = (event->type() == QEvent::KeyPress) ? it.value : 0.0f;
            events.pushInputAxis(it.axis, value);
        }
    }
}
void InputMapping::dispatchMouseButtonEvent(const QMouseEvent *event, mini3d::AppEvents &events) const
{
    if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonRelease) {
        auto mouse_button_to_action = m_mouseButtonToAction.find(event->button());
        if (mouse_button_to_action != m_mouseButtonToAction.end()) {
            auto state = (event->type() == QEvent::MouseButtonPress) ? MINI3D_ACTION_STATE_PRESSED : MINI3D_ACTION_STATE_RELEASED;
            for (auto &it : mouse_button_to_action->second) {
                events.pushInputAction(it.action, state);
            }
        }
        auto mouse_button_to_axis = m_mouseButtonToAxis.find(event->button());
        if (mouse_button_to_axis != m_mouseButtonToAxis.end()) {
            for (auto &it : mouse_button_to_axis->second) {
                auto value = (event->type() == QEvent::MouseButtonPress) ? it.value : 0.0f;
                events.pushInputAxis(it.axis, value);
            }
        }
    }
}
void InputMapping::dispatchMousePositionEvent(float pos_x, float pos_y, mini3d::AppEvents &events) const
{
    for (auto &it : m_mousePositionXToAxis) {
        events.pushInputAxis(it.axis, pos_x);
    }
    for (auto &it : m_mousePositionYToAxis) {
        events.pushInputAxis(it.axis, pos_y);
    }
}
void InputMapping::dispatchMouseMotionEvent(float motion_x, float motion_y, mini3d::AppEvents &events) const
{
    for (auto &it : m_mouseMotionXToAxis) {
        events.pushInputAxis(it.axis, motion_x * 0.01);
    }
    for (auto &it : m_mouseMotionYToAxis) {
        events.pushInputAxis(it.axis, motion_y * 0.01);
    }
}
