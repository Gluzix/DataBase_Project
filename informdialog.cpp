#include "informdialog.h"
#include "ui_informdialog.h"

InformDialog::InformDialog(QDialog *parent, QString header, QString content) :
    QDialog(parent),
    ui(new Ui::InformDialog)
{
    ui->setupUi(this);
    ui->headerLabel->setText(header);
    ui->contentLabel->setText(content);
    connect(ui->confirmButton, SIGNAL(clicked()), this, SLOT(OnConfirmButtonClick()));
}

InformDialog::~InformDialog()
{
    delete ui;
}

void InformDialog::ExecInformDialog(QString h, QString c)
{
    InformDialog dialog(nullptr, h, c);
    dialog.exec();
}

void InformDialog::OnConfirmButtonClick()
{
    close();
}
