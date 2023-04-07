#ifndef ZOBRIST_H
#define ZOBRIST_H
#include "stdint.h"
#include "vector"
#include <iostream>
#include <random>
//#include <cstdlib>
//#include <ctime>
#include <qdebug.h>
#include <QPoint>

#define C_NONE 0//棋子：黑子,白子,无子
#define C_BLACK 1
#define C_WHITE 2

class HashEntry {
public:
    unsigned long long hashKey; // 用于判断是否为同一个局面的哈希值
    int depth; // 当前节点的搜索深度
    int score; // 当前节点的估值
    int flag; // 当前节点的类型
    int couWorth;
    int worth[15][15];
};

class zobrist {
private:
    std::vector<HashEntry> table;
public:
    zobrist(unsigned long long size) ;

    zobrist();

    void store(unsigned long long hashKey, int depth, int score, int flag) ;

    bool probe(unsigned long long hashKey, int depth, int& score, int& flag);

    void initRandomTable();

    unsigned long long calculateHash(int board[][15]);

};



#endif // ZOBRIST_H
