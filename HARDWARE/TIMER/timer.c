#include "timer.h"
#include "led.h"
#include "usart.h"

void TIM1_ALL_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB , ENABLE);  //使能GPIO外设时钟 
//1001101011
	//TIM1复用功能重映像
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10; //TIM1_CH1 2 3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15; //TIM1_CH1N 2N 3N  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10);	
	GPIO_ResetBits(GPIOB, GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);        //使能定时器1时钟
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;         
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	/*
	TIM_ClearFlag(TIM1, TIM_FLAG_Update);//清中断标志位
	//TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE); //使能指定的TIM1中断,允许更新中断
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  	   //从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
	//TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;//输出比较
	*/
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//输出使能
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //使能  互补 输出状态

	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//有效电平为高电平  没翻转前为低电平
 
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStructure.TIM_Pulse = 60;  // 移相度数 = 180*CCR/（ARR+1）
	
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
				 
	
	//TIM_Cmd(TIM1, ENABLE);//打开定时器1        
	TIM_CtrlPWMOutputs(TIM1, ENABLE);///////主输出使能

}
void TIM8_ALL_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC , ENABLE);  //使能GPIO外设时钟        
	GPIO_ResetBits(GPIOC, GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);	
	GPIO_ResetBits(GPIOA, GPIO_Pin_7);	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8; //TIM8_CH1 2 3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM8_CH1N
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA



	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1; //TIM8_CH 2N 3N  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);        //使能定时器8时钟
	
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;         
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;//输出比较
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2

	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//输出使能
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //使能  互补 输出状态

	TIM_OCInitStructure.TIM_Pulse = 80;//设置比较值（跳变值）        
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//有效电平为高电平  没翻转前为低电平        
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);//初始化输出比较寄存器
	TIM_OC1PreloadConfig(TIM8,TIM_OCPreload_Enable);//禁止预转载
	
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);//初始化输出比较寄存器
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);//禁止预转载
	
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);//初始化输出比较寄存器
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);//禁止预转载
	

	TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable);//主从模式MSM
	TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Enable);//Tim1使能输出作为触发信号        
	TIM_SelectMasterSlaveMode(TIM8, TIM_MasterSlaveMode_Enable);//主从模式MSM
	TIM_SelectInputTrigger(TIM8, TIM_TS_ITR0);//触发选择,ITR0即TIM1
	TIM_SelectSlaveMode(TIM8, TIM_SlaveMode_Trigger);//触发模式只启动;门模式起停都控制
 
		
	TIM_CtrlPWMOutputs(TIM8, ENABLE);///////主输出使能
}

void TIM2_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器
	
	
  TIM_SelectMasterSlaveMode(TIM8, TIM_MasterSlaveMode_Enable);//主从模式MSM
	TIM_SelectOutputTrigger(TIM8, TIM_TRGOSource_Enable);//Tim8使能输出作为触发信号        
	TIM_SelectMasterSlaveMode(TIM2, TIM_MasterSlaveMode_Enable);//主从模式MSM
	TIM_SelectInputTrigger(TIM2, TIM_TS_ITR1);//触发选择,ITR0即TIM1
	TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Trigger);//触发模式只启动;门模式起停都控制
 
		
	TIM_CtrlPWMOutputs(TIM2, ENABLE);///////主输出使能
 		 //HSE_VALUE
}


