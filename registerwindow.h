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
    void OnLineEditsTextChanged(const QString &);
    void OnPwdBoxStateChanged(int);

private:
    Ui::RegisterWindow *ui;

    void ValidateEmail( bool &ifNothingIsEmpty );
};

#endif // REGISTERWINDOW_H
