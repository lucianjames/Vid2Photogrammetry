#include <QApplication>

#include "mainwindow.h"
#include "qtDarkTheme.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    qApp->setStyle(QStyleFactory::create("fusion"));
    qApp->setPalette(createDarkQPallette());
    MainWindow w;
    w.show();
    return a.exec();
}
