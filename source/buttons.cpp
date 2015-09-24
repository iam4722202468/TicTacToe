#include <buttons.h>
#include <nds.h>
#include <stdio.h>

BUTTON::BUTTON(int sety, int setx, int settype, int setscale, int r1, int g1, int b1, bool getslitup)
{
	x = setx; y = sety; type = settype;
	sizex = sizes[type][0];
	sizey = sizes[type][1];
	
	r = r1;	g = g1;	b = b1;
	r_lit = 10+r; g_lit = 10+g; b_lit = 10+b;
	
	getslit = getslitup;
	islit = false;
	scale = setscale;
	
	return;
}	

void BUTTON::draw_button(int a, int b, int c)
{
	for(int sx = x; sx < x + (sizey*scale); sx++)
		for(int sy = y; sy < y + (sizex*scale); sy++)
			if(buttons[type][((sx-x)/scale*sizex+(sy-y)/scale)] == 1)
				VRAM_A[(sx * 256) + (sy)] = RGB15(a,b,c);
	return;
}

void BUTTON::draw_button() { draw_button(r,g,b);}

bool BUTTON::checktouch(int pressx, int pressy)
{
	if(pressy >= x && pressy <= x + sizey*scale && pressx >= y && pressx <= y + sizex*scale) 
	{
		if(not islit and getslit)
			draw_button(r_lit, g_lit, b_lit);
		islit = true;
		return true;
	}
	else if(islit)
	{
		draw_button(r,g,b);
		islit = false;
	}
	return false;
}

void clearscreen(int r, int g, int b)
{
	for(int sx = 0; sx < 256; sx++)
	    for(int sy = 0; sy < 192; sy++)
			VRAM_A[(sy * 256) + (sx)] = RGB15(r,g,b);
	return;
}

int sleep(int time)
{
	while(time != 0)
	{
		time--;
		swiWaitForVBlank();
	}
	return 0;
}

void plot(int x, int y, int r, int g, int b)
{
	VRAM_A[x + 256*y] = RGB15(r,g,b);
	return;
}

void rect(int x1, int y1, int x2, int y2, int r, int g, int b)
{

	for(int y = y1; y < y1+y2; y++)
		for(int x = x1; x < x1+x2; x++)
			plot(x,y,r,g,b);

	return;
}
