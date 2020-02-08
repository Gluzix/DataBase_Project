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
    explicit CinemaHall(QDialog *parent = nullptr, int row=0, int col=0 );
    ~CinemaHall();

    static QVector<int> execCinemaHall( int row, int col, QVector<int>&cont);
    bool GetIfConfirmed();

private slots:
    void OnSubmitButtonClick();

private:
    Ui::CinemaHall *ui;
    QVector<seat*> m_SeatsContainer;
    bool m_IfConfirmed;

    void SetAlreadyChecked( QVector<int>&cont );
};

#endif // CINEMAHALL_H
