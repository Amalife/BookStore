#include "bookstore.h"

#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BookStore w(nullptr, "../BookStore/books.txt");
    w.show();

    return a.exec();
}
