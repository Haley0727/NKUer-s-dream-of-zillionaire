#include "mywidget.h"
#include "ui_mywidget.h"
#include "global.h"


#ifdef DEBUG
static void LYL232BUGS()
{
    LYL232::bugs+=11;
    LYL232::bugsfixed+=11;
}
void LYL232::mywidgetcpp()
{
    LYL232BUGS();
}
#endif

class Block;
class AvailableBlock;

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
}

MyWidget::~MyWidget()
{
    delete scrollwidget_l;
    delete scrollwidget_r;
    delete spinbox_l;
    delete spinbox_r;
    delete slider_l;
    delete slider_r;
    delete scrollarea_l;
    delete scrollarea_r;
    delete checkboxes_l;
    delete checkboxes_r;
    delete pushbutton_accept;
    delete pushbutton_cancle;
    delete mainpixmap;
    delete ui;
}

MyWidget::MyWidget(MyWidgetType atype,int a1,int a2) :
    type(atype),arg1(a1),arg2(a2),ui(new Ui::MyWidget)
{

    ui->setupUi(this);
    const int width=GLOBAL::simap["ResolutionWidth"]*2/3,
            height=GLOBAL::simap["ResolutionHeight"]*2/3;
    resize(width,height);
    setFixedSize(width,height);
    pushbutton_accept=NULL;
    pushbutton_cancle=NULL;
    scrollarea_l=NULL;
    scrollarea_r=NULL;

    checkboxes_l=NULL;
    checkboxes_r=NULL;

    spinbox_l=NULL;
    spinbox_r=NULL;

    slider_l=NULL;
    slider_r=NULL;

    mainpixmap=NULL;

    scrollwidget_l=NULL;
    scrollwidget_r=NULL;

    GLOBAL::piiimap[PII((int)this,0)]=0;
    switch(type)
    {
        case MyWidgetType::Trading:
        {
            pushbutton_accept=new QPushButton(this);
            pushbutton_cancle=new QPushButton(this);

            scrollarea_l=new QScrollArea(this);
            scrollarea_r=new QScrollArea(this);

            checkboxes_l=new QVector<QCheckBox*>;
            checkboxes_r=new QVector<QCheckBox*>;

            spinbox_l=new QSpinBox(this);
            spinbox_r=new QSpinBox(this);

            slider_l=new QSlider(this);
            slider_r=new QSlider(this);

            scrollwidget_l=new QWidget;
            scrollwidget_r=new QWidget;

            mainpixmap=new QPixmap(width,height);

            if(!pushbutton_accept||!pushbutton_cancle||
                    !scrollarea_l||!scrollarea_r||
                    !checkboxes_l||!checkboxes_r||
                    !spinbox_l||!spinbox_r||
                    !slider_l||!slider_r||
                    !mainpixmap||
                    !scrollwidget_l||!scrollwidget_r
                    )
                GLOBAL::Gaming=false;
            else
            {
                    setWindowTitle("交易");

                    QFont font("微软雅黑",width*3/128,QFont::Bold,false);

                    QPainter painter(mainpixmap);

                    mainpixmap->fill(Qt::white);

                    painter.setFont(font);
                    painter.drawText(width*3/16,height/12,GLOBAL::gamemainwidget->players[arg1]->name);
                    painter.drawText(width*3/4,height/12,GLOBAL::gamemainwidget->players[arg2]->name);

                    font.setPointSize(width*3/256);
                    painter.setFont(font);
                    painter.drawText(width*3/16,height/6,tr("区块交换给对方"));
                    painter.drawText(width*3/4,height/6,tr("区块交换给对方"));
                    {
                        QPixmap pixmap;

                        pixmap.load(GLOBAL::ssmap["Trade"]);

                        pixmap.scaled(width/8,height/3,Qt::IgnoreAspectRatio);
                        painter.drawPixmap(width/2-width/16,height*5/12-height/6,width/8,height/3,pixmap);

                        pixmap.load(GLOBAL::ssmap["PlayerImage"+QString::number(arg1)]);
                        pixmap.scaled(width/10,width/10,Qt::IgnoreAspectRatio);
                        painter.drawPixmap(width/16,height/128,width/8,width/8,pixmap);

                        pixmap.load(GLOBAL::ssmap["PlayerImage"+QString::number(arg2)]);
                        pixmap.scaled(width/10,width/10,Qt::IgnoreAspectRatio);
                        painter.drawPixmap(width*7/12,height/128,width/8,width/8,pixmap);
                    }

                    font.setPointSize(width*3/192);
                    painter.setFont(font);
                    painter.drawText(width/12,height*2/3,"现金交换给对方");
                    painter.drawText(width*7/12,height*2/3,"现金交换给对方");

                    pushbutton_accept->setGeometry(width/4,height/8*7,width/4,height/16);
                    pushbutton_accept->setFont(font);
                    pushbutton_accept->setStyleSheet(GLOBAL::ssmap["PushButtonStyleSheet1"]);//鼠标按下的色彩
                    pushbutton_accept->setText("接受");

                   pushbutton_cancle->setGeometry(width/8*5,height/8*7,width/4,height/16);
                   pushbutton_cancle->setFont(font);
                   pushbutton_cancle->setStyleSheet(GLOBAL::ssmap["PushButtonStyleSheet1"]);//鼠标按下的色彩
                   pushbutton_cancle->setText("取消");

                  connect(pushbutton_cancle,SIGNAL(clicked()),this,SLOT(Cancle_clicked()));
                  connect(pushbutton_accept,SIGNAL(clicked()),this,SLOT(Accept_clicked()));


                  slider_l->setGeometry(width/12,height*19/24,width/4,height/24);
                  slider_l->setRange(0,GLOBAL::gamemainwidget->players[arg1]->cash);
                  slider_l->setOrientation(Qt::Horizontal);
                  slider_r->setGeometry(width*7/12,height*19/24,width/4,height/24);
                  slider_r->setRange(0,GLOBAL::gamemainwidget->players[arg2]->cash);
                  slider_r->setOrientation(Qt::Horizontal);

                  spinbox_l->setGeometry(width/12,height*17/24,width/8,height/16);
                  spinbox_l->setRange(0,GLOBAL::gamemainwidget->players[arg1]->cash);
                  spinbox_r->setGeometry(width*7/12,height*17/24,width/8,height/16);
                  spinbox_r->setRange(0,GLOBAL::gamemainwidget->players[arg2]->cash);

                  connect(slider_l,SIGNAL(valueChanged(int)),spinbox_l,SLOT(setValue(int)));
                  connect(spinbox_l,SIGNAL(valueChanged(int)),slider_l,SLOT(setValue(int)));

                  connect(slider_r,SIGNAL(valueChanged(int)),spinbox_r,SLOT(setValue(int)));
                  connect(spinbox_r,SIGNAL(valueChanged(int)),slider_r,SLOT(setValue(int)));

                  scrollarea_l->setMaximumSize(width*3/8,height*11/24);
                  scrollarea_r->setMaximumSize(width*3/8,height*11/24);

                  Block** blocks=GLOBAL::gamemainwidget->blocks;
                  for(int i=0;i<40;i++)
                  {
                        if(blocks[i]->type==BlockType::Available)
                        {
                            if(((AvailableBlock*)blocks[i])->owner!=NULL)
                            {
                                if(((AvailableBlock*)blocks[i])->owner->id==arg1)
                                {
                                    QCheckBox* checkbox=new QCheckBox(scrollwidget_l);
                                    GLOBAL::piiimap[PII((int)checkbox,0)]=i;
                                    checkboxes_l->push_back(checkbox);
                                    checkbox->setText(blocks[i]->name);
                                    checkbox->setChecked(false);
                                    checkbox->hide();
                                }
                                else
                                if(((AvailableBlock*)blocks[i])->owner->id==arg2)
                                {
                                    QCheckBox* checkbox=new QCheckBox(scrollwidget_r);
                                    GLOBAL::piiimap[PII((int)checkbox,0)]=i;
                                    checkbox->setText(blocks[i]->name);
                                    checkbox->setChecked(false);
                                    checkboxes_r->push_back(checkbox);
                                    checkbox->hide();
                                }
                            }

                        }
                  }
                 scrollarea_l->setGeometry(width/24,height*5/24,width*3/8,height/3);
                 scrollarea_r->setGeometry(width*7/12,height*5/24,width*3/8,height/3);

                 QVector<QCheckBox*>::iterator iter=checkboxes_l->begin();
                 int rowcount=0,linecount=0;
                 for(;iter!=checkboxes_l->end();iter++)
                 {
                     if(rowcount>3){rowcount=0;linecount++;}
                     (*iter)->setGeometry(rowcount*width/12,height/6*linecount,width/12,height/6);
                     (*iter)->show();
                     rowcount++;
                 }

                 scrollwidget_l->resize(width/3,height/6*(linecount+1));
                 scrollarea_l->setWidget(scrollwidget_l);
                 scrollarea_l->resize(width*11/24,height/3);
                 rowcount=0,linecount=0;
                 iter=checkboxes_r->begin();
                 for(;iter!=checkboxes_r->end();iter++)
                 {
                     if(rowcount>3){rowcount=0;linecount++;}
                     (*iter)->setGeometry(rowcount*width/12,height/6*linecount,width/12,height/6);
                     (*iter)->show();
                     rowcount++;
                 }

                 scrollwidget_r->resize(width/3,height/6*(linecount+1));
                 scrollarea_r->setWidget(scrollwidget_r);
                 scrollarea_r->resize(width*11/24,height/3);
            }

            break;
        }
        case MyWidgetType::Purchasing:
        {
            //此处arg1为区块id,arg2为玩家id
            pushbutton_accept=new QPushButton(this);
            pushbutton_cancle=new QPushButton(this);
            if(!pushbutton_accept||!pushbutton_cancle)
                GLOBAL::Gaming=false;
            else
            {
                const int width=GLOBAL::simap["ResolutionWidth"]/3,
                        height=GLOBAL::simap["ResolutionHeight"]/2;
                resize(width,height);
                setFixedSize(width,height);
                setWindowTitle(tr("开发"));

                QFont font("微软雅黑",width*11/320,QFont::Bold,false);

                pushbutton_accept->setGeometry(width*2/3,height/3,width/4,width/6);
                pushbutton_accept->setFont(font);
                pushbutton_accept->setStyleSheet(GLOBAL::ssmap["PushButtonStyleSheet1"]);
                pushbutton_accept->setText("承包");

                   if(GLOBAL::gamemainwidget->players[arg2]->cash <
                       (((AvailableBlock*)  GLOBAL::gamemainwidget->blocks[arg1])->purchaseprice))
                        pushbutton_accept->setEnabled(false);

                   pushbutton_cancle->setGeometry(width*2/3,height*7/12,width/4,width/6);
                   pushbutton_cancle->setFont(font);
                   pushbutton_cancle->setStyleSheet(GLOBAL::ssmap["PushButtonStyleSheet1"]);//鼠标按下的色彩
                  pushbutton_cancle->setText("竞价转让");

                  connect(pushbutton_accept,SIGNAL(clicked()),this,SLOT(Accept_clicked()));
                  connect(pushbutton_cancle,SIGNAL(clicked()),this,SLOT(Cancle_clicked()));

                update();

              }


            break;
        }
        case MyWidgetType::DDL:
        {
            const int width=GLOBAL::simap["ResolutionWidth"]/2,
                    height=GLOBAL::simap["ResolutionHeight"]/2;
                resize(width,height);
             setFixedSize(width,height);

             pushbutton_accept=new QPushButton(this);
             pushbutton_cancle=new QPushButton(this);
             if(pushbutton_accept&&pushbutton_cancle)
             {
                setWindowTitle(tr("图书馆"));
                QFont font("微软雅黑",width*3/128,QFont::Bold,false);

                {
                    QPixmap pixmap;
                    pixmap.load(GLOBAL::ssmap["Deadline_Widget"]);
                    pixmap=pixmap.scaled(width*7/16,width*3/8,Qt::IgnoreAspectRatio);
                    QLabel*label=new QLabel(this);
                    label->setGeometry(width/32,width/8,width*7/16,width*3/8);
                    label->setPixmap(pixmap);
                    label->show();
                    label=new QLabel(this);

                    QFont font("微软雅黑",width/40,QFont::Bold,false);
                    label->setFont(font);
                    label->setText(tr("加油！还剩%1轮").arg(GLOBAL::gamemainwidget->playerfornow->ddls));
                    label->setGeometry(width/32,width/32,width*7/16,width/20);

                }

                pushbutton_cancle->setGeometry(width/2,height*5/16,width*7/16,height/8);
                pushbutton_cancle->setFont(font);
                pushbutton_cancle->setStyleSheet(GLOBAL::ssmap["PushButtonStyleSheet1"]);
                pushbutton_cancle->setText("灵感乍现：掷出同点");


                pushbutton_accept->setGeometry(width/2,height*9/16,width*7/16,height/8);
                pushbutton_accept->setFont(font);
                pushbutton_accept->setStyleSheet(GLOBAL::ssmap["PushButtonStyleSheet1"]);
                pushbutton_accept->setText("请人帮忙：支付100");

                arg1=0;
                connect(pushbutton_accept,SIGNAL(clicked()),this,SLOT(Accept_clicked()));
                connect(pushbutton_cancle,SIGNAL(clicked()),this,SLOT(Cancle_clicked()));
             }
             break;
        }
        case MyWidgetType::IntroductionWidget:
        {
            setFixedSize(GLOBAL::simap["ResolutionWidth"]/2,
                    GLOBAL::simap["ResolutionHeight"]*4);
            update();
            break;
        }
    }
}

void MyWidget::Accept_clicked()
{
    switch(type)
    {
    case MyWidgetType::Trading:
    {
        GLOBAL::piiimap[PII((int)this,0)]=1;
        close();
        break;
    }
    case MyWidgetType::Purchasing:
    {
        GLOBAL::piiimap[PII((int)this,0)]=1;
        close();
        break;
    }
    case MyWidgetType::DDL:
    {
        arg1=1;
        close();
        break;
    }
    default:break;
    }

}

void MyWidget::Cancle_clicked()
{
    switch(type)
    {
    case MyWidgetType::Trading:
    {
    GLOBAL::piiimap[PII((int)this,0)]=0;
    close();
    break;
    }
    case MyWidgetType::Purchasing:
    {
        GLOBAL::piiimap[PII((int)this,0)]=0;
        close();
        break;
    }
    case MyWidgetType::DDL:
    {
        arg1=0;
        close();
        break;
    }
    default:break;
    }
}

void MyWidget::closeEvent(QCloseEvent*)
{
    if(type!=MyWidgetType::IntroductionWidget)
    GLOBAL::gamemainwidget->MyWidgetReturn(this);
}

void MyWidget::paintEvent(QPaintEvent*)
{
    const int width=this->width(),height=this->height();
    switch(type)
    {
    case MyWidgetType::Purchasing:
    {
        QPixmap pixmap(width,height);
        pixmap.fill(Qt::white);
        QPainter painter(&pixmap),mainpainter(this);
        QPen pen;
        QFont font("微软雅黑",height/10,QFont::Bold,false);
        font.setPointSize(width*3/64);
        painter.setFont(font);
        pen.setColor(Qt::black);
        painter.setPen(pen);
        painter.drawText(width/10,height*3/20,GLOBAL::gamemainwidget->blocks[arg1]->name+
                        "：¥"+QString::number(
                             ((AvailableBlock*)GLOBAL::gamemainwidget->blocks[arg1])->purchaseprice));

        if(((AvailableBlock*)GLOBAL::gamemainwidget->blocks[arg1])->type==AvailableBlockType::Buildable)
        {
            BuildableBlock* blockp=(BuildableBlock*)GLOBAL::gamemainwidget->blocks[arg1];
            font.setPointSize(width*9/320);
            painter.setFont(font);
            painter.drawText(width/10,height/20*5,"基础收费：¥"+
                             QString::number(blockp->chargebase));
            for(int i=1;i<=blockp->maxlevel;i++)
            painter.drawText(width/10,height/20*(7+2*(i-1)),QString("level%1：¥%2").arg(i).arg(
                             blockp->chargebase+blockp->chargeperlevel*i));
        }
        else
        {
            font.setPointSize(width*9/320);
            painter.setFont(font);
            painter.drawText(width/10,height/20*5,"快速旅行");
            painter.drawText(width/10,height/20*7,"1车站 ¥25");
            painter.drawText(width/10,height/20*9,"2车站 ¥50");
            painter.drawText(width/10,height/20*11,"3车站 ¥100");
            painter.drawText(width/10,height/20*13,"4车站 ¥200");
        }
        mainpainter.drawPixmap(0,0,pixmap);
        break;
    }
    case MyWidgetType::Trading:
    {
        QPainter mainpainter(this);

        mainpainter.drawPixmap(0,0,*mainpixmap);
        break;
    }
    case MyWidgetType::IntroductionWidget:
    {
        QPainter painter(this);
        painter.drawPixmap(0,0,width,height,*(GLOBAL::IntroductionPixmap));
    }
    default:break;
    }
}
