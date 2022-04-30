#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "exti.h"
#include "sequence.h"

#define PWM_PERIOD 10  //ʵ������ΪPWM_PERIOD
#define PWM1_LOW_TIME 2 
#define PWM2_LOW_TIME 6
/*
  �߼���ʱ��1 ѡ��ͨ��1/2/3  PA8/9/10
						  ��Ӧ�Ļ���ͨ��Ϊ PB13 PB14 PB15
	�߼���ʱ��8 ѡ��ͨ��1/2/3  PC6/7/8
						  ��Ӧ�Ļ���ͨ��Ϊ PA7 PB0 PB1
  ��ʱ��1������ʱ��8��
	��ʱ��1->��ʱ��8->��ʱ��2
*/
FOUR four = {0,NULL};
FOUR* pfour = &four;
/*SIX six = {0,NULL};
SIX* psix = &six;
EIGHT eight = {0,NULL};
EIGHT* peight = &eight;
TEN ten = {0,NULL};
TEN* pten = &ten;
TWELVE twelve = {0,NULL};
TWELVE* ptwelve = &twelve;
THIRTEEN thirteen = {0,NULL};
THIRTEEN* pthirteen = &thirteen;
*/
int array[15]={1 ,1 ,0 ,0 ,0 ,1, 0 ,0, 1 ,1 ,0 ,1 ,0, 1 ,1 };
static int count = 0;
int main(void)
{		
	  int array_four[4] = {0,0,1,1};
		/*
		int array_six[6] = {0,0,0,0,1,1};
		int array_eight[8] = {0,0,0,1,1,1,0,1};
		int array_ten[10] = {0,0,0,0,0,0,1,0,0,1};
		int array_twelve[12] = {0,0,0,0,0,1,0,1,0,0,1,1};
		int array_thirteen[13] = {0,0,0,0,0,0,0,0,1,1,0,1,1};
		*/
		int i = 0;
  //psix = SixOrder_Sequence(array_six,psix);
	//peight = EightOrder_Sequence(array_eight,peight);
	//pten = TenOrder_Sequence(array_ten,pten);
	//ptwelve = TwelveOrder_Sequence(array_twelve,ptwelve);
	//pthirteen = ThirteenOrder_Sequence(array_thirteen,pthirteen);
		uart_init(115200);	 //���ڳ�ʼ��Ϊ115200	https://www.codeleading.com/article/37512487974/
		//pfour = FourOrder_Sequence(array_four,pfour);
		for(i = 0;i < 15;i++){
		    printf("%d ",array[i]);
		
		}
		EXTIX_Init();	 
		delay_init();	    	 //��ʱ������ʼ��	  
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
		LED_Init();	
		KEY_Init();	 
		while(1)
		{
			if(count==15){
					count = 0;
			}// printf("%d ",count);
		}

}

void TIM2_IRQHandler(void) //TIM2 �ж�
{
		if(array[count]==1){
			TIM1->CCR1 = PWM1_LOW_TIME;
			TIM8->CCR1 = PWM2_LOW_TIME;
		}
		else{
			TIM1->CCR1 = PWM_PERIOD;
			TIM8->CCR1 = PWM_PERIOD;
		}
		count++; 
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); //��� TIM2 �����жϱ�־
}
//�ⲿ�ж�0������� �ж����Լ��жϳ�ʼ������ �����ش��� PA0  WK_UP
//LED.c�е�GPIOA.0��Ҫ����
void EXTI0_IRQHandler(void)
{
  
  TIM1_ALL_Init(PWM_PERIOD-1,71,PWM1_LOW_TIME);
	
	TIM8_ALL_Init(PWM_PERIOD-1,71,PWM2_LOW_TIME);
	
  TIM2_Int_Init(PWM_PERIOD-1,71);
	TIM_Cmd(TIM1, ENABLE);
	EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ 
		
}
 
//�ⲿ�ж�4�������
void EXTI4_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY0==1)	 //����KEY0
	{
		LED0=!LED0;
	}		 
	EXTI_ClearITPendingBit(EXTI_Line4);  //���LINE4�ϵ��жϱ�־λ  
}