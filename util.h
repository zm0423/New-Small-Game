#ifndef UTIL_H
#define UTIL_H

#include<gint/display.h>

inline constexpr int X(int x){return 6 * x - 5;}
inline constexpr int Y(int y){return 8 * y - 8;}

inline void print_per(int x, int y, int up, int down)
{
	if(up == down && up != 0)
	{
		dtext(x, y, C_BLACK, "100 %");
		return;
	}
	int upper;
	int lower;
	if(down == 0)
		upper = lower = 0;
	else
	{	
		int a = up * 10000 / down;
		upper = a / 100;
		lower = a - 100 * upper;
	}
	dprint(x, y, C_BLACK, "%2d.%2.2d%%", upper, lower);
}









#endif
