#include "mainwindow.h"
#include <QApplication>
#include <QListView>
#include <QStringListModel>


#include "api.h"
#include "light.h"
#include "lightlistmodel.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QLocale::setDefault(QLocale::English);

    return a.exec();
}
