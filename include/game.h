#ifndef GAME_H
#define GAME_H

#include <vector>

int startgame(int players, int difficulty, bool mode);

struct settings{
	int sx_size, sy_size;
	int mx_size, my_size;
	int r_b, g_b, b_b;
	int winsize;
	int scale;
	std::vector<int> stats_s;
	std::vector<int> stats_m;
};

extern settings main_settings;

class Game
{
        int **board;
        int **copyboard;
        int sizeX;
        int sizeY;
        bool turn;
        int last_cpu_x, last_cpu_y;

public:
        Game(int sizeX, int sizeY);
        ~Game();
        int At(int x, int y);
        void DoMove(int x, int y, int player);
        void PrintBoard();
        int CheckWin();
        
        void AI_Easy();
        void AI_Medium();
        void AI_Hard();
};

#endif
