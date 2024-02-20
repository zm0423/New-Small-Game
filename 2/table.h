#ifndef A_TABLE_H
#define A_TABLE_H

#include<array>

namespace a{

class table
{
 public:
    enum{LEFT, RIGHT, UP, DOWN};
    table();
    int operate(int arrow);//-1 to be dead
 private:
    std::array<std::array<int, 4>, 4> data;
}

}//namespace a


#endif 