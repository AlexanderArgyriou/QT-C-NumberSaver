#ifndef SHOWALLDIALOG_H
#define SHOWALLDIALOG_H

#include <QDialog>
#include <QTextEdit>
#include <QString>
#include <QGridLayout>

class ShowAllDialog : public QDialog
{
    private:
        QTextEdit *Field;
        QGridLayout *Lay;

    public:
        inline ShowAllDialog(QWidget *parent = nullptr) noexcept;
        inline void SetTextInDialog(const QString &TheString) noexcept;
        inline const QTextEdit *GetField() const noexcept;
};

#endif // SHOWALLDIALOG_H
