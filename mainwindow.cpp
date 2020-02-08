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
    setMovies();
    //QFontDatabase::addApplicationFont(":/Resources/fonts/Bangers/Bangers-Regular.ttf");
    //QFont Bangers("Bangers");
    //QApplication::setFont(Bangers);

    bIfLogged = false;
    loginWidget = new LoginWidget( this );
    userWidget = new UserWidget( this );
    userWidget->hide();

    connect(loginWidget, SIGNAL(SendWidgetChangeSignal()), this, SLOT(ChangeToUserWidget()) );
    connect(userWidget, SIGNAL(SendWidgetChangeSignal()), this, SLOT(ChangeToLoginWidget()) );

    ui->userWidgetLayout->addWidget(loginWidget);
}

MainWindow::~MainWindow()
{
    movieContainer.clear();
    delete ui;
}

void MainWindow::BookSeats( int id )
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./../DataBaseProject/projekt.db");
    QSqlQuery query;
    int cols=0;
    int rows=0;
    int idhall = 0;
    int userId = 0;
    int bookId = -1;
    QString login = QString();
    QString name = QString();
    loginWidget->GetLoginAndId(login, userId, name);
    QVector<int> container;
    if( db.open() )
    {
        QString d = movieContainer.at(id)->GetCurrentDate();
        QString h = movieContainer.at(id)->GetCurrentHour();
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
            userWidget->SetInfo(name,login, userId);
        }
        db.close();
    }
}

void MainWindow::ChangeToUserWidget()
{
    int userId = 0;
    QString login = QString();
    QString name = QString();
    loginWidget->GetLoginAndId(login, userId, name);
    ui->userWidgetLayout->removeWidget(loginWidget);
    loginWidget->hide();
    ui->userWidgetLayout->addWidget(userWidget);
    userWidget->SetInfo(name,login, userId);
    userWidget->show();

    for(int i=0; i<movieContainer.size(); i++)
    {
        movieContainer.at(i)->SetState( true );
    }
}

void MainWindow::ChangeToLoginWidget()
{
    ui->userWidgetLayout->removeWidget(userWidget);
    userWidget->hide();
    ui->userWidgetLayout->addWidget(loginWidget);
    loginWidget->Reset();
    loginWidget->show();
    for(int i=0; i<movieContainer.size(); i++)
    {
        movieContainer.at(i)->SetState( false );
    }
}

void MainWindow::setMovies()
{
    ui->widget->setLayout(new QGridLayout(this));

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./../DataBaseProject/projekt.db");
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

        for(int i=0; i<movieContainer.size(); i++)
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
                movieContainer.at(i)->SetItemToCombo(query.value("Data").toString());
            }
        }
        db.close();

        for(int i=0; i<movieContainer.size(); i++)
        {
            movieContainer[i]->SetFirstItem();
        }
    }
}

void MainWindow::AddNewWidget( QString path, QString info, int id)
{
    Movie *movie = new Movie( this, info, path, id );
    connect(movie, SIGNAL( SendButtonSignal(int) ), this, SLOT( BookSeats(int) ));
    ui->widget->layout()->addWidget( movie );
    movieContainer.push_back(movie);
}
