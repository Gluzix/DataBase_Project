#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "loginwidget.h"
#include "userwidget.h"
#include "movie.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void BookSeats( int id );
    void ChangeToUserWidget();
    void ChangeToLoginWidget();

private:
    Ui::MainWindow  *ui;
    LoginWidget     *loginWidget;
    UserWidget      *userWidget;

    bool bIfLogged;

    void setMovies();
    void AddNewWidget(QString info, QString path, int id);
    QVector<Movie*> movieContainer;
};

#endif // MAINWINDOW_H
