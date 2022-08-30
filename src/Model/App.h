#pragma once

#include <QObject>
#include <mini3d.h>

#include "WGPURenderer.h"

namespace mini3d
{
    class App : public QObject
    {
        Q_OBJECT
    public:
        App();
        ~App();

        void progress();
        void render(WGPURenderer &renderer);
        void pushInputButton(const char *name, mini3d_button_state state);
        void pushInputCursorPosition(float x, float y, uint32_t width, uint32_t height);

    private:
        mini3d_app *m_handle = nullptr;
    };
}
