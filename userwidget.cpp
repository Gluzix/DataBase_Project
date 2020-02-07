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
            ui->reservationInfo->setText( "Id filmu: "+ query.value("IdFilmu").toString()+"\n"
                                          "Id Sali: "+query.value("IdSali").toString()+"\n"
                                          "Godzina: "+query.value("Godzina").toString()+"\n"
                                          "Miejsca: "+ places );
        }
        db.close();
    }
}

void UserWidget::OnLogoutButtonClick()
{
    emit SendWidgetChangeSignal();
}
