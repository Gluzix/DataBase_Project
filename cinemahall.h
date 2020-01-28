#ifndef CINEMAHALL_H
#define CINEMAHALL_H

#include <QDialog>
#include "seat.h"

namespace Ui {
class CinemaHall;
}

class CinemaHall : public QDialog
{
    Q_OBJECT

public:
    explicit CinemaHall(QDialog *parent = nullptr, uint row=0, uint col=0 );
    ~CinemaHall();

    static void execCinemaHall( uint row, uint col );

private:
    Ui::CinemaHall *ui;
    QVector<seat*> m_SeatsContainer;
};

#endif // CINEMAHALL_H
