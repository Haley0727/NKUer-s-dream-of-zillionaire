#include "mydialog.h"
#include "ui_mydialog.h"
#include "gamemainwidget.h"
#include "global.h"
#include "Classes.h"
class Block;
class AvailableBlock;
class BuildableBlock;
class Player;

#ifdef DEBUG
static void LYL232BUGS()
{
    LYL232::bugs+=10;
    LYL232::bugsfixed+=10;
}
void LYL232::mydialogcpp()
{
    LYL232BUGS();
}
#endif

MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);
}

MyDialog::MyDialog(MyDialogType atype,const int aarg1,const int aarg2, QWidget *parent) :
    QDialog(parent),type(atype),arg1(aarg1),arg2(aarg2),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);
    pushbutton_back=NULL;
    pushbutton_confirm=NULL;
    pushbutton_next=NULL;
    pushbutton_previous=NULL;
    playercustomizespinbox=NULL;
    mainpixmap=NULL;
    confirm=NULL;
    pushbutton_playeriamgelist=NULL;
    playercustomizenameedit=NULL;
    biddingplayerordertoid=NULL;
    timer=NULL;
    biddingslider=NULL;
    biddingspinbox=NULL;
    label=NULL;

    scrollarea=NULL;


    switch(type)
    {
    case MyDialogType::GameMenu:
    {
        setFixedSize(GLOBAL::simap["ResolutionWidth"]/4,
                GLOBAL::simap["ResolutionHeight"]/2);

        pushbutton_back=new QPushButton(this);
        pushbutton_confirm=new QPushButton(this);
        label=new QLabel(this);
        biddingslider=new QSlider(this);//不是竞价模式，拿来用一下
        biddingspinbox=new QSpinBox(this);
        if(!pushbutton_back||!pushbutton_confirm||!label||
                !biddingslider||!biddingspinbox
                )reject();
        else
        {

            QFont font("微软雅黑",width()*3/80,QFont::Bold,false);

            setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint&~Qt::WindowMinimizeButtonHint&~Qt::WindowContextHelpButtonHint);

            pushbutton_back->setGeometry(width()*7/18,height()*3/4-parent->width()/36,(parent->width())/18,(parent->width())/24);
            pushbutton_back->setStyleSheet(GLOBAL::ssmap["PushButtonStyleSheet1"]);
            pushbutton_back->setFont(font);

            pushbutton_back->setText("返回");
            pushbutton_back->show();
            connect(pushbutton_back,SIGNAL(clicked()),this,SLOT(PushButton_Back_Clicked()));

            pushbutton_confirm->setGeometry(width()*3/10,height()/2-parent->width()/36,(parent->width())/10,(parent->width())/24);
            pushbutton_confirm->setStyleSheet(GLOBAL::ssmap["PushButtonStyleSheet1"]);
            pushbutton_confirm->setFont(font);

            pushbutton_confirm->setText("游戏说明");
            pushbutton_confirm->show();
            connect(pushbutton_confirm,SIGNAL(clicked()),this,SLOT(PushButton_Confirm_clicked()));

            font.setPointSize(width()/40);
            label->setGeometry(width()/6,height()/10,width()/2,height()/12);
            label->setFont(font);
            label->setText(tr("背景音乐音量："));

            biddingslider->setGeometry(width()/4,height()/4,width()/2,height()/15);

            biddingspinbox->setFont(font);
            biddingspinbox->setGeometry(width()*5/8,height()/9,width()/8,height()/15);

            biddingspinbox->setRange(0,99);


            biddingslider->setOrientation(Qt::Horizontal);

            connect(biddingslider,SIGNAL(valueChanged(int)),biddingspinbox,SLOT(setValue(int)));
            connect(biddingspinbox,SIGNAL(valueChanged(int)),biddingslider,SLOT(setValue(int)));
            connect(biddingslider,SIGNAL(valueChanged(int)),this,SLOT(VolumeSliderValueChange(int)));

            biddingspinbox->setValue(GLOBAL::simap["MusicVolume"]);

            setWindowTitle("菜单");
        }


        break;
    }
    case MyDialogType::PlayerCustomize:
    {
        resize(GLOBAL::simap["ResolutionWidth"]*2/3,
            GLOBAL::simap["ResolutionHeight"]*2/3);
        int width=this->width(),height=this->height();

        pushbutton_back=new QPushButton(this);
        pushbutton_confirm=new QPushButton(this);
        pushbutton_next=new QPushButton(this);
        pushbutton_previous=new QPushButton(this);
        pushbutton_playeriamgelist=new QPushButton*[30];
        playercustomizespinbox=new QSpinBox(this);
        playercustomizenameedit=new QLineEdit(this);
        mainpixmap=new QPixmap(width,height);

        for(int i=0;i<30;i++)
            if((pushbutton_playeriamgelist[i]=new QPushButton(this))==NULL)
                reject();


        if(!pushbutton_back||
                !pushbutton_confirm||
                !pushbutton_next||
                !pushbutton_previous||
                !pushbutton_playeriamgelist||
                !playercustomizespinbox||
                !playercustomizenameedit||
                !mainpixmap
                )
            reject();
        else
        {

        playercustomizeindex=-1;

        playercustomizespinbox->setRange(2,6);
        playercustomizespinbox->setValue(6);
        {
            QFont font("微软雅黑",width*3/128,QFont::Bold,false);
            playercustomizespinbox->setFont(font);
        }

        playercustomizespinbox->show();

        playercustomizenameedit->setGeometry(width/6,height/8,width/4,height/8);
        playercustomizenameedit->hide();
        {
            QFont font("微软雅黑",width*3/128,QFont::Bold,false);
            playercustomizenameedit->setFont(font);
        }

        QFont font("微软雅黑",width*3/160,QFont::Bold,false);
        {
            pushbutton_back->setGeometry(width/11,height/12*11-width/18,width/12,width/18);
            pushbutton_back->setStyleSheet(GLOBAL::ssmap["PushButtonStyleSheet1"]);
            pushbutton_back->setText("取消");
            pushbutton_back->setFont(font);
        }
        {
            pushbutton_next->setGeometry(width*19/24,height/12*11-width/18,width/9,width/18);
            pushbutton_next->setStyleSheet(GLOBAL::ssmap["PushButtonStyleSheet1"]);
            pushbutton_next->setText("下一个");
            pushbutton_next->setShortcut(Qt::Key_Return);
            pushbutton_next->setShortcut(Qt::Key_Enter);
            pushbutton_next->setFont(font);
        }
        {
            pushbutton_previous->setGeometry(width/12*7,height/12*11-width/18,width/12,width/18);
            pushbutton_previous->setStyleSheet(GLOBAL::ssmap["PushButtonStyleSheet1"]);
            pushbutton_previous->setText("返回");
            pushbutton_previous->setFont(font);
        }
        {
            pushbutton_confirm->setGeometry(width*19/24,height/12*11-width/18,width/9,width/18);
            pushbutton_confirm->setStyleSheet(GLOBAL::ssmap["PushButtonStyleSheet1"]);
            pushbutton_confirm->setText("确定");
            pushbutton_next->setShortcut(Qt::Key_Return);
            pushbutton_next->setShortcut(Qt::Key_Enter);
            pushbutton_confirm->setFont(font);
        }
        //这个好想要循环写啊啊啊啊啊啊！！！
        {
            pushbutton_playeriamgelist[0]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/LYL232.png);}");
            pushbutton_playeriamgelist[0]->setGeometry(width*19/36,width/6,width/18,width/18);
            pushbutton_playeriamgelist[1]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/PlayerImages/1-1.png);}");
            pushbutton_playeriamgelist[1]->setGeometry(width*21/36,width/6,width/18,width/18);
            pushbutton_playeriamgelist[2]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/PlayerImages/1-2.png);}");
            pushbutton_playeriamgelist[2]->setGeometry(width*23/36,width/6,width/18,width/18);
            pushbutton_playeriamgelist[3]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/PlayerImages/1-3.png);}");
            pushbutton_playeriamgelist[3]->setGeometry(width*25/36,width/6,width/18,width/18);
            pushbutton_playeriamgelist[4]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/PlayerImages/1-4.png);}");
            pushbutton_playeriamgelist[4]->setGeometry(width*27/36,width/6,width/18,width/18);
            pushbutton_playeriamgelist[5]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/PlayerImages/1-5.png);}");
            pushbutton_playeriamgelist[5]->setGeometry(width*29/36,width/6,width/18,width/18);
            pushbutton_playeriamgelist[6]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/PlayerImages/1-6.png);}");
            pushbutton_playeriamgelist[6]->setGeometry(width*31/36,width/6,width/18,width/18);
            pushbutton_playeriamgelist[7]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/PlayerImages/1-7.png);}");
            pushbutton_playeriamgelist[7]->setGeometry(width*19/36,width*2/9,width/18,width/18);
            pushbutton_playeriamgelist[8]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/PlayerImages/2-1.png);}");
            pushbutton_playeriamgelist[8]->setGeometry(width*21/36,width*2/9,width/18,width/18);
            pushbutton_playeriamgelist[9]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/PlayerImages/2-2.png);}");
            pushbutton_playeriamgelist[9]->setGeometry(width*23/36,width*2/9,width/18,width/18);
            pushbutton_playeriamgelist[10]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/PlayerImages/2-3.png);}");
            pushbutton_playeriamgelist[10]->setGeometry(width*25/36,width*2/9,width/18,width/18);
            pushbutton_playeriamgelist[11]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/PlayerImages/2-4.png);}");
            pushbutton_playeriamgelist[11]->setGeometry(width*27/36,width*2/9,width/18,width/18);
            pushbutton_playeriamgelist[12]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/PlayerImages/2-5.png);}");
            pushbutton_playeriamgelist[12]->setGeometry(width*29/36,width*2/9,width/18,width/18);
            pushbutton_playeriamgelist[13]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/PlayerImages/2-6.png);}");
            pushbutton_playeriamgelist[13]->setGeometry(width*31/36,width*2/9,width/18,width/18);
            pushbutton_playeriamgelist[14]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/PlayerImages/2-7.png);}");
            pushbutton_playeriamgelist[14]->setGeometry(width*19/36,width*5/18,width/18,width/18);
            pushbutton_playeriamgelist[15]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/PlayerImages/2-8.png);}");
            pushbutton_playeriamgelist[15]->setGeometry(width*21/36,width*5/18,width/18,width/18);
            pushbutton_playeriamgelist[16]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/PlayerImages/2-9.png);}");
            pushbutton_playeriamgelist[16]->setGeometry(width*23/36,width*5/18,width/18,width/18);
            pushbutton_playeriamgelist[17]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/PlayerImages/2-10.png);}");
            pushbutton_playeriamgelist[17]->setGeometry(width*25/36,width*5/18,width/18,width/18);
            pushbutton_playeriamgelist[18]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/PlayerImages/2-11.png);}");
            pushbutton_playeriamgelist[18]->setGeometry(width*27/36,width*5/18,width/18,width/18);
            pushbutton_playeriamgelist[19]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/PlayerImages/2-12.png);}");
            pushbutton_playeriamgelist[19]->setGeometry(width*29/36,width*5/18,width/18,width/18);
            pushbutton_playeriamgelist[20]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/PlayerImages/3-1.png);}");
            pushbutton_playeriamgelist[20]->setGeometry(width*31/36,width*5/18,width/18,width/18);
            pushbutton_playeriamgelist[21]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/PlayerImages/3-2.png);}");
            pushbutton_playeriamgelist[21]->setGeometry(width*19/36,width/3,width/18,width/18);
            pushbutton_playeriamgelist[22]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/PlayerImages/3-3.png);}");
            pushbutton_playeriamgelist[22]->setGeometry(width*21/36,width/3,width/18,width/18);
            pushbutton_playeriamgelist[23]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/PlayerImages/3-4.png);}");
            pushbutton_playeriamgelist[23]->setGeometry(width*23/36,width/3,width/18,width/18);
            pushbutton_playeriamgelist[24]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/PlayerImages/3-5.png);}");
            pushbutton_playeriamgelist[24]->setGeometry(width*25/36,width/3,width/18,width/18);
            pushbutton_playeriamgelist[25]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/PlayerImages/3-6.png);}");
            pushbutton_playeriamgelist[25]->setGeometry(width*27/36,width/3,width/18,width/18);
            pushbutton_playeriamgelist[26]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/PlayerImages/3-7.png);}");
            pushbutton_playeriamgelist[26]->setGeometry(width*29/36,width/3,width/18,width/18);
            pushbutton_playeriamgelist[27]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/PlayerImages/3-8.png);}");
            pushbutton_playeriamgelist[27]->setGeometry(width*31/36,width/3,width/18,width/18);
            pushbutton_playeriamgelist[28]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/PlayerImages/3-9.png);}");
            pushbutton_playeriamgelist[28]->setGeometry(width*19/36,width*7/18,width/18,width/18);
            pushbutton_playeriamgelist[29]->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/PlayerImages/3-10.png);}");
            pushbutton_playeriamgelist[29]->setGeometry(width*21/36,width*7/18,width/18,width/18);
        }

        connect(pushbutton_back,SIGNAL(clicked()),this,SLOT(PushButton_PlayerCustomize_Clicked()));
        connect(pushbutton_next,SIGNAL(clicked()),this,SLOT(PushButton_PlayerCustomize_Clicked()));
        connect(pushbutton_previous,SIGNAL(clicked()),this,SLOT(PushButton_PlayerCustomize_Clicked()));
        connect(pushbutton_confirm,SIGNAL(clicked()),this,SLOT(PushButton_PlayerCustomize_Clicked()));

        pushbutton_back->show();
        pushbutton_next->hide();
        pushbutton_previous->hide();
        pushbutton_confirm->show();
        for(int i=0;i<30;i++)
        {
            pushbutton_playeriamgelist[i]->hide();
            connect(pushbutton_playeriamgelist[i],SIGNAL(clicked()),this,SLOT(PushButton_PlayerCustomize_Clicked()));
        }

        width/=2,height/=2;
        resize(width,height);
        setFixedSize(width,height);
        playercustomizespinbox->setGeometry(width/2-width/6,height/2-height/8,width/3,height/4);

        pushbutton_back->setGeometry(width/12,height*5/6-width/20,width/4,width/10);
        pushbutton_confirm->setGeometry(width*2/3,height*5/6-width/20,width/4,width/10);



        }
        break;
    }
    case MyDialogType::Bidding:
    {
            pushbutton_back=new QPushButton(this);//放弃竞价
            pushbutton_confirm=new QPushButton(this);//竞价

            biddingslider=new QSlider(this);
            biddingspinbox=new QSpinBox(this);

            biddingplayerordertoid=new int[6];

            timer=new QTimer(this);

            if(!pushbutton_back||!pushbutton_confirm||
               !biddingplayerordertoid||!biddingslider||!biddingspinbox||
               !timer
               )
                reject();
            else
            {
                this->resize(GLOBAL::simap["ResolutionWidth"]*2/3,
                        GLOBAL::simap["ResolutionHeight"]*2/3);
                const int width=this->width(),height=this->height();

                QFont font("微软雅黑",width*3/128,QFont::Bold,false);
                {
                    pushbutton_back->setGeometry(width*17/24,height*19/24-width/18,width/5,width/18);
                    pushbutton_back->setStyleSheet(GLOBAL::ssmap["PushButtonStyleSheet1"]);//鼠标按下的色彩
                    pushbutton_back->setText("放弃竞价");
                    pushbutton_back->setFont(font);
                }
                {
                    pushbutton_confirm->setGeometry(width*11/24,height*19/24-width/18,width/8,width/18);
                    pushbutton_confirm->setStyleSheet(GLOBAL::ssmap["PushButtonStyleSheet1"]);//鼠标按下的色彩
                    pushbutton_confirm->setText("竞价");
                    pushbutton_confirm->setFont(font);
                }
                    connect(pushbutton_confirm,SIGNAL(clicked()),this,SLOT(PushButton_Bidding_Clicked()));
                    connect(pushbutton_back,SIGNAL(clicked()),this,SLOT(PushButton_Bidding_Clicked()));


                    for(int i=0;i<GLOBAL::simap["Players"];i++)
                    {
                        isplayerbidding[i]=true;
                        biddingplayerordertoid[i]=GLOBAL::gamemainwidget->playerordertoid[i];
                    }
                    //变量初始化
                    {
                    biddingplayernum=GLOBAL::gamemainwidget->playeractivenum;

                    //防止第一个竞价的玩家已失败
                    for(biddingorder=0;biddingorder<GLOBAL::simap["Players"];biddingorder++)
                        if(GLOBAL::gamemainwidget->players[biddingplayerordertoid[biddingorder]]->isfailed==false)break;


                    biddingprice=0;
                    owningplayerid=biddingplayerordertoid[biddingorder];
                    confirm=false;
                    isbiddingplayeroperated=false;

                    }


                    font.setPointSize(height/15);
                    biddingspinbox->setFont(font);
                    biddingspinbox->setGeometry(width*7/12,height/2,width/4,height/8);
                    biddingslider->setGeometry(width/12,height/6*5,width*5/6,height/12);

                    biddingspinbox->setRange(0,GLOBAL::gamemainwidget->players[biddingplayerordertoid[0]]->cash);
                    biddingslider->setRange(0,GLOBAL::gamemainwidget->players[biddingplayerordertoid[0]]->cash);

                    connect(biddingslider,SIGNAL(valueChanged(int)),biddingspinbox,SLOT(setValue(int)));
                    connect(biddingspinbox,SIGNAL(valueChanged(int)),biddingslider,SLOT(setValue(int)));

                    biddingspinbox->setValue(0);
                    biddingslider->setOrientation(Qt::Horizontal);

                    timer->setTimerType(Qt::PreciseTimer);
                    biddingtimelimit=GLOBAL::simap["OperateTime"]/3;//设置每个玩家能考虑的时间
                    biddingtimercounter=biddingtimelimit;
                    connect(timer,SIGNAL(timeout()),this,SLOT(BiddingTurns()));
                    timer->setSingleShot(false);
                    timer->start(1000);

                    update();

            }
            break;
    }
    case MyDialogType::IntroductionDialog:
    {
        pushbutton_back=new QPushButton(this);
        scrollarea=new QScrollArea(this);
        if(!pushbutton_back||!scrollarea)
            reject();
        else
        {
            setWindowTitle(tr("游戏说明"));
            this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint&~Qt::WindowMinimizeButtonHint&~Qt::WindowContextHelpButtonHint);
            resize(GLOBAL::simap["ResolutionWidth"]*11/20,GLOBAL::simap["ResolutionHeight"]);
            const int width=this->width(),height=this->height();
            scrollarea->setWidget((MyWidget*)arg1);
            scrollarea->setGeometry(width*7/176,height/25,width*83/88,height*7/8);
            scrollarea->setAlignment(Qt::AlignCenter);
            scrollarea->setFixedSize(width*83/88,height*7/8);

            pushbutton_back->setGeometry(width*9/10,height*37/40,width/12,height/20);
            pushbutton_back->setStyleSheet(GLOBAL::ssmap["PushButtonStyleSheet1"]);
            pushbutton_back->setText(tr("返回"));
            connect(pushbutton_back,SIGNAL(clicked()),this,SLOT(PushButton_Back_Clicked()));
            break;
        }
    }
    }
}

void MyDialog::paintEvent(QPaintEvent *)
{
    switch(this->type)
    {
    case MyDialogType::PlayerCustomize:
    {
        QPainter mainpainter(this);
        QPainter pixmappainter(mainpixmap);
        QPen pen;
        pen.setWidth((GLOBAL::simap["ResolutionWidth"])/160);

        switch(playercustomizeindex)
        {
        case 0:pen.setColor(QColor(220,20,60));break;
        case 1:pen.setColor(QColor(30,144,255));break;
        case 2:pen.setColor(QColor(0,255,255));break;
        case 3:pen.setColor(QColor(255,0,255));break;
        case 4:pen.setColor(QColor(255,255,0));break;
        case 5:pen.setColor(QColor(255,140,0));break;
        default:break;
        }

        pixmappainter.setPen(pen);
        switch(playercustomizeindex)
        {
        case-1:
        {
            mainpixmap->fill(Qt::white);
            const int width=this->width(),height=this->height();
            QFont font("微软雅黑",this->width()*27/320,QFont::Bold,false);
            pen.setColor(Qt::black);
            pixmappainter.setPen(pen);
            pixmappainter.setFont(font);
            QTextOption option(Qt::AlignLeft | Qt::AlignTop);
            option.setWrapMode(QTextOption::WordWrap);
            pixmappainter.drawText(QRect(width/8,height/8,width*3/2,height/3), tr("请选择玩家数量："), option);

            break;
        }
        default:
        {
            mainpixmap->fill(Qt::white);

            {
                QPixmap pixmap,scaledpximap;
                pixmap.load(GLOBAL::ssmap["PlayerImage"+QString::number(playercustomizeindex)]);
                scaledpximap=pixmap.scaled(this->width()/4,this->width()/4,Qt::IgnoreAspectRatio);
                pixmappainter.drawPixmap(mainpixmap->width()/6,mainpixmap->height()/3,scaledpximap);
            }
            pixmappainter.drawRect(mainpixmap->width()/6,mainpixmap->height()/3,mainpixmap->width()/4,mainpixmap->width()/4);
            {
                const int width=this->width(),height=this->height();
                QFont font("微软雅黑",this->width()*3/128,QFont::Bold,false);
                pen.setColor(Qt::black);
                pixmappainter.setPen(pen);
                pixmappainter.setFont(font);
                QTextOption option(Qt::AlignLeft | Qt::AlignTop);
                option.setWrapMode(QTextOption::WordWrap);
                pixmappainter.drawText(QRect(width/15,height/7,width/8,height/3), tr("名字："), option);
                pixmappainter.drawText(QRect(width*7/12,height/8,width,height/3), tr("请选择玩家图标："), option);
            }
            break;
        }
        }
        pixmappainter.setPen(pen);

        mainpainter.drawPixmap(0,0,this->width(),this->height(),*mainpixmap);


        break;
    }
    case MyDialogType::Bidding:
    {
        const int width=this->width(),height=this->height();
        QPixmap pixmap(width,height);
        QFont font("微软雅黑",width*3/128,QFont::Bold,false);
        QPainter painter(&pixmap),mainpainter(this);
        QPen pen;
        pixmap.fill(Qt::white);
        painter.setFont(font);
        pen.setColor(Qt::black);
        painter.setPen(pen);

        Block*blockp=GLOBAL::gamemainwidget->blocks[arg1];

        painter.drawText(width/20,height*3/20,blockp->name);


        if(((AvailableBlock*)GLOBAL::gamemainwidget->blocks[arg1])->type==AvailableBlockType::Buildable)
        {
            BuildableBlock* blockp=(BuildableBlock*)GLOBAL::gamemainwidget->blocks[arg1];
            font.setPointSize(width*9/640);
            painter.setFont(font);
            painter.drawText(width/20,height/20*5,"基础收费：¥"+
                             QString::number(blockp->chargebase));
            for(int i=1;i<=blockp->maxlevel;i++)
            painter.drawText(width/20,height/20*(7+2*(i-1)),QString("level%1：¥%2").arg(i).arg(
                             blockp->chargebase+blockp->chargeperlevel*i));
        }
        else
        {
            font.setPointSize(width*9/640);
            painter.setFont(font);
            painter.drawText(width/20,height/20*5,"快速旅行");
            painter.drawText(width/20,height/20*7,"1车站 ¥25");
            painter.drawText(width/20,height/20*9,"2车站 ¥50");
            painter.drawText(width/20,height/20*11,"3车站 ¥100");
            painter.drawText(width/20,height/20*13,"4车站 ¥200");
        }

        font.setPointSize(width*3/160);
        painter.setFont(font);
        painter.drawText(width*5/12,height/18,width/2,height/6,QFont::Bold,
                         GLOBAL::gamemainwidget->players[owningplayerid]->name+"竞价:¥"+
                         QString::number(biddingprice));
        {
            QPixmap pixmap(GLOBAL::ssmap["PlayerImage"+QString::number(owningplayerid)]);
            pixmap.scaled(width/8,width/8,Qt::IgnoreAspectRatio);
            painter.drawPixmap(width*9/12,height*2/9,width/8,width/8,pixmap);
        }

        switch(biddingplayerordertoid[biddingorder])
        {
        case 0:pen.setColor(Qt::red);break;
        case 1:pen.setColor(Qt::blue);break;
        case 2:pen.setColor(QColor(0,100,100));break;
        case 3:pen.setColor(QColor(255,0,255));break;
        case 4:pen.setColor(Qt::yellow);break;
        case 5:pen.setColor(QColor(255,97,0));break;
        default:break;
        }
        painter.setPen(pen);
        painter.drawText(width*5/12,height/4,
                         GLOBAL::gamemainwidget->players[biddingplayerordertoid[biddingorder]]->name);
        pen.setColor(QColor(0,0,0));
        painter.setPen(pen);
        painter.drawText(width*5/12,height*3/8,
                    "正在竞价:"+QString::number(biddingtimercounter));


        for(int i=0;i<GLOBAL::gamemainwidget->playernum;i++)
        {
            Player* player=GLOBAL::gamemainwidget->players[biddingplayerordertoid[i]];
            if(i==biddingorder&&player->isfailed==false)
            {
                pen.setColor(Qt::darkGreen);
            }
            else
            {
                if(isplayerbidding[biddingplayerordertoid[i]]&&player->isfailed==false)
                    pen.setColor(QColor(127,127,127));
                else
                    pen.setColor(QColor(150,0,0));
            }
            pen.setWidth(width*3*6/2/1600);
            painter.setPen(pen);
            font.setBold(false);
            font.setPointSize(width*3/320);
            QRect rect(width*11/48,height/9+i*height/9,width/6,height/10);
            painter.drawRect(rect);
            switch(biddingplayerordertoid[i])
            {
            case 0:pen.setColor(Qt::red);break;
            case 1:pen.setColor(Qt::blue);break;
            case 2:pen.setColor(QColor(0,100,100));break;
            case 3:pen.setColor(QColor(255,0,255));break;
            case 4:pen.setColor(Qt::yellow);break;
            case 5:pen.setColor(QColor(255,97,0));break;
            default:break;
            }
            painter.setPen(pen);
            painter.drawText(width*23/96,height/9+i*height/9,width/6,height/10,0,player->name);

        }

        mainpainter.drawPixmap(0,0,pixmap);


    }
    default:break;
    }
}

MyDialog::~MyDialog()
{
    delete label;
    delete biddingslider;
    delete biddingspinbox;
    delete timer;
    delete biddingplayerordertoid;
    delete mainpixmap;
    delete playercustomizespinbox;
    delete []pushbutton_playeriamgelist;
    delete pushbutton_confirm;
    delete pushbutton_next;
    delete pushbutton_previous;
    delete pushbutton_back;
    delete playercustomizenameedit;
    delete scrollarea;
    delete ui;
}

void MyDialog::PushButton_Back_Clicked()
{
    accept();
}


void MyDialog::PushButton_Confirm_clicked()
{
    MyWidget *myintroductionwidget=new MyWidget(MyWidgetType::IntroductionWidget);
    MyDialog introductiondialog(MyDialogType::IntroductionDialog,(int)myintroductionwidget,0);
    introductiondialog.exec();
    delete myintroductionwidget;
}


void MyDialog:: PushButton_PlayerCustomize_Clicked()
{
    QPushButton*p=(QPushButton*)sender();
    for(int i=0;i<30;i++)
        if(p==pushbutton_playeriamgelist[i])
        {
            GLOBAL::ssmap["PlayerImage"+QString::number(playercustomizeindex)]=
                    GLOBAL::ssmap["Image"+QString::number(i)];
            update();
            return;
        }
   if(p==pushbutton_next)
   {
       GLOBAL::ssmap["PlayerName"+QString::number(playercustomizeindex)]=playercustomizenameedit->text();

       if(playercustomizeindex>=GLOBAL::simap["Players"]-2)
       {
           pushbutton_next->hide();
           pushbutton_confirm->show();
       }
       playercustomizeindex++;
       playercustomizenameedit->setText(GLOBAL::ssmap["PlayerName"+QString::number(playercustomizeindex)]);
        update();
        return;
   }
   if(p==pushbutton_back)//取消
   {
        this->close();
        return;
   }
   if(p==pushbutton_confirm)
   {
       if(playercustomizeindex==-1)
       {
           GLOBAL::simap["Players"]=playercustomizespinbox->value();
           playercustomizenameedit->setText(GLOBAL::ssmap["PlayerName0"]);

           playercustomizeindex=0;

           playercustomizenameedit->show();
           pushbutton_next->show();
           playercustomizespinbox->hide();
           pushbutton_confirm->hide();
           pushbutton_previous->show();

           move(x()-width()/2,y()-height()/2);
           setFixedSize(this->width()*2,this->height()*2);

           const int width=this->width(),height=this->height();
           pushbutton_back->setGeometry(width/11,height/12*11-width/18,width/12,width/18);
           pushbutton_confirm->setGeometry(width/24*19,height/12*11-width/18,width/9,width/18);

           for(int i=0;i<30;i++)pushbutton_playeriamgelist[i]->show();

           update();
       }
       else
       {
           GLOBAL::ssmap["PlayerName"+QString::number(playercustomizeindex)]=playercustomizenameedit->text();;
           confirm=true;
           GLOBAL::mainwindow->hide();
           this->close();//开始游戏
       }
        return;
   }
   if(p==pushbutton_previous)
   {
       GLOBAL::ssmap["PlayerName"+QString::number(playercustomizeindex)]=playercustomizenameedit->text();;
       if(playercustomizeindex==0)
       {
           pushbutton_next->hide();
           pushbutton_previous->hide();
           pushbutton_confirm->show();
           playercustomizespinbox->show();
           playercustomizenameedit->hide();

           move(x()+width()/4,y()+height()/4);
           setFixedSize(this->width()/2,this->height()/2);
           const int width=this->width(),height=this->height();
           pushbutton_back->setGeometry(width/12,height*5/6-width/20,width/4,width/10);
           pushbutton_confirm->setGeometry(width*2/3,height*5/6-width/20,width/4,width/10);
           for(int i=0;i<30;i++)pushbutton_playeriamgelist[i]->hide();
       }
       else
       if(playercustomizeindex==5)
       {
            pushbutton_confirm->hide();
            pushbutton_next->show();
       }
       playercustomizeindex--;
       playercustomizenameedit->setText(GLOBAL::ssmap["PlayerName"+QString::number(playercustomizeindex)]);
       update();
       return;
   }

}

void MyDialog::closeEvent(QCloseEvent *)
{
    if(type==MyDialogType::Bidding)
    {
        arg1=biddingprice;//记录竞价价格
        arg2=owningplayerid;//记录获胜的玩家id
    }
    if(confirm)accept();
    else
    reject();
}

void MyDialog::keyPressEvent(QKeyEvent *event)
{
    if(type==MyDialogType::PlayerCustomize)
    {
        switch(event->key())
        {
        case Qt::Key_Return:
        case Qt::Key_Enter:{ event->ignore();break;}
        }
    }
}

void MyDialog::PushButton_Bidding_Clicked()
{
    QPushButton*pushedbutton=(QPushButton*)sender();
    if(pushedbutton==pushbutton_back)
    {
        biddingplayernum--;
        isplayerbidding[biddingplayerordertoid[biddingorder]]=false;
        if(owningplayerid==biddingplayerordertoid[biddingorder])
        {
            //查找下一个有资格的玩家
            int biddingordertemp=biddingorder+1;
            if(biddingordertemp>=GLOBAL::gamemainwidget->playernum)biddingordertemp=0;
            while(isplayerbidding[biddingplayerordertoid[biddingordertemp]]==false
                  ||(GLOBAL::gamemainwidget->players[biddingplayerordertoid[biddingordertemp]]->isfailed==true))
            {
                biddingordertemp++;
                if(biddingordertemp>=(GLOBAL::gamemainwidget->playernum))biddingordertemp=0;
            }
            owningplayerid=biddingplayerordertoid[biddingordertemp];
        }
    }
    else
    if(pushedbutton==pushbutton_confirm)
    {
        biddingprice=biddingspinbox->value();
        owningplayerid=biddingplayerordertoid[biddingorder];
    }
    pushbutton_back->setEnabled(false);
    pushbutton_confirm->setEnabled(false);
    biddingtimercounter=1;
    isbiddingplayeroperated=true;
}

void MyDialog::BiddingTurns()
{
    if(biddingtimercounter)
        biddingtimercounter--;
    else
    {
        //到时未操作玩家默认放弃
        if(isbiddingplayeroperated==false)
        {
            biddingplayernum--;
            isplayerbidding[biddingplayerordertoid[biddingorder]]=false;
            if(owningplayerid==biddingplayerordertoid[biddingorder])
            {
                //查找下一个有资格的玩家
                int biddingordertemp=biddingorder+1;
                if(biddingordertemp>=GLOBAL::gamemainwidget->playernum)biddingordertemp=0;
                while(isplayerbidding[biddingplayerordertoid[biddingordertemp]]==false
                      ||(GLOBAL::gamemainwidget->players[biddingplayerordertoid[biddingordertemp]]->isfailed==true))
                {
                    biddingordertemp++;
                    if(biddingordertemp>=(GLOBAL::gamemainwidget->playernum))biddingordertemp=0;
                }
                owningplayerid=biddingplayerordertoid[biddingordertemp];
            }
        }
        if(biddingplayernum>1)
        {
            //如果当前轮到的玩家已经失败或者已经放弃则继续循环
            biddingorder++;
            if(biddingorder>=GLOBAL::gamemainwidget->playernum)biddingorder=0;
            while(isplayerbidding[biddingplayerordertoid[biddingorder]]==false
                  ||(GLOBAL::gamemainwidget->players[biddingplayerordertoid[biddingorder]]->isfailed==true))
            {
                biddingorder++;
                if(biddingorder>=(GLOBAL::gamemainwidget->playernum))biddingorder=0;
            }

            biddingtimercounter=biddingtimelimit;
            isbiddingplayeroperated=false;
        }
        else
        {
            timer->stop();

            confirm=true;//返回
            this->close();
        }

        Player *player=GLOBAL::gamemainwidget->players[biddingplayerordertoid[biddingorder]];
        if(player->cash>=biddingprice*26/25+10)
        {
            pushbutton_confirm->setEnabled(true);
            biddingspinbox->setRange(biddingprice*26/25+10,player->cash);
            biddingslider->setRange(biddingprice*26/25+10,player->cash);
        }
        else
        {
            pushbutton_confirm->setEnabled(false);
            biddingspinbox->setRange(biddingprice*26/25+10,biddingprice*26/25);
            biddingslider->setRange(biddingprice*26/25+10,biddingprice*26/25);
        }
        biddingspinbox->setValue(biddingprice*26/25);
        pushbutton_back->setEnabled(true);
    }
    update();
}

void MyDialog::VolumeSliderValueChange(int value)
{
    GLOBAL::mainwindow->musicsplayer->setVolume(value);
    GLOBAL::simap["MusicVolume"]=value;
}
