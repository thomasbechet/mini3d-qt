#include "EventRecorder.h"

using namespace mini3d;

EventRecorder::EventRecorder() : m_handle(mini3d_event_recorder_new()) {}
EventRecorder::~EventRecorder()
{
    mini3d_event_recorder_delete(m_handle);
}

struct mini3d_event_recorder *EventRecorder::handle() const
{
    return m_handle;
}
void EventRecorder::reset()
{
    mini3d_event_recorder_reset(m_handle);
}
void EventRecorder::pushInputButton(const char *name, mini3d_button_state state)
{
    mini3d_record_input_button(m_handle, name, state);
}
void EventRecorder::pushInputCursorPosition(float x, float y, uint32_t width, uint32_t height)
{
    mini3d_record_input_cursor_position(m_handle, x, y, width, height);
}
