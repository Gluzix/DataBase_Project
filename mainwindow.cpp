#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "movie.h"
#include "cinemahall.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMovies();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setMovies()
{
    ui->widget->setLayout(new QGridLayout(this));
    ui->widget->layout()->addWidget(new Movie( this, "url(:/Resources/movie_1.jfif)"));
}
