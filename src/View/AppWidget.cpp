#include "AppWidget.h"

#include <QPlatformSurfaceEvent>
#include <QWindow>

AppWidget::AppWidget(QWidget* parent)
    : QFrame{parent}
{
    parent->installEventFilter(this);

    // Configure QFrame
    setAutoFillBackground(false);
    setUpdatesEnabled(false);
    setMouseTracking(true);
    setCursor(Qt::BlankCursor);

    // Create app and renderer
    m_app = std::make_unique<mini3d::App>();
    m_renderer = std::make_unique<mini3d::WGPURenderer>((void*)winId());
}

void AppWidget::progressAppAndRender()
{
    m_app->progress();
    m_app->render(*m_renderer);
    m_renderer->present();
}

void AppWidget::resizeEvent(QResizeEvent *event)
{
    if (m_renderer) {
        m_renderer->resize(event->size().width(), event->size().height());
    }
}
bool AppWidget::eventFilter(QObject *obj, QEvent *e)
{
    if (e->type() == QEvent::KeyPress || e->type() == QEvent::KeyRelease) {
        auto *keyEvent = static_cast<QKeyEvent*>(e);
        auto state = (e->type() == QEvent::KeyPress) ? MINI3D_BUTTON_STATE_PRESSED : MINI3D_BUTTON_STATE_RELEASED;
        switch (keyEvent->key()) {
        case Qt::Key::Key_Z:
            m_app->pushInputButton("up", state);
            break;
        case Qt::Key::Key_S:
            m_app->pushInputButton("down", state);
            break;
        case Qt::Key::Key_D:
            m_app->pushInputButton("right", state);
            break;
        case Qt::Key::Key_Q:
            m_app->pushInputButton("left", state);
            break;
        case Qt::Key::Key_M:
            m_app->pushInputButton("switch_selection_mode", state);
        default:
            break;
        }
    } else if (e->type() == QEvent::MouseMove) {
        auto *mouseEvent = static_cast<QMouseEvent*>(e);
        m_app->pushInputCursorPosition(mouseEvent->pos().x(), mouseEvent->pos().y(), width(), height());
    }
    return false;
}
