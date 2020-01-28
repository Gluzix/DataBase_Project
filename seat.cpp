#include "seat.h"
#include "ui_seat.h"
#include <qdebug.h>

seat::seat(QWidget *parent, unsigned int id) :
    QWidget(parent),
    ui(new Ui::seat), m_ID(id)
{
    ui->setupUi(this);
    this->setCursor(Qt::PointingHandCursor);
    connect(ui->checkBox,SIGNAL(stateChanged(int)), this, SLOT(OnStateChanged(int)));
}

seat::~seat()
{
    delete ui;
}

void seat::OnStateChanged(int state)
{
    if( state == 2 )
    {
        qDebug()<<"Seat nr:"<<m_ID<<"has been booked";
    }
    else if( state == 0 ){
        qDebug()<<"Seat nr:"<<m_ID<<"has been unbooked";
    }
}
