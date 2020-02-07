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
    delete ui;
}

void UserWidget::SetInfo(QString name, QString login, int id)
{
    ui->nameLabel->setText("Hello "+name+"!");
    if(login.isEmpty())
    {
        ui->reservationInfo->setText("You have no reservations!");
    }
    else
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("./../DataBaseProject/projekt.db");
        if(db.open())
        {
            QSqlQuery query;
            if( !query.exec( "SELECT IdFilmu, IdSali, NrMiejsca, Godzina FROM Rezerwacje r INNER JOIN Uzytkownicy u ON r.IdUzytkownika = u.IdUzytkownika "
                             "WHERE u.IdUzytkownika="+QString::number(id)+" AND u.Login='"+login+"'" ) )
            {
                InformDialog::ExecInformDialog("Error", query.lastError().text() );
            }
            else
            {
                QString places;
                while(query.next())
                {
                    places += ","+query.value("NrMiejsca").toString();
                }
                query.first();
                query.value("IdFilmu").toString();
                ui->reservationInfo->setText( query.value("IdFilmu").toString()+ query.value("IdSali").toString()+
                                              query.value("Godzina").toString()+ places );
            }
            db.close();
        }
    }
}

void UserWidget::OnLogoutButtonClick()
{
    emit SendWidgetChangeSignal();
}
