#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "informdialog.h"
#include "registerwindow.h"
#include <QRegExpValidator>
#include <QtSql>
#include <QSqlQuery>

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    connect(ui->registerButton, SIGNAL(clicked()), this, SLOT(OnRegisterButtonClick()));
    connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(OnLoginButtonClick()));
    connect(ui->checkBox, SIGNAL(stateChanged(int)), this, SLOT(OnCheckBoxStateChanged(int)));

    ui->loginEdit->setValidator( new QRegExpValidator( QRegExp("[A-Za-z0-9]{30}"), this) );
    ui->pwdEdit->setValidator( new QRegExpValidator( QRegExp("[A-Za-z0-9!@#$%^&*()<> ]{35}"), this) );
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::OnLoginButtonClick()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/Kamil/Desktop/projekt.db");
    QSqlQuery query;

    if(db.open())
    {
        query.exec("SELECT Login, Imie FROM Uzytkownicy WHERE Login='"+ui->loginEdit->text()+"' AND Haslo='"+ui->pwdEdit->text()+"';");
        query.first();
        if( query.isNull(0) )
        {
            InformDialog::ExecInformDialog("Error", "Wrong Credentials!");
        }
        else
        {
            QString name = query.value("Imie").toString();
            emit SendWidgetChangeSignal(name);
        }
        db.close();
    }
}

void LoginWidget::OnCheckBoxStateChanged( int state )
{
    if(state == 0)
    {
        ui->pwdEdit->setEchoMode(QLineEdit::Password);
    }
    else if( state == 2)
    {
        ui->pwdEdit->setEchoMode(QLineEdit::Normal);
    }
}

void LoginWidget::OnRegisterButtonClick()
{
    RegisterWindow::ExecRegisterWindow();
}
