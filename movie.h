#ifndef MOVIE_H
#define MOVIE_H

#include <QWidget>

namespace Ui {
class Movie;
}

class Movie : public QWidget
{
    Q_OBJECT

public:
    explicit Movie(QWidget *parent = nullptr, QString desc=QString(), QString pathToImage=QString() );
    ~Movie();

signals:
    void SendButtonSignal();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Movie *ui;
};

#endif // MOVIE_H
