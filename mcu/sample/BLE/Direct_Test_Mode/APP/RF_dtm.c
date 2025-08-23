/********************************** (C) COPYRIGHT *******************************
 * File Name          : rf_basic.c
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2024/08/15
 * Description        : dtm����
 *
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

/******************************************************************************/
/* ͷ�ļ����� */
#include "rf_test.h"
#include "hal.h"
#include "RingMem.h"
/*********************************************************************
 * GLOBAL TYPEDEFS
 */
#define  ALIGNED4(x)       ((x+3)/4*4)

tmosTaskID rfTaskID;
rfRoleParam_t gParm;

rfipTx_t gTxParam;
rfipRx_t gRxParam;

__attribute__((__aligned__(4))) uint8_t TxBuf[255]; //������ֽ�255
__attribute__((__aligned__(4))) uint8_t RxBuf[264]; // ����DMA buf����С��264�ֽ�


uint8_t uartRingMemBuff[1024];
RingMemParm uartRingParm = {0};
const uint8_t endTestCmd[4]={0x01, 0x1F, 0x20, 0x00};
const uint8_t resetCmd[4]={0x01, 0x03, 0x0C, 0x00};
const uint8_t receiverCmd[4]={0x01, 0x1D, 0x20, 0x01};
const uint8_t transmitterCmd[4]={0x01, 0x1E, 0x20, 0x03};
const uint8_t receiver2MCmd[4]={0x01, 0x33};
const uint8_t transmitter2MCmd[4]={0x01, 0x34};
const uint8_t setPowerCmd[4]={0x01, 0x01, 0xFF, 0x01};
const uint8_t pFCmd[4]={0x01, 0x02, 0xFF, 0x01};
const uint8_t SingleCarrierCmd[4]={0x01, 0x03, 0xFF, 0x01};
uint8_t cmdCompleteEvt[23]={0x04, 0x0E};
uint8_t TEST_MODE= 0xFF;   // ����ģʽ�����ͻ��߽���
uint8_t ttflag=0; //������ɱ�־
uint8_t ch;
rfRoleConfig_t rf_cfg= {0};
#define  MODE_RX     0
#define  MODE_TX     1
#define WHITE_ON   0
#define WHITE_OFF  1

int8_t gRssi;

int8_t gRssiAverage;
uint32_t gTxCount;
uint32_t gRxCount;

/******************************** ������غ��� ********************************/
/**
 * @brief   ���÷��͵�Ƶ��
 *
 * @param   channel_num - ��Ҫ�л���ͨ��
 *
 * @return  None.
 */
__HIGH_CODE
void rf_tx_set_channel( uint8_t channel_num )
{
    gTxParam.frequency = channel_num;
}

/**
 * @brief   ���÷��͵ĵ�ַ
 *
 * @param   sync_word - ��Ҫ���õĽ����ַ
 *
 * @return  None.
 */
__HIGH_CODE
void rf_tx_set_sync_word( uint32_t sync_word )
{
    gTxParam.accessAddress = sync_word;
}

/**
 * @brief   rf���������ӳ���
 *
 * @param   pBuf - ���͵�DMA��ַ
 *
 * @return  None.
 */
__HIGH_CODE
void rf_tx_start( uint8_t *pBuf )
{
    RFIP_SetTxStart( );
    mDelayuS(1);
    gTxParam.txDMA = (uint32_t)pBuf;
    RFIP_SetTxParm( &gTxParam );
}

/******************************** ������غ��� ********************************/
/**
 * @brief   ���ý��յĵ�ַ
 *
 * @param   sync_word - ��Ҫ���õĽ����ַ
 *
 * @return  None.
 */

__HIGH_CODE
void rf_rx_set_sync_word( uint32_t sync_word )
{
    gRxParam.accessAddress = sync_word;
}

/**
 * @brief   ���ý��յ�Ƶ��
 *
 * @param   channel_num - ��Ҫ�л���ͨ��
 *
 * @return  None.
 */

__HIGH_CODE
void rf_rx_set_channel( uint8_t channel_num )
{
    gRxParam.frequency = channel_num;
}

/**
 * @brief   rf���������ӳ���
 *
 * @param   None.
 *
 * @return  None.
 */
__HIGH_CODE
void rf_rx_start( void )
{
    // ���ý��յĳ�ʱʱ�䣬0���޳�ʱ
    gRxParam.timeOut = 0;
//    gRxParam.accessAddress = gParm.accessAddress; // ����ͬ����
    RFIP_SetRx( &gRxParam );
}

///*******************************************************************************
// * @fn      LLE_IRQHandler
// *
// * @brief   LLE_IRQHandler
// *
// * @return  None.
// */
//__INTERRUPT
//__HIGH_CODE
//void LLE_IRQHandler( void )
//{
//    LLE_LibIRQHandler( );
//}
//
///*******************************************************************************
// * @fn      BB_IRQHandler
// *
// * @brief   BB_IRQHandler
// *
// * @return  None.
// */
//__INTERRUPT
//__HIGH_CODE
//void BB_IRQHandler( void )
//{
//    BB_LibIRQHandler( );
//}

__HIGH_CODE
void m_UART_SendString(uint8_t *buf, uint16_t l)
{
    uint16_t len = l;

    while(len)
    {
        if(R8_UART1_TFC != UART_FIFO_SIZE)
        {
            R8_UART1_THR = *buf++;
            len--;
        }
    }
}
__HIGH_CODE
uint16_t m_UART_RecvString(uint8_t *buf)
{
    uint16_t len = 0;

    while(R8_UART1_RFC)
    {
        *buf++ = R8_UART1_RBR;
        len++;
    }

    return (len);
}


/*******************************************************************************
 * @fn      RF_ProcessCallBack
 *
 * @brief   rf�жϴ������
 *
 * @param   sta - �ж�״̬.
 *          id - ����
 *
 * @return  None.
 */
__HIGH_CODE
void RF_ProcessCallBack( rfRole_States_t sta,uint8_t id  )
{
    if( sta&RF_STATE_RX )
    {
        gRxCount ++;
        rf_rx_start();
    }
    if( sta&RF_STATE_RX_CRCERR )
    {
        rf_rx_start( );
    }
    if( sta&RF_STATE_TX_FINISH )
    {
        if( TEST_MODE ==  MODE_TX )
        {
            gTxCount ++;
            ttflag = 1;
        }
    }
    if( sta&RF_STATE_TIMEOUT )
    {
        if( TEST_MODE ==  MODE_RX )
        {
          rf_rx_start( );
        }
    }
}

/*******************************************************************************
 * @fn      RF_ProcessEvent
 *
 * @brief   RF��ϵͳ������
 *
 * @param   None.
 *
 * @return  None.
 */
__HIGH_CODE
tmosEvents RFRole_ProcessEvent( tmosTaskID task_id, tmosEvents events )
{
    if( events & SYS_EVENT_MSG )
    {
        uint8_t * msgPtr;

        msgPtr = tmos_msg_receive(task_id);
        if( msgPtr )
        {
            /* De-allocate */
             tmos_msg_deallocate( msgPtr );
        }
        return events ^ SYS_EVENT_MSG;
    }
    if( events & RF_START_RX_EVENT )
    {
        rf_rx_start( );
    }
//    if( events & RF_TEST_TX_EVENT )
//    {
//        PRINT("%d\t%d\t%d\n",gTxCount,gRxCount,gRssiAverage );
//        gTxCount = 0;
//        gRxCount = 0;
//        gRssiAverage = 0;
//        return events ^ RF_TEST_TX_EVENT;
//    }
//    if( events & RF_TEST_RX_EVENT )
//    {
//        PRINT("%d\t%d\t%d\n",gTxCount,gRxCount,gRssiAverage );
//        gTxCount = 0;
//        gRxCount = 0;
//        gRssiAverage = 0;
//        return events ^ RF_TEST_RX_EVENT;
//    }
    return 0;
}

/*******************************************************************************
 * @fn      RFRole_Init
 *
 * @brief   RFӦ�ò��ʼ��
 *
 * @param   None.
 *
 * @return  None.
 */
__HIGH_CODE
void RFRole_Init(void)
{
    rfTaskID = TMOS_ProcessEventRegister( RFRole_ProcessEvent );
    RingMemInit( &uartRingParm, uartRingMemBuff, sizeof(uartRingMemBuff) );
    {
        rfRoleConfig_t conf ={0};

        rf_cfg.TxPower = LL_TX_POWEER_0_DBM;
        conf.TxPower = LL_TX_POWEER_0_DBM;
        conf.rfProcessCB = RF_ProcessCallBack;
        conf.processMask = RF_STATE_RX|RF_STATE_RX_CRCERR|RF_STATE_TX_FINISH|RF_STATE_TIMEOUT;
        RFRole_BasicInit( &conf );
    }
    {
        gParm.accessAddress = 0x71764129;
        gParm.crcInit = 0x555555;
        // ����PHY����
        gParm.properties = WHITE_OFF | LLE_MODE_PHY_1M;
        // ���÷����ȶ�ʱ��
        gParm.sendTime = 20*2;
        RFRole_SetParam( &gParm );
    }
    // TX��ز�����ȫ�ֱ���
    {
        gTxParam.accessAddress = gParm.accessAddress;
        gTxParam.crcInit = gParm.crcInit;
        gTxParam.properties = gParm.properties;
        gTxParam.sendCount = 1;
        gTxParam.txDMA = (uint32_t)TxBuf;
    }
    // RX��ز�����ȫ�ֱ���
    {
        gRxParam.accessAddress = gParm.accessAddress;
        gRxParam.crcInit = gParm.crcInit;
        gRxParam.properties = gParm.properties;
        gRxParam.rxDMA = (uint32_t)RxBuf;
        gRxParam.rxMaxLen = 255;
    }
    PFIC_EnableIRQ( BLEB_IRQn );
    PFIC_EnableIRQ( BLEL_IRQn );
}

__attribute__((interrupt("WCH-Interrupt-fast")))
__HIGH_CODE
void UART1_IRQHandler()
{
      if( (R8_UART1_IIR & RB_IIR_INT_MASK) !=1 )
      {
        switch( R8_UART1_IIR & RB_IIR_INT_MASK )
        {
            case UART_II_RECV_RDY:       //�������ݿ���
            case UART_II_RECV_TOUT:      //���ճ�ʱ
            {
                uint8_t uartRecBuff[10];
                uint8_t uartRecLen;
                uartRecLen = m_UART_RecvString( uartRecBuff );
                // д�뻺����
                if( RingMemWrite( &uartRingParm, uartRecBuff, uartRecLen ) )
                {
                    PRINT("RingMem err %d %d %d \n",uartRecLen,uartRingParm.RemanentLen,uartRingParm.MaxLen);
                }
                break;
            }
            default:
                break;
        }
      }
}



/*******************************************************************************
 * @fn      Choose_CH
 *
 * @brief   rfͨ��ת��ΪBLEͨ��
 *
 * @param   rfͨ��.
 *
 * @return  BLEͨ��.
 */
__HIGH_CODE
uint8 Choose_CH( uint8 cch )
{
  if( cch == 0 )
    return 37;
  else if( cch == 12 )
    return 38;
  else if( cch == 39 )
    return 39;
  else if( cch < 12 )
    return cch-1;
  else if( cch > 12 )
    return cch-2;
  else
    return 0;
}


/*******************************************************************************
 * @fn      UART_Process_Data
 *
 * @brief   ���������
 *
 * @param   None.
 *
 * @return  None.
 */

uint8 single =0;
__HIGH_CODE
void UART_Process_Data(void)
{
 if( uartRingParm.CurrentLen >=4  )
 {
    uint8_t pData[23];
    uint8 dataLen;
    if( RingReturnSingleData( &uartRingParm, 0 )!=0x01 )
    {
      RingMemDelete( &uartRingParm, 1 );
      return;
    }
    dataLen = RingReturnSingleData( &uartRingParm, 3 );
    if( uartRingParm.CurrentLen < dataLen+4 )
    {
      return;
    }
    RingMemCopy( &uartRingParm, pData, dataLen+4 );

    if( __wrap_memcmp( pData, endTestCmd, 4 ) == 0)
    {
      RFRole_Shut();
      cmdCompleteEvt[2] = 0x06;
      cmdCompleteEvt[3] = 0x01;
      cmdCompleteEvt[4] = pData[1];
      cmdCompleteEvt[5] = pData[2];
      cmdCompleteEvt[6] = 0x00;
      if( single == 1)
      {
        RFIP_TestEnd();
        single = 0;
      }
      if( TEST_MODE == MODE_TX )
      {
        cmdCompleteEvt[7] = (gTxCount)&0xFF;
        cmdCompleteEvt[8] = ((gTxCount)>>8)&0xFF;
        m_UART_SendString( cmdCompleteEvt, 9 );
        ch=0;
        gRxCount = 0;
        gTxCount = 0;
        TEST_MODE = 0xFF;
      }
      else
      {//rx
        cmdCompleteEvt[7] = (gRxCount)&0xFF;
        cmdCompleteEvt[8] = ((gRxCount)>>8)&0xFF;
        m_UART_SendString( cmdCompleteEvt, 9 );
        ch=0;
        gRxCount = 0;
        gTxCount = 0;
        TEST_MODE = 0xFF;
      }
    }
    else if( __wrap_memcmp( pData, SingleCarrierCmd, 4 ) == 0)
    {
      cmdCompleteEvt[2] = 0x04;
      cmdCompleteEvt[3] = 0x01;
      cmdCompleteEvt[4] = pData[1];
      cmdCompleteEvt[5] = pData[2];
      cmdCompleteEvt[6] = 0x00;
      m_UART_SendString( cmdCompleteEvt, 7 );
      ch = pData[4];
      single = 1;
      RFIP_SetTxPower( rf_cfg.TxPower );  //flash
      RFIP_SingleChannel( ch );
    }
    else if( __wrap_memcmp( pData, resetCmd, 4 ) == 0)
    {
      cmdCompleteEvt[2] = 0x04;
      cmdCompleteEvt[3] = 0x01;
      cmdCompleteEvt[4] = pData[1];
      cmdCompleteEvt[5] = pData[2];
      cmdCompleteEvt[6] = 0x00;
      m_UART_SendString( cmdCompleteEvt, 7 );
      ch=0;
      gRxCount = 0;
      gTxCount = 0;
      TEST_MODE = 0xFF;
    }
    else if( __wrap_memcmp( pData, receiverCmd, 4 ) == 0)
    {
      RFRole_Shut();
      cmdCompleteEvt[2] = 0x04;
      cmdCompleteEvt[3] = 0x01;
      cmdCompleteEvt[4] = pData[1];
      cmdCompleteEvt[5] = pData[2];
      cmdCompleteEvt[6] = 0x00;
      m_UART_SendString( cmdCompleteEvt, 7 );
      ch = Choose_CH(pData[4]);
      gRxCount = 0;
      gRxParam.properties &=~(3<<4);
      gRxParam.frequency = ch;
      TEST_MODE = MODE_RX;
      rf_rx_start();
    }
    else if( __wrap_memcmp( pData, transmitterCmd, 4 ) == 0)
    {
      RFRole_Shut();
      cmdCompleteEvt[2] = 0x04;
      cmdCompleteEvt[3] = 0x01;
      cmdCompleteEvt[4] = pData[1];
      cmdCompleteEvt[5] = pData[2];
      cmdCompleteEvt[6] = 0x00;
      m_UART_SendString( cmdCompleteEvt, 7 );
      ch = Choose_CH(pData[4]);
      gRxCount = 0;
      gTxParam.properties &=~(3<<4);;
      gTxParam.frequency = ch;
      TxBuf[1] = pData[5];
      TxBuf[0] = pData[6];
      TEST_MODE = MODE_TX;
      TX_DATA( TxBuf, TxBuf[1] );
      rf_tx_start(TxBuf);
   }
   else if( __wrap_memcmp( pData, setPowerCmd, 4 ) == 0)
   {
      cmdCompleteEvt[2] = 0x04;
      cmdCompleteEvt[3] = 0x01;
      cmdCompleteEvt[4] = pData[1];
      cmdCompleteEvt[5] = pData[2];
      cmdCompleteEvt[6] = 0x00;
      m_UART_SendString( cmdCompleteEvt, 7 );
      rf_cfg.TxPower = pData[4];
      RFIP_SetTxPower( rf_cfg.TxPower );
    }
   else if( __wrap_memcmp( pData, pFCmd, 4 ) == 0)
   {
      cmdCompleteEvt[2] = 0x04;
      cmdCompleteEvt[3] = 0x01;
      cmdCompleteEvt[4] = pData[1];
      cmdCompleteEvt[5] = pData[2];
      cmdCompleteEvt[6] = 0x00;
      m_UART_SendString( cmdCompleteEvt, 7 );
      //����
      R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
      R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
      R8_XT32M_TUNE &= ~RB_XT32M_C_LOAD;
      R8_XT32M_TUNE |= pData[4]<<4;
      R8_SAFE_ACCESS_SIG = 0;
   }
   else if( __wrap_memcmp( pData, receiver2MCmd, 2 ) == 0)
   {
      RFRole_Shut();
      cmdCompleteEvt[2] = 0x04;
      cmdCompleteEvt[3] = 0x01;
      cmdCompleteEvt[4] = pData[1];
      cmdCompleteEvt[5] = pData[2];
      cmdCompleteEvt[6] = 0x00;
      m_UART_SendString( cmdCompleteEvt, 7 );
      ch = Choose_CH(pData[4]);

      if( pData[5]==1 )
      {
          gRxParam.properties &=~(3<<4);
      }
      else if( pData[5]==2 )
      {
          gRxParam.properties |= LLE_MODE_PHY_2M ;
      }
      gRxCount = 0;
      gRxParam.frequency = ch;
      TEST_MODE = MODE_RX;
      rf_rx_start();
    }
    else if( __wrap_memcmp( pData, transmitter2MCmd, 2 ) == 0)
    {
      RFRole_Shut();
      cmdCompleteEvt[2] = 0x04;
      cmdCompleteEvt[3] = 0x01;
      cmdCompleteEvt[4] = pData[1];
      cmdCompleteEvt[5] = pData[2];
      cmdCompleteEvt[6] = 0x00;
      m_UART_SendString( cmdCompleteEvt, 7 );
      ch = Choose_CH(pData[4]);
      TxBuf[1] = pData[5];
      TxBuf[0] = pData[6];
      TX_DATA( TxBuf, TxBuf[1] );
     if( pData[7]==1 )
     {
        gTxParam.properties &=~(3<<4);
      }
      else if( pData[7]==2 )
      {
        gTxParam.properties |= LLE_MODE_PHY_2M ;
      }
      else if( pData[7]==3 )
      {
      }
      else if( pData[7]==4 )
      {
      }
      gRxCount = 0;
      gTxParam.frequency = ch;
      TEST_MODE = MODE_TX;
      rf_tx_start(TxBuf);
    }
    else
    {
      cmdCompleteEvt[2] = 0x04;
      cmdCompleteEvt[3] = 0x01;
      cmdCompleteEvt[4] = pData[1];
      cmdCompleteEvt[5] = pData[2];
      cmdCompleteEvt[6] = 0x00;
      m_UART_SendString( cmdCompleteEvt, 7 );
    }
    RingMemDelete( &uartRingParm, dataLen+4 );
 }
}


/*******************************************************************************
 * @fn      PRBS9_Get
 *
 * @brief   ����ת��ΪPRBS9����
 *
 * @param   pData - ����������
 * @param   len   - ���ݳ���
 *
 * @return  None.
 */
uint16 PRBS9_INIT=0x01FF;
__HIGH_CODE
void PRBS9_Get( uint8 *pData, uint16 len )
{
  uint8 outData=0;
  uint8 i,j;
  for(j=0; j<len; j++)
  {
    outData=0;
    for( i=0; i<8; i++)
    {
      outData |= (PRBS9_INIT&0x01)<<i;
      PRBS9_INIT = (PRBS9_INIT>>1)|(((PRBS9_INIT^(PRBS9_INIT>>4))&0x0001)<<8);
    }
    pData[j] = outData;
  }
}


/*******************************************************************************
 * @fn      PRBS15_Get
 *
 * @brief   ����ת��ΪPRBS15����
 *
 * @param   pData - ����������
 * @param   len   - ���ݳ���
 *
 * @return  None.
 */
uint16 PRBS15_INIT=0x7FFF;
__HIGH_CODE
void PRBS15_Get( uint8 *pData, uint16 len )
{
  uint8 outData=0;
  uint8 i,j;
  for(j=0; j<len; j++)
  {
    outData=0;
    for( i=0; i<8; i++)
    {
      outData |= (PRBS15_INIT&0x01)<<i;
      PRBS15_INIT = (PRBS15_INIT>>1)|(((PRBS15_INIT^(PRBS15_INIT>>1))&0x0001)<<14);
    }
    pData[j] = outData;
  }
}

/*******************************************************************************
 * @fn      TX_DATA
 *
 * @brief   ����ת��Ϊָ������
 *
 * @param   buf - ����������
 * @param   len - ���ݳ���
 *
 * @return  None.
 */

__HIGH_CODE
void TX_DATA( uint8_t* buf, uint8_t len )
{
  switch( buf[0])
  {
    case 0:
    {
      PRBS9_Get( &buf[2], len );
      break;
    }
    case 1:
    {
        __wrap_memset(&buf[2],0xF0, len+4 );
      break;
    }
    case 2:
    {
        __wrap_memset(&buf[2],0xAA, len+4 );
      break;
    }
    case 3:
    {
        PRBS15_Get( &buf[2], len );
        break;
    }
    case 4:
    {
        __wrap_memset(&buf[2],0xFF, len+4 );
      break;
    }
    case 5:
    {
        __wrap_memset(&buf[2],0x00, len+4 );
      break;
    }
    case 6:
    {
        __wrap_memset(&buf[2],0x0F, len+4 );
      break;
    }
    case 7:
    {
        __wrap_memset(&buf[2],0x55, len+4 );
      break;
    }
  }
  buf[1] = len;
}


__HIGH_CODE
void DtmProcess(void)
{
// sys_safe_access_enable();
// R8_FLASH_SCK &= ~(1<<4);
// R8_FLASH_CFG = 0X00;       //312/(2*2)=312/4=78M
// sys_safe_access_disable();
  while(1){
    UART_Process_Data();
    if(ttflag)
    {
      mDelayuS(150);
      ttflag = 0;
      TX_DATA( TxBuf, TxBuf[1] );
      rf_tx_start(TxBuf);
    }
  }
}
/******************************** endfile @rf ******************************/
