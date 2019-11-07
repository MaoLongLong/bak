//
// Created by MaoLongLong on 2019/6/28.
//

#include "uct_node.h"

UCT_Node::UCT_Node(int **state, UCT_Node *parent) {
    this->boardState = new int*[N];
    for (int i = 0; i < N; ++i) {
        this->boardState[i] = new int[N];
        for (int j = 0; j < N; ++j) {
            this->boardState[i][j] = state[i][j];
            if (state[i][j] == 0)
        }
    }
    this->parent = parent;
}

int **UCT_Node::copyState() {
    int **state = new int*[N];
    for (int i = 0; i < N; ++i) {
        state[i] = new int[N];
        for (int j = 0; j < N; ++j)
            state[i][j] = this->boardState[i][j];
    }
    return state;
}
