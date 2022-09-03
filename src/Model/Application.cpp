#include "Application.h"

using namespace mini3d;

Application::Application() : m_handle(mini3d_application_new()) {}
Application::~Application()
{
    mini3d_application_delete(m_handle);
}

struct mini3d_application *Application::handle() const
{
    return m_handle;
}
void Application::progress(const EventRecorder &eventRecorder)
{
    mini3d_application_progress(m_handle, eventRecorder.handle());
}
