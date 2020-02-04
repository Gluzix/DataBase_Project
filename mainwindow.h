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

private slots:
    void OnRegisterButtonClick();

private:
    Ui::MainWindow  *ui;

    void setMovies();
    void AddNewWidget(QString info, QString path);
};

#endif // MAINWINDOW_H
