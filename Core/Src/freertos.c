/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "fatfs.h"
#include "stdio.h"
#include "tftpserverif.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 1024 * 4
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

extern void MX_LWIP_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* init code for LWIP */
  MX_LWIP_Init();
  /* USER CODE BEGIN StartDefaultTask */
//  uint32_t byteswritten;                /* File write counts */
//  uint32_t bytesread;                   /* File read counts */
//  uint8_t wtext[] = "This is STM32 working with FatFs_with_DMA_and_Freertos mode"; /* File write buffer */
//  uint8_t rtext[100];
//  char filename[] = "stm32_11111.txt";
//  /*##-1- Register the file system object to the FatFs module ##############*/
//  retSD = f_mount(&SDFatFS,"", 1);
//  if(retSD)
//  {
//    printf("mount error : %d \r\n",retSD);
//    Error_Handler();
//  }
//  else
//    printf("mount sucess!!! \r\n");
//  /*##-2- Create and Open new text file objects with write access ######*/
//  retSD = f_open(&SDFile, filename, FA_CREATE_ALWAYS | FA_WRITE);
//  if(retSD)
//    printf("open file error : %d\r\n",retSD);
//  else
//    printf("open file sucess!!! \r\n");
//  /*##-3- Write data to the text files ###############################*/
//  retSD = f_write(&SDFile, wtext, sizeof(wtext), (void *)&byteswritten);
//  if(retSD)
//    printf("write file error : %d\r\n",retSD);
//  else
//  {
//    printf("write file sucess!!! \r\n");
//    printf("write Data : %s\r\n",wtext);
//  }
//  /*##-4- Close the open text files ################################*/
//  retSD = f_close(&SDFile);
//  if(retSD)
//    printf("close error : %d\r\n",retSD);
//  else
//    printf("close sucess!!! \r\n");
//
//  /*##-5- Open the text files object with read access ##############*/
//  retSD = f_open(&SDFile, filename, FA_READ);
//  if(retSD)
//    printf("open file error : %d\r\n",retSD);
//  else
//    printf("open file sucess!!! \r\n");
//
//  /*##-6- Read data from the text files ##########################*/
//  retSD = f_read(&SDFile, rtext, sizeof(rtext), (UINT*)&bytesread);
//  if(retSD)
//    printf("read error!!! %d\r\n",retSD);
//  else
//  {
//    printf("read sucess!!! \r\n");
//    printf("read Data : %s\r\n",rtext);
//  }
//
//  /*##-7- Close the open text files ############################*/
//  retSD = f_close(&SDFile);
//  if(retSD)
//    printf("close error!!! %d\r\n",retSD);
//  else
//    printf("close sucess!!! \r\n");
//
//  /*##-8- Compare read data with the expected data ############*/
//  if(bytesread == byteswritten)
//  {
//    printf("FatFs is working well!!!\r\n");
//  }
  tftpserverif_init();
  /* Infinite loop */
  for(;;)
  {
    osDelay(1000);
    HAL_GPIO_TogglePin(BLUE_GPIO_Port, BLUE_Pin);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
