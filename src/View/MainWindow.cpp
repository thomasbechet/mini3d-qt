#include "MainWindow.h"

#include <QMenuBar>
#include <QStatusBar>
#include <QLabel>
#include <QWindow>
#include <QLayout>

#include <QTimer>

#include "BindingsEditor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}, ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Configure main window
    setWindowTitle("mini3d");

    // Setup update loop
    auto *timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start();

//    showFullScreen();
//    menuBar()->hide();
//    ui->frame->showFullScreen();
}

void MainWindow::openBindingsEditor()
{
    BindingsEditor dialog(this);
    dialog.exec();
}
void MainWindow::update()
{
    ui->frame->progressAppAndRender();
}
