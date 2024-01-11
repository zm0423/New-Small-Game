#include<cstdlib>
#include<gint/display.h>
#include<gint/rtc.h>
#include<gint/clock.h>
#include<cstring>

#include "table.h"

extern bopti_image_t miner_icon;

namespace miner
{

inline void print(int x, int y, int frontc)
{
    dsubimage(6 * x + 1, 8 * y, &miner_icon, 5 * frontc, 0, 5, 6, DIMAGE_NONE);
    dupdate();
}

table::table(int mine)
{
	std::memset(this, 0, sizeof(table));
    mines = mine;
	x = 0;
	y = 0;
}

inline void table::print_s(int x_, int y_) const
{
    if(all[x_][y_].b_status == S_SEEN)
        print(x_, y_, all[x_][y_].num);
    else if(all[x_][y_].b_status == 0)
        print(x_, y_, C_BLOCK);
    else
        print(x_, y_, all[x_][y_].b_status);
}

void table::initialize()
{
    int x1, y1;
    std::srand(static_cast<int>(rtc_ticks()));
    for(int i = 0;i < mines;++i)
        while(1)
        {
            x1 = std::rand() % LENGTH;
            y1 = std::rand() % 8;
			int judge = x1 * 10 + y1;//not to generate in the corner
            if(judge == 0 || judge == 150 || judge == 7 || judge == 157)
                continue;
            if(all[x1][y1].num == BOMB)
                continue;
            all[x1][y1].num = BOMB;
            for(int j = -1;j < 2;++j)
                for(int k = -1;k < 2;++k)
                {
                    if((!j)&&(!k))
                        continue;
                    if(x1+j == -1||x1+j == LENGTH||y1+k == -1||y1+k == HEIGHT)
                        continue;
                    if((all[x1+j][y1+k]).num == BOMB)
                        continue;
                    ++all[x1+j][y1+k].num;
                }
            break;
        }
    initialized = 1;
    return;
}

void table::print_all(int type) const
{
    for(int i = 0;i < LENGTH;++i)
        for(int j = 0;j < HEIGHT;++j)
            if(!initialized)
                print(i, j, C_BLOCK);
            else if(type == NORMAL)
                print_s(i, j);
            else
                print(i, j, all[i][j].num);
    if(!initialized)
        print(x, y, C_CURSOR);
}

void table::change_pos(int x_, int y_)
{
    print_s(x, y);
    x = x_;
    y = y_;
    print(x, y, C_CURSOR);
}

void table::flag()
{
    if(all[x][y].b_status == S_SEEN)
        return;
    if(all[x][y].b_status == S_FLAG)
    {
       all[x][y].b_status = S_UNSEEN;
       flags--;
    }
    else
    {
       all[x][y].b_status = S_FLAG;
       flags++;
    }
    print_s(x, y);
    sleep_ms(250);
    print(x, y, C_CURSOR);
}

bool table::enter()
{
    if(!initialized)
        initialize();
    if(all[x][y].b_status == S_SEEN || all[x][y].b_status == S_FLAG)
        return true;
    if(all[x][y].num == BOMB)
		return false;

	all[x][y].b_status = S_SEEN;
    seen++;
    print_s(x, y);
    if(all[x][y].num == 0)
        autoprocess(x, y);
    sleep_ms(250);
    print(x, y, C_CURSOR);
    return true;
}

bool table::auto_enter()
{
    if(all[x][y].b_status == S_UNSEEN || all[x][y].b_status == S_FLAG)
        return true;
    int count = 0;
    int valid = 1;
    for(int i = -1;i < 2;++i)
        for(int j = -1;j < 2;++j)
        {
            if((!i)&&(!j))
                continue;
            if(x+i == -1||x+i == LENGTH||y+j == -1||y+j == HEIGHT)
                continue;
            if(all[x+i][y+j].b_status == S_FLAG)
            {
                count++;
                if(all[x+i][y+j].num != BOMB)
                    valid = 0;
            }
        }
    if(count != all[x][y].num)
        return true;
    if(!valid)
        return false;
    print_s(x, y);
    autoprocess(x, y);
    sleep_ms(250);
    print(x, y, C_CURSOR);
    return true;
}


void table::autoprocess(int x_, int y_)
{
    for(int i = -1;i < 2;++i)
        for(int j = -1;j < 2;++j)
        {
            if(x_+i == -1||x_+i == LENGTH||y_+j == -1||y_+j == HEIGHT)
                continue;
            if(all[x_+i][y_+j].b_status == S_SEEN || all[x_+i][y_+j].b_status == S_FLAG)
                continue;
            all[x_+i][y_+j].b_status = S_SEEN;
            seen++;
            print_s(x_+i, y_+j);
            if(all[x_+i][y_+j].num == 0)
                autoprocess(x_+i, y_+j);
        }
}


} //namespace miner
