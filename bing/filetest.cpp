#include<gint/bfile.h>
#include<gint/display.h>
#include<gint/gint.h>

#define IS_CH(C) ((C) & 0x80)

static int fh_HZK = 0;

int OpenFont()
{
	fh_HZK = gint_world_switch(GINT_CALL(BFile_Open,u"\\\\fls0\\HZK12.df", BFile_File));
	return fh_HZK;
}

int CloseFont()
{
	gint_world_switch(GINT_CALL(BFile_Close, fh_HZK));;
}

void PrintChChar (unsigned char c1,unsigned char c2,int pX,int pY)
{
	uint8_t mat[12][2];
	int i,j,k;
	int sec,pot; 
	sec = c1-0xa0;
	pot = c2-0xa0;
	gint_world_switch(GINT_CALL(BFile_Read, fh_HZK, mat, 24, (94*(sec-1)+(pot-1))*24l));
    bopti_image_t chara;
    chara.gray = 0;
    chara.profile = 0;
    chara.height = 12;
    chara.width = 12;
    chara.data = mat;
	dimage(pX, pY, chara);
    dupdate();
}

void PrintChStr (unsigned char *cStr,int pX,int pY)
{
	unsigned int key;
	unsigned char c[]=" ";
	while (*cStr)
	{
		if (IS_CH(*cStr))
		{
			unsigned char c1 = *cStr++,
						  c2 = *cStr;
			PrintChChar(c1,c2,pX,pY);
			++cStr;
			pX +=12;
		}
		else
		{
			c[0]=*(cStr++);
			dtext(pX,pY+3,C_BLACK,c);
			pX +=6;
		}
	}
}


测试

