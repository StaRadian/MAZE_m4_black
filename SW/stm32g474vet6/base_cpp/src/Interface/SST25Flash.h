#ifndef SST25FLASH_H_
#define SST25FLASH_H_

#include "stm32g4xx_hal.h"

class SST25Flash {
private:
    GPIO_TypeDef *m_CE_base;
    const uint16_t m_CE_pin;

    uint8_t txdata_RDSR = 0x05;
    uint8_t rxdata_RDSR = 0x00;

    uint8_t txdata_4KbyteSectorErase[4] = {0x20, 0x00, 0x00, 0x00};

    uint8_t txdata_WREN = 0x06;

    uint8_t txdata_WRSR[2] = {0x01, 0b00000000};

    uint8_t txdata_ByteProgram[5] = {0x02, 0x00, 0x00, 0x00, 0x4d};
    uint8_t txdata_JEDEC = 0x9f;
    uint8_t rxdata_JEDEC[3] = {0x00, 0x00, 0x00};
    

public:
    SST25Flash(GPIO_TypeDef* _CE_base, const uint32_t _CE_pin);

    void getData(const uint32_t &address, uint16_t size);
    static uint16_t txdata;
    static uint16_t rxdata;

private:
    void CE_H() { m_CE_base->BSRR = (uint32_t)m_CE_pin; }
    void CE_L() { m_CE_base->BRR = (uint32_t)m_CE_pin; }

};

#endif /* SST25FLASH_H_ */ 
