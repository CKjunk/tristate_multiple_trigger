#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "exti.h"
#include "sequence.h"

#define PWM_PERIOD 10  //实际周期为PWM_PERIOD
#define PWM1_LOW_TIME 2 
#define PWM2_LOW_TIME 6
/*
  高级定时器1 选择通道1/2/3  PA8/9/10
						  对应的互补通道为 PB13 PB14 PB15
	高级定时器8 选择通道1/2/3  PC6/7/8
						  对应的互补通道为 PA7 PB0 PB1
  定时器1主，定时器8从
	定时器1->定时器8->定时器2
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
		uart_init(115200);	 //串口初始化为115200	https://www.codeleading.com/article/37512487974/
		//pfour = FourOrder_Sequence(array_four,pfour);
		for(i = 0;i < 15;i++){
		    printf("%d ",array[i]);
		
		}
		EXTIX_Init();	 
		delay_init();	    	 //延时函数初始化	  
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
		LED_Init();	
		KEY_Init();	 
		while(1)
		{
			if(count==15){
					count = 0;
			}// printf("%d ",count);
		}

}

void TIM2_IRQHandler(void) //TIM2 中断
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
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); //清除 TIM2 更新中断标志
}
//外部中断0服务程序 中断线以及中断初始化配置 上升沿触发 PA0  WK_UP
//LED.c中的GPIOA.0先要拉低
void EXTI0_IRQHandler(void)
{
  
  TIM1_ALL_Init(PWM_PERIOD-1,71,PWM1_LOW_TIME);
	
	TIM8_ALL_Init(PWM_PERIOD-1,71,PWM2_LOW_TIME);
	
  TIM2_Int_Init(PWM_PERIOD-1,71);
	TIM_Cmd(TIM1, ENABLE);
	EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位 
		
}
 
//外部中断4服务程序
void EXTI4_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(KEY0==1)	 //按键KEY0
	{
		LED0=!LED0;
	}		 
	EXTI_ClearITPendingBit(EXTI_Line4);  //清除LINE4上的中断标志位  
}