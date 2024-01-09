#include<gint/bfile.h>
#include<gint/gint.h>
#include "file.h"
#include<cstring>

data_use::data_use()
{
	std::memset(&ud, 0, sizeof(ud));
    int handle = gint_world_switch(GINT_CALL(BFile_Open, FILENAME, BFile_ReadOnly));
    if(handle >= 0)
    {
        int size = gint_world_switch(GINT_CALL(BFile_Size, handle));
        gint_world_switch(GINT_CALL(BFile_Read, handle, &ud, size, 0)); 
		gint_world_switch(GINT_CALL(BFile_Close, handle));
	}
}


void data_use::update()
{
    gint_world_switch(GINT_CALL(BFile_Remove, FILENAME));
    gint_world_switch(GINT_CALL(BFile_Create, FILENAME, BFile_File, &USER_DATA_SIZE));
    int handle = gint_world_switch(GINT_CALL(BFile_Open, FILENAME, BFile_WriteOnly));
    gint_world_switch(GINT_CALL(BFile_Write, handle, &ud, USER_DATA_SIZE)); 
    gint_world_switch(GINT_CALL(BFile_Close, handle));
    return ;
}


