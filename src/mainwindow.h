#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mini3d.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void openBindingsEditor();

private:
    mini3d_app *m_app;
    mini3d_renderer *m_renderer;
};

#endif // MAINWINDOW_H
