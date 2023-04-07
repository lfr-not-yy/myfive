#include "widget.h"
#include "zobrist.h"
#include <QApplication>
#include "chessai.h"
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
