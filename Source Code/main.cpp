#include "numbersbook.h"
#include "numbersbook.cpp"
#include "logindialog.h"
#include "logindialog.cpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    LoginDialog L;
    NumbersBook Wdj;
    L.show();

    if ( L.exec() == QMessageBox::Accepted )
        Wdj.show();

    return app.exec();
}   // main
