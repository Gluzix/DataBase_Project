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
    explicit seat(QWidget *parent = nullptr, unsigned int id = 0);
    ~seat();

private slots:
    void OnStateChanged(int state);

private:
    Ui::seat *ui;
    unsigned int m_ID;
};

#endif // SEAT_H
