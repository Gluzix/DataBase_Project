#include "mainwindow.h"
#include "ui_mainwindow.h"

const int m_AmountOfSeats = 5;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for(int i=0; i<m_AmountOfSeats; i++)
    {
        m_SeatsContainer.push_back( new seat(this) );
    }

    for(int i=0; i<m_AmountOfSeats; i++)
    {
        for(int j=0; j<m_AmountOfSeats; j++)
        {
            ui->gridLayout->addWidget( m_SeatsContainer[i],i,j, Qt::AlignmentFlag::AlignLeft );
        }
    }
}

MainWindow::~MainWindow()
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
