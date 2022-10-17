#include "screen.h"
#include "ui_screen.h"

Screen::Screen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Screen)
{
    ui->setupUi(this);
}

Screen::~Screen()
{
    delete ui;
}
