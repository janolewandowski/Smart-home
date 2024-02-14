#include "lwip/opt.h"
#include "lwip/api.h"
#include "lwip/sys.h"
#include "string.h"
#include "tcpserver.h"

#include "../CLU/CLU.h"

int ledcmd;

extern int sem;
extern struct DIMM Przedpokoj;
extern struct DIMM Sypialnia;
extern struct DIMM Kuchnia_1;
extern struct DIMM Kuchnia_2;
extern struct DIMM Salon_1;
extern struct DIMM Salon_2;
extern struct DIMM Lazienka;
extern struct LED Salon_LED;
extern struct LED Salon_LED_Biurko;

//char cmd_DIMMSwitch[] = "DIMM_Switch";
//char cmd_LED[] = "DIMM_Switch";


void TCPServerTask(void const * argument)
{
	static struct netconn *conn, *newconn;
	static struct netbuf *buf;
	static ip_addr_t *addr;
	static unsigned short port;
	char msg[100];
	char smsg[100];

	err_t err, accept_err, recv_error;

	while (!sem){
		osDelay(50);
	}
	/* Create a new connection identifier. */
	conn = netconn_new(NETCONN_TCP);

	if (conn!=NULL){
			/* Bind connection to the port number 7. */
			err = netconn_bind(conn, IP_ADDR_ANY, 7);

			if (err == ERR_OK){
				/* Tell connection to go into listening mode. */
				netconn_listen(conn);
				for(;;)
				{
					/* Grab new connection. */
					accept_err = netconn_accept(conn, &newconn);

					/* Process the new connection. */
					if (accept_err == ERR_OK)
					{
						/* receive the data from the client */
						while (netconn_recv(newconn, &buf) == ERR_OK)
						{
							/* Extract the address and port in case they are required */
							addr = netbuf_fromaddr(buf);  // get the address of the client
							port = netbuf_fromport(buf);  // get the Port of the client
							/* If there is some data remaining to be sent, the following process will continue */
							do
							{
								strncpy (msg, buf->p->payload, buf->p->len);   // get the message from the client

								// Or modify the message received, so that we can send it back to the client
								int len = sprintf (smsg, "\"%s\" was sent by Client\n", msg);

//								if (ledcmd){
//									LED_SetRedValue(&Salon_LED, (int) msg[0], 0);
//									LED_SetGreenValue(&Salon_LED, (int) msg[1], 0);
//									LED_SetBlueValue(&Salon_LED,(int) msg[2], 0);
//									LED_SetWhiteValue(&Salon_LED,(int)  msg[3], 0);
//									ledcmd = 0;
//								}

								if (!(strcmp(msg, "sypialnia"))){
									DIMM_Switch(&Sypialnia, 0, 0);
								}

								if (!(strcmp(msg, "przedpokoj"))){
													DIMM_Switch(&Przedpokoj, 0, 0);
												}

								if (!(strcmp(msg, "kuchnia"))){
													DIMM_Switch(&Kuchnia_1, 0, 0);
													DIMM_Switch(&Kuchnia_2, 0, 0);
												}

								if (!(strcmp(msg, "salon"))){
													DIMM_Switch(&Salon_1, 0, 0);
													DIMM_Switch(&Salon_2, 0, 0);
												}

								if (!(strcmp(msg, "lazienka"))){
													DIMM_Switch(&Lazienka, 0, 0);
												}
								if (!(strcmp(msg, "salonled"))){
									Salon_LED.WhiteValue = 200;
									Salon_LED_Biurko.WhiteValue = 200;
									LED_Switch(&Salon_LED, 0, 0);
									LED_Switch(&Salon_LED_Biurko, 0, 0);
													//ledcmd = 1;
												}

								netconn_write(newconn, smsg, len, NETCONN_COPY);  // send the message back to the client
								memset (msg, '\0', 100);  // clear the buffer
							}while (netbuf_next(buf) >0);

							netbuf_delete(buf);
						}
						/* Close connection and discard connection identifier. */
						netconn_close(newconn);
						netconn_delete(newconn);
					}
					osDelay(5);
				}
			}
			else
			{
				netconn_delete(conn);
				Error_Handler();
			}
		}else{
			Error_Handler();
		}
  /* USER CODE END TCPServerTask */
}
