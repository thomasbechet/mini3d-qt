#pragma once

#include <QObject>
#include <mini3d.h>

namespace mini3d
{
    class AppRequests : public QObject
    {
        Q_OBJECT
    public:
        AppRequests();
        ~AppRequests();

        mini3d_app_requests *handle() const;
        bool shutdown() const;
        bool reloadInputMapping() const;
        void reset();

    private:
        mini3d_app_requests *m_handle = nullptr;
    };
}
