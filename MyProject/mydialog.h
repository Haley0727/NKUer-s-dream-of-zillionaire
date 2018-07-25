#ifndef MYDIALOG_H
#define MYDIALOG_H

#include"global.h"
#include"gamemainwidget.h"

class GameMainWidget;

namespace Ui {
class MyDialog;
}

enum MyDialogType
{
    GameMenu=0,PlayerCustomize,Bidding,IntroductionDialog
};

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    MyDialogType type;
    explicit MyDialog(QWidget *parent = 0);
    MyDialog(MyDialogType atpye,const int aarg1=0,const int aarg2=0,QWidget *parent = 0);
    ~MyDialog();

    QPushButton *pushbutton_back,*pushbutton_next,
                           *pushbutton_previous,*pushbutton_confirm,
                            **pushbutton_playeriamgelist
    ;
    QSpinBox* playercustomizespinbox,*biddingspinbox;//原先没考虑这么多，以为就玩家自定义需要spinbox

    QSlider *biddingslider;


    QLineEdit *playercustomizenameedit;

    QPixmap *mainpixmap;

    QScrollArea *scrollarea;

    int arg1,arg2;

protected:
    void paintEvent(QPaintEvent*);
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent *);
private:
    Ui::MyDialog *ui;
    int playercustomizeindex;
    bool confirm;

    QLabel *label;

    int* biddingplayerordertoid,biddingorder,biddingprice,
    biddingtimercounter,biddingtimelimit,biddingplayernum,
    owningplayerid;

    bool isplayerbidding[6],isbiddingplayeroperated;

    QTimer *timer;

private slots:
    void PushButton_Back_Clicked();
    void PushButton_PlayerCustomize_Clicked();
    void PushButton_Bidding_Clicked();
    void BiddingTurns();
    void PushButton_Confirm_clicked();
    void VolumeSliderValueChange(int value);
};




#endif // MYDIALOG_H
