#include "global.h"

typedef std::pair<int,int> PII;

typedef QMap<QString,QString> SSMAP;
typedef QMap<QString,int> SIMAP;
typedef QMap<PII,int> PIIIMAP;

SIMAP GLOBAL::simap;
SSMAP GLOBAL::ssmap;
PIIIMAP GLOBAL::piiimap;
MainWindow* GLOBAL::mainwindow;
GameMainWidget*GLOBAL::gamemainwidget;
bool GLOBAL::Gaming=true;bool GLOBAL::isplaymusic=true;
QPixmap* GLOBAL::IntroductionPixmap=NULL;

#ifdef DEBUG
unsigned long long LYL232::bugs=0;
unsigned long long LYL232::bugsfixed=0;
bool LYL232::theresnotwoLYL232s=false;
QVector<QString> LYL232::notes;

LYL232::LYL232()
{
    if(!theresnotwoLYL232s)
    {
        theresnotwoLYL232s=true;
        notes.push_back("我是LYL232,今天收到了从零敲大富翁的需求，我现在慌得一批——2018.7.4");
        notes.push_back("原谅我还没学会try catch这种东西。。所以。。。见谅");
        notes.push_back("个人觉得ui设计界面有点僵硬。。所以游戏主界面还是手算的。。。更僵硬了");
        notes.push_back("dynami_cast这个东西一定要虚函数，不然报错，但是确实没有虚函数的必要，所以我还是用C语言比较'笨'的方法了");
        notes.push_back("不得不承认，我的按钮状态切换、隐藏、显示做得真烂！没有一个好的框架设计真的是会带来大量BUG，下次下手写代码一定要设计一个框架！");
        notes.push_back("试玩效果不错，准备收工！-7.22");
        Classcpp();
        gamemainwidgetcpp();
        mainwindowcpp();
        mydialogcpp();
        mywidgetcpp();
        chatwidgetcpp();
    }
    else
    {
        LYL232* lyl232sangry=new LYL232;
        lyl232sangry->ago_when_LYL232_create_this_project=0;
        LYL232::bugs++;
        LYL232::bugsfixed=0;
    }

}

#endif


const double GLOBAL::pi=3.14159265358;

GLOBAL::GLOBAL()
{

    simap["InitialFund"]=3500;
    //屏幕分辨率
    simap["ResolutionWidth"]=1600;
    simap["ResolutionHeight"]=900;

    simap["ResolutionIndex"]=0;//分辨率组合框的索引

    simap["MusicVolume"]=50;

    simap["OperateTime"]=60;//玩家每轮能操作时间

    simap["Players"]=6;

    ssmap["Image0"]=":/new/prefix1/myimages/LYL232.png";
    ssmap["Image1"]=":/new/prefix1/myimages/PlayerImages/1-1.png";
    ssmap["Image2"]=":/new/prefix1/myimages/PlayerImages/1-2.png";
    ssmap["Image3"]=":/new/prefix1/myimages/PlayerImages/1-3.png";
    ssmap["Image4"]=":/new/prefix1/myimages/PlayerImages/1-4.png";
    ssmap["Image5"]=":/new/prefix1/myimages/PlayerImages/1-5.png";
    ssmap["Image6"]=":/new/prefix1/myimages/PlayerImages/1-6.png";
    ssmap["Image7"]=":/new/prefix1/myimages/PlayerImages/1-7.png";
    ssmap["Image8"]=":/new/prefix1/myimages/PlayerImages/2-1.png";
    ssmap["Image9"]=":/new/prefix1/myimages/PlayerImages/2-2.png";
    ssmap["Image10"]=":/new/prefix1/myimages/PlayerImages/2-3.png";
    ssmap["Image11"]=":/new/prefix1/myimages/PlayerImages/2-4.png";
    ssmap["Image12"]=":/new/prefix1/myimages/PlayerImages/2-5.png";
    ssmap["Image13"]=":/new/prefix1/myimages/PlayerImages/2-6.png";
    ssmap["Image14"]=":/new/prefix1/myimages/PlayerImages/2-7.png";
    ssmap["Image15"]=":/new/prefix1/myimages/PlayerImages/2-8.png";
    ssmap["Image16"]=":/new/prefix1/myimages/PlayerImages/2-9.png";
    ssmap["Image17"]=":/new/prefix1/myimages/PlayerImages/2-10.png";
    ssmap["Image18"]=":/new/prefix1/myimages/PlayerImages/2-11.png";
    ssmap["Image19"]=":/new/prefix1/myimages/PlayerImages/2-12.png";
    ssmap["Image20"]=":/new/prefix1/myimages/PlayerImages/3-1.png";
    ssmap["Image21"]=":/new/prefix1/myimages/PlayerImages/3-2.png";
    ssmap["Image22"]=":/new/prefix1/myimages/PlayerImages/3-3.png";
    ssmap["Image23"]=":/new/prefix1/myimages/PlayerImages/3-4.png";
    ssmap["Image24"]=":/new/prefix1/myimages/PlayerImages/3-5.png";
    ssmap["Image25"]=":/new/prefix1/myimages/PlayerImages/3-6.png";
    ssmap["Image26"]=":/new/prefix1/myimages/PlayerImages/3-7.png";
    ssmap["Image27"]=":/new/prefix1/myimages/PlayerImages/3-8.png";
    ssmap["Image28"]=":/new/prefix1/myimages/PlayerImages/3-9.png";
    ssmap["Image29"]=":/new/prefix1/myimages/PlayerImages/3-10.png";


    //玩家可选择的角色图标
    ssmap["PlayerImage0"]=ssmap["Image0"];
    ssmap["PlayerImage1"]=ssmap["Image0"];
    ssmap["PlayerImage2"]=ssmap["Image0"];
    ssmap["PlayerImage3"]=ssmap["Image0"];
    ssmap["PlayerImage4"]=ssmap["Image0"];
    ssmap["PlayerImage5"]=ssmap["Image0"];

    //绝对路径
    //GLOBAL::ssmap["image1"]="D:\\qt\\projects\\MyProject\\myimages\\xzydcjlx.png";
    //GLOBAL::ssmap["image2"]="D:\\qt\\projects\\MyProject\\myimages\\LYL232.png"
    ssmap["PlayerName0"]="player1";
    ssmap["PlayerName1"]="player2";
    ssmap["PlayerName2"]="player3";
    ssmap["PlayerName3"]="player4";
    ssmap["PlayerName4"]="player5";
    ssmap["PlayerName5"]="player6";

    ssmap["Numbers0"]=":/new/prefix1/myimages/numbers/0.png";
    ssmap["Numbers1"]=":/new/prefix1/myimages/numbers/1.png";
    ssmap["Numbers2"]=":/new/prefix1/myimages/numbers/2.png";
    ssmap["Numbers3"]=":/new/prefix1/myimages/numbers/3.png";
    ssmap["Numbers4"]=":/new/prefix1/myimages/numbers/4.png";
    ssmap["Numbers5"]=":/new/prefix1/myimages/numbers/5.png";
    ssmap["Numbers6"]=":/new/prefix1/myimages/numbers/6.png";
    ssmap["Numbers7"]=":/new/prefix1/myimages/numbers/7.png";
    ssmap["Numbers8"]=":/new/prefix1/myimages/numbers/8.png";
    ssmap["Numbers9"]=":/new/prefix1/myimages/numbers/9.png";
    ssmap["Plus"]=":/new/prefix1/myimages/numbers/plus.png";
    ssmap["Sub"]=":/new/prefix1/myimages/numbers/sub.png";

    ssmap["Dices1"]=":/new/prefix1/myimages/dices/1.png";
    ssmap["Dices2"]=":/new/prefix1/myimages/dices/2.png";
    ssmap["Dices3"]=":/new/prefix1/myimages/dices/3.png";
    ssmap["Dices4"]=":/new/prefix1/myimages/dices/4.png";
    ssmap["Dices5"]=":/new/prefix1/myimages/dices/5.png";
    ssmap["Dices6"]=":/new/prefix1/myimages/dices/6.png";

    ssmap["Level1"]=":/new/prefix1/myimages/levels/1.png";
    ssmap["Level2"]=":/new/prefix1/myimages/levels/2.png";
    ssmap["Level3"]=":/new/prefix1/myimages/levels/3.png";
    ssmap["Level4"]=":/new/prefix1/myimages/levels/4.png";
    ssmap["Level5"]=":/new/prefix1/myimages/levels/5.png";

    ssmap["PushButtonStyleSheetPassive"]="QPushButton{background-color:darkred;\
            color: white;   border-radius: 10px;  border: 2px groove gray;\
            border-style: outset;}"//按键本色
            "QPushButton:disabled{background-color:rgb(111,0,0); color: rgb(0,0,0)}"//禁止时的色彩
            "QPushButton:hover{background-color:white; color: black;}"//鼠标停放时的色彩
            "QPushButton:pressed{background-color:rgb(85, 170, 255);\
            border-style: inset; }";//鼠标按下的颜色

    ssmap["PushButtonStyleSheet1"]="QPushButton{background-color:rgb(1,107,187);\
            color: white;   border-radius: 10px;  border: 2px groove rgb(17,255,255);\
            border-style: outset;}"//按键本色
            "QPushButton:disabled{background-color:rgb(0,25,60); color: rgb(0,0,0)}"//禁止时的色彩
            "QPushButton:hover{background-color:white; color: rgb(183,250,250);}"//鼠标停放时的色彩
            "QPushButton:pressed{background-color:rgb(95, 211, 211);\
            border-style: inset; }";

    ssmap["GameBackGround"]=":/new/prefix1/myimages/gamebackground.png";
    ssmap["CardsBack"]=":/new/prefix1/myimages/cardsback.png";
    ssmap["CardsFront"]=":/new/prefix1/myimages/cardsfront.png";
    ssmap["Hint"]=":/new/prefix1/myimages/hint.png";
    ssmap["Library"]=":/new/prefix1/myimages/nankaijinnanlibrary.png";
    ssmap["Deadline"]=":/new/prefix1/myimages/deadline.png";
    ssmap["Hospital"]=":/new/prefix1/myimages/hospital.png";
    ssmap["HelloWorld"]=":/new/prefix1/myimages/helloworld.png";
    ssmap["Subway_LR"]=":/new/prefix1/myimages/subway_lr.png";
    ssmap["Subway_UD"]=":/new/prefix1/myimages/subway_ud.png";
    ssmap["Trade"]=":/new/prefix1/myimages/trade.png";
    ssmap["RandomEvent"]=":/new/prefix1/myimages/randomevent.png";
    ssmap["Clover"]=":/new/prefix1/myimages/clover.png";
    ssmap["Deadline_Widget"]=":/new/prefix1/myimages/deadline_widget.png";
    ssmap["MainWindowBackGround"]=":/new/prefix1/myimages/mainwindowbackground.png";
    ssmap["IntroDuctionBackGround"]=":/new/prefix1/myimages/introductionbackground.png";
    ssmap["SchoolGate"]=":/new/prefix1/myimages/schoolgate.png";


    IntroductionInitialize();
}

void GLOBAL::IntroductionInitialize()
{
    const int width=simap["ResolutionWidth"]/2,height=simap["ResolutionHeight"],maxheight=height*4;
    IntroductionPixmap=new QPixmap(width,maxheight);
    QPainter painter(IntroductionPixmap);
    QPen pen;
    QFont font("微软雅黑",width/40,QFont::Bold,false);

    {
        QPixmap pixmap(ssmap["IntroDuctionBackGround"]);
        pixmap.scaled(width,maxheight);
        painter.drawPixmap(0,0,width,maxheight,pixmap);
    }

    QTextOption option(Qt::AlignLeft | Qt::AlignTop);
    option.setWrapMode(QTextOption::WordWrap);

    font.setPointSize(width/18);
    pen.setColor(QColor(0,0,0,233));
    painter.setFont(font);
    painter.setPen(pen);
    painter.drawText(QRect(width/20,height/25,width,width/5),"游戏说明：", option);

    font.setPointSize(width/30);
    pen.setColor(QColor(254,67,101,180));
    painter.setFont(font);
    painter.setPen(pen);
    painter.drawText(QRect(width/20,height*4/24,width,width/5),"游戏开始：", option);

    font.setPointSize(width/45);
    pen.setColor(QColor(66,88,78,255));
    painter.setFont(font);
    painter.setPen(pen);
    painter.drawText(QRect(width*2/20,height*7/24,width*4/5,width/5),
                     "每位玩家游戏开始时都有一定浪的资本，可以在设置界面进行设置。点击本地游戏按钮后需进行玩家自定义设置，设置完毕会随机打乱玩家的进行顺序，之后后游戏开始。", option);


    font.setPointSize(width/45);
    pen.setColor(QColor(66,88,78,255));
    painter.setFont(font);
    painter.setPen(pen);
    painter.drawText(QRect(width*2/20,height*11/24,width*4/5,width/5),
                     "游戏开始时，会有5秒钟倒计时，倒计时后进入第一个玩家的开始阶段", option);

    font.setPointSize(width/30);
    pen.setColor(QColor(254,67,101,180));
    painter.setFont(font);
    painter.setPen(pen);
    painter.drawText(QRect(width/20,height*14/24,width,width/5),
                     "玩家阶段：", option);

    font.setPointSize(width/45);
    pen.setColor(QColor(66,88,78,255));
    painter.setFont(font);
    painter.setPen(pen);
    painter.drawText(QRect(width*2/20,height*17/24,width*4/5,width/3),
                     "每个玩家开始阶段屏幕中心会出现投骰子图标，点击投骰子图标玩家随即会根据两个骰子点数相加的结果进行移动，移动到不同的区块有不同的触发事件。当骰子的点数相同时，将强制奖励多一次骰子机会和一些时间", option);

    font.setPointSize(width/45);
    pen.setColor(QColor(66,88,78,255));
    painter.setFont(font);
    painter.setPen(pen);
    painter.drawText(QRect(width*2/20,height*23/24,width*4/5,width/5),
                     "在每个玩家的阶段可以进行与其他玩家的交易、对自己所有符合条件的区块进行升级和对已升级的地块出售的操作。每个玩家阶段有固定的操作时间。可在设置界面设置", option);

    font.setPointSize(width/30);
    pen.setColor(QColor(254,67,101,180));
    painter.setFont(font);
    painter.setPen(pen);
    painter.drawText(QRect(width/20,height*28/24,width,width/5),
                     "区块：", option);

    font.setPointSize(width/45);
    pen.setColor(QColor(66,88,78,255));
    painter.setFont(font);
    painter.setPen(pen);
    painter.drawText(QRect(width*2/20,height*30/24,width*4/5,width/5),
                     "特殊区块：DDL警告、随机事件、幸运卡牌、Hello World!、图书馆、医院。", option);

    font.setPointSize(width/45);
    pen.setColor(QColor(66,88,78,255));
    painter.setFont(font);
    painter.setPen(pen);
    painter.drawText(QRect(width*2/20,height*33/24,width*4/5,width/3),
                     "可获得区块：所有标有价格的区块，分为车站和普通区块。"
                     "当玩家移动到该种类区块时，若无人拥有，玩家可选择承包之或与所有玩家竞价拥有，但玩家不可获得竞价成功后的收益"
                     "当玩家移动到另一个玩家所有的可获得区块时，该区块所有者将会获得一定收益，但当玩家拥有免费游玩券时，将被其抵消。", option);

    font.setPointSize(width/45);
    pen.setColor(QColor(66,88,78,255));
    painter.setFont(font);
    painter.setPen(pen);
    painter.drawText(QRect(width*2/20,height*41/24,width*4/5,width/5),
                     "Helloworld：每次通过投骰子到达或经过“Hello World！”地块，可以获得200收益。", option);

    font.setPointSize(width/45);
    pen.setColor(QColor(66,88,78,255));
    painter.setFont(font);
    painter.setPen(pen);
    painter.drawText(QRect(width*2/20,height*44/24,width*4/5,width/2),
                     "DDL警告与图书馆：当玩家移动的终点为DDL警告或者受到随机事件而进入DDL状态时，将会被拖入图书馆中，"
                     "取消当前阶段的操作，并进入持续3轮的DDL状态，该状态下玩家不可获得收益。"
                     "并且轮到处于该状态的玩家的阶段时，会让玩家进行选择掷出同点还是支付。选择前者"
                     "如果出现同点结果，则玩家可直接根据该结果移动，若否，则跳过该玩家的阶段。若选择后者"
                     "则玩家阶段正常进行。", option);

    font.setPointSize(width/45);
    pen.setColor(QColor(66,88,78,255));
    painter.setFont(font);
    painter.setPen(pen);
    painter.drawText(QRect(width*2/20,height*54/24,width*4/5,width/2),
                     "随机事件与幸运卡牌：会根据卡牌上或提示内容进行事件触发。", option);

    font.setPointSize(width/45);
    pen.setColor(QColor(66,88,78,255));
    painter.setFont(font);
    painter.setPen(pen);
    painter.drawText(QRect(width*2/20,height*57/24,width*4/5,width/2),
                     "车站：当玩家投骰子的终点到达车站且无骰子机会，且玩家拥有的车站超过1个时，可触发搭车按钮，玩家可以选择直接移动到另一个车站所在地。", option);

    font.setPointSize(width/45);
    pen.setColor(QColor(66,88,78,255));
    painter.setFont(font);
    painter.setPen(pen);
    painter.drawText(QRect(width*2/20,height*61/24,width*4/5,width/2),
                     "普通区块：所有非车站可获得区块。所有被上述区块隔开的2至3个普通区块连成一个街区，有的甚至一个区块自成一个街区，只有当一个街区完全属于一个玩家时，该玩家才可对其进行升级操作。", option);

    font.setPointSize(width/30);
    pen.setColor(QColor(222,125,44,180));
    painter.setFont(font);
    painter.setPen(pen);
    painter.drawText(QRect(width/20,height*66/24,width,width/5),
                     "交易：", option);

    font.setPointSize(width/45);
    pen.setColor(QColor(20,68,106,255));
    painter.setFont(font);
    painter.setPen(pen);
    painter.drawText(QRect(width*2/20,height*69/24,width*4/5,width/2),
                     "在玩家的阶段，玩家可与其他玩家进行交易操作，交易需要双方商量好后选择内容点击接受即可。", option);

    font.setPointSize(width/30);
    pen.setColor(QColor(222,125,44,180));
    painter.setFont(font);
    painter.setPen(pen);
    painter.drawText(QRect(width/20,height*72/24,width,width/5),
                     "升级：", option);
    font.setPointSize(width/45);
    pen.setColor(QColor(20,68,106,255));
    painter.setFont(font);
    painter.setPen(pen);
    painter.drawText(QRect(width*2/20,height*75/24,width*4/5,width/2),
                     "在玩家的阶段，玩家可对其拥有的区块进行升级，由此增加收益", option);

    font.setPointSize(width/30);
    pen.setColor(QColor(222,125,44,180));
    painter.setFont(font);
    painter.setPen(pen);
    painter.drawText(QRect(width/20,height*78/24,width,width/5),
                     "出售：", option);
    font.setPointSize(width/45);
    pen.setColor(QColor(20,68,106,255));
    painter.setFont(font);
    painter.setPen(pen);
    painter.drawText(QRect(width*2/20,height*80/24,width*4/5,width/2),
                     "在玩家的阶段，玩家可对其拥有的有等级的区块进行出售，获取升级时耗费的半价。", option);

    font.setPointSize(width/30);
    pen.setColor(QColor(220,87,18,233));
    painter.setFont(font);
    painter.setPen(pen);
    painter.drawText(QRect(width/20,height*84/24,width,width/5),
                     "胜利条件：", option);
    font.setPointSize(width/45);
    pen.setColor(QColor(29,131,8,255));
    painter.setFont(font);
    painter.setPen(pen);
    painter.drawText(QRect(width*2/20,height*87/24,width*4/5,width/2),
                     "当一名玩家游戏阶段结束时，其当前资本数小于0，则判定为失败。失去对游戏的操作权", option);
    font.setPointSize(width/45);
    pen.setColor(QColor(29,131,8,255));
    painter.setFont(font);
    painter.setPen(pen);
    painter.drawText(QRect(width*2/20,height*90/24,width*4/5,width/2),
                     "当一名玩家失败时，若场上剩余玩家为一个，则其为胜利玩家。游戏结束。", option);


}

QPoint GetRandomQPointInRadiu(const QPoint&Center,const qreal Radiu,bool RandomDistance)
{
    if(RandomDistance)
    return QPoint(
                ((qreal)((qrand()%16384)-8196))*Radiu/16384+Center.x(),
                ((qreal)((qrand()%16384)-8196))*Radiu/16384+Center.y());
    else
    {
        double rad=(double)(qrand()%16384)/16384*2*GLOBAL::pi;
        return QPoint(std::cos(rad)*Radiu+Center.x(),
                      std::sin(rad)*Radiu+Center.y());
    }


}


QImage GreyScale(const QImage & origin, const int light)
{
    QImage newImage(origin.width(), origin.height(), QImage::Format_ARGB32);
    QColor oldColor;
    for(int x = 0; x<newImage.width(); x++)
        for(int y = 0; y<newImage.height(); y++)
        {
            oldColor = QColor(origin.pixel(x,y));
            int average = (oldColor.red()+oldColor.green()+oldColor.blue())*light/300;
            newImage.setPixel(x,y,qRgb(average,average,average));
        }
    return newImage;
}

QImage DarkScale(const QImage & origin,const int scale)
{
    QImage newImage(origin.width(), origin.height(), QImage::Format_ARGB32);
    QColor oldColor;
    for(int x = 0; x<newImage.width(); x++)
        for(int y = 0; y<newImage.height(); y++)
        {
            oldColor = QColor(origin.pixel(x,y));
            newImage.setPixel(x,y,qRgb(oldColor.red()/scale,oldColor.green()/scale,oldColor.blue()/scale));
        }
    return newImage;
}

QImage ImageShrinkScale(const QImage & source,const int width,const int height)
{
    if(width&&height)
    {
        QImage newImage(width, height, QImage::Format_ARGB32);
        const qreal widthscale=((qreal)source.width())/width;
        const qreal heightscale=((qreal)source.height())/height;
        QColor oldColor;
        for(int x = 0; x<width; x++)
            for(int y = 0; y<height; y++)
            {
                int xs=((qreal)x)*widthscale,ys=((qreal)y)*heightscale;
                if(xs>source.width())xs=source.width()-1;
                if(ys>source.height())ys=source.height()-1;
                oldColor = QColor(source.pixel(xs,ys));
                if(oldColor!=QColor(0,0,0))newImage.setPixel(x,y,qRgb(oldColor.red(),oldColor.green(),oldColor.blue()));
                else newImage.setPixelColor(x,y,QColor(255,255,255,0));
            }
        return newImage;
    }
    else
    {
        QImage newImage(1, 1, QImage::Format_ARGB32);
        newImage.setPixelColor(0,0,QColor(0,0,0,0));
        return newImage;
    }
}

void disorderintarray(int*array,const int num)
{
    for(int i=0;i<num;i++)*(array+i)=i;
    for(int i=num-1;i>=1;i--)
    {
        int index=qrand()%(i+1);
        //交换 [index] to [i]
        int temp=*(array+i);
        *(array+i)=*(array+index);
        *(array+index)=temp;
    }
}

void stringToHtmlFilter(QString &str)
{
   //注意这几行代码的顺序不能乱，否则会造成多次替换
   str.replace("&","&amp;");
   str.replace(">","&gt;");
   str.replace("<","&lt;");
   str.replace("\"","&quot;");
   str.replace("\'","&#39;");
   str.replace(" ","&nbsp;");
   str.replace("\n","<br>");
   str.replace("\r","<br>");
}

void stringToHtml(QString &str,QColor crl)
{
     QByteArray array;
     array.append(crl.red());
     array.append(crl.green());
     array.append(crl.blue());
     QString strC(array.toHex());
     str = (QString("<span style=\" color:#%1;\">%2</span>").arg(strC).arg(str));
}

QColor PlayerIdToColor(const int id)
{
    switch(id)
    {
    case 0:return (QColor(220,20,60));break;
    case 1:return (QColor(30,144,255));break;
    case 2:return (QColor(0,255,255));break;
    case 3:return (QColor(255,0,255));break;
    case 4:return (QColor(233,233,0));break;
    case 5:return (QColor(255,140,0));break;
    }
    return Qt::black;
}
