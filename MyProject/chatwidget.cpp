#include "chatwidget.h"
#include "ui_chatwidget.h"

#ifdef DEBUG
static void LYL232BUGS()
{
    LYL232::bugs+=4;
    LYL232::bugsfixed+=4;
}

void LYL232::chatwidgetcpp()
{
    LYL232BUGS();
}
#endif

ChatWidget::ChatWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWidget),width(GLOBAL::simap["ResolutionWidth"]*13/24),
    height(GLOBAL::simap["ResolutionHeight"]*2/3)
{
    ui->setupUi(this);
    QTextEdit *texteditori=&(GLOBAL::gamemainwidget->chattextedit);
    player=GLOBAL::gamemainwidget->players[GLOBAL::gamemainwidget->playerordertoid[GLOBAL::gamemainwidget->stageplayerorder]];

    {
        QFont font(*(GLOBAL::gamemainwidget->fontdefault));

        resize(width,height);
        setFixedSize(width,height);
        isdelete=false;
        {
            QImage scaledimage=player->image->scaled(width/18,width/18,Qt::IgnoreAspectRatio);
            QPixmap pixmap=QPixmap::fromImage(scaledimage);
            playername.setParent(this);
            playername.setFont(font);
            playername.setGeometry(width/12,width/320,width/4,width/16);
            playername.setAlignment(Qt::AlignLeft);
            playername.setText(player->name);

            playerimage.setParent(this);
            playerimage.setPixmap(pixmap);
            playerimage.setGeometry(width/320,width/320,width/18,width/18);
            playerimage.show();
        }

        {
            textbroser.setParent(this);
            textbroser.setGeometry(width/32,height/9,width*15/16,height*23/36);
            textbroser.setFont(font);
            textbroser.setHtml(texteditori->toHtml());
            textbroser.show();
        }
        {
            font.setPointSize(width/80);
            textedit.setParent(this);
            textedit.setGeometry(width/32,height*29/36,width*27/36,height*6/36);
            textedit.setFont(font);
        }
        {
            font.setPointSize(width*5/320);
            pushbutton_back.setParent(this);
            pushbutton_back.setGeometry(width*29/36,height*30/36,width/16,width/16);
            pushbutton_back.setStyleSheet(GLOBAL::ssmap["PushButtonStyleSheet1"]);
            pushbutton_back.setText(tr("关闭"));
            pushbutton_back.setFont(font);
            pushbutton_send.setParent(this);
            pushbutton_send.setGeometry(width*32/36,height*30/36,width/16,width/16);
            pushbutton_send.setStyleSheet(GLOBAL::ssmap["PushButtonStyleSheet1"]);
            pushbutton_send.setText(tr("发送"));
            pushbutton_send.setFont(font);

            textedit.setFocus();
            textbroser.moveCursor(QTextCursor::End);

            connect(&pushbutton_back,SIGNAL(clicked()),this,SLOT(Pushbutton_Back_clicked()));
            connect(&pushbutton_send,SIGNAL(clicked()),this,SLOT(Pushbutton_Send_clicked()));
        }

    }
}

ChatWidget::~ChatWidget()
{
    delete ui;
}

void ChatWidget::Pushbutton_Back_clicked()
{
    this->close();
}

void ChatWidget::Pushbutton_Send_clicked()
{
    QTextEdit *texteditori=&(GLOBAL::gamemainwidget->chattextedit);
    QString str,strsend,teststr;
    if(textedit.toPlainText()!="")
    {
        teststr=str=textedit.toPlainText();

        for(int i=0;i<str.length();i++)
            if(str[i]=='\n')
                strsend+="<br/>&#9;";
            else
                strsend+=str[i];

        QString playername=player->name;
        stringToHtml(playername,PlayerIdToColor(player->id));
        str="<h3>"+playername+":</h3><pre><h4>&#9;"+strsend+"</h4><br/></pre>";
        texteditori->moveCursor(QTextCursor::End);
        texteditori->insertHtml(str);
        textedit.clear();

        if(GLOBAL::gamemainwidget->stage==GameMainWidget::Stage::START)
        {
            if(teststr=="-test")
            {
                QString LYL232name("LYL232");
                stringToHtml(LYL232name,QColor(128,0,128));
                QString strtest("<h4>"+LYL232name+":辣个蓝人：他lei了！<br/></h4>");
                texteditori->moveCursor(QTextCursor::End);
                texteditori->insertHtml(strtest);
                GLOBAL::gamemainwidget->istest=true;
            }
        }
        if((teststr[0]=='-')&&GLOBAL::gamemainwidget->istest)
        {
            QString strtest=teststr.left(4);
            if(strtest=="-own")
            {
                QString strnum=teststr.mid(5);
                bool isnum;
                int x=strnum.toInt(&isnum);
                if(isnum&&x>0&&x<40&&
                        GLOBAL::gamemainwidget->blocks[x]->type==BlockType::Available)
                {
                    GLOBAL::gamemainwidget->AvailableBlockowning(
                                (AvailableBlock*)(GLOBAL::gamemainwidget->blocks[x]),
                                player->id);
                    QString LYL232name("LYL232");
                    stringToHtml(LYL232name,QColor(128,0,128));
                    QString strtest("<h4>"+LYL232name+":OK~<br/></h4>");
                    texteditori->moveCursor(QTextCursor::End);
                    texteditori->insertHtml(strtest);
                }
            }
            strtest.clear();
            strtest=teststr.left(5);
            if(strtest=="-dice")
            {
                QString strnumx=teststr.mid(6,1),strnumy=teststr.mid(8,1);
                bool isnumx,isnumy;
                int x=strnumx.toInt(&isnumx),y=strnumy.toInt(&isnumy);
                if(isnumx&&isnumy&&x>0&&x<7&&y>0&&y<7)
                {
                    GLOBAL::gamemainwidget->dicechange_f=x;
                    GLOBAL::gamemainwidget->dicechange_s=y;
                    GLOBAL::gamemainwidget->isdice=true;
                    QString LYL232name("LYL232");
                    stringToHtml(LYL232name,QColor(128,0,128));
                    QString strtest("<h4>"+LYL232name+":OK~<br/></h4>");
                    texteditori->moveCursor(QTextCursor::End);
                    texteditori->insertHtml(strtest);
                }
            }
            strtest.clear();
            strtest=teststr.left(7);
            if(strtest=="-moveto")
            {
                QString strnum=teststr.mid(8);
                bool isnum;
                int x=strnum.toInt(&isnum);
                if(isnum&&x>0&&x<40)
                {
                    if(GLOBAL::gamemainwidget->pushbutton_dice->isEnabled()==true&&
                        GLOBAL::gamemainwidget->pushbutton_dice->isHidden()==false    )
                    {
                        GLOBAL::gamemainwidget->pushbutton_dice->hide();
                        GLOBAL::gamemainwidget->PlayerRoleTravel(*(GLOBAL::gamemainwidget->players[GLOBAL::gamemainwidget->playerordertoid[GLOBAL::gamemainwidget->stageplayerorder]]),x,true);
                        GLOBAL::gamemainwidget->testcmd=true;
                        QString LYL232name("LYL232");
                        stringToHtml(LYL232name,QColor(128,0,128));
                        QString strtest("<h4>"+LYL232name+":OK~<br/></h4>");
                        texteditori->moveCursor(QTextCursor::End);
                        texteditori->insertHtml(strtest);
                    }
                    else
                    {
                        QString strtest("LYL232:"+tr("you can not move now！")+"\n");
                        texteditori->moveCursor(QTextCursor::End);
                        texteditori->insertHtml(strtest);
                    }

                }
            }
            if(teststr=="-stagefinish")
            {
                GLOBAL::gamemainwidget->stagecounter=1;
                QString LYL232name("LYL232");
                stringToHtml(LYL232name,QColor(128,0,128));
                QString strtest("<h4>"+LYL232name+":OK~<br/></h4>");
                texteditori->moveCursor(QTextCursor::End);
                texteditori->insertHtml(strtest);
            }


        }
    }
}

void ChatWidget::closeEvent(QCloseEvent*)
{
    isdelete=true;
    QVector<ChatWidget*>::iterator iter=GLOBAL::gamemainwidget->activechatwidgets.begin();
    for(;iter!=GLOBAL::gamemainwidget->activechatwidgets.end();)
        if((*iter)->isdelete==true)
        {
            delete (*iter);
            GLOBAL::gamemainwidget->activechatwidgets.erase(iter);
            iter=GLOBAL::gamemainwidget->activechatwidgets.begin();
        }
        else
            iter++;
}

void ChatWidget::keyPressEvent(QKeyEvent*event)
{
    if(event->key()==Qt::Key_Control){this->focusWidget();}
    if (event->key() == Qt::Key_Enter ||event->key() == Qt::Key_Return)
    {
            pushbutton_send.click();
    }
}


