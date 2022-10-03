#include <QApplication>
#include <QMainWindow>

#include <View/MainWindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();

    QElapsedTimer timer;
    while (mainWindow.running()) {

        // Process Qt events
        a.processEvents();

        // Compute elapsed time
        auto elapsed = timer.nsecsElapsed();
        auto deltaTime = (float)(((double)elapsed) / 1000000.0);
        timer.restart();

        mainWindow.update(deltaTime);
    }

    a.exit();
    return 0;
}
