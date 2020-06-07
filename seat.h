#ifndef SEAT_H
#define SEAT_H

#include <QWidget>

namespace Ui {
class seat;
}

class seat : public QWidget
{
    Q_OBJECT

public:
    explicit seat(QWidget *parent = nullptr, int id = 0);
    ~seat();
    void StateChange(bool state);
    bool GetIfBooked();

private slots:
    void OnStateChanged(int state);

private:
    Ui::seat    *ui;
    int         m_ID;
    bool        m_bIfBooked;
};

#endif // SEAT_H
