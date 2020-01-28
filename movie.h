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
    explicit Movie(QWidget *parent = nullptr, QString pathToImage=QString() );
    ~Movie();

private:
    Ui::Movie *ui;
};

#endif // MOVIE_H
