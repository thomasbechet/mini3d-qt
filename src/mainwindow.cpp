#include "mainwindow.h"

#include <QMenuBar>
#include <QStatusBar>
#include <QLabel>
#include <qt_windows.h>

#include "bindingseditor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    // Configure main window
    setWindowTitle("mini3d");
    resize(600, 450);

    // Create menu bar
    QMenu *fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction("Open");
    QMenu *editMenu = menuBar()->addMenu("Edit");
    QAction *editBindings = editMenu->addAction("Edit bindings");
    connect(editBindings, SIGNAL(triggered()), this, SLOT(openBindingsEditor()));
    QMenu *helpMenu = menuBar()->addMenu("Help");
    helpMenu->addAction("About");

    // Configure status bar
    statusBar()->addPermanentWidget(new QLabel("0.0.1"));

    // Create application
    m_app = mini3d_app_new();
    auto *surface_widget = new QWidget(this);
    surface_widget->resize(1600, 900);
    m_renderer = mini3d_renderer_new_wgpu_win32(
                (void*)surface_widget->winId(),
                (void*)GetModuleHandle(nullptr));
}
MainWindow::~MainWindow()
{
    // Free application
    mini3d_renderer_delete(m_renderer);
    mini3d_app_delete(m_app);
}

void MainWindow::openBindingsEditor()
{
    BindingsEditor dialog(this);
    dialog.exec();
}
