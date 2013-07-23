/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "module_motor.h"
/*=====================================================================================================*/
/*=====================================================================================================*
**��� : Motor_Config
**�\�� : �]�wPWM��X�T��
**��J : None
**��X : None
**�ϥ� : Motor_Config();
**=====================================================================================================*/
/*=====================================================================================================*/
void Motor_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
  TIM_OCInitTypeDef TIM_OCInitStruct;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);

  GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_TIM2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM3);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_TIM3);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_TIM3);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM8);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM8);

  /* TIM2 PWM3  PA0 */	/* TIM2 PWM4  PA1 */	/* TIM2 PWM5  PA2 */	/* TIM2 PWM8  PA3 */
  /* TIM3 PWM9  PA6 */	/* TIM3 PWM10 PA7 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  /* TIM3 PWM11 PB0 */	/* TIM3 PWM12 PB1 */	/* TIM4 PWM1  PB6 */	/* TIM4 PWM2  PB7 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStruct);
  /* TIM8 PWM7  PC6 */	/* TIM8 PWM6  PC7 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOC, &GPIO_InitStruct);

  TIM_DeInit(TIM2);
  TIM_DeInit(TIM3);
  TIM_DeInit(TIM4);
  TIM_DeInit(TIM8);

  /************************** PWM Output **************************************/
  /* �]�w TIM2 TIM3 TIM4 Time Base */
  TIM_TimeBaseStruct.TIM_Period = (u16)(2500-1);              // �g�� = 2.5ms, 400Hz
  TIM_TimeBaseStruct.TIM_Prescaler = (u16)(84-1);             // ���W84 = 1M ( 1us )
  TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;		// �W��
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStruct);
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStruct);
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStruct);
  /* �]�wTIM8 Time Base */
  TIM_TimeBaseStruct.TIM_Period = (u16)(2500-1);							// �g�� = 2.5ms, 400kHz
  TIM_TimeBaseStruct.TIM_Prescaler = (u16)(168-1);						// ���W42 = 1M ( 1us )
  TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;		// �W��
  TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStruct);

  /* �]�w TIM2 TIM3 TIM4 TIM8 OC */
  TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;							// �t�m�� PWM1 �Ҧ�
  TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;	// �P�� OC
  TIM_OCInitStruct.TIM_Pulse = PWM_MOTOR_MAX;									// �]�m���ܭ�
  TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;			// ��p�ƭȤp�� PWM_MOTOR_MIN �ɬ����q��
  TIM_OC1Init(TIM2, &TIM_OCInitStruct);												// ��l�� TIM2 OC1
  TIM_OC2Init(TIM2, &TIM_OCInitStruct);												// ��l�� TIM2 OC2
  TIM_OC3Init(TIM2, &TIM_OCInitStruct);												// ��l�� TIM2 OC3
  TIM_OC4Init(TIM2, &TIM_OCInitStruct);												// ��l�� TIM2 OC4
  TIM_OC1Init(TIM3, &TIM_OCInitStruct);												// ��l�� TIM3 OC1
  TIM_OC2Init(TIM3, &TIM_OCInitStruct);												// ��l�� TIM3 OC2
  TIM_OC3Init(TIM3, &TIM_OCInitStruct);												// ��l�� TIM3 OC3
  TIM_OC4Init(TIM3, &TIM_OCInitStruct);												// ��l�� TIM3 OC4
  TIM_OC1Init(TIM4, &TIM_OCInitStruct);												// ��l�� TIM4 OC1
  TIM_OC2Init(TIM4, &TIM_OCInitStruct);												// ��l�� TIM4 OC2
  TIM_OC1Init(TIM8, &TIM_OCInitStruct);												// ��l�� TIM8 OC1
  TIM_OC2Init(TIM8, &TIM_OCInitStruct);												// ��l�� TIM8 OC2
  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);						// �P�� TIM2 OC1 �w�˸�
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);						// �P�� TIM2 OC2 �w�˸�
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);						// �P�� TIM2 OC3 �w�˸�
  TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);						// �P�� TIM2 OC4 �w�˸�
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);						// �P�� TIM3 OC1 �w�˸�
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);						// �P�� TIM3 OC2 �w�˸�
  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);						// �P�� TIM3 OC3 �w�˸�
  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);						// �P�� TIM3 OC4 �w�˸�
  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);						// �P�� TIM4 OC1 �w�˸�
  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);						// �P�� TIM4 OC2 �w�˸�
  TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);						// �P�� TIM8 OC1 �w�˸�
  TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);						// �P�� TIM8 OC2 �w�˸�

  /* �Ұ� */
  TIM_ARRPreloadConfig(TIM2, ENABLE);													// �P�� TIM2 �����H�s��ARR
  TIM_ARRPreloadConfig(TIM3, ENABLE);													// �P�� TIM3 �����H�s��ARR
  TIM_ARRPreloadConfig(TIM4, ENABLE);													// �P�� TIM4 �����H�s��ARR
  TIM_ARRPreloadConfig(TIM8, ENABLE);													// �P�� TIM8 �����H�s��ARR
  TIM_Cmd(TIM2, ENABLE);																			// �P�� TIM2
  TIM_Cmd(TIM3, ENABLE);																			// �P�� TIM3
  TIM_Cmd(TIM4, ENABLE);																			// �P�� TIM4
  TIM_Cmd(TIM8, ENABLE);																			// �P�� TIM8
}
/*=====================================================================================================*/
/*=====================================================================================================*
**��� : Motor_Control
**�\�� : �L�갨�F����
**��J : Motor1, Motor2, Motor3, Motor4
**��X : None
**�ϥ� : Motor_Control( Motor1, Motor2, Motor3, Motor4 );
**=====================================================================================================*/
/*=====================================================================================================*/
void Motor_Control( u16 Motor1, u16 Motor2, u16 Motor3, u16 Motor4 )
{
  if(Motor1>PWM_MOTOR_MAX)  Motor1 = PWM_MOTOR_MAX;
  if(Motor2>PWM_MOTOR_MAX)  Motor2 = PWM_MOTOR_MAX;
  if(Motor3>PWM_MOTOR_MAX)  Motor3 = PWM_MOTOR_MAX;
  if(Motor4>PWM_MOTOR_MAX)  Motor4 = PWM_MOTOR_MAX;
  if(Motor1<PWM_MOTOR_MIN)  Motor1 = PWM_MOTOR_MIN;
  if(Motor2<PWM_MOTOR_MIN)  Motor2 = PWM_MOTOR_MIN;
  if(Motor3<PWM_MOTOR_MIN)  Motor3 = PWM_MOTOR_MIN;
  if(Motor4<PWM_MOTOR_MIN)  Motor4 = PWM_MOTOR_MIN;

  PWM_Motor1 = Motor1;
  PWM_Motor2 = Motor2;
  PWM_Motor3 = Motor3;
  PWM_Motor4 = Motor4;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**��� : Sevro_Control
**�\�� : ���A���F����
**��J : SevroA, SevroB
**��X : None
**�ϥ� : Sevro_Control( SevroA, SevroB );
**=====================================================================================================*/
/*=====================================================================================================*/
void Sevro_Control( u16 SevroA, u16 SevroB )
{
//	if(SevroA>PWM_SEVRO_MAX)	SevroA = PWM_SEVRO_MAX;
//	if(SevroB>PWM_SEVRO_MAX)	SevroB = PWM_SEVRO_MAX;
//	if(SevroA<PWM_SEVRO_MIN)	SevroA = PWM_SEVRO_MIN;
//	if(SevroB<PWM_SEVRO_MIN)	SevroB = PWM_SEVRO_MIN;
//	
//	PWM_SevroA = SevroA;
//	PWM_SevroB = SevroB;
}
/*=====================================================================================================*/
/*=====================================================================================================*/
