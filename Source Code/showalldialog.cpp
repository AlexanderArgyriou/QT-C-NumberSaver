#include "showalldialog.h"

inline ShowAllDialog::ShowAllDialog(QWidget *parent) noexcept
    : QDialog(parent)
{
    Field = new QTextEdit;
    this->setGeometry(50, 50, 500, 500);
    this->setWindowTitle("Numbers in Memory");
    Field->setReadOnly(true);
    Lay = new QGridLayout;
    Lay->addWidget(Field);
    setLayout(Lay);
}   // Constructor

inline void ShowAllDialog::SetTextInDialog(const QString &TheString) noexcept
{
    Field->setText(TheString);
}   // SetTextInDialog

inline const QTextEdit *ShowAllDialog::GetField() const noexcept { return Field;  }
