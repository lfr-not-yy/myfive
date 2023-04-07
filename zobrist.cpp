#include "zobrist.h"


zobrist::zobrist(unsigned long long size) {
        size = std::max(size, (unsigned long long)1);
        table.resize(size);
    }
zobrist::zobrist(){

}

void zobrist::store(uint64_t hashKey, int depth, int score, int flag) {
    HashEntry& entry = table[hashKey % table.size()];
    if (entry.hashKey == 0 || entry.hashKey == hashKey) {
        // 当前节点不在置换表中或者当前节点与置换表中的节点相同，直接替换
        entry.hashKey = hashKey;
        entry.depth = depth;
        entry.score = score;
        entry.flag = flag;
    }
}

bool zobrist::probe(uint64_t hashKey, int depth,  int &score,  int &flag){
    HashEntry& entry = table[hashKey % table.size()];
    if (entry.hashKey == hashKey && entry.depth >= depth)
    {
        // 当前节点在置换表中且深度不低于当前节点深度，返回置换表中的值
        score = entry.score;
        flag = entry.flag;
        return true;
    }
    return false;
}
unsigned long long randomTable[2][15][15];

// 初始化随机数表
void zobrist::initRandomTable() {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<unsigned long long> dis;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 15; j++) {
            for (int k = 0; k < 15; k++) {
                randomTable[i][j][k] = dis(gen);
            }
        }
    }
}

// 计算局面的哈希值
unsigned long long zobrist::calculateHash(int board[][15]) {
    unsigned int hash = 0;
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (board[i][j] == C_BLACK) {
                hash ^= randomTable[0][i][j];
            } else if (board[i][j] == C_WHITE) {
                hash ^= randomTable[1][i][j];
            }
        }
    }
    return hash;
}

