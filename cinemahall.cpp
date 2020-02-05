#include "cinemahall.h"
#include "ui_cinemahall.h"
#include <QThread>

CinemaHall::CinemaHall(QDialog *parent, uint row, uint col) :
    QDialog(parent),
    ui(new Ui::CinemaHall)
{
    ui->setupUi(this);
    uint size = row*col;
    for(uint i=0; i<size; i++)
    {
        m_SeatsContainer.push_back( new seat(this, static_cast<unsigned int>(i)) );
    }
    int iterator = 0;
    for(uint i=0; i<row; i++)
    {
        for(uint j=0; j<col; j++)
        {
            ui->mainGrid->addWidget( m_SeatsContainer[iterator],static_cast<int>(i),static_cast<int>(j) );
            iterator++;
        }
    }
}

CinemaHall::~CinemaHall()
{
    QVector<seat>::iterator *iterator;
    for( iterator = m_SeatsContainer.begin(); iterator
         < m_SeatsContainer.end(); iterator++)
    {
        delete (*iterator);
        (*iterator) = nullptr;
    }
    delete ui;
}

void CinemaHall::execCinemaHall( uint row, uint col )
{
    CinemaHall cinemaHall(nullptr, row, col);
    cinemaHall.exec();
}
