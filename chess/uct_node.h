//
// Created by MaoLongLong on 2019/6/28.
//

#ifndef CHESS_UCT_NODE_H
#define CHESS_UCT_NODE_H
#define N 3

#include <vector>

class UCT_Node {
public:
    UCT_Node(int **state, UCT_Node *parent);
    int **copyState();
private:
    int **boardState;
    int win;
    int lose;
    int **children;
    UCT_Node *parent;
    int **untried_actions;
};

#endif //CHESS_UCT_NODE_H
