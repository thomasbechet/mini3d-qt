#pragma once

#include <QWidget>
#include <QResizeEvent>
#include <QWindow>
#include <QFrame>
#include <QElapsedTimer>

#include <Model/App.h>
#include <Model/AppEvents.h>
#include <Model/AppRequests.h>
#include <Model/WGPURenderer.h>
#include <Model/InputMapping.h>

class AppWidget : public QFrame
{
    Q_OBJECT
public:
    explicit AppWidget(QWidget* parent = nullptr);

    void update();

private:
    void setFocus(bool toggle);
    void resizeEvent(QResizeEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *e) override;

    std::unique_ptr<mini3d::App> m_app;
    std::unique_ptr<mini3d::AppEvents> m_events;
    std::unique_ptr<mini3d::AppRequests> m_requests;
    std::unique_ptr<mini3d::WGPURenderer> m_renderer;
    std::unique_ptr<InputMapping> m_mapping;

    bool m_focus;
    QPointF m_virtualMouse;
    QElapsedTimer m_timer;
};
