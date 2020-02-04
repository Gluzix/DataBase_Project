#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QDialog>

namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterWindow(QDialog *parent = nullptr);
    ~RegisterWindow();

    static void ExecRegisterWindow();

private slots:
    void ProcessRegister();
    void CloseWindow();

private:
    Ui::RegisterWindow *ui;
};

#endif // REGISTERWINDOW_H
