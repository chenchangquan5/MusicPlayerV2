#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QPoint>


namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

signals:
    void signalShowRegister(void);
    void signalLoginSuccess(void);

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);

private slots:
    void on_pb_enter_clicked();
    void on_pb_register_clicked();
    void on_pb_close_clicked();
    void on_pb_min_clicked();

    void on_pb_cancel_clicked();

private:
    Ui::Login *ui;

    void initWindow(void);

//    //密码框小键盘按钮
//    QPushButton *m_keyboardButton;

    QPoint m_widgetMove;
};

#endif // LOGIN_H
