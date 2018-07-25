#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include "global.h"

enum MyWidgetType{
  Trading=0,Purchasing,DDL,IntroductionWidget
};

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    MyWidgetType type;
    explicit MyWidget(QWidget *parent = 0);
    MyWidget(MyWidgetType atype,int a1=0,int a2=0);

    void closeEvent(QCloseEvent*);
    ~MyWidget();

    int arg1,arg2;

    QVector<QCheckBox*> *checkboxes_l,*checkboxes_r;

    QSlider* slider_l,*slider_r;

    QSpinBox* spinbox_l,*spinbox_r;

private slots:
    void Accept_clicked();
    void Cancle_clicked();

private:

    Ui::MyWidget *ui;
    QPushButton *pushbutton_accept,*pushbutton_cancle;

    QScrollArea*scrollarea_l,*scrollarea_r;

    QPixmap *mainpixmap;

    QWidget *scrollwidget_l,*scrollwidget_r;

protected:
    void paintEvent(QPaintEvent*);

};

#endif // MYWIDGET_H
