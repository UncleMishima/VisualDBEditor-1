#include <QApplication>
#include <QQuickView>

#include <Controller.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Controller controller();

    return app.exec();
}
