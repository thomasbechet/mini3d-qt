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
}

void MainWindow::update(float deltaTime)
{
    ui->frame->update(deltaTime);
}
bool MainWindow::running() const
{
    return m_running;
}

void MainWindow::openBindingsEditor()
{
    InputEditor dialog(this);
    dialog.exec();
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
    m_running = false;
}
void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    toggleFullscreen();
}
