#include "AppRequests.h"

using namespace mini3d;

AppRequests::AppRequests() : m_handle(mini3d_app_requests_new()) {}
AppRequests::~AppRequests()
{
    mini3d_app_requests_delete(m_handle);
}

mini3d_app_requests *AppRequests::handle() const
{
    return m_handle;
}
bool AppRequests::shutdown() const
{
    return mini3d_app_requests_shutdown(m_handle);
}
bool AppRequests::reloadInputMapping() const
{
    return mini3d_app_requests_reload_input_mapping(m_handle);
}
void AppRequests::reset()
{
    mini3d_app_requests_reset(m_handle);
}

