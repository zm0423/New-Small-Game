#ifndef UTIL_H
#define UTIL_H

#include<gint/display.h>
#include<utility>
#include<array>

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

//regardless of the initial picture, cleared at end
//info refers to the place that can be selected
//return the axis, (-1, -1)if exit is pressed
template<std::size_t row, std::size_t column>
inline std::pair<int, int> menu_interface(
    std::array<std::array<int, column>, row> info,
    int up_left_x, int up_left_y, int width, int height
    )
{
    int x = 0;
    int y = 0;
    drect(up_left_x + x * width, up_left_y + y * height, 
          up_left_x + (x + 1) * width, up_left_y + (y + 1) * height, C_INVERT);
    dupdate();
    int key;
    while(1)
    {
       key = getkey().key;
       if(key == KEY_DOWN && info[x][y + 1])
       {
           drect(   up_left_x + x * width,         up_left_y + y * height, 
                    up_left_x + (x + 1) * width,   up_left_y + (y + 1) * height, C_INVERT);
           y++;
           drect(   up_left_x + x * width,         up_left_y + y * height, 
                    up_left_x + (x + 1) * width,   up_left_y + (y + 1) * height, C_INVERT);
           dupdate();
       }
       if(key == KEY_UP && info[x][y - 1])
       {
           drect(   up_left_x + x * width,         up_left_y + y * height, 
                    up_left_x + (x + 1) * width,   up_left_y + (y + 1) * height, C_INVERT);
           y--;
           drect(   up_left_x + x * width,         up_left_y + y * height, 
                    up_left_x + (x + 1) * width,   up_left_y + (y + 1) * height, C_INVERT);
           dupdate();
       }
       if(key == KEY_RIGHT && info[x + 1][y])
       {
           drect(   up_left_x + x * width,         up_left_y + y * height, 
                    up_left_x + (x + 1) * width,   up_left_y + (y + 1) * height, C_INVERT);
           x++;
           drect(   up_left_x + x * width,         up_left_y + y * height, 
                    up_left_x + (x + 1) * width,   up_left_y + (y + 1) * height, C_INVERT);
           dupdate();
       }
       if(key == KEY_LEFT && info[x - 1][y])
       {
           drect(   up_left_x + x * width,         up_left_y + y * height, 
                    up_left_x + (x + 1) * width,   up_left_y + (y + 1) * height, C_INVERT);
           x--;
           drect(   up_left_x + x * width,         up_left_y + y * height, 
                    up_left_x + (x + 1) * width,   up_left_y + (y + 1) * height, C_INVERT);
           dupdate();
       }
       if(key == KEY_EXE) break;
       if(key == KEY_EXIT)
       {
           x = y = -1;
           break;
       }
    }
    dclear(C_WHITE);
    return std::make_pair(x, y);
}







#endif
