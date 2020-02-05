#include "registerwindow.h"
#include "ui_registerwindow.h"
#include <QtSql>
#include <QSqlQuery>
#include <QDebug>
#include <QRegExpValidator>

RegisterWindow::RegisterWindow(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
    connect(ui->registerButton, SIGNAL(clicked()), this, SLOT(ProcessRegister()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(CloseWindow()));

    /*QRegExp rx("");
    rx.setPattern("");

    ui->firstNameEdit->setValidator( new QRegExpValidator(rx, this) );
    ui->secondNameEdit->setValidator( new QRegExpValidator(rx, this) );
    ui->loginEdit->setValidator( new QRegExpValidator(rx, this) );
    ui->pwdEdit->setValidator( new QRegExpValidator(rx, this) );
    ui->pwdRepeatEdit->setValidator( new QRegExpValidator(rx, this) );
    ui->emailEdit->setValidator( new QRegExpValidator(rx, this) );*/
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::ExecRegisterWindow()
{
    RegisterWindow window(nullptr);
    window.exec();
}

void RegisterWindow::ProcessRegister()
{
    bool ifNothingIsEmpty = true;

    ui->firstNameEdit->setStyleSheet("QLineEdit{font-size:14px;border-radius:6px;background-color:rgb(110,110,110);padding-top:6px;padding-bottom:6px;}");
    ui->secondNameEdit->setStyleSheet("QLineEdit{font-size:14px;border-radius:6px;background-color:rgb(110,110,110);padding-top:6px;padding-bottom:6px;}");
    ui->loginEdit->setStyleSheet("QLineEdit{font-size:14px;border-radius:6px;background-color:rgb(110,110,110);padding-top:6px;padding-bottom:6px;}");
    ui->pwdEdit->setStyleSheet("QLineEdit{font-size:14px;border-radius:6px;background-color:rgb(110,110,110);padding-top:6px;padding-bottom:6px;}");
    ui->pwdRepeatEdit->setStyleSheet("QLineEdit{font-size:14px;border-radius:6px;background-color:rgb(110,110,110);padding-top:6px;padding-bottom:6px;}");
    ui->emailEdit->setStyleSheet("QLineEdit{font-size:14px;border-radius:6px;background-color:rgb(110,110,110);padding-top:6px;padding-bottom:6px;}");

    if(ui->firstNameEdit->text().isEmpty())
    {
        ui->firstNameEdit->setStyleSheet("QLineEdit{font-size:14px;border-radius:6px;background-color:rgb(180,0,0);padding-top:6px;padding-bottom:6px;}");
        ifNothingIsEmpty = false;
    }
    if( ui->secondNameEdit->text().isEmpty())
    {
        ui->secondNameEdit->setStyleSheet("QLineEdit{font-size:14px;border-radius:6px;background-color:rgb(180,0,0);padding-top:6px;padding-bottom:6px;}");
        ifNothingIsEmpty = false;
    }
    if( ui->loginEdit->text().isEmpty())
    {
        ui->loginEdit->setStyleSheet("QLineEdit{font-size:14px;border-radius:6px;background-color:rgb(180,0,0);padding-top:6px;padding-bottom:6px;}");
        ifNothingIsEmpty = false;
    }
    if( ui->pwdEdit->text().isEmpty())
    {
        ui->pwdEdit->setStyleSheet("QLineEdit{font-size:14px;border-radius:6px;background-color:rgb(180,0,0);padding-top:6px;padding-bottom:6px;}");
        ifNothingIsEmpty = false;
    }
    if( ui->pwdRepeatEdit->text().isEmpty())
    {
        ui->pwdRepeatEdit->setStyleSheet("QLineEdit{font-size:14px;border-radius:6px;background-color:rgb(180,0,0);padding-top:6px;padding-bottom:6px;}");
        ifNothingIsEmpty = false;
    }
    if( ui->emailEdit->text().isEmpty())
    {
        ui->emailEdit->setStyleSheet("QLineEdit{font-size:14px;border-radius:6px;background-color:rgb(180,0,0);padding-top:6px;padding-bottom:6px;}");
        ifNothingIsEmpty = false;
    }

    if( ui->pwdEdit->text()!= ui->pwdRepeatEdit->text() && ifNothingIsEmpty )
    {
        ifNothingIsEmpty = false;
    }

    if( ifNothingIsEmpty )
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("C:/Users/Kamil/Desktop/projekt.db");
        if(db.open())
        {
            QSqlQuery query;
            query.exec("SELECT COUNT(*) FROM Uzytkownicy");
            if( query.isSelect() )
            {
                query.first();
                int latestID = query.value(0).toInt();

                //query.exec("INSERT INTO Uzytkownicy VALUES (1, 'Kamil', 'Ciesielski', 'kamil5640', 'haslo123', 'kamil.ciesielski@xd.pl', 0 );");



                query.exec("INSERT INTO Uzytkownicy VALUES("+QString::number(latestID)+", '"+ui->firstNameEdit->text()+"','"+
                     ui->secondNameEdit->text()+"','"+ui->loginEdit->text()+"','"+ui->pwdEdit->text()+"','"+ui->emailEdit->text()+
                           "',"+QString::number(0));

                QSqlError err = query.lastError();
                qDebug()<< err.text();

            }
            else
            {
                //ERROR
            }
            db.close();
        }
        close();
    }
}

void RegisterWindow::CloseWindow()
{
    close();
}
