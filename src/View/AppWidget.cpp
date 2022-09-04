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
    m_app = std::make_unique<mini3d::Application>();
    m_eventRecorder = std::make_unique<mini3d::EventRecorder>();
    m_renderer = std::make_unique<mini3d::WGPURenderer>(winId());
}

void AppWidget::progressAppAndRender()
{
    if (m_app && m_renderer) {
        m_app->progress(*m_eventRecorder);
        m_eventRecorder->reset();
        m_renderer->render(*m_app);
    }
}

void AppWidget::resizeEvent(QResizeEvent *event)
{
    if (m_renderer) {
        m_renderer->resize(event->size().width(), event->size().height());
    }
}
void AppWidget::closeEvent(QCloseEvent *event)
{
    m_renderer.reset();
    m_app.reset();
}
bool AppWidget::eventFilter(QObject *obj, QEvent *e)
{
    if (e->type() == QEvent::KeyPress || e->type() == QEvent::KeyRelease) {
        auto *keyEvent = static_cast<QKeyEvent*>(e);
        auto state = (e->type() == QEvent::KeyPress) ? MINI3D_BUTTON_STATE_PRESSED : MINI3D_BUTTON_STATE_RELEASED;
        switch (keyEvent->key()) {
        case Qt::Key::Key_Z:
            m_eventRecorder->pushInputButton("up", state);
            break;
        case Qt::Key::Key_S:
            m_eventRecorder->pushInputButton("down", state);
            break;
        case Qt::Key::Key_D:
            m_eventRecorder->pushInputButton("right", state);
            break;
        case Qt::Key::Key_Q:
            m_eventRecorder->pushInputButton("left", state);
            break;
        case Qt::Key::Key_M:
            m_eventRecorder->pushInputButton("switch_selection_mode", state);
        default:
            break;
        }
    } else if (e->type() == QEvent::MouseMove) {
        auto *mouseEvent = static_cast<QMouseEvent*>(e);
        m_eventRecorder->pushInputCursorPosition(mouseEvent->pos().x(), mouseEvent->pos().y(), width(), height());
    }
    return false;
}
