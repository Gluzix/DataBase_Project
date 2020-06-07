#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QPushButton>
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


private slots:
    void OnHideButtonClick();
    void OnShowButtonClick();

private:
    Ui::MainWindow  *ui;
    LoginWidget     *m_pLoginWidget;
    UserWidget      *m_pUserWidget;
    QPushButton     *m_pOpenButton;

    bool m_bIfLogged;

    void SetMovies();
    void AddNewWidget(QString info, QString path, int id);
    QVector<Movie*> m_MovieContainer;
};

#endif // MAINWINDOW_H
