#include "userwidget.h"
#include "ui_userwidget.h"

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

void UserWidget::SetName(QString name)
{
    ui->nameLabel->setText("Hello "+name+"!");
}

void UserWidget::OnLogoutButtonClick()
{
    emit SendWidgetChangeSignal();
}
