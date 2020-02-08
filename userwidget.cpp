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
    for(int i=0; i<bookWidgetContainer.size(); i++)
    {
        ui->booksGridLayout->removeWidget(bookWidgetContainer.at(i));
        delete bookWidgetContainer.at(i);
        bookWidgetContainer[i] = nullptr;
    }
    bookWidgetContainer.clear();
    delete ui;
}

void UserWidget::SetInfo( QString name, QString login, int id )
{
    ui->nameLabel->setText("Hello "+name+"!");
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./../DataBaseProject/projekt.db");
    for(int i=0; i<bookWidgetContainer.size(); i++)
    {
        ui->booksGridLayout->removeWidget(bookWidgetContainer.at(i));
        delete bookWidgetContainer.at(i);
        bookWidgetContainer[i] = nullptr;
    }
    bookWidgetContainer.clear();

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
                bookWidgetContainer.push_back(new BookWidget(this));
                bookWidgetContainer.last()->SetBookId(query.value("IdRezerwacji").toInt());
                connect(bookWidgetContainer.last(), SIGNAL( RemoveCurrentWidget(int) ), this, SLOT( RemoveReservation(int) ) );
                ui->booksGridLayout->addWidget( bookWidgetContainer.last() );
            }
        }

        for( int i=0; i<bookWidgetContainer.size(); i++)
        {
            if( !query.exec( "SELECT IdFilmu, IdSali, NrMiejsca, Godzina FROM ( Rezerwacje r INNER JOIN "
                             "Uzytkownicy u ON r.IdUzytkownika = u.IdUzytkownika ) "
                             "INNER JOIN RezerwacjeMiejsca rm ON r.IdRezerwacji = rm.IdRezerwacji "
                             "WHERE u.IdUzytkownika="+QString::number(id)+" "
                             "AND u.Login='"+login+"' "
                             "AND r.IdRezerwacji="+QString::number(bookWidgetContainer.at(i)->returnBookId()) ) )
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
                bookWidgetContainer.at(i)->SetInfo( "Id filmu: "+ query.value("IdFilmu").toString()+"\n"
                                              "Id Sali: "+query.value("IdSali").toString()+"\n"
                                              "Godzina: "+query.value("Godzina").toString()+"\n"
                                              "Miejsca: "+ places );
            }
        }

        db.close();
    }
}

void UserWidget::RemoveReservation( int id )
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./../DataBaseProject/projekt.db");
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
        for( int i=0; i<bookWidgetContainer.size(); i++)
        {
            if( bookWidgetContainer.at(i)->returnBookId() == id )
            {
                ui->booksGridLayout->removeWidget( bookWidgetContainer.at( i ) );
                delete bookWidgetContainer[i];
                bookWidgetContainer[i] = nullptr;
                bookWidgetContainer.removeAt(i);
                break;
            }
        }
    }
}

void UserWidget::OnLogoutButtonClick()
{
    emit SendWidgetChangeSignal();
}
