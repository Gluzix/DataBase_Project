#include "cinemahall.h"
#include "ui_cinemahall.h"

CinemaHall::CinemaHall(QDialog *parent, int row, int col) :
    QDialog(parent),
    ui(new Ui::CinemaHall), m_IfConfirmed( false )
{
    ui->setupUi(this);
    int size = row*col;
    for(int i=0; i<size; i++)
    {
        m_SeatsContainer.push_back( new seat(this, i) );
    }
    int iterator = 0;
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            ui->mainGrid->addWidget( m_SeatsContainer[iterator],i,j );
            iterator++;
        }
    }
    connect(ui->submitButton, SIGNAL(clicked()), this, SLOT(OnSubmitButtonClick()));
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

QVector<int> CinemaHall::execCinemaHall( int row, int col, QVector<int>&cont )
{
    CinemaHall cinemaHall(nullptr, row, col);
    cinemaHall.SetAlreadyChecked(cont);
    cinemaHall.exec();
    QVector<int> vect;
    if( cinemaHall.GetIfConfirmed() )
    {
        for( int i=0; i<cinemaHall.m_SeatsContainer.size(); i++ )
        {
            if( cinemaHall.m_SeatsContainer.at(i)->GetIfBooked() )
            {
                vect.push_back( i );
            }
        }
    }
    return vect;
}

bool CinemaHall::GetIfConfirmed()
{
    return m_IfConfirmed;
}

void CinemaHall::OnSubmitButtonClick()
{
    m_IfConfirmed = true;
    close();
}

void CinemaHall::SetAlreadyChecked( QVector<int> &cont )
{
    for(int i=0; i<cont.size(); i++)
    {
        m_SeatsContainer.at( cont.at(i) )->StateChange(true);
    }
}
