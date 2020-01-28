#include "movie.h"
#include "ui_movie.h"

Movie::Movie( QWidget *parent, QString desc, QString pathToImage, QVector<QString> dates, QVector<QString> hours ) :
    QWidget(parent),
    ui(new Ui::Movie)
{
    ui->setupUi(this);
    ui->image->setStyleSheet(pathToImage);
    ui->description->setText(desc);

    QVector<QString>::iterator iterator;
    for( iterator = dates.begin(); iterator
         < dates.end(); iterator++)
    {
        ui->dateBox->addItem( (*iterator) );
    }

    for( iterator = hours.begin(); iterator
         < hours.end(); iterator++)
    {
        ui->hourBox->addItem( (*iterator) );
    }
}

Movie::~Movie()
{
    delete ui;
}

void Movie::on_pushButton_clicked()
{
    emit SendButtonSignal();
}

