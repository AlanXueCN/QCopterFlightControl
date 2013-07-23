/* #include "module_nrf24l01.h" */

#ifndef __MODULE_NRF24L01_H
#define __MODULE_NRF24L01_H

#include "stm32f4xx.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
#define nRF_SPI					SPI2	// nRF�ϥ�SPI2

#define SendTimes				2
#define ReadTimes				2
#define TxBufSize				32
#define RxBufSize				32

#define TX_ADR_WIDTH		5  	// �o�g�a�}�e��
#define TX_PLOAD_WIDTH	32  // �o�g�ƾڳq�D���ļƾڼe��0~32Byte

#define RX_ADR_WIDTH		5
#define RX_PLOAD_WIDTH	32

#define CHANAL					40	// �W�D���

// SPI(nRF24L01) commands ,	NRF��SPI�R�O���w�q�A�Ԩ�NRF�\��ϥΤ���
#define NRF_READ			0x00  // Define read command to register
#define NRF_WRITE			0x20  // Define write command to register
#define RD_RX_PLOAD		0x61  // Define RX payload register address
#define WR_TX_PLOAD		0xA0  // Define TX payload register address
#define FLUSH_TX			0xE1  // Define flush TX register command
#define FLUSH_RX			0xE2  // Define flush RX register command
#define REUSE_TX_PL		0xE3  // Define reuse TX payload register command
#define NOP						0xFF  // Define No Operation, might be used to read status register

// SPI(nRF24L01) registers(addresses) �ANRF24L01 �����H�s���a�}�����w�q
#define CONFIG    	  0x00  // 'Config' register address
#define EN_AA       	0x01  // 'Enable Auto Acknowledgment' register address
#define EN_RXADDR   	0x02  // 'Enabled RX addresses' register address
#define SETUP_AW    	0x03  // 'Setup address width' register address
#define SETUP_RETR  	0x04  // 'Setup Auto. Retrans' register address
#define RF_CH       	0x05  // 'RF channel' register address
#define RF_SETUP    	0x06  // 'RF setup' register address
#define STATUS      	0x07  // 'Status' register address
#define OBSERVE_TX  	0x08  // 'Observe TX' register address
#define CD          	0x09  // 'Carrier Detect' register address
#define RX_ADDR_P0  	0x0A  // 'RX address pipe0' register address
#define RX_ADDR_P1  	0x0B  // 'RX address pipe1' register address
#define RX_ADDR_P2  	0x0C  // 'RX address pipe2' register address
#define RX_ADDR_P3  	0x0D  // 'RX address pipe3' register address
#define RX_ADDR_P4  	0x0E  // 'RX address pipe4' register address
#define RX_ADDR_P5  	0x0F  // 'RX address pipe5' register address
#define TX_ADDR     	0x10  // 'TX address' register address
#define RX_PW_P0    	0x11  // 'RX payload width, pipe0' register address
#define RX_PW_P1    	0x12  // 'RX payload width, pipe1' register address
#define RX_PW_P2    	0x13  // 'RX payload width, pipe2' register address
#define RX_PW_P3    	0x14  // 'RX payload width, pipe3' register address
#define RX_PW_P4    	0x15  // 'RX payload width, pipe4' register address
#define RX_PW_P5    	0x16  // 'RX payload width, pipe5' register address
#define FIFO_STATUS 	0x17  // 'FIFO Status Register' register address

#define MAX_RT  			0x10	// �F��̤j���o���Ƥ��_�лx��
#define TX_DS					0x20 	// �o�e�������_�лx��

#define RX_DR					0x40	// ������ƾڤ��_�лx��
/*=====================================================================================================*/
/*=====================================================================================================*/
#define NRF_CSN		PBO(12)		// PB12
#define NRF_CE		PCO(4)		// PC4
#define NRF_IRQ		PCI(5)		// PC5
/*=====================================================================================================*/
/*=====================================================================================================*/
void nRF24L01_Config( void );
void nRF_WriteReg( u8, u8 );
u8 nRF_ReadReg( u8 );
void nRF_WriteBuf( u8, u8*, u8 );
void nRF_ReadBuf( u8, u8*, u8 );
void nRF_RX_Mode( void );
void nRF_TX_Mode( void );
u8 nRF_Check( void );
u8 nRF_Tx_Data( u8* );
u8 nRF_Rx_Data( u8* );
/*====================================================================================================*/
/*====================================================================================================*/
extern u8 TxBuf[SendTimes][TxBufSize];
extern u8 RxBuf[ReadTimes][RxBufSize];
/*====================================================================================================*/
/*====================================================================================================*/
#endif
