#include	<windows.h>
#include	<stdio.h>
#include	"le.h"

extern	HANDLE	NonOverWriteCreateFile(LPCSTR);
		void	decode_g4b2bmp(unsigned char *,char *);
extern	void	decode_palette_4bit(unsigned char *);
extern	void	decode_ps2_d4t(unsigned char *,unsigned long,unsigned long);



void	decode_g4b2bmp(
	unsigned char		*src,
	char				*name	)
{	unsigned char		*pal=src+0x70;
	unsigned long		px=*(unsigned long *)(src+0x40);
	unsigned long		py=*(unsigned long *)(src+0x44);
	unsigned long		sx=*(unsigned long *)(src+0x70+px*py*4+0x40);
	unsigned long		sy=*(unsigned long *)(src+0x70+px*py*4+0x44);
	unsigned char		*gdh=src+0x70+px*py*4;
	unsigned char		*gdt=src+0x70+px*py*4+0x70;
	unsigned char		*gdp;
	unsigned long		cp,cx,cy,cz;	//counter
	unsigned long		tl;				//tmp

	char				tfn[0x100];
	HANDLE				hbmp;
	unsigned char		*bmp;
	BITMAPFILEHEADER	bf;
	BITMAPINFOHEADER	bi;

	switch(*(gdh+1)){				//graphics data header check
		case	0x02:				//encrypt
			break;
		case	0x10:				//tile
		case	0x04:				//tile
		case	0x08:				//tile
		case	0x01:				//tile
			sx*=2;	sy*=4;
printf("sx/sy = %08X/%08X\n",sx,sy);
printf("px/py = %08X/%08X\n",px,py);

			sprintf(tfn,"%s.bmp",name);
			hbmp=NonOverWriteCreateFile((LPCSTR)tfn);
			if(hbmp==(HANDLE)-1){
				printf("\tError\tcan't create bmp file\n");
				exit(-1);									}

			memset(&bf,0x00,sizeof(BITMAPFILEHEADER));
			memset(&bi,0x00,sizeof(BITMAPINFOHEADER));

			*((char *)&bf.bfType+0)='B';
			*((char *)&bf.bfType+1)='M';
			bf.bfSize=			sizeof(BITMAPFILEHEADER)+
								sizeof(BITMAPINFOHEADER)+
								sx*sy*4;							//image
			bf.bfOffBits=		sizeof(BITMAPFILEHEADER)+
								sizeof(BITMAPINFOHEADER);
			bi.biSize=			sizeof(BITMAPINFOHEADER);
			bi.biWidth=			sx;
			bi.biHeight=		sy;
			bi.biPlanes=		1;
			bi.biBitCount=		32;
			WriteFile(hbmp,&bf,sizeof(BITMAPFILEHEADER),&tl,NULL);
			WriteFile(hbmp,&bi,sizeof(BITMAPINFOHEADER),&tl,NULL);

			for(cx=0;cx<(px*py*4);cx+=4){						//pal•ÏŠ·
				tl			=ler4(pal+cx);
				*(pal+cx+0)	=(unsigned char)(tl>> 8);		//B
				*(pal+cx+1)	=(unsigned char)(tl>>16);		//G
				*(pal+cx+2)	=(unsigned char)(tl>>24);		//R
				*(pal+cx+3)	=(unsigned char)(tl>> 0);	}	//X
//			decode_palette_4bit(pal);						//ps2 pal•ÏŠ·

			bmp=new unsigned char[sx*sy*4];
			for(cp=0;cp<(sx*sy/2);cp++){					//pal > rgb
				memcpy(bmp+cp*8+0,pal+(*(gdt+cp)>>4)*4,4);
				memcpy(bmp+cp*8+4,pal+(*(gdt+cp)&15)*4,4);	}
//				memset(bmp+cp*8+0,(*(gdt+cp)>>4)<<4,4);
//				memset(bmp+cp*8+4,(*(gdt+cp)&15)<<4,4);	}

			decode_ps2_d4t(bmp,sx,sy);

			for(cy=sy;cy>0;cy--)
				WriteFile(hbmp,bmp+(cy-1)*sx*4,sx*4,&tl,NULL);

			CloseHandle(hbmp);
			delete[]	bmp;
			break;



		case	0x00:										//non tile
			sprintf(tfn,"%s.bmp",name);
			hbmp=NonOverWriteCreateFile((LPCSTR)tfn);
			if(hbmp==(HANDLE)-1){
				printf("\tError\tcan't create bmp file\n");
				exit(-1);									}

			memset(&bf,0x00,sizeof(BITMAPFILEHEADER));
			memset(&bi,0x00,sizeof(BITMAPINFOHEADER));

			*((char *)&bf.bfType+0)='B';
			*((char *)&bf.bfType+1)='M';
			bf.bfSize=			sizeof(BITMAPFILEHEADER)+
								sizeof(BITMAPINFOHEADER)+
								sx*sy*8;								//image
			bf.bfOffBits=		sizeof(BITMAPFILEHEADER)+
								sizeof(BITMAPINFOHEADER);
			bi.biSize=			sizeof(BITMAPINFOHEADER);
			bi.biWidth=			sx;
			bi.biHeight=		sy;
			bi.biPlanes=		1;
			bi.biBitCount=		32;
			WriteFile(hbmp,&bf,sizeof(BITMAPFILEHEADER),&tl,NULL);
			WriteFile(hbmp,&bi,sizeof(BITMAPINFOHEADER),&tl,NULL);

			for(cx=0;cx<(px*py*4);cx+=4){						//pal•ÏŠ·
				tl			=ler4(pal+cx);
				*(pal+cx+0)	=(unsigned char)(tl>> 8);		//B
				*(pal+cx+1)	=(unsigned char)(tl>>16);		//G
				*(pal+cx+2)	=(unsigned char)(tl>>24);		//R
				*(pal+cx+3)	=(unsigned char)(tl>> 0);	}	//X
			decode_palette_4bit(pal);						//ps2 pal•ÏŠ·

			bmp=new unsigned char[sx*sy*4];
			for(cp=0;cp<(sx*sy/2);cp++){						//pal > rgb
//				memcpy(bmp+cp*8+0,pal+(*(gdt+cp)>>4)*4,4);
//				memcpy(bmp+cp*8+4,pal+(*(gdt+cp)&15)*4,4);	}
				memset(bmp+cp*8+0,(*(gdt+cp)>>4)<<4,4);
				memset(bmp+cp*8+4,(*(gdt+cp)&15)<<4,4);	}

			for(cy=sy;cy>0;cy--)
				WriteFile(hbmp,bmp+(cy-1)*sx*8,sx*8,&tl,NULL);

			CloseHandle(hbmp);
			delete[]	bmp;
			break;


		default:
			printf("gdh+1=%02X\n",*(gdh+1));
			break;
	}
}
