/*
 * bsp_bt.c
 *
 *  Created on: 2017��6��26��
 *      Author: fly
 */

#include "bsp.h"

void Wireless2d4_InitHard(void) {

	//SCK
	clr_P0M1_4;
	set_P0M2_4;

	//CSN
	P3M1 &= ~SET_BIT4;
	P3M2 |= SET_BIT4;

	//TX
	P3M1 &= ~SET_BIT5;
	P3M2 |= SET_BIT5;

}

const uint8_t TX_ADDRESS_DEF[5] = { 0xCC, 0xCC, 0xCC, 0xCC, 0xCC }; //RF ��ַ�����ն˺ͷ��Ͷ���һ��

/******************************************************************************/
//            SPI_init
//               init spi pin  input/out mode
/******************************************************************************/
void SPI_init(void) {
//	GPIO_Init(GPIOB, GPIO_Pin_4, GPIO_Mode_Out_PP_High_Fast); //CSN PIN output High pulling push
//	GPIO_Init(GPIOB, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Fast); //SCK PIN output Low  pulling push
//	GPIO_Init(GPIOB, GPIO_Pin_6, GPIO_Mode_Out_PP_High_Fast); //DATA PIN output  DEFAULT  High pulling push
}

/******************************************************************************/
//           SPI_WW
//                SPI Write a byte for write regiest
/******************************************************************************/
void SPI_WW(uint8_t R_REG) {
	uint8_t i;
	for (i = 0; i < 8; i++) {
		SCK_LOW;
		if (R_REG & 0x80) {
			SPI_DATA_HIGH;
		} else {
			SPI_DATA_LOW;
		}
		R_REG <<= 1;
		nop
		SCK_HIGH;
		nop
		nop
	}
	SCK_LOW;

}

/******************************************************************************/
//            RF_WriteReg
//                Write Data(1 Byte Address ,1 byte data)
/******************************************************************************/
void RF_WriteReg(uint8_t reg, uint8_t wdata) {
	CSN_LOW;
	nop
	SPI_WW(reg);
	SPI_WW(wdata);
	nop
	CSN_HIGH;
}

/******************************************************************************/
//            RF_WriteBuf
//                Write Buffer
/******************************************************************************/
void RF_WriteBuf(uint8_t reg, uint8_t *pBuf, uint8_t length) {
	uint8_t j;
	CSN_LOW;
	j = 0;
	SPI_WW(reg);
	for (j = 0; j < length; j++) {
		SPI_WW(pBuf[j]);
	}
	j = 0;
	CSN_HIGH;
}

/******************************************************************************/
//            SPI_WR
//                SPI Write a byte for read regiset
/******************************************************************************/
void SPI_WR(uint8_t R_REG) {
	uint8_t i;
	for (i = 0; i < 8; i++) {
		SCK_LOW;
		if (R_REG & 0x80) {
			SPI_DATA_HIGH;
		} else {
			SPI_DATA_LOW;
		}
		R_REG <<= 1;
		nop
		SCK_HIGH;
		nop
		nop
	}
	SPI_DATA_INPUT_MODE
	;
	SCK_LOW;

}

/******************************************************************************/
//            ucSPI_Read
//                SPI Read BYTE
/******************************************************************************/
uint8_t ucSPI_Read(void) {
	uint8_t i, dt;
	dt = 0;
	for (i = 0; i < 8; i++) {
		SCK_LOW;
		dt = dt << 1;
		nop
		SCK_HIGH;
		if (SPI_DATA_STATUS) {
			dt |= 0x01;
		}
	}
	SCK_LOW;
	return dt;
}

/******************************************************************************/
//            ucRF_ReadReg
//                Read Data(1 Byte Address ,1 byte data return)
/******************************************************************************/
uint8_t ucRF_ReadReg(uint8_t reg) {
	uint8_t dt;

	CSN_LOW;
	nop
	SPI_WR(reg);
	dt = ucSPI_Read();
	SPI_DATA_OUTPUT_MODE
	;
	nop
	CSN_HIGH;

	return dt;
}

/******************************************************************************/
//            RF_ReadBuf
//                Read Data(1 Byte Address ,length byte data read)
/******************************************************************************/
void RF_ReadBuf(uint8_t reg, unsigned char *pBuf, uint8_t length) {
	uint8_t byte_ctr;

	CSN_LOW;
	SPI_WR(reg);
	for (byte_ctr = 0; byte_ctr < length; byte_ctr++)
		pBuf[byte_ctr] = ucSPI_Read();
	SPI_DATA_OUTPUT_MODE
	;
	CSN_HIGH;
}

/******************************************************************************/
//            RF_TxMode
//                Set RF into TX mode
/******************************************************************************/
void RF_TxMode(void) {
	CE_LOW;
	RF_WriteReg(W_REGISTER + CONFIG, 0X8E);						// ��RF���ó�TXģʽ
//	delay_10us(1);
	nop
	nop
	nop
	nop
}

/******************************************************************************/
//            RF_RxMode
//            ��RF���ó�RXģʽ��׼����������
/******************************************************************************/
void RF_RxMode(void) {
	uint16_t i = 0;
	CE_LOW;
	RF_WriteReg(W_REGISTER + CONFIG, 0X8F);						// ��RF���ó�RXģʽ
	CE_HIGH;										// Set CE pin high ��ʼ��������
//	delay_ms(2);
	for (i = 0; i < 2000; i++) {
		nop
	}

}

/******************************************************************************/
//            RF_GetStatus
//            read RF IRQ status,3bits return
/******************************************************************************/
uint8_t ucRF_GetStatus(void) {
	return ucRF_ReadReg(STATUS) & 0x70;								//��ȡRF��״̬
}
/******************************************************************************/
//            ucRF_GetRSSI
//                ��ȡrssi ֵ
/******************************************************************************/
uint8_t ucRF_GetRSSI(void) {
	return (ucRF_ReadReg(DATAOUT));								//��ȡRF RSSI
}
/******************************************************************************/
//            RF_ClearStatus
//                clear RF IRQ
/******************************************************************************/
void RF_ClearStatus(void) {
	RF_WriteReg(W_REGISTER + STATUS, 0x70);							//���RF��IRQ��־
}

/******************************************************************************/
//            RF_ClearFIFO
//                clear RF TX/RX FIFO
/******************************************************************************/
void RF_ClearFIFO(void) {
	RF_WriteReg(FLUSH_TX, 0);			                        //���RF �� TX FIFO
	RF_WriteReg(FLUSH_RX, 0);                                   //���RF �� RX FIFO
}

/******************************************************************************/
//            RF_SetChannel
//                Set RF TX/RX channel:Channel
/******************************************************************************/
void RF_SetChannel(uint8_t Channel) {
	CE_LOW;
	RF_WriteReg(W_REGISTER + RF_CH, Channel);
}

/******************************************************************************/
//            �������ݣ�
//            ������
//              1. ucPayload����Ҫ���͵������׵�ַ
//              2. length:  ��Ҫ���͵����ݳ���
//              length ͨ������ PAYLOAD_WIDTH
/******************************************************************************/
void RF_TxData(uint8_t *ucPayload, uint8_t length) {
	if (0 == ucRF_GetStatus()) {                             // rf free status
		uint16_t i = 0;
		RF_WriteBuf(W_TX_PAYLOAD, ucPayload, length);
		CE_HIGH;                             //rf entery tx mode start send data
//		delay_10us(60);                            //keep ce high at least 600us
		for (i = 0; i < 200; i++) {
			nop
		}
		CE_LOW;                                                 //rf entery stb3
	}
}

/******************************************************************************/
//            ucRF_DumpRxData
//            �������յ������ݣ�
//            ������
//              1. ucPayload���洢��ȡ�������ݵ�Buffer
//              2. length:    ��ȡ�����ݳ���
//              Return:
//              1. 0: û�н��յ�����
//              2. 1: ��ȡ���յ������ݳɹ�
//              note: Only use in Rx Mode
//              length ͨ������ PAYLOAD_WIDTH
/******************************************************************************/
uint8_t ucRF_DumpRxData(uint8_t *ucPayload, uint8_t length) {
	if (ucRF_GetStatus() & RX_DR_FLAG) {

		CE_LOW;
		RF_ReadBuf(R_RX_PAYLOAD, ucPayload, length); //�����յ������ݶ�����ucPayload�������rxfifo
		RF_ClearFIFO();
		RF_ClearStatus();                              		          //���Status
		CE_HIGH;                                                         //������ʼ��
		return 1;
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////////////

//          ���²�����RFͨ����أ��������޸�
////////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
//            PN006_Initial
//                Initial RF
/******************************************************************************/
void RF_Init(void) {
	uint8_t BB_cal_data[5] = { 0x0A, 0x6D, 0x67, 0x9C, 0x46 };
	uint8_t RF_cal_data[3] = { 0xF6, 0x37, 0x5D };
	uint8_t RF_cal2_data[6] = { 0x45, 0x21, 0xef, 0xAC, 0x5A, 0x50 };
	uint8_t Dem_cal_data[1] = { 0x01 };
	uint8_t Dem_cal2_data[3] = { 0x0b, 0xDF, 0x02 };
	SPI_init();
	RF_WriteReg(RST_FSPI, 0x5A);								//Software Reset
	RF_WriteReg(RST_FSPI, 0XA5);

	if (PAYLOAD_WIDTH < 33) {
		RF_WriteReg(W_REGISTER + FEATURE, 0x20);//FIFO_LEN=32 BYTE  and enable Software control ce
	} else {
		RF_WriteReg(W_REGISTER + FEATURE, 0x38);//FIFO_LEN=64 BYTE  and enable Software control ce
	}
	CE_LOW;
	RF_WriteReg(FLUSH_TX, 0);									// CLEAR TXFIFO
	RF_WriteReg(FLUSH_RX, 0);									// CLEAR  RXFIFO
	RF_WriteReg(W_REGISTER + STATUS, 0x70);						// CLEAR  STATUS
	RF_WriteReg(W_REGISTER + EN_RXADDR, 0x01);					// Enable Pipe0
	RF_WriteReg(W_REGISTER + SETUP_AW, 0x03);		// address witdth is 5 bytes
	RF_WriteReg(W_REGISTER + RF_CH, DEFAULT_CHANNEL);                // 2478M HZ
	RF_WriteReg(W_REGISTER + RX_PW_P0, PAYLOAD_WIDTH);				// 8 bytes
	RF_WriteBuf(W_REGISTER + TX_ADDR, (uint8_t*) TX_ADDRESS_DEF,
			sizeof(TX_ADDRESS_DEF));	// Writes TX_Address to PN006
	RF_WriteBuf(W_REGISTER + RX_ADDR_P0, (uint8_t*) TX_ADDRESS_DEF,
			sizeof(TX_ADDRESS_DEF));	// RX_Addr0 same as TX_Adr for Auto.Ack
	RF_WriteBuf(W_REGISTER + BB_CAL, BB_cal_data, sizeof(BB_cal_data));
	RF_WriteBuf(W_REGISTER + RF_CAL2, RF_cal2_data, sizeof(RF_cal2_data));
	RF_WriteBuf(W_REGISTER + DEMOD_CAL, Dem_cal_data, sizeof(Dem_cal_data));
	RF_WriteBuf(W_REGISTER + RF_CAL, RF_cal_data, sizeof(RF_cal_data));
	RF_WriteBuf(W_REGISTER + DEM_CAL2, Dem_cal2_data, sizeof(Dem_cal2_data));
	RF_WriteReg(W_REGISTER + DYNPD, 0x00);
	RF_WriteReg(W_REGISTER + RF_SETUP, RF_POWER);						// 13DBM

#if(TRANSMIT_TYPE == TRANS_ENHANCE_MODE)
	RF_WriteReg(W_REGISTER + SETUP_RETR, 0x03);					//  3 retrans...
	RF_WriteReg(W_REGISTER + EN_AA, 0x01);// Enable Auto.Ack:Pipe0
#elif(TRANSMIT_TYPE == TRANS_BURST_MODE)
	RF_WriteReg(W_REGISTER + SETUP_RETR, 0x00);	// Disable retrans...
	RF_WriteReg(W_REGISTER + EN_AA, 0x00);	// Disable AutoAck
#endif

}

/******************************************************************************/
//            		�����ز�ģʽ
/******************************************************************************/
void RF_Carrier(uint8_t ucChannel_Set) {
	uint8_t i = 0;
	uint8_t BB_cal_data[5] = { 0x0A, 0x6D, 0x67, 0x9C, 0x46 };
	uint8_t RF_cal_data[3] = { 0xF6, 0x37, 0x5D };
	uint8_t RF_cal2_data[6] = { 0x45, 0x21, 0xEF, 0xAC, 0x5A, 0x50 };
	uint8_t Dem_cal_data[1] = { 0xE1 };
	uint8_t Dem_cal2_data[3] = { 0x0B, 0xDF, 0x02 };

	RF_WriteReg(RST_FSPI, 0x5A);								//Software Reset
	RF_WriteReg(RST_FSPI, 0XA5);
	RF_WriteReg(W_REGISTER + FEATURE, 0x20);
	CE_LOW;
//	delay_ms(200);
	for (i = 0; i < 220; i++) {
		nop
		nop
		nop
		nop
	}

	RF_WriteReg(W_REGISTER + RF_CH, ucChannel_Set);						//���ز�Ƶ��
	RF_WriteReg(W_REGISTER + RF_SETUP, RF_POWER);      					//13dbm
	RF_WriteBuf(W_REGISTER + BB_CAL, BB_cal_data, sizeof(BB_cal_data));
	RF_WriteBuf(W_REGISTER + RF_CAL2, RF_cal2_data, sizeof(RF_cal2_data));
	RF_WriteBuf(W_REGISTER + DEMOD_CAL, Dem_cal_data, sizeof(Dem_cal_data));
	RF_WriteBuf(W_REGISTER + RF_CAL, RF_cal_data, sizeof(RF_cal_data));
	RF_WriteBuf(W_REGISTER + DEM_CAL2, Dem_cal2_data, sizeof(Dem_cal2_data));
}

/***************************************end of file ************************************/
