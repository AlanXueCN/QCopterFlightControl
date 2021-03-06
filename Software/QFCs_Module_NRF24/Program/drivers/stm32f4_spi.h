/**
  *      __            ____
  *     / /__ _  __   / __/                      __  
  *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
  *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
  *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
  *                    /_/   github.com/KitSprout    
  * 
  * @file    stm32f4_spi.h
  * @author  KitSprout
  * @date    18-Mar-2017
  * @brief   
  * 
  */

/* Define to prevent recursive inclusion ---------------------------------------------------*/
#ifndef __STM32F4_SPI_H
#define __STM32F4_SPI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes --------------------------------------------------------------------------------*/
#include "stm32f4_system.h"

/* Exported types --------------------------------------------------------------------------*/
typedef struct {
  SPI_HandleTypeDef *handle;
  uint16_t txBufLens;
  uint16_t rxBufLens;
  uint8_t *pTxBuf;
  uint8_t *pRxBuf;
  pFunc txEventCallback;
  pFunc rxEventCallback;
} __attribute__((aligned)) SpiHandle_st;

/* Exported constants ----------------------------------------------------------------------*/
/* Exported functions ----------------------------------------------------------------------*/
#if defined(KS_HW_SPI_HAL_LIBRARY)

#define SPI_SendData( _H, _DAT, _LEN, _TIME )           HAL_SPI_Transmit(_H, _DAT, _LEN, _TIME)
#define SPI_RecvData( _H, _DAT, _LEN, _TIME )           HAL_SPI_Receive(_H, _DAT, _LEN, _TIME)
#define SPI_SendRecv( _H, _TDAT, _RDAT, _LEN, _TIME )   HAL_SPI_TransmitReceive(_H, _TDAT, _RDAT, _LEN, _TIME)
#define SPI_SendDataIT( _H, _DAT, _LEN )                HAL_SPI_Transmit_IT(_H, _DAT, _LEN)
#define SPI_RecvDataIT( _H, _DAT, _LEN )                HAL_SPI_Receive_IT(_H, _DAT, _LEN)
#define SPI_SendRecvIT( _H, _TDAT, _RDAT, _LEN )        HAL_SPI_TransmitReceive_IT(_H, _TDAT, _RDAT, _LEN)
#define SPI_SendDataDMA( _H, _DAT, _LEN )               HAL_SPI_Transmit_DMA(_H, _DAT, _LEN)
#define SPI_RecvDataDMA( _H, _DAT, _LEN )               HAL_SPI_Receive_DMA(_H, _DAT, _LEN)
#define SPI_SendRecvDMA( _H, _TDAT, _RDAT, _LEN )       HAL_SPI_TransmitReceive_DMA(_H, _TDAT, _RDAT, _LEN)

#else
int8_t  SPI_SendData( SPI_HandleTypeDef *hspi, uint8_t *sendData, uint16_t lens, uint32_t timeout );
int8_t  SPI_RecvData( SPI_HandleTypeDef *hspi, uint8_t *recvData, uint16_t lens, uint32_t timeout );
int8_t  SPI_SendRecv( SPI_HandleTypeDef *hspi, uint8_t *sendData, uint8_t *recvData, uint16_t lens, uint32_t timeout );
//int8_t  SPI_SendDataIT( SPI_HandleTypeDef *hspi, uint8_t *sendData, uint16_t lens );
//int8_t  SPI_RecvDataIT( SPI_HandleTypeDef *hspi, uint8_t *recvData, uint16_t lens );
//int8_t  SPI_SendDataDMA( SPI_HandleTypeDef *hspi, uint8_t *sendData, uint16_t lens );
//int8_t  SPI_RecvDataDMA( SPI_HandleTypeDef *hspi, uint8_t *recvData, uint16_t lens );

#endif

uint8_t  SPI_RW( SPI_HandleTypeDef *hspi, uint8_t writeByte );
void     SPI_SetSpeed( SPI_HandleTypeDef *hspi, uint8_t speedSel );

extern SpiHandle_st hNrf24;

#ifdef __cplusplus
}
#endif

#endif

/*************************************** END OF FILE ****************************************/
