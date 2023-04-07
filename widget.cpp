#include "widget.h"
#include "gamewidget.h"
#include "ui_widget.h"

//这是游戏初始页面代码
//利用构造函数初始化一个指针parent，并且生成一个ui
Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{
    //将设计好的控件添加到界面中，setupUi由qt自动生成

    ui->setupUi(this);

    game=new gameWidget();
    game->hide();
    //将初始界面的ai和player控件与后端连接
    connect(this->ui->btn_player,SIGNAL(clicked(bool)),this,SLOT(playerButtonPush()));
    connect(this->ui->btn_ai,SIGNAL(clicked(bool)),this,SLOT(aiButtonPush()));
    //将gameWidget类中的returnSignal与show函数连接，当从游戏界面返回时，回到主页面
    connect(game,&gameWidget::returnSignal,this,&Widget::show);
    this->setWindowTitle("内测改bug3.0版模式选择");

}
//退出函数
Widget::~Widget()
{
    delete ui;
}
//将玩家对战功能与button联系，即隐藏当前页面，显示游戏界面，设置ai功能
void Widget::playerButtonPush(){
    this->hide();
    game->show();
    game->setGameMode(PLAYER);
}
//将Ai对战功能与相应button联系
void Widget::aiButtonPush(){
    this->hide();
    game->show();
    game->setGameMode(AI);
}
