#include "registerwindow.h"
#include "ui_registerwindow.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QDebug>

RegisterWindow::RegisterWindow(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
    connect(ui->registerButton, SIGNAL(clicked()), this, SLOT(ProcessRegister()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(CloseWindow()));
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
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("projekt");
    db.setUserName("root");
    db.setPassword("");
    if(db.open())
    {
        qDebug()<<"You have connected with database!";
    }
    close();
}

void RegisterWindow::CloseWindow()
{
    close();
}
