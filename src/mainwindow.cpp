#include "mainwindow.h"

#include <QMenuBar>
#include <QStatusBar>
#include <QLabel>

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
}
MainWindow::~MainWindow()
{

}

void MainWindow::openBindingsEditor()
{
    BindingsEditor dialog(this);
    dialog.exec();
}
