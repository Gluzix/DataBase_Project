#include "movie.h"
#include "ui_movie.h"

Movie::Movie( QWidget *parent, QString desc, QString pathToImage ) :
    QWidget(parent),
    ui(new Ui::Movie)
{
    ui->setupUi(this);
    ui->image->setStyleSheet(pathToImage);
    ui->description->setText(desc);
}

Movie::~Movie()
{
    delete ui;
}

void Movie::on_pushButton_clicked()
{
    emit SendButtonSignal();
}
