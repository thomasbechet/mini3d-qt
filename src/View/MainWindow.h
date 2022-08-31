#pragma once

#include <QMainWindow>

#include "ui_mainwindow.h"

class MainWindow : public QMainWindow, Ui::MainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

public slots:
    void openBindingsEditor();
    void update();
    void toggleFullscreen();

private:
    void closeEvent(QCloseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    Ui::MainWindow *ui;
};
