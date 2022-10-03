#pragma once

#include <QObject>
#include <mini3d.h>

namespace mini3d
{
    class AppEvents;
    class AppRequests;
    class WGPURenderer;

    class App : public QObject
    {
        Q_OBJECT
    public:
        App();
        ~App();

        mini3d_app *handle() const;
        void progress(const AppEvents &events, AppRequests &requests, WGPURenderer &renderer, float deltaTime);

    private:
        mini3d_app *m_handle = nullptr;
    };
}
