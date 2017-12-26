#include "sys.h"
#include "usart.h"	  
///////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 0
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART3->SR&0X40)==0);//ѭ������,ֱ���������   
    USART3->DR = (u8) ch;
}
#endif 


void uart_init(u32 bordrate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_instructure;
	 
    /******************ʱ�ӳ�ʼ��**********************/	
	/* �� GPIO ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC,ENABLE);
	/* �� UART ʱ�� */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
    
    /******************���ų�ʼ��**********************/
	/* ���� USART  IO */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;  		 //����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	//��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;			// ����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure); 

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    USART3_RX;
    
    /******************���ڳ�ʼ��**********************/
    USART_DeInit(USART3);			   //�������踴λ

	USART_instructure.USART_BaudRate=bordrate;												  //������������
	USART_instructure.USART_WordLength=USART_WordLength_8b;
	USART_instructure.USART_StopBits=USART_StopBits_1;
	USART_instructure.USART_Parity=USART_Parity_No;
	USART_instructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_instructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    
	USART_Init(USART3,&USART_instructure);

    USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ���3 
}

/**
  * @brief  Print a character on the HyperTerminal
  * @param  c: The character to be printed
  * @retval None
  */
void SerialPutChar(uint8_t c)
{    
  USART3_TX;
    
  USART_SendData(USART3, c);  
  while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
  {}
       
  USART3_RX;
}

/**
  * @brief  Print a string on the HyperTerminal
  * @param  s: The string to be printed
  * @retval None
  */
void Serial_PutString(uint8_t *s)
{    
  while (*s != '\0')
  {
    SerialPutChar(*s);
    s++;
  }
}
