#include "AppEvents.h"

using namespace mini3d;

AppEvents::AppEvents() : m_handle(mini3d_app_events_new()) {}
AppEvents::~AppEvents()
{
    mini3d_app_events_delete(m_handle);
}

mini3d_app_events *AppEvents::handle() const
{
    return m_handle;
}
void AppEvents::pushInputAction(uint64_t id, mini3d_action_state state)
{
    mini3d_app_events_push_input_action(m_handle, id, state);
}
void AppEvents::pushInputAxis(uint64_t id, float value)
{
    mini3d_app_events_push_input_axis(m_handle, id, value);
}
