#pragma once

#include <QWidget>
#include <QResizeEvent>
#include <QWindow>
#include <QFrame>

#include <Model/App.h>

class AppWidget : public QFrame
{
    Q_OBJECT
public:
    explicit AppWidget(QWidget* parent = nullptr);

    void progressAppAndRender();

private:
    void resizeEvent(QResizeEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *e) override;

    std::shared_ptr<mini3d::App> m_app;
    std::shared_ptr<mini3d::WGPURenderer> m_renderer;
};
