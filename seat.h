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
    explicit seat(QWidget *parent = nullptr);
    ~seat();

private:
    Ui::seat *ui;
};

#endif // SEAT_H
