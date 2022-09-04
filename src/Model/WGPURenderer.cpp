#include "WGPURenderer.h"

#include <QtGlobal>
#include <QtWidgets>

#if defined(Q_OS_WIN)
#include <qt_windows.h>
#endif

using namespace mini3d;

WGPURenderer::WGPURenderer(WId wid)
{
#ifdef Q_OS_WIN
    m_handle = mini3d_renderer_new_wgpu_win32((void*)GetModuleHandle(nullptr), (void*)wid);
#elif defined(Q_OS_LINUX)
    auto *app = static_cast<QApplication*>(QApplication::instance());
    auto *interface = app->nativeInterface<QNativeInterface::QX11Application>();
    m_handle = mini3d_renderer_new_wgpu_xlib((uint64_t)wid, interface->display());
#endif
}
WGPURenderer::~WGPURenderer()
{
    mini3d_renderer_delete(m_handle);
}

void WGPURenderer::render(const Application &app)
{
    if (!mini3d_renderer_render(m_handle, app.handle())) {
        mini3d_renderer_recreate(m_handle);
    }
}
void WGPURenderer::resize(uint32_t width, uint32_t height)
{
    mini3d_renderer_resize(m_handle, width, height);
}
