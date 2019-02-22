#include "system.h"

extern int SystemMode;
static volatile uint32_t usTicks = 0;
extern int16_t Angle_Target;

uint32_t currentTime = 0;
uint32_t loopTime_1ms=0;
uint32_t previousTime = 0;
uint16_t cycleTime = 0; 



short gyrox,gyroy,gyroz;	//������ԭʼ����
float pitch,roll,yaw,yaw_10;		//ŷ����
	
//�޷�
float constrain(float amt, float low, float high)
{
	if (amt < low)
		return low;
	else if (amt > high)
		return high;
	else
		return amt;
}
int32_t constrain_int32(int32_t amt, int32_t low, int32_t high)
{
	if (amt < low)
		return low;
	else if (amt > high)
		return high;
	else
		return amt;
}

int16_t constrain_int16(int16_t amt, int16_t low, int16_t high)
{
	if (amt < low)
		return low;
	else if (amt > high)
		return high;
	else
		return amt;
}

int constrain_int(int amt,int low,int high)
{
	if (amt < low)
		return low;
	else if (amt > high)
		return high;
	else
		return amt;
}

//��������ʼ��
static void cycleCounterInit(void)
{
	RCC_ClocksTypeDef clocks;
	RCC_GetClocksFreq(&clocks);
	usTicks = clocks.SYSCLK_Frequency / 1000000; 
}

//��΢��Ϊ��λ����ϵͳʱ��
uint32_t micros(void)
{
	register uint32_t ms, cycle_cnt;
	do {
			ms = sysTickUptime;
			cycle_cnt = SysTick->VAL;
	} while (ms != sysTickUptime);
	return (ms * 1000) + (usTicks * 1000 - cycle_cnt) / usTicks;
}

//΢�뼶��ʱ
void delay_us(uint32_t us)
{
	uint32_t now = micros();
	while (micros() - now < us);
}

//���뼶��ʱ
void delay_ms(uint32_t ms)
{
	while (ms--)
			delay_us(1000);
}

//�Ժ���Ϊ��λ����ϵͳʱ��
uint32_t millis(void)
{
	return sysTickUptime;
}

//ϵͳ��ʼ��
void systemInit(void)
{
	cycleCounterInit();
	SysTick_Config(SystemCoreClock / 1000);	//�δ�ʱ�����ã�1ms
}

//ʧ�ر���
int SystemMonitor=Normal_Mode;
void Stop()
{
		
}


//������ʼ��
void Parameter_Init(void)
{      
	
}


//ϵͳ��ʼ��
int pass_num;
bool pass_flag=1;
void System_Init(void)
{	
	static uint32_t loopTime_mpu6050 = 0;
	CRC_init();	
	cycleCounterInit();
	SysTick_Config(SystemCoreClock / 1000);
	
	A_GPIO_Init(GPIOB,GPIO_Pin_9);
	delay_ms(1000);
	
	
	Parameter_Init();
	usart2_Init();
	Led_Init();
	MPU_Init();
	while(mpu_dmp_init())//ע���Լ캯��
	{
		currentTime = micros();//��ȡ��ǰϵͳʱ��	
		if((int32_t)(currentTime - loopTime_mpu6050) >= 100000)  
		{	
			loopTime_mpu6050 = currentTime + 100000;			//100ms
			pass_num++;
			if(pass_num>=3)//����ʱ �������Լ캯��
			{
				pass_flag=0;
				pass_num=10;
			}
		}
	}
}

uint8_t hahaha=0;
//��ѭ��
void Loop(void)
{	
	static uint32_t currentTime = 0;
	static uint32_t loopTime_1ms = 0;
	static uint32_t loopTime_2ms = 0;
	
	currentTime = micros();	//��ȡ��ǰϵͳʱ��
	
	if((int32_t)(currentTime - loopTime_1ms) >= 0)  
	{	
		loopTime_1ms = currentTime + 1000;	//1ms	
    Get_SystemMode();			
		MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//��ȡ���ٶ�
		mpu_dmp_get_data(&roll,&pitch,&yaw);		//��ȡŷ����
		
	}
	
	if((int32_t)(currentTime - loopTime_2ms) >= 0)
	{
		loopTime_2ms = currentTime + 1000000;//2ms

		if(hahaha  == 0)
		{
			BlueOne_Flow_ArrowHead_Light(GPIOB,GPIO_Pin_9);
		}
		else if(hahaha == 1)
		{
			BlueTwo_Flow_ArrowHead_Light(GPIOB,GPIO_Pin_9);
		}
			else if(hahaha == 2)
		{
			BlueThree_Flow_ArrowHead_Light(GPIOB,GPIO_Pin_9);
		}
		else if(hahaha == 3)
		{
			BlueFour_Flow_ArrowHead_Light(GPIOB,GPIO_Pin_9);
		}
		

		hahaha ++;

	}	
}









