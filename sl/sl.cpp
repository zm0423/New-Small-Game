#include<gint/display.h>
#include<gint/keyboard.h>
#include<gint/clock.h>
#include<gint/timer.h>
#include "sl.h"
#include "../util.h"

extern bopti_image_t miner_instruction;
extern bopti_image_t miner_about;
extern bopti_image_t miner_difficulty;
extern bopti_image_t miner_win;
extern bopti_image_t miner_lose;
extern bopti_image_t miner_menu;

namespace miner
{

static int callback_tick(volatile int *tick)
{
    *tick = 1;
    return TIMER_CONTINUE;
}

void miner_main(data_use &du)
{
    int main;
    int key;
    int check = 0;
    int diff;

    int end_choice;

    /* main menu */
    while(1)
    {
        main = menu();
        if(main == 2)
        {
            instruction();
            continue;
        }
        if(main == 3)
        {
            about();
            continue;
        }
        if(main == 4)
            return;
        diff = difficulty();
        if(diff == DIFF_EXIT)
            continue;
        while(1)
        {    
            table ta(DIFF_NUM[diff]);
            print_all(ta);
            key = getkey().key;
            while(!(check = operatekey(ta, key)))
                key = getkey().key;
			if(check == 3)
				break;
            end_choice = end(ta, du, check - 1);
            if(end_choice == 2)
            {
                diff = difficulty();
                if(diff == DIFF_EXIT)
                    break;
            }
            if(end_choice == 3)break;
        }
    }
    return;
}

int menu()
{
	dclear(C_WHITE);
    dimage(0, 0, &miner_menu);
    drect(25, 21, 91, 29, C_INVERT);
    dupdate();
    int key;
    int a = 1;
    while(1)
    {
       key = getkey().key;
       if(key == KEY_DOWN && a != 4)
       {
           drect(25, 10 * a + 11, 91, 10 * a + 19, C_INVERT);
           a++;
           drect(25, 10 * a + 11, 91, 10 * a + 19, C_INVERT);
           dupdate();
       }
       if(key == KEY_UP && a != 1)
       {
           drect(25, 10 * a + 11, 91, 10 * a + 19, C_INVERT);
           a--;
           drect(25, 10 * a + 11, 91, 10 * a + 19, C_INVERT);
           dupdate();
       }
       if(key == KEY_EXE) break;
       if(key == KEY_EXIT)
       {
           a = 4;
           break;
       }
    }
    dclear(C_WHITE);
    return a;
}

void instruction(void)
{
    int a = 0;
    key_event_t key;
	key.key = 0;
    dclear(C_WHITE);
    dimage(0, 0, &miner_instruction);
    volatile int tick = 0;
    int timer = timer_configure(TIMER_ANY, 800 * 1000, GINT_CALL(callback_tick, &tick));
    timer_start(timer);
    while(key.type == KEYEV_NONE || key.key != KEY_EXE)
    {
        dtext(1, 50, a ? C_WHITE : C_BLACK, "PRESS:[EXE]");
        dupdate();
        key = getkey_opt(GETKEY_DEFAULT, &tick);
        a = (a + 1) % 2;
        tick = 0;
    }
    timer_stop(timer);
    dclear(C_WHITE);
}

void about(void)
{
    key_event_t key;
	key.key = 0;
    int a = 0;
    volatile int tick = 0;
    dclear(C_WHITE);
    dimage(0, 0, &miner_about);
    int timer = timer_configure(TIMER_ANY, 800 * 1000, GINT_CALL(callback_tick, &tick));
    timer_start(timer);
    while(key.type == KEYEV_NONE || key.key != KEY_EXE)
    {
        dtext(1, 50, a ? C_WHITE : C_BLACK, "PRESS:[EXE]");
        dupdate();
        key = getkey_opt(GETKEY_DEFAULT, &tick);
        a = (a + 1) % 2;
        tick = 0;
    }
    timer_stop(timer);
    dclear(C_WHITE);
}

int difficulty()
{
    int a = 0;
    dclear(C_WHITE);
    dimage(0, 0, &miner_difficulty);
    drect(30, 8 * a + 20, 92, 8 * a + 28, C_INVERT);
    dupdate();
    int key;
    while(1)
    {
       key = getkey().key;
       if(key == KEY_DOWN && a != 4)
       {
           drect(30, 8 * a + 20, 92, 8 * a + 28, C_INVERT);
           a++;
		   drect(30, 8 * a + 20, 92, 8 * a + 28, C_INVERT);
           dupdate();
       }
       if(key == KEY_UP && a != 0)
       {
           drect(30, 8 * a + 20, 92, 8 * a + 28, C_INVERT);
           a--;
		   drect(30, 8 * a + 20, 92, 8 * a + 28, C_INVERT);
           dupdate();
       }
       if(key == KEY_EXE) break;
       if(key == KEY_EXIT)
       {
           a = DIFF_EXIT;
           break;
       }
    }
    dclear(C_WHITE);
    return a;
}

void print_all(const table &ta)
{
    ta.print_all(table::NORMAL);
    dvline(98, C_BLACK);
    dvline(99, C_BLACK);
    dvline(100, C_BLACK);
    dtext(104, 13, C_BLACK, "ALL:");
    dprint(104, 21, C_BLACK, "%d",ta.s_mines());
    dtext(104, 37, C_BLACK, "NOW:");
    dprint(104, 45, C_BLACK, "%d",ta.s_mines() - ta.s_flags());
    dupdate();
}

int operatekey(table &ta, int key)
{
    bool ck = true;
	bool pa = true;
    int xx = ta.s_x();
    int yy = ta.s_y();
    switch(key)
    {
        case KEY_COS:    ck = ta.enter();                  break;
        case KEY_F6:     ta.flag();                        break;
        case KEY_TAN:    ck = ta.auto_enter();             break;
		case KEY_LEFT:   ta.change_pos((xx + 15) % 16, yy);break;
        case KEY_RIGHT:  ta.change_pos(++xx % 16, yy);     break;
        case KEY_DOWN:   ta.change_pos(xx, ++yy % 8);      break;
		case KEY_UP:     ta.change_pos(xx, (yy + 7) % 8);  break;
		case KEY_EXIT:   pa = pause(ta);
	}
	drect(104, 45, 115, 52, C_WHITE);
    dprint(104, 45, C_BLACK, "%d", ta.s_mines() - ta.s_flags());

	dupdate();
	if(pa == false)
		return 3;
	if(ck == false)
        return 1;
    if(ta.s_seen() == ALL_NUM - ta.s_mines())
        return 2;
    return 0;
}


int end(const table &ta, data_use &du, bool win)
{
    int a = 1;
    volatile int tick = 0;
    int key;
    ta.print_all(table::END);

    int timer = timer_configure(TIMER_ANY, 2000 * 1000, GINT_CALL(callback_tick, &tick));
    timer_start(timer);
    getkey_opt(GETKEY_DEFAULT, &tick);
    timer_stop(timer);

    ++du.ud.m_all;
    if(ta.s_mines() == DIFF_NUM[EASY])
	{
		++du.ud.m_e_all;
		if(win)
            ++du.ud.m_e_win;
	}
	if(ta.s_mines() == DIFF_NUM[NORMAL])
	{
		++du.ud.m_n_all;
		if(win)
            ++du.ud.m_n_win;
	}
	if(ta.s_mines() == DIFF_NUM[HARD])
    {
		++du.ud.m_h_all;
		if(win)
            ++du.ud.m_h_win;
	}
	if(ta.s_mines() == DIFF_NUM[C_ONE])
		++du.ud.m_c1_win;
	if(ta.s_mines() == DIFF_NUM[C_TWO])
		++du.ud.m_c2_win;
    du.update();

    dimage(0, 0, win ? &miner_win : &miner_lose);
    drect(3, 10 * a + 21, 75, 10 * a + 29, C_INVERT);
	dupdate();
	while(1)
    {
       key = getkey().key;
       if(key == KEY_DOWN && a != 3)
       {
           drect(3, 10 * a + 21, 75, 10 * a + 29, C_INVERT);
           a++;
           drect(3, 10 * a + 21, 75, 10 * a + 29, C_INVERT);
           dupdate();
       }
       if(key == KEY_UP && a != 1)
       {
           drect(3, 10 * a + 21, 75, 10 * a + 29, C_INVERT);
           a--;
           drect(3, 10 * a + 21, 75, 10 * a + 29, C_INVERT);
           dupdate();
       }
       if(key == KEY_EXE) break;
       if(key == KEY_EXIT)
       {
           a = 3;
           break;
       }
    }
    dclear(C_WHITE);
    return a;
}

bool pause(const table &ta)
{
	drect_border(11, 11, 114, 43, C_WHITE, 1, C_BLACK);
	dline(12, 44, 115, 44, C_BLACK);
	dline(115, 12, 115, 44, C_BLACK);
	dtext(X(4), Y(3), C_BLACK, "Pause");
	dtext(X(4), Y(4), C_BLACK, "[F1]:Exit");
	dtext(X(4), Y(5), C_BLACK, "[EXE]:Continue");
	dupdate();
	while(1)
	{
		int key = getkey().key;
		if(key == KEY_EXE)
			break;
		if(key == KEY_F1)
			return false;
	}
	print_all(ta);
	return true;
}

} //namespace miner
