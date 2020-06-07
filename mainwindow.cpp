#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cinemahall.h"
#include "informdialog.h"
#include <QFontDatabase>
#include <QtSql>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SetMovies();
    QFontDatabase::addApplicationFont(":/Resources/fonts/Open_Sans/OpenSans-Regular.ttf");
    QFont openSans("Open Sans");
    QApplication::setFont(openSans);

    m_bIfLogged = false;
    m_pLoginWidget = new LoginWidget( this );
    m_pUserWidget = new UserWidget( this );
    m_pUserWidget->hide();
    m_pOpenButton = new QPushButton( this );
    m_pOpenButton->setStyleSheet("QPushButton{"
                                 "font-size:14px;"
                                 "border-radius:6px;"
                                 "background-color:rgb(110,110,110);"
                                 "padding-top:6px;"
                                 "padding-bottom:6px;"
                                 "}  "
                                 "QPushButton:hover{"
                                 "background-color:rgb(130,130,130);"
                                 "}");
    layout()->addWidget(m_pOpenButton);
    m_pOpenButton->setGeometry(0,25,20,100);
    m_pOpenButton->setText("->");
    m_pOpenButton->hide();
    connect(m_pLoginWidget, SIGNAL(SendWidgetChangeSignal()), this, SLOT(ChangeToUserWidget()) );
    connect(m_pUserWidget, SIGNAL(SendWidgetChangeSignal()), this, SLOT(ChangeToLoginWidget()) );
    connect( ui->hideLeftPanelButton, SIGNAL(clicked()), this, SLOT(OnHideButtonClick()) );
    connect(m_pOpenButton, SIGNAL(clicked()), this, SLOT(OnShowButtonClick()));
    ui->userWidgetLayout->addWidget(m_pLoginWidget);
}

MainWindow::~MainWindow()
{
    m_MovieContainer.clear();
    delete ui;
}

void MainWindow::BookSeats( int id )
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("projekt.db");
    QSqlQuery query;
    int cols=0;
    int rows=0;
    int idhall = 0;
    int userId = 0;
    int bookId = -1;
    QString login = QString();
    QString name = QString();
    m_pLoginWidget->GetLoginAndId(login, userId, name);
    QVector<int> container;
    if( db.open() )
    {
        QString d = m_MovieContainer.at(id)->GetCurrentDate();
        QString h = m_MovieContainer.at(id)->GetCurrentHour();
        if( !query.exec( "SELECT s.Rzedy, s.Kolumny, s.IdSali FROM ( Terminarz t INNER JOIN Sala s ON t.IdSali=s.IdSali ) "
                         "INNER JOIN DataTerminarz dt ON t.IdTerminarz = dt.IdTerminarz "
                         "WHERE t.GodzinaSeansu='"+h+
                         "' AND dt.Data='"+d+
                         "' AND t.IdFilmu="+QString::number(id) ) )
        {
            InformDialog::ExecInformDialog("Error", query.lastError().text());
        }

        query.next();
        rows = query.value("Rzedy").toInt();
        cols = query.value("Kolumny").toInt();
        idhall = query.value("IdSali").toInt();

        if( !query.exec( "SELECT NrMiejsca FROM RezerwacjeMiejsca rm INNER JOIN Rezerwacje r ON rm.IdRezerwacji = r.IdRezerwacji "
                         "WHERE Godzina='"+h+"' "
                         "AND Data='"+d+
                         "' AND IdSali="+QString::number(idhall)+" "
                         "AND IdFilmu ="+QString::number(id)) )
        {
            InformDialog::ExecInformDialog("Error", query.lastError().text());
        }

        while(query.next())
        {
            container.push_back( query.value("NrMiejsca").toInt() );
        }

        QVector<int> cont = CinemaHall::execCinemaHall( rows,cols,container );

        if( !cont.isEmpty() )
        {
            if( !query.exec("SELECT IdRezerwacji FROM Rezerwacje WHERE "
                           "Godzina='"+h+"' "
                           "AND Data='"+d+
                           "' AND IdSali="+QString::number(idhall)+" "
                           "AND IdFilmu ="+QString::number(id)+" "
                           "AND IdUzytkownika ="+QString::number(userId)))
            {
                InformDialog::ExecInformDialog("Error", query.lastError().text());
            }
            else
            {
                query.first();
                if( query.isNull(0) )
                {
                    if( !query.exec( "INSERT INTO Rezerwacje ( 'Godzina', 'IdFilmu', 'IdSali', 'IdUzytkownika', 'Data' )"
                                     " VALUES('"+h+"',"+QString::number(id)+","+QString::number(idhall)+", "+QString::number(userId)+", '"+d+"' )" ) )
                    {
                        InformDialog::ExecInformDialog("Error", query.lastError().text());
                    }
                }
                if( !query.exec("SELECT IdRezerwacji FROM Rezerwacje WHERE "
                               "Godzina='"+h+"' "
                               "AND Data='"+d+"' "
                               "AND IdSali="+QString::number(idhall)+" "
                               "AND IdFilmu ="+QString::number(id)+" "
                               "AND IdUzytkownika ="+QString::number(userId)))
                {
                    InformDialog::ExecInformDialog("Error", query.lastError().text());
                }
                else
                {
                    query.first();
                    bookId = query.value(0).toInt();
                }
            }

            for( int i=0; i<cont.size(); i++ )
            {
                if( !query.exec( "INSERT INTO RezerwacjeMiejsca ( 'IdRezerwacji', 'NrMiejsca' )"
                                 " VALUES("+QString::number(bookId)+", "+QString::number(cont.at(i))+")"))
                {
                    InformDialog::ExecInformDialog("Error", query.lastError().text());
                }
            }
            m_pUserWidget->SetInfo(name,login, userId);
        }
        db.close();
    }
}

void MainWindow::ChangeToUserWidget()
{
    int userId = 0;
    QString login = QString();
    QString name = QString();
    m_pLoginWidget->GetLoginAndId(login, userId, name);
    ui->userWidgetLayout->removeWidget(m_pLoginWidget);
    m_pLoginWidget->hide();
    ui->userWidgetLayout->addWidget(m_pUserWidget);
    m_pUserWidget->SetInfo(name,login, userId);
    m_pUserWidget->show();

    for(int i=0; i<m_MovieContainer.size(); i++)
    {
        m_MovieContainer.at(i)->SetState( true );
    }
}

void MainWindow::ChangeToLoginWidget()
{
    ui->userWidgetLayout->removeWidget(m_pUserWidget);
    m_pUserWidget->hide();
    ui->userWidgetLayout->addWidget(m_pLoginWidget);
    m_pLoginWidget->Reset();
    m_pLoginWidget->show();
    for(int i=0; i<m_MovieContainer.size(); i++)
    {
        m_MovieContainer.at(i)->SetState( false );
    }
}

void MainWindow::OnHideButtonClick()
{
    ui->userWidget->hide();
    m_pOpenButton->show();
}

void MainWindow::OnShowButtonClick()
{
    m_pOpenButton->hide();
    ui->userWidget->show();
}

void MainWindow::SetMovies()
{
    ui->widget->setLayout(new QGridLayout(this));

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("projekt.db");
    QSqlQuery query;

    if( db.open() )
    {
        if( !query.exec("SELECT * FROM Filmy") )
        {
            InformDialog::ExecInformDialog("Error", query.lastError().text() );
        }
        int iterator = 0;
        while(query.next())
        {
            AddNewWidget( query.value("Url").toString()+";" , query.value("Opis").toString(), iterator );
            iterator++;
        }

        for(int i=0; i<m_MovieContainer.size(); i++)
        {
            if( !query.exec("SELECT DISTINCT Data FROM DataTerminarz dt "
                            "INNER JOIN Terminarz t ON dt.IdTerminarz=t.IdTerminarz "
                            "WHERE IdFilmu="+QString::number(i)) )
            {
                InformDialog::ExecInformDialog("Error", query.lastError().text() );
                break;
            }
            while( query.next() )
            {
                m_MovieContainer.at(i)->SetItemToCombo(query.value("Data").toString());
            }
        }
        db.close();

        for(int i=0; i<m_MovieContainer.size(); i++)
        {
            m_MovieContainer[i]->SetFirstItem();
        }
    }
}

void MainWindow::AddNewWidget( QString path, QString info, int id)
{
    Movie *movie = new Movie( this, info, path, id );
    connect(movie, SIGNAL( SendButtonSignal(int) ), this, SLOT( BookSeats(int) ));
    ui->widget->layout()->addWidget( movie );
    m_MovieContainer.push_back(movie);
}
