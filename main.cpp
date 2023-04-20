#include "bookstore.h"

#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BookStore w("../BookStore/books.txt", "../BookStore/clients.txt", nullptr);
    w.show();

    return a.exec();
}
