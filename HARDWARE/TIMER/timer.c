#include "timer.h"
#include "led.h"
#include "usart.h"

void TIM1_ALL_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB , ENABLE);  //ʹ��GPIO����ʱ�� 
//1001101011
	//TIM1���ù�����ӳ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10; //TIM1_CH1 2 3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15; //TIM1_CH1N 2N 3N  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10);	
	GPIO_ResetBits(GPIOB, GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);        //ʹ�ܶ�ʱ��1ʱ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;         
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	/*
	TIM_ClearFlag(TIM1, TIM_FLAG_Update);//���жϱ�־λ
	//TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE); //ʹ��ָ����TIM1�ж�,��������ж�
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  	   //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
	//TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;//����Ƚ�
	*/
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//���ʹ��
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //ʹ��  ���� ���״̬

	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//��Ч��ƽΪ�ߵ�ƽ  û��תǰΪ�͵�ƽ
 
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStructure.TIM_Pulse = 60;  // ������� = 180*CCR/��ARR+1��
	
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
				 
	
	//TIM_Cmd(TIM1, ENABLE);//�򿪶�ʱ��1        
	TIM_CtrlPWMOutputs(TIM1, ENABLE);///////�����ʹ��

}
void TIM8_ALL_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC , ENABLE);  //ʹ��GPIO����ʱ��        
	GPIO_ResetBits(GPIOC, GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);	
	GPIO_ResetBits(GPIOA, GPIO_Pin_7);	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8; //TIM8_CH1 2 3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM8_CH1N
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA



	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1; //TIM8_CH 2N 3N  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);        //ʹ�ܶ�ʱ��8ʱ��
	
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;         
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;//����Ƚ�
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2

	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//���ʹ��
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //ʹ��  ���� ���״̬

	TIM_OCInitStructure.TIM_Pulse = 80;//���ñȽ�ֵ������ֵ��        
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//��Ч��ƽΪ�ߵ�ƽ  û��תǰΪ�͵�ƽ        
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);//��ʼ������ȽϼĴ���
	TIM_OC1PreloadConfig(TIM8,TIM_OCPreload_Enable);//��ֹԤת��
	
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);//��ʼ������ȽϼĴ���
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);//��ֹԤת��
	
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);//��ʼ������ȽϼĴ���
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);//��ֹԤת��
	

	TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable);//����ģʽMSM
	TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Enable);//Tim1ʹ�������Ϊ�����ź�        
	TIM_SelectMasterSlaveMode(TIM8, TIM_MasterSlaveMode_Enable);//����ģʽMSM
	TIM_SelectInputTrigger(TIM8, TIM_TS_ITR0);//����ѡ��,ITR0��TIM1
	TIM_SelectSlaveMode(TIM8, TIM_SlaveMode_Trigger);//����ģʽֻ����;��ģʽ��ͣ������
 
		
	TIM_CtrlPWMOutputs(TIM8, ENABLE);///////�����ʹ��
}

void TIM2_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���
	
	
  TIM_SelectMasterSlaveMode(TIM8, TIM_MasterSlaveMode_Enable);//����ģʽMSM
	TIM_SelectOutputTrigger(TIM8, TIM_TRGOSource_Enable);//Tim8ʹ�������Ϊ�����ź�        
	TIM_SelectMasterSlaveMode(TIM2, TIM_MasterSlaveMode_Enable);//����ģʽMSM
	TIM_SelectInputTrigger(TIM2, TIM_TS_ITR1);//����ѡ��,ITR0��TIM1
	TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Trigger);//����ģʽֻ����;��ģʽ��ͣ������
 
		
	TIM_CtrlPWMOutputs(TIM2, ENABLE);///////�����ʹ��
 		 //HSE_VALUE
}


