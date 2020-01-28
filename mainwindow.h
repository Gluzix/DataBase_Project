#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

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
    void BookSeats();

private:
    Ui::MainWindow  *ui;


    void setMovies();
    void AddNewWidget(QString info, QString path);
};

#endif // MAINWINDOW_H
