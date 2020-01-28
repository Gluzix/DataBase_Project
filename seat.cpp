#include "seat.h"
#include "ui_seat.h"

seat::seat(QWidget *parent, unsigned int id) :
    QWidget(parent),
    ui(new Ui::seat), m_ID(id)
{
    ui->setupUi(this);
}

seat::~seat()
{
    delete ui;
}
