#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>

#include "bst.h"

using namespace std;

// Written by Nicholas Verdugo
//function to insert a player's name and stats into the bst
void bst::insert(bst::bstNode player, bst tree) {
    bst::bstNode* temp = &tree.root;
    if (player.name == root.name) {
        return;
    }
    while (1) {
        //move left if the player's name comes before the current player's name
        if (player.name < temp->name) {
            if (temp->left != nullptr) {
                temp = temp->left;
            }
            else {
                temp->left = &player;
                return;
            }
        }
            //move right if the player's name comes after the current player's name
        else if (player.name > temp->name) {
            if (temp->right != nullptr) {
                temp = temp->right;
            }
            else {
                temp->right = &player;
                return;
            }
        }
    }

}

// Written by Turner Shultz
vector <double> bst::calc(const int stats[]) {

    double ISO;
    double RF;
    double PS;
    vector<double> advStats;

    for (int i = 0; i < 3; i++) {

        advStats.push_back(0);

    }

    ISO = double(stats[6] + 2 * stats[7] + 3 * stats[8]) / stats[5];
    advStats[0] = ISO;
    RF = double(stats[3] + stats[4]) / stats[0];
    advStats[1] = RF;
    PS = double(stats[2]) / stats[1];
    advStats[2] = PS;

    return advStats;
}

vector <double> bst::search(const string& name, bst tree2) {

    auto beforeSearch = chrono::high_resolution_clock::now();
    vector <double> empty;

    ifstream playerStats("src/stats.csv");
    string line, stats;
    int data2 = 0;
    //skip the first line
    getline(playerStats, line);
    //create the root node
    bst::bstNode temp;
    getline(playerStats, temp.name, ',');
    getline(playerStats, stats, ',');
    istringstream(stats) >> data2;
    temp.stats[0] = data2;
    getline(playerStats, stats, ',');
    istringstream(stats) >> data2;
    temp.stats[1] = data2;
    getline(playerStats, stats, ',');
    istringstream(stats) >> data2;
    temp.stats[2] = data2;
    getline(playerStats, stats, ',');
    istringstream(stats) >> data2;
    temp.stats[3] = data2;
    getline(playerStats, stats, ',');
    istringstream(stats) >> data2;
    temp.stats[4] = data2;
    getline(playerStats, stats, ',');
    istringstream(stats) >> data2;
    temp.stats[5] = data2;
    getline(playerStats, stats, ',');
    istringstream(stats) >> data2;
    temp.stats[6] = data2;
    getline(playerStats, stats, ',');
    istringstream(stats) >> data2;
    temp.stats[7] = data2;
    getline(playerStats, stats);
    istringstream(stats) >> data2;
    temp.stats[8] = data2;
    tree2.insert(temp, tree2);
    tree2.size++;
    tree2.root = temp;
    if (temp.name == name) {

        return calc(temp.stats);

    }
    //store all other values
    while (!playerStats.eof()) {
        bst::bstNode temp;
        getline(playerStats, temp.name, ',');
        getline(playerStats, stats, ',');
        istringstream(stats) >> data2;
        temp.stats[0] = data2;
        getline(playerStats, stats, ',');
        istringstream(stats) >> data2;
        temp.stats[1] = data2;
        getline(playerStats, stats, ',');
        istringstream(stats) >> data2;
        temp.stats[2] = data2;
        getline(playerStats, stats, ',');
        istringstream(stats) >> data2;
        temp.stats[3] = data2;
        getline(playerStats, stats, ',');
        istringstream(stats) >> data2;
        temp.stats[4] = data2;
        getline(playerStats, stats, ',');
        istringstream(stats) >> data2;
        temp.stats[5] = data2;
        getline(playerStats, stats, ',');
        istringstream(stats) >> data2;
        temp.stats[6] = data2;
        getline(playerStats, stats, ',');
        istringstream(stats) >> data2;
        temp.stats[7] = data2;
        getline(playerStats, stats);
        istringstream(stats) >> data2;
        temp.stats[8] = data2;
        tree2.insert(temp, tree2);
        tree2.size++;
        if (temp.name == name) {

            auto afterSearch = chrono::high_resolution_clock::now();
            std::chrono::duration<float> timeElapsed = afterSearch - beforeSearch;
            setTimeElapsed(timeElapsed);
            return calc(temp.stats);

        }

    }
    
    return empty;

}

// Written by Nicholas Verdugo
void bst::readFile(string filename, bst tree) {
    ifstream playerStats(filename);
    string line, stats;
    int data2 = 0;
    //skip the first line
    getline(playerStats, line);
    //create the root node
    bst::bstNode temp;
    getline(playerStats, temp.name, ',');
    getline(playerStats, stats, ',');
    istringstream(stats) >> data2;
    temp.stats[0] = data2;
    getline(playerStats, stats, ',');
    istringstream(stats) >> data2;
    temp.stats[1] = data2;
    getline(playerStats, stats, ',');
    istringstream(stats) >> data2;
    temp.stats[2] = data2;
    getline(playerStats, stats, ',');
    istringstream(stats) >> data2;
    temp.stats[3] = data2;
    getline(playerStats, stats, ',');
    istringstream(stats) >> data2;
    temp.stats[4] = data2;
    getline(playerStats, stats, ',');
    istringstream(stats) >> data2;
    temp.stats[5] = data2;
    getline(playerStats, stats, ',');
    istringstream(stats) >> data2;
    temp.stats[6] = data2;
    getline(playerStats, stats, ',');
    istringstream(stats) >> data2;
    temp.stats[7] = data2;
    getline(playerStats, stats);
    istringstream(stats) >> data2;
    temp.stats[8] = data2;
    tree.insert(temp, tree);
    tree.size++;
    tree.root = temp;
    //store all other values
    while (!playerStats.eof()) {
        bst::bstNode temp;
        getline(playerStats, temp.name, ',');
        getline(playerStats, stats, ',');
        istringstream(stats) >> data2;
        temp.stats[0] = data2;
        getline(playerStats, stats, ',');
        istringstream(stats) >> data2;
        temp.stats[1] = data2;
        getline(playerStats, stats, ',');
        istringstream(stats) >> data2;
        temp.stats[2] = data2;
        getline(playerStats, stats, ',');
        istringstream(stats) >> data2;
        temp.stats[3] = data2;
        getline(playerStats, stats, ',');
        istringstream(stats) >> data2;
        temp.stats[4] = data2;
        getline(playerStats, stats, ',');
        istringstream(stats) >> data2;
        temp.stats[5] = data2;
        getline(playerStats, stats, ',');
        istringstream(stats) >> data2;
        temp.stats[6] = data2;
        getline(playerStats, stats, ',');
        istringstream(stats) >> data2;
        temp.stats[7] = data2;
        getline(playerStats, stats);
        istringstream(stats) >> data2;
        temp.stats[8] = data2;
        tree.insert(temp, tree);
        tree.size++;
    }
}

// Written by Sean Kullmann
std::chrono::duration<float> bst::getTimeElapsed()
{
    return mTimeElapsed;
}

// Written by Sean Kullmann
void bst::setTimeElapsed(std::chrono::duration<float> timeElapsed)
{
    mTimeElapsed = timeElapsed;
}