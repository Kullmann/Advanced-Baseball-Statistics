#include "Gui/Menu.hpp"
#include "Gui/Theme.hpp"
#include "Gui/Gui.hpp"
#include <SFML/Graphics.hpp>
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

#include "HashTable.h"

using namespace std;

// Written by Nick Verdugo and Turner Shultz
class BinarySearchTree
{
public:

private:
};

// Snippet of boilerplate code for gui from sfml-widgets library
sf::Color hex2color(const std::string& hexcolor)
{
    sf::Color color = sf::Color::Black;
    if (hexcolor.size() == 7) // #ffffff
    {
        color.r = strtoul(hexcolor.substr(1, 2).c_str(), NULL, 16);
        color.g = strtoul(hexcolor.substr(3, 2).c_str(), NULL, 16);
        color.b = strtoul(hexcolor.substr(5, 2).c_str(), NULL, 16);
    }
    else if (hexcolor.size() == 4) // #fff
    {
        color.r = strtoul(hexcolor.substr(1, 1).c_str(), NULL, 16) * 17;
        color.g = strtoul(hexcolor.substr(2, 1).c_str(), NULL, 16) * 17;
        color.b = strtoul(hexcolor.substr(3, 1).c_str(), NULL, 16) * 17;
    }
    return color;
}

struct Theme
{
    sf::Color backgroundColor;
    std::string texturePath;
};
// End snippet

// Entire main method written by Sean Kullmann with the use of sfml-widgets library, talked about and sourced in report
int main()
{
    // Snippet of boilerplate code for gui from sfml-widgets library
    Theme defaultTheme = {
        hex2color("#dddbde"),
        "src/texture-default.png"
    };
    // End snippet

    //BinarySearchTree b;
    HashTable h;

    h.readData();

    // Create the main window
    
    // Snippet of boilerplate code for gui from sfml-widgets library
    sf::RenderWindow window(sf::VideoMode(640, 480), "Advanced Baseball Statistics", sf::Style::Close);

    gui::Menu menu(window);
    menu.setPosition(10, 10);

    gui::Theme::loadFont("src/tahoma.ttf");
    gui::Theme::loadTexture(defaultTheme.texturePath);
    gui::Theme::textSize = 11;
    gui::Theme::click.textColor      = hex2color("#191B18");
    gui::Theme::click.textColorHover = hex2color("#191B18");
    gui::Theme::click.textColorFocus = hex2color("#000");
    gui::Theme::input.textColor = hex2color("#000");
    gui::Theme::input.textColorHover = hex2color("#000");
    gui::Theme::input.textColorFocus = hex2color("#000");
    gui::Theme::PADDING = 2.f;
    gui::Theme::windowBgColor = defaultTheme.backgroundColor;

    gui::HBoxLayout* hbox = menu.addHBoxLayout();
    // End snippet

    gui::VBoxLayout* vbox = hbox->addVBoxLayout();

    sf::Text banner("", gui::Theme::getFont());
    banner.setPosition(350, 15);
    banner.setFillColor(sf::Color::Black);
    banner.setScale(0.8, 0.8);

    // Table
    float xOffSet = 0;
    float yOffSet = 0;
    int counter = 0;
    sf::RectangleShape table[8];
    for (auto &rect : table)
    {
        if (counter % 2 == 0)
        {
            xOffSet = 0;
            yOffSet += 20;
        }

        rect.setPosition(300 + xOffSet, 30 + yOffSet);
        rect.setSize(sf::Vector2f(150, 20));
        rect.setFillColor(gui::Theme::windowBgColor);  
        rect.setOutlineColor(sf::Color::Black);
        rect.setOutlineThickness(3);
        xOffSet += 150;
        counter++;
    }

    // Table Text
    string tableText[8] = {"Player Name", "", "Isolated Power", "", "Pitches per Start", "", "Range Factor", ""};
    sf::Text sfTableText[8];
    xOffSet = 0;
    yOffSet = 0;
    counter = 0;
    for (auto &text : sfTableText)
    {
        if (counter % 2 == 0)
        {
            xOffSet = 0;
            yOffSet += 20;
        }
        text.setString(tableText[counter]);
        text.setFont(gui::Theme::getFont());
        text.setFillColor(sf::Color::Black);
        text.setScale(0.5, 0.5);
        text.setPosition(300 + xOffSet, 30 + yOffSet);
        xOffSet += 150;
        counter++;
    }

    // Main Banner Label
    gui::Label* ABS = new gui::Label();
    ABS->setText("Advanced Baseball Statistics");
    ABS->setTextSize(20);
    vbox->add(ABS);

    // Search Method
    vbox->addLabel("Search Method");

    int searchMethodChoice = 1;

    gui::OptionsBox<int>* searchMethod = new gui::OptionsBox<int>();
    searchMethod->addItem("Hash Map", 0);
    searchMethod->addItem("Binary Search Tree", 1);
    searchMethod->setCallback([&]() {
        searchMethodChoice = searchMethod->getSelectedValue();
    });
    vbox->add(searchMethod);

    // Search Player Name
    vbox->addLabel("Player Name");

    // Data Structure Time to Search
    sf::Text timeToSearch;
    timeToSearch.setFont(gui::Theme::getFont());
    timeToSearch.setFillColor(sf::Color::Black);
    timeToSearch.setScale(0.5, 0.5);
    timeToSearch.setPosition(310, 135);
    string timeToSearchMethod = "";

    gui::TextBox* textbox = new gui::TextBox();
    textbox->setText("search");
    textbox->setCallback([&]() {
        if (searchMethodChoice == 0)
        {
            if (h.searchPlayer(textbox->getText()))
            {
                vector<float> test = h.searchTable(textbox->getText());
                sfTableText[1].setString(textbox->getText());
                sfTableText[3].setString(to_string(test[0]));
                sfTableText[5].setString(to_string(test[1]));
                sfTableText[7].setString(to_string(test[2]));
                timeToSearchMethod = "Hash Map Search Time: " + to_string(h.getTimeElapsed().count()) + " seconds.";
                timeToSearch.setString(timeToSearchMethod);
                banner.setString("Player found");
            }
            else
                banner.setString("Player not found");

        }
        else if (searchMethodChoice == 1)
        {
            // b.setName(textbox->getText());
            // sfTableText[5].setString(b.getName());  
        }
    });
    vbox->add(textbox);

    // Spacer
    vbox->addLabel("");

    // User Input Labels
    string userInputText[10] = {"Enter Player Name", "Enter Games Played", "Enter Games Started Pitching", "Enter Number of Pitches", "Enter Putouts", "Enter Assists", "Enter At Bats", "Enter 2nd Bases", "Enter 3rd Bases", "Enter Homeruns"};
    sf::Text sfUserInputText[10];
    xOffSet = 220;
    yOffSet = 0;
    counter = 0;
    for (auto &text : sfUserInputText)
    {

        text.setString(userInputText[counter]);
        text.setFont(gui::Theme::getFont());
        text.setFillColor(sf::Color::Black);
        text.setScale(0.4, 0.4);
        text.setPosition(xOffSet, 167 + yOffSet);
        yOffSet += 28;
        counter++;
    }

    // Enter Player Data
    vbox->addLabel("User Input");

    gui::TextBox* textbox2 = new gui::TextBox();
    vbox->add(textbox2);

    gui::TextBox* textbox3 = new gui::TextBox();
    vbox->add(textbox3);

    gui::TextBox* textbox4 = new gui::TextBox();
    vbox->add(textbox4);

    gui::TextBox* textbox5 = new gui::TextBox();
    vbox->add(textbox5);

    gui::TextBox* textbox6 = new gui::TextBox();
    vbox->add(textbox6);

    gui::TextBox* textbox7 = new gui::TextBox();
    vbox->add(textbox7);

    gui::TextBox* textbox8 = new gui::TextBox();
    vbox->add(textbox8);

    gui::TextBox* textbox9 = new gui::TextBox();
    vbox->add(textbox9);

    gui::TextBox* textbox10 = new gui::TextBox();
    vbox->add(textbox10);

    gui::TextBox* textbox11 = new gui::TextBox();
    vbox->add(textbox11);

    vector<string> userData;
    for (int i = 0; i < 8; i++)
        userData.push_back("");

    sf::Text playerEntered;
    playerEntered.setFont(gui::Theme::getFont());
    playerEntered.setFillColor(sf::Color::Black);
    playerEntered.setScale(0.4, 0.4);
    playerEntered.setPosition(110, 447);
    
    vbox->addButton("Enter User Data", [&]()
    {
        if (searchMethodChoice == 0)
        {
            string player = "Player " + textbox2->getText() + " entered into database.";

            userData[0] = textbox3->getText();
            userData[1] = textbox4->getText();
            userData[2] = textbox5->getText();
            userData[3] = textbox6->getText();
            userData[4] = textbox7->getText();
            userData[5] = textbox8->getText();
            userData[6] = textbox9->getText();
            userData[7] = textbox10->getText();
            h.insertPlayer(textbox2->getText(), userData);
            playerEntered.setString(player);
        }
        else if (searchMethodChoice == 1)
        {

        }
    });

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            menu.onEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(gui::Theme::windowBgColor);
        window.draw(menu);
        window.draw(banner);
        for (const auto& rect : table)
        {
            window.draw(rect);
        }
        for (const auto& text : sfTableText)
        {
            window.draw(text);
        }
        for (const auto& text : sfUserInputText)
        {
            window.draw(text);
        }
        window.draw(playerEntered);
        window.draw(timeToSearch);

        window.display();
    }

    return EXIT_SUCCESS;
}