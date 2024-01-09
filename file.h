#ifndef FILE_H
#define FILE_H

#include<cstdint>

struct userdata
{
    //miner region
    int m_all;
    int m_e_all, m_e_win;
    int m_n_all, m_n_win;
    int m_h_all, m_h_win;
    int m_c1_win;
    int m_c2_win;

    //bing region
    int b_all, b_win;

    //2048 region
    int a_all;
    int a_high_score;
    int a_num[13]; //16384 is almost impossible...
    int a_high_pattens; //TBD



    //...
};

const int USER_DATA_SIZE = sizeof(userdata); //const

struct data_use
{
    const char16_t FILENAME[21] = u"\\\\fls0\\gc_data.bin";
    userdata ud;
    data_use();
    void update();
};



#endif
