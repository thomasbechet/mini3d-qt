#include "App.h"

using namespace mini3d;

App::App() : m_handle(mini3d_app_new()) {}
App::~App()
{
    mini3d_app_delete(m_handle);
}

void App::progress()
{
    mini3d_app_progress(m_handle);
}
void App::render(WGPURenderer &renderer)
{
    mini3d_app_render(m_handle, renderer.handle());
}
void App::pushInputButton(const char *name, mini3d_button_state state)
{
    mini3d_app_push_input_button(m_handle, name, state);
}
void App::pushInputCursorPosition(float x, float y, uint32_t width, uint32_t height)
{
    mini3d_app_push_input_cursor_position(m_handle, x, y, width, height);
}
