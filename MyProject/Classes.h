#ifndef CLASSES_H
#define CLASSES_H
#include "global.h"

class GLOBAL;

class Player
{
    public:
    const QString name;
    const int id,iconid;//id=1~6,0为无效ID
    int cash,locationid,resttimes,ddls;//locationid表示玩家现在所在block的id
    bool isfailed,iscashprotected;
    QImage *image;
    QLabel* rolelabel;
    QColor color;

    const QRect listrect;

    Player(const QString&aname,const int aid,const int aiconid,const QRect &alistrect);
    ~Player()
    {
        delete image;
        delete rolelabel;
    }
};


//不知道为什么，dynamic_cast有问题。。。所以只好用枚举类型来判断类型
enum BlockType
{
    Available=0,Specific
};
class Block
{
public:
    const BlockType type;
    const QString name;
    const QRect rect;
    const int id;
    const QPoint position;
    QPixmap activepixmap,originpixmap;

    Block(const BlockType atype,
          const QString &aname,
          const QRect&arect,
          const int aid):
        type(atype),name(aname),
     rect(arect)
    ,id(aid),
   position(QPoint(rect.x()+rect.width()/2,rect.y()+rect.height()/2))
    {}
};

enum SpecificBlockType
{
    HelloWorld=0,Deadline,LuckCard,RandomEvent,Hospital,Library
};
class SpecificBlock :public Block
{
public:
    SpecificBlockType type;
    SpecificBlock(
                  const SpecificBlockType astype,
                  const QString &aname,const QRect&arect,const int aid):
        Block(BlockType::Specific,aname,arect,aid),type(astype){}
};

enum AvailableBlockType
{
    BusStop=0,Buildable
};
class AvailableBlock :public Block
{
public:
    AvailableBlockType type;
    const int purchaseprice;
    Player* owner;
    AvailableBlock(const AvailableBlockType aatype,
                   const QString &aname,
                   const QRect&arect,
                   const int aid,const int aprice):
        Block(BlockType::Available,aname,arect,aid),type(aatype),purchaseprice(aprice),owner(NULL)
    {}
};

class BuildableBlock:public AvailableBlock
{
public:
    int level;
    const int buildprice,maxlevel,chargebase,chargeperlevel;

    BuildableBlock *buildneed_f, *buildneed_s;

    bool isoperateallowed;

    BuildableBlock(
                   const QString &aname,
                   const QRect&arect,
                   const int aid,const int aprice,
                   const int abuildprice,
                   const int amaxlevel,const int achargebase,
                   const int achargeperlevel
                   ):
    AvailableBlock(AvailableBlockType::Buildable,aname,arect,aid,aprice),
    level(0),buildprice(abuildprice),maxlevel(amaxlevel),
    chargebase(achargebase),chargeperlevel(achargeperlevel),buildneed_f(NULL),buildneed_s(NULL)
    ,isoperateallowed(false)
    {}
};

#endif // CLASSES_H
