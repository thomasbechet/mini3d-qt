#pragma once

#include <QObject>
#include <mini3d.h>

#include "EventRecorder.h"

namespace mini3d
{
    class Application : public QObject
    {
        Q_OBJECT
    public:
        Application();
        ~Application();

        struct mini3d_application *handle() const;
        void progress(const EventRecorder &eventRecorder);

    private:
        mini3d_application *m_handle = nullptr;
    };
}
