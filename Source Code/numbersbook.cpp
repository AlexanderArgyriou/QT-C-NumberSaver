#include "numbersbook.h"
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QTextStream>
#include <QTextCodec>
#include <iostream>
#include <Windows.h>
#include <QIcon>

inline NumbersBook::NumbersBook(QWidget *parent) noexcept
    : QWidget(parent)
{
    //Log->close();
    //this->setFixedSize(1'000, 500);
    this->setWindowIcon(QIcon("emblem.jpg"));
    this->setWindowTitle("NumberSaver Running...");
    this->setGeometry(50, 50, 1'250, 600);
    QLabel *Author = new QLabel("Creator : Alexander Argyriou (C)");
    QLabel *Users = new QLabel("Users : 8ος Λόχος Διαβιβάσεων");

    // Create Label objects
    QLabel *TheLabels[6];
    TheLabels[0] = new QLabel("Αριθμός Τηλ.");
    TheLabels[1] = new QLabel("Ανταποκριτής");
    TheLabels[2] = new QLabel("Κάρτα Τηλ. Κέντρου");
    TheLabels[3] = new QLabel("Κεντρικός Κατανεμητής");
    TheLabels[4] = new QLabel("Εξωτερικός Κατανεμητής");
    TheLabels[5] = new QLabel("Σχόλια");

    // labels font
    QFont fL("italic", 10, QFont::Bold);

    for (size_t i = 0; i < 6; ++i)
    {
        TheLabels[i]->setFont(fL);
        TheLabels[i]->setFrameStyle(QFrame::Box | QFrame::Raised );
        //TheLabels[i]->setStyleSheet( "QLabel { color : ; }" );
    }

    // Background image
    QLabel *myimage = new QLabel;
    QPixmap pix("hermes.jpg");
    pix = pix.scaled(150,100);
    myimage->setPixmap(pix);

    // TextFields Font
    QFont fT("Times New Roman", 14, QFont::Bold);

    // Create Text Objects
    for (size_t i = 0; i < 6; ++i)
    {
        TextFields[i] = new QTextEdit;
        TextFields[i]->setReadOnly(true);
        TextFields[i]->setFont(fT);
        TextFields[i]->setFrameStyle(QFrame::Box | QFrame::Raised);
        TextFields[i]->setLineWidth(2);
        TextFields[i]->setMidLineWidth(1);
    }   // for

    // Create and set the basic layout
    QGridLayout *MainLayout = new QGridLayout;
    MainLayout->addWidget(TheLabels[0], 0, 0, Qt::AlignHCenter);
    MainLayout->addWidget(TheLabels[1], 0, 1, Qt::AlignHCenter);
    MainLayout->addWidget(TheLabels[2], 0, 2, Qt::AlignHCenter);
    MainLayout->addWidget(TheLabels[3], 0, 3, Qt::AlignHCenter);
    MainLayout->addWidget(TheLabels[4], 0, 4, Qt::AlignHCenter);
    MainLayout->addWidget(TheLabels[5], 0, 5, Qt::AlignHCenter);

    MainLayout->addWidget(TextFields[0], 1, 0);
    MainLayout->addWidget(TextFields[1], 1, 1);
    MainLayout->addWidget(TextFields[2], 1, 2);
    MainLayout->addWidget(TextFields[3], 1, 3);
    MainLayout->addWidget(TextFields[4], 1, 4);
    MainLayout->addWidget(TextFields[5], 1, 5);

    QVBoxLayout *AuthorUsers = new QVBoxLayout;
    AuthorUsers->addWidget(Author);
    AuthorUsers->addWidget(Users);

    //MainLayout->addWidget(Author, 2, 0);
    //MainLayout->addWidget(Users, 3, 0);
    MainLayout->addLayout(AuthorUsers, 2, 0, Qt::AlignBottom);

    // Create Button Objects
    AddButton = new QPushButton("Add");
    AddButton->show();
    AddButton->setStyleSheet("QPushButton { color: #333; border: 2px solid #555; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
    SubmitButton = new QPushButton("Submit");
    SubmitButton->setStyleSheet("QPushButton { color: #333; border: 2px solid #555; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
    SubmitButton->hide();
    CancelButton = new QPushButton("Cancel");
    CancelButton->setStyleSheet("QPushButton { color: #333; border: 2px solid #555; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
    CancelButton->hide();
    NextButton = new QPushButton(tr("&Next"));
    NextButton->setEnabled(false);
    NextButton->setStyleSheet("QPushButton { color: #333; border: 2px solid #555; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
    PreviousButton = new QPushButton(tr("&Previous"));
    PreviousButton->setEnabled(false);
    PreviousButton->setStyleSheet("QPushButton { color: #333; border: 2px solid #555; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
    EditButton = new QPushButton(tr("&Edit"));
    EditButton->setStyleSheet("QPushButton { color: #333; border: 2px solid #555; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
    EditButton->setEnabled(false);
    RemoveButton = new QPushButton(tr("&Remove"));
    RemoveButton->setStyleSheet("QPushButton { color: red; border: 2px solid #555; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
    RemoveButton->setEnabled(false);
    FindButton = new QPushButton(tr("&Find"));
    FindButton->setStyleSheet("QPushButton { color: #333; border: 2px solid #555; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
    FindButton->setEnabled(false);
    LoadButton = new QPushButton(tr("&Load"));
    LoadButton->setStyleSheet("QPushButton { color: #333; border: 2px solid #555; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
    SaveButton = new QPushButton(tr("&Save"));
    SaveButton->setStyleSheet("QPushButton { color: #333; border: 2px solid #555; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
    LoadButton->setToolTip(tr("Load Numbers from a file"));
    SaveButton->setToolTip(tr("Save Numbers to a file"));
    ShowButton = new QPushButton(tr("&Show"));
    ShowButton->setStyleSheet("QPushButton { color: #333; border: 2px solid #555; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
    ShowButton->setEnabled(false);
    PrintButton = new QPushButton(tr("&Print"));
    PrintButton->setStyleSheet("QPushButton { color: #333; border: 2px solid #555; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
    PrintButton->setEnabled(false);

    // Connect Buttons With proper functions
    connect( AddButton, &QPushButton::clicked, this, &NumbersBook::AddNumber );
    connect( SubmitButton, &QPushButton::clicked, this, &NumbersBook::SubmitNumber );
    connect( CancelButton, &QPushButton::clicked, this, &NumbersBook::CancelNumber );
    connect( NextButton, &QPushButton::clicked, this, &NumbersBook::NextNumber );
    connect( PreviousButton, &QPushButton::clicked, this, &NumbersBook::PreviousNumber );
    connect( EditButton, &QPushButton::clicked, this, &NumbersBook::EditContact );
    connect( RemoveButton, &QPushButton::clicked, this, &NumbersBook::RemoveContact );
    connect( FindButton, &QPushButton::clicked, this, &NumbersBook::FindNumber );
    connect( LoadButton, &QPushButton::clicked, this, &NumbersBook::LoadFromFile );
    connect( SaveButton, &QPushButton::clicked, this, &NumbersBook::SaveToFile );
    connect( ShowButton, &QPushButton::clicked, this, &NumbersBook::ShowAll );
    connect( PrintButton, &QPushButton::clicked, this, &NumbersBook::PrintNumbers );

    // ButtonsLayouts
    QVBoxLayout *ButtonLayout1 = new QVBoxLayout;
    ButtonLayout1->addWidget(AddButton, Qt::AlignTop);
    ButtonLayout1->addWidget(SubmitButton);
    ButtonLayout1->addWidget(CancelButton);
    ButtonLayout1->addWidget(EditButton);
    ButtonLayout1->addWidget(RemoveButton);
    ButtonLayout1->addWidget(FindButton);
    ButtonLayout1->addWidget(LoadButton);
    ButtonLayout1->addWidget(SaveButton);
    ButtonLayout1->addWidget(ShowButton);
    ButtonLayout1->addWidget(PrintButton);
    //ButtonLayout1->addWidget(myimage);
    ButtonLayout1->addStretch();
    MainLayout->addLayout(ButtonLayout1, 1, 6);
    //MainLayout->addWidget(myimage, 2 , 6);

    QHBoxLayout *ButtonLayout2 = new QHBoxLayout;
    ButtonLayout2->addWidget(PreviousButton);
    ButtonLayout2->addWidget(NextButton);
    MainLayout->addLayout( ButtonLayout2, 2, 2, Qt::AlignTop );
    MainLayout->addWidget( myimage, 2, 6 );

    // Dialog Find and Show Creation
    Dialog = new FindDialog(this);
    SDialog = new ShowAllDialog(this);

    // Set Layout
    setLayout(MainLayout);
    this->FirstLoad();
}   // Constructor

inline void NumbersBook::AddNumber() noexcept
{
    UpdateInterface(AddingMode);
    // Disable navigation
    NextButton->setEnabled(false);
    PreviousButton->setEnabled(false);
    FindButton->setEnabled(false);
    LoadButton->setEnabled(false);
    SaveButton->setEnabled(false);
    ShowButton->setEnabled(false);
    PrintButton->setEnabled(false);
    LoadButton->setEnabled(false);
    SaveButton->setEnabled(false);

    AddButton->setStyleSheet("QPushButton { color:  #333; border: 1px solid #d7d6d5; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
    NextButton->setStyleSheet("QPushButton { color:  #333; border: 1px solid #d7d6d5; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
    PreviousButton->setStyleSheet("QPushButton { color:  #333; border: 1px solid #d7d6d5; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
    LoadButton->setStyleSheet("QPushButton { color:  #333; border: 1px solid #d7d6d5; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
    SaveButton->setStyleSheet("QPushButton { color:  #333; border: 1px solid #d7d6d5; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
    ShowButton->setStyleSheet("QPushButton { color:  #333; border: 1px solid #d7d6d5; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
    PrintButton->setStyleSheet("QPushButton { color:  #333; border: 1px solid #d7d6d5; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
    LoadButton->setStyleSheet("QPushButton { color:  #333; border: 1px solid #d7d6d5; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
    SaveButton->setStyleSheet("QPushButton { color:  #333; border: 1px solid #d7d6d5; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");

    // take the text from fields atm
    OldNumber = TextFields[0]->toPlainText();
    OldInfos.SetFeature1(TextFields[1]->toPlainText());
    OldInfos.SetFeature2(TextFields[2]->toPlainText());
    OldInfos.SetFeature3(TextFields[3]->toPlainText());
    OldInfos.SetFeature4(TextFields[4]->toPlainText());
    OldInfos.SetFeature5(TextFields[5]->toPlainText());

    // celar fields, make them writable
    for ( size_t i = 0; i < 6; ++i )
        TextFields[i]->clear(), TextFields[i]->setReadOnly(false);

    // focus on first field
    TextFields[0]->setFocus(Qt::OtherFocusReason);

    // disable a second add , and show submit and cancel
    AddButton->setEnabled(false);
    SubmitButton->show();
    CancelButton->show();
}   // AddNumber

inline void NumbersBook::SubmitNumber() noexcept
{
    if ( CurrentMode == AddingMode )
    {
        // check for empty field
        if ( TextFields[0]->toPlainText().isEmpty() ||
             TextFields[1]->toPlainText().isEmpty() ||
             TextFields[2]->toPlainText().isEmpty() ||
             TextFields[3]->toPlainText().isEmpty() ||
             TextFields[4]->toPlainText().isEmpty() ||
             TextFields[5]->toPlainText().isEmpty() )
        {
            QMessageBox::information(this, tr("Empty Field,"),
            tr("Please fill all the fields."));
            return;
        }   // if

        // check for duplicates
        if (!Server.contains(TextFields[0]->toPlainText()))
        {
            Server.insert( QString::fromUtf8( TextFields[0]->toPlainText().toUtf8() ),
                    Infos( QString::fromUtf8( TextFields[1]->toPlainText().toUtf8() ),
                           QString::fromUtf8( TextFields[2]->toPlainText().toUtf8() ),
                           QString::fromUtf8( TextFields[3]->toPlainText().toUtf8() ),
                           QString::fromUtf8( TextFields[4]->toPlainText().toUtf8() ),
                           QString::fromUtf8( TextFields[5]->toPlainText().toUtf8() ) ) );

            QMessageBox::information(this, tr("Add Successful"),
            tr("\"%1\" has been added to your Numbers book.").arg( TextFields[0]->toPlainText()) );

            // enable Nav depend on numbers
            NextButton->setEnabled( Server.size() > 0 );
            PreviousButton->setEnabled( Server.size() > 0 );
        }   // if
        else
        {
            QMessageBox::information(this, tr("Add Unsuccessful"),
            tr("Sorry, \"%1\" is already in your Numbers book.").arg(TextFields[0]->toPlainText()) );
            return;
        }   // else
    }   // if
    else if ( CurrentMode == EditingMode )
    {
        if ( OldNumber != TextFields[0]->toPlainText() )
        {
            if ( !Server.contains(TextFields[0]->toPlainText()) )
            {
                Server.remove(OldNumber);
                Server.insert(TextFields[0]->toPlainText(), OldInfos);
            }   // if
            else
            {
                QMessageBox::information(this, tr("Edit Unsuccessful"),
                 tr("Sorry, \"%1\" is already in your address book.").arg(TextFields[0]->toPlainText()));
            }
        }   // if

        if ( OldInfos.GetFeature1() != TextFields[1]->toPlainText() )
        {
                Server.find( TextFields[0]->toPlainText() ).value().SetFeature1(TextFields[1]->toPlainText());
        }   // if

        if (OldInfos.GetFeature2() != TextFields[2]->toPlainText())
        {
                Server.find( TextFields[0]->toPlainText() ).value().SetFeature2(TextFields[2]->toPlainText());
        }   // if

        if (OldInfos.GetFeature3() != TextFields[3]->toPlainText())
        {
                Server.find( TextFields[0]->toPlainText() ).value().SetFeature3(TextFields[3]->toPlainText());
        }   // if

        if (OldInfos.GetFeature4() != TextFields[4]->toPlainText())
        {
            Server.find(TextFields[0]->toPlainText()).value().SetFeature4(TextFields[4]->toPlainText());
        }   // if

        if (OldInfos.GetFeature5() != TextFields[5]->toPlainText())
        {
            Server.find(TextFields[0]->toPlainText()).value().SetFeature5(TextFields[5]->toPlainText());
        }   // if

        QMessageBox::information(this, "Edit ", "Edit Was Successful");
    }   // else if

    UpdateInterface(NavigationMode);

    // Reset AfterAdd
    if ( Server.isEmpty() )
    {
        for ( size_t i = 0; i < 6; ++i )
            TextFields[i]->clear();
    }   // if

    for ( size_t i = 0; i < 6; ++i )
        TextFields[i]->clear(), TextFields[i]->setReadOnly(true);

    AddButton->setEnabled(true);
    SubmitButton->hide();
    CancelButton->hide();
}   // SubmitNumber

inline void NumbersBook::CancelNumber() noexcept
{
    // enable Nav depend on numbers
    NextButton->setEnabled( Server.size() > 0 );
    PreviousButton->setEnabled( Server.size() > 0 );

    // reset fields with latest infos
    TextFields[0]->setText(OldNumber);
    TextFields[1]->setText(OldInfos.GetFeature1());
    TextFields[2]->setText(OldInfos.GetFeature2());
    TextFields[3]->setText(OldInfos.GetFeature3());
    TextFields[4]->setText(OldInfos.GetFeature4());
    TextFields[5]->setText(OldInfos.GetFeature5());

    // lock fields
    for ( size_t i = 0; i < 6; ++i )
       TextFields[i]->setReadOnly(true);

    AddButton->setEnabled(true);
    SubmitButton->hide();
    CancelButton->hide();

    UpdateInterface(NavigationMode);
}   // CancelNumber

inline void NumbersBook::NextNumber() noexcept
{
    QMap<QString, Infos>::iterator i = Server.find( TextFields[0]->toPlainText() );

    if (i != Server.end())
           ++i;

    if (i == Server.end())
        i = Server.begin();

     TextFields[0]->setText(i.key());
     TextFields[1]->setText(i.value().GetFeature1());
     TextFields[2]->setText(i.value().GetFeature2());
     TextFields[3]->setText(i.value().GetFeature3());
     TextFields[4]->setText(i.value().GetFeature4());
     TextFields[5]->setText(i.value().GetFeature5());
}   // NextNumber

inline void NumbersBook::PreviousNumber() noexcept
{
    QMap<QString, Infos>::iterator i = Server.find( TextFields[0]->toPlainText() );

    if (i == Server.end())
    {
        for ( size_t i = 0; i < 6; ++i )
            TextFields[i]->clear();
        return;
    }   // if

    if (i == Server.begin())
           i = Server.end();

    i--;

    TextFields[0]->setText(i.key());
    TextFields[1]->setText(i.value().GetFeature1());
    TextFields[2]->setText(i.value().GetFeature2());
    TextFields[3]->setText(i.value().GetFeature3());
    TextFields[4]->setText(i.value().GetFeature4());
    TextFields[5]->setText(i.value().GetFeature5());
}  // PreviousNumber

inline void NumbersBook::EditContact() noexcept
{
    OldNumber = TextFields[0]->toPlainText();
    OldInfos.SetFeature1(TextFields[1]->toPlainText());
    OldInfos.SetFeature2(TextFields[2]->toPlainText());
    OldInfos.SetFeature3(TextFields[3]->toPlainText());
    OldInfos.SetFeature4(TextFields[4]->toPlainText());
    OldInfos.SetFeature5(TextFields[5]->toPlainText());

    UpdateInterface(EditingMode);
}  // EditContatct

inline void NumbersBook::UpdateInterface(const Mode &newMode) noexcept
{
    CurrentMode = newMode;

    switch (CurrentMode)
    {
        case AddingMode:
        case EditingMode:
            for ( size_t i = 0; i < 6; ++i )
                TextFields[i]->setReadOnly(false);

            TextFields[0]->setFocus(Qt::OtherFocusReason);

            AddButton->setEnabled(false);
            EditButton->setEnabled(false);
            RemoveButton->setEnabled(false);
            FindButton->setEnabled(false);
            NextButton->setEnabled(false);
            PreviousButton->setEnabled(false);
            LoadButton->setEnabled(false);
            SaveButton->setEnabled(false);
            ShowButton->setEnabled(false);
            PrintButton->setEnabled(false);

            AddButton->setStyleSheet("QPushButton { color:  #333; border: 1px solid #d7d6d5; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
            EditButton->setStyleSheet("QPushButton { color:  #333; border: 1px solid #d7d6d5; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
            NextButton->setStyleSheet("QPushButton { color:  #333; border: 1px solid #d7d6d5; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
            PreviousButton->setStyleSheet("QPushButton { color:  #333; border: 1px solid #d7d6d5; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
            LoadButton->setStyleSheet("QPushButton { color:  #333; border: 1px solid #d7d6d5; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
            SaveButton->setStyleSheet("QPushButton { color:  #333; border: 1px solid #d7d6d5; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
            ShowButton->setStyleSheet("QPushButton { color:  #333; border: 1px solid #d7d6d5; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
            PrintButton->setStyleSheet("QPushButton { color:  #333; border: 1px solid #d7d6d5; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
            RemoveButton->setStyleSheet("QPushButton { color:  #333; border: 1px solid #d7d6d5; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
            FindButton->setStyleSheet("QPushButton { color:  #333; border: 1px solid #d7d6d5; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");

            SubmitButton->show();
            CancelButton->show();
        break;

        case NavigationMode:
            if (Server.isEmpty())
            {
                for ( size_t i = 0; i < 6; ++i )
                    TextFields[i]->clear();
            }   // if

            for ( size_t i = 0; i < 6; ++i )
                TextFields[i]->setReadOnly(true);
            AddButton->setEnabled(true);
            AddButton->setStyleSheet("QPushButton { color: #333; border: 2px solid #555; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");

            int number = Server.size();
            EditButton->setEnabled(number >= 1);
            RemoveButton->setEnabled(number >= 1);
            NextButton->setEnabled(number > 0);
            PreviousButton->setEnabled(number > 0);
            FindButton->setEnabled(number > 0);
            LoadButton->setEnabled(true);
            SaveButton->setEnabled(true);
            LoadButton->setStyleSheet("QPushButton { color: #333; border: 2px solid #555; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
            SaveButton->setStyleSheet("QPushButton { color: #333; border: 2px solid #555; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
            ShowButton->setEnabled(number > 0);
            PrintButton->setEnabled(number > 0);

            if ( number > 0 )
            {
                NextButton->setStyleSheet("QPushButton { color: #333; border: 2px solid #555; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
                PreviousButton->setStyleSheet("QPushButton { color: #333; border: 2px solid #555; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
                EditButton->setStyleSheet("QPushButton { color: #333; border: 2px solid #555; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
                RemoveButton->setStyleSheet("QPushButton { color: red; border: 2px solid #555; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
                FindButton->setStyleSheet("QPushButton { color: #333; border: 2px solid #555; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
                ShowButton->setStyleSheet("QPushButton { color: #333; border: 2px solid #555; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
                PrintButton->setStyleSheet("QPushButton { color: #333; border: 2px solid #555; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
            }   // if
            else
            {
                EditButton->setStyleSheet("QPushButton { color:  #333; border: 1px solid #d7d6d5; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
                NextButton->setStyleSheet("QPushButton { color:  #333; border: 1px solid #d7d6d5; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
                PreviousButton->setStyleSheet("QPushButton { color:  #333; border: 1px solid #d7d6d5; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
                ShowButton->setStyleSheet("QPushButton { color:  #333; border: 1px solid #d7d6d5; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
                PrintButton->setStyleSheet("QPushButton { color:  #333; border: 1px solid #d7d6d5; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
                RemoveButton->setStyleSheet("QPushButton { color:  #333; border: 1px solid #d7d6d5; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
                FindButton->setStyleSheet("QPushButton { color:  #333; border: 1px solid #d7d6d5; border-radius: 11px; padding: 5px; background: qradialgradient(cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4, radius: 1.35, stop: 0 #fff, stop: 1 #888); min-width: 80px; }");
            }   // else

            SubmitButton->hide();
            CancelButton->hide();
        break;
    }   // switch
}   // Update Interface


inline void NumbersBook::RemoveContact() noexcept
{
    if (Server.contains(TextFields[0]->toPlainText()))
    {
        int button = QMessageBox::question(this, tr("Confirm Remove"),
        tr("Are you sure you want to remove \"%1\"?").arg(TextFields[0]->toPlainText()),
        QMessageBox::Yes | QMessageBox::No);

        if (button == QMessageBox::Yes)
        {
            QString Del = TextFields[0]->toPlainText();
            PreviousNumber();
            Server.remove(Del);
            QMessageBox::information(this, tr("Remove Successful"),
              tr("\"%1\" has been removed from your Numbers book.").arg(TextFields[0]->toPlainText()));
        }   // if
    } // if

    UpdateInterface(NavigationMode);
}  // RemoveContact

inline void NumbersBook::FindNumber() noexcept
{
    UpdateInterface(EditingMode);
    Dialog->show();

    if ( Dialog->exec() == QDialog::Accepted )
    {
        QString Num = Dialog->GetFindText();

        if ( Server.contains(Num) )
        {
            TextFields[0]->setText( Num );
            TextFields[1]->setText(Server.find( Num ).value().GetFeature1() );
            TextFields[2]->setText(Server.find( Num ).value().GetFeature2() );
            TextFields[3]->setText(Server.find( Num ).value().GetFeature3() );
            TextFields[4]->setText(Server.find( Num ).value().GetFeature4() );
            TextFields[5]->setText(Server.find( Num ).value().GetFeature5() );
        }   // if
        else
        {
            QMessageBox::information(this, tr("Number Not Found"),
                tr("Sorry, \"%1\" is not in your Numbers book.").arg( Num ));
            //return;
        }   // else
    }   // if

    UpdateInterface(NavigationMode);
}   // FindNumber

inline void NumbersBook::SaveToFile() noexcept
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Numbers Book"), "",
        tr("Numbers Book (*.txt);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else
    {
        QFile file(fileName);
        if ( !file.open( QIODevice::WriteOnly ) )
        {
                QMessageBox::information(this, tr("Unable to open file"),
                    file.errorString());
                return;
        }   // if

        QTextStream out(&file);
        //out.setVersion(QDataStream::Qt_4_5);
        out.setCodec("UTF-8");

        QMap<QString, Infos>::iterator i = Server.begin();
        while( i != Server.end() )
        {
            QString NewLine('\n');

            out << i.key() << NewLine
                << i.value().GetFeature1() << NewLine
                << i.value().GetFeature2() << NewLine
                << i.value().GetFeature3() << NewLine
                << i.value().GetFeature4() << NewLine
                << i.value().GetFeature5() << NewLine
                << NewLine;
            i++;
        }   // While
    }   // else
}   // SaveToFile

inline void NumbersBook::LoadFromFile() noexcept
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open Numbers Book"), "",
            tr("Numbers Book (*.txt);;All Files (*)"));

    if (fileName.isEmpty())
       return;
    else
    {
        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
            return;
        }   // if

        QTextStream in(&file);
        //in.setVersion(QDataStream::Qt_4_5);
        in.setCodec("UTF-8");

        // read the file
        QVector<QString> V;
        while( !in.atEnd() )
        {
            QString L = in.readLine();
            if ( L != "" )
                V.push_back( L );
        }   // while

        Server.clear();

        for ( size_t i = 0; i < (size_t)V.size(); i += 6 )
        {
             Server.insert( V[i],Infos(V[i+1], V[i+2], V[i+3], V[i+4], V[i+5] ) );
        }   // for

        if ( Server.isEmpty() )
        {
            QMessageBox::information(this, tr("No contacts in file"),
                  tr("The file you are attempting to open contains no contacts."));
            return;
        } // if
        else
        {
            QMap<QString, Infos>::iterator i = Server.begin();
            TextFields[0]->setText( i.key() );
            TextFields[1]->setText( i.value().GetFeature1() );
            TextFields[2]->setText( i.value().GetFeature2() );
            TextFields[3]->setText( i.value().GetFeature3() );
            TextFields[4]->setText( i.value().GetFeature4() );
            TextFields[5]->setText( i.value().GetFeature5() );
        }   // else
     }  // else

     UpdateInterface(NavigationMode);
}  // LoadFromFile

inline void NumbersBook::ShowAll() noexcept
{
    QString Informations;

    QMap<QString, Infos>::iterator i = Server.begin();

    while ( i != Server.end() )
    {
        Informations += "Αριθμός τηλεφώνου: " + i.key()
            + '\n' + "Ανταποκριτής: " + i.value().GetFeature1()
            + '\n' + "Κάρτα τηλ. κέντρου: " + i.value().GetFeature2()
            + '\n' + "Κεντρικός κατανεμητής: " + i.value().GetFeature3()
            + '\n' + "Εξωτερικός κατανεμητής: " + i.value().GetFeature4()
            + '\n' + "Σχόλια: " + i.value().GetFeature5()
            + '\n' + "--------------------------------------------------------------------------" + '\n';
        ++i;
    }   // while

    SDialog->SetTextInDialog(Informations);
    SDialog->show();
}   // ShowAll

inline void NumbersBook::FirstLoad() noexcept
{
    QFile file("DataBase.txt");

    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
        return;
    }   // if

    QTextStream in(&file);
    //in.setVersion(QDataStream::Qt_4_5);
    in.setCodec("UTF-8");

    // read the file
    QVector<QString> V;
    while (!in.atEnd())
    {
        QString L = in.readLine();
        if (L != "")
            V.push_back(L);
    }   // while

    Server.clear();

    for (size_t i = 0; i < (size_t)V.size(); i += 6)
    {
        Server.insert(V[i], Infos(V[i + 1], V[i + 2], V[i + 3], V[i + 4], V[i + 5]));
    }   // for

    if (Server.isEmpty())
    {
        QMessageBox::information(this, tr("No contacts in file"),
            tr("The file you are attempting to open contains no contacts."));
        return;
    } // if
    else
    {
        QMap<QString, Infos>::iterator i = Server.begin();
        TextFields[0]->setText(i.key());
        TextFields[1]->setText(i.value().GetFeature1());
        TextFields[2]->setText(i.value().GetFeature2());
        TextFields[3]->setText(i.value().GetFeature3());
        TextFields[4]->setText(i.value().GetFeature4());
        TextFields[5]->setText(i.value().GetFeature5());
        UpdateInterface(NavigationMode);
    }   // else
}	// First Load

inline void NumbersBook::PrintNumbers() noexcept
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("output.pdf");

    QString Informations;

    QMap<QString, Infos>::iterator i = Server.begin();

    while (i != Server.end())
    {
        Informations += "Αριθμός τηλεφώνου: " + i.key()
            + '\n' + "Ανταποκριτής: " + i.value().GetFeature1()
            + '\n' + "Κάρτα τηλ. κέντρου: " + i.value().GetFeature2()
            + '\n' + "Κεντρικός κατανεμητής: " + i.value().GetFeature3()
            + '\n' + "Εξωτερικός κατανεμητής: " + i.value().GetFeature4()
            + '\n' + "Σχόλια: " + i.value().GetFeature5()
            + '\n' + "--------------------------------------------------------------------------" + '\n';
        ++i;
    }   // while
    //howAllDialog *D = new ShowAllDialog(this);
    //D->GetField()->print(&printer

    SDialog->SetTextInDialog(Informations);
    SDialog->GetField()->print(&printer);

    system("output.pdf");
}	// PrintNumbers

void NumbersBook::closeEvent(QCloseEvent *event)
{
    if (event->spontaneous())
    {
        int Answer = QMessageBox::question(this, tr("Exiting..."),
                     tr("Are you sure you saved the temporary data base ?"
                        " Press (Yes) if u have already saved it, (No) to save and exit"
                        " or (Cancel) to return"),
                     QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel );

        if ( Answer == QMessageBox::Cancel )
           event->ignore();
        else if ( Answer == QMessageBox::Yes )
            event->accept();
        else if ( Answer == QMessageBox::No )
            this->SaveToFile(), event->accept();
    }   // if
}   // CloseEvent override function



