/******************************************************************************
	PS2 4bit tile decoding
******************************************************************************/
#include	<windows.h>
#include	<stdio.h>



void	decode_ps2_d4t(
	unsigned char		*src,
	unsigned long		sx,
	unsigned long		sy		)
{	unsigned long		sz=sx*sy;
	unsigned long		cx,cy,cz;
	unsigned char		*ba;
	unsigned char		*bb;

	ba=new unsigned char[sx*sy*4];
	bb=new unsigned char[sx*sy*4];
	memset(ba,0x00,sx*sy*4);
	memcpy(bb,src ,sx*sy*4);

	for(cy=0;cy<sy;cy++){
		for(cx=0;cx<sx;cx+=64){
			for(cz=0;cz<8;cz++){
	memcpy(ba+(cy*sx+cx+cz*8+0)*4,bb+(cy*sx+cx+0*8+cz)*4,4);
	memcpy(ba+(cy*sx+cx+cz*8+1)*4,bb+(cy*sx+cx+1*8+cz)*4,4);
	memcpy(ba+(cy*sx+cx+cz*8+2)*4,bb+(cy*sx+cx+2*8+cz)*4,4);
	memcpy(ba+(cy*sx+cx+cz*8+3)*4,bb+(cy*sx+cx+3*8+cz)*4,4);
	memcpy(ba+(cy*sx+cx+cz*8+4)*4,bb+(cy*sx+cx+4*8+cz)*4,4);
	memcpy(ba+(cy*sx+cx+cz*8+5)*4,bb+(cy*sx+cx+5*8+cz)*4,4);
	memcpy(ba+(cy*sx+cx+cz*8+6)*4,bb+(cy*sx+cx+6*8+cz)*4,4);
	memcpy(ba+(cy*sx+cx+cz*8+7)*4,bb+(cy*sx+cx+7*8+cz)*4,4);
	}	}	}

/*	for(cx=0;cx<sz;cx+=sx*8){
	memcpy(bb+(cx+sx*0)*4,ba+(cx+sx*0)*4,sx*4);
	memcpy(bb+(cx+sx*1)*4,ba+(cx+sx*2)*4,sx*4);
	memcpy(bb+(cx+sx*2)*4,ba+(cx+sx*1)*4,sx*4);
	memcpy(bb+(cx+sx*3)*4,ba+(cx+sx*3)*4,sx*4);

	memcpy(bb+(cx+sx*4)*4,ba+(cx+sx*5)*4,sx*4);
	memcpy(bb+(cx+sx*5)*4,ba+(cx+sx*7)*4,sx*4);
	memcpy(bb+(cx+sx*6)*4,ba+(cx+sx*4)*4,sx*4);
	memcpy(bb+(cx+sx*7)*4,ba+(cx+sx*6)*4,sx*4);
	}

/*
	for(cy=0;cy<sy;cy+=4){
		for(cx=0;cx<sx;cx+=32){
			for(cz=0;cz<4;cz++){
	memcpy(ba+((cy+cz)*sx+(cx+ 0))*4,bb+((cy+0)*sx+(cx+cz*8))*4,32);
	memcpy(ba+((cy+cz)*sx+(cx+ 8))*4,bb+((cy+1)*sx+(cx+cz*8))*4,32);
	memcpy(ba+((cy+cz)*sx+(cx+16))*4,bb+((cy+2)*sx+(cx+cz*8))*4,32);
	memcpy(ba+((cy+cz)*sx+(cx+24))*4,bb+((cy+3)*sx+(cx+cz*8))*4,32);
	}	}	}

	for(cy=0;cy<sy;cy++){
		for(cx=0;cx<sx;cx+=64){
			for(cz=0;cz<32;cz++){
	memcpy(bb+(cy*sx+cx+cz*2+0)*4,ba+(cy*sx+cx+cz+ 0)*4,4);
	memcpy(bb+(cy*sx+cx+cz*2+1)*4,ba+(cy*sx+cx+cz+32)*4,4);
	}	}	}

	for(cy=0;cy<sy;cy++){
		for(cx=0;cx<sx;cx+=4){
	memcpy(ba+(cy*sx+cx+0)*4,bb+(cy*sx+cx+2)*4,4);
	memcpy(ba+(cy*sx+cx+1)*4,bb+(cy*sx+cx+3)*4,4);
	memcpy(ba+(cy*sx+cx+2)*4,bb+(cy*sx+cx+1)*4,4);
	memcpy(ba+(cy*sx+cx+3)*4,bb+(cy*sx+cx+4)*4,4);
	}	}


	for(cy=0;cy<sy;cy+=4){
		for(cx=0;cx<sx;cx+=32){
			for(cz=0;cz<4;cz++){
	memcpy(ba+((cy+cz)*sx+(cx+ 0))*4,bb+((cy+0)*sx+(cx+cz*4))*4,16);
	memcpy(ba+((cy+cz)*sx+(cx+ 4))*4,bb+((cy+1)*sx+(cx+cz*4))*4,16);
	memcpy(ba+((cy+cz)*sx+(cx+ 8))*4,bb+((cy+2)*sx+(cx+cz*4))*4,16);
	memcpy(ba+((cy+cz)*sx+(cx+12))*4,bb+((cy+3)*sx+(cx+cz*4))*4,16);
	}	}	}

	for(cy=0;cy<sy;cy+=4){
		for(cx=0;cx<sx;cx+=16){
			for(cz=0;cz<4;cz++){
	memcpy(ba+((cy+cz)*sx+(cx+ 0))*4,bb+((cy+0)*sx+(cx+cz*4))*4,16);
	memcpy(ba+((cy+cz)*sx+(cx+ 4))*4,bb+((cy+1)*sx+(cx+cz*4))*4,16);
	memcpy(ba+((cy+cz)*sx+(cx+ 8))*4,bb+((cy+2)*sx+(cx+cz*4))*4,16);
	memcpy(ba+((cy+cz)*sx+(cx+12))*4,bb+((cy+3)*sx+(cx+cz*4))*4,16);
	}	}	}

	for(cy=0;cy<sy;cy++){
		for(cx=0;cx<sx;cx+=64){
			for(cz=0;cz<16;cz++){
	memcpy(bb+(cy*sx+(cx+4*cz+0))*4,ba+(cy*sx+(cx+cz+16*0))*4,4);
	memcpy(bb+(cy*sx+(cx+4*cz+1))*4,ba+(cy*sx+(cx+cz+16*1))*4,4);
	memcpy(bb+(cy*sx+(cx+4*cz+2))*4,ba+(cy*sx+(cx+cz+16*2))*4,4);
	memcpy(bb+(cy*sx+(cx+4*cz+3))*4,ba+(cy*sx+(cx+cz+16*3))*4,4);
	}	}	}

	for(cy=0;cy<sy;cy++){
		for(cx=0;cx<sx;cx+=64){
	memcpy(ba+(cy*sx+cx+ 0)*4,bb+(cy*sx+cx+ 0)*4,64);
	memcpy(ba+(cy*sx+cx+16)*4,bb+(cy*sx+cx+32)*4,64);
	memcpy(ba+(cy*sx+cx+32)*4,bb+(cy*sx+cx+16)*4,64);
	memcpy(ba+(cy*sx+cx+48)*4,bb+(cy*sx+cx+48)*4,64);
	}	}
*/


		memcpy(src,ba,sx*sy*4);

	delete[]	ba;
	delete[]	bb;
}
