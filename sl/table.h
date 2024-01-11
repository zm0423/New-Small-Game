#ifndef TABLE_H
#define TABLE_H

#include<array>
#include<exception>

namespace miner
{


/* block status */

enum{
    S_UNSEEN = 9,
    S_SEEN = 1,
    S_FLAG = 10,
};

/* fontc code */
/* small0~8:0~8 */
enum{
    C_BLOCK = 9,
    C_FLAG = 10,
    C_CURSOR = 11,
    C_MINE = 12,

    BOMB = 12,
};

struct block
{
    int b_status{0};
    int num{0};
};

const int ALL_NUM = 16 * 8;

const int LENGTH = 16;
const int HEIGHT = 8;

/* x:0~15 y:0~7 */
class table
{
 public:
    explicit table(int mine):mines(mine){}
    void initialize();
    enum{NORMAL, END};
    void print_all(int type) const;
    void change_pos(int x_, int y_);
    bool enter();
    bool auto_enter();
    void flag();

    int s_mines() const {return mines;}
    int s_flags() const {return flags;}
    int s_seen() const {return seen;}
    int s_x() const {return x;}
    int s_y() const {return y;}

 private:
    inline void print_s(int x_, int y_) const;
    void autoprocess(int x_, int y_);
    std::array<std::array<block, HEIGHT>, LENGTH> all{};
    int x{0};
    int y{0};
    int flags{0};
    int seen{0};
    int mines{0};
    int initialized{0};
};


} //namespace miner

#endif
