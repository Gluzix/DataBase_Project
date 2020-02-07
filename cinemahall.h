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

    static QVector<uint> execCinemaHall( uint row, uint col, QVector<uint>&cont);

private slots:
    void OnSubmitButtonClick();

private:
    Ui::CinemaHall *ui;
    QVector<seat*> m_SeatsContainer;

    void SetAlreadyChecked( QVector<uint>&cont );
};

#endif // CINEMAHALL_H
