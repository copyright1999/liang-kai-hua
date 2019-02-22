#include "can2.h"

/*----CAN2_TX-----PB13----*/
/*----CAN2_RX-----PB12----*/





/**
  * @brief  CAN2��ʼ��
  * @param  void
  * @retval void
  */
void CAN2_Init(void)
{
    CAN_InitTypeDef        can;
    CAN_FilterInitTypeDef  can_filter;
    GPIO_InitTypeDef       gpio;
    NVIC_InitTypeDef       nvic;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_CAN2);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_CAN2); 

    gpio.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 ;
    gpio.GPIO_Mode = GPIO_Mode_AF;
    GPIO_Init(GPIOB, &gpio);

    nvic.NVIC_IRQChannel = CAN2_RX0_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 1;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);
		
		nvic.NVIC_IRQChannel = CAN2_TX_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 1;
    nvic.NVIC_IRQChannelSubPriority = 1;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic); 

    CAN_DeInit(CAN2);
    CAN_StructInit(&can);

    can.CAN_TTCM = DISABLE;
    can.CAN_ABOM = DISABLE;    
    can.CAN_AWUM = DISABLE;    
    can.CAN_NART = DISABLE;    
    can.CAN_RFLM = DISABLE;    
    can.CAN_TXFP = ENABLE;     
    can.CAN_Mode = CAN_Mode_Normal; 
    can.CAN_SJW  = CAN_SJW_1tq;
    can.CAN_BS1 = CAN_BS1_9tq;
    can.CAN_BS2 = CAN_BS2_4tq;
    can.CAN_Prescaler = 3;   //CAN BaudRate 42/(1+9+4)/3=1Mbps
    CAN_Init(CAN2, &can);
    
    can_filter.CAN_FilterNumber=14;
    can_filter.CAN_FilterMode=CAN_FilterMode_IdMask;
    can_filter.CAN_FilterScale=CAN_FilterScale_32bit;
    can_filter.CAN_FilterIdHigh=0x0000;
    can_filter.CAN_FilterIdLow=0x0000;
    can_filter.CAN_FilterMaskIdHigh=0x0000;
    can_filter.CAN_FilterMaskIdLow=0x0000;
    can_filter.CAN_FilterFIFOAssignment=0;//the message which pass the filter save in fifo0 CAN_Filter_FIFO0
    can_filter.CAN_FilterActivation=ENABLE;
    CAN_FilterInit(&can_filter);
    
    CAN_ITConfig(CAN2,CAN_IT_FMP0,ENABLE);    ////FIFO0��Ϣ�Һ��ж�����
		CAN_ITConfig(CAN2,CAN_IT_TME,ENABLE);
} 




/**
  * @brief  CAN2ʧ�ر���
  * @param  
  * @retval void
  */
void CAN2_Send_Message(uint32_t Equipment_ID,int16_t Data0,int16_t Data1,int16_t Data2,int16_t Data3)		
{
		CanTxMsg	tx_message;
		tx_message.StdId = Equipment_ID;					 //ʹ�õı�׼ID
		tx_message.IDE = CAN_ID_STD;				 //��׼ģʽ
		tx_message.RTR = CAN_RTR_DATA;			 //���͵�������
		tx_message.DLC = 0x08;		//���ݳ���Ϊ8�ֽ�
	
		tx_message.Data[0] = Data0>>8; 
	  tx_message.Data[1] = Data0;
	  tx_message.Data[2] = Data1>>8; 
	  tx_message.Data[3] = Data1;
	  tx_message.Data[4] = Data2>>8; 
	  tx_message.Data[5] = Data2;
	  tx_message.Data[6] = Data3>>8; 
	  tx_message.Data[7] = Data3;
		CAN_Transmit(CAN2, &tx_message);
}





/**
  * @brief  CAN2�����ж�
  * @param  void
  * @retval void
  */
void CAN2_RX0_IRQHandler(void)
{
		CanRxMsg RxMessage;
		if (CAN_GetITStatus(CAN2,CAN_IT_FMP0)!= RESET) 
    {				 
				CAN_ClearITPendingBit(CAN2, CAN_IT_FMP0);
				CAN_Receive(CAN2, CAN_FIFO0, &RxMessage);

				if(RxMessage.StdId == 0x207)
				{
					
				}
		}
}


/**
  * @brief  CAN2�����ж�
  * @param  void
  * @retval void
  */
void CAN2_TX_IRQHandler(void)
{
	if (CAN_GetITStatus(CAN2,CAN_IT_TME)!= RESET) 
	{
		CAN_ClearITPendingBit(CAN2,CAN_IT_TME);
	}
}



