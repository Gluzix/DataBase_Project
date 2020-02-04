#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "movie.h"
#include "cinemahall.h"
#include "registerwindow.h"
#include <QFontDatabase>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMovies();
    QFontDatabase::addApplicationFont(":/Resources/fonts/Bangers/Bangers-Regular.ttf");
    QFont Bangers("Bangers");
    QApplication::setFont(Bangers);
    connect(ui->registerButton, SIGNAL(clicked()), this, SLOT(OnRegisterButtonClick()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::BookSeats()
{
    CinemaHall::execCinemaHall(5,10);
}

void MainWindow::OnRegisterButtonClick()
{
    RegisterWindow::ExecRegisterWindow();
}

void MainWindow::setMovies()
{
    ui->widget->setLayout(new QGridLayout(this));
    AddNewWidget("image: url(:/Resources/1.jpg);", "Po 25 latach odsiadki Franz Maurer wychodzi z więzienia i wkracza w nową Polskę, w której nic nie jest takie, jak zapamiętał. Kto i co czeka na człowieka, który przez ostatnie ćwierć wieku… nie robił nic? Jak odnajdzie się w świecie, w którym dawne zasady i lojalność przestały obowiązywać? Tego dowiemy się, gdy los ponownie połączy Franza i „Nowego”. Ich spotkanie zmieni wszystko.");
    AddNewWidget("image: url(:/Resources/2.jpg);","Wielkie wojenne widowisko na miarę „Dunkierki” i „Szeregowca Ryana”, które przybliża nam dramatyczne losy żołnierzy na froncie jednej z najbardziej tragicznych wojen w dziejach świata.");
    AddNewWidget("image: url(:/Resources/3.jpg);","Robert Downey Jr. wciela się w jedną z najsłynniejszych postaci światowej literatury w pełnej przygód nowej filmowej wersji opowieści o człowieku, który potrafi rozmawiać ze zwierzętami. Oto doktor Dolittle.");
    AddNewWidget("image: url(:/Resources/4.jpg);","Druga część niezwykle popularnej animowanej baśni Disneya. Elsa i Anna powracają do kin, a wraz z nimi przesympatyczny bałwanek Olaf.");
}

void MainWindow::AddNewWidget( QString path, QString info )
{
    Movie *movie = new Movie( this, info, path);
    connect(movie, SIGNAL( SendButtonSignal() ), this, SLOT( BookSeats() ));
    ui->widget->layout()->addWidget( movie );
}
