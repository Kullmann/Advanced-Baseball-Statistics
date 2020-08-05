// Written by Sean Kullmann

#include "HashMap.h"

void HashMap::insertPlayer(string playerName, vector<string> playerNumbers)
{
    hTable.insert(make_pair(playerName, playerNumbers));
    ofstream outfile;

    outfile.open("src/stats.csv", std::ios_base::app);
    outfile << "\n" << playerName << "," << playerNumbers[0] << "," << playerNumbers[1] << "," << playerNumbers[2] << "," << playerNumbers[3] << "," << playerNumbers[4] << "," << playerNumbers[5] << "," << playerNumbers[6] << "," << playerNumbers[7] << "," << playerNumbers[8];
}

void HashMap::printTable()
{
    unordered_map<string, vector<string>>:: iterator itr;
    for (itr = hTable.begin(); itr != hTable.end(); itr++)
    {
        cout << itr->first;
        for (auto &j : itr->second)
        {
            cout << " " <<  j;
        }
        cout << "\n";
    }
}

bool HashMap::searchPlayer(string playerName)
{
    unordered_map<string, vector<string>>:: iterator itr;
    for (itr = hTable.begin(); itr != hTable.end(); itr++)
    {
        if (itr->first == playerName)
            return true;
    }
    return false;
}

vector<float> HashMap::searchTable(string playerName)
{
    float isolatedPower = 0;
    float pitchesPerStart = 0;
    float rangeFactor = 0;

    unordered_map<string, vector<string>>:: iterator itr;
    vector<float> playerValues;
    vector<float> calculateStats;
    auto beforeSearch = chrono::high_resolution_clock::now();
    for (itr = hTable.begin(); itr != hTable.end(); itr++)
    {
        if (itr->first == playerName)
        {
            for (auto &j : itr->second)
            {
                calculateStats.push_back(stof(j));
            }
            isolatedPower = (1 * calculateStats[6] + 2 * calculateStats[7] + 3 * calculateStats[8]) / calculateStats[5];
            playerValues.push_back(isolatedPower);

            pitchesPerStart = (calculateStats[2] / calculateStats[1]);
            playerValues.push_back(pitchesPerStart);

            rangeFactor = (calculateStats[3] + calculateStats[4]) / calculateStats[0];
            playerValues.push_back(rangeFactor);
        }
    }
    auto afterSearch = chrono::high_resolution_clock::now();
    std::chrono::duration<float> timeElapsed = afterSearch - beforeSearch;
    setTimeElapsed(timeElapsed);

    return playerValues;
}

void HashMap::readData()
{
    ifstream myFile("src/stats.csv", ios::in);

    string line;
    getline(myFile, line);

    vector<string> tempVec;
    for (int i = 0; i < 9; i++)
        tempVec.push_back("");

    while(!myFile.eof())
    {
        getline(myFile, line);
        istringstream stream(line);
        string first, second, third, fourth, fifth, sixth, seventh, eigth, ninth, tenth;

        getline(stream, first, ',');
        getline(stream, second, ',');
        getline(stream, third, ',');
        getline(stream, fourth, ',');
        getline(stream, fifth, ',');
        getline(stream, sixth, ',');
        getline(stream, seventh, ',');
        getline(stream, eigth, ',');
        getline(stream, ninth, ',');
        getline(stream, tenth, ',');

        tempVec[0] = (second);
        tempVec[1] = (third);
        tempVec[2] = (fourth);
        tempVec[3] = (fifth);
        tempVec[4] = (sixth);
        tempVec[5] = (seventh);
        tempVec[6] = (eigth);
        tempVec[7] = (ninth);
        tempVec[8] = (tenth);

        hTable.insert(make_pair(first, tempVec));
    }
    myFile.close();
}

std::chrono::duration<float> HashMap::getTimeElapsed()
{
    return mTimeElapsed;
}

void HashMap::setTimeElapsed(std::chrono::duration<float> timeElapsed)
{
    mTimeElapsed = timeElapsed;
}