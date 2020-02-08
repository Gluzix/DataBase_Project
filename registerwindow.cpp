#include "registerwindow.h"
#include "ui_registerwindow.h"
#include "informdialog.h"
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

    connect(ui->firstNameEdit, SIGNAL(textChanged(const QString &)), this, SLOT(OnLineEditsTextChanged(const QString &)));
    connect(ui->secondNameEdit, SIGNAL(textChanged(const QString &)), this, SLOT(OnLineEditsTextChanged(const QString &)));
    connect(ui->loginEdit, SIGNAL(textChanged(const QString &)), this, SLOT(OnLineEditsTextChanged(const QString &)));
    connect(ui->pwdEdit, SIGNAL(textChanged(const QString &)), this, SLOT(OnLineEditsTextChanged(const QString &)));
    connect(ui->pwdRepeatEdit, SIGNAL(textChanged(const QString &)), this, SLOT(OnLineEditsTextChanged(const QString &)));
    connect(ui->emailEdit, SIGNAL(textChanged(const QString &)), this, SLOT(OnLineEditsTextChanged(const QString &)));

    connect(ui->pwdBox, SIGNAL(stateChanged(int)), this, SLOT(OnPwdBoxStateChanged(int)));

    ui->firstNameEdit->setValidator( new QRegExpValidator( QRegExp("[A-Za-z]{30}"), this) );
    ui->secondNameEdit->setValidator( new QRegExpValidator( QRegExp("[A-Za-z]{30}"), this) );
    ui->loginEdit->setValidator( new QRegExpValidator( QRegExp("[A-Za-z0-9]{30}"), this) );
    ui->pwdEdit->setValidator( new QRegExpValidator( QRegExp("[A-Za-z0-9!@#$%^&*()<> ]{35}"), this) );
    ui->pwdRepeatEdit->setValidator( new QRegExpValidator( QRegExp("[A-Za-z0-9!@#$%^&*()<> ]{35}"), this) );
    ui->emailEdit->setValidator( new QRegExpValidator( QRegExp("[A-Za-z0-9@.]{30}"), this) );
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
    bool ifNoErrorOccured = true;

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
    if( ui->loginEdit->text().isEmpty() || ui->loginEdit->text().length()<6 )
    {
        ui->loginEdit->setStyleSheet("QLineEdit{font-size:14px;border-radius:6px;background-color:rgb(180,0,0);padding-top:6px;padding-bottom:6px;}");
        ifNothingIsEmpty = false;
    }
    if( ui->pwdEdit->text().isEmpty() || ui->loginEdit->text().length()<6 )
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

    ValidateEmail(ifNothingIsEmpty);



    if( ui->pwdEdit->text()!= ui->pwdRepeatEdit->text() && ifNothingIsEmpty )
    {
        ifNothingIsEmpty = false;
        InformDialog::ExecInformDialog("Error", "Password are incorrect");
    }

    if( ifNothingIsEmpty )
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("./../DataBaseProject/projekt.db");
        if(db.open())
        {
            QSqlQuery query;
            QSqlError err;
            bool bIfAlreadyExist = false;

            query.exec("SELECT Login FROM Uzytkownicy WHERE Login='"+ui->loginEdit->text()+"';");
            query.first();
            if( !query.isNull(0) )
            {
                bIfAlreadyExist = true;
            }

            query.exec("SELECT Email FROM Uzytkownicy WHERE Email='"+ui->emailEdit->text()+"';");
            query.first();
            if( !query.isNull(0) )
            {
                bIfAlreadyExist = true;
            }

            if(!bIfAlreadyExist)
            {
                query.exec("SELECT COUNT(*) FROM Uzytkownicy");
                if( query.isSelect() )
                {
                    query.first();
                    int latestID = query.value(0).toInt();

                    if( !query.exec("INSERT INTO Uzytkownicy VALUES("+QString::number(latestID)+",'"+ui->firstNameEdit->text()+"','"+
                         ui->secondNameEdit->text()+"','"+ui->loginEdit->text()+"','"+ui->pwdEdit->text()+"','"+ui->emailEdit->text()+
                               "')") )
                    {
                        err = query.lastError();
                        InformDialog::ExecInformDialog("Error", err.text());
                        ifNoErrorOccured = false;
                    }
                }
                else
                {
                    err = query.lastError();
                    InformDialog::ExecInformDialog("Error", err.text());
                    ifNoErrorOccured = false;
                }
            }
            else
            {
                InformDialog::ExecInformDialog("Error", "login lub mail jest juz zajety!");
                ifNoErrorOccured = false;
            }
            db.close();
        }
        else
        {
            InformDialog::ExecInformDialog("Error", "Nie mozna polaczyc sie z baza danych!");
            ifNoErrorOccured = false;
        }

        if( ifNoErrorOccured )
        {
            close();
        }
    }
}

void RegisterWindow::CloseWindow()
{
    close();
}

void RegisterWindow::OnLineEditsTextChanged(const QString &str)
{
    QObject *obj = this->sender();
    QLineEdit *wsk = qobject_cast< QLineEdit* >(obj);
    wsk->setStyleSheet("QLineEdit{font-size:14px;border-radius:6px;background-color:rgb(110,110,110);padding-top:6px;padding-bottom:6px;}");
}

void RegisterWindow::OnPwdBoxStateChanged(int state)
{
    if(state == 0)
    {
        ui->pwdEdit->setEchoMode(QLineEdit::Password);
        ui->pwdRepeatEdit->setEchoMode(QLineEdit::Password);
    }
    else if( state == 2)
    {
        ui->pwdEdit->setEchoMode(QLineEdit::Normal);
        ui->pwdRepeatEdit->setEchoMode(QLineEdit::Normal);
    }
}

void RegisterWindow::ValidateEmail( bool &ifNothingIsEmpty )
{
    QString str = ui->emailEdit->text();
    bool ifIsMonk = false;
    bool ifIsEnough = false;
    bool ifIsDot = false;
    short x = 0;
    short y = 0;
    for( int i=0; i<str.length(); i++ )
    {
        if( str[i]=='@' )
        {
            ifIsMonk = true;
        }

        if( ifIsMonk )
        {
            if( x>2 && str[i]=='.' && x<6 )
            {
                ifIsDot = true;
            }
            x++;

            if( ifIsDot )
            {
                if( y>1 && y<4 )
                {
                    ifIsEnough = true;
                }
                else
                {
                    ifIsEnough = false;
                }
                y++;
            }
        }
    }

    if( !ifIsMonk || !ifIsEnough || !ifIsDot )
    {
        ui->emailEdit->setStyleSheet("QLineEdit{font-size:14px;border-radius:6px;background-color:rgb(180,0,0);padding-top:6px;padding-bottom:6px;}");
        ifNothingIsEmpty = false;
    }
}
