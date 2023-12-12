#include "SST25Flash.h"
#include "spi.h"

uint16_t SST25_SPI3_TXData(uint16_t &data) {
    return data;
}

SST25Flash::SST25Flash(GPIO_TypeDef* _CE_base, const uint32_t _CE_pin)
    : m_CE_base(_CE_base), m_CE_pin(_CE_pin) {
    HAL_NVIC_EnableIRQ(SPI3_IRQn);
    SPI3->CR2 &= ~(0x1000);
    SPI3->CR2 |= 0x00C0;

}

void SST25Flash::getData(const uint32_t &address, uint16_t size) {
    const uint16_t txrx_size = size + 4;

    uint16_t txdata_READ[txrx_size];
    uint16_t rxdata_READ[txrx_size];

    txdata_READ[0] = 0x0300;
    txdata_READ[1] = 0x0000;
    txdata_READ[2] = 0x0000;

    // SPI3->CR1 |=0x800;
    SPI3->CR1 |= 0x40;
    // SPI3->CR2 |= 0x1000;
    CE_L();
    for(int i = 0;i<2;i++) {
        SPI3->DR = txdata_READ[i];
        while(!(SPI3->SR & 0x02)) {}
    }
    for(int i = 0;i<4;i++) {
        while(!(SPI3->SR & 0x01)) {}
        SPI3->DR = 0;
        rxdata_READ[i] = SPI3->DR;
        while(SPI3->SR & 0x80) {}
    }
    while(SPI3->SR & 0x80) {}
    SPI3->CR1 &= ~(0x40);
    CE_H();
    HAL_SPI_Transmit(&hspi3, txdata_4KbyteSectorErase, 4, 0xffffff);

    return;
}
  // // HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_RESET);
  //   // HAL_SPI_Transmit(&hspi3, &txdata_RDSR, 1, 0xffffff);
  //   // HAL_SPI_Receive(&hspi3, &rxdata_RDSR, 1, 0xffffff); 
  //   // HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_SET);
  //   // vfd.Print("%X", rxdata_RDSR); //12
    
  //   HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_RESET);
  //   HAL_SPI_Transmit(&hspi3, txdata_WRSR, 2, 0xffffff);
  //   HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_SET);
  //   vfd.Print("WRSR");

  //   HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_RESET);
  //   HAL_SPI_Transmit(&hspi3, &txdata_WREN, 1, 0xffffff);
  //   HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_SET);
  //   vfd.Print("WREN");

  //   // HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_RESET);
  //   // HAL_SPI_Transmit(&hspi3, &txdata_RDSR, 1, 0xffffff);
  //   // HAL_SPI_Receive(&hspi3, &rxdata_RDSR, 1, 0xffffff); 
  //   // HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_SET);
  //   // vfd.Print("%X", rxdata_RDSR); //12

  //   HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_RESET);
  //   HAL_SPI_Transmit(&hspi3, txdata_4KbyteSectorErase, 4, 0xffffff);
  //   HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_SET);
  //   vfd.Print("4KErase");

  //   // HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_RESET);
  //   // HAL_SPI_Transmit(&hspi3, &txdata_RDSR, 1, 0xffffff);
  //   // HAL_SPI_Receive(&hspi3, &rxdata_RDSR, 1, 0xffffff); 
  //   // HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_SET);
  //   // vfd.Print("%X", rxdata_RDSR); //12

  //   do
  //   {
  //     HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_RESET);
  //     HAL_SPI_Transmit(&hspi3, &txdata_RDSR, 1, 0xffffff);
  //     HAL_SPI_Receive(&hspi3, &rxdata_RDSR, 1, 0xffffff); 
  //     HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_SET);
  //   } while (rxdata_RDSR &= 0b00000001);
    


  //   HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_RESET);
  //   HAL_SPI_Transmit(&hspi3, &txdata_WREN, 1, 0xffffff);
  //   HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_SET);
  //   vfd.Print("WREN");

  //   // HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_RESET);
  //   // HAL_SPI_Transmit(&hspi3, txdata_READ, 4, 0xffffff);
  //   // HAL_SPI_Receive(&hspi3, rxdata_READ, 5, 0xffffff);
  //   // HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_SET);
  //   // vfd.Print("%X", rxdata_READ[0]);

  //   HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_RESET);
  //   HAL_SPI_Transmit(&hspi3, txdata_ByteProgram, 5, 0xffffff);
  //   HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_SET);
  //   vfd.Print("ByteProg");
    
  //   HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_RESET);
  //   HAL_SPI_Transmit(&hspi3, txdata_READ, 4, 0xffffff);
  //   HAL_SPI_Receive(&hspi3, rxdata_READ, 5, 0xffffff);
  //   HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_SET);
  //   vfd.Print("%X", rxdata_READ[0]);

  //   HAL_Delay(400);
  //   txdata_ByteProgram[4]++;