#ifndef UARTPRINT_H_
#define UARTPRINT_H_

#include "stm32g4xx_hal.h"

class UartPrint {
private:
    UART_HandleTypeDef *m_huart;
public:
    UartPrint(UART_HandleTypeDef *huart);
    void Print( char *pchar , ... );

};

#endif /* UARTPRINT_H_ */