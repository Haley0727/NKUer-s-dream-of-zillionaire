#include "Classes.h"
#ifdef DEBUG
static void LYL232BUGS()
{
    LYL232::bugs+=2;
    LYL232::bugsfixed+=2;
}

void LYL232::Classcpp()
{
    LYL232BUGS();
}
#endif

Player::Player(const QString&aname,const int aid/*玩家id*/,
               const int aiconid/*玩家选择的图标的id*/,const QRect &alistrect):
    name(aname),id(aid),iconid(aiconid),listrect(alistrect)
{
    iscashprotected=isfailed=false;

    image=new QImage(GLOBAL::ssmap["PlayerImage"+QString::number(iconid)]);
    rolelabel=new QLabel;
    QImage *scaledimg=new QImage;
    ddls=resttimes=locationid=0;

    cash=GLOBAL::simap["InitialFund"];

    if(!image||!rolelabel||!scaledimg)GLOBAL::Gaming=false;
    else
    {
        const int roleimagesize=GLOBAL::simap["ResolutionWidth"]/24;
        rolelabel->resize(roleimagesize,roleimagesize);
        *scaledimg=image->scaled(roleimagesize,roleimagesize,Qt::KeepAspectRatio);
        rolelabel->setPixmap(QPixmap::fromImage(*scaledimg));

        delete scaledimg;
    }
}
