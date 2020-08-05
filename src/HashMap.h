#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iomanip>
#include <map>
#include <random>
#include <ctime>
#include <sstream>
#include <ratio>
#include <thread>
#include <chrono>

#pragma once

using namespace std;

// Written by Sean Kullmann
class HashMap
{
public:
	void insertPlayer(string playerName, vector<string> playerNumbers);

	void printTable();

    bool searchPlayer(string playerName);

	vector<float> searchTable(string playerName);

	void readData();

    std::chrono::duration<float> getTimeElapsed();

    void setTimeElapsed(std::chrono::duration<float> timeElapsed);


private:
	unordered_map<string, vector<string>> hTable;
    std::chrono::duration<float> mTimeElapsed;
    
};
