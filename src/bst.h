#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <chrono>

#pragma once    

using namespace std;

// Written by Nicholas Verdugo
class bst {
public:
    //bst node struct
    struct bstNode {
    public:
        string name;
        int stats[9];
        bstNode* left = nullptr, * right = nullptr;
    };
    int size;
    bstNode root;
    void insert(bst::bstNode player, bst tree);
    vector <double> calc(const int* stats);
    vector <double> search(const string& name, bst tree);
    void readFile(string filename, bst tree);
    bool findPlayer(string name);
    std::chrono::duration<float> getTimeElapsed();
    void setTimeElapsed(std::chrono::duration<float> timeElapsed);

private:
    std::chrono::duration<float> mTimeElapsed;

};