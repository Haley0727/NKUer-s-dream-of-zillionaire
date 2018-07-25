#include "optiondialog.h"
#include "ui_optiondialog.h"
#include "global.h"

OptionDialog::OptionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionDialog)
{
    ui->setupUi(this);

    this->setWindowTitle("设置");

    ui->operatetime->setRange(30,90);
    ui->operatetime_Slider->setRange(30,90);

    connect(ui->operatetime,SIGNAL(valueChanged(int)),ui->operatetime_Slider,SLOT(setValue(int)));
    connect(ui->operatetime_Slider,SIGNAL(valueChanged(int)),ui->operatetime,SLOT(setValue(int)));

    ui->operatetime->setValue(GLOBAL::simap["OperateTime"]);

    ui->initial_fund_Slider->setRange(1500,6000);
    ui->initial_fund_SpinBox->setRange(1500,6000);

    ui->initial_fund_Slider->setValue(GLOBAL::simap["InitialFund"]);
    ui->initial_fund_SpinBox->setValue(GLOBAL::simap["InitialFund"]);

    //设置两个部件的值相关联
    connect(ui->initial_fund_Slider,SIGNAL(valueChanged(int)),ui->initial_fund_SpinBox,SLOT(setValue(int)));
    connect(ui->initial_fund_SpinBox,SIGNAL(valueChanged(int)),ui->initial_fund_Slider,SLOT(setValue(int)));

    connect(ui->musicvolumeslider,SIGNAL(valueChanged(int)),ui->musicvolumespinBox,SLOT(setValue(int)));
    connect(ui->musicvolumespinBox,SIGNAL(valueChanged(int)),ui->musicvolumeslider,SLOT(setValue(int)));
    ui->musicvolumeslider->setValue(GLOBAL::simap["MusicVolume"]);


    ui->resolution->setCurrentIndex(GLOBAL::simap["ResolutionIndex"]);

    ui->isplaymusic->setChecked(GLOBAL::isplaymusic);

    //希望能搞一个配置文件存上一次的设置效果
}

OptionDialog::~OptionDialog()
{
    delete ui;
}

void OptionDialog::on_confirm_clicked()
{
    switch(ui->resolution->currentIndex())
    {
    case 0:
    {
        GLOBAL::simap["ResolutionWidth"]=1600;
        GLOBAL::simap["ResolutionHeight"]=900;
        break;
    }
    case 1:
    {
        GLOBAL::simap["ResolutionWidth"]=1440;
        GLOBAL::simap["ResolutionHeight"]=810;
        break;
    }
    case 2:
    {
        GLOBAL::simap["ResolutionWidth"]=1280;
        GLOBAL::simap["ResolutionHeight"]=720;
        break;
    }
    }
    GLOBAL::simap["ResolutionIndex"]=ui->resolution->currentIndex();
    GLOBAL::simap["InitialFund"]=ui->initial_fund_SpinBox->value();
    GLOBAL::simap["OperateTime"]=ui->operatetime->value();
    this->close();
}

void OptionDialog::on_cancel_clicked()
{
    this->close();
}

void OptionDialog::closeEvent(QCloseEvent*event)
{
    event->accept();
    delete this;
}


void OptionDialog::on_musicvolumeslider_valueChanged(int value)
{
    GLOBAL::mainwindow->musicsplayer->setVolume(value);
    GLOBAL::simap["MusicVolume"]=value;
}

void OptionDialog::on_isplaymusic_stateChanged(int)
{
    if(ui->isplaymusic->isChecked())
    {
        if(GLOBAL::isplaymusic==false)
        {
            GLOBAL::mainwindow->musicslist->setCurrentIndex(0);
            GLOBAL::mainwindow->musicslist->setPlaybackMode(QMediaPlaylist::Random);
            GLOBAL::mainwindow->musicsplayer->setPlaylist(GLOBAL::mainwindow->musicslist);
            GLOBAL::mainwindow->musicsplayer->play();
            GLOBAL::isplaymusic=true;
        }
    }
    else
    {
        GLOBAL::mainwindow->musicsplayer->stop();
        GLOBAL::isplaymusic=false;
    }

}
