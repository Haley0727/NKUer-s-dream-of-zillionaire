#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<gamemainwidget.h>
#include<Classes.h>
#include<optiondialog.h>
#include"global.h"


/*
我是LYL232,今天收到了从0编写大富翁的需求，我现在慌得一批
                                                                    -----2018.7.4
*/


class QMediaPlayer;
class QMediaPlaylist;

class GameMainWidget;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    GameMainWidget *gamemainwidget;
    ~MainWindow();

    QMediaPlayer *musicsplayer;
    QMediaPlaylist *musicslist;

private slots:
    void on_EnterGame_clicked();

    void on_QuitGame_clicked();

    void on_options_clicked();

    void on_Help_clicked();

private:
    Ui::MainWindow *ui;

    OptionDialog *optiondialog;

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // MAINWINDOW_H
