#pragma once

#include <QWidget>
#include <mini3d.h>

namespace mini3d
{
    class WGPURenderer : public QObject
    {
        Q_OBJECT
    public:
        WGPURenderer(WId wid);
        ~WGPURenderer();

        mini3d_renderer *handle();
        void resize(uint32_t width, uint32_t height);
        void present();

    private:
        mini3d_renderer *m_handle;
    };
}
