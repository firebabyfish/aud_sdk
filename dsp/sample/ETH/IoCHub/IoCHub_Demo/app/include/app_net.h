/*
 * app_net.h
 *
 *  Created on: Sep 9, 2022
 *      Author: TECH66
 */

#ifndef USER_APP_NET_H_
#define USER_APP_NET_H_
#ifdef CH579
#include "CH57x_common.h"
#endif
#include "WCHNET.h"
#include "eth_driver.h"

extern u8 dhcpflag;
void WCHNET_HandleGlobalInt(void);
void WCHNET_CreatTcpSocket (uint32_t srcport, uint32_t desport, uint8_t *DESIP, uint8_t *SocketId);
void WCHNET_CreatUdpSocket (uint32_t srcport, uint8_t *SocketId);
void TCP_Send (uint8_t socketid, uint8_t *buf, uint32_t len);
void UDP_Send (uint8_t socketid, uint8_t *buf, uint32_t slen, uint8_t *dstIP, uint16_t port);
void NET_Init (void);

static inline void NET_Process(void)
{
    WCHNET_MainTask(); /*��̫������������,��Ҫѭ������*/

    if(WCHNET_QueryGlobalInt()) /*��ѯ��̫��ȫ���ж�,������ж�,����ȫ���жϴ�����*/
    {
        WCHNET_HandleGlobalInt();
    }
}

#endif /* USER_APP_NET_H_ */
