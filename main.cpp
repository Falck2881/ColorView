#include "MainWindow.h"
#include <QFile>
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QFile file(":/Takezo.qss");
    if(file.open(QIODevice::ReadOnly))
        qDebug() << "File Takezo.qss open successfully";

    QApplication app(argc, argv);
    app.setStyleSheet(file.readAll());
    App::MainWindow w;
    w.show();
    return app.exec();
}
