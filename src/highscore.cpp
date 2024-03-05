#include "highscore.hpp"
#include <iostream>
#include <fstream>

void Highscore::SaveHighscoreToFile(int highscore) 
{
    std::ofstream highscoreFile("highscore.txt");
    if(highscoreFile.is_open())
    {
        highscoreFile << highscore;
        highscoreFile.close();
    }
    else
    {
        std::cerr << "Failed to save highscore to file!" << std::endl;
    }

}


int Highscore::LoadHighscoreFromFile()
{
    int loadedHighscore = 0;
    std::ifstream highscoreFile("highscore.txt");

    if(highscoreFile.is_open())
    {
        highscoreFile >> loadedHighscore;
        highscoreFile.close();

    }
    else
    {
        std::cerr << "Failed to load highscore from file!" << std::endl;
    }

    return loadedHighscore;
}

void Highscore::CheckHighscore(int score, int highscore) 
{
    if (score > highscore) 
    {
        highscore = score;
        SaveHighscoreToFile(highscore);
    }

}