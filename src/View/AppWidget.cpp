#include "AppWidget.h"

#include <QPlatformSurfaceEvent>
#include <QCoreApplication>
#include <QWindow>
#include <mini3d.h>

AppWidget::AppWidget(QWidget* parent)
    : QFrame{parent}
{
    // Initialize values
    m_focus = false;
    m_virtualMouse = QPointF(0, 0);
    m_timer.start();

    // Install event filter
    parent->installEventFilter(this);

    // Configure QFrame
    setAutoFillBackground(false);
    setUpdatesEnabled(false);

    // Create app and renderer
    m_app = std::make_unique<mini3d::App>();
    m_events = std::make_unique<mini3d::AppEvents>();
    m_requests = std::make_unique<mini3d::AppRequests>();
    m_renderer = std::make_unique<mini3d::WGPURenderer>(winId());
    m_mapping = std::make_unique<InputMapping>();

    // Import default assets
    mini3d_utils_import_image_info imageInfo;
    imageInfo.name   = "car";
    imageInfo.source = "../mini3d-qt/mini3d/assets/car.png";
    mini3d_utils_import_image(&imageInfo, m_events->handle());
    imageInfo.name   = "alfred";
    imageInfo.source = "../mini3d-qt/mini3d/assets/alfred.png";
    mini3d_utils_import_image(&imageInfo, m_events->handle());
    mini3d_utils_import_model_info modelInfo;
    modelInfo.name         = "car";
    modelInfo.obj_source   = "../mini3d-qt/mini3d/assets/car.obj";
    modelInfo.flat_normals = false;
    mini3d_utils_import_model(&modelInfo, m_events->handle());
    modelInfo.name         = "alfred";
    modelInfo.obj_source   = "../mini3d-qt/mini3d/assets/alfred.obj";
    modelInfo.flat_normals = false;
    mini3d_utils_import_model(&modelInfo, m_events->handle());
}

void AppWidget::update(float deltaTime)
{
    if (m_app && m_renderer) {

        // Compute elapsed time
//        auto elapsed = m_timer.nsecsElapsed();
//        auto deltaTime = (float)(((double)elapsed) / 1000000.0);
//        m_timer.restart();

//        qDebug() << deltaTime;

        // Progress the app
        m_app->progress(*m_events, *m_requests, *m_renderer, deltaTime);

        // Check requests
        if (m_requests->reloadInputMapping()) {
            m_mapping->reload(*m_app);
        }
        if (m_requests->shutdown()) {

        }
        m_requests->reset();

        // Render the app
        m_renderer->render(*m_app);
    }
}

void AppWidget::setFocus(bool toggle)
{
    m_focus = toggle;
    if (m_focus) {
        grabMouse();
        setMouseTracking(true);
        setCursor(Qt::BlankCursor);
    } else {
        releaseMouse();
        setMouseTracking(false);
        setCursor(Qt::ArrowCursor);
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
    m_mapping.reset();
    m_renderer.reset();
    m_requests.reset();
    m_events.reset();
    m_app.reset();
}
bool AppWidget::eventFilter(QObject *obj, QEvent *e)
{
    if (e->type() == QEvent::KeyPress && static_cast<QKeyEvent*>(e)->key() == Qt::Key_Escape) {
        setFocus(false);
    }

    if (e->type() == QEvent::MouseButtonPress && static_cast<QMouseEvent*>(e)->button() == Qt::MouseButton::LeftButton) {
        setFocus(true);
    }

    if (m_focus) {
        if (e->type() == QEvent::KeyPress || e->type() == QEvent::KeyRelease) {
            auto *keyEvent = static_cast<QKeyEvent*>(e);
            m_mapping->dispatchKeyEvent(keyEvent, *m_events);

        } else if (e->type() == QEvent::MouseButtonPress || e->type() == QEvent::MouseButtonRelease) {
            auto *mouseEvent = static_cast<QMouseEvent*>(e);
            m_mapping->dispatchMouseButtonEvent(mouseEvent, *m_events);
        } else if (e->type() == QEvent::MouseMove) {
            auto *mouseEvent = static_cast<QMouseEvent*>(e);

            // Compute global coordinates
            QPointF current = mapToGlobal(mouseEvent->position());
            QPoint target = mapToGlobal(QPoint(width() / 2.0, height() / 2.0));

            // Compute motion
            auto motion = QPointF(0.0, 0.0);
            if ((int)current.x() != target.x() || (int)current.y() != target.y()) {

                // Compute motion
                motion = current - target;
                m_mapping->dispatchMouseMotionEvent(motion.x(), motion.y(), *m_events);

                // Update virtual mouse
                m_virtualMouse += motion;
                m_virtualMouse.setX(qMax(0.0, qMin((float)width(), m_virtualMouse.x())));
                m_virtualMouse.setY(qMax(0.0, qMin((float)height(), m_virtualMouse.y())));

                // Dispatch mouse position
                float viewport_x, viewport_y;
                mini3d_utils_inner_to_viewport_position(m_virtualMouse.x(), m_virtualMouse.y(), width(), height(), &viewport_x, &viewport_y);
                m_mapping->dispatchMousePositionEvent(viewport_x, viewport_y, *m_events);

                // Recenter mouse
                QCursor::setPos(target);
                e->accept();
            } else {
                m_mapping->dispatchMouseMotionEvent(0.0, 0.0, *m_events);
            }
        }
    }

    return false;
}
