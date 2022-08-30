#include "WGPURenderer.h"

#include <qt_windows.h>

using namespace mini3d;

WGPURenderer::WGPURenderer(void *hwnd)
{
    m_handle = mini3d_renderer_new_wgpu_win32((void*)GetModuleHandle(nullptr), hwnd);
}
WGPURenderer::~WGPURenderer()
{
    mini3d_renderer_delete(m_handle);
}

mini3d_renderer *WGPURenderer::handle()
{
    return m_handle;
}
void WGPURenderer::resize(uint32_t width, uint32_t height)
{
    mini3d_renderer_resize(m_handle, width, height);
}
void WGPURenderer::present()
{
    if (!mini3d_renderer_present(m_handle)) {
        mini3d_renderer_recreate(m_handle);
    }
}
