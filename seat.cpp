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
    bIfBooked = false;
}

seat::~seat()
{
    delete ui;
}

void seat::StateChange(bool state)
{
    if( state )
    {
        ui->checkBox->setStyleSheet("QCheckBox{image: url(:/Resources/seatUnAvailable.png);background:none;} QCheckBox::indicator {image: url(:/Resources/seatUnAvailable.png);background:none;}");
        ui->checkBox->setDisabled( state );
    }
}

bool seat::GetIfBooked()
{
    return bIfBooked;
}

void seat::OnStateChanged(int state)
{
    if( state == 2 )
    {
        qDebug()<<"Seat nr:"<<m_ID<<"has been booked";
        bIfBooked = true;
    }
    else if( state == 0 ){
        qDebug()<<"Seat nr:"<<m_ID<<"has been unbooked";
        bIfBooked = false;
    }
}
