#include <nds.h>
#include <stdio.h>

#include <vector>
#include <game.h>
#include <buttons.h>

//for random
#include <stdlib.h>
#include <time.h>

Game::Game(int sizeX, int sizeY):
        sizeX(sizeX),
        sizeY(sizeY)
{
	copyboard = new int*[sizeY];
	board = new int*[sizeY];
	for (int i = 0; i < sizeY; i++)
	{
		board[i] = new int[sizeX];
		copyboard[i] = new int[sizeX];
	}
	for (int i = 0; i < sizeY; i++)
		for (int j = 0; j < sizeX; j++)
		{
			board[j][i] = 0;
			copyboard[j][i] = 0;
		}
	
	last_cpu_x = sizeX/2; last_cpu_y = sizeY/2;
}

Game::~Game()
{
	for (int i = 0; i < sizeY; i++)
		delete[] board[i];
	delete[] board;
}

int Game::At(int x, int y)
{
	return board[x][y];
}

void Game::DoMove(int x, int y, int player)
{
	board[x][y] = player;
}

void Game::AI_Easy()
{
	int x_rand = rand() % sizeX, y_rand = rand() % sizeY;
	
	while(board[x_rand][y_rand] != 0)
	{
		x_rand = rand() % sizeX; y_rand = rand() % sizeY;
	}
	
	DoMove(x_rand, y_rand, 2);
	printf("Cpu      -> %i,%i\n", x_rand,y_rand);
	return;
}

void Game::AI_Medium()
{
	if(CheckWin() == 100)
		return;
	
	for(int i = 0; i < sizeY; i++)
		for(int j = 0; j < sizeX; j++)
		{
			if(board[j][i] == 0)
			{
				board[j][i] = 1;
				
				if(CheckWin() == 1)
				{
					board[j][i] = 2;
					printf("Cpu      -> %i,%i\n", j,i);
					return;
				}
				
				board[j][i] = 0;
			}
		}
	
	int x_rand = rand() % sizeX, y_rand = rand() % sizeY;
	
	while(board[x_rand][y_rand] != 0)
	{
		x_rand = rand() % sizeX; y_rand = rand() % sizeY;
	}
	
	board[x_rand][y_rand] = 2;
	printf("Cpu      -> %i,%i\n", x_rand,y_rand);
	
	return;
}

void Game::AI_Hard()
{
	if(CheckWin() == 100)
		return;
	
	for(int i = 0; i < sizeY; i++)
		for(int j = 0; j < sizeX; j++)
			if(board[j][i] == 0)
			{
				board[j][i] = 2;
				
				if(CheckWin() == 2)
				{
					board[j][i] = 2;
					printf("Cpu      -> %i,%i\n", j,i);
					return;
				}
				board[j][i] = 0;
			}
	
	for(int i = 0; i < sizeY; i++)
		for(int j = 0; j < sizeX; j++)
			if(board[j][i] == 0)
			{
				board[j][i] = 1;
				
				if(CheckWin() == 1)
				{
					board[j][i] = 2;
					printf("Cpu      -> %i,%i\n", j,i);
					return;
				}
				board[j][i] = 0;
			}
	
	bool is_surrounded = true;
	
	for(int a = 0; a < 3; a++)
		for(int b = 0; b < 3; b++)
			if(last_cpu_x-1 + b >= 0 and last_cpu_y-1 + a > 0 and 
			last_cpu_y-1 + a < sizeY and last_cpu_x-1 + b < sizeX and 
			board[last_cpu_x-1 + b][last_cpu_y-1 + a] == 0)
				is_surrounded = false;
	
	if(not is_surrounded)
	{
		int x_rand = rand() % 3 - 1, y_rand = rand() % 3 - 1;
		
		while(board[last_cpu_x + x_rand][last_cpu_y + y_rand] != 0 or 
		
			last_cpu_x + x_rand >= sizeX or last_cpu_x + x_rand < 0 or 
			last_cpu_y + y_rand >= sizeY or last_cpu_y + y_rand < 0)
	
		{
			x_rand = rand() % 3 - 1; y_rand = rand() % 3 - 1;
		}
		
		board[last_cpu_x + x_rand][last_cpu_y + y_rand] = 2;
		printf("Cpu      -> %i,%i\n", last_cpu_x + x_rand,last_cpu_y + y_rand);
		
		last_cpu_x += x_rand;
		last_cpu_y += y_rand;
	}
	else
	{
		int x_rand = rand() % sizeX, y_rand = rand() % sizeY;
		
		while(board[x_rand][y_rand] != 0)
		{
			x_rand = rand() % sizeX; y_rand = rand() % sizeY;
		}
		board[x_rand][y_rand] = 2;
		printf("Cpu      -> %i,%i\n", x_rand,y_rand);
		
		last_cpu_x = x_rand;
		last_cpu_y = y_rand;
	}
	
	return;
}

void Game::PrintBoard()
{
	int scale;
	
	if(150/sizeX < 185/sizeY)
		scale = 150/sizeX;
	else
		scale = 185/sizeY;
	
	main_settings.scale = scale;
	
	for(int p = 0; p < sizeX+1; p++)
		rect(scale*p,0,3,scale*sizeY,31,31,31);
	for(int p = 0; p < sizeY+1; p++)
		rect(0,scale*p,scale*sizeX,3,31,31,31);
	
	rect(scale*sizeX,scale*sizeY,3,3,31,31,31);
	
	BUTTON drawbutton(0,0,0,0);
	
		for (int i = 0; i < sizeY; i++)
			for (int j = 0; j < sizeX; j++)
				if(board[j][i] != 0)
				{
					drawbutton.resetinfo(scale*j+8,scale*i+8,8+board[j][i],scale/5-2);
					drawbutton.draw_button();
				}
}

int Game::CheckWin()
{
	bool haswon = false;
	bool fullboard = true;
	
	for(int y = 0; y < sizeY; y++)
		for(int x = 0; x < sizeX; x++)
			if(board[x][y] == 0)
				fullboard = false;
	
	for(int y = 0; y < sizeY; y++)
		for(int x = 0; x < sizeX; x++)
		{
			if(y - main_settings.winsize + 1 >= 0 and board[x][y] != 0) //up
			{
				haswon = true;
				for(int z = 0; z < main_settings.winsize; z++)
				{
					if(board[x][y-z] != board[x][y])
						haswon = false;
				}
				
				if(haswon)
					return board[x][y];
				haswon = false;
			}
			
			if(x - main_settings.winsize + 1 >= 0 and board[x][y] != 0) //left
			{
				haswon = true;
				for(int z = 0; z < main_settings.winsize; z++)
				{
					if(board[x-z][y] != board[x][y])
						haswon = false;
				}
				
				if(haswon)
					return board[x][y];
				haswon = false;
			}
			
			if(y - main_settings.winsize + 1 >= 0 and x - main_settings.winsize + 1 >= 0 and board[x][y] != 0) //up-left
			{
				haswon = true;
				for(int z = 0; z < main_settings.winsize; z++)
				{
					if(board[x-z][y-z] != board[x][y])
						haswon = false;
				}
				
				if(haswon)
					return board[x][y];
				haswon = false;
			}
			
			if(y - main_settings.winsize + 1 >= 0 and x + main_settings.winsize <= sizeX and board[x][y] != 0) //up-right
			{
				haswon = true;
				for(int z = 0; z < main_settings.winsize; z++)
				{
					if(board[x+z][y-z] != board[x][y])
						haswon = false;
				}
				
				if(haswon)
					return board[x][y];
				haswon = false;
			}
			
		}
	
	if(fullboard)
		return 100;
	return -1;
}

int startgame(int players, int difficulty, bool mode)
{
	consoleDemoInit();
	if(mode == 0)
		printf("	  Tictactoe Multiplayer \n			  %i players\n\n", players);
	else
		printf("	  Tictactoe Single Player \n			  Difficulty: %i\n\n", difficulty);
	
	sleep(20);
	
	int playerturn = 1;
	clearscreen(main_settings.r_b, main_settings.g_b, main_settings.b_b);
	
	int board_x, board_y;
	
	if(mode == 0)
	{
		board_x = main_settings.mx_size;
		board_y = main_settings.my_size;
	}
	else
	{
		board_x = main_settings.sx_size;
		board_y = main_settings.sy_size;
	}

	Game *game = new Game(board_x, board_y);
	
    game->PrintBoard();
	
	std::vector<BUTTON*> buttonvector;
	
	buttonvector.push_back(new BUTTON(220,170,22,2,21,0,0,1)); //back
	buttonvector.push_back(new BUTTON(180,4,43,2,31,0,0)); //turn
	
	for(int playercount = 0; playercount < players; playercount++)
	{
		buttonvector.push_back(new BUTTON(160,25 + playercount*20,42,2,0,20,31));
		buttonvector.push_back(new BUTTON(230,25 + playercount*20 + 1,9+playercount,3,0,20,31));
	}
	
	buttonvector.at(0)->draw_button();	
	buttonvector.at(1)->draw_button();
	
	buttonvector.at(2)->draw_button();
	buttonvector.at(3)->draw_button();
	
	while(game->CheckWin() < 0)
	{
		touchPosition touch;
		touchRead(&touch);
		
		if(buttonvector.at(0)->checktouch(touch.px,touch.py))
		{
			sleep(40);
			delete game;
			return 0;
		}
		
		for(int y = 0; y < board_y; y++)
			for(int x = 0; x < board_x; x++)
			{
				if(touch.px > x*main_settings.scale and touch.px < (x+1)*main_settings.scale and touch.py > y*main_settings.scale and touch.py < (y+1)*main_settings.scale and game->At(x,y) == 0)
				{
					game->DoMove(x, y, playerturn);
					printf("Player %i -> %i,%i\n", playerturn, x,y);
					if(mode == 1 and game->CheckWin() < 0)
					{
						if(difficulty == 0)
							game->AI_Easy();
						else if(difficulty == 1)
							game->AI_Medium();
						else if(difficulty == 2)
							game->AI_Hard();
					}
					game->PrintBoard();
					
					buttonvector.at(2+(playerturn-1)*2)->draw_button(main_settings.r_b, main_settings.g_b, main_settings.b_b);
					buttonvector.at(2+(playerturn-1)*2 +1)->draw_button(main_settings.r_b, main_settings.g_b, main_settings.b_b);
					
					if(mode == 0)
					{
						playerturn++;
						
						if(playerturn > players)
							playerturn = 1;
					}
					
					buttonvector.at(2+(playerturn-1)*2)->draw_button();
					buttonvector.at(2+(playerturn-1)*2 +1)->draw_button();
				}
			}
	}
	
	if(game->CheckWin() == 100)
	{
		printf("\nCat's game, no winner :(");
		delete game;
		return 100;
	}
	
	if(mode == 0)
		main_settings.stats_m.push_back(game->CheckWin());
	else
		main_settings.stats_s.push_back(game->CheckWin());
	
	if(game->CheckWin() > 0)
		printf("\nPlayer %i has won!", game->CheckWin());
	
	delete game;
	return 1;
}
