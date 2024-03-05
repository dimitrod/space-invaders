#pragma once

class Highscore {
    public:
        static int LoadHighscoreFromFile();
        static void CheckHighscore(int score, int highscore);
    private:
        static void SaveHighscoreToFile(int highscore);

};