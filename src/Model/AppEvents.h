#pragma once

#include <QObject>
#include <mini3d.h>

namespace mini3d
{
    class AppEvents : public QObject
    {
        Q_OBJECT
    public:
        AppEvents();
        ~AppEvents();

        mini3d_app_events *handle() const;
        void pushInputAction(uint64_t id, mini3d_action_state state);
        void pushInputAxis(uint64_t id, float value);

    private:
        mini3d_app_events *m_handle = nullptr;
    };
}
