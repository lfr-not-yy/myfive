#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QMap>
//#include <QRandomGenerator>
#include <QTimer>
#include <QTime>
#include <sys/time.h>
#include <QDebug>
#include <iostream>
#include "chessai.h"
#include "zobrist.h"
using namespace std;


namespace Ui {
class gameWidget;
}

class gameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit gameWidget(QWidget *parent = nullptr);
    ~gameWidget()override;
    void initializeGame();
    void setGameMode(gameMode m){mode=m;}
    bool chessOneByPlayer();
    void oneChessMove(int row,int col);//给出要走子的地址，走一步
    bool isDeadGame();//判断是否是僵局
    bool isLegalMove(int row,int col);//判断下子位置是否合法
    bool deadWindow(QMessageBox *msg);
    QMessageBox msg;
    void exRegret();
    bool reIsLegalMove(int row,int col);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;//实际落子

signals:
    void returnSignal();

public slots:
    void returnPush();
    void chessOneByAi();
    //重新开始
    void initializeGame1();
    //悔棋
    void regret();

private:
    Ui::gameWidget *ui;
    QPoint chessboard[15][15];//第一个下标是列，第二个是行
    chessAi ai;//棋盘放在ai当中
    int cursorRow;//光标位置
    int cursorCol;
    //记录刚下的子的位置，方便做出特殊标记
    int lastRow;
    int lastCol;
    //记录已经下过的子的位置，便于悔棋
    int usedChesses[15][15];

    gameMode mode =NONE;
    gameTurn turn;
    gameStatus status;

    int score_black;
    int score_write;
    int numOfChess;


};

#endif // GAMEWIDGET_H
