#pragma once

#include <QMainWindow>

#include "ui_mainwindow.h"

class MainWindow : public QMainWindow, Ui::MainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    void closeEvent(QCloseEvent *event) override;

public slots:
    void openBindingsEditor();
    void update();

private:
    Ui::MainWindow *ui;
};
