/**
  *      __            ____
  *     / /__ _  __   / __/                      __  
  *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
  *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
  *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
  *                    /_/   github.com/KitSprout    
  * 
  * @file    stm32f4xx_bsp.c
  * @author  KitSprout
  * @date    16-Mar-2017
  * @brief   
  * 
  */

/* Includes --------------------------------------------------------------------------------*/
#include "drivers\stm32f4_system.h"
#include "modules\serial.h"
#include "modules\kSerial.h"
#include "modules\imu.h"
#include "algorithms\ahrs.h"
#include "stm32f4xx_bsp.h"

/** @addtogroup STM32_Program
  * @{
  */

/* Private typedef -------------------------------------------------------------------------*/
/* Private define --------------------------------------------------------------------------*/
/* Private macro ---------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------*/
extern ahrs_t ahrs;

/* Private function prototypes -------------------------------------------------------------*/
/* Private functions -----------------------------------------------------------------------*/

void BSP_GPIO_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* Enable all GPIO Clk *******************************************************/
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /* GPIO all analog input *****************************************************/
  GPIO_InitStruct.Mode  = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  GPIO_InitStruct.Pin   = GPIO_PIN_All & (~(GPIO_PIN_13 | GPIO_PIN_14));
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* GPIO Pin ******************************************************************/
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;

  GPIO_InitStruct.Pin   = LED_R_PIN;
  HAL_GPIO_Init(LED_R_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin   = LED_G_PIN;
  HAL_GPIO_Init(LED_G_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin   = LED_B_PIN;
  HAL_GPIO_Init(LED_B_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

  GPIO_InitStruct.Pin   = KEY_PIN;
  HAL_GPIO_Init(KEY_GPIO_PORT, &GPIO_InitStruct);

  LED_R_Set();
  LED_G_Set();
  LED_B_Set();
}

void BSP_UART_SERIAL_Config( pFunc rxEvent )
{
  hSerial.rxEventCallback = rxEvent;

  Serial_Config();
  kSerial_Config(SERIAL_UARTx);
  printf("\r\nHello World!\r\n\r\n");
}

void BSP_SPI_IMU_Config( void )
{
  IMU_InitTypeDef IMU_InitStruct;

  IMU_Config();
  delay_ms(50);

  printf("IMU Init ... ");
  IMU_InitStruct.Data                           = &(ahrs.imu);
  IMU_InitStruct.Data->calibState               = DISABLE;
  IMU_InitStruct.InitMPU.MPU_Gyr_FullScale      = MPU_GyrFS_2000dps;
  IMU_InitStruct.InitMPU.MPU_Gyr_LowPassFilter  = MPU_GyrLPS_41Hz;
  IMU_InitStruct.InitMPU.MPU_Acc_FullScale      = MPU_AccFS_4g;
  IMU_InitStruct.InitMPU.MPU_Acc_LowPassFilter  = MPU_AccLPS_41Hz;
  IMU_InitStruct.InitMPU.MPU_Mag_FullScale      = MPU_MagFS_16b;
  if (IMU_Init(&IMU_InitStruct) != SUCCESS) {
    printf("ERROR\r\n");
    while(1) {
      LED_R_Toggle();
      delay_ms(100);
    }
  }
  printf("SUCCESS\r\n\r\n");
  delay_ms(50);
}

void BSP_AHRS_Config( pFunc event, uint32_t sampleRate )
{
  hTimAhrs.EventCallback = event;

  AHRS_Config();
  AHRS_Init(&ahrs);

  AHRS_Cmd(ENABLE);
}

/*************************************** END OF FILE ****************************************/
