#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QMessageBox>

class FindDialog : public QDialog
{
    Q_OBJECT

    private:
        QPushButton *FindButton;
        QLineEdit *LineEdit;
        QString FindText;

    public:
        inline FindDialog(QWidget *parent = nullptr) noexcept;
        inline QString GetFindText() noexcept;

    public slots:
        inline void FindClicked() noexcept;
};  // FindDialog Interface

#endif // FINDDIALOG_H
