#include "userwidget.h"
#include "ui_userwidget.h"
#include "informdialog.h"
#include <QtSql>
#include <QSqlQuery>

UserWidget::UserWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserWidget)
{
    ui->setupUi(this);
    connect(ui->logoutButton, SIGNAL(clicked()), this, SLOT(OnLogoutButtonClick()));
}

UserWidget::~UserWidget()
{
    for(int i=0; i<m_BookWidgetContainer.size(); i++)
    {
        ui->booksGridLayout->removeWidget(m_BookWidgetContainer.at(i));
        delete m_BookWidgetContainer.at(i);
        m_BookWidgetContainer[i] = nullptr;
    }
    m_BookWidgetContainer.clear();
    delete ui;
}

void UserWidget::SetInfo( QString name, QString login, int id )
{
    ui->nameLabel->setText("Hello "+name+"!");
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("projekt.db");
    for(int i=0; i<m_BookWidgetContainer.size(); i++)
    {
        ui->booksGridLayout->removeWidget(m_BookWidgetContainer.at(i));
        delete m_BookWidgetContainer.at(i);
        m_BookWidgetContainer[i] = nullptr;
    }
    m_BookWidgetContainer.clear();

    if(db.open())
    {
        QSqlQuery query;

        if( !query.exec( "SELECT IdRezerwacji FROM Rezerwacje r INNER JOIN Uzytkownicy u ON r.IdUzytkownika = u.IdUzytkownika"
                         " WHERE u.IdUzytkownika="+QString::number(id)+" AND u.Login='"+login+"'" ))
        {
            InformDialog::ExecInformDialog("Error", query.lastError().text() );
        }
        else
        {
            while(query.next())
            {
                m_BookWidgetContainer.push_back(new BookWidget(this));
                m_BookWidgetContainer.last()->SetID(query.value("IdRezerwacji").toInt());
                connect(m_BookWidgetContainer.last(), SIGNAL( RemoveCurrentWidget(int) ), this, SLOT( RemoveReservation(int) ) );
                ui->booksGridLayout->addWidget( m_BookWidgetContainer.last() );
            }
        }

        for( int i=0; i<m_BookWidgetContainer.size(); i++)
        {
            if( !query.exec( "SELECT IdFilmu, IdSali, NrMiejsca, Godzina, Data FROM ( Rezerwacje r INNER JOIN "
                             "Uzytkownicy u ON r.IdUzytkownika = u.IdUzytkownika ) "
                             "INNER JOIN RezerwacjeMiejsca rm ON r.IdRezerwacji = rm.IdRezerwacji "
                             "WHERE u.IdUzytkownika="+QString::number(id)+" "
                             "AND u.Login='"+login+"' "
                             "AND r.IdRezerwacji="+QString::number(m_BookWidgetContainer.at(i)->GetID()) ) )
            {
                InformDialog::ExecInformDialog("Error", query.lastError().text() );
            }
            else
            {
                QString places;
                int iter=0;
                while(query.next())
                {
                    if(iter>0)
                    {
                        places += ","+query.value("NrMiejsca").toString();
                    }
                    else
                    {
                        places += query.value("NrMiejsca").toString();
                    }
                    iter++;
                }
                query.first();
                QSqlQuery secQuery;
                int idFilmu = query.value("IdFilmu").toInt();
                if( !secQuery.exec("SELECT Nazwa FROM Filmy WHERE IdFilmu="+QString::number(idFilmu)) )
                {
                    InformDialog::ExecInformDialog("Error", query.lastError().text() );
                }
                else
                {
                    secQuery.first();
                }
                m_BookWidgetContainer.at(i)->SetDesc( "Tytuł: "    +secQuery.value("Nazwa").toString()  +"\n"
                                                "Id Sali: "           +query.value("IdSali").toString()   +"\n"
                                                "Godzina: "           +query.value("Godzina").toString()  +"\n"
                                                "Data: "              +query.value("Data").toString()     +"\n"
                                                "Miejsca: "           +places );
            }
        }
        db.close();
    }
}

void UserWidget::RemoveReservation( int id )
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("projekt.db");
    QSqlQuery query;
    bool ifToDelete = true;
    if( db.open() )
    {
        if( !query.exec( "DELETE FROM RezerwacjeMiejsca WHERE IdRezerwacji="+QString::number(id) ) )
        {
            InformDialog::ExecInformDialog("Error", query.lastError().text() );
            ifToDelete = false;
        }
        else
        {
            if( !query.exec( "DELETE FROM Rezerwacje WHERE IdRezerwacji="+QString::number(id) ) )
            {
                InformDialog::ExecInformDialog("Error", query.lastError().text() );
                ifToDelete = false;
            }
        }
        db.close();
    }
    if( ifToDelete )
    {
        for( int i=0; i<m_BookWidgetContainer.size(); i++)
        {
            if( m_BookWidgetContainer.at(i)->GetID() == id )
            {
                ui->booksGridLayout->removeWidget( m_BookWidgetContainer.at( i ) );
                delete m_BookWidgetContainer[i];
                m_BookWidgetContainer[i] = nullptr;
                m_BookWidgetContainer.removeAt(i);
                break;
            }
        }
    }
}

void UserWidget::OnLogoutButtonClick()
{
    emit SendWidgetChangeSignal();
}
