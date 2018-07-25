#include "mainwindow.h"
#include <QApplication>
#include<gamemainwidget.h>
#include<global.h>


class QMediaPlaylist;
class QMediaPlayer;

int main(int argc, char *argv[])
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    QApplication a(argc, argv);
    GLOBAL global;//只是为了初始化
    MainWindow w;
    GLOBAL::mainwindow=&w;


    w.show();

    return a.exec();
}
