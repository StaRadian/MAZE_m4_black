#include "stm32g4xx_hal.h"
#include "uart_print.h"
#include "usart.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hcms.h"


void uartprint( char *pchar , ... )
{
    char buf[ 128 ] = { 0 , };
	
    va_list va_ptr;
	
    va_start( va_ptr , pchar );	 
    vsprintf( buf , pchar , va_ptr );
    va_end( va_ptr );
	
    HAL_UART_Transmit(&huart1, buf, strlen(buf), 0xFFFF);
}

//hc-06 AT command mode
void hc06_ATCommand(
    const uint16_t hc06_baudrate,
    const char *name,
    const char *pin
    )
{
    if(HAL_UART_Init(&huart1) != HAL_OK)
    {
        Error_Handler();
    }
    HAL_UART_Transmit(&huart1, "AT", 2, 0xFFFF);

    // const uint16_t baudrate_temp = huart1.Init.BaudRate;
    // huart1.Init.BaudRate = hc06_baudrate;
    
    // if(HAL_UART_Init(&huart1) != HAL_OK) 
    // {
    //     Error_Handler();
    // }

    // switch(buff_baudrate) 
    // {
    //     case 1200:
    //         HAL_UART_Transmit(&huart1, "AT+BAUD1\r\n", 10, 0xFFFF);
    //         break;
    //     case 2400:
    //         HAL_UART_Transmit(&huart1, "AT+BAUD2\r\n", 10, 0xFFFF);
    //         break;
    //     case 4800:
    //         HAL_UART_Transmit(&huart1, "AT+BAUD3\r\n", 10, 0xFFFF);
    //         break;
    //     case 9600:
    //         HAL_UART_Transmit(&huart1, "AT+BAUD4\r\n", 10, 0xFFFF);
    //         break;
    //     case 19200:
    //         HAL_UART_Transmit(&huart1, "AT+BAUD5\r\n", 10, 0xFFFF);
    //         break;
    //     case 38400:
    //         HAL_UART_Transmit(&huart1, "AT+BAUD6\r\n", 10, 0xFFFF);
    //         break;
    //     case 57600:
    //         HAL_UART_Transmit(&huart1, "AT+BAUD7\r\n", 10, 0xFFFF);
    //         break;
    //     case 115200:
    //         HAL_UART_Transmit(&huart1, "AT+BAUD8\r\n", 10, 0xFFFF);
    //         break;
    //     case 230400:
    //         HAL_UART_Transmit(&huart1, "AT+BAUD9\r\n", 10, 0xFFFF);
    //         break;
    //     case 460800:
    //         HAL_UART_Transmit(&huart1, "AT+BAUDA\r\n", 10, 0xFFFF);
    //         break;
    //     case 921600:
    //         HAL_UART_Transmit(&huart1, "AT+BAUDB\r\n", 10, 0xFFFF);
    //         break;
    //     case 1382400:
    //         HAL_UART_Transmit(&huart1, "AT+BAUDC\r\n", 10, 0xFFFF);
    //         break;
    //     default:
    //         huart1.Init.BaudRate = buff_baudrate;
    
    //         if(HAL_UART_Init(&huart1) != HAL_OK) 
    //         {
    //             Error_Handler();
    //         }
    //         return;
    // }

    // const size_t name_len = strlen(name);
    // const size_t prefix_len = 8 + 2;
    // const size_t total_len = name_len + prefix_len;
    // char* name_str = calloc(total_len, sizeof(char));

    // strcpy(name_str, "AT-NAME=");
    // strcat(name_str, name);
    // strcat(name_str, "\r\n");

    // HAL_UART_Transmit(&huart1, "AT+NAMEasft\r\n", 13, 0xFFFF);

    // HAL_UART_Transmit(&huart1, name_str, total_len, 0xFFFF);

    // huart1.Init.BaudRate = baudrate_temp;
    // //hcmsprint("%s",name_str);
    
    // if(HAL_UART_Init(&huart1) != HAL_OK)
    // {
    //     Error_Handler();
    // }

}