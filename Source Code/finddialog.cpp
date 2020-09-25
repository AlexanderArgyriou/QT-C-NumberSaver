#include "finddialog.h"

inline FindDialog::FindDialog(QWidget *parent) noexcept
    : QDialog(parent)
{
    QLabel *FindLabel = new QLabel(tr("Enter the Number:"));
    LineEdit = new QLineEdit;

    FindButton = new QPushButton(tr("&Find"));
    FindText = "";

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(FindLabel);
    layout->addWidget(LineEdit);
    layout->addWidget(FindButton);

    setLayout(layout);
    setWindowTitle(tr("Find a Number"));
    connect(FindButton, &QPushButton::clicked,
            this, &FindDialog::FindClicked);
    connect(FindButton, &QPushButton::clicked,
            this, &FindDialog::accept);
}   // Constructor

inline void FindDialog::FindClicked() noexcept
{
    QString text = LineEdit->text();

    if ( text.isEmpty() )
    {
        QMessageBox::information(this, tr("Empty Field"),
            tr("Please enter a Number."));
        return;
    }   // if
    else
    {
        FindText = text;
        LineEdit->clear();
        hide();
    }   // else
}   //  FindClicked

inline QString FindDialog::GetFindText() noexcept
{
    return FindText;
}   //    GetFindText()
