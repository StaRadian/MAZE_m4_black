#include "main.h"

#include "gpio.h"
#include "spi.h"
#include "usart.h"

#include "Interface/HCMSDisplay.h"
#include "Interface/UartPrint.h"

#include <iomanip>

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

uint8_t txdata_RDSR = 0x05;
uint8_t rxdata_RDSR = 0x00;

uint8_t txdata_4KbyteSectorErase[4] = {0x20, 0x00, 0x00, 0x00};

uint8_t txdata_WREN = 0x06;

uint8_t txdata_WRSR[2] = {0x01, 0x00};

uint8_t txdata_ByteProgram[5] = {0x02, 0x00, 0x00, 0x00, 0x4d};

uint8_t txdata_READ[4] = {0x03, 0x00, 0x00, 0x00};
uint8_t rxdata_READ[5] = {0x00, 0x00, 0x00, 0x00, 0x00};

uint8_t txdata_JEDEC = 0x9f;
uint8_t rxdata_JEDEC[3] = {0x00, 0x00, 0x00};

int main(void)
{
  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();
  MX_SPI3_Init();
  MX_USART1_UART_Init();

  HCMSDisplay vfd(
    GPIOE ,GPIO_PIN_5,
    GPIOB ,GPIO_PIN_6,
    GPIOB ,GPIO_PIN_7,
    GPIOE ,GPIO_PIN_6,
    GPIOB ,GPIO_PIN_9
  );

  UartPrint tx(&huart1, 9600);

  vfd.Print("Hi bart");
  
  tx.Print("Welcome to the M4");

  HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi3, &txdata_RDSR, 1, 0xffffff);
  HAL_SPI_Receive(&hspi3, &rxdata_RDSR, 1, 0xffffff); 
  HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_SET);
  vfd.Print("%X", rxdata_RDSR); //12

  txdata_WRSR[1] = rxdata_RDSR & 0b11110011;

  HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi3, txdata_WRSR, 2, 0xffffff);
  HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_SET);
  vfd.Print("WRSR");

  HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi3, &txdata_RDSR, 1, 0xffffff);
  HAL_SPI_Receive(&hspi3, &rxdata_RDSR, 1, 0xffffff); 
  HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_SET);
  vfd.Print("%X", rxdata_RDSR); //14

  HAL_GPIO_WritePin(Flash_WP_GPIO_Port, Flash_WP_Pin, GPIO_PIN_SET);  //WP START

  HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi3, txdata_4KbyteSectorErase, 4, 0xffffff);
  HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_SET);
  vfd.Print("4KErase");

  HAL_Delay(500);

  HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi3, &txdata_WREN, 1, 0xffffff);
  HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_SET);
  vfd.Print("WREN");

  HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi3, &txdata_RDSR, 1, 0xffffff);
  HAL_SPI_Receive(&hspi3, &rxdata_RDSR, 1, 0xffffff); 
  HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_SET);
  vfd.Print("%X", rxdata_RDSR);

  HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi3, txdata_ByteProgram, 5, 0xffffff);
  HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_SET);
  vfd.Print("ByteProg");
  
  HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi3, txdata_READ, 4, 0xffffff);
  HAL_SPI_Receive(&hspi3, rxdata_READ, 5, 0xffffff);
  HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_SET);
  vfd.Print("%X", rxdata_READ[0]);
  
  HAL_GPIO_WritePin(Flash_WP_GPIO_Port, Flash_WP_Pin, GPIO_PIN_RESET);  //WP END

  HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi3, &txdata_JEDEC, 1, 0xffffff);
  HAL_SPI_Receive(&hspi3, rxdata_JEDEC, 3, 0xffffff); 
  HAL_GPIO_WritePin(Flash_CE_GPIO_Port, Flash_CE_Pin, GPIO_PIN_SET);

  while (1)
  {

  }
}

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
