#include	<windows.h>
#include	<stdio.h>

extern	HANDLE	NonOverWriteCreateFile(LPCSTR);
		void	decode_tgs(unsigned char *,unsigned long);
extern	void	decode_g8b2bmp(unsigned char *,char *);
extern	void	decode_g4b2bmp(unsigned char *,char *);



void	decode_tgs(unsigned char *src,unsigned long size)
{
	unsigned long	INB;
	unsigned long	IMX=*(unsigned long*)(src+0x08);
	unsigned long	ITA=*(unsigned long*)(src+0x14);
	unsigned char	*ITP;
	char			INM[0x100];

	for(INB=0;INB!=IMX;INB++){
		ITP=src+*(unsigned long*)(src+ITA+INB*4);
		sprintf(INM,"%08X",*(unsigned long*)(src+ITA+INB*4));

		if(	(*(unsigned long *)(ITP+0x00)==0x10000046)	&&
			(*(unsigned long *)(ITP+0x0c)==0x50000046)		){
			printf("Graphics 8bit palette 0 - %s\n",INM);
			decode_g8b2bmp(ITP,INM);
			goto	item_skip;					}					//8bit-1

		if(	(*(unsigned long *)(ITP+0x00)==0x10000046)	&&
			(*(unsigned long *)(ITP+0x0c)==0x51000046)		){
			printf("Graphics 8bit palette 1 - %s\n",INM);
			decode_g8b2bmp(ITP,INM);
			goto	item_skip;					}					//8bit-2
/*
		if(	(*(unsigned long *)(ITP+0x00)==0x1000000a)	&&
			(*(unsigned long *)(ITP+0x0c)==0x5000000a)		){
			printf("Graphics 4bit palette - %s\n",INM);
			decode_g4b2bmp(ITP,INM);
			goto	item_skip;					}					//4bit-1

		if(	(*(unsigned long *)(ITP+0x00)==0x1000000a)	&&
			(*(unsigned long *)(ITP+0x0c)==0x5100000a)		){
			printf("Graphics 4bit palette - %s\n",INM);
			decode_g4b2bmp(ITP,INM);
			goto	item_skip;					}					//4bit-2
*/
			printf("item skip - %s\n",(char *)INM);
item_skip:
			NULL;
	}
}
