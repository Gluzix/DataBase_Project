#include "seat.h"
#include "ui_seat.h"

seat::seat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::seat)
{
    ui->setupUi(this);
}

seat::~seat()
{
    delete ui;
}
