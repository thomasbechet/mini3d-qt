#include <QApplication>
#include <QMainWindow>

#include "mainwindow.h"
#include <mini3d.h>

int main(int argc, char *argv[])
{
    auto *app = mini3d_app_new();
    mini3d_app_delete(app);

    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return a.exec();
}
