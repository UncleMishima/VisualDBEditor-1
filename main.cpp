#include <QApplication>

#include <Controller.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Controller controller;
    controller.start();

    return app.exec();
}
