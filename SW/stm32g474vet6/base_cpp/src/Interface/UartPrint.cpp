#include "UartPrint.h"

#include <cstdarg>
#include <cstdio>
#include <cstring>

#include "usart.h"

UartPrint::UartPrint(UART_HandleTypeDef *huart) : m_huart(huart) {
  huart1.Init.BaudRate = 9600;
  HAL_UART_Init(&huart1);
}

void UartPrint::Print( char *pchar , ... ) {
    char buf[ 128 ] = { 0 , };
	
    va_list va_ptr;
	
    va_start( va_ptr , pchar );	 
    vsprintf( buf , pchar , va_ptr );
    va_end( va_ptr );
	
    HAL_UART_Transmit(m_huart, (uint8_t *)buf, strlen(buf), 0xFFFF);
}