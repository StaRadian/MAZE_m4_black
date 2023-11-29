#ifndef UART_PRINT_H_
#define UART_PRINT_H_

void uartprint( char *pchar , ... );

void hc06_ATCommand(
    const uint16_t hc06_baudrate,
    const char *name,
    const char *pin
    );

#endif /* HCMS_H_ */