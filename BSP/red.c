#include <red.h>

void Red_Equipment_All_Light(GPIO_TypeDef* GPIOx,uint16_t IO)
{

	
uint32_t a[12]={0x00F0F0,0x00F00F,0x000FF0,0x000F0F,0x0000FF,0xFFF000,
		              0xFF0F00,0xFF00F0,0xFF000F,0xFFFFFF,0xFFFF00,0x00FFFF,	};	
	
//uint32_t a[8]={0xF00F00,0x0F00F0,0xF0000F,0x0FF000,0x0F0F00,0x0F00F0,
//		              0x0F000F,0x00FF00	};
//��ɫ �ں� ��ɫ ��ɫ �ں� �ں� �� �ں�
//	uint32_t a[8]={0xF00000,0x0F0000,0x00F000,0x000F00,0x0000F0,0x00000F,
//		              0xFF0000,0xF0F000	};
//��ɫ ��ɫ ��ɫ ��ɫ ��ɫ    ����     ��ɫ ��ɫ	
//	uint32_t a[8]={0xFFF000,0xFFF000,0x0FF00F,0x0FF0F0,0x0FF00F,0x0FF000,
//		              0xFFF000,0xF000FF	};									
//��ɫ  ��ɫ ��ɫ ��ɫ ��ɫ ��ɫ ��ɫ ��ɫ	
									
	uint8_t i,j=0;
	unsigned char byte;
//	for(j=0;j<56;j++)
	for(j=0;j<12;j++)
	{
			for(i=24;i>0;i--)
	   {
					byte = ((a[j]>>i) & 0x01);
					if(byte == 1 )
					{
							Code1_RGB_bulingbuling_RED(GPIOx,IO);
					}
					else
					{
							Code0_RGB_bulingbuling_RED(GPIOx,IO);
					}	
			}

	}
}
