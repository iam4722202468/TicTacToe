#include <nds.h>
#include <stdio.h>
#include <vector>

#include <game.h>
#include <buttons.h>

using namespace std;

settings main_settings;

int titlescreen()
{
	consoleDemoInit();
	
	clearscreen(main_settings.r_b, main_settings.g_b, main_settings.b_b);
	vector<BUTTON*> buttonvector;
	
	buttonvector.push_back(new BUTTON(45,0,23,3,30,0,0));	//tic
	buttonvector.push_back(new BUTTON(90,0,24,3,0,30,0,0));	//tac
	buttonvector.push_back(new BUTTON(138,0,25,3,0,0,30));	//toe
	
	buttonvector.push_back(new BUTTON(0,40,26,2,31,31,0,1));	//singleplayer
	buttonvector.push_back(new BUTTON(0,70,27,2,0,31,31,1));	//multiplayer
	buttonvector.push_back(new BUTTON(0,130,28,2,31,0,31,1));	//settings
	
	buttonvector.push_back(new BUTTON(0,100,49,2,10,0,30,1));	//stats 6
	
	buttonvector.push_back(new BUTTON(2,180,41,1,0,0,31,1));	//copyright
	
	for(unsigned int z = 0; z < buttonvector.size(); z++)
	{
		buttonvector.at(z)->setlit(31,31,31);
		buttonvector.at(z)->draw_button();
	}
	
	int chosen = 0;
	
	while(chosen == 0)
	{
		touchPosition touch;
		touchRead(&touch);
		
		for(unsigned int z = 0; z < buttonvector.size(); z++)
			if(buttonvector.at(z)->checktouch(touch.px, touch.py))
			{
				if(z == 3)
					chosen = 1;
				else if(z == 4)
					chosen = 2;
				else if(z == 5)
					chosen = 3;
				else if(z == 6)
					chosen = 5;
			}
	}
	sleep(40);
	
	return chosen;
}

int settings_page()
{
	consoleDemoInit();
	printf("		  Settings");
	
	clearscreen(main_settings.r_b, main_settings.g_b, main_settings.b_b);
	vector<BUTTON*> buttonvector;
	
	buttonvector.push_back(new BUTTON(220,170,22,2,21,0,0,1)); //back
	
	buttonvector.push_back(new BUTTON(45,0,28,3,31,0,31));	//settings
	buttonvector.push_back(new BUTTON(0,25,31,2,31,0,0)); //board
	buttonvector.push_back(new BUTTON(0,115,32,2,31,0,0)); //colour
	
	buttonvector.push_back(new BUTTON(20,50,26,1,0,31,0)); //singleplayer 4
		buttonvector.push_back(new BUTTON(40,65,29,1,31,31,0)); //x size
			buttonvector.push_back(new BUTTON(80,65,3,1,0,10,30,1)); // 6
			buttonvector.push_back(new BUTTON(90,65,8+main_settings.sx_size,2,10,10,31)); //
			buttonvector.push_back(new BUTTON(100,65,1,1,0,10,30,1));// 8
		
		buttonvector.push_back(new BUTTON(120,65,30,1,31,31,0)); //y size
			buttonvector.push_back(new BUTTON(160,65,3,1,0,10,30,1)); // 10
			buttonvector.push_back(new BUTTON(170,65,8+main_settings.sy_size,2,10,10,31)); //
			buttonvector.push_back(new BUTTON(180,65,1,1,0,10,30,1)); // 12
	
	buttonvector.push_back(new BUTTON(20,75,27,1,0,31,0)); //multiplayer
		buttonvector.push_back(new BUTTON(40,90,29,1,31,31,0)); //x size
			buttonvector.push_back(new BUTTON(80,90,3,1,0,10,30,1)); //15
			buttonvector.push_back(new BUTTON(90,90,8+main_settings.mx_size,2,10,10,31)); //
			buttonvector.push_back(new BUTTON(100,90,1,1,0,10,30,1));//17
		
		buttonvector.push_back(new BUTTON(120,90,30,1,31,31,0)); //y size
			buttonvector.push_back(new BUTTON(160,90,3,1,0,10,30,1)); //19
			buttonvector.push_back(new BUTTON(170,90,8+main_settings.my_size,2,10,10,31)); //
			buttonvector.push_back(new BUTTON(180,90,1,1,0,10,30,1)); //21
	
	buttonvector.push_back(new BUTTON(20,125+15,33,1,0,31,0)); //background
			buttonvector.push_back(new BUTTON(90,125+15,3,1,0,10,30,1)); // 23
			buttonvector.push_back(new BUTTON(100,125+15,8 + main_settings.r_b/10, 2,10,10,31)); //
			buttonvector.push_back(new BUTTON(108,125+15,8 + main_settings.r_b%10, 2,10,10,31)); //
			buttonvector.push_back(new BUTTON(119,125+15,1,1,0,10,30,1));// 26
			
			buttonvector.push_back(new BUTTON(90 +50,125+15,3,1,0,10,30,1)); // 27
			buttonvector.push_back(new BUTTON(100+50,125+15,8 + main_settings.g_b/10, 2,10,10,31)); //
			buttonvector.push_back(new BUTTON(108+50,125+15,8 + main_settings.g_b%10, 2,10,10,31)); //
			buttonvector.push_back(new BUTTON(119+50,125+15,1,1,0,10,30,1));// 30
			
			buttonvector.push_back(new BUTTON(90 +100,125+15,3,1,0,10,30,1)); // 31
			buttonvector.push_back(new BUTTON(100+100,125+15,8 + main_settings.b_b/10, 2,10,10,31)); //
			buttonvector.push_back(new BUTTON(108+100,125+15,8 + main_settings.b_b%10, 2,10,10,31)); //
			buttonvector.push_back(new BUTTON(119+100,125+15,1,1,0,10,30,1));// 34
			
	buttonvector.push_back(new BUTTON(20,105,47,1,0,31,0)); //linewinsize
		buttonvector.push_back(new BUTTON(90 ,107,3,1,0,10,30,1)); // 36
		buttonvector.push_back(new BUTTON(100,107,8 + main_settings.winsize, 2,10,10,31)); //
		buttonvector.push_back(new BUTTON(110,107,1,1,0,10,30,1));// 38
		
	for(unsigned int z = 0; z < buttonvector.size(); z++)
	{
		buttonvector.at(z)->setlit(31,31,31);
		buttonvector.at(z)->draw_button();
	}
	
	buttonvector.at(0)->setlit(31,10,10);
	
	int chosen = -1;
	
	while(chosen == -1)
	{
		touchPosition touch;
		touchRead(&touch);
		
		for(unsigned int z = 0; z < buttonvector.size(); z++)
			if(buttonvector.at(z)->checktouch(touch.px, touch.py))
			{
				if(z == 0)
					chosen = 0;
				else if(z == 6 and main_settings.sx_size > 3)
				{
					main_settings.sx_size--;
					buttonvector.at(7)->draw_button(main_settings.r_b, main_settings.g_b, main_settings.b_b);
					buttonvector.at(7)->resetinfo(90,65,8+main_settings.sx_size,2);
					buttonvector.at(7)->draw_button();
					sleep(20);
				}
				else if(z == 8 and main_settings.sx_size < 9)
				{
					main_settings.sx_size++;
					buttonvector.at(7)->draw_button(main_settings.r_b, main_settings.g_b, main_settings.b_b);
					buttonvector.at(7)->resetinfo(90,65,8+main_settings.sx_size,2);
					buttonvector.at(7)->draw_button();
					sleep(20);
				}
				
				else if(z == 10 and main_settings.sy_size > 3)
				{
					main_settings.sy_size--;
					buttonvector.at(11)->draw_button(main_settings.r_b, main_settings.g_b, main_settings.b_b);
					buttonvector.at(11)->resetinfo(170,65,8+main_settings.sy_size,2);
					buttonvector.at(11)->draw_button();
					sleep(20);
				}
				else if(z == 12 and main_settings.sy_size < 9)
				{
					main_settings.sy_size++;
					buttonvector.at(11)->draw_button(main_settings.r_b, main_settings.g_b, main_settings.b_b);
					buttonvector.at(11)->resetinfo(170,65,8+main_settings.sy_size,2);
					buttonvector.at(11)->draw_button();
					sleep(20);
				}

				else if(z == 15 and main_settings.mx_size > 3)
				{
					main_settings.mx_size--;
					buttonvector.at(16)->draw_button(main_settings.r_b, main_settings.g_b, main_settings.b_b);
					buttonvector.at(16)->resetinfo(90,90,8+main_settings.mx_size,2);
					buttonvector.at(16)->draw_button();
					sleep(20);
				}
				else if(z == 17 and main_settings.mx_size < 9)
				{
					main_settings.mx_size++;
					buttonvector.at(16)->draw_button(main_settings.r_b, main_settings.g_b, main_settings.b_b);
					buttonvector.at(16)->resetinfo(90,90,8+main_settings.mx_size,2);
					buttonvector.at(16)->draw_button();
					sleep(20);
				}
				
				else if(z == 19 and main_settings.my_size > 3)
				{
					main_settings.my_size--;
					buttonvector.at(20)->draw_button(main_settings.r_b, main_settings.g_b, main_settings.b_b);
					buttonvector.at(20)->resetinfo(170,90,8+main_settings.my_size,2);
					buttonvector.at(20)->draw_button();
					sleep(20);
				}
				else if(z == 21 and main_settings.my_size < 9)
				{
					main_settings.my_size++;
					buttonvector.at(20)->draw_button(main_settings.r_b, main_settings.g_b, main_settings.b_b);
					buttonvector.at(20)->resetinfo(170,90,8+main_settings.my_size,2);
					buttonvector.at(20)->draw_button();
					sleep(20);
				}
				
				else if(z == 23 and main_settings.r_b > 0)
				{
					main_settings.r_b--;
					buttonvector.at(24)->resetinfo(100,125+15,8 + main_settings.r_b/10, 2);
					buttonvector.at(25)->resetinfo(108,125+15,8 + main_settings.r_b%10, 2);
					
					clearscreen(main_settings.r_b, main_settings.g_b, main_settings.b_b);
					
					for(unsigned int z = 0; z < buttonvector.size(); z++)
						buttonvector.at(z)->draw_button();

					sleep(10);
				}
				else if(z == 26 and main_settings.r_b < 31)
				{
					main_settings.r_b++;
					buttonvector.at(24)->resetinfo(100,125+15,8 + main_settings.r_b/10, 2);
					buttonvector.at(25)->resetinfo(108,125+15,8 + main_settings.r_b%10, 2);
					
					clearscreen(main_settings.r_b, main_settings.g_b, main_settings.b_b);
					
					for(unsigned int z = 0; z < buttonvector.size(); z++)
						buttonvector.at(z)->draw_button();

					sleep(10);
				}
				else if(z == 27 and main_settings.g_b > 0)
				{
					main_settings.g_b--;
					buttonvector.at(28)->resetinfo(100+50,125+15,8 + main_settings.g_b/10, 2);
					buttonvector.at(29)->resetinfo(108+50,125+15,8 + main_settings.g_b%10, 2);
					
					clearscreen(main_settings.r_b, main_settings.g_b, main_settings.b_b);
					
					for(unsigned int z = 0; z < buttonvector.size(); z++)
						buttonvector.at(z)->draw_button();

					sleep(10);
				}
				else if(z == 30 and main_settings.g_b < 31)
				{
					main_settings.g_b++;
					buttonvector.at(28)->resetinfo(100+50,125+15,8 + main_settings.g_b/10, 2);
					buttonvector.at(29)->resetinfo(108+50,125+15,8 + main_settings.g_b%10, 2);
					
					clearscreen(main_settings.r_b, main_settings.g_b, main_settings.b_b);
					
					for(unsigned int z = 0; z < buttonvector.size(); z++)
						buttonvector.at(z)->draw_button();

					sleep(10);
				}
				else if(z == 31 and main_settings.b_b > 0)
				{
					main_settings.b_b--;
					buttonvector.at(32)->resetinfo(100+100,125+15,8 + main_settings.b_b/10, 2);
					buttonvector.at(33)->resetinfo(108+100,125+15,8 + main_settings.b_b%10, 2);
					
					clearscreen(main_settings.r_b, main_settings.g_b, main_settings.b_b);
					
					for(unsigned int z = 0; z < buttonvector.size(); z++)
						buttonvector.at(z)->draw_button();

					sleep(10);
				}
				else if(z == 34 and main_settings.b_b < 31)
				{
					main_settings.b_b++;
					buttonvector.at(32)->resetinfo(100+100,125+15,8 + main_settings.b_b/10, 2);
					buttonvector.at(33)->resetinfo(108+100,125+15,8 + main_settings.b_b%10, 2);
					
					clearscreen(main_settings.r_b, main_settings.g_b, main_settings.b_b);
					
					for(unsigned int z = 0; z < buttonvector.size(); z++)
						buttonvector.at(z)->draw_button();

					sleep(10);
				}
				
				else if(z == 36 and main_settings.winsize > 3)
				{
					main_settings.winsize--;
					buttonvector.at(37)->draw_button(main_settings.r_b, main_settings.g_b, main_settings.b_b);
					buttonvector.at(37)->resetinfo(100,107,8 + main_settings.winsize, 2);
					buttonvector.at(37)->draw_button();
					sleep(20);
				}
				else if(z == 38 and main_settings.winsize < 9)
				{
					main_settings.winsize++;
					buttonvector.at(37)->draw_button(main_settings.r_b, main_settings.g_b, main_settings.b_b);
					buttonvector.at(37)->resetinfo(100,107,8 + main_settings.winsize, 2);
					buttonvector.at(37)->draw_button();
					sleep(20);
				}
			}
	}
	
	sleep(40);
	
	return chosen;
}

int single_player()
{
	consoleDemoInit();
	printf("		  Single Player\n\nCurrent board size: %i by %i", main_settings.sx_size, main_settings.sy_size);
	
	clearscreen(main_settings.r_b, main_settings.g_b, main_settings.b_b);
	vector<BUTTON*> buttonvector;
	
	int difficulty = 2;
	
	int first_player = 1;
	
	buttonvector.push_back(new BUTTON(220,170,22,2,21,0,0,1)); //back
	buttonvector.push_back(new BUTTON(30,0,26,3,31,31,0));	//single player
	buttonvector.push_back(new BUTTON(65,80,40,2,main_settings.r_b, main_settings.g_b, main_settings.b_b)); //clear 2
	
	buttonvector.push_back(new BUTTON(75,40,34,2,31,0,0)); //difficulty
			buttonvector.push_back(new BUTTON(45,80,3,2,0,10,30,1)); //
			buttonvector.push_back(new BUTTON(65,80,35+difficulty,2,10,10,31)); //5
			buttonvector.push_back(new BUTTON(175,80,1,2,0,10,30,1));//
	
	buttonvector.push_back(new BUTTON(90,160,39,2,0,31,0,1)); //start
	
	buttonvector.push_back(new BUTTON(10,110,50,2,0,31,0)); //first turn
	buttonvector.push_back(new BUTTON(120,110,42,2,0,31,0)); //player
	
	for(unsigned int z = 0; z < buttonvector.size(); z++)
	{
		buttonvector.at(z)->setlit(31,31,31);
		buttonvector.at(z)->draw_button();
	}
	
	buttonvector.at(0)->setlit(31,10,10);
	
	int chosen = -1;
	while(chosen == -1)
	{
		touchPosition touch;
		touchRead(&touch);
		
		for(unsigned int z = 0; z < buttonvector.size(); z++)
			if(buttonvector.at(z)->checktouch(touch.px, touch.py))
			{
				if(z == 0)
				{
					sleep(40);
					return 0;
				}
				else if(z == 7)
				{
					sleep(40);
					chosen = 1;
				}
				else if(z == 4 and difficulty > 0)
				{
					difficulty--;
					buttonvector.at(5)->resetinfo(65,80,35+difficulty,2);
					buttonvector.at(2)->draw_button(main_settings.r_b, main_settings.g_b, main_settings.b_b);
					buttonvector.at(5)->draw_button();
					sleep(20);
				}
				else if(z == 6 and difficulty < 3)
				{
					difficulty++;
					buttonvector.at(5)->resetinfo(65,80,35+difficulty,2);
					buttonvector.at(2)->draw_button(main_settings.r_b, main_settings.g_b, main_settings.b_b);
					buttonvector.at(5)->draw_button();
					sleep(20);
				}
			}
	}
	
	sleep(40);
	
	int returned = startgame(2, difficulty, 1);
	
	if(returned == 0)
		return 0;
	
	chosen = -1;
	
	buttonvector.clear();
	
	buttonvector.push_back(new BUTTON(220,170,22,2,21,0,0,1)); //back
	buttonvector.push_back(new BUTTON(167,150,45,1,0,21,0,1)); //play again
	
	buttonvector.push_back(new BUTTON(188,120,48,2,21,31,0)); //tie
	
	for(unsigned int z = 0; z < buttonvector.size()-1; z++)
		buttonvector.at(z)->draw_button();
	
	if(returned == 100)
		buttonvector.at(2)->draw_button();
	
	while(chosen < 0)
	{
		touchPosition touch;
		touchRead(&touch);
		
		for(unsigned int z = 0; z < buttonvector.size(); z++)
			if(buttonvector.at(z)->checktouch(touch.px, touch.py))
			{
				if(z == 0)
					chosen = 0;
				else if(z == 1)
				{
					sleep(40);
					returned = startgame(2, difficulty, 1);
					if(returned == 0)
						return 0;
					else if(returned == 100)
						buttonvector.at(2)->draw_button();
				}
			}
	}
	
	sleep(40);
	
	return chosen;
}

int multi_player()
{
	consoleDemoInit();
	
	printf("		  Multi Player\n\nCurrent board size: %i by %i", main_settings.mx_size, main_settings.my_size);
	
	int players = 2;
	int chosen = -1;
	
	clearscreen(main_settings.r_b, main_settings.g_b, main_settings.b_b);
		
	vector<BUTTON*> buttonvector;
	
	buttonvector.push_back(new BUTTON(220,170,22,2,21,0,0,1)); //back
	buttonvector.push_back(new BUTTON(30,0,27,3,0,31,31));	//multiplayer
	
	buttonvector.push_back(new BUTTON(30,40,46,2,20,0,20)); //amount of players
		buttonvector.push_back(new BUTTON(85,70,3,2,0,10,30,1)); //3
		buttonvector.push_back(new BUTTON(105,70,8+players,4,10,10,31)); //player number
		buttonvector.push_back(new BUTTON(125,70,1,2,0,10,30,1));//5
	
	buttonvector.push_back(new BUTTON(90,110,39,2,0,31,0,1)); //start
	
	buttonvector.at(3)->setlit(31,31,31);
	buttonvector.at(5)->setlit(31,31,31);
	buttonvector.at(6)->setlit(31,31,31);
	
	for(unsigned int z = 0; z < buttonvector.size(); z++)
		buttonvector.at(z)->draw_button();
	
	while(chosen < 0)
	{
		touchPosition touch;
		touchRead(&touch);
		
		for(unsigned int z = 0; z < buttonvector.size(); z++)
			if(buttonvector.at(z)->checktouch(touch.px, touch.py))
			{
				if(z == 0)
				{
					sleep(30);
					return 0;
				}
				else if(z == 6)
					chosen = 1;
				else if(z == 3 and players > 2)
				{
					buttonvector.at(4)->draw_button(main_settings.r_b, main_settings.g_b, main_settings.b_b);
					players--;
					buttonvector.at(4)->resetinfo(105,70,8+players,4);
					buttonvector.at(4)->draw_button();
					sleep(20);
				}
				else if(z == 5 and players < 5)
				{
					buttonvector.at(4)->draw_button(main_settings.r_b, main_settings.g_b, main_settings.b_b);
					players++;
					buttonvector.at(4)->resetinfo(105,70,8+players,4);
					buttonvector.at(4)->draw_button();
					sleep(20);
				}
			}
	}
	
	sleep(40);
	
	int returned = startgame(players, 0, 0);
	if(returned == 0)
		return 0;
	
	chosen = -1;
	
	buttonvector.clear();
	
	buttonvector.push_back(new BUTTON(220,170,22,2,21,0,0,1)); //back
	buttonvector.push_back(new BUTTON(167,150,45,1,0,21,0,1)); //play again
	
	buttonvector.push_back(new BUTTON(188,120,48,2,21,31,0)); //tie
	
	for(unsigned int z = 0; z < buttonvector.size()-1; z++)
		buttonvector.at(z)->draw_button();
	
	if(returned == 100)
		buttonvector.at(2)->draw_button();
	
	while(chosen < 0)
	{
		touchPosition touch;
		touchRead(&touch);
		
		for(unsigned int z = 0; z < buttonvector.size(); z++)
			if(buttonvector.at(z)->checktouch(touch.px, touch.py))
			{
				if(z == 0)
					chosen = 0;
				else if(z == 1)
				{
					sleep(40);
					returned = startgame(players, 0, 0);
					if(returned == 0)
						return 0;
					else if(returned == 100)
						buttonvector.at(2)->draw_button();
				}
			}
	}
	
	sleep(40);
	
	return chosen;
}

int statistics_page()
{
	int chosen = -1;
	
	consoleDemoInit();
	printf("		  Statistics\n\n");
	clearscreen(main_settings.r_b, main_settings.g_b, main_settings.b_b);
	
	vector<BUTTON*> buttonvector;
	
	buttonvector.push_back(new BUTTON(220,170,22,2,21,0,0,1)); //back
	
	buttonvector.push_back(new BUTTON(45,0,49,3,10,0,30,1)); //Statistics
	
	for(unsigned int z = 0; z < buttonvector.size(); z++)
		buttonvector.at(z)->draw_button();
	
	
	if(main_settings.stats_s.size() == 0)
		printf("No Single Player statistics!\n\n");
	else
	{
		int maxplayers = 0;
		vector<int> wincounter;
		
		for(int z = 0; z < main_settings.stats_s.size(); z++)
		{
			if(main_settings.stats_s.at(z) > maxplayers)
			{
				maxplayers = main_settings.stats_s.at(z);
				
				while(wincounter.size() < maxplayers)
				{
					wincounter.push_back(0);
				}
				
			}
			
			wincounter.at(main_settings.stats_s.at(z)-1)++;
		}
		
		double percentagefind;
		
		for(int z = 0; z < wincounter.size(); z++)
		{
			percentagefind = wincounter.at(z);
			printf("Player %i has won %i times (%.0f%%)\n", z+1, wincounter.at(z), (percentagefind/main_settings.stats_s.size())*100);
		}
		printf("\n");
	}
	
	if(main_settings.stats_m.size() == 0)
		printf("No Multi Player statistics!\n\n");
	else
	{
		int maxplayers = 0;
		vector<int> wincounter;
		
		for(int z = 0; z < main_settings.stats_m.size(); z++)
		{
			if(main_settings.stats_m.at(z) > maxplayers)
			{
				maxplayers = main_settings.stats_m.at(z);
				
				while(wincounter.size() < maxplayers)
				{
					wincounter.push_back(0);
				}
				
			}
			
			wincounter.at(main_settings.stats_m.at(z)-1)++;
		}
		
		double percentagefind;
		
		for(int z = 0; z < wincounter.size(); z++)
		{
			percentagefind = wincounter.at(z);
			printf("Player %i has won %i times (%.0f%%)\n", z+1, wincounter.at(z), (percentagefind/main_settings.stats_m.size())*100);
		}
		
	}
	
	
	while(chosen < 0)
	{
		touchPosition touch;
		touchRead(&touch);
		
		for(unsigned int z = 0; z < buttonvector.size(); z++)
			if(buttonvector.at(z)->checktouch(touch.px, touch.py))
			{
				if(z == 0)
				{
					sleep(40);
					chosen = 0;
				}
			}
	}
	return chosen;
}

int main(void) {
	
	consoleDemoInit();
	videoSetMode(MODE_FB0);
	vramSetBankA(VRAM_A_LCD);
	lcdMainOnBottom();
	
	main_settings.sx_size = 4; 	main_settings.sy_size = 4; 	main_settings.mx_size = 3; 	main_settings.my_size = 3;
	main_settings.r_b = 0; 	main_settings.g_b = 0; 	main_settings.b_b = 0;
	
	main_settings.winsize = 4;
	
	clearscreen(main_settings.r_b, main_settings.g_b, main_settings.b_b);
	
	int chosen = titlescreen();
	
	while(chosen < 10)
	{
		if(chosen == 0)
			chosen = titlescreen();
		else if(chosen == 1)
			chosen = single_player(); // single player
		else if(chosen == 2)
			chosen = multi_player(); // multiplayer
		else if(chosen == 3)
			chosen = 4; // setting main
		else if(chosen == 4)
			chosen = settings_page();	
		else if(chosen == 5)
			chosen = statistics_page();
	}
	
	while(1) {
		touchPosition touch;
		touchRead(&touch);
		swiWaitForVBlank();
	}
	
	return 0;
}
