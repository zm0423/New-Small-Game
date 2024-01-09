#include<gint/display.h>
#include<gint/drivers/keydev.h>

#include "sl/sl.h"
#include "file.h"
#include "util.h"


enum{
	MENU_MINER,
	MENU_BING,
	MENU_QLDY,
	MENU_DATA,
	MENU_2048,
	MENU_EXIT,
};

int main_menu(void);
void show_data(const data_use &du);

extern bopti_image_t game;

int main()
{	
	keydev_set_standard_repeats(keydev_std(), 500 * 1000, 120 * 1000);
	data_use du;
	while(1)
	{
		switch(main_menu())
		{
			case MENU_MINER: miner::miner_main(du);break;
			case MENU_BING: miner::miner_main(du) ;break;//TBD
			case MENU_QLDY: miner::miner_main(du) ;break;//TBD
			case MENU_2048: miner::miner_main(du) ;break;//TBD
			case MENU_DATA: show_data(du)		  ;break;
			case MENU_EXIT: return 0;
		}
	}
	return 0;
}

//0 for exit
//1 for exe
int main_menu_assist(int &x, int &y, int key);

int main_menu()
{
	dclear(C_WHITE);
	dimage(0, 0, &game);
	dtext(1, 37, C_BLACK, "MINER");
	dtext(1, 46, C_BLACK, "BING");
	dtext(1, 55, C_BLACK, "QLDY");
	dtext(36, 37, C_BLACK, "2048");
	dtext(36, 55, C_BLACK, "DATA");
	drect(0, 36, 31, 44, C_INVERT);
	dupdate();
	int x = 0, y = 0, key = 0, j = 0;
	while(1)
	{
		key = getkey().key;
		drect(35 * x, 36 + 9 * y, 31 + 35 * x, 44 + 9 * y, C_INVERT);
		j = main_menu_assist(x, y, key);
		if(j == 0)
			return MENU_EXIT;
		if(j == 1)
			break;
		drect(35 * x, 36 + 9 * y, 31 + 35 * x, 44 + 9 * y, C_INVERT);
		dupdate();
	}
	if(x == 0)
	{
		switch(y)
		{
			case 0:return MENU_MINER;
			case 1:return MENU_BING;
			case 2:return MENU_QLDY;
		}
	}
	if(y == 0)
		return MENU_2048;
	return MENU_DATA;
}

int main_menu_assist(int &x, int &y, int key)
{
	if(key == KEY_UP && y == 2 && x == 1)
	{
		y = 0;
		return 2;
	}
	if(key == KEY_EXIT)
		return 0;
	if(key == KEY_EXE)
		return 1;
	if(key == KEY_UP && y != 0)
		--y;
	if(key == KEY_DOWN && y != 2)
		++y;
	if(key == KEY_LEFT && x != 0)
		--x;
	if(key == KEY_RIGHT && x != 1)
        ++x;
	if(x == 1 && y == 1)
		y = 2;
	return 2;
}

void show_data(const data_use &du)
{
	dclear(C_WHITE);
	dtext(X(1), Y(1), C_BLACK, "Miner");
	dtext(X(10), Y(1), C_BLACK, "All:");
	dprint(X(14), Y(1), C_BLACK, "%d", du.ud.m_all);
	dtext(X(1), Y(3), C_BLACK, "Easy");
	dtext(X(1), Y(4), C_BLACK, "Norm");
	dtext(X(1), Y(5), C_BLACK, "Hard");
	dtext(X(1), Y(6), C_BLACK, "Challange1 win:");
	dtext(X(1), Y(7), C_BLACK, "Challange2 win:");
	dtext(X(6), Y(2), C_BLACK, "All");
	dtext(X(16), Y(2), C_BLACK, "Rate");
	dtext(X(11), Y(2), C_BLACK, "Win");
	dprint(X(6), Y(3), C_BLACK, "%-4d", du.ud.m_e_all);
	dprint(X(6), Y(4), C_BLACK, "%-4d", du.ud.m_n_all);
	dprint(X(6), Y(5), C_BLACK, "%-4d", du.ud.m_h_all);
	dprint(X(11), Y(3), C_BLACK, "%-4d", du.ud.m_e_win);
    dprint(X(11), Y(4), C_BLACK, "%-4d", du.ud.m_n_win);
    dprint(X(11), Y(5), C_BLACK, "%-4d", du.ud.m_h_win);
	dprint(X(16), Y(6), C_BLACK, "%-3d", du.ud.m_c1_win);
	dprint(X(16), Y(7), C_BLACK, "%-3d", du.ud.m_c2_win);
	print_per(X(16), Y(3), du.ud.m_e_win, du.ud.m_e_all);
	print_per(X(16), Y(4), du.ud.m_n_win, du.ud.m_n_all);
	print_per(X(16), Y(5), du.ud.m_h_win, du.ud.m_h_all);
	dupdate();
	getkey();

	return;
}
