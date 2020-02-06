#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cinemahall.h"
#include "database.h"
#include "informdialog.h"
#include <QFontDatabase>
#include <QtSql>
#include <QSqlQuery>
#include <QDebug>

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

    connect(loginWidget, SIGNAL(SendWidgetChangeSignal(QString)), this, SLOT(ChangeToUserWidget(QString)) );
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
    db.setDatabaseName("C:/Users/Kamil/Desktop/projekt.db");
    QSqlQuery query;
    unsigned int cols=0;
    unsigned int rows=0;
    unsigned int idhall = 0;
    QVector<uint> container;
    if(db.open())
    {
        QString h = movieContainer.at(id)->GetCurrentHour();
        if( !query.exec( "SELECT s.Rzedy, s.Kolumny, s.IdSali FROM Terminarz t INNER JOIN Sala s ON t.IdSali=s.IdSali WHERE t.GodzinaSeansu='"+h+
                        "' AND t.IdFilmu="+QString::number(id) ) )
        {
            InformDialog::ExecInformDialog("Error", query.lastError().text());
        }
        query.next();
        rows = query.value("Rzedy").toUInt();
        cols = query.value("Kolumny").toUInt();
        idhall = query.value("IdSali").toUInt();

        if( !query.exec( "SELECT NrMiejsca FROM Rezerwacje WHERE Godzina='"+h+"' AND IdFilmu ="+QString::number(id)) )
        {
            InformDialog::ExecInformDialog("Error", query.lastError().text());
        }

        while(query.next())
        {
            container.push_back( query.value("NrMiejsca").toUInt() );
        }

        QVector<uint> cont = CinemaHall::execCinemaHall( rows,cols,container );
        if(!cont.isEmpty())
        {
            if( !query.exec( "SELECT NrMiejsca FROM Rezerwacje WHERE NrMiejsca="+QString::number(cont.at(0))) )
            {
                InformDialog::ExecInformDialog("Error", query.lastError().text());
            }
            query.first();
            if( !query.isNull(0) )
            {

            }
        }
        db.close();
    }
}

void MainWindow::ChangeToUserWidget( QString name )
{
    ui->userWidgetLayout->removeWidget(loginWidget);
    loginWidget->hide();
    ui->userWidgetLayout->addWidget(userWidget);
    userWidget->SetName(name);
    userWidget->show();
}

void MainWindow::ChangeToLoginWidget()
{
    ui->userWidgetLayout->removeWidget(userWidget);
    userWidget->hide();
    ui->userWidgetLayout->addWidget(loginWidget);
    loginWidget->show();
}

void MainWindow::setMovies()
{
    ui->widget->setLayout(new QGridLayout(this));

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/Kamil/Desktop/projekt.db");
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

            if( !query.exec("SELECT GodzinaSeansu FROM Terminarz WHERE IdFilmu="+QString::number(i)) )
            {
                InformDialog::ExecInformDialog("Error", query.lastError().text() );
                break;
            }
            while(query.next())
            {
                movieContainer.at(i)->SetItemToCombo(query.value("GodzinaSeansu").toString());
            }
        }
        db.close();
    }

}

void MainWindow::AddNewWidget( QString path, QString info, int id)
{
    Movie *movie = new Movie( this, info, path, id );
    connect(movie, SIGNAL( SendButtonSignal(int) ), this, SLOT( BookSeats(int) ));
    ui->widget->layout()->addWidget( movie );
    movieContainer.push_back(movie);
}
