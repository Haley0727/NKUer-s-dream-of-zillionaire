#ifndef GAMEMAINWIDGET_H
#define GAMEMAINWIDGET_H

#include"global.h"
#include"Classes.h"
#include"mywidget.h"
#include"chatwidget.h"

class Player;
class Block;
class MyWidget;class MyDialog;
class AvailableBlock;
class BuildableBlock;
class ChatWidget;



namespace Ui {
class GameMainWidget;
}
class GameMainWidget : public QWidget
{
    Q_OBJECT

    friend class ChatWidget;
public:
    explicit GameMainWidget(QWidget *parent = 0);
    ~GameMainWidget();

    void BlockCheck();

    void MyWidgetReturn(MyWidget *returnevent);

    void PlayercashChange(const int playerid,const int howmuch);//有正负

    void PlayerRoleMoveByDice(Player&player, const int steps);

    void SetContinue();//设置继续
    void SetOperable(bool b);
    void SetPause();//设置暂停

    void StageFinish();

    void ShowPlayerStageButton();
    void ShowStageFinishPushButton();

    void ShowDicePushButton();

    const int width,height/*窗口长宽*/,
    //viewwidth/*绘图区域宽度*/,
    playerroleimagewidth/*玩家角色图标宽度（正方形）*/,
    playerlistimagewdith/*玩家列表图标宽度(正方形)*/,
    playernum/*玩家数量*/,blocksmargin/*区块边距*/
    ;

    Player* players[6];

    Block* blocks[40];

    QTextEdit chattextedit;

    bool ispause;

    int playeractivenum,playerordertoid[6]/*由玩家操作顺序到玩家id的映射*/,
    stageplayerorder/*当前阶段的玩家顺序，0~5*/;

    QFont *fontdefault;//字体

    Player* playerfornow;

    QVector<ChatWidget*> activechatwidgets;//动态更新聊天窗口

private:
    Ui::GameMainWidget *ui;

    enum Stage
    {
        START=0,
        PAUSE,
        WATING,
        FORPLAYER,
        OVER
    }stage,nextstage;

    int dice_f,dice_s/*两个骰子的数*/,dicechange_f,dicechange_s,
          stagecounter/*当前游戏阶段剩余秒数*/,nextstagecounter,
          cardreversaltimercount/*卡牌计时器倒数*/,
          cardreversx/*卡牌当前移动的横坐标*/,
          cardtypeorder[7]/*卡牌种类随机打乱后的数组*/,
          cardsremain/*当前卡牌库剩余*/,
          randomeventstypeorder[5]/*随机事件种类随机打乱后的数组*/,
          randomeventsremain/*随机事件卡牌库剩余*/
    ;

    MyWidget *mywidget;
    MyDialog *mydialog;



    QPixmap *GameBackground,*GameBackgrounddarker,
                    *GameBackgroundalternate, //游戏背景
                    *Dices/*骰子*/,
                    *Levels;

    QPushButton *pushbutton_menu,*pushbutton_quit,
                            *pushbutton_dice,*pushbutton_trade,
                            *pushbutton_stagefinish,
                            *pushbutton_build,*pushbutton_build_cancle,
                            *pushbutton_sell,*pushbutton_sell_cancle,
                            **pushbutton_tradeplayerlist,
                            *pushbutton_failed_confirm,
                            *pushbutton_stagefinish_failed_alternate,
                            *pushbutton_travel,*pushbutton_travel_cancle,
                            *pushbutton_chat_widget_show
    ;

    QString stagestring;

    QTimer *counttimer/*每秒钟计时器*/,
                *dicerefreshtimer/*骰子变换特效计时器*/,
                *labelmovestagetimer/*玩家label移动阶段计时器*/,
                *playertravelstagetimer/*玩家通过旅行进行移动计时器*/,
                *cardreversaltimer/*卡牌旋转动画计时器*/,
                *hinttimer/*提示动画计时器*/
    ;

    QImage *cardback,*cardfront,*cardbacktemp,*cardfronttemp;

    QVector<QPushButton*> operablepushbuttonv/*在游戏动画过程中不可操作的按钮*/;

    QVector<QPoint> playerrolewaypoint;

    QVector<BuildableBlock*> operablebuildablocksv;//可以进行操作的可建造区块

    QLabel *hintrolelabel,*hintlabel,*stagelabel;

    bool operable/*游戏是否能被玩家操作*/,
            iscount/*每秒计时器是否进行动作*/,
            isdicebuttonclicked/*该轮玩家是否点击了骰子按钮*/,
            showdices/*是否展示骰子*/,
            istradeplayerlistshown/*是否显示交易玩家列表*/,
            isbuilding/*是否是建筑模式*/,
            isselling/*是否出售模式*/,//别问我为什么这个变量名不是isupdating，我不知道！
            istest/*是否测试模式*/,
            istraveling/*是否在选择旅行目的地*/,
            isdice/*是否通过控制台输入骰子数量*/,testcmd/*是否输入命令判断*/
    ;

    void Labelmove(QLabel&label,const int desx,const int desy,const int msec,const int style);

    void AvailableBlockowning(AvailableBlock* block,const int ownerid);

    void PlayerRoleTravel(Player&player, const int desid, bool ischeckblock);

    void CardReversal();

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*event);
    void closeEvent(QCloseEvent *event);
private slots:

    void Pushbutton_Travel_clicked();
    void Pushbutton_Travel_Cancle_clicked();
    void PushButton_Build_clicked();
    void PushButton_Build_Cancle_clicked();
    void PushButton_Sell_clicked();
    void PushButton_Sell_Cancle_clicked();
    void PushButton_Quit_clicked();
    void PushButton_Menu_clicked();
    void PushButton_Dice_clicked();
    void PushButton_Trade_clicked();
    void PushButton_StageFinish_clicked();
    void PushButton_TradePlayerList_clicked();
    void PushButton_Chat_Widget_Show_clicked();

    void CardReversalTimer_TimeOut();

    void PlayerTravelStageTimer_TimeOut();

    void DiceRefresh_TimeOut();
    void LabelMoveStageTimer_TimeOut();

    void ActionPerSecond();

    void DeleteLater();

    void PlayercashChangeInTime();

    void ChatTextEdit_Changed();

    void HintTimer_TimeOut();
};

#endif // GAMEMAINWIDGET_H
