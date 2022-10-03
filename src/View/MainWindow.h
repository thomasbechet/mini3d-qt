#pragma once

#include <QMainWindow>

#include "ui_mainwindow.h"

class MainWindow : public QMainWindow, Ui::MainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    void update(float deltaTime);
    bool running() const;

public slots:
    void openBindingsEditor();
    void toggleFullscreen();

private:
    void closeEvent(QCloseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    Ui::MainWindow *ui;
    bool m_running = true;
};
