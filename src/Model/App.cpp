#include "App.h"

#include "AppEvents.h"
#include "AppRequests.h"
#include "WGPURenderer.h"

using namespace mini3d;

App::App() : m_handle(mini3d_app_new()) {}
App::~App()
{
    mini3d_app_delete(m_handle);
}

mini3d_app *App::handle() const
{
    return m_handle;
}
void App::progress(const AppEvents &events, AppRequests &requests, WGPURenderer &renderer, float deltaTime)
{
    mini3d_app_progress(m_handle, events.handle(), requests.handle(), renderer.handle(), deltaTime);
}
