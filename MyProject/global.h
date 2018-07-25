#ifndef GLOBAL_H
#define GLOBAL_H
#include<QMap>
#include<QString>
#include<QCursor>
#include<QPainter>
#include<QDebug>
#include<QMessageBox>
#include<QMouseEvent>
#include<QTimer>
#include<QTime>
#include<QLabel>
#include<QWidget>
#include<QDialog>
#include<QVector>
#include<QPropertyAnimation>
#include<QPushButton>
#include<QIcon>
#include<QFont>
#include<QLineEdit>
#include<QSpinBox>
#include<QSlider>
#include<QCheckBox>
#include<QScrollArea>
#include<QTextBrowser>
#include<QShortcut>
#include<QMediaPlayer>
#include<QMediaPlaylist>


#include<math.h>


#include<mydialog.h>
#include<mainwindow.h>

#define DEBUG

typedef std::pair<int,int> PII;

typedef QMap<QString,QString> SSMAP;
typedef QMap<QString,int> SIMAP;
typedef QMap<PII,int> PIIIMAP;

class MainWindow;
class QMediaPlayer;
class QMediaPlaylist;

class GLOBAL
{
    void IntroductionInitialize();
public:

    //用于储存设置之类的信息，还有一些图像的路径
    static SSMAP ssmap;//为什么要用这个存字符串？因为我懒，不用声明多个变量，舒服
    static SIMAP simap;
    static PIIIMAP piiimap;//用来传递一些参数
    static MainWindow*mainwindow;
    static GameMainWidget*gamemainwidget;
    static const double pi;
    static bool Gaming,isplaymusic;
    static QPixmap *IntroductionPixmap;
    GLOBAL();
    ~GLOBAL()
    {
        if(IntroductionPixmap)
            delete IntroductionPixmap;
    }
};

#ifdef DEBUG
class LYL232
{
    long long ago_when_LYL232_create_this_project;
    static bool theresnotwoLYL232s;
public:
    static unsigned long long bugs;
    static unsigned long long bugsfixed;
    static QVector<QString> notes;
    void Classcpp();
    void gamemainwidgetcpp();
    void mainwindowcpp();
    void mydialogcpp();
    void mywidgetcpp();
    void chatwidgetcpp();

    LYL232();
    ~LYL232(){theresnotwoLYL232s=false;}
};
#endif

QPoint GetRandomQPointInRadiu(const QPoint&Center,const qreal Radiu,bool RandomDistance);

QImage GreyScale(const QImage & origin,const int light);

QImage DarkScale(const QImage & origin,const int scale);

QImage ImageShrinkScale(const QImage & source,const int width,const int height);

void disorderintarray(int *array,const int num);

void stringToHtmlFilter(QString &str);

QColor PlayerIdToColor(const int id);

void stringToHtml(QString &str,QColor crl);

#endif // GLOBAL_H
