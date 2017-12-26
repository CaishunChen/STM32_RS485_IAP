#ifndef __IAP_H__
#define __IAP_H__
#include "sys.h"  

typedef  void (*iapfun)(void);				//����һ���������͵Ĳ���.

#define FLASH_APP_Info_ADDR		0X0800FC00      //APP���Է�������ַ
#define FLASH_APP_ADDR		    0x08010000  	//��һ��Ӧ�ó�����ʼ��ַ(�����FLASH)
#define APPLICATION_ADDRESS	FLASH_APP_ADDR									//����0X08000000~0X0800FFFF�Ŀռ�ΪIAPʹ��

#define USER_FLASH_LAST_PAGE_ADDRESS  0x0800F800
#define USER_FLASH_END_ADDRESS        0x08040000 /* 64 KBytes */
/* define the user application size */
#define USER_FLASH_SIZE   (USER_FLASH_END_ADDRESS - APPLICATION_ADDRESS + 1)


void iap_load_app(u32 appxaddr);			//ִ��flash�����app����
void iap_load_appsram(u32 appxaddr);		//ִ��sram�����app����
void iap_write_appbin(u32 appxaddr,u8 *appbuf,u32 applen);	//��ָ����ַ��ʼ,д��bin
#endif







































