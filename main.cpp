#include "screen.h"
#include <QPainter>
#include <QLabel>
#include <QDebug>
#include <QTimer>
#include <qmath.h>
#include <QVBoxLayout>
#include <QBasicTimer>
#include <QApplication>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <string>
#include <vector>
#include "mainwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Screen w;

    MainWidget * widgetMain = new MainWidget();

    w.setCentralWidget(widgetMain);
    w.resize(1024, 640);
    w.show();

    return a.exec();
}
