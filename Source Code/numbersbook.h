#ifndef NUMBERSBOOK_H
#define NUMBERSBOOK_H

#include "infos.h"
#include "infos.cpp"
#include "finddialog.h"
#include "finddialog.cpp"
#include "showalldialog.h"
#include "showalldialog.cpp"
#include "logindialog.h"
#include "logindialog.cpp"
#include <QString>
#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QMap>
#include <QFileDialog>
#include <QPrinter>
#include <QPainter>
#include <QCloseEvent>

enum Mode { NavigationMode, AddingMode, EditingMode };

class NumbersBook : public QWidget
{
    Q_OBJECT

    //  private data members
    private:
        QTextEdit *TextFields[6];
        QPushButton *AddButton, *SubmitButton, *CancelButton,
        *NextButton, *PreviousButton, *EditButton, *RemoveButton,
        *FindButton, *LoadButton, *SaveButton, *ShowButton, *PrintButton;
        QMap<QString, Infos> Server;
        QString OldNumber;
        Infos OldInfos;
        Mode CurrentMode;
        FindDialog *Dialog;
        ShowAllDialog *SDialog;
        LoginDialog *Log;

    //  protected methods
    protected:
        void closeEvent(QCloseEvent *event) override;

    //  public methods
    public:
        inline explicit NumbersBook(QWidget *parent = nullptr) noexcept;    // Constructor
        inline void UpdateInterface(const Mode &newMode) noexcept;  // Update Interface
        inline void FirstLoad() noexcept;	// First Load

    //  button connections
    public slots:
        inline void AddNumber() noexcept;   // AddNumber
        inline void SubmitNumber() noexcept;    // SubitNumber
        inline void CancelNumber() noexcept;    // CancelNumber
        inline void NextNumber() noexcept;  // NextNumber
        inline void PreviousNumber() noexcept;    // PreviousNumber
        inline void EditContact() noexcept; // EditContatct
        inline void RemoveContact() noexcept;  // RemoveContact
        inline void FindNumber() noexcept;  // FindNumber
        inline void SaveToFile() noexcept;  // SaveToFile
        inline void LoadFromFile() noexcept;    // LoadFromFile
        inline void ShowAll() noexcept; // ShowAll
        inline void PrintNumbers() noexcept; // PrintNumbers
};

#endif // NUMBERSBOOK_H
