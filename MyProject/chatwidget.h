#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include "global.h"
#include "Classes.h"

class Player;

namespace Ui {
class ChatWidget;
}

class ChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWidget(QWidget *parent = 0);
    ~ChatWidget();

    bool isdelete;

    QTextBrowser textbroser;



private:
    Ui::ChatWidget *ui;
    const int width,height;

    Player*player;

    QTextEdit textedit;

    QLabel playerimage,playername;

    QPushButton pushbutton_send,pushbutton_back;

private slots:
    void Pushbutton_Back_clicked();
    void Pushbutton_Send_clicked();
protected:
    void closeEvent(QCloseEvent*);
    void keyPressEvent(QKeyEvent*);
};

#endif // CHATWIDGET_H
