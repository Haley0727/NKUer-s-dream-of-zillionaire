#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mydialog.h"
#include<global.h>

#ifdef DEBUG
static void LYL232BUGS()
{
    LYL232::bugs+=3;
    LYL232::bugsfixed+=3;
}
void LYL232::mainwindowcpp()
{
    LYL232BUGS();
}
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GLOBAL::mainwindow=this;
    gamemainwidget=NULL;
    musicslist=new QMediaPlaylist(this);
    musicsplayer=new QMediaPlayer(this);
    musicslist->addMedia(QUrl::fromLocalFile("D:\\qt\\projects\\MyProject\\mymusic\\0.mp3"));
    musicslist->addMedia(QUrl::fromLocalFile("D:\\qt\\projects\\MyProject\\mymusic\\1.mp3"));
    musicslist->addMedia(QUrl::fromLocalFile("D:\\qt\\projects\\MyProject\\mymusic\\2.mp3"));
    musicslist->addMedia(QUrl::fromLocalFile("D:\\qt\\projects\\MyProject\\mymusic\\3.mp3"));
    musicslist->addMedia(QUrl::fromLocalFile("D:\\qt\\projects\\MyProject\\mymusic\\4.mp3"));
    musicslist->addMedia(QUrl::fromLocalFile("D:\\qt\\projects\\MyProject\\mymusic\\5.mp3"));
    musicslist->addMedia(QUrl::fromLocalFile("D:\\qt\\projects\\MyProject\\mymusic\\6.mp3"));
    musicslist->addMedia(QUrl::fromLocalFile("D:\\qt\\projects\\MyProject\\mymusic\\7.mp3"));
    musicslist->addMedia(QUrl::fromLocalFile("D:\\qt\\projects\\MyProject\\mymusic\\8.mp3"));
    musicslist->addMedia(QUrl::fromLocalFile("D:\\qt\\projects\\MyProject\\mymusic\\9.mp3"));
    musicslist->setCurrentIndex(0);
    musicslist->setPlaybackMode(QMediaPlaylist::Random);
    musicsplayer->setPlaylist(musicslist);
    musicsplayer->play();
    musicsplayer->setVolume(50);
}

MainWindow::~MainWindow()
{
    delete musicslist;
    delete musicsplayer;
    delete ui;
}

void MainWindow::on_EnterGame_clicked()
{

    MyDialog playercustomizedig(MyDialogType::PlayerCustomize,0,0,this);
    playercustomizedig.setWindowFlags(playercustomizedig.windowFlags()&~Qt::WindowMaximizeButtonHint&~Qt::WindowMinimizeButtonHint&~Qt::WindowContextHelpButtonHint);
    playercustomizedig.setWindowTitle(tr("玩家设置"));
    if(playercustomizedig.exec()==QDialog::Accepted)
    {
        setCursor(Qt::WaitCursor);
        gamemainwidget=new GameMainWidget;
        GLOBAL::gamemainwidget=gamemainwidget;

        if(GLOBAL::Gaming==true)
        {
            gamemainwidget->setWindowTitle("∫Ndz");
            gamemainwidget->setWindowFlags(gamemainwidget->windowFlags()&~Qt::WindowMaximizeButtonHint&~Qt::WindowMinimizeButtonHint&~Qt::WindowContextHelpButtonHint);
            gamemainwidget->show();
            /*不想把边框去掉，只想去掉问号按钮
            setWindowFlags(windowFlags()&~Qt::WindowCloseButtonHint&~Qt::WindowContextHelpButtonHint);
            关闭和问号按钮都去掉
            setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
            */

            setCursor(Qt::ArrowCursor);
            this->hide();
        }
        else//游戏初始化失败;
        {
            QMessageBox::warning(this,tr("error"),tr("初始化过程中发生未知错误！无法启动游戏。"),QMessageBox::Ok);
            setCursor(Qt::ArrowCursor);
            this->show();
            delete gamemainwidget;
            gamemainwidget=NULL;
        }
    }
    else
    {
        this->show();
    }
}

void MainWindow::on_QuitGame_clicked()
{
    this->close();
}

void MainWindow::on_options_clicked()
{
    optiondialog=new OptionDialog(this);
    optiondialog->exec();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pixmap(GLOBAL::ssmap["MainWindowBackGround"]);
    pixmap=pixmap.scaled(640,360);
    painter.drawPixmap(0,0,640,360,pixmap);


}

void MainWindow::on_Help_clicked()
{
    MyWidget *mywidget=new MyWidget(MyWidgetType::IntroductionWidget);
    MyDialog mydialog(MyDialogType::IntroductionDialog,(int)mywidget,0);
    mydialog.exec();
    delete mywidget;
}
