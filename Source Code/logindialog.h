#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QString>
#include <QLabel>

const QString PassWord = "8LDB";

class LoginDialog : public QDialog
{
    Q_OBJECT

    private:
        QGridLayout *Lay;
        QLabel *PassLabel, *PassMsg;
        QPushButton *Login;
        QLineEdit *Line;
        QString Pass;

    public:
        inline LoginDialog(QWidget *parent = nullptr) noexcept
            : QDialog(parent)
        {
            this->setWindowTitle("Connected...");
            this->setWindowIcon(QIcon("emblem.jpg"));
            Lay = new QGridLayout;
            Login = new QPushButton("Login");
            Login->setStyleSheet("QPushButton { color: #340; border: 1px solid #655; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
            Line = new QLineEdit;
            Line->setEchoMode(QLineEdit::Password);
            PassLabel = new QLabel("Password:");
            PassMsg = new QLabel;

            Lay->addWidget(PassLabel,0,0);
            Lay->addWidget(Line,0,1);
            Lay->addWidget(Login,1,0);
            Lay->addWidget(PassMsg,1,1);

            setLayout(Lay);

            connect ( Login, &QPushButton::pressed, this, &LoginDialog::LoginPressed );
        }   // Constructor
        inline const QString GetPass() { return Pass; }

    public slots:

        inline void LoginPressed() noexcept
        {
            Pass = Line->text();
            if (Pass == PassWord)
                this->accept();
            else
                PassMsg->setText("Wrong PassWord! Try Again.");
            //qDebug(Pass.toStdString().c_str());
        }
};

#endif // LOGINDIALOG_H
