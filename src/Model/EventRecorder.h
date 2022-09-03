#pragma once

#include <QObject>
#include <mini3d.h>

namespace mini3d
{
    class EventRecorder : public QObject
    {
        Q_OBJECT
    public:
        EventRecorder();
        ~EventRecorder();

        struct mini3d_event_recorder *handle() const;
        void reset();
        void pushInputButton(const char *name, mini3d_button_state state);
        void pushInputCursorPosition(float x, float y, uint32_t width, uint32_t height);

    private:
        mini3d_event_recorder *m_handle = nullptr;
    };
}
