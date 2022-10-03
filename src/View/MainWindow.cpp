#include "MainWindow.h"

#include <QMenuBar>
#include <QStatusBar>
#include <QLabel>
#include <QWindow>
#include <QLayout>

#include <QTimer>

#include "InputEditor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}, ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Configure main window
    setWindowTitle("mini3d");

    // Setup update loop
    auto *timer = new QTimer(this);
    timer->setInterval(0);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start();
}

void MainWindow::openBindingsEditor()
{
    InputEditor dialog(this);
    dialog.exec();
}
void MainWindow::update()
{
    ui->frame->update();
}
void MainWindow::toggleFullscreen()
{
    if (isFullScreen()) {
        showNormal();
        menuBar()->show();
        ui->frame->showNormal();
    } else {
        showFullScreen();
        menuBar()->hide();
        ui->frame->showFullScreen();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    ui->frame->close();
}
void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    toggleFullscreen();
}
