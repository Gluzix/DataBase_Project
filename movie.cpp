#include "movie.h"
#include "ui_movie.h"

Movie::Movie(QWidget *parent, QString pathToImage) :
    QWidget(parent),
    ui(new Ui::Movie)
{
    ui->setupUi(this);
}

Movie::~Movie()
{
    delete ui;
}
