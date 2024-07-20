#include<display.h>
#include "../util.h"





int bing_main()
{
    //start?
    
    while(1)
    {
        int i = getrequest();
        if(i = -1)
            lose();
        int j = operate(i);
        if(j = -1)
            lose();
        else if(j = 1)
            win();
        
    }



}