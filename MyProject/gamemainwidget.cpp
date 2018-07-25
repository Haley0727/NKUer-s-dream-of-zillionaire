#include "gamemainwidget.h"
#include "ui_gamemainwidget.h"
#include<global.h>
#include "Classes.h"

typedef std::pair<int,int> PII;
typedef QMap<QString,QString> SSMAP;
typedef QMap<QString,int> SIMAP;
typedef QMap<PII,int> PIIIMAP;

#ifdef DEBUG
static void LYL232BUGS()
{
    LYL232::bugs+=61;
    LYL232::bugsfixed+=61;
}
void LYL232::gamemainwidgetcpp()
{
    LYL232BUGS();
}
#endif
GameMainWidget::GameMainWidget(QWidget *parent) :
    QWidget(parent),
    width(GLOBAL::simap["ResolutionWidth"]),
    height(GLOBAL::simap["ResolutionHeight"]),
    playerroleimagewidth(width/20),
    playerlistimagewdith(width/18),
    playernum(GLOBAL::simap["Players"]),blocksmargin(width*3/1600),
    playeractivenum(playernum),
    ui(new Ui::GameMainWidget)
{
    ui->setupUi(this);

    //没有学过try throw catch。。。。。不会用
    //所以就用C语言的比较愚蠢（应该说我的方法比较愚蠢，尽管我不愿意承认）的异常处理机制
    //变量申请
    {
        cardback=cardfront=cardbacktemp=cardfronttemp=NULL;
        counttimer=NULL;

        cardreversaltimer=NULL;

        dicerefreshtimer=NULL;
        Dices=NULL;

        fontdefault=NULL;

        GameBackground=NULL;
        GameBackgrounddarker=NULL;

        hinttimer=NULL;
        hintlabel=hintrolelabel=NULL;

        labelmovestagetimer=NULL;
        Levels=NULL;

        mywidget=NULL;
        mydialog=NULL;

        pushbutton_build=pushbutton_build_cancle=NULL;
        pushbutton_dice=NULL;
        pushbutton_failed_confirm=NULL;
        pushbutton_menu=NULL;
        pushbutton_quit=NULL;
        pushbutton_sell=NULL;
        pushbutton_sell_cancle=NULL;
        pushbutton_stagefinish=NULL;
        pushbutton_stagefinish_failed_alternate=NULL;
        pushbutton_trade=NULL;
        pushbutton_tradeplayerlist=NULL;
        pushbutton_travel=NULL;pushbutton_travel_cancle=NULL;
        pushbutton_chat_widget_show=NULL;

        playertravelstagetimer=NULL;

        stagelabel=NULL;

        counttimer=new QTimer(this);//每秒钟计时器
        dicerefreshtimer=new QTimer(this);//骰子刷新计时器
        labelmovestagetimer=new QTimer(this);//玩家角色移动阶段计时器
        playertravelstagetimer=new QTimer(this);
        cardreversaltimer=new QTimer(this);
        hinttimer=new QTimer(this);

        hintlabel=new QLabel(this);
        hintrolelabel=new QLabel(this);

        pushbutton_menu=new QPushButton(this);
        pushbutton_quit=new QPushButton(this);
        pushbutton_dice=new QPushButton(this);
        pushbutton_trade=new QPushButton(this);
        pushbutton_stagefinish=new QPushButton(this);
        pushbutton_sell=new QPushButton(this);
        pushbutton_sell_cancle=new QPushButton(this);
        pushbutton_build=new QPushButton(this);
        pushbutton_build_cancle=new QPushButton(this);
        pushbutton_failed_confirm=new QPushButton(this);
        pushbutton_travel=new QPushButton(this);
        pushbutton_travel_cancle=new QPushButton(this);
        pushbutton_tradeplayerlist=new QPushButton*[6];
        pushbutton_chat_widget_show=new QPushButton(this);

        pushbutton_stagefinish_failed_alternate=pushbutton_stagefinish;

        stagelabel=new QLabel(this);

        cardback=new QImage;
        cardfront=new QImage;
        cardfronttemp=new QImage;
        cardbacktemp=new QImage;

        if(pushbutton_tradeplayerlist)
        {
            for(int i=0;i<6;i++)pushbutton_tradeplayerlist[i]=NULL;
            for(int i=0;i<playernum;i++)
                if((pushbutton_tradeplayerlist[i]=new QPushButton(this))==NULL)
                    GLOBAL::Gaming=false;
        }

        GameBackground=new QPixmap(width,height);
        GameBackgrounddarker=new QPixmap(width,height);

        Dices=new QPixmap[6];
        if(Dices)
        for(int i=0;i<6&&GLOBAL::Gaming;i++)
        {
            QPixmap pixmap;
            GLOBAL::Gaming=pixmap.load(GLOBAL::ssmap["Dices"+QString::number(i+1)]);
            Dices[i]=pixmap.scaled(width/16,width/16,Qt::IgnoreAspectRatio);
        }
        Levels =new QPixmap[5];
        if(Levels)
        for(int i=0;i<5&&GLOBAL::Gaming;i++)
             GLOBAL::Gaming=Levels[i].load(GLOBAL::ssmap["Level"+QString::number(i+1)]);

        //区块初始化
        {
            for(int i=0;i<40;i++)blocks[i]=NULL;
                //第一排
                if(GLOBAL::Gaming==false||
                        (blocks[0]=new SpecificBlock(
                                            SpecificBlockType::HelloWorld,"HelloWorld",
                                            QRect(width*1110/1600-blocksmargin,height*720/900-blocksmargin,
                                                  width*109/1600-2*blocksmargin,width*100/1600-2*blocksmargin),
                                                     0))==NULL)GLOBAL::Gaming=false;
                if(GLOBAL::Gaming==false||
                        (blocks[1]=new BuildableBlock("新北面馆",
                                                      QRect(width*1001/1600-blocksmargin,height*720/900-blocksmargin,
                                                            width*109/1600-2*blocksmargin,width*100/1600-2*blocksmargin),
                                                      1/*id*/,100/*price*/,50/*buildprice*/,
                                                      4/*maxlevel*/,5/*chargebase*/,50/*chargeperlevel*/))==NULL)GLOBAL::Gaming=false;
                if(GLOBAL::Gaming==false||
                        (blocks[2]=new BuildableBlock("花店",
                                                      QRect(width*892/1600-blocksmargin,height*720/900-blocksmargin,
                                                            width*109/1600-2*blocksmargin,width*100/1600-2*blocksmargin),
                                                      2/*id*/,115/*price*/,50/*buildprice*/,
                                                      4/*maxlevel*/,10/*chargebase*/,55/*chargeperlevel*/))==NULL)GLOBAL::Gaming=false;
                if(GLOBAL::Gaming==false||
                        (blocks[3]=new BuildableBlock("元和西饼",
                                                      QRect(width*783/1600-blocksmargin,height*720/900-blocksmargin,
                                                            width*109/1600-2*blocksmargin,width*100/1600-2*blocksmargin),
                                                      3/*id*/,130/*price*/,50/*buildprice*/,
                                                      4/*maxlevel*/,15/*chargebase*/,55/*chargeperlevel*/))==NULL)GLOBAL::Gaming=false;
                ((BuildableBlock*)(blocks[1]))->buildneed_f=((BuildableBlock*)(blocks[2]));
                ((BuildableBlock*)(blocks[1]))->buildneed_s=((BuildableBlock*)(blocks[3]));
                ((BuildableBlock*)(blocks[2]))->buildneed_f=((BuildableBlock*)(blocks[1]));
                ((BuildableBlock*)(blocks[2]))->buildneed_s=((BuildableBlock*)(blocks[3]));
                ((BuildableBlock*)(blocks[3]))->buildneed_f=((BuildableBlock*)(blocks[1]));
                ((BuildableBlock*)(blocks[3]))->buildneed_s=((BuildableBlock*)(blocks[2]));

                if(GLOBAL::Gaming==false||
                        (blocks[4]=new SpecificBlock(SpecificBlockType::LuckCard,"幸运卡牌",
                                                      QRect(width*674/1600-blocksmargin,height*720/900-blocksmargin,
                                                            width*109/1600-2*blocksmargin,width*100/1600-2*blocksmargin),
                                                      4/*id*/))==NULL)GLOBAL::Gaming=false;
                if(GLOBAL::Gaming==false||
                        (blocks[5]=new AvailableBlock(AvailableBlockType::BusStop,"永旺站",
                                                      QRect(width*565/1600-blocksmargin,height*720/900-blocksmargin,
                                                            width*109/1600-2*blocksmargin,width*100/1600-2*blocksmargin),
                                                      5/*id*/,200/*price*/))==NULL)GLOBAL::Gaming=false;
                if(GLOBAL::Gaming==false||
                        (blocks[6]=new SpecificBlock(SpecificBlockType::RandomEvent,"？？？？",
                                                      QRect(width*456/1600-blocksmargin,height*720/900-blocksmargin,
                                                            width*109/1600-2*blocksmargin,width*100/1600-2*blocksmargin),
                                                      6/*id*/))==NULL)GLOBAL::Gaming=false;


                if(GLOBAL::Gaming==false||
                        (blocks[7]=new BuildableBlock("修车铺",
                                                      QRect(width*347/1600-blocksmargin,height*720/900-blocksmargin,
                                                            width*109/1600-2*blocksmargin,width*100/1600-2*blocksmargin),
                                                      7/*id*/,145/*price*/,100/*buildprice*/,
                                                      4/*maxlevel*/,20/*chargebase*/,110/*chargeperlevel*/))==NULL)GLOBAL::Gaming=false;
                if(GLOBAL::Gaming==false||
                        (blocks[8]=new BuildableBlock("7-11",
                                                      QRect(width*238/1600-blocksmargin,height*720/900-blocksmargin,
                                                            width*109/1600-2*blocksmargin,width*100/1600-2*blocksmargin),
                                                      8/*id*/,160/*price*/,100/*buildprice*/,
                                                      4/*maxlevel*/,25/*chargebase*/,125/*chargeperlevel*/))==NULL)GLOBAL::Gaming=false;
                if(GLOBAL::Gaming==false||
                        (blocks[9]=new BuildableBlock("洗衣店",
                                                      QRect(width*129/1600-blocksmargin,height*720/900-blocksmargin,
                                                            width*109/1600-2*blocksmargin,width*100/1600-2*blocksmargin),
                                                      9/*id*/,175/*price*/,100/*buildprice*/,
                                                      4/*maxlevel*/,25/*chargebase*/,130/*chargeperlevel*/))==NULL)GLOBAL::Gaming=false;
                ((BuildableBlock*)(blocks[7]))->buildneed_f=((BuildableBlock*)(blocks[8]));
                ((BuildableBlock*)(blocks[7]))->buildneed_s=((BuildableBlock*)(blocks[9]));
                ((BuildableBlock*)(blocks[8]))->buildneed_f=((BuildableBlock*)(blocks[7]));
                ((BuildableBlock*)(blocks[8]))->buildneed_s=((BuildableBlock*)(blocks[9]));
                ((BuildableBlock*)(blocks[9]))->buildneed_f=((BuildableBlock*)(blocks[7]));
                ((BuildableBlock*)(blocks[9]))->buildneed_s=((BuildableBlock*)(blocks[8]));

                if(GLOBAL::Gaming==false||
                        (blocks[10]=new SpecificBlock(SpecificBlockType::Library,"图书馆",
                                                      QRect(width*20/1600-blocksmargin,height*720/900-blocksmargin,
                                                            109*width/1600-2*blocksmargin,100*height/900-2*blocksmargin),
                                                      10/*id*/))==NULL)GLOBAL::Gaming=false;

                if(GLOBAL::Gaming==false||
                        (blocks[11]=new BuildableBlock("泰达MSD",
                                                      QRect(width*20/1600-blocksmargin,height*656/900-blocksmargin,
                                                            109*width/1600-2*blocksmargin,64*height/900-2*blocksmargin),
                                                      11/*id*/,190/*price*/,125/*buildprice*/,
                                                      4/*maxlevel*/,30/*chargebase*/,170/*chargeperlevel*/))==NULL)GLOBAL::Gaming=false;
                if(GLOBAL::Gaming==false||
                        (blocks[12]=new BuildableBlock("星巴克",
                                                      QRect(width*20/1600-blocksmargin,height*592/900-blocksmargin,
                                                            109*width/1600-2*blocksmargin,64*height/900-2*blocksmargin),
                                                      12/*id*/,205/*price*/,125/*buildprice*/,
                                                      5/*maxlevel*/,35/*chargebase*/,175/*chargeperlevel*/))==NULL)GLOBAL::Gaming=false;
                ((BuildableBlock*)(blocks[11]))->buildneed_f=((BuildableBlock*)(blocks[12]));
                ((BuildableBlock*)(blocks[12]))->buildneed_f=((BuildableBlock*)(blocks[11]));

                if(GLOBAL::Gaming==false||
                        (blocks[13]=new SpecificBlock(SpecificBlockType::RandomEvent,"？？？？",
                                                      QRect(width*20/1600-blocksmargin,height*528/900-blocksmargin,
                                                            109*width/1600-2*blocksmargin,64*height/900-2*blocksmargin),
                                                      13/*id*/))==NULL)GLOBAL::Gaming=false;
                if(GLOBAL::Gaming==false||
                        (blocks[14]=new BuildableBlock("科技园",
                                                      QRect(width*20/1600-blocksmargin,height*464/900-blocksmargin,
                                                            109*width/1600-2*blocksmargin,64*height/900-2*blocksmargin),
                                                      14/*id*/,350/*price*/,125/*buildprice*/,
                                                      4/*maxlevel*/,35/*chargebase*/,180/*chargeperlevel*/))==NULL)GLOBAL::Gaming=false;
                if(GLOBAL::Gaming==false||
                        (blocks[15]=new AvailableBlock(AvailableBlockType::BusStop,"泰达站",
                                                      QRect(width*20/1600-blocksmargin,height*376/900-blocksmargin,
                                                            109*width/1600-2*blocksmargin,88*height/900-2*blocksmargin),
                                                      15/*id*/,200/*price*/))==NULL)GLOBAL::Gaming=false;
                if(GLOBAL::Gaming==false||
                        (blocks[16]=new SpecificBlock(SpecificBlockType::LuckCard,"幸运卡牌",
                                                      QRect(width*20/1600-blocksmargin,height*312/900-blocksmargin,
                                                            109*width/1600-2*blocksmargin,64*height/900-2*blocksmargin),
                                                      16/*id*/))==NULL)GLOBAL::Gaming=false;

                if(GLOBAL::Gaming==false||
                        (blocks[17]=new BuildableBlock("泰达足球场",
                                                      QRect(width*20/1600-blocksmargin,height*248/900-blocksmargin,
                                                            109*width/1600-2*blocksmargin,64*height/900-2*blocksmargin),
                                                      17/*id*/,235/*price*/,150/*buildprice*/,
                                                      4/*maxlevel*/,40/*chargebase*/,210/*chargeperlevel*/))==NULL)GLOBAL::Gaming=false;
                if(GLOBAL::Gaming==false||
                        (blocks[18]=new BuildableBlock("滨海广场",
                                                      QRect(width*20/1600-blocksmargin,height*184/900-blocksmargin,
                                                            109*width/1600-2*blocksmargin,64*height/900-2*blocksmargin),
                                                      18/*id*/,250/*price*/,150/*buildprice*/,
                                                      4/*maxlevel*/,40/*chargebase*/,215/*chargeperlevel*/))==NULL)GLOBAL::Gaming=false;
                if(GLOBAL::Gaming==false||
                        (blocks[19]=new BuildableBlock("泰丰公园",
                                                      QRect(width*20/1600-blocksmargin,height*120/900-blocksmargin,
                                                            109*width/1600-2*blocksmargin,64*height/900-2*blocksmargin),
                                                      19/*id*/,265/*price*/,150/*buildprice*/,
                                                      4/*maxlevel*/,45/*chargebase*/,220/*chargeperlevel*/))==NULL)GLOBAL::Gaming=false;
                ((BuildableBlock*)(blocks[17]))->buildneed_f=((BuildableBlock*)(blocks[18]));
                ((BuildableBlock*)(blocks[17]))->buildneed_s=((BuildableBlock*)(blocks[19]));
                ((BuildableBlock*)(blocks[18]))->buildneed_f=((BuildableBlock*)(blocks[17]));
                ((BuildableBlock*)(blocks[18]))->buildneed_s=((BuildableBlock*)(blocks[19]));
                ((BuildableBlock*)(blocks[19]))->buildneed_f=((BuildableBlock*)(blocks[17]));
                ((BuildableBlock*)(blocks[19]))->buildneed_s=((BuildableBlock*)(blocks[18]));

                if(GLOBAL::Gaming==false||
                        (blocks[20]=new SpecificBlock(SpecificBlockType::Hospital,"医院",
                                                      QRect(width*20/1600-blocksmargin,height*20/900-blocksmargin,
                                                            109*width/1600-2*blocksmargin,100*height/900-2*blocksmargin),
                                                      20/*id*/))==NULL)GLOBAL::Gaming=false;

                if(GLOBAL::Gaming==false||
                        (blocks[21]=new BuildableBlock("动物公园",
                                                      QRect(width*129/1600-blocksmargin,height*20/900-blocksmargin,
                                                            109*width/1600-2*blocksmargin,100*height/900-2*blocksmargin),
                                                      21/*id*/,280/*price*/,175/*buildprice*/,
                                                      4/*maxlevel*/,50/*chargebase*/,245/*chargeperlevel*/))==NULL)GLOBAL::Gaming=false;
                if(GLOBAL::Gaming==false||
                        (blocks[22]=new BuildableBlock("水上公园",
                                                      QRect(width*238/1600-blocksmargin,height*20/900-blocksmargin,
                                                            109*width/1600-2*blocksmargin,100*height/900-2*blocksmargin),
                                                      22/*id*/,295/*price*/,175/*buildprice*/,
                                                      4/*maxlevel*/,55/*chargebase*/,250/*chargeperlevel*/))==NULL)GLOBAL::Gaming=false;
                if(GLOBAL::Gaming==false||
                        (blocks[23]=new BuildableBlock("古城区",
                                                      QRect(width*347/1600-blocksmargin,height*20/900-blocksmargin,
                                                            109*width/1600-2*blocksmargin,100*height/900-2*blocksmargin),
                                                      23/*id*/,310/*price*/,175/*buildprice*/,
                                                      5/*maxlevel*/,60/*chargebase*/,255/*chargeperlevel*/))==NULL)GLOBAL::Gaming=false;
                ((BuildableBlock*)(blocks[21]))->buildneed_f=((BuildableBlock*)(blocks[22]));
                ((BuildableBlock*)(blocks[21]))->buildneed_s=((BuildableBlock*)(blocks[23]));
                ((BuildableBlock*)(blocks[22]))->buildneed_f=((BuildableBlock*)(blocks[21]));
                ((BuildableBlock*)(blocks[22]))->buildneed_s=((BuildableBlock*)(blocks[23]));
                ((BuildableBlock*)(blocks[23]))->buildneed_f=((BuildableBlock*)(blocks[21]));
                ((BuildableBlock*)(blocks[23]))->buildneed_s=((BuildableBlock*)(blocks[22]));

                if(GLOBAL::Gaming==false||
                        (blocks[24]=new SpecificBlock(SpecificBlockType::LuckCard,"幸运卡牌",
                                                      QRect(width*456/1600-blocksmargin,height*20/900-blocksmargin,
                                                            109*width/1600-2*blocksmargin,100*height/900-2*blocksmargin),
                                                      24/*id*/))==NULL)GLOBAL::Gaming=false;
                if(GLOBAL::Gaming==false||
                        (blocks[25]=new AvailableBlock(AvailableBlockType::BusStop,"天塔站",
                                                      QRect(width*565/1600-blocksmargin,height*20/900-blocksmargin,
                                                            109*width/1600-2*blocksmargin,100*height/900-2*blocksmargin),
                                                      25/*id*/,200/*price*/))==NULL)GLOBAL::Gaming=false;
                if(GLOBAL::Gaming==false||
                        (blocks[26]=new SpecificBlock(SpecificBlockType::RandomEvent,"？？？？",
                                                      QRect(width*674/1600-blocksmargin,height*20/900-blocksmargin,
                                                            109*width/1600-2*blocksmargin,100*height/900-2*blocksmargin),
                                                      26/*id*/))==NULL)GLOBAL::Gaming=false;

                if(GLOBAL::Gaming==false||
                        (blocks[27]=new BuildableBlock("五大道",
                                                      QRect(width*783/1600-blocksmargin,height*20/900-blocksmargin,
                                                            109*width/1600-2*blocksmargin,100*height/900-2*blocksmargin),
                                                      27/*id*/,325/*price*/,190/*buildprice*/,
                                                      5/*maxlevel*/,65/*chargebase*/,260/*chargeperlevel*/))==NULL)GLOBAL::Gaming=false;
                if(GLOBAL::Gaming==false||
                        (blocks[28]=new BuildableBlock("天津之眼",
                                                      QRect(width*892/1600-blocksmargin,height*20/900-blocksmargin,
                                                            109*width/1600-2*blocksmargin,100*height/900-2*blocksmargin),
                                                      28/*id*/,340/*price*/,190/*buildprice*/,
                                                      5/*maxlevel*/,65/*chargebase*/,255/*chargeperlevel*/))==NULL)GLOBAL::Gaming=false;
                if(GLOBAL::Gaming==false||
                        (blocks[29]=new BuildableBlock("意风区",
                                                      QRect(width*1001/1600-blocksmargin,height*20/900-blocksmargin,
                                                            109*width/1600-2*blocksmargin,100*height/900-2*blocksmargin),
                                                      29/*id*/,355/*price*/,190/*buildprice*/,
                                                      4/*maxlevel*/,70/*chargebase*/,275/*chargeperlevel*/))==NULL)GLOBAL::Gaming=false;
                ((BuildableBlock*)(blocks[27]))->buildneed_f=((BuildableBlock*)(blocks[28]));
                ((BuildableBlock*)(blocks[27]))->buildneed_s=((BuildableBlock*)(blocks[29]));
                ((BuildableBlock*)(blocks[28]))->buildneed_f=((BuildableBlock*)(blocks[27]));
                ((BuildableBlock*)(blocks[28]))->buildneed_s=((BuildableBlock*)(blocks[29]));
                ((BuildableBlock*)(blocks[29]))->buildneed_f=((BuildableBlock*)(blocks[27]));
                ((BuildableBlock*)(blocks[29]))->buildneed_s=((BuildableBlock*)(blocks[28]));

                if(GLOBAL::Gaming==false||
                        (blocks[30]=new SpecificBlock(SpecificBlockType::Deadline,"DDL警告",
                                                      QRect(width*1110/1600-blocksmargin,height*20/900-blocksmargin,
                                                            109*width/1600-2*blocksmargin,100*height/900-2*blocksmargin),
                                                      30/*id*/))==NULL)GLOBAL::Gaming=false;

                if(GLOBAL::Gaming==false||
                        (blocks[31]=new BuildableBlock("健身房",
                                                      QRect(width*1110/1600-blocksmargin,height*120/900-blocksmargin,
                                                            109*width/1600-2*blocksmargin,64*height/900-2*blocksmargin),
                                                      31/*id*/,500/*price*/,250/*buildprice*/,
                                                      5/*maxlevel*/,80/*chargebase*/,300/*chargeperlevel*/))==NULL)GLOBAL::Gaming=false;

                if(GLOBAL::Gaming==false||
                        (blocks[32]=new SpecificBlock(SpecificBlockType::RandomEvent,"？？？？",
                                                      QRect(width*1110/1600-blocksmargin,height*184/900-blocksmargin,
                                                            109*width/1600-2*blocksmargin,64*height/900-2*blocksmargin),
                                                      32/*id*/))==NULL)GLOBAL::Gaming=false;

                if(GLOBAL::Gaming==false||
                        (blocks[33]=new BuildableBlock("浴园",
                                                      QRect(width*1110/1600-blocksmargin,height*248/900-blocksmargin,
                                                            109*width/1600-2*blocksmargin,64*height/900-2*blocksmargin),
                                                      33/*id*/,385/*price*/,240/*buildprice*/,
                                                      5/*maxlevel*/,75/*chargebase*/,285/*chargeperlevel*/))==NULL)GLOBAL::Gaming=false;
                if(GLOBAL::Gaming==false||
                        (blocks[34]=new BuildableBlock("马蹄湖",
                                                      QRect(width*1110/1600-blocksmargin,height*312/900-blocksmargin,
                                                            109*width/1600-2*blocksmargin,64*height/900-2*blocksmargin),
                                                      34/*id*/,400/*price*/,240/*buildprice*/,
                                                      4/*maxlevel*/,75/*chargebase*/,290/*chargeperlevel*/))==NULL)GLOBAL::Gaming=false;
                ((BuildableBlock*)(blocks[33]))->buildneed_f=((BuildableBlock*)(blocks[34]));
                ((BuildableBlock*)(blocks[34]))->buildneed_f=((BuildableBlock*)(blocks[33]));

                if(GLOBAL::Gaming==false||
                        (blocks[35]=new AvailableBlock(AvailableBlockType::BusStop,"西南村站",
                                                      QRect(width*1110/1600-blocksmargin,height*376/900-blocksmargin,
                                                            109*width/1600-2*blocksmargin,88*height/900-2*blocksmargin),
                                                      35/*id*/,200/*price*/))==NULL)GLOBAL::Gaming=false;

                if(GLOBAL::Gaming==false||
                        (blocks[36]=new SpecificBlock(SpecificBlockType::LuckCard,"幸运卡牌",
                                                      QRect(width*1110/1600-blocksmargin,height*464/900-blocksmargin,
                                                            109*width/1600-2*blocksmargin,64*height/900-2*blocksmargin),
                                                      36/*id*/))==NULL)GLOBAL::Gaming=false;

                if(GLOBAL::Gaming==false||
                        (blocks[37]=new BuildableBlock("奶茶铺",
                                                      QRect(width*1110/1600-blocksmargin,height*528/900-blocksmargin,
                                                            109*width/1600-2*blocksmargin,64*height/900-2*blocksmargin),
                                                      37/*id*/,415/*price*/,230/*buildprice*/,
                                                      4/*maxlevel*/,80/*chargebase*/,335/*chargeperlevel*/))==NULL)GLOBAL::Gaming=false;
                if(GLOBAL::Gaming==false||
                        (blocks[38]=new BuildableBlock("炸鸡铺",
                                                      QRect(width*1110/1600-blocksmargin,height*592/900-blocksmargin,
                                                            109*width/1600-2*blocksmargin,64*height/900-2*blocksmargin),
                                                      38/*id*/,430/*price*/,230/*buildprice*/,
                                                      4/*maxlevel*/,80/*chargebase*/,360/*chargeperlevel*/))==NULL)GLOBAL::Gaming=false;
                if(GLOBAL::Gaming==false||
                        (blocks[39]=new BuildableBlock("烧烤铺",
                                                      QRect(width*1110/1600-blocksmargin,height*656/900-blocksmargin,
                                                            109*width/1600-2*blocksmargin,64*height/900-2*blocksmargin),
                                                      39/*id*/,445/*price*/,230/*buildprice*/,
                                                      4/*maxlevel*/,85/*chargebase*/,355/*chargeperlevel*/))==NULL)GLOBAL::Gaming=false;
                ((BuildableBlock*)(blocks[37]))->buildneed_f=((BuildableBlock*)(blocks[38]));
                ((BuildableBlock*)(blocks[37]))->buildneed_s=((BuildableBlock*)(blocks[39]));
                ((BuildableBlock*)(blocks[38]))->buildneed_f=((BuildableBlock*)(blocks[37]));
                ((BuildableBlock*)(blocks[38]))->buildneed_s=((BuildableBlock*)(blocks[39]));
                ((BuildableBlock*)(blocks[39]))->buildneed_f=((BuildableBlock*)(blocks[37]));
                ((BuildableBlock*)(blocks[39]))->buildneed_s=((BuildableBlock*)(blocks[38]));



        }
        //玩家初始化
        {
            //随机打乱玩家顺序
            disorderintarray(playerordertoid,playernum);

            for(int i=0;i<6;i++)players[i]=NULL;
            for(int i=0;i<playernum&&GLOBAL::Gaming;i++)
           {

               const QString str(GLOBAL::ssmap["PlayerName"+QString::number(playerordertoid[i])]);
               QPixmap pixmap;
               if((players[playerordertoid[i]]=new Player(str,playerordertoid[i],playerordertoid[i],
                    QRect(width*63/80+width/320,height*(105+110*i)/900,width/5-width/160,height*11/90-height/90)))==NULL||
               (players[playerordertoid[i]]->rolelabel=new QLabel(this))==NULL||
                 (players[playerordertoid[i]]->image=new QImage)==NULL)
                   GLOBAL::Gaming=false;

                QPoint randompoint=GetRandomQPointInRadiu(blocks[0]->position,width/64,true);

                players[playerordertoid[i]]->rolelabel->setGeometry(randompoint.x()-playerroleimagewidth/2,randompoint.y()-playerroleimagewidth/2,playerroleimagewidth,playerroleimagewidth);

                pixmap.load(GLOBAL::ssmap["PlayerImage"+QString::number(playerordertoid[i])]);
                QPixmap scaledpixmap=pixmap.scaled(playerlistimagewdith,playerlistimagewdith,Qt::IgnoreAspectRatio);

                *(players[playerordertoid[i]]->image)=scaledpixmap.toImage();
                scaledpixmap=pixmap.scaled(playerroleimagewidth,playerroleimagewidth,Qt::IgnoreAspectRatio);
                players[playerordertoid[i]]->rolelabel->setPixmap(scaledpixmap);
                players[playerordertoid[i]]->rolelabel->show();
           }
        }
    }

    if(GLOBAL::Gaming==true&&GameBackground)//绘制背景
    {
        //20,20,880,560  110*70
        QPixmap pixmap(width,height),imagepixmap,scaledpixmap;
        QPainter painter(GameBackground);
        QFont font("微软雅黑",width*3/400,QFont::Bold,false);
        QPen pen;
        if((GLOBAL::Gaming=pixmap.load(GLOBAL::ssmap["GameBackGround"]))==true&&
           (GLOBAL::Gaming=imagepixmap.load(GLOBAL::ssmap["CardsBack"]))==true
            )
        {
            painter.drawPixmap(0,0,width,height,pixmap.scaled(width,height,Qt::IgnoreAspectRatio));

            scaledpixmap=imagepixmap.scaled(width/5,height*22/45);
            *(cardback)=scaledpixmap.toImage();
            GLOBAL::Gaming=imagepixmap.load(GLOBAL::ssmap["CardsFront"]);
            scaledpixmap=imagepixmap.scaled(width/5,height*22/45);
            *(cardfront)=scaledpixmap.toImage();
            painter.drawImage(width*84/800,width*104/800,*cardback);
            painter.drawImage(width*86/800,width*106/800,*cardback);
            painter.drawImage(width*88/800,width*108/800,*cardback);
            painter.drawImage(width*9/80,width*11/80,*cardback);


            //绘制区块信息
            {
                painter.setFont(font);
                pen.setColor(QColor(85,85,85));
                pen.setWidth(blocksmargin);
                painter.setPen(pen);

                for(int i=0;i<40;i++)
                {
                    switch(i)
                    {
                    case 0:
                    {
                        QPixmap pixmap;
                        GLOBAL::Gaming=pixmap.load(GLOBAL::ssmap["HelloWorld"]);
                        pixmap=pixmap.scaled(blocks[0]->rect.width(),blocks[0]->rect.height());
                        painter.drawPixmap(blocks[0]->rect,pixmap);
                        break;
                    }
                    case 5:
                    case 25:
                    {
                        QPixmap pixmap;
                        GLOBAL::Gaming=pixmap.load(GLOBAL::ssmap["Subway_UD"]);
                        pixmap=pixmap.scaled(blocks[i]->rect.width(),blocks[i]->rect.height());
                        painter.drawPixmap(blocks[i]->rect,pixmap);
                        painter.drawText(blocks[i]->position.x()-width*3/128,blocks[i]->position.y()-height/36,
                                                                      width/20,height*5/90,
                                                                      Qt::AlignLeft,blocks[i]->name);
                        break;
                    }
                    case 15:
                    case 35:
                    {
                        QPixmap pixmap;
                        GLOBAL::Gaming=pixmap.load(GLOBAL::ssmap["Subway_LR"]);
                        pixmap=pixmap.scaled(blocks[i]->rect.width(),blocks[i]->rect.height());
                        painter.drawPixmap(blocks[i]->rect,pixmap);
                        painter.drawText(blocks[i]->position.x()-width*3/128,blocks[i]->position.y()-height/36,
                                                                      width/20,height*5/90,
                                                                      Qt::AlignLeft,blocks[i]->name);
                        break;
                    }
                    case 10:
                    {
                        QPixmap pixmap;
                        GLOBAL::Gaming=pixmap.load(GLOBAL::ssmap["Library"]);
                        pixmap=pixmap.scaled(blocks[10]->rect.width(),blocks[10]->rect.height());
                        painter.drawPixmap(blocks[10]->rect,pixmap);
                        break;
                    }
                    case 20:
                    {
                        QPixmap pixmap;
                        GLOBAL::Gaming=pixmap.load(GLOBAL::ssmap["Hospital"]);
                        pixmap=pixmap.scaled(blocks[20]->rect.width(),blocks[20]->rect.height());
                        painter.drawPixmap(blocks[20]->rect,pixmap);
                        break;
                    }
                    case 30:
                    {
                        QPixmap pixmap;
                        GLOBAL::Gaming=pixmap.load(GLOBAL::ssmap["Deadline"]);
                        pixmap=pixmap.scaled(blocks[30]->rect.width(),blocks[30]->rect.height());
                        painter.drawPixmap(blocks[30]->rect,pixmap);
                        break;
                    }
                    case 17:
                    case 11:
                    {
                        QFont fonttemp(font);
                        fonttemp.setPointSize(width*5/800);
                        painter.setFont(fonttemp);
                        QTextOption option(Qt::AlignLeft | Qt::AlignTop);
                        painter.drawText(QRect(blocks[i]->position.x()-width*25/1024,blocks[i]->position.y()-height/36,
                                               width/18,height*5/90), blocks[i]->name, option);
                        painter.setFont(font);
                        break;
                    }
                    case 6:
                    case 13:
                    case 26:
                    case 32:
                    {
                        QPixmap pixmap;
                        GLOBAL::Gaming=pixmap.load(GLOBAL::ssmap["RandomEvent"]);
                        pixmap=pixmap.scaled(blocks[i]->rect.width(),blocks[i]->rect.height());
                        painter.drawPixmap(blocks[i]->rect,pixmap);
                        painter.drawText(blocks[i]->position.x()-width*3/128,blocks[i]->position.y()-height/36,
                                                                      width/20,height*5/90,
                                                                      Qt::AlignLeft,blocks[i]->name);
                        break;
                    }
                    case 4:
                    case 16:
                    case 24:
                    case 36:
                    {
                        QPixmap pixmap;
                        GLOBAL::Gaming=pixmap.load(GLOBAL::ssmap["Clover"]);
                        pixmap=pixmap.scaled(blocks[i]->rect.width(),blocks[i]->rect.height());
                        painter.drawPixmap(blocks[i]->rect,pixmap);
                        break;
                    }
                    default:
                    {
                        QTextOption option(Qt::AlignLeft | Qt::AlignTop);
                        painter.drawText(QRect(blocks[i]->position.x()-width*3/128,blocks[i]->position.y()-height/36,
                                               width/20,height*5/90), blocks[i]->name, option);
                                break;
                    }

                    }


                    pen.setColor(QColor(255,255,255,150));
                    painter.setPen(pen);

                    painter.drawRect(blocks[i]->rect);
                    pen.setColor(QColor(85,85,85));
                    painter.setPen(pen);
                    switch(blocks[i]->type)
                    {
                    case BlockType::Available:
                        {
                            painter.drawText(blocks[i]->position.x()-width*3/128,
                                             blocks[i]->position.y(),
                                             width*80/1280,height*50/720,
                                             Qt::AlignLeft,"¥"+QString::number(
                                                 ((AvailableBlock*)blocks[i])->purchaseprice));
                            break;
                        }
                    case BlockType::Specific:
                        {
                            break;
                        }
                    default:break;
                    }
                }
            }
            //绘制玩家列表
            {
                painter.setFont(font);
                pen.setWidth(5);
                 for(int i=0;i<playernum;i++)
                 {
                     int playerid=playerordertoid[i];
                     pen.setColor(PlayerIdToColor(playerid));
                     painter.setPen(pen);
                     painter.drawRect(players[playerid]->listrect);
                     painter.drawText(players[playerid]->listrect.x()+width/80,height*(110+i*110)/900,width*3/16,height/20,Qt::AlignLeft,players[playerid]->name);
                     painter.drawImage(players[playerid]->listrect.x()+players[playerid]->listrect.width()-width/80-playerlistimagewdith,height*(195+i*110)/900-playerlistimagewdith,*(players[playerid]->image));
                 }
            }
            //储存区块图像
            {
                for(int i=0;i<40;i++)
                {
                    blocks[i]->activepixmap=GameBackground->copy(blocks[i]->rect);
                    blocks[i]->originpixmap=GameBackground->copy(blocks[i]->rect);
                }

            }
        }
      }


    if(
            GLOBAL::Gaming==false||

            !cardback||!cardfront||!cardbacktemp||!cardfronttemp||
            !counttimer||

            !cardreversaltimer||

            !dicerefreshtimer||
            !Dices||

            !GameBackground||
            !GameBackgrounddarker||

            !hintlabel||!hintrolelabel||!hinttimer||

            !labelmovestagetimer||

            !pushbutton_build||!pushbutton_build_cancle||
            !pushbutton_dice||
            !pushbutton_failed_confirm||
            !pushbutton_menu||
            !pushbutton_quit||
            !pushbutton_sell||!pushbutton_sell_cancle||
            !pushbutton_stagefinish||
            !pushbutton_trade||
            !pushbutton_tradeplayerlist||
            !pushbutton_travel||!pushbutton_travel_cancle||
            !pushbutton_chat_widget_show||

            !stagelabel

      )
        GLOBAL::Gaming=false;//游戏初始化失败

    if(GLOBAL::Gaming)//初始化
    {
        /*变量，什么？你问我为什么不在初始化列表里初始化？
        老哥，只要我初始化的顺序对不上结构体申明里的顺序，编译器就给我个警告，看着真不爽，还是函数体
        初始化比较实在*/
        {
            operable=true;
            this->setFixedSize(width,height);//设置窗口固定分辨率
            this->setWindowTitle("GameMainUi");//改变窗口标题

            stage=Stage::START;stagecounter=5;
            stageplayerorder=0;
            nextstage=Stage::FORPLAYER;nextstagecounter=GLOBAL::simap["OperateTime"];

            iscount=true;
            isbuilding=false;
            isselling=false;
            isdice=false;
            showdices=false;
            ispause=false;
            istest=false;
            istraveling=false;
            istradeplayerlistshown=false;
            isdicebuttonclicked=false;
            testcmd=false;

            GameBackgroundalternate=GameBackground;

            mywidget=NULL;

            chattextedit.setReadOnly(true);

            cardreversaltimercount=0;

            //初始化卡牌
            disorderintarray(cardtypeorder,7);
            cardsremain=7;

            //初始化随机事件
            disorderintarray(randomeventstypeorder,5);
            randomeventsremain=5;
        }

        //timer
        {

            counttimer->setTimerType(Qt::PreciseTimer);
            counttimer->setSingleShot(false);
            connect(counttimer,SIGNAL(timeout()),this,SLOT(ActionPerSecond()));

            dicerefreshtimer->setTimerType(Qt::PreciseTimer);
            dicerefreshtimer->setSingleShot(false);
            connect(dicerefreshtimer,SIGNAL(timeout()),this,SLOT(DiceRefresh_TimeOut()));

            labelmovestagetimer->setTimerType(Qt::PreciseTimer);
            labelmovestagetimer->setSingleShot(true);
            connect(labelmovestagetimer,SIGNAL(timeout()),this,SLOT(LabelMoveStageTimer_TimeOut()));

            playertravelstagetimer->setTimerType(Qt::PreciseTimer);
            playertravelstagetimer->setSingleShot(true);
            connect(playertravelstagetimer,SIGNAL(timeout()),this,SLOT(PlayerTravelStageTimer_TimeOut()));

            cardreversaltimer->setTimerType(Qt::PreciseTimer);
            cardreversaltimer->setSingleShot(false);
            connect(cardreversaltimer,SIGNAL(timeout()),this,SLOT(CardReversalTimer_TimeOut()));

            hinttimer->setTimerType(Qt::PreciseTimer);
            hinttimer->setSingleShot(true);
            connect(hinttimer,SIGNAL(timeout()),this,SLOT(HintTimer_TimeOut()));
        }

        //字体
        {
            fontdefault=new QFont("微软雅黑", width/80, QFont::Bold, false);
            //最后一个参数是否斜体
            //设置下划线
             //font.setUnderline(true);
             //设置上划线
             //font.setOverline(true);
             //设置字母大小写
             //font.setCapitalization(QFont::SmallCaps);
             //设置字符间的间距
             fontdefault->setLetterSpacing(QFont::AbsoluteSpacing, 2);
        }

        //pushbutton_quit
        {
            pushbutton_quit->setGeometry(width*117/128,height/45,width/16,width/24);
            pushbutton_quit->setStyleSheet(GLOBAL::ssmap["PushButtonStyleSheet1"]);
            pushbutton_quit->setText("返回");
            pushbutton_quit->setFont(*fontdefault);
        }
        //pushbutton_menu
        {
            pushbutton_menu->setGeometry(width*4/5,height/45,width/16,width/24);
            pushbutton_menu->setStyleSheet(GLOBAL::ssmap["PushButtonStyleSheet1"]);
            pushbutton_menu->setText("菜单");
            pushbutton_menu->setFont(*fontdefault);
        }
        //pushbutton_stagefinish
        {
            pushbutton_stagefinish->setGeometry(width/2-width/36,height/2-width/36,width/18,width/18);
            pushbutton_stagefinish->setStyleSheet(GLOBAL::ssmap["PushButtonStyleSheet1"]);
            pushbutton_stagefinish->setText("完成");
            pushbutton_stagefinish->setFont(*fontdefault);
            pushbutton_stagefinish->hide();
        }
        //pushbutton_travel
        {
            pushbutton_travel->setGeometry(width/2-width/36,height*5/8-width/36,width/18,width/18);
            pushbutton_travel->setStyleSheet(GLOBAL::ssmap["PushButtonStyleSheet1"]);
            pushbutton_travel->setText("搭车");
            pushbutton_travel->setFont(*fontdefault);
            pushbutton_travel->hide();
        }
        //pushbutton_travel_cancle
        {
            pushbutton_travel_cancle->setGeometry(width/2-width/36,height*5/8-width/36,width/18,width/18);
            pushbutton_travel_cancle->setStyleSheet(GLOBAL::ssmap["PushButtonStyleSheet1"]);
            pushbutton_travel_cancle->setText("取消");
            pushbutton_travel_cancle->setFont(*fontdefault);
            pushbutton_travel_cancle->hide();
        }
        //pushbutton_failedconfirm
        {
            pushbutton_failed_confirm->setGeometry(width/2-width/36,height/2-width/36,width/9,width/18);
            pushbutton_failed_confirm->setStyleSheet(GLOBAL::ssmap["PushButtonStyleSheetPassive"]);
            pushbutton_failed_confirm->setText("回去学习");
            pushbutton_failed_confirm->setFont(*fontdefault);
            pushbutton_failed_confirm->hide();
        }
        //pushbutton_dice
        {
            pushbutton_dice->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/dices/dicebutton.png);}"
                                          "QPushButton:hover{border-image: url(:/new/prefix1/myimages/dices/dicebutton-hover.png);}"
                                           "QPushButton:disabled{border-image: url(:/new/prefix1/myimages/dices/dicebutton-banned.png);}"
                                          "QPushButton:pressed{border-image: url(:/new/prefix1/myimages/dices/dicebutton-clicking.png);}");
            pushbutton_dice->setGeometry(width/2-width/20,height/2-width/20,width/10,width/10);
            pushbutton_dice->hide();
        }
        //pushbutton_trade
        {
            pushbutton_trade->setGeometry(width*3/80,height*14/15,width*5/32,height*4/90);
            pushbutton_trade->setStyleSheet(GLOBAL::ssmap["PushButtonStyleSheet1"]);
            pushbutton_trade->setText("交易");

            pushbutton_trade->setFont(*fontdefault);
        }
        //pushbutton_tradeplayerlist
        {
            for(int i=0;i<playernum;i++)
            {
                GLOBAL::piiimap[PII((int)pushbutton_tradeplayerlist[i],0)]=i;//为每个按钮存下玩家id
                pushbutton_tradeplayerlist[i]->setGeometry(width*3/80,height*(810-30*i)/900,width*5/32,height/30);
                pushbutton_tradeplayerlist[i]->setFont(*fontdefault);
                pushbutton_tradeplayerlist[i]->setStyleSheet(GLOBAL::ssmap["PushButtonStyleSheet1"]);
                pushbutton_tradeplayerlist[i]->setText(players[i]->name);
                pushbutton_tradeplayerlist[i]->hide();
                connect(pushbutton_tradeplayerlist[i],SIGNAL(clicked()),this,SLOT(PushButton_TradePlayerList_clicked()));
            }
        }
        //pushbutton_sell
        {
            pushbutton_sell->setGeometry(width*63/80,height*14/15,width*5/32,height*4/90);
            pushbutton_sell->setStyleSheet(GLOBAL::ssmap["PushButtonStyleSheet1"]);
             pushbutton_sell->setText("出售");
             pushbutton_sell->setFont(*fontdefault);
        }
        {
            pushbutton_sell_cancle->setGeometry(width*63/80,height*14/15,width*5/32,height*4/90);
            pushbutton_sell_cancle->setStyleSheet(GLOBAL::ssmap["PushButtonStyleSheet1"]);
             pushbutton_sell_cancle->setText("完成");
             pushbutton_sell_cancle->setFont(*fontdefault);
             pushbutton_sell_cancle->hide();;
        }
        //pushbutton_build
        {
            pushbutton_build->setGeometry(width*33/80,height*14/15,width*5/32,height*4/90);
            pushbutton_build->setStyleSheet(GLOBAL::ssmap["PushButtonStyleSheet1"]);
             pushbutton_build->setText("升级");
             pushbutton_build->setFont(*fontdefault);
        }
        //pushbutton_build_cancle
        {
            pushbutton_build_cancle->setGeometry(width*33/80,height*14/15,width*5/32,height*4/90);
            pushbutton_build_cancle->setStyleSheet(GLOBAL::ssmap["PushButtonStyleSheet1"]);
             pushbutton_build_cancle->setText("完成");
             pushbutton_build_cancle->setFont(*fontdefault);
             pushbutton_build_cancle->hide();
        }
        //pushbutton_chat_wiget_show
        {
            pushbutton_chat_widget_show->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/myimages/wechat.png);}"
                                          "QPushButton:hover{border-image: url(:/new/prefix1/myimages/wechat-highlight.png);}"
                                          "QPushButton:disabled{border-image: url(:/new/prefix1/myimages/wechat-banned.png);}"
                                          "QPushButton:pressed{border-image: url(:/new/prefix1/myimages/wechat-clicking.png);}");
            pushbutton_chat_widget_show->setGeometry(width*139/160,height/45,width/24,width/24);
            pushbutton_chat_widget_show->show();
        }

        connect(pushbutton_quit,SIGNAL(clicked()),this,SLOT(PushButton_Quit_clicked()));
        connect(pushbutton_menu,SIGNAL(clicked()),this,SLOT(PushButton_Menu_clicked()));
        connect(pushbutton_dice,SIGNAL(clicked()),this,SLOT(PushButton_Dice_clicked()));
        connect(pushbutton_trade,SIGNAL(clicked()),this,SLOT(PushButton_Trade_clicked()));
        connect(pushbutton_stagefinish,SIGNAL(clicked()),this,SLOT(PushButton_StageFinish_clicked()));
        connect(pushbutton_failed_confirm,SIGNAL(clicked()),this,SLOT(PushButton_StageFinish_clicked()));
        connect(pushbutton_build,SIGNAL(clicked()),this,SLOT(PushButton_Build_clicked()));
        connect(pushbutton_build_cancle,SIGNAL(clicked()),this,SLOT(PushButton_Build_Cancle_clicked()));
        connect(pushbutton_sell,SIGNAL(clicked()),this,SLOT(PushButton_Sell_clicked()));
        connect(pushbutton_sell_cancle,SIGNAL(clicked()),this,SLOT(PushButton_Sell_Cancle_clicked()));
        connect(pushbutton_travel,SIGNAL(clicked()),this,SLOT(Pushbutton_Travel_clicked()));
        connect(pushbutton_travel_cancle,SIGNAL(clicked()),this,SLOT(Pushbutton_Travel_Cancle_clicked()));
        connect(pushbutton_chat_widget_show,SIGNAL(clicked()),this,SLOT(PushButton_Chat_Widget_Show_clicked()));

        connect(&chattextedit,SIGNAL(textChanged()),this,SLOT(ChatTextEdit_Changed()));

        operablepushbuttonv.push_back(pushbutton_trade);
        operablepushbuttonv.push_back(pushbutton_failed_confirm);
        operablepushbuttonv.push_back(pushbutton_dice);
        operablepushbuttonv.push_back(pushbutton_stagefinish);
        operablepushbuttonv.push_back(pushbutton_build);
        operablepushbuttonv.push_back(pushbutton_sell);
        operablepushbuttonv.push_back(pushbutton_travel);

        //背景暗色预处理
        {
            QImage img=GameBackground->toImage();
            img=DarkScale(img,2);
            *GameBackgrounddarker=QPixmap::fromImage(img);
        }

        //提示框预处理
        {
            QPixmap pixmap(GLOBAL::ssmap["Image0"]);
            pixmap=pixmap.scaled(pixmap.width()/2,pixmap.height()/2,Qt::IgnoreAspectRatio);
            hintrolelabel->setPixmap(pixmap);
            hintrolelabel->setGeometry(width*3/2,height*3/2,pixmap.width(),pixmap.height());
            pixmap.load(GLOBAL::ssmap["Hint"]);
            pixmap=pixmap.scaled(pixmap.width()*5/6,pixmap.height()*5/12);
            hintlabel->setPixmap(pixmap);
            hintlabel->setGeometry(width*3/2,height*3/2,pixmap.width(),pixmap.height());
            hintlabel->hide();
        }

        //stagelabel
        {
            stagelabel->setGeometry(width*16/27,height*9/20,playerlistimagewdith,playerlistimagewdith);
            stagelabel->hide();
        }

        SetOperable(false);
        iscount=true;
        counttimer->start(1000);//启动每秒计时器
    }
}

GameMainWidget::~GameMainWidget()
{
    //我好像听说继承父窗口的子部件不用自行delete，但是我是强迫症
    for(int i=0;i<6;i++)delete players[i];
    for(int i=0;i<40;i++)delete blocks[i];
    delete counttimer;
    delete dicerefreshtimer;
    delete fontdefault;
    delete GameBackground;
    delete GameBackgrounddarker;
    delete hinttimer;
    delete hintlabel;
    delete hintrolelabel;
    delete pushbutton_failed_confirm;
    delete pushbutton_menu;
    delete pushbutton_stagefinish;
    delete pushbutton_build;
    delete pushbutton_build_cancle;
    delete pushbutton_sell;
    delete pushbutton_sell_cancle;
    delete pushbutton_quit;
    delete pushbutton_trade;
    delete pushbutton_travel;
    delete pushbutton_travel_cancle;
    delete pushbutton_dice;
    delete []pushbutton_tradeplayerlist;
    delete pushbutton_chat_widget_show;
    delete playertravelstagetimer;
    delete cardback;
    delete cardfront;
    delete stagelabel;
    delete []Dices;
    delete []Levels;
    delete ui;

    GLOBAL::piiimap.clear();//清除所有地址映射到整数的储存
}

void GameMainWidget::paintEvent(QPaintEvent *)
{
    QPainter mainpainter(this);
    QPen mainpainterpen;

    //绘制背景
    mainpainter.drawPixmap(0,0,width,height,*GameBackgroundalternate);
    //绘制背景end

    //对背景的改变
    if(isbuilding)
    {
        for(QVector<BuildableBlock*>::iterator iter=operablebuildablocksv.begin();
                iter!=operablebuildablocksv.end();iter++)
            mainpainter.drawPixmap((*iter)->rect,(*iter)->activepixmap);
    }
    else
    if(isselling)
    {
        for(QVector<BuildableBlock*>::iterator iter=operablebuildablocksv.begin();
                iter!=operablebuildablocksv.end();iter++)
            if((*iter)->level>0)mainpainter.drawPixmap((*iter)->rect,(*iter)->activepixmap);
    }
    else
    if(istraveling)
    {
        for(int i=5;i<45;i+=10)
            if(((AvailableBlock*)blocks[i])->owner==players[playerordertoid[stageplayerorder]]&&players[playerordertoid[stageplayerorder]]->locationid!=i)
                mainpainter.drawPixmap(blocks[i]->rect,blocks[i]->activepixmap);
    }
    else
    {
        //绘制玩家拥有地块
        mainpainterpen.setWidth(width/320);
        for(int i=0;i<40;i++)
            if(blocks[i]->type==BlockType::Available)
            {
                AvailableBlock*block=(AvailableBlock*)blocks[i];
                if(block->owner!=NULL)
                {
                    mainpainterpen.setColor(PlayerIdToColor(block->owner->id));
                    mainpainter.setPen(mainpainterpen);
                    mainpainter.drawRect(block->rect);
                    mainpainter.drawPixmap(block->rect,block->activepixmap);
                }


            }

        //白色的游戏阶段执行者
        mainpainterpen.setWidth(width/160);
        mainpainterpen.setColor(Qt::white);
        mainpainter.setPen(mainpainterpen);
        mainpainter.drawRect(players[playerordertoid[stageplayerorder]]->listrect);

    }



    //绘制字体
    {
        QFont font(*fontdefault);
        font.setPointSize(width/80);
        font.setLetterSpacing(QFont::AbsoluteSpacing,width/320);
        mainpainter.setFont(font);
        mainpainterpen.setColor(QColor(48,48,255));
        mainpainter.setPen(mainpainterpen);
        mainpainter.drawText(width/10,height*7/45,width/3,height/18,Qt::AlignLeft,stagestring);


        mainpainterpen.setColor(QColor(211,120,13));
        mainpainter.setPen(mainpainterpen);
        font.setPointSize(width/80);
        for(int i=0;i<playernum;i++)//绘制现金
        {
            mainpainter.drawText(players[playerordertoid[i]]->listrect.x()+width/80,
                                 height*(145+i*110)/900,
                                 width*3/16,height*4/45,Qt::AlignLeft,QString::number(players[playerordertoid[i]]->cash));
        }
    }
    //绘制字体end

    //绘制图片
    {
        //骰子
        if(showdices)
        {
            if(dice_f>0&&dice_f<7)
            mainpainter.drawPixmap(width*15/32,height*13/45,Dices[dice_f-1]);
            if(dice_s>0&&dice_s<7)
            mainpainter.drawPixmap(width*15/32,height*27/45,Dices[dice_s-1]);
        }
    }

    if(cardreversaltimercount>=425)
    {
        mainpainter.drawImage(cardreversx,width*11/80,*cardbacktemp);
    }
    else
        if(cardreversaltimercount>75&&cardreversaltimercount<=423)
        {
            mainpainter.drawImage(cardreversx,width*11/80,*cardfronttemp);
            mainpainter.drawImage(width*9/80,width*11/80,*cardback);
        }
        else
        if(cardreversaltimercount>0&&cardreversaltimercount<=75)
        {
            mainpainter.drawImage(cardreversx,width*11/80,*cardbacktemp);
            mainpainter.drawImage(width*9/80,width*11/80,*cardback);
        }

}

void GameMainWidget::mousePressEvent(QMouseEvent *event)
{
    if(istraveling)
    {
        for(int i=5;i<45;i+=10)
        if(players[playerordertoid[stageplayerorder]]->locationid!=i&&((AvailableBlock*)blocks[i])->rect.contains(event->x(),event->y()))
        {
            PlayerRoleTravel(*(players[playerordertoid[stageplayerorder]]),i,false);
            Pushbutton_Travel_Cancle_clicked();
            SetOperable(false);
            pushbutton_travel->hide();
            pushbutton_travel_cancle->hide();
        }
    }
    else
    if(isbuilding||isselling)
    for(int i=0;i<40;i++)
        if(blocks[i]->type==BlockType::Available&&
                ((AvailableBlock*)blocks[i])->type==AvailableBlockType::Buildable
                &&blocks[i]->rect.contains(event->x(),event->y()))
        {
            BuildableBlock*blockp=(BuildableBlock*)blocks[i];
            if(isbuilding&&blockp->isoperateallowed==true&&blockp->level<blockp->maxlevel&&
                    players[playerordertoid[stageplayerorder]]->cash>=blockp->buildprice)
            {
                    PlayercashChange(playerordertoid[stageplayerorder],-1*(blockp->buildprice));
                    blockp->level++;
                    //绘制区块信息
                    {
                        QPainter apainter(&(blockp->activepixmap));
                        QPixmap scaledpixmap=Levels[blockp->level-1].scaled(blockp->rect.width()*2/3,blockp->rect.height()*2/3,Qt::IgnoreAspectRatio);

                        apainter.drawPixmap(0,0,blockp->rect.width(),blockp->rect.height(),blockp->originpixmap);
                        apainter.drawPixmap(blockp->rect.width()/6,blockp->rect.height()/3,blockp->rect.width()*2/3,blockp->rect.height()*2/3,scaledpixmap);

                        QFont font("微软雅黑",width*3/400,QFont::Bold,false);
                        QPen pen;
                        apainter.setFont(font);
                        pen.setColor(QColor(85,85,85));
                        apainter.setPen(pen);
                        apainter.drawText(blockp->rect.width()/2-width*3/128,blockp->rect.height()/2-height/36,width/20,height*5/90,Qt::AlignLeft,blockp->name);
                        update();
                    }
            }
            if(isselling&&blockp->isoperateallowed==true&&blockp->level>0)
            {
                PlayercashChange(playerordertoid[stageplayerorder],(blockp->buildprice)/2);
                blockp->level--;
                if(blockp->level>0)
                {
                    QPainter apainter(&(blockp->activepixmap));
                    QPixmap scaledpixmap=Levels[blockp->level-1].scaled(blockp->rect.width()*2/3,blockp->rect.height()*2/3,Qt::IgnoreAspectRatio);

                    apainter.drawPixmap(0,0,blockp->rect.width(),blockp->rect.height(),blockp->originpixmap);
                    apainter.drawPixmap(blockp->rect.width()/6,blockp->rect.height()/6,blockp->rect.width()*2/3,blockp->rect.height()*2/3,scaledpixmap);

                    QFont font("微软雅黑",width*3/400,QFont::Bold,false);
                    QPen pen;
                    apainter.setFont(font);
                    pen.setColor(QColor(85,85,85));
                    apainter.setPen(pen);
                    apainter.drawText(blockp->rect.width()/2-width*3/128,blockp->rect.height()/2-height/36,width/20,height*5/90,Qt::AlignLeft,blockp->name);
                    update();
                }
                else
                {
                    QPainter apainter(&(blockp->activepixmap));
                    apainter.drawPixmap(0,0,blockp->rect.width(),blockp->rect.height(),blockp->originpixmap);
                    update();
                }
            }
            break;
        }
    if(istradeplayerlistshown==true)
    {
        for(int i=0;i<playernum;i++)
        {
            if(players[i]->rolelabel)
            players[i]->rolelabel->show();
            if( pushbutton_tradeplayerlist[i])pushbutton_tradeplayerlist[i]->hide();
        }
        istradeplayerlistshown=false;
    }



}

void GameMainWidget::closeEvent(QCloseEvent *event)
{
    if(stage!=Stage::OVER)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "返回主界面", "游戏未结束，确定返回主界面?", QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes)
        {
            event->accept();
            GLOBAL::mainwindow->show();
            if(mywidget)mywidget->close();
            if(mydialog)mydialog->close();

            QVector<ChatWidget*>::iterator iter=activechatwidgets.begin();
            for(;iter!=activechatwidgets.end();iter++)
                (*iter)->hide();

            GLOBAL::gamemainwidget=NULL;
            delete this;
        }
        else
        {
            event->ignore();
        }
    }
    else
    {
        GLOBAL::mainwindow->show();
        if(mywidget)mywidget->close();
        if(mydialog)mydialog->close();

        QVector<ChatWidget*>::iterator iter=activechatwidgets.begin();
        for(;iter!=activechatwidgets.end();iter++)
            (*iter)->hide();
        GLOBAL::gamemainwidget=NULL;
        delete this;
    }

}

//设置是否可操作
void GameMainWidget::SetOperable(bool b)
{

    operable=b;
    if(operable)//使按钮可用
    {
        QVector<QPushButton*>::iterator iter;
        for(iter=operablepushbuttonv.begin();iter!=operablepushbuttonv.end();iter++)
            (*iter)->setEnabled(true);

        iscount=true;
    }
    else
    {
        QVector<QPushButton*>::iterator iter;
        for(iter=operablepushbuttonv.begin();iter!=operablepushbuttonv.end();iter++)
            (*iter)->setEnabled(false);

        iscount=false;
    }
}

void GameMainWidget::PushButton_Quit_clicked()
{
    if(istradeplayerlistshown)
    for(int i=0;i<playernum;i++)
    {
        pushbutton_tradeplayerlist[i]->hide();
        if(players[i]->rolelabel)
        players[i]->rolelabel->show();
    }
    this->close();
}

void GameMainWidget::PushButton_Menu_clicked()//有待补充
{
    if(istradeplayerlistshown)
    for(int i=0;i<playernum;i++)
    {
        pushbutton_tradeplayerlist[i]->hide();
        if(players[i]->rolelabel)
        players[i]->rolelabel->show();
    }

    SetPause();

    MyDialog menu_dialog(MyDialogType::GameMenu,0,0,this);
    menu_dialog.resize(width/4,height/3);

    pushbutton_chat_widget_show->setEnabled(false);

    if(menu_dialog.exec()==QDialog::Accepted)
    {

    }
    else
    {

    }
    pushbutton_chat_widget_show->setEnabled(true);
    SetContinue();
}

void GameMainWidget::PushButton_Dice_clicked()
{
    if(istradeplayerlistshown)
    for(int i=0;i<playernum;i++)
    {
        pushbutton_tradeplayerlist[i]->hide();
        if(players[i]->rolelabel)
        players[i]->rolelabel->show();
    }

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    GLOBAL::piiimap[PII((int)dicerefreshtimer,0)]=30;//记录一共刷新的次数
    pushbutton_dice->hide();
    stagelabel->hide();
    isdicebuttonclicked=true;
    showdices=true;
    SetOperable(false);
    dicerefreshtimer->start(100);//100毫秒刷新一次
}

void GameMainWidget::PushButton_Trade_clicked()
{
    if(istradeplayerlistshown==false)
    {
        istradeplayerlistshown=true;
        for(int i=0;i<playernum;i++)
        {
            pushbutton_tradeplayerlist[i]->show();
            if(players[i]->rolelabel)
            players[i]->rolelabel->hide();
            if(players[i]->isfailed==false)
            pushbutton_tradeplayerlist[i]->setEnabled(true);
            else
            pushbutton_tradeplayerlist[i]->setEnabled(false);
        }
        pushbutton_tradeplayerlist[playerordertoid[stageplayerorder]]->setEnabled(false);
    }
    else
    {
        istradeplayerlistshown=false;
        for(int i=0;i<playernum;i++)
        {
            pushbutton_tradeplayerlist[i]->hide();
            if(players[i]->rolelabel)
            players[i]->rolelabel->show();
        }

    }

}

void GameMainWidget::PushButton_TradePlayerList_clicked()
{
    const QPushButton *pushedbutton=dynamic_cast<QPushButton*>(sender());
    for(int i=0;i<playernum;i++)
    {
        pushbutton_tradeplayerlist[i]->hide();
        if(players[i]->rolelabel)
        players[i]->rolelabel->show();
    }
    istradeplayerlistshown=false;

    if(pushedbutton)
    {
        int tradingplayerid=GLOBAL::piiimap[PII((int)pushedbutton,0)];

        mywidget=new MyWidget(MyWidgetType::Trading,playerordertoid[stageplayerorder],tradingplayerid);
        //该变量内存的释放将在mywidget return 函数中进行
        mywidget->show();
        SetOperable(false);
        pushbutton_menu->setEnabled(false);
        pushbutton_quit->setEnabled(false);
        iscount=true;
    }
}

void GameMainWidget::PushButton_StageFinish_clicked()
{
    if(istradeplayerlistshown)
    for(int i=0;i<playernum;i++)
    {
        pushbutton_tradeplayerlist[i]->hide();
        if(players[i]->rolelabel)
        players[i]->rolelabel->show();
    }
    if(mywidget==NULL)
    {
        StageFinish();
        stagecounter=1;
    }
    else
    {
        //hint
    }

}

void GameMainWidget::Labelmove(QLabel &label, const int desx,const int desy,const int msec,const int style)
//des就是label中点移动的终点
{
    QPropertyAnimation *qpa=new QPropertyAnimation(&label,"geometry",this);
    /*  设置动画持续时长  */
    qpa->setDuration(msec);
      /*  设置动画的起始状态 起始点  起始大小   */
    qpa->setStartValue(QRect(label.x(), label.y(), label.width(), label.height()));
         /*  设置动画的结束状态 结束点 结束大小   */
    qpa->setEndValue(QRect(desx-label.width()/2, desy-label.height()/2, label.width(),label.height()));
         /*  设置动画效果  */
    switch(style)
    {
    case 1:
        if(qrand()&1)
            qpa->setEasingCurve(QEasingCurve::InOutQuad);
        else
            qpa->setEasingCurve(QEasingCurve::OutInQuad);
        break;
    case 2:
        if(qrand()&1)
            qpa->setEasingCurve(QEasingCurve::InOutSine);
        else
            qpa->setEasingCurve(QEasingCurve::OutInSine);
        break;
    default:qpa->setEasingCurve(QEasingCurve::Linear);break;
    }

    /*效果：
     * QEasingCurve::OutBounce
     * QEasingCurve::Linear 线性
     * QEasingCurve::InQuad 二次凹曲线
     * QEasingCurve::OutQuad 二次凸曲线
     * QEasingCurve::InOutQuad 类似sin
     * QEasingCurve::OutInQuad 同上
     * 将Quad换成Cubi则是3次曲线
     * 换成Quart是4次，Quin5次
     *换成Sine 是Sine曲线
     * Expo是2^t曲线 Circ为圆曲线
     * Elastic为震荡曲线
     * Bounce是对称震荡
    */

     /*  开始执行动画 QAbstractAnimation::DeleteWhenStopped 动画结束后进行自清理(效果就好像智能指针里的自动delete animation) */
    qpa->start(QAbstractAnimation::DeleteWhenStopped);
}

void GameMainWidget::ActionPerSecond()
{
    if(iscount)
    {
        if(stagecounter>0)
        {
            switch(stage)
            {
                case Stage::FORPLAYER:
                {
                    stagecounter--;
                    stagestring=players[playerordertoid[stageplayerorder]]->name
                            +":"+tr("%1").arg(stagecounter);
                    if(!stagecounter&&isdicebuttonclicked==false)
                    {
                        iscount=false;
                         PushButton_Dice_clicked();//超时强制掷骰子
                    }

                    break;
                }
                case Stage::PAUSE:
                {
                    stagestring="Pause";
                    break;
                }
                case Stage::START:
                {
                    stagecounter--;
                    stagestring="Start in:"+tr("%1").arg(stagecounter);
                    break;
                }
                case Stage::WATING:
                {
                     break;
                }
                case Stage::OVER:
                {
                    for(stageplayerorder=0;stageplayerorder<playernum;stageplayerorder++)
                        if(players[playerordertoid[stageplayerorder]]->cash>=0)break;
                    stagestring="WINNER:"+players[playerordertoid[stageplayerorder]]->name;
                    update();
                    counttimer->stop();
                    break;
                }
           }

        }
        else//游戏阶段切换
        {
            switch(stage)
            {
                case Stage::FORPLAYER://玩家阶段一般不需要转换
                {
                    pushbutton_stagefinish->hide();
                    stagelabel->hide();
                    StageFinish();
                    stageplayerorder++;
                    if(stageplayerorder>=playernum)
                        stageplayerorder=0;
                    while(players[playerordertoid[stageplayerorder]]->resttimes>0||players[playerordertoid[stageplayerorder]]->isfailed==true)
                    {
                        if(players[playerordertoid[stageplayerorder]]->resttimes>0)players[playerordertoid[stageplayerorder]]->resttimes--;
                        stageplayerorder++;
                        if(stageplayerorder>=playernum)
                            stageplayerorder=0;
                    }
                    playerfornow=players[playerordertoid[stageplayerorder]];


                    {
                        QPixmap pixmap;
                        pixmap=QPixmap::fromImage(*(playerfornow->image));
                        pixmap=pixmap.scaled(playerlistimagewdith,playerlistimagewdith);
                        stagelabel->setPixmap(pixmap);
                    }


                    if(playerfornow->ddls)
                    {
                        mywidget=new MyWidget(MyWidgetType::DDL);
                        mywidget->show();
                    }
                    else
                    {
                        pushbutton_dice->show();
                        stagelabel->show();
                    }

                    isdicebuttonclicked=false;
                    stagecounter=GLOBAL::simap["OperateTime"];
                    stagestring=playerfornow->name
                            +":"+tr("%1").arg(stagecounter);
                    SetOperable(true);

                    break;
                }
                case Stage::PAUSE://任何阶段都有可能暂停
                {
                    stage=nextstage;
                    stagecounter=nextstagecounter;
                    break;
                }
                case Stage::START:
                case Stage::WATING:
                {


                     stage=Stage::FORPLAYER;
                     stagecounter=GLOBAL::simap["OperateTime"];
                     pushbutton_dice->show();
                     playerfornow=players[playerordertoid[stageplayerorder]];
                     stagestring=playerfornow->name
                             +":"+tr("%1").arg(stagecounter);
                     {
                         QPixmap pixmap;
                         pixmap=QPixmap::fromImage(*(playerfornow->image));
                         pixmap=pixmap.scaled(playerlistimagewdith,playerlistimagewdith);
                         stagelabel->setPixmap(pixmap);
                     }
                     stagelabel->show();
                     SetOperable(true);
                     break;
                }
                case Stage::OVER:
                {
                for(stageplayerorder=0;stageplayerorder<playernum;stageplayerorder++)
                    if(players[playerordertoid[stageplayerorder]]->cash>=0)break;
                stagestring="WINNER:"+players[playerordertoid[stageplayerorder]]->name;
                update();
                counttimer->stop();
                break;
                }

           }
        }
     update();
    }
}

void GameMainWidget::DiceRefresh_TimeOut()
{
    if(!ispause)
    {
        int times=GLOBAL::piiimap[PII((int)dicerefreshtimer,0)];
        if(times>20)
        {
            dice_f=qrand()%6+1;
            dice_s=qrand()%6+1;
            if(isdice&&times==21)
            {
                dice_f=dicechange_f;
                dice_s=dicechange_s;
                isdice=false;
            }
            update();
            GLOBAL::piiimap[PII((int)dicerefreshtimer,0)]=times-1;
        }
        else
        if(times==20)
        {
            if(playerfornow->ddls>0)
            {
                if(dice_f==dice_s)//若同点则移动
                {
                    isdicebuttonclicked=false;//奖励
                    stagecounter+=GLOBAL::simap["OperateTime"]/3;
                    playerfornow->ddls=0;
                    PlayerRoleMoveByDice(*playerfornow
                            ,dice_f+dice_s);
                }
                else
                {
                    SetOperable(true);
                    playerfornow->ddls--;
                    if(stagecounter)
                    {
                        stagecounter=1;
                    }
                    StageFinish();

                }
            }
            else//无ddl状态
            {
                if(dice_f==dice_s)
                {
                    isdicebuttonclicked=false;//奖励
                    stagecounter+=GLOBAL::simap["OperateTime"]/3;
                }
                PlayerRoleMoveByDice(*(players[playerordertoid[stageplayerorder]])
                        ,dice_f+dice_s);
            }

            GLOBAL::piiimap[PII((int)dicerefreshtimer,0)]=19;
        }
        else
        if(times>0)
        {
            GLOBAL::piiimap[PII((int)dicerefreshtimer,0)]=times-1;
        }
        else
        {
            showdices=false;
            dicerefreshtimer->stop();

            if(playerfornow->ddls>0)//若有ddl状态，则
            {
                StageFinish();
                playerfornow->ddls--;
                stagecounter=1;
            }
        }
    }


}

void GameMainWidget::PlayerRoleMoveByDice(Player&player,const int steps)
//通过掷骰子而调用的玩家角色移动函数
{
    //steps<=12
    SetOperable(false);
    playerrolewaypoint.clear();

    if(player.locationid>=0&&player.locationid<10)
    {
        GLOBAL::piiimap[PII((int)labelmovestagetimer,1)]=steps*200;
        if(player.locationid+steps>10)
        {
            GLOBAL::piiimap[PII((int)labelmovestagetimer,1)]=(10-player.locationid)*200;
            GLOBAL::piiimap[PII((int)labelmovestagetimer,2)]=(steps-(10-player.locationid))*200;
            playerrolewaypoint.push_back(blocks[10]->position);
        }
        if(player.locationid+steps>20)
        {
            GLOBAL::piiimap[PII((int)labelmovestagetimer,2)]=2000;
            GLOBAL::piiimap[PII((int)labelmovestagetimer,3)]=(steps-(20-player.locationid))*200;
            playerrolewaypoint.push_back(blocks[20]->position);
        }

    }
    else
    if(player.locationid>=10&&player.locationid<20)
    {
        GLOBAL::piiimap[PII((int)labelmovestagetimer,1)]=steps*200;
        if(player.locationid+steps>20)
        {
            GLOBAL::piiimap[PII((int)labelmovestagetimer,1)]=(20-player.locationid)*200;
            GLOBAL::piiimap[PII((int)labelmovestagetimer,2)]=(steps-(20-player.locationid))*200;
            playerrolewaypoint.push_back(blocks[20]->position);
        }
        if(player.locationid+steps>30)
        {
            GLOBAL::piiimap[PII((int)labelmovestagetimer,2)]=2000;
            GLOBAL::piiimap[PII((int)labelmovestagetimer,3)]=(steps-(30-player.locationid))*200;
            playerrolewaypoint.push_back(blocks[30]->position);
        }
    }
    else
    if(player.locationid>=20&&player.locationid<30)
    {
        GLOBAL::piiimap[PII((int)labelmovestagetimer,1)]=steps*200;
        if(player.locationid+steps>30)
        {
            GLOBAL::piiimap[PII((int)labelmovestagetimer,1)]=(30-player.locationid)*200;
            GLOBAL::piiimap[PII((int)labelmovestagetimer,2)]=(steps-(30-player.locationid))*200;
            playerrolewaypoint.push_back(blocks[30]->position);
        }
        if(player.locationid+steps>40)
        {
            GLOBAL::piiimap[PII((int)labelmovestagetimer,2)]=2000;
            GLOBAL::piiimap[PII((int)labelmovestagetimer,3)]=(steps-(40-player.locationid))*200;
            playerrolewaypoint.push_back(blocks[0]->position);
        }
    }
    else
    if(player.locationid>=30&&player.locationid<=39)
    {
        GLOBAL::piiimap[PII((int)labelmovestagetimer,1)]=steps*200;
        if(player.locationid+steps>40)
        {
            GLOBAL::piiimap[PII((int)labelmovestagetimer,1)]=(40-player.locationid)*200;
            GLOBAL::piiimap[PII((int)labelmovestagetimer,2)]=(steps-(40-player.locationid))*200;
            playerrolewaypoint.push_back(blocks[0]->position);
        }
        if(player.locationid+steps>50)
        {
            GLOBAL::piiimap[PII((int)labelmovestagetimer,2)]=2000;
            GLOBAL::piiimap[PII((int)labelmovestagetimer,3)]=(steps-(50-player.locationid))*200;
            playerrolewaypoint.push_back(blocks[10]->position);
        }
    }
    int desid=(player.locationid+steps>39)?player.locationid+steps-40:player.locationid+steps;
    player.locationid=desid;
    this->playerrolewaypoint.push_back(blocks[desid]->position);

    GLOBAL::piiimap[PII((int)labelmovestagetimer,0)]=0;//阶段数
    GLOBAL::piiimap[PII((int)labelmovestagetimer,10)]=player.id;//移动的玩家id
    LabelMoveStageTimer_TimeOut();
}

//之所以不用group，是因为我每一阶段都要有一些其他的动作，group做不到
void GameMainWidget::LabelMoveStageTimer_TimeOut()
{
    int timerstage=GLOBAL::piiimap[PII((int)labelmovestagetimer,0)];
    Player&player=*(players[GLOBAL::piiimap[PII((int)labelmovestagetimer,10)]]);
    QVector<QPoint>::iterator iter=playerrolewaypoint.begin()+timerstage;
    if(iter!=playerrolewaypoint.end())
    {
        QPoint waypoint=GetRandomQPointInRadiu(
                    QPoint(iter->x(),iter->y()),width/64,true);
        if(blocks[0]->rect.contains(*iter))
        {
            QTimer*timer=new QTimer;
            timer->setTimerType(Qt::PreciseTimer);
            GLOBAL::piiimap[PII((int)timer,0)]=playerordertoid[stageplayerorder];
            GLOBAL::piiimap[PII((int)timer,1)]=200;
            connect(timer,SIGNAL(timeout()),this,SLOT(PlayercashChangeInTime()));
            timer->start(GLOBAL::piiimap[PII((int)labelmovestagetimer,1+timerstage)]);
        }
        if(player.rolelabel)
        Labelmove(*(player.rolelabel),waypoint.x(),waypoint.y(),GLOBAL::piiimap[PII((int)labelmovestagetimer,1+timerstage)],1);
        labelmovestagetimer->start(GLOBAL::piiimap[PII((int)labelmovestagetimer,1+timerstage)]);
        GLOBAL::piiimap[PII((int)labelmovestagetimer,0)]=GLOBAL::piiimap[PII((int)labelmovestagetimer,0)]+1;
    }
    else
    {
        playerrolewaypoint.clear();
        labelmovestagetimer->stop();
        BlockCheck();
    }

}

//主要是隐藏完成按钮，和关闭正在打开的阶段窗口，取消阶段的任何操作，并判断是否失败
void GameMainWidget::StageFinish()
{
    pushbutton_stagefinish->hide();
    stagelabel->hide();
    pushbutton_failed_confirm->hide();
    pushbutton_travel->hide();

    for(int i=0;i<playernum;i++)
        pushbutton_tradeplayerlist[i]->hide();

    if(mywidget)
            mywidget->close();//有正在打开的窗口则关闭
    if(isbuilding)
    {
        PushButton_Build_Cancle_clicked();
    }
    if(isselling)
    {
        PushButton_Sell_Cancle_clicked();
    }
    if(istraveling)
    {
        Pushbutton_Travel_Cancle_clicked();
        pushbutton_travel->hide();
        pushbutton_travel_cancle->hide();
    }

    Player* player=players[playerordertoid[stageplayerorder]];
    if(player->cash<0)//失败
    {
        for(int i=0;i<40;i++)
            if(blocks[i]->type==BlockType::Available&&
            ((AvailableBlock*)blocks[i])->owner==player)
                    ((AvailableBlock*)blocks[i])->owner=NULL;

        player->isfailed=true;

        playeractivenum=0;
        for(int i=0;i<playernum;i++)
            if(players[i]->isfailed==false)playeractivenum++;

        QPainter painter(GameBackground),dpainter(GameBackgrounddarker);
        QPen pen;
        pen.setWidth(width/320);
        pen.setColor(Qt::darkRed);
        painter.setPen(pen);
        dpainter.setPen(pen);
        painter.drawRect(player->listrect);
        dpainter.drawRect(player->listrect);
        update();

        QPropertyAnimation *qpa=new QPropertyAnimation(player->rolelabel,"geometry");
        qpa->setDuration(2000);
        qpa->setStartValue(QRect(player->rolelabel->x(), player->rolelabel->y(), playerroleimagewidth, playerroleimagewidth));
        qpa->setEndValue(QRect(width*37/40,height/45,playerroleimagewidth,playerroleimagewidth));
             /*  设置动画效果  */
        qpa->setEasingCurve(QEasingCurve::InOutElastic);

        qpa->start(QAbstractAnimation::DeleteWhenStopped);

        QTimer *timer=new QTimer;
        timer->setTimerType(Qt::PreciseTimer);
        GLOBAL::piiimap[PII((int)timer,0)]=(int)(player->id);
        GLOBAL::piiimap[PII((int)timer,1)]=1;
        connect(timer,SIGNAL(timeout()),this,SLOT(DeleteLater()));

        timer->start(2500);

        if(playeractivenum<=1)
        {
            stage=Stage::OVER;
        }
    }

}

//玩家角色移动完毕后检查区块类型并触发响应事件
void GameMainWidget::BlockCheck()
{
    const Player&player=*(players[playerordertoid[stageplayerorder]]);
    const Block* blockp=blocks[player.locationid];
    switch(blockp->type)
    {
    case BlockType::Available:
    {
         AvailableBlock*ablockp=(AvailableBlock*)blockp;
        if(ablockp->owner==NULL)//若此地无主
        {
            //弹出购买或者竞价窗口，并显示相应信息
            SetOperable(false);

            if(stagecounter)
            {
                iscount=true;

                mywidget=new MyWidget(MyWidgetType::Purchasing,
                                      players[playerordertoid[stageplayerorder]]->locationid,
                        playerordertoid[stageplayerorder]);
                mywidget->show();//把stagepushbutton显示任务交给mywidgetreturn
            }
            else
            {
                SetPause();
                mydialog= new MyDialog(MyDialogType::Bidding);

                mydialog->setWindowFlags(windowFlags()|Qt::FramelessWindowHint);
                mydialog->arg1=players[playerordertoid[stageplayerorder]]->locationid;//传递区块id
                mydialog->setWindowTitle(tr("竞价"));
                mydialog->exec();
                SetContinue();

                ShowPlayerStageButton();

                PlayercashChange(mydialog->arg2,-1*(mydialog->arg1));
                AvailableBlockowning((AvailableBlock*)blocks[players[playerordertoid[stageplayerorder]]->locationid],mydialog->arg2);
            }

        }
        else//若此地有主
        {
            if(ablockp->owner!=players[playerordertoid[stageplayerorder]])
                //非自己地盘
            switch(ablockp->type)
            {
            case AvailableBlockType::Buildable:
            {
                BuildableBlock*bblockp=(BuildableBlock*)blockp;
                if(ablockp->owner->ddls==0)
                {
                    if(playerfornow->iscashprotected!=true)
                    {
                        int cost =bblockp->chargebase+bblockp->level*bblockp->chargeperlevel;
                        PlayercashChange(playerordertoid[stageplayerorder],-1*cost);
                        PlayercashChange(ablockp->owner->id,cost);
                    }
                    else
                    {
                        {
                            QPixmap pixmap;
                            pixmap=QPixmap::fromImage(*(playerfornow->image));
                            pixmap=pixmap.scaled(playerroleimagewidth,playerroleimagewidth,Qt::IgnoreAspectRatio);
                            playerfornow->rolelabel->setPixmap(pixmap);
                        }
                        playerfornow->iscashprotected=false;
                    }
                }
                ShowPlayerStageButton();
                break;
            }
            case AvailableBlockType::BusStop:
            {
                if(playerfornow->iscashprotected!=true)
                {
                    int exp=1;
                    if(((AvailableBlock*)blocks[5])->owner==ablockp->owner)exp*=2;
                    if(((AvailableBlock*)blocks[15])->owner==ablockp->owner)exp*=2;
                    if(((AvailableBlock*)blocks[25])->owner==ablockp->owner)exp*=2;
                    if(((AvailableBlock*)blocks[35])->owner==ablockp->owner)exp*=2;
                    PlayercashChange(playerordertoid[stageplayerorder],-1*(exp/2*25));
                    PlayercashChange(ablockp->owner->id,exp/2*25);
                }
                else
                {
                    {
                        QPixmap pixmap;
                        pixmap=QPixmap::fromImage(*(playerfornow->image));
                        pixmap=pixmap.scaled(playerroleimagewidth,playerroleimagewidth,Qt::IgnoreAspectRatio);
                        playerfornow->rolelabel->setPixmap(pixmap);
                    }
                    playerfornow->iscashprotected=false;
                }

                ShowPlayerStageButton();
                break;
            }
            }
            else//自己地盘
            {
                if(ablockp->type==AvailableBlockType::BusStop&&isdicebuttonclicked)
                {
                    int busstopcount=0;
                    for(int i=5;i<45;i+=10)
                    if(((AvailableBlock*)blocks[i])->owner==ablockp->owner)busstopcount++;
                    if(busstopcount>1)
                    pushbutton_travel->show();
                }
                ShowPlayerStageButton();
            }
        }
        break;
    }
    case BlockType::Specific:
    {
        const SpecificBlock* sblockp=(SpecificBlock*)blocks[player.locationid];
        switch(sblockp->type)
        {
        case SpecificBlockType::RandomEvent:
        {
            pushbutton_stagefinish->hide();
            stagelabel->hide();
            pushbutton_failed_confirm->hide();

            QString hintstr;
            SetOperable(false);
            if(randomeventsremain<1)
            {
                disorderintarray(randomeventstypeorder,5);
                randomeventsremain=5;
            }
            randomeventsremain--;
                switch(randomeventstypeorder[randomeventsremain])
                {
                case 0:
                {
                    isdicebuttonclicked=true;
                    pushbutton_dice->hide();
                    stagelabel->hide();
                    hintstr=tr("吃街边小吃吃坏肚子，送去医院治疗，支付100");
                    break;
                }
                case 1:
                {
                    int blockid=qrand()%40;
                    while(blocks[blockid]->type!=BlockType::Available||
                          ((AvailableBlock*)blocks[blockid])->type!=AvailableBlockType::Buildable)
                        blockid=qrand()%40;

                    hintstr=tr("搭便车去")+blocks[blockid]->name;
                    GLOBAL::piiimap[PII((int)hinttimer,1)]=blockid;
                    break;
                }
                case 2:{hintstr=tr("逛街过度，身心俱疲，休息一轮");players[playerordertoid[stageplayerorder]]->resttimes=1;break;}
                case 3:{hintstr=tr("收到客户需求，赶去图书馆赶DDL");break;}
                case 4:{hintstr=tr("获得免费游玩券");break;}
                }
            //绘制hintlabel
                {
                    QPixmap pixmap(GLOBAL::ssmap["Hint"]);
                    pixmap=pixmap.scaled(pixmap.width()*5/6,pixmap.height()*5/12);
                    QPainter painter(&pixmap);
                    QPen pen;
                    QFont font(*fontdefault);
                    const int hintwidth=cardfront->width(),hintheight=hintlabel->width();

                    pen.setColor(QColor(0,0,0,255));
                    font.setPointSize(hintwidth/22);
                    font.setLetterSpacing(QFont::AbsoluteSpacing,hintwidth/140);
                    painter.setPen(pen);
                    painter.setFont(font);

                    QTextOption option(Qt::AlignLeft | Qt::AlignTop);
                    option.setWrapMode(QTextOption::WordWrap);

                    painter.drawText(QRect(hintwidth*3/10,hintheight/10,hintwidth,hintheight*4/5), hintstr, option);

                    hintlabel->setPixmap(pixmap);
                    hintlabel->move(width*3/2,height*3/2);
                }

            GLOBAL::piiimap[PII((int)hinttimer,0)]=3;
            GLOBAL::piiimap[PII((int)hinttimer,2)]=0;//DDL警告识别

            HintTimer_TimeOut();//ShowPlayerStageButton();

            break;
        }
        case SpecificBlockType::LuckCard:
        {
            pushbutton_stagefinish_failed_alternate->hide();
            CardReversal();//ShowPlayerStageButton();
            break;
        }
        case SpecificBlockType::Deadline:
        {
            players[playerordertoid[stageplayerorder]]->ddls=3;
            pushbutton_stagefinish->hide();
            stagelabel->hide();
            pushbutton_failed_confirm->hide();

            QString hintstr(tr("收到DDL警告，拖入图书馆闭关3轮"));
            SetOperable(false);
            //绘制hintlabel
                {
                    QPixmap pixmap(GLOBAL::ssmap["Hint"]);
                    pixmap=pixmap.scaled(pixmap.width()*5/6,pixmap.height()*5/12);
                    QPainter painter(&pixmap);
                    QPen pen;
                    QFont font(*fontdefault);
                    const int hintwidth=cardfront->width(),hintheight=hintlabel->width();

                    pen.setColor(QColor(0,0,0,255));
                    font.setPointSize(hintwidth/22);
                    font.setLetterSpacing(QFont::AbsoluteSpacing,hintwidth/140);
                    painter.setPen(pen);
                    painter.setFont(font);

                    QTextOption option(Qt::AlignLeft | Qt::AlignTop);
                    option.setWrapMode(QTextOption::WordWrap);

                    painter.drawText(QRect(hintwidth*3/10,hintheight/10,hintwidth,hintheight*4/5), hintstr, option);

                    hintlabel->setPixmap(pixmap);
                    hintlabel->move(width*3/2,height*3/2);
                }
            GLOBAL::piiimap[PII((int)hinttimer,0)]=3;
            GLOBAL::piiimap[PII((int)hinttimer,2)]=1;//DDL警告识别
            HintTimer_TimeOut();
            break;
        }
        default:ShowPlayerStageButton();break;
        }
        break;
    }
    default:ShowPlayerStageButton();break;
    }
}

void GameMainWidget::MyWidgetReturn(MyWidget* returnevent)
{
    mywidget=NULL;
    switch(returnevent->type)
    {
    case MyWidgetType::Trading:
    {
        if(GLOBAL::piiimap[PII((int)returnevent,0)]==1)//1代表accpet
        {
            QVector<QCheckBox*>::iterator iter=returnevent->checkboxes_l->begin();
            for(;iter!=returnevent->checkboxes_l->end();iter++)
            {
                if((*iter)->isChecked()==true)
                    AvailableBlockowning((AvailableBlock*)blocks[GLOBAL::piiimap[PII((int)(*iter),0)]],returnevent->arg2);
                PIIIMAP::iterator piiimapiter=GLOBAL::piiimap.find(PII((int)(*iter),0));
                if(piiimapiter!=GLOBAL::piiimap.end())GLOBAL::piiimap.erase(piiimapiter);
            }
            iter=returnevent->checkboxes_r->begin();
            for(;iter!=returnevent->checkboxes_r->end();iter++)
            {
                if((*iter)->isChecked()==true)
                    AvailableBlockowning((AvailableBlock*)blocks[GLOBAL::piiimap[PII((int)(*iter),0)]],returnevent->arg1);
                PIIIMAP::iterator piiimapiter=GLOBAL::piiimap.find(PII((int)(*iter),0));
                if(piiimapiter!=GLOBAL::piiimap.end())GLOBAL::piiimap.erase(piiimapiter);
            }
            PlayercashChange(returnevent->arg1,returnevent->spinbox_r->value()-1*(returnevent->spinbox_l->value()));
            PlayercashChange(returnevent->arg2,returnevent->spinbox_l->value()-1*(returnevent->spinbox_r->value()));
        }
        break;
    }
    case MyWidgetType::Purchasing:
    {
        if(GLOBAL::piiimap[PII((int)returnevent,0)]==1)//1代表承包
        {
            PlayercashChange(playerordertoid[stageplayerorder],-1*(((AvailableBlock*)(blocks[players[playerordertoid[stageplayerorder]]->locationid]))->purchaseprice));
            AvailableBlockowning((AvailableBlock*)blocks[players[playerordertoid[stageplayerorder]]->locationid],playerordertoid[stageplayerorder]);
            ShowPlayerStageButton();
        }
        else//竞价
        {
            returnevent->hide();
            SetOperable(false);
            SetPause();
            mydialog= new MyDialog(MyDialogType::Bidding);
            mydialog->setWindowTitle(tr("竞价"));
            mydialog->setWindowFlags(windowFlags()|Qt::FramelessWindowHint);
            mydialog->arg1=returnevent->arg1;//传递区块id
            mydialog->exec();
            SetContinue();

            PlayercashChange(mydialog->arg2,-1*(mydialog->arg1));
            AvailableBlockowning((AvailableBlock*)blocks[returnevent->arg1],mydialog->arg2);

            ShowPlayerStageButton();

            delete mydialog;
            mydialog=NULL;
        }
        break;
    }
    case MyWidgetType::DDL:
    {
        isdicebuttonclicked=false;
        pushbutton_dice->show();
        if(returnevent->arg1==1)
        {
            PlayercashChange(playerordertoid[stageplayerorder],-100);
            players[playerordertoid[stageplayerorder]]->ddls=0;
        }
    }
    default:break;
    }
    PIIIMAP::iterator iter=GLOBAL::piiimap.find(PII((int)returnevent,0));
    if(iter!=GLOBAL::piiimap.end())iter=GLOBAL::piiimap.erase(iter);

    SetOperable(true);
    pushbutton_menu->setEnabled(true);
    pushbutton_quit->setEnabled(true);
    delete returnevent;

}

void GameMainWidget::PushButton_Build_clicked()
{
    if(istradeplayerlistshown)
    for(int i=0;i<playernum;i++)
    {
        pushbutton_tradeplayerlist[i]->hide();
        if(players[i]->rolelabel)
        players[i]->rolelabel->show();
    }

    pushbutton_build->hide();
    pushbutton_build_cancle->show();
    SetOperable(false);
    pushbutton_menu->setEnabled(false);
    pushbutton_quit->setEnabled(false);
    GameBackgroundalternate=GameBackgrounddarker;


    Player*player=players[playerordertoid[stageplayerorder]];
    bool ischecked[40];
    for(int i=0;i<40;i++)ischecked[i]=false;
    for(int i=0;i<40;i++)
    {
        if(ischecked[i]==false&&blocks[i]->type==BlockType::Available&&
                ((AvailableBlock*)blocks[i])->type==AvailableBlockType::Buildable)
        {
            BuildableBlock*blockp=(BuildableBlock*)blocks[i];
            if(blockp->owner==player)
            {
                if(blockp->buildneed_f==NULL)//单成一体
                {
                    operablebuildablocksv.push_back(blockp);
                }
                else
                if(blockp->buildneed_f&&blockp->buildneed_s==NULL)//两块一体
                {
                    ischecked[blockp->buildneed_f->id]=true;
                    if(blockp->buildneed_f->owner==player)
                    {
                        operablebuildablocksv.push_back(blockp);
                        operablebuildablocksv.push_back(blockp->buildneed_f);
                    }
                }
                else
                if(blockp->buildneed_f&&blockp->buildneed_s)//三块一体
                {
                    ischecked[blockp->buildneed_f->id]=true;
                    ischecked[blockp->buildneed_s->id]=true;
                    if(blockp->buildneed_f->owner==player&&blockp->buildneed_s->owner==player)
                    {
                        operablebuildablocksv.push_back(blockp);
                        operablebuildablocksv.push_back(blockp->buildneed_f);
                        operablebuildablocksv.push_back(blockp->buildneed_s);
                    }
                }

            }
        }
        ischecked[i]=true;
    }

    {
        QString hintstr(tr("只有一条街区的所有区块都是你的你才可以升级它们，点击高亮地块即可升级"));
        QPixmap pixmap(GLOBAL::ssmap["Hint"]);
        pixmap=pixmap.scaled(pixmap.width()*5/6,pixmap.height()*5/12);
        QPainter painter(&pixmap);
        QPen pen;
        QFont font(*fontdefault);
        const int hintwidth=cardfront->width(),hintheight=hintlabel->width();

        pen.setColor(QColor(0,0,0,255));
        font.setPointSize(hintwidth/22);
        font.setLetterSpacing(QFont::AbsoluteSpacing,hintwidth/140);
        painter.setPen(pen);
        painter.setFont(font);

        QTextOption option(Qt::AlignLeft | Qt::AlignTop);
        option.setWrapMode(QTextOption::WordWrap);

        painter.drawText(QRect(hintwidth*3/10,hintheight/10,hintwidth,hintheight*4/5), hintstr, option);

        hintlabel->setPixmap(pixmap);
        hintlabel->move(width*11/32,height/8);
        hintlabel->show();
        hintrolelabel->move(width*17/64,height*7/24);
    }


    for(QVector<BuildableBlock*>::iterator iter=operablebuildablocksv.begin();
            iter!=operablebuildablocksv.end();iter++)
        (*iter)->isoperateallowed=true;

    iscount=true;
    isbuilding=true;
    update();

}

void GameMainWidget::PushButton_Build_Cancle_clicked()
{
    if(istradeplayerlistshown)
    for(int i=0;i<playernum;i++)
    {
        pushbutton_tradeplayerlist[i]->hide();
        if(players[i]->rolelabel)
        players[i]->rolelabel->show();
    }

    pushbutton_build_cancle->hide();
    pushbutton_build->show();
    SetOperable(true);
    pushbutton_menu->setEnabled(true);
    pushbutton_quit->setEnabled(true);
    GameBackgroundalternate=GameBackground;
    isbuilding=false;

    hintlabel->move(width*3/2,height*3/2);
    hintrolelabel->move(width*3/2,height*3/2);

    for(QVector<BuildableBlock*>::iterator iter=operablebuildablocksv.begin();
            iter!=operablebuildablocksv.end();iter++)
        (*iter)->isoperateallowed=false;
    operablebuildablocksv.clear();
    update();


}

void GameMainWidget::PushButton_Sell_clicked()
{
    if(istradeplayerlistshown)
    for(int i=0;i<playernum;i++)
    {
        pushbutton_tradeplayerlist[i]->hide();
        if(players[i]->rolelabel)
        players[i]->rolelabel->show();
    }

    pushbutton_sell->hide();
    pushbutton_sell_cancle->show();
    SetOperable(false);
    pushbutton_menu->setEnabled(false);
    pushbutton_quit->setEnabled(false);
    GameBackgroundalternate=GameBackgrounddarker;

    Player*player=players[playerordertoid[stageplayerorder]];
    bool ischecked[40];
    for(int i=0;i<40;i++)ischecked[i]=false;
    for(int i=0;i<40;i++)
    {
        if(ischecked[i]==false&&blocks[i]->type==BlockType::Available&&
                ((AvailableBlock*)blocks[i])->type==AvailableBlockType::Buildable)
        {
            BuildableBlock*blockp=(BuildableBlock*)blocks[i];
            if(blockp->owner==player&&blockp->level>0)
                operablebuildablocksv.push_back(blockp);
        }
        ischecked[i]=true;
    }

    {
        QString hintstr(tr("你只可以出售升级过的区块，点击高亮地块即可出售"));
        QPixmap pixmap(GLOBAL::ssmap["Hint"]);
        pixmap=pixmap.scaled(pixmap.width()*5/6,pixmap.height()*5/12);
        QPainter painter(&pixmap);
        QPen pen;
        QFont font(*fontdefault);
        const int hintwidth=cardfront->width(),hintheight=hintlabel->width();

        pen.setColor(QColor(0,0,0,255));
        font.setPointSize(hintwidth/22);
        font.setLetterSpacing(QFont::AbsoluteSpacing,hintwidth/140);
        painter.setPen(pen);
        painter.setFont(font);

        QTextOption option(Qt::AlignLeft | Qt::AlignTop);
        option.setWrapMode(QTextOption::WordWrap);

        painter.drawText(QRect(hintwidth*3/10,hintheight/10,hintwidth,hintheight*4/5), hintstr, option);

        hintlabel->setPixmap(pixmap);
        hintlabel->move(width*11/32,height/8);
        hintlabel->show();
        hintrolelabel->move(width*17/64,height*7/24);
    }

    for(QVector<BuildableBlock*>::iterator iter=operablebuildablocksv.begin();
            iter!=operablebuildablocksv.end();iter++)
        (*iter)->isoperateallowed=true;

    iscount=true;
    isselling=true;
    update();
}

void GameMainWidget::PushButton_Sell_Cancle_clicked()
{
    if(istradeplayerlistshown)
    for(int i=0;i<playernum;i++)
    {
        pushbutton_tradeplayerlist[i]->hide();
        if(players[i]->rolelabel)
        players[i]->rolelabel->show();
    }

    pushbutton_sell_cancle->hide();
    pushbutton_sell->show();
    SetOperable(true);
    pushbutton_menu->setEnabled(true);
    pushbutton_quit->setEnabled(true);
    GameBackgroundalternate=GameBackground;
    isselling=false;

    hintlabel->move(width*3/2,height*3/2);
    hintrolelabel->move(width*3/2,height*3/2);

    for(QVector<BuildableBlock*>::iterator iter=operablebuildablocksv.begin();
            iter!=operablebuildablocksv.end();iter++)
        (*iter)->isoperateallowed=false;
    operablebuildablocksv.clear();
    update();
}

void GameMainWidget::PlayercashChange(const int playerid,const int howmuch)
{
    if(howmuch)
    {
        QLabel*textlabel=new QLabel(this);
        QTimer *deletetimer=new QTimer;
        GLOBAL::piiimap[PII((int)deletetimer,0)]=(int)textlabel;
        GLOBAL::piiimap[PII((int)deletetimer,1)]=0;

        QFont font("微软雅黑",width/80,QFont::Bold,true);

        textlabel->setFont(font);
        textlabel->setGeometry(players[playerid]->listrect.x()-width/96,players[playerid]->listrect.y()+players[playerid]->listrect.height()/2,
                          width/8,width/40);
        players[playerid]->cash+=howmuch;
        textlabel->setText("¥"+QString::number(howmuch));
        textlabel->setAlignment(Qt::AlignLeft);
        if(howmuch>0)
            textlabel->setStyleSheet("color:green;");
        else
            textlabel->setStyleSheet("color:red;");

        textlabel->show();

        Labelmove(*textlabel,players[playerid]->listrect.x(),players[playerid]->listrect.y()+players[playerid]->listrect.height()/2,1500,0);
        connect(deletetimer,SIGNAL(timeout()),this,SLOT(DeleteLater()));
        deletetimer->start(2000);

        if(players[playerordertoid[stageplayerorder]]->cash>=0&&pushbutton_failed_confirm->isHidden()==false)
        {
            pushbutton_failed_confirm->hide();
            if(players[playerordertoid[stageplayerorder]]->ddls==0)pushbutton_stagefinish->show();
            else stagelabel->hide();
        }
    }
}

//piiimap(p,1)的值 0为：QLabel;1为删除玩家角色图标
void GameMainWidget::DeleteLater()
{
    QTimer*timer=(QTimer*)sender();

    switch(GLOBAL::piiimap[PII((int)timer,1)])
    {
    case 0:delete (QLabel*)GLOBAL::piiimap[PII((int)timer,0)];break;
    case 1:delete players[GLOBAL::piiimap[PII((int)timer,0)]]->rolelabel;
        players[GLOBAL::piiimap[PII((int)timer,0)]]->rolelabel=NULL;
    break;
    }

    PIIIMAP::iterator iter=GLOBAL::piiimap.find(PII((int)timer,0));
    GLOBAL::piiimap.erase(iter);
    iter=GLOBAL::piiimap.find(PII((int)timer,1));
    GLOBAL::piiimap.erase(iter);

    delete timer;

}

void GameMainWidget::AvailableBlockowning(AvailableBlock* block,const int ownerid)
{
    block->owner=players[ownerid];
    update();
}

void GameMainWidget::SetPause()
{
    if(stage!=GameMainWidget::Stage::PAUSE)
    {
        nextstage=stage;
        nextstagecounter=stagecounter;
    }
    stage=GameMainWidget::Stage::PAUSE;
    stagecounter=9999;
    ispause=true;
    stagestring="Pause";
    SetOperable(false);
    pushbutton_menu->setEnabled(false);
    pushbutton_quit->setEnabled(false);
    GameBackgroundalternate=GameBackgrounddarker;
    update();
}

void GameMainWidget::SetContinue()
{
    if(nextstage!=Stage::START)
    {
        SetOperable(true);
    }
    pushbutton_menu->setEnabled(true);
    pushbutton_quit->setEnabled(true);
    iscount=true;
    GameBackgroundalternate=GameBackground;
    ispause=false;
    update();
    stagecounter=0;
}

void GameMainWidget::PlayercashChangeInTime()
{
    QTimer* timer=(QTimer*)sender();
    PlayercashChange(GLOBAL::piiimap[PII((int)timer,0)],GLOBAL::piiimap[PII((int)timer,1)]);

    PIIIMAP::iterator iter=GLOBAL::piiimap.find(PII((int)timer,0));
    if(iter!=GLOBAL::piiimap.end())GLOBAL::piiimap.erase(iter);
    iter=GLOBAL::piiimap.find(PII((int)timer,1));
    if(iter!=GLOBAL::piiimap.end())GLOBAL::piiimap.erase(iter);

    delete timer;
}

void GameMainWidget::Pushbutton_Travel_clicked()
{
    if(istradeplayerlistshown)
    for(int i=0;i<playernum;i++)
    {
        pushbutton_tradeplayerlist[i]->hide();
        if(players[i]->rolelabel)
        players[i]->rolelabel->show();
    }

    pushbutton_travel->hide();
    pushbutton_travel_cancle->show();
    SetOperable(false);
    pushbutton_menu->setEnabled(false);
    pushbutton_quit->setEnabled(false);
    GameBackgroundalternate=GameBackgrounddarker;

    iscount=true;
    istraveling=true;
    update();
}

void GameMainWidget::Pushbutton_Travel_Cancle_clicked()
{
    if(istradeplayerlistshown)
    for(int i=0;i<playernum;i++)
    {
        pushbutton_tradeplayerlist[i]->hide();
        if(players[i]->rolelabel)
        players[i]->rolelabel->show();
    }
    pushbutton_travel_cancle->hide();
    pushbutton_travel->show();
    SetOperable(true);
    pushbutton_menu->setEnabled(true);
    pushbutton_quit->setEnabled(true);
    GameBackgroundalternate=GameBackground;
    istraveling=false;
    update();
}

void GameMainWidget::PlayerRoleTravel(Player&player,const int desid,bool ischeckblock)
//通过搭车、随机事件而调用的玩家角色移动函数
{
    SetOperable(false);
    if(testcmd)
    {
        pushbutton_dice->hide();
        stagelabel->hide();
        isdicebuttonclicked=true;
        testcmd=false;
    }
    playerrolewaypoint.clear();
    int steps;
    if(desid<=player.locationid)steps=40-player.locationid+desid;
    else
        steps=desid-player.locationid;
    if(player.locationid>=0&&player.locationid<10)
    {

        if(desid<player.locationid&&desid>=0)
        {
            GLOBAL::piiimap[PII((int)playertravelstagetimer,1)]=200*(40-steps);
        }
        else
        {
            GLOBAL::piiimap[PII((int)playertravelstagetimer,1)]=200*steps;
            if(desid>10)
            {
                GLOBAL::piiimap[PII((int)playertravelstagetimer,1)]=200*(10-player.locationid);
                GLOBAL::piiimap[PII((int)playertravelstagetimer,2)]=200*(steps-(10-player.locationid));
                playerrolewaypoint.push_back(blocks[10]->position);
            }
            if(desid>20)
            {
                GLOBAL::piiimap[PII((int)playertravelstagetimer,2)]=2000;
                GLOBAL::piiimap[PII((int)playertravelstagetimer,3)]=200*(steps-(20-player.locationid));
                playerrolewaypoint.push_back(blocks[20]->position);
            }
            if(desid>30)
            {
                GLOBAL::piiimap[PII((int)playertravelstagetimer,3)]=2000;
                GLOBAL::piiimap[PII((int)playertravelstagetimer,4)]=200*(steps-(30-player.locationid));
                playerrolewaypoint.push_back(blocks[30]->position);
            }
        }

    }
    else
    if(player.locationid>=10&&player.locationid<20)
    {

        if(desid<player.locationid&&desid>=10)
        {
            GLOBAL::piiimap[PII((int)playertravelstagetimer,1)]=200*(40-steps);
        }
        else
        {
            if(desid<10)
            {
                GLOBAL::piiimap[PII((int)playertravelstagetimer,1)]=200*(20-player.locationid);
                playerrolewaypoint.push_back(blocks[20]->position);
                GLOBAL::piiimap[PII((int)playertravelstagetimer,2)]=2000;
                playerrolewaypoint.push_back(blocks[30]->position);
                GLOBAL::piiimap[PII((int)playertravelstagetimer,3)]=2000;
                playerrolewaypoint.push_back(blocks[0]->position);
                GLOBAL::piiimap[PII((int)playertravelstagetimer,4)]=200*(steps-(40-player.locationid));
            }
            else
            {
                GLOBAL::piiimap[PII((int)playertravelstagetimer,1)]=200*steps;
                if(desid>20)
                {
                    GLOBAL::piiimap[PII((int)playertravelstagetimer,1)]=200*(20-player.locationid);
                    GLOBAL::piiimap[PII((int)playertravelstagetimer,2)]=200*(steps-(20-player.locationid));
                    playerrolewaypoint.push_back(blocks[20]->position);
                }
                if(desid>30)
                {
                    GLOBAL::piiimap[PII((int)playertravelstagetimer,2)]=2000;
                    GLOBAL::piiimap[PII((int)playertravelstagetimer,3)]=200*(steps-(30-player.locationid));
                    playerrolewaypoint.push_back(blocks[30]->position);
                }
            }
        }

    }
    else
    if(player.locationid>=20&&player.locationid<30)
    {
        if(desid<player.locationid&&desid>=20)
        {
            GLOBAL::piiimap[PII((int)playertravelstagetimer,1)]=200*(40-steps);
        }
        else
        {
            if(desid<20)
            {
                GLOBAL::piiimap[PII((int)playertravelstagetimer,1)]=200*(30-player.locationid);
                playerrolewaypoint.push_back(blocks[30]->position);
                GLOBAL::piiimap[PII((int)playertravelstagetimer,2)]=2000;
                playerrolewaypoint.push_back(blocks[0]->position);
                GLOBAL::piiimap[PII((int)playertravelstagetimer,3)]=200*desid;
                if(desid>10)
                {

                    GLOBAL::piiimap[PII((int)playertravelstagetimer,3)]=2000;
                    GLOBAL::piiimap[PII((int)playertravelstagetimer,4)]=200*(desid-10);
                    playerrolewaypoint.push_back(blocks[10]->position);
                }

            }
            else
            {
                GLOBAL::piiimap[PII((int)playertravelstagetimer,1)]=200*steps;
                if(desid>30)
                {
                    GLOBAL::piiimap[PII((int)playertravelstagetimer,1)]=200*(30-player.locationid);
                    GLOBAL::piiimap[PII((int)playertravelstagetimer,2)]=200*(steps-(30-player.locationid));
                    playerrolewaypoint.push_back(blocks[30]->position);
                }
            }
        }

    }
    else
    if(player.locationid>=30&&player.locationid<40)
    {
        if(desid<player.locationid&&desid>=20)
        {
            GLOBAL::piiimap[PII((int)playertravelstagetimer,1)]=200*(40-steps);
        }
        else
        {
            if(desid>player.locationid)
                GLOBAL::piiimap[PII((int)playertravelstagetimer,1)]=200*steps;
            else
            {
                GLOBAL::piiimap[PII((int)playertravelstagetimer,1)]=200*(40-player.locationid);
                GLOBAL::piiimap[PII((int)playertravelstagetimer,2)]=200*(steps-(40-player.locationid));
                playerrolewaypoint.push_back(blocks[0]->position);
                if(desid>10)
                {
                    GLOBAL::piiimap[PII((int)playertravelstagetimer,2)]=2000;
                    GLOBAL::piiimap[PII((int)playertravelstagetimer,3)]=200*(steps-(50-player.locationid));
                    playerrolewaypoint.push_back(blocks[10]->position);
                }
                if(desid>20)
                {
                    GLOBAL::piiimap[PII((int)playertravelstagetimer,3)]=2000;
                    GLOBAL::piiimap[PII((int)playertravelstagetimer,4)]=200*(steps-(60-player.locationid));
                    playerrolewaypoint.push_back(blocks[20]->position);
                }
            }
        }
    }
    player.locationid=desid;
    this->playerrolewaypoint.push_back(blocks[desid]->position);

    GLOBAL::piiimap[PII((int)playertravelstagetimer,0)]=0;//当前进行到的阶段数

    GLOBAL::piiimap[PII((int)playertravelstagetimer,10)]=player.id;//移动的玩家id
    if(ischeckblock)GLOBAL::piiimap[PII((int)playertravelstagetimer,11)]=1;//移动结束后是否进行区块检查并展示完成按钮
    else
        GLOBAL::piiimap[PII((int)playertravelstagetimer,11)]=0;
    PlayerTravelStageTimer_TimeOut();
}

void GameMainWidget::PlayerTravelStageTimer_TimeOut()
{
    int timerstage=GLOBAL::piiimap[PII((int)playertravelstagetimer,0)];
    QVector<QPoint>::iterator iter=playerrolewaypoint.begin()+timerstage;
    Player& player=*(players[GLOBAL::piiimap[PII((int)playertravelstagetimer,10)]]);
    if(iter!=playerrolewaypoint.end())
    {
        QPoint waypoint=*iter;
        if(player.rolelabel)
        Labelmove(*(player.rolelabel),waypoint.x(),waypoint.y(),GLOBAL::piiimap[PII((int)playertravelstagetimer,1+timerstage)],0);
        playertravelstagetimer->start(GLOBAL::piiimap[PII((int)playertravelstagetimer,1+timerstage)]);
        GLOBAL::piiimap[PII((int)playertravelstagetimer,0)]=timerstage+1;
    }
    else
    {
        playerrolewaypoint.clear();
        playertravelstagetimer->stop();
        SetOperable(true);
        if(GLOBAL::piiimap[PII((int)playertravelstagetimer,11)]==1)
            BlockCheck();
    }
}

void GameMainWidget::PushButton_Chat_Widget_Show_clicked()
{
    ChatWidget *chatwidget=new ChatWidget;
    activechatwidgets.push_back(chatwidget);
    chatwidget->setWindowFlags(chatwidget->windowFlags()&~Qt::WindowMaximizeButtonHint&~Qt::WindowMinimizeButtonHint);
    chatwidget->setWindowTitle(tr("聊天"));
    chatwidget->show();
}

void GameMainWidget::ChatTextEdit_Changed()
{
    QVector<ChatWidget*>::iterator iter=activechatwidgets.begin();
    for(;iter!=activechatwidgets.end();iter++)
    {
        (*iter)->textbroser.setHtml(chattextedit.toHtml());
        (*iter)->textbroser.moveCursor(QTextCursor::End);
    }
}

void GameMainWidget::CardReversal()
{
    pushbutton_stagefinish->hide();
    pushbutton_failed_confirm->hide();
    pushbutton_dice->hide();
    stagelabel->hide();
    SetOperable(false);
    QString cardstr;
    if(cardsremain<1)
    {
        disorderintarray(cardtypeorder,7);
        cardsremain=7;
    }
    cardsremain--;
        switch(cardtypeorder[cardsremain])
        {
        case 0:{cardstr=tr("去公教路上拾金不昧，奖励100¥");break;}
        case 1:{cardstr=tr("在软件楼勤工助学工资到账，奖励200¥");break;}
        case 2:{cardstr=tr("帮助高三学生补课获得工资150¥");break;}
        case 3:{cardstr=tr("努力学习，成绩优异，获得奖学金300¥");break;}
        case 4:{cardstr=tr("参加社团轰趴，支付200¥");break;}
        case 5:{cardstr=tr("分摊宿舍电费，支付50¥");break;}
        case 6:{cardstr=tr("假期回家，路费支付250¥");break;}
        }
    cardreversaltimercount=500;
    *cardbacktemp=cardback->copy(0,0,cardback->width(),cardback->height());
    {
        QPixmap pixmap;
        pixmap.load(GLOBAL::ssmap["CardsFront"]);
        pixmap=pixmap.scaled(width/5,height*22/45);
        QPainter painter(&pixmap);
        QPen pen;
        QFont font(*fontdefault);
        const int cardwidth=cardfront->width(),cardheight=cardfront->height();

        pen.setColor(QColor(1,1,1,255));
        font.setPointSize(cardwidth/22);
        font.setLetterSpacing(QFont::AbsoluteSpacing,cardwidth/140);
        painter.setPen(pen);
        painter.setFont(font);

        QTextOption option(Qt::AlignLeft | Qt::AlignTop);
        option.setWrapMode(QTextOption::WordWrap);

        painter.drawText(QRect(cardwidth/5,cardheight/8,cardwidth*3/5,cardheight*4/5), cardstr, option);

        *cardfront=pixmap.toImage();
    }
    cardreversaltimer->start(10);
}

void GameMainWidget::CardReversalTimer_TimeOut()
{
    if(cardreversaltimercount)
    {
        if(cardreversaltimercount>=450)
        {
            cardreversx=width*9/80+width*17*(500-cardreversaltimercount)/4000;
        }
        else
        if(cardreversaltimercount>=400)//翻转
        {
            if(cardreversaltimercount>425)
            {
                *cardbacktemp=ImageShrinkScale(*cardback,cardback->width()*(cardreversaltimercount-425)/25,cardback->height());
                cardreversx=width*34/80-cardbacktemp->width()/2;
            }
            else
            if(cardreversaltimercount==425)
            {
                *cardbacktemp=ImageShrinkScale(*cardback,0,0);
                cardreversx=width*26/80;
            }
            else
            {
                *cardfronttemp=ImageShrinkScale(*cardfront,cardfront->width()*(425-cardreversaltimercount)/25,cardfront->height());
                cardreversx=width*34/80-cardfronttemp->width()/2;
            }
        }
        else
        if(cardreversaltimercount==399)
        {
            switch(cardtypeorder[cardsremain])
            {
                case 0:{PlayercashChange(playerordertoid[stageplayerorder],100);break;}
                case 1:{PlayercashChange(playerordertoid[stageplayerorder],200);break;}
                case 2:{PlayercashChange(playerordertoid[stageplayerorder],150);break;}
                case 3:{PlayercashChange(playerordertoid[stageplayerorder],300);break;}
                case 4:{PlayercashChange(playerordertoid[stageplayerorder],-200);break;}
                case 5:{PlayercashChange(playerordertoid[stageplayerorder],-50);break;}
                case 6:{PlayercashChange(playerordertoid[stageplayerorder],-250);break;}
            }
        }
        else
            if(cardreversaltimercount<=100)
            {
                if(cardreversaltimercount>75)
                {
                    *cardfronttemp=ImageShrinkScale(*cardfront,cardfront->width()*(cardreversaltimercount-75)/25,cardfront->height());
                    cardreversx=width*34/80-cardfronttemp->width()/2;
                }
                else
                if(cardreversaltimercount==75)
                {
                    *cardfronttemp=ImageShrinkScale(*cardfront,0,0);
                    cardreversx=width*26/80;
                }
                else
                if(cardreversaltimercount>=50)
                {
                    *cardbacktemp=ImageShrinkScale(*cardback,cardback->width()*(75-cardreversaltimercount)/25,cardback->height());
                    cardreversx=width*34/80-cardbacktemp->width()/2;
                }
                else
                if(cardreversaltimercount<50)//收回卡牌
                {
                    cardreversx=width*9/80+width*17*cardreversaltimercount/4000;
                }
            }

        cardreversaltimercount--;
    }
    else
    {
        ShowPlayerStageButton();
        cardreversaltimer->stop();
    }
    update();
}

void GameMainWidget::HintTimer_TimeOut()
{
    int hintstagecount=GLOBAL::piiimap[PII((int)hinttimer,0)];
    switch(hintstagecount)
    {
    case 3:
    {
        Labelmove(*hintrolelabel,width*37/64+hintrolelabel->width()/2,height*41/48+hintrolelabel->height()/2,250,0);
        hinttimer->start(750);
        break;
    }
    case 2:
    {
        Labelmove(*hintrolelabel,width*17/64+hintrolelabel->width()/2,height*7/24+hintrolelabel->height()/2,500,1);
        hinttimer->start(500);
        break;
    }
    case 1://显示完全
    {
        hintlabel->show();
        hintlabel->move(width*11/32,height/8);
        if(GLOBAL::piiimap[PII((int)hinttimer,2)]==0)
        {
            switch(randomeventstypeorder[randomeventsremain])
            {
            case 0:
            {
                PlayercashChange(playerordertoid[stageplayerorder],-100);
                PlayerRoleTravel(*(players[playerordertoid[stageplayerorder]]),20,true);
                break;
            }
            case 1:
            {
                PlayerRoleTravel(*(players[playerordertoid[stageplayerorder]]),GLOBAL::piiimap[PII((int)hinttimer,1)],true);
                break;
            }
            case 2:
            {
                players[playerordertoid[stageplayerorder]]->resttimes=1;
                isdicebuttonclicked=true;
                ShowPlayerStageButton();
                break;
            }
            case 3:
            {
                PlayerRoleTravel(*(players[playerordertoid[stageplayerorder]]),10,true);
                players[playerordertoid[stageplayerorder]]->ddls=3;
                break;
            }
            case 4:
            {
                {
                    QPixmap pixmap;
                    pixmap=QPixmap::fromImage(*(playerfornow->image));
                    pixmap=pixmap.scaled(playerroleimagewidth,playerroleimagewidth,Qt::IgnoreAspectRatio);
                    QPainter painter(&pixmap);
                    QPen pen;
                    pen.setColor(QColor(0,200,225));
                    painter.setPen(pen);
                    pen.setWidth(playerroleimagewidth/10);
                    painter.setPen(pen);
                    painter.drawEllipse(playerroleimagewidth/10,playerroleimagewidth/10,playerroleimagewidth*4/5,playerroleimagewidth*4/5);
                    playerfornow->rolelabel->setPixmap(pixmap);
                }
                playerfornow->iscashprotected=true;
                ShowPlayerStageButton();
                break;
            }
            }
        }
        else
        {
            PlayerRoleTravel(*(playerfornow),10,true);
            players[playerordertoid[stageplayerorder]]->ddls=3;
            isdicebuttonclicked=true;
            stagecounter=1;
        }
        hinttimer->start(2500);
        break;
    }
    case 0:
    {
        hintlabel->hide();
        Labelmove(*hintrolelabel,width*3/2,height*3/2,500,1);
        hinttimer->stop();
        break;
    }
    }
    GLOBAL::piiimap[PII((int)hinttimer,0)]=hintstagecount-1;
}

void GameMainWidget::ShowDicePushButton()
{
    pushbutton_stagefinish->hide();
    pushbutton_failed_confirm->hide();
    pushbutton_dice->show();
    isdicebuttonclicked=false;
}

void GameMainWidget::ShowStageFinishPushButton()
{
    pushbutton_dice->hide();
    if(players[playerordertoid[stageplayerorder]]->cash>=0)
        pushbutton_stagefinish_failed_alternate=pushbutton_stagefinish;
    else
        pushbutton_stagefinish_failed_alternate=pushbutton_failed_confirm;
    pushbutton_stagefinish_failed_alternate->show();
}

void GameMainWidget::ShowPlayerStageButton()
{
    SetOperable(true);
    if(stagecounter||(stage==Stage::PAUSE&&stagecounter==0))
    {
        if(playerfornow->ddls==0)
        {
            stagelabel->show();
            if(isdicebuttonclicked)
                ShowStageFinishPushButton();
            else
                ShowDicePushButton();
        }
        else
        {
            isdicebuttonclicked=true;
            stagecounter=1;
        }
    }
    else
        StageFinish();
}
