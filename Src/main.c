/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"
#include "stm32f1xx_hal.h"
#include "math.h"	
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "dwt_stm32_delay.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define REAR_COUNT 80
#define RUN  1
#define NORUN 0


/* ------------------------------MODE-----------------------------------------*/
#define ACTIVE 0x03
#define READ 0x04
#define WRITE 0x05
#define MEASUREMENT 0x06
/* ------------------------------END------------------------------------------*/

/* ------------------------------ACTION-----------------------------------------*/
#define RUN_ACTIVE 0x01
#define NORUN_ACTIVE 0x02
#define GRADE_INFO_ 0x03
#define PACKER_INFO_ 0x04
#define MARKING_INFO_ 0x05
#define SOL_RUN_TIME_INFO_ 0x06
#define MEASUREMENT_INFO_ 0x07
#define LOADCELL_INFO_ZERO_ 0x08
#define LOADCELL_INFO_WEIGHT_ 0x09
#define INIT_DATA_SET_ 0x11
#define ALL_INFO_ 0x12
#define LOADCELL_INFO_ 0x13
#define SOL_TEST_ 0x15
#define CURENT_WEIGHT_ 0x16
#define MEASURE_RUN_ 0x17
#define COM_CHK_ 0x18

/* USER CODE END PD */
/* ------------------------------END------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* ------------------------------flash memory map-----------------------------------------*/
#define ADDR_FLASH_PAGE_0     ((uint32_t)0x08000000) // Page 0, 1 Kbyte
#define ADDR_FLASH_PAGE_1     ((uint32_t)0x08000400) // Page 1, 1 Kbyte
#define ADDR_FLASH_PAGE_2     ((uint32_t)0x08000800) // Page 2, 1 Kbyte
#define ADDR_FLASH_PAGE_3     ((uint32_t)0x08000C00) // Page 3, 1 Kbyte
#define ADDR_FLASH_PAGE_4     ((uint32_t)0x08001000) // Page 4, 1 Kbyte
#define ADDR_FLASH_PAGE_5     ((uint32_t)0x08001400) // Page 5, 1 Kbyte
#define ADDR_FLASH_PAGE_6     ((uint32_t)0x08001800) // Page 6, 1 Kbyte
#define ADDR_FLASH_PAGE_7     ((uint32_t)0x08001C00) // Page 7, 1 Kbyte
#define ADDR_FLASH_PAGE_8     ((uint32_t)0x08002000) // Page 8, 1 Kbyte
#define ADDR_FLASH_PAGE_9     ((uint32_t)0x08002400) // Page 9, 1 Kbyte
#define ADDR_FLASH_PAGE_10    ((uint32_t)0x08002800) // Page 10, 1 Kbyte
#define ADDR_FLASH_PAGE_11    ((uint32_t)0x08002C00) // Page 11, 1 Kbyte
#define ADDR_FLASH_PAGE_12    ((uint32_t)0x08003000) // Page 12, 1 Kbyte
#define ADDR_FLASH_PAGE_13    ((uint32_t)0x08003400) // Page 13, 1 Kbyte
#define ADDR_FLASH_PAGE_14    ((uint32_t)0x08003800) // Page 14, 1 Kbyte
#define ADDR_FLASH_PAGE_15    ((uint32_t)0x08003C00) // Page 15, 1 Kbyte
#define ADDR_FLASH_PAGE_16    ((uint32_t)0x08004000) // Page 16, 1 Kbyte
#define ADDR_FLASH_PAGE_17    ((uint32_t)0x08004400) // Page 17, 1 Kbyte
#define ADDR_FLASH_PAGE_18    ((uint32_t)0x08004800) // Page 18, 1 Kbyte
#define ADDR_FLASH_PAGE_19    ((uint32_t)0x08004C00) // Page 19, 1 Kbyte
#define ADDR_FLASH_PAGE_20    ((uint32_t)0x08005000) // Page 20, 1 Kbyte
#define ADDR_FLASH_PAGE_21    ((uint32_t)0x08005400) // Page 21, 1 Kbyte
#define ADDR_FLASH_PAGE_22    ((uint32_t)0x08005800) // Page 22, 1 Kbyte
#define ADDR_FLASH_PAGE_23    ((uint32_t)0x08005C00) // Page 23, 1 Kbyte
#define ADDR_FLASH_PAGE_24    ((uint32_t)0x08006000) // Page 24, 1 Kbyte
#define ADDR_FLASH_PAGE_25    ((uint32_t)0x08006400) // Page 25, 1 Kbyte
#define ADDR_FLASH_PAGE_26    ((uint32_t)0x08006800) // Page 26, 1 Kbyte
#define ADDR_FLASH_PAGE_27    ((uint32_t)0x08006C00) // Page 27, 1 Kbyte
#define ADDR_FLASH_PAGE_28    ((uint32_t)0x08007000) // Page 28, 1 Kbyte
#define ADDR_FLASH_PAGE_29    ((uint32_t)0x08007400) // Page 29, 1 Kbyte
#define ADDR_FLASH_PAGE_30    ((uint32_t)0x08007800) // Page 30, 1 Kbyte
#define ADDR_FLASH_PAGE_31    ((uint32_t)0x08007C00) // Page 31, 1 Kbyte
#define ADDR_FLASH_PAGE_32    ((uint32_t)0x08008000) // Page 32, 1 Kbyte
#define ADDR_FLASH_PAGE_33    ((uint32_t)0x08008400) // Page 33, 1 Kbyte
#define ADDR_FLASH_PAGE_34    ((uint32_t)0x08008800) // Page 34, 1 Kbyte
#define ADDR_FLASH_PAGE_35    ((uint32_t)0x08008C00) // Page 35, 1 Kbyte
#define ADDR_FLASH_PAGE_36    ((uint32_t)0x08009000) // Page 36, 1 Kbyte
#define ADDR_FLASH_PAGE_37    ((uint32_t)0x08009400) // Page 37, 1 Kbyte
#define ADDR_FLASH_PAGE_38    ((uint32_t)0x08009800) // Page 38, 1 Kbyte
#define ADDR_FLASH_PAGE_39    ((uint32_t)0x08009C00) // Page 39, 1 Kbyte
#define ADDR_FLASH_PAGE_40    ((uint32_t)0x08010000) // Page 40, 1 Kbyte
#define ADDR_FLASH_PAGE_41    ((uint32_t)0x08010400) // Page 41, 1 Kbyte
#define ADDR_FLASH_PAGE_42    ((uint32_t)0x08010800) // Page 42, 1 Kbyte
#define ADDR_FLASH_PAGE_43    ((uint32_t)0x08010C00) // Page 43, 1 Kbyte
#define ADDR_FLASH_PAGE_44    ((uint32_t)0x08011000) // Page 44, 1 Kbyte
#define ADDR_FLASH_PAGE_45    ((uint32_t)0x08011400) // Page 45, 1 Kbyte
#define ADDR_FLASH_PAGE_46    ((uint32_t)0x08011800) // Page 46, 1 Kbyte
#define ADDR_FLASH_PAGE_47    ((uint32_t)0x08011C00) // Page 47, 1 Kbyte
#define ADDR_FLASH_PAGE_48    ((uint32_t)0x08012000) // Page 48, 1 Kbyte
#define ADDR_FLASH_PAGE_49    ((uint32_t)0x08012400) // Page 49, 1 Kbyte
#define ADDR_FLASH_PAGE_50    ((uint32_t)0x08012800) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_50    ((uint32_t)0x08012800) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_51    ((uint32_t)0x08012C00) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_52    ((uint32_t)0x08013000) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_53    ((uint32_t)0x08013400) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_54    ((uint32_t)0x08013800) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_55    ((uint32_t)0x08013C00) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_56    ((uint32_t)0x08014000) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_57    ((uint32_t)0x08014400) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_58    ((uint32_t)0x08014800) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_59    ((uint32_t)0x08014C00) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_60    ((uint32_t)0x08015000) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_61    ((uint32_t)0x08015400) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_62    ((uint32_t)0x08015800) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_63    ((uint32_t)0x08015C00) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_64    ((uint32_t)0x08016000) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_65    ((uint32_t)0x08016400) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_66    ((uint32_t)0x08016800) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_67    ((uint32_t)0x08016C00) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_68    ((uint32_t)0x08017000) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_69    ((uint32_t)0x08017400) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_70    ((uint32_t)0x08017800) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_71    ((uint32_t)0x08017C00) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_72    ((uint32_t)0x08018000) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_73    ((uint32_t)0x08018400) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_74    ((uint32_t)0x08018800) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_75    ((uint32_t)0x08018C00) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_76    ((uint32_t)0x08019000) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_77    ((uint32_t)0x08019400) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_78    ((uint32_t)0x08019800) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_79    ((uint32_t)0x08019C00) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_80    ((uint32_t)0x08020000) // Page 50, 1 Kbyte
#define ADDR_FLASH_PAGE_81    ((uint32_t)0x08020400) // Page 50, 1 Kbyte
/*-----------------------flash memory config----------------------------*/
#define FLASH_PAGE_SIZE   0x400U // 1024 bytes
#define FLASH_USER_START_ADDR    ADDR_FLASH_PAGE_70 // 0x08007C00
#define FLASH_USER_END_ADDR      ADDR_FLASH_PAGE_70 + FLASH_PAGE_SIZE

#define GRADE_INFO_START_ADDR    ADDR_FLASH_PAGE_71 
#define GRADE_INFO_END_ADDR      ADDR_FLASH_PAGE_71 + FLASH_PAGE_SIZE

#define PACKER_INFO_START_ADDR   ADDR_FLASH_PAGE_72 
#define PACKER_INFO_END_ADDR     ADDR_FLASH_PAGE_72 + FLASH_PAGE_SIZE

#define MARKING_INFO_START_ADDR  ADDR_FLASH_PAGE_73 
#define MARKING_INFO_END_ADDR   ADDR_FLASH_PAGE_73 + FLASH_PAGE_SIZE

#define SOL_RUN_TIME_INFO_START_ADDR   ADDR_FLASH_PAGE_74 
#define SOL_RUN_TIME_INFO_END_ADDR     ADDR_FLASH_PAGE_74 + FLASH_PAGE_SIZE

#define MEASUREMENT_INFO_START_ADDR ADDR_FLASH_PAGE_75 
#define MEASUREMENT_INFO_END_ADDR   ADDR_FLASH_PAGE_75 + FLASH_PAGE_SIZE

#define LOADCELL_INFO_START_ADDR ADDR_FLASH_PAGE_76 
#define LOADCELL_INFO_END_ADDR   ADDR_FLASH_PAGE_76 + FLASH_PAGE_SIZE

#define GRADE_INFO_START ((GRADE_INFO_TYPE*)GRADE_INFO_START_ADDR)
#define PACKER_INFO_START ((PACKER_INFO_TYPE*)PACKER_INFO_START_ADDR)
#define MARKING_INFO_START ((MARKING_INFO_TYPE*)MARKING_INFO_START_ADDR)
#define SOL_RUN_TIME_INFO_START ((SOL_RUN_TIME_INFO_TYPE*)SOL_RUN_TIME_INFO_START_ADDR)
#define MEASUREMENT_INFO_START ((MEASUREMENT_INFO_TYPE*)MEASUREMENT_INFO_START_ADDR)
#define LOADCELL_INFO_START ((LOADCELL_INFO_TYPE*)LOADCELL_INFO_START_ADDR)

#define     MAX_GRADE               9
#define     MAX_PACKER              8
#define     MAX_PACKER_SOL          6
#define     MAX_PRT                 2 

#define GRADE_INFO_DATA 1
#define PACKER_INFO_DATA 2
#define MARKING_INFO_DATA 3
#define SOL_RUN_TIME_INFO_DATA 4
#define MEASUREMENT_INFO_DATA 5
#define LOADCELL_INFO_DATA 6

#define GRADE_1 0
#define GRADE_2 1
#define GRADE_3 2
#define GRADE_4 3
#define GRADE_5 4
#define GRADE_6 5
#define GRADE_7 6
#define GRADE_8 7
#define ETC 8

#define PRT_NO 0
#define PRT_A 1
#define PRT_B 2

#define PACKER_1 0
#define PACKER_2 1
#define PACKER_3 2
#define PACKER_4 3
#define PACKER_5 4
#define PACKER_6 5
#define PACKER_7 6
#define PACKER_8 7

#define PACKER_SOL_1 0
#define PACKER_SOL_2 1
#define PACKER_SOL_3 2
#define PACKER_SOL_4 3
#define PACKER_SOL_5 4
#define PACKER_SOL_6 5

#define STX 0x02
#define ETX 0x03

#define STX_NUM 0
#define LEN_NUM 1
/* ------------------------------END---------------------------------  */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;

uint8_t rxtemp;

/* USER CODE BEGIN PV */

uint8_t RUN_ACTIVE_NUM = 0x00;
uint8_t init_run_data[64]={0};

bool send_count = false;
bool sendvalue = false;

uint8_t send_cnt;
uint8_t data_strem[1004]={0};

uint8_t rx_data[256],rx_data_[256],run_data[256], rx_data_tmp[256];
uint8_t txbuff[100];
uint8_t txbuff_SEND[1024];

uint32_t SOL_SELECT = 0;

uint32_t filtereadValue=0, sensorValue;
uint32_t msTimer;
uint32_t timerCnt;
uint32_t Grade_speed;
uint32_t interuptCnt=0, startTime=0 , endTime=0;

uint8_t RearLine [REAR_COUNT];
uint8_t Rear_Count = 1;

uint8_t RearLine_Prt [REAR_COUNT];
uint8_t Rear_Count_Prt = 1;

uint8_t GRADE_PACKER_SELECT_DOUBLE;
uint8_t PACKER_SOL_SELECT_DOUBLE[MAX_PACKER_SOL];


uint8_t G_PACKER_CNT[MAX_GRADE];
uint8_t P_SOL_CNT[MAX_PACKER];
uint8_t GRADE_PACKER[MAX_PACKER][MAX_PACKER];

#pragma pack(push, 1)

typedef struct struct_G_DATA{  
    uint8_t gRCount;  
		uint8_t gPCount;	
    uint32_t gNumber[MAX_GRADE];               
    uint32_t pNumber[MAX_GRADE];        
    uint32_t gTNumber;
	  uint32_t gHNumber;
    uint32_t gSpeed;                   	
    float gWeight[MAX_GRADE]; 	
    float gTWeight;                 
}G_DATA_TYPE;

typedef struct struct_GRADE_INFO{     
    uint8_t PACKER_NUMBER[MAX_PACKER];	
    uint8_t PACKER_COUNT;                          
    uint8_t PRT_USED;	
	  uint32_t PRT_COUNT; 
	  float HILIMIT;        
    float LOLIMIT;
}GRADE_INFO_TYPE;

typedef struct struct_PACKER_INFO{      
    uint8_t SOL_COUNT;
		uint8_t SOL_NUMBER[MAX_PACKER_SOL];
		uint8_t SOL_CONNECT[MAX_PACKER_SOL];                
}PACKER_INFO_TYPE;

typedef struct struct_MARKING_INFO{      
		uint8_t MARKING_1_BURKET_NUM;  // 마킹기1의 동작 버켓번호
		uint8_t MARKING_1_CONNECT;     // 마킹기1의 동작 포트번호   
		uint8_t MARKING_2_BURKET_NUM;  // 마킹기2의 동작 버켓번호
		uint8_t MARKING_2_CONNECT;     // 마킹기2의 동작 포트번호                  
}MARKING_INFO_TYPE;

typedef struct struct_SOL_RUN_TIME_INFO{      
    uint8_t SOL_ON_TIME_;
		uint8_t SOL_OFF_TIME_;            
}SOL_RUN_TIME_INFO_TYPE;

typedef struct struct_MEASUREMENT_INFO{      
    uint8_t START_TIME;
		uint8_t END_TIME;            
}MEASUREMENT_INFO_TYPE;

typedef struct struct_LOADCELL_INFO{
//	  uint8_t CHANNEL; 
    uint32_t OFFSET;        
		uint32_t MOVING_AVRAGE; 
    float SPAN;	
    	
}LOADCELL_INFO_TYPE;

#pragma pack(pop)


G_DATA_TYPE GRADE_DATA;
GRADE_INFO_TYPE GRADE_INFO[MAX_GRADE];
PACKER_INFO_TYPE PACKER_INFO[MAX_PACKER];
MARKING_INFO_TYPE MARKING_INFO;
SOL_RUN_TIME_INFO_TYPE SOL_RUN_TIME_INFO; 
MEASUREMENT_INFO_TYPE MEASUREMENT_INFO;
LOADCELL_INFO_TYPE LOADCELL_INFO;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_ADC1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM3_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int fputc(int ch, FILE *f)
{
	uint8_t temp[1] = {ch} ;
	
	HAL_UART_Transmit(&huart1, temp, 1, 50) ;
	
	return(ch) ;
}

//----------------------Flash set function------------------------------//

HAL_StatusTypeDef FLASH_UPDATE(uint8_t select)
{
	uint32_t *ptr ;
	HAL_FLASH_Unlock();
	uint32_t PAGEError = 0;
  uint32_t *Address;
	uint32_t Data;
	uint32_t i;
	
	FLASH_EraseInitTypeDef EraseInitStruct;
	EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
	
	switch (select)
	{
		case 1:
			EraseInitStruct.PageAddress = GRADE_INFO_START_ADDR;
			EraseInitStruct.NbPages     = (GRADE_INFO_END_ADDR - GRADE_INFO_START_ADDR) / FLASH_PAGE_SIZE;
			HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError); 
			ptr = (uint32_t*)&GRADE_INFO;	
			for( i=0 ; i < sizeof(GRADE_INFO); i++)
			{  
				Address = (uint32_t*)GRADE_INFO_START+i;
				Data = *((uint32_t*)ptr+i);
				HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,(uint32_t)Address,Data);
			}
			break;		
			
		case 2:
			EraseInitStruct.PageAddress = PACKER_INFO_START_ADDR;
			EraseInitStruct.NbPages     = (PACKER_INFO_END_ADDR - PACKER_INFO_START_ADDR) / FLASH_PAGE_SIZE;
			HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError); 
			ptr = (uint32_t*)&PACKER_INFO;	
			for( i=0 ; i < sizeof(PACKER_INFO); i++)
			{  
				Address = (uint32_t*)PACKER_INFO_START+i;
				Data = *((uint32_t*)ptr+i);
				HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,(uint32_t)Address,Data);
			}
			break;
			
		case 3:
			EraseInitStruct.PageAddress = MARKING_INFO_START_ADDR;
			EraseInitStruct.NbPages     = (MARKING_INFO_END_ADDR - MARKING_INFO_START_ADDR) / FLASH_PAGE_SIZE;
			HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError); 
			ptr = (uint32_t*)&MARKING_INFO ;	
			for( i=0 ; i < sizeof(MARKING_INFO); i++)
			{  
				Address = (uint32_t*)MARKING_INFO_START+i;
				Data = *((uint32_t*)ptr+i);
				HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,(uint32_t)Address,Data);
			}
			break;

		case 4:
			EraseInitStruct.PageAddress = SOL_RUN_TIME_INFO_START_ADDR;
			EraseInitStruct.NbPages     = (SOL_RUN_TIME_INFO_END_ADDR - SOL_RUN_TIME_INFO_START_ADDR) / FLASH_PAGE_SIZE;
			HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError); 
			ptr = (uint32_t*)&SOL_RUN_TIME_INFO;	
			for( i=0 ; i < sizeof(SOL_RUN_TIME_INFO); i++)
			{  
				Address = (uint32_t*)SOL_RUN_TIME_INFO_START+i;
				Data = *((uint32_t*)ptr+i);
				HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,(uint32_t)Address,Data);
			}
			break;

		case 5:
			EraseInitStruct.PageAddress = MEASUREMENT_INFO_START_ADDR;
			EraseInitStruct.NbPages     = (MEASUREMENT_INFO_END_ADDR - MEASUREMENT_INFO_START_ADDR) / FLASH_PAGE_SIZE;
			HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError); 
			ptr = (uint32_t*)&MEASUREMENT_INFO;	
			for( i=0 ; i < sizeof(MEASUREMENT_INFO); i++)
			{  
				Address = (uint32_t*)MEASUREMENT_INFO_START +i;
				Data = *((uint32_t*)ptr+i);
				HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,(uint32_t)Address,Data);
			}
			break;
			
		case 6:
			EraseInitStruct.PageAddress = LOADCELL_INFO_START_ADDR;
			EraseInitStruct.NbPages     = (LOADCELL_INFO_END_ADDR - LOADCELL_INFO_START_ADDR) / FLASH_PAGE_SIZE;
			HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError); 
			ptr = (uint32_t*)&LOADCELL_INFO;	
			for( i=0 ; i < sizeof(LOADCELL_INFO); i++)
			{  
				Address = (uint32_t*)LOADCELL_INFO_START+i;
				Data = *((uint32_t*)ptr+i);
				HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,(uint32_t)Address,Data);
			}
			break;
		}
  	HAL_FLASH_Lock(); // lock
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET); HAL_Delay(100);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET); HAL_Delay(100);	
}

/* ------------------------------ SOL RUN --------------------------------------------  */
//PACKER SOL SELECTE
void SOL_RUN_SELECTE(uint8_t selcte1)
{
//  int selcte = selcte1;
	
	switch(selcte1)
	{
		case 1: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
			break;		
		case 2: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
			break;		
		case 3: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
			break;		
		case 4: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
			break;		
		case 5: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
			break;		
		case 6: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);
			break;		
		case 7: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
			break;		
		case 8: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
			break;		
		case 9: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
			break;		
		case 10: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
			break;		
		case 11: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);
			break;		
		case 12: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_SET);
			break;		
		case 13: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET);
			break;		
		case 14: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);		 
			break;		
		case 15: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);	
			break;		
		case 16: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET);
			break;		
		case 17: 
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
			break;		
		case 18: 
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
			break;		
		case 19: 
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
			break;		
		case 20: 
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
			break;		
		case 21: 
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
			break;		
		case 22: 
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
			break;		
		case 23: 
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
			break;		
		case 24: 
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
			break;
	}
}
//END PACKER SOL SELECTE

//RUN SOL TEST 
void SOL_RUN_(uint8_t selcte1)
{
  int selcte =(int)selcte1;
	
	switch(selcte)
	{
			case 1:
				/*-------------SOL_1-1-------------------*/
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
				DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
				break;
			case 2:
				/*-------------SOL_1-2-------------------*/
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
				DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
				break;
			case 3:
				/*-------------SOL_1-3-------------------*/		
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
				DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
				break;
			case 4:
				/*-------------SOL_1-4-------------------*/
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
				DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
			  break;
			case 5:
				/*-------------SOL_1-5-------------------*/
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
				DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
			 break;
			case 6:
				/*-------------SOL_1-6-------------------*/
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);
				DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
			  break;
			case 7:
				/*-------------SOL_1-7-------------------*/
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
				DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
			  break;
			case 8:
				/*-------------SOL_1-8-------------------*/
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
				DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
			  break;
			case 9:
				/*-------------SOL_2-1-------------------*/
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
				DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
				break;
			case 10:
				/*-------------SOL_2-2-------------------*/
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
				DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);
				break;
			case 11:
				/*-------------SOL_2-3-------------------*/
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);
				DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);
			case 12:
				/*-------------SOL_2-4-------------------*/
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_SET);
				DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_RESET);
				break;
			case 13:
				/*-------------SOL_2-5-------------------*/
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET);
				DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);
				break;
			case 14:
				/*-------------SOL_2-6-------------------*/
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
				DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
				break;
			case 15:
				/*-------------SOL_2-7-------------------*/
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);
				DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET);
				break;
			case 16:
				/*-------------SOL_2-8-------------------*/
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET);
				DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET);
				break;
			case 17:
				/*-------------SOL_3-1-------------------*/
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
				DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
				break;
			case 18:
				/*-------------SOL_3-2-------------------*/
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
				DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
				break;
			case 19:
				/*-------------SOL_3-3-------------------*/
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
				DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
				break;
			case 20:
				/*-------------SOL_3-4-------------------*/
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
				DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
				break;
			case 21:
				/*-------------SOL_3-5-------------------*/
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
				DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
				break;
			case 22:
				/*-------------SOL_3-6-------------------*/
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
				DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
				break;
			case 23:
				/*-------------SOL_3-7-------------------*/
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
				DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
				break;
			case 24:
				/*-------------SOL_3-8-------------------*/
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
				DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);	
				break;			
	}
}
//END SOL TEST 

// ALL PACKER SOL OFF
void SOL_RUN_OFF()
{		
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);		
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);		
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);			
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);		
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);		
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);	
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);	
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);	
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);	
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);	
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);	
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_RESET);		
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);		
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);	
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET);	
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET);	
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);	
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);	
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);	
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);		
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
	}
	
//RUN PACKER SOL  	
void SOL_RUN(void)
{	
	for(int i = 0; i < MAX_PACKER; i++)
	{
		for(int j = 0; j < MAX_PACKER_SOL; j++)
		{
			if(RearLine[PACKER_INFO[i].SOL_NUMBER[j]] == PACKER_INFO[i].SOL_NUMBER[j] && PACKER_INFO[i].SOL_NUMBER[j] !=0)
			{
					SOL_RUN_SELECTE(PACKER_INFO[i].SOL_CONNECT[j]);
					RearLine[PACKER_INFO[i].SOL_NUMBER[j]] = NORUN;
			}
		}
	}		
	if(RearLine_Prt[MARKING_INFO.MARKING_1_BURKET_NUM] == MARKING_INFO.MARKING_1_BURKET_NUM)
	{
		SOL_RUN_SELECTE(MARKING_INFO.MARKING_1_CONNECT);
		RearLine_Prt[MARKING_INFO.MARKING_1_BURKET_NUM] = NORUN;
	}		
		
	if(RearLine_Prt[MARKING_INFO.MARKING_2_BURKET_NUM] == MARKING_INFO.MARKING_2_BURKET_NUM)
	{
		SOL_RUN_SELECTE(MARKING_INFO.MARKING_2_CONNECT);
		RearLine_Prt[MARKING_INFO.MARKING_2_BURKET_NUM] = NORUN;
	}				
}
//END PACKER SOL 
/* ------------------------------ SOL TEST --------------------------------------------  */
void SOL_TEST_RUN()
{
	/*-------------SOL_1-1-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
	DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
	/*-------------SOL_1-2-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
	DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
	/*-------------SOL_1-3-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
	DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
	/*-------------SOL_1-4-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
	DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
	/*-------------SOL_1-5-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
	DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
	/*-------------SOL_1-6-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);
	DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
	/*-------------SOL_1-7-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
	DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
	/*-------------SOL_1-8-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
	DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
	/*-------------SOL_2-1-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
	DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
	/*-------------SOL_2-2-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
	DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);
	/*-------------SOL_2-3-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);
	DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);
	/*-------------SOL_2-4-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_SET);
	DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_RESET);
	/*-------------SOL_2-5-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET);
	DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);
	/*-------------SOL_2-6-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
	DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
	/*-------------SOL_2-7-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);
	DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET);
	/*-------------SOL_2-8-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET);
	DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET);
	/*-------------SOL_3-1-------------------*/
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
	DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
	/*-------------SOL_3-2-------------------*/
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
	DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	/*-------------SOL_3-3-------------------*/
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
	DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
	/*-------------SOL_3-4-------------------*/
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
	DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
	/*-------------SOL_3-5-------------------*/
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
	DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
	/*-------------SOL_3-6-------------------*/
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
	DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
	/*-------------SOL_3-7-------------------*/
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
	DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
	/*-------------SOL_3-8-------------------*/
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
	DWT_Delay_ms(SOL_RUN_TIME_INFO.SOL_OFF_TIME_-SOL_RUN_TIME_INFO.SOL_ON_TIME_);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
}

/* ---------------------GRADER_INIT-----------------------*/

/* ---------------------END-----------------------*/

/* ------------------Loadcell params--------------*/
unsigned int avg = 0;
unsigned int avg_real = 0;
unsigned int avg_volt = 0;
float avg_float = 0;
unsigned int time_count = 0;
/* ---------------------END-----------------------*/

/* ------------------------------LoadCell Params--------------------------------  */
unsigned int LOADCELL_ZERO(void)
{
	int i = 0 ;
	unsigned int avg_zero = 0;
	for(i = 0; i <= 100; i++)
  {	
		avg_zero += filtereadValue;
		DWT_Delay_ms(1);
	}
	avg_zero = avg_zero/i;
	avg_zero = ceil(avg_zero*10)/10;
	return avg_zero;
}

float LOADCELL_SPAN(unsigned int ZERO)
{
	int i; 
	float avg_weight = 0;
	
	for(i = 0; i <= 100; i++)
	{
		avg_weight += filtereadValue;
		DWT_Delay_ms(1);
	}
	avg_weight = avg_weight/i;
	avg_weight = 50/(avg_weight-ZERO);
	avg_weight = ceil(avg_weight*10000)/10000;
	return avg_weight;
}

float LOADCELL_WEIGHT(unsigned int ZERO, float SPAN)
{
	int i = 0; 
	float avg_weight = 0;
	
	for(i = 0; i <= 100; i++)
	{
		avg_weight += filtereadValue;
		DWT_Delay_ms(1);
	}
  avg_weight = avg_weight/i;	
	avg_weight = (avg_weight-ZERO)*SPAN;
	avg_weight = ceil(avg_weight*10)/10;
	
	
	return avg_weight;
}


/* ---------------------END-----------------------  */

void BUZZER_ON_OFF(void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET); HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET); HAL_Delay(100);	
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  uint32_t ReceiveDATA, TX_DATA = 0, RX_DATA = 0;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  DWT_Delay_Init();
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART3_UART_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
	
  HAL_TIM_OC_Start_IT(&htim3,TIM_CHANNEL_1);
  HAL_ADC_Start(&hadc1);
//  HAL_ADC_Stop(&hadc1);
	HAL_NVIC_EnableIRQ(USART1_IRQn);
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);
 // __HAL_UART_ENABLE_IT(&huart1,UART_IT_TC);
 
 
	//RUNING TIME
	for(int jcnt=0;jcnt<40;jcnt++)
	{
				if((jcnt%2)==0)
				{
					 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET); HAL_Delay(50);
					 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET); HAL_Delay(50);
					 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET); HAL_Delay(50);
				}
				else
				{
					 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET); HAL_Delay(50);
					 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET); HAL_Delay(50);
					 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET); HAL_Delay(50);
				}   	
	}
	BUZZER_ON_OFF();
	BUZZER_ON_OFF();
	
	 

// Using data stored in flash memory
	memcpy(&GRADE_INFO ,GRADE_INFO_START  ,sizeof(GRADE_INFO));
	memcpy(&PACKER_INFO ,PACKER_INFO_START  ,sizeof(PACKER_INFO));
	memcpy(&MARKING_INFO  ,MARKING_INFO_START  ,sizeof(MARKING_INFO));
	memcpy(&SOL_RUN_TIME_INFO  ,SOL_RUN_TIME_INFO_START  ,sizeof(SOL_RUN_TIME_INFO));
	memcpy(&MEASUREMENT_INFO ,MEASUREMENT_INFO_START ,sizeof(MEASUREMENT_INFO));
	memcpy(&LOADCELL_INFO  ,LOADCELL_INFO_START   ,sizeof(LOADCELL_INFO));
	 
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET); 
	
	G_DATA_TYPE GRADE_DATA_TMP;
	G_DATA_TYPE GRADE_DATA_INIT = {0};
	
// Number of GRADE and PACKER END (Interrupt applied)	
	uint8_t k;
	k = 0;

	for(int i = 0; i < MAX_GRADE-1;i++)
	{
		P_SOL_CNT[i]=PACKER_INFO[i].SOL_COUNT;
		for(int j = 0; j < MAX_PACKER; j++ )
		{
			if(GRADE_INFO[i].PACKER_NUMBER[j]==1)
			{
				GRADE_PACKER[i][k++] = j;
			}
		}
		for(int j = 0; j < MAX_PACKER - GRADE_INFO[i].PACKER_COUNT; j++ )
		{
				GRADE_PACKER[i][k++] = 0;
		}
		k=0;		
	}
	
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7) == 1)  //AUTO 모드로 수정
	{         
		RUN_ACTIVE_NUM = RUN_ACTIVE;   
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);	
	}		
	 uint8_t size = 0;
	
	 uint32_t tmp; 
	
	 RUN_ACTIVE_NUM = RUN_ACTIVE;
  /* USER CODE END 2 */
	
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */ 
		/*---------------MODE SECTION------------------------*/	   
	 	switch (run_data[0])  
		{
/*---------------READ SECTION START--------------------------*/				
			case READ :  
				switch (run_data[1]) 
				{
					case GRADE_INFO_:	 /* GRADE_INFO_ VALUE SEND*/		
						RUN_ACTIVE_NUM = GRADE_INFO_;					
						txbuff_SEND[STX_NUM] = STX;	
						TX_DATA = LEN_NUM;
					  TX_DATA++;
						for(int j = 0; j < MAX_GRADE; j++)
						{
							txbuff_SEND[TX_DATA++] = (uint8_t)(*((uint32_t*)&GRADE_INFO[j].HILIMIT ) >> 24);		
							txbuff_SEND[TX_DATA++] = (uint8_t)(*((uint32_t*)&GRADE_INFO[j].HILIMIT ) >> 16);		
							txbuff_SEND[TX_DATA++] = (uint8_t)(*((uint32_t*)&GRADE_INFO[j].HILIMIT ) >> 8);
							txbuff_SEND[TX_DATA++] = (uint8_t)(*((uint32_t*)&GRADE_INFO[j].HILIMIT ));	
							
							txbuff_SEND[TX_DATA++] = (uint8_t)(*((uint32_t*)&GRADE_INFO[j].LOLIMIT ) >> 24);		
							txbuff_SEND[TX_DATA++] = (uint8_t)(*((uint32_t*)&GRADE_INFO[j].LOLIMIT ) >> 16);		
							txbuff_SEND[TX_DATA++] = (uint8_t)(*((uint32_t*)&GRADE_INFO[j].LOLIMIT ) >> 8);
							txbuff_SEND[TX_DATA++] = (uint8_t)(*((uint32_t*)&GRADE_INFO[j].LOLIMIT ));
							
						  txbuff_SEND[TX_DATA++] = (uint8_t)(*((uint32_t*)&GRADE_INFO[j].PRT_COUNT ) >> 24);		
							txbuff_SEND[TX_DATA++] = (uint8_t)(*((uint32_t*)&GRADE_INFO[j].PRT_COUNT ) >> 16);		
							txbuff_SEND[TX_DATA++] = (uint8_t)(*((uint32_t*)&GRADE_INFO[j].PRT_COUNT ) >> 8);
							txbuff_SEND[TX_DATA++] = (uint8_t)(*((uint32_t*)&GRADE_INFO[j].PRT_COUNT ));								
							txbuff_SEND[TX_DATA++] = GRADE_INFO[j].PRT_USED;	
							
							txbuff_SEND[TX_DATA++] = GRADE_INFO[j].PACKER_COUNT;							
							for(int k = 0; k < MAX_PACKER; k++)
							{
								txbuff_SEND[TX_DATA++] = GRADE_INFO[j].PACKER_NUMBER[k];
							}			
			
						}
						for(int k = 0; k < MAX_PACKER; k++)
						{
								txbuff_SEND[TX_DATA++] = PACKER_INFO[k].SOL_COUNT;
						}	
					
					  txbuff_SEND[LEN_NUM] = TX_DATA-2;
						txbuff_SEND[TX_DATA++] = ETX;	
						HAL_UART_Transmit(&huart1,txbuff_SEND,TX_DATA,50);	
						BUZZER_ON_OFF();	
						memcpy(run_data,init_run_data,sizeof(init_run_data));	
						break;
						
					case PACKER_INFO_:	   /* PACKER_INFO_ VALUE SEND*/	
						RUN_ACTIVE_NUM = PACKER_INFO_;	
						txbuff_SEND[STX_NUM] = STX;	
						TX_DATA = LEN_NUM;
					  TX_DATA++; 
						for(int j = 0; j < MAX_PACKER; j++)
						{
								txbuff_SEND[TX_DATA++] = PACKER_INFO[j].SOL_COUNT;	
								for(int k = 0; k < MAX_PACKER_SOL; k++)
								{
									txbuff_SEND[TX_DATA++]=PACKER_INFO[j].SOL_NUMBER[k];													
								}
								for(int k = 0; k < MAX_PACKER_SOL; k++)
								{
									txbuff_SEND[TX_DATA++]=PACKER_INFO[j].SOL_CONNECT[k];	
								}
						}	

						txbuff_SEND[TX_DATA++]=MARKING_INFO.MARKING_1_BURKET_NUM;
						txbuff_SEND[TX_DATA++]=MARKING_INFO.MARKING_1_CONNECT;
						txbuff_SEND[TX_DATA++]=MARKING_INFO.MARKING_2_BURKET_NUM;
						txbuff_SEND[TX_DATA++]=MARKING_INFO.MARKING_2_CONNECT;
						txbuff_SEND[TX_DATA++]=SOL_RUN_TIME_INFO.SOL_ON_TIME_;
						txbuff_SEND[TX_DATA++]=SOL_RUN_TIME_INFO.SOL_OFF_TIME_;						
					
						txbuff_SEND[LEN_NUM] = TX_DATA-2;
						txbuff_SEND[TX_DATA++] = ETX;	
						
						HAL_UART_Transmit(&huart1,txbuff_SEND,TX_DATA,50);	
						BUZZER_ON_OFF();
						memcpy(run_data,init_run_data,sizeof(init_run_data));	           				
						break;	
						
				 
					case MEASUREMENT_INFO_:	 /* MEASUREMENT_INFO_ VALUE SEND*/	
						RUN_ACTIVE_NUM = MEASUREMENT_INFO_;		
						txbuff_SEND[STX_NUM] = STX;
						TX_DATA = LEN_NUM;
						TX_DATA++;
					  txbuff_SEND[TX_DATA++] = MEASUREMENT_INFO.START_TIME;
					  txbuff_SEND[TX_DATA++] = MEASUREMENT_INFO.END_TIME;
						txbuff_SEND[LEN_NUM] = TX_DATA-2;
						txbuff_SEND[TX_DATA++] = ETX;	
						HAL_UART_Transmit(&huart1,txbuff_SEND,TX_DATA,50); 	
						BUZZER_ON_OFF();	
						memcpy(run_data,init_run_data,sizeof(init_run_data));	
						break;		
						
					case LOADCELL_INFO_:	  /* INIT_CONFIG VALUE SEND*/	
						RUN_ACTIVE_NUM = LOADCELL_INFO_;									   
					  avg_float = LOADCELL_WEIGHT(LOADCELL_INFO.OFFSET,LOADCELL_INFO.SPAN);
					  BUZZER_ON_OFF();
						txbuff_SEND[STX_NUM] = STX;	
						TX_DATA = LEN_NUM;
					  TX_DATA++;					
					  txbuff_SEND[TX_DATA++] = (uint8_t)(*((uint32_t*)&avg_float ) >> 24);		
						txbuff_SEND[TX_DATA++] = (uint8_t)(*((uint32_t*)&avg_float ) >> 16);		
						txbuff_SEND[TX_DATA++] = (uint8_t)(*((uint32_t*)&avg_float ) >> 8);
						txbuff_SEND[TX_DATA++] = (uint8_t)(*((uint32_t*)&avg_float ));	
					  txbuff_SEND[TX_DATA++] = (uint8_t)(*((uint32_t*)&LOADCELL_INFO.OFFSET ) >> 24);		
						txbuff_SEND[TX_DATA++] = (uint8_t)(*((uint32_t*)&LOADCELL_INFO.OFFSET ) >> 16);		
						txbuff_SEND[TX_DATA++] = (uint8_t)(*((uint32_t*)&LOADCELL_INFO.OFFSET ) >> 8);
						txbuff_SEND[TX_DATA++] = (uint8_t)(*((uint32_t*)&LOADCELL_INFO.OFFSET ));	
					  txbuff_SEND[TX_DATA++] = (uint8_t)(*((uint32_t*)&LOADCELL_INFO.SPAN ) >> 24);		
						txbuff_SEND[TX_DATA++] = (uint8_t)(*((uint32_t*)&LOADCELL_INFO.SPAN ) >> 16);		
						txbuff_SEND[TX_DATA++] = (uint8_t)(*((uint32_t*)&LOADCELL_INFO.SPAN ) >> 8);
						txbuff_SEND[TX_DATA++] = (uint8_t)(*((uint32_t*)&LOADCELL_INFO.SPAN ));	
					  txbuff_SEND[TX_DATA++] = (uint8_t)(*((uint32_t*)&LOADCELL_INFO.MOVING_AVRAGE ) >> 24);		
						txbuff_SEND[TX_DATA++] = (uint8_t)(*((uint32_t*)&LOADCELL_INFO.MOVING_AVRAGE ) >> 16);		
						txbuff_SEND[TX_DATA++] = (uint8_t)(*((uint32_t*)&LOADCELL_INFO.MOVING_AVRAGE ) >> 8);
						txbuff_SEND[TX_DATA++] = (uint8_t)(*((uint32_t*)&LOADCELL_INFO.MOVING_AVRAGE ));	
						txbuff_SEND[LEN_NUM] = TX_DATA-2;		
						txbuff_SEND[TX_DATA++] = ETX;	
						HAL_UART_Transmit(&huart1,txbuff_SEND,TX_DATA,50); 
						BUZZER_ON_OFF();				
						memcpy(run_data,init_run_data,sizeof(init_run_data));		         				
						break;
						
					case ALL_INFO_:	  /* INIT_CONFIG VALUE SEND*/	
						RUN_ACTIVE_NUM = ALL_INFO_;	
						BUZZER_ON_OFF();
						BUZZER_ON_OFF();
						memcpy(run_data,init_run_data,sizeof(init_run_data));		         				
						break;			
					case COM_CHK_:	  /* INIT_CONFIG VALUE SEND*/	
						RUN_ACTIVE_NUM = ALL_INFO_;	
						BUZZER_ON_OFF();
					  txbuff_SEND[STX_NUM] = STX;	
						TX_DATA = LEN_NUM;
					  TX_DATA++;					
            txbuff_SEND[TX_DATA++] = 51; 					
						txbuff_SEND[LEN_NUM] = TX_DATA-2;		
						txbuff_SEND[TX_DATA++] = ETX;	
						HAL_UART_Transmit(&huart1,txbuff_SEND,TX_DATA,50); 
						BUZZER_ON_OFF();
						memcpy(run_data,init_run_data,sizeof(init_run_data));		         				
						break;						
				}
			break;
/*---------------READ SECTION END--------------------------*/		
					
/*---------------SET START--------------------------*/					
			case WRITE : // WRITE
				switch (run_data[1])	
				{
					case GRADE_INFO_:
							RUN_ACTIVE_NUM = GRADE_INFO_;
					    BUZZER_ON_OFF();
							ReceiveDATA = 2;
					   
							for (int i = 0; i < MAX_GRADE; i++)
							{
								tmp  =   run_data[ReceiveDATA++];
								tmp +=   ((run_data[ReceiveDATA++]&0xFF)<<8);
								tmp +=   ((run_data[ReceiveDATA++]&0xFF)<<16);
								tmp +=   ((run_data[ReceiveDATA++]&0xFF)<<24);										
								GRADE_INFO[i].HILIMIT = *((float*)&tmp);
								GRADE_INFO[i].HILIMIT = ceil(GRADE_INFO[i].HILIMIT*10)/10;
								
								tmp  =   run_data[ReceiveDATA++];
								tmp +=   ((run_data[ReceiveDATA++]&0xFF)<<8);
								tmp +=   ((run_data[ReceiveDATA++]&0xFF)<<16);
								tmp +=   ((run_data[ReceiveDATA++]&0xFF)<<24);								
								GRADE_INFO[i].LOLIMIT = *((float*)&tmp);
							  GRADE_INFO[i].LOLIMIT = ceil(GRADE_INFO[i].LOLIMIT*10)/10;
								
								GRADE_INFO[i].PRT_COUNT = 0;
                GRADE_INFO[i].PRT_COUNT =    (((uint32_t)run_data[ReceiveDATA++] & 0xFF));							
								GRADE_INFO[i].PRT_COUNT +=   (((uint32_t)run_data[ReceiveDATA++] & 0xFF) << 8);
								GRADE_INFO[i].PRT_COUNT +=   (((uint32_t)run_data[ReceiveDATA++] & 0xFF) << 16);
								GRADE_INFO[i].PRT_COUNT +=   (((uint32_t)run_data[ReceiveDATA++] & 0xFF) << 24);	
								if(GRADE_INFO[i].PRT_COUNT != 0)
								{
									GRADE_INFO[i].PRT_COUNT = GRADE_INFO[i].PRT_COUNT+2;
								}
								GRADE_INFO[i].PRT_USED = run_data[ReceiveDATA++];
							    
								GRADE_INFO[i].PACKER_COUNT = run_data[ReceiveDATA++];	
								for(int j = 0 ; j < MAX_PACKER; j++)
								{
									GRADE_INFO[i].PACKER_NUMBER[j] = run_data[ReceiveDATA++];
								}	
							}			
							for(int j = 0 ; j < MAX_PACKER; j++)
							{
									PACKER_INFO[j].SOL_COUNT = run_data[ReceiveDATA++];
							}			
							FLASH_UPDATE(GRADE_INFO_DATA);
							FLASH_UPDATE(PACKER_INFO_DATA);
							k = 0;
							for(int i = 0; i < MAX_PACKER; i++)
							{
								for(int j = 0; j < MAX_PACKER; j++ )
								{
									if(GRADE_INFO[i].PACKER_NUMBER[j]==1)
									{
										GRADE_PACKER[i][k++] = j;
									}
								}
								for(int j = 0; j < MAX_PACKER - GRADE_INFO[i].PACKER_COUNT; j++ )
								{
										GRADE_PACKER[i][k++] = 0;
								}
								k=0;		
							}
							memset(G_PACKER_CNT,0,MAX_PACKER);
							memcpy(run_data,init_run_data,sizeof(init_run_data));						
						break;
							
					case PACKER_INFO_:
							RUN_ACTIVE_NUM = PACKER_INFO_;	
							BUZZER_ON_OFF();
							ReceiveDATA = 2;
							for (int i = 0; i <MAX_PACKER; i++)
							{
								PACKER_INFO[i].SOL_COUNT = run_data[ReceiveDATA++];								
								
								for(int j = 0 ; j < MAX_PACKER_SOL; j++)
								{
									PACKER_INFO[i].SOL_NUMBER[j] = run_data[ReceiveDATA++];								
								}
								for(int j = 0 ; j < MAX_PACKER_SOL; j++)
								{
									PACKER_INFO[i].SOL_CONNECT[j] = run_data[ReceiveDATA++];
								}
							}	
							MARKING_INFO.MARKING_1_BURKET_NUM = run_data[ReceiveDATA++];
							MARKING_INFO.MARKING_1_CONNECT = run_data[ReceiveDATA++];
							MARKING_INFO.MARKING_2_BURKET_NUM = run_data[ReceiveDATA++];
							MARKING_INFO.MARKING_2_CONNECT = run_data[ReceiveDATA++];
							
							SOL_RUN_TIME_INFO.SOL_ON_TIME_ = run_data[ReceiveDATA++];
							SOL_RUN_TIME_INFO.SOL_OFF_TIME_ = run_data[ReceiveDATA++];
							
							FLASH_UPDATE(PACKER_INFO_DATA);
							FLASH_UPDATE(MARKING_INFO_DATA);
							FLASH_UPDATE(SOL_RUN_TIME_INFO_DATA);
							for(int i = 0; i < MAX_PACKER; i++)
							{
								P_SOL_CNT[i]=PACKER_INFO[i].SOL_COUNT;
							}
							memcpy(run_data,init_run_data,sizeof(init_run_data));						
						break;
												
					case MEASUREMENT_INFO_: /* LOADCELL_CONFIG VALUE MEMORY SAVE [DELAY TIME/END TIME]*/	
							RUN_ACTIVE_NUM = MEASUREMENT_INFO_;	
							BUZZER_ON_OFF();
							ReceiveDATA = 2;
							MEASUREMENT_INFO.START_TIME = run_data[ReceiveDATA++];													
							MEASUREMENT_INFO.END_TIME =  run_data[ReceiveDATA++];	
							FLASH_UPDATE(MEASUREMENT_INFO_DATA);
							BUZZER_ON_OFF();					
							memcpy(run_data,init_run_data,sizeof(init_run_data));
						break;	
					
					case INIT_DATA_SET_:   /* INIT_DATA*/	
						RUN_ACTIVE_NUM = INIT_DATA_SET_;							
							for(int i; i < MAX_GRADE; i++)
							{
									GRADE_DATA.gNumber[i] = 0;
									GRADE_DATA.gWeight[i] = 0;
									GRADE_DATA.pNumber[i] = 0;	
							}
							GRADE_DATA.gTNumber = 0;
							GRADE_DATA.gTWeight = 0;
							GRADE_DATA.gPCount = 0;
							GRADE_DATA.gRCount = 0;
								
							HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET); HAL_Delay(100);
							HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET); HAL_Delay(100);
							memcpy(run_data,init_run_data,sizeof(init_run_data));					  	
						break;						
				}
			break;
/*---------------WRITE SECTION END--------------------------*/	
				
/*---------------RUN ACTIVE SECTION START--------------------------*/					
			case ACTIVE : 
				switch (run_data[1])	
				{
					case RUN_ACTIVE:	/* RUN_ACTIVE START*/	
						RUN_ACTIVE_NUM = RUN_ACTIVE;
						BUZZER_ON_OFF();
					  memcpy(run_data,init_run_data,sizeof(init_run_data));
					break;	
					
					case NORUN_ACTIVE:	/* RUN_ACTIVE STOP */	
						RUN_ACTIVE_NUM = NORUN_ACTIVE;		
						BUZZER_ON_OFF();				
					  memcpy(run_data,init_run_data,sizeof(init_run_data));
					break;					
				}	
			break;
/*---------------RUN ACTIVE SECTION END--------------------------*/		
				
/*---------------MEASUREMENT SECTION START--------------------------*/					
			case MEASUREMENT : 
				switch (run_data[1])	
				{
					case LOADCELL_INFO_ZERO_: 	/* LOADCELL_ZERO_MEASUREMENT START*/	
						RUN_ACTIVE_NUM = LOADCELL_INFO_ZERO_;						
						for(int i =0; i<5;i++)
						{
							LOADCELL_INFO.OFFSET=LOADCELL_ZERO();
						}						
						BUZZER_ON_OFF();	
						txbuff[0] = 0x02;	
						txbuff[1] = sizeof(LOADCELL_INFO.OFFSET);	
						txbuff[2] = (uint8_t)(*((uint32_t*)&LOADCELL_INFO.OFFSET ) >> 24);		
						txbuff[3] = (uint8_t)(*((uint32_t*)&LOADCELL_INFO.OFFSET ) >> 16);		
						txbuff[4] = (uint8_t)(*((uint32_t*)&LOADCELL_INFO.OFFSET ) >> 8);
						txbuff[5] = (uint8_t)(*((uint32_t*)&LOADCELL_INFO.OFFSET ));	
						txbuff[6] = 0x03;	
						FLASH_UPDATE(LOADCELL_INFO_DATA);
						HAL_UART_Transmit(&huart1,txbuff,3+sizeof(LOADCELL_INFO.OFFSET),10); 	
						memcpy(run_data,init_run_data,sizeof(init_run_data));
							
						break;						
					case LOADCELL_INFO_WEIGHT_: 	/* LOADCELL_WEIGHT_MEASUREMENT START */	
						RUN_ACTIVE_NUM = LOADCELL_INFO_WEIGHT_;					
					  for(int i =0; i<5;i++)
					  {
							LOADCELL_INFO.SPAN = LOADCELL_SPAN(LOADCELL_INFO.OFFSET);		
						}												
						BUZZER_ON_OFF();
						txbuff[0] = 0x02;	
						txbuff[1] =  sizeof(LOADCELL_INFO.SPAN);	
						txbuff[2] = (uint8_t)(*((uint32_t*)&LOADCELL_INFO.SPAN ) >> 24);		
						txbuff[3] = (uint8_t)(*((uint32_t*)&LOADCELL_INFO.SPAN ) >> 16);		
						txbuff[4] = (uint8_t)(*((uint32_t*)&LOADCELL_INFO.SPAN ) >> 8);
						txbuff[5] = (uint8_t)(*((uint32_t*)&LOADCELL_INFO.SPAN ));	
						txbuff[6] = 0x03;	
						HAL_UART_Transmit(&huart1,txbuff,3+sizeof(LOADCELL_INFO.SPAN),10);
						FLASH_UPDATE(LOADCELL_INFO_DATA);
						memcpy(run_data,init_run_data,sizeof(init_run_data));	
						break;		
					
					case MEASURE_RUN_:	/* LOADCELL_WEIGHT_MEASUREMENT START */	
						RUN_ACTIVE_NUM = MEASURE_RUN_;	
					  send_count = true;
					  sendvalue = false;
					  send_cnt =0;
						BUZZER_ON_OFF();
					  memset (data_strem, 0, sizeof(data_strem));
						memcpy(run_data,init_run_data,sizeof(init_run_data));
						break;
					
					case SOL_TEST_:	/* SOL_TEST START */	
						RUN_ACTIVE_NUM = SOL_TEST_;						
					  SOL_SELECT =run_data[2];							  
					  if (SOL_SELECT < 40)
						{
							SOL_RUN_(SOL_SELECT);
							memcpy(run_data,init_run_data,sizeof(init_run_data)); 
							SOL_SELECT = 0;	
						}
						else if (SOL_SELECT == 41)
						{
							SOL_TEST_RUN();							
						}
						else if (SOL_SELECT == 42)
						{			
							memcpy(run_data,init_run_data,sizeof(init_run_data)); 
							SOL_SELECT = 0;	
						}	
						BUZZER_ON_OFF();
						break;			
				}	
/*---------------MEASUREMENT SECTION END--------------------------*/	
				break;
/*----------------------MODE SECTION END--------------------------*/	
			}
    /* USER CODE BEGIN 3 */
			}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV2;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV16;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV8;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

 /* USER CODE BEGIN ADC1_Init 1 */

 /* USER CODE END ADC1_Init 1 */
  /** Common config 
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  //hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.ExternalTrigConv = ADC1_2_EXTERNALTRIG_T3_TRGO;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 3;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel 
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_55CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel 
  */
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel 
  */
  sConfig.Rank = ADC_REGULAR_RANK_3;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 36000-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 100;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_ENABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 72-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 100-1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_ENABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_0 
                          |GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4 
                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8 
                          |GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14 
                          |GPIO_PIN_15|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8|GPIO_PIN_11|GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC13 PC14 PC15 PC0 
                           PC1 PC2 PC3 PC4 
                           PC5 PC6 PC7 PC8 
                           PC9 PC10 PC11 PC12 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_0 
                          |GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4 
                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8 
                          |GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA3 PA4 PA5 PA6 
                           PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;                         
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin =  GPIO_PIN_7; 
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);



  /*Configure GPIO pins : PB0 PB1 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB2 PB12 PB13 PB14 
                           PB15 PB5 PB6 PB7 
                           PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14 
                          |GPIO_PIN_15|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7 
                          |GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA8 PA11 PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PD2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 4, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 4, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_IRQn, 4, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 4, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 4, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

//  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 4, 0);
//  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{		
	uint8_t data[200] = {0};
	uint32_t i_cnt =0, j =2;
	avg = 0;
	float resultData =0;
	uint32_t grade = MAX_GRADE+1;
	uint8_t data_count =0;
	uint8_t avg_cnt =0;
	uint8_t SEL_PACKER = 9;
	
	if (RUN_ACTIVE_NUM == RUN_ACTIVE)
	{
		for (i_cnt = 0; i_cnt <= 255; i_cnt++)
		{
			if (i_cnt == SOL_RUN_TIME_INFO.SOL_ON_TIME_)
			{
					SOL_RUN();
			}	
			
			if (i_cnt == (SOL_RUN_TIME_INFO.SOL_ON_TIME_+SOL_RUN_TIME_INFO.SOL_OFF_TIME_))
			{
					SOL_RUN_OFF();
			}	
			
			if ( i_cnt >=  MEASUREMENT_INFO.START_TIME && i_cnt <= MEASUREMENT_INFO.END_TIME)
			{
				avg += filtereadValue;
				avg_cnt++;
			}		
			
			if(i_cnt == MEASUREMENT_INFO.END_TIME)
			{
				resultData = avg/avg_cnt;
				resultData = (resultData-LOADCELL_INFO.OFFSET)*LOADCELL_INFO.SPAN;
				resultData = ceil(resultData*10)/10;
			}			
			
			if(i_cnt == MEASUREMENT_INFO.END_TIME+1)
			{
					RearLine[0] =0;
					if(resultData <= GRADE_INFO[GRADE_1].HILIMIT && resultData >= GRADE_INFO[GRADE_1].LOLIMIT)
					{
						grade = GRADE_1;
						///////////////////////SET MARKING//////////////////////////////////////
						switch(GRADE_INFO[grade].PRT_USED)
						{
							case PRT_NO:
								RearLine_Prt[0] = 0;	
								break;				
							
							case PRT_A:
								if(GRADE_INFO[grade].PRT_COUNT == 0)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_1_BURKET_NUM;
								}
								else if(GRADE_INFO[grade].PRT_COUNT >= 1)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_1_BURKET_NUM;
									GRADE_INFO[grade].PRT_COUNT--;							
									if(GRADE_INFO[grade].PRT_COUNT == 1)
									{
										RearLine_Prt[0] = 0;
										GRADE_INFO[grade].PRT_USED = PRT_NO;								
									}
								}
								break;
								
							case PRT_B:
								if(GRADE_INFO[grade].PRT_COUNT == 0)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_2_BURKET_NUM;
								}
								else if(GRADE_INFO[grade].PRT_COUNT >= 1)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_2_BURKET_NUM;
									GRADE_INFO[grade].PRT_COUNT--;							
									if(GRADE_INFO[grade].PRT_COUNT == 1)
									{
										RearLine_Prt[0] = 0;
										GRADE_INFO[grade].PRT_USED = PRT_NO;								
									}
								}
								break;					
							}			
							///////////////SELECT PACKER////////////////////////////////
						  if(GRADE_INFO[grade].PACKER_COUNT > 0)
							{
								SEL_PACKER = GRADE_PACKER[grade][G_PACKER_CNT[grade]];
							}
					}
					else if(resultData <= GRADE_INFO[GRADE_2].HILIMIT &&  resultData >= GRADE_INFO[GRADE_2].LOLIMIT)
					{
						grade = GRADE_2;
						///////////////////////SET MARKING//////////////////////////////////////
						switch(GRADE_INFO[GRADE_2].PRT_USED)
						{
							case PRT_NO:
								RearLine_Prt[0] = 0;	
								break;				
							
							case PRT_A:
								if(GRADE_INFO[grade].PRT_COUNT == 0)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_1_BURKET_NUM;
								}
								else if(GRADE_INFO[grade].PRT_COUNT >= 1)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_1_BURKET_NUM;
									GRADE_INFO[grade].PRT_COUNT--;							
									if(GRADE_INFO[grade].PRT_COUNT == 1)
									{
										RearLine_Prt[0] = 0;
										GRADE_INFO[grade].PRT_USED = PRT_NO;								
									}
								}
								break;
								
							case PRT_B:
								if(GRADE_INFO[grade].PRT_COUNT == 0)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_2_BURKET_NUM;
								}
								else if(GRADE_INFO[grade].PRT_COUNT >= 1)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_2_BURKET_NUM;
									GRADE_INFO[grade].PRT_COUNT--;							
									if(GRADE_INFO[grade].PRT_COUNT == 1)
									{
										RearLine_Prt[0] = 0;
										GRADE_INFO[grade].PRT_USED = PRT_NO;								
									}
								}
								break;					
							}			
							///////////////SELECT PACKER////////////////////////////////
						  if(GRADE_INFO[grade].PACKER_COUNT > 0)
							{
								SEL_PACKER = GRADE_PACKER[grade][G_PACKER_CNT[grade]];
							}
					}
					else if(resultData <= GRADE_INFO[GRADE_3].HILIMIT &&  resultData >= GRADE_INFO[GRADE_3].LOLIMIT)
					{
						grade = GRADE_3;
						///////////////////////SET MARKING//////////////////////////////////////
						switch(GRADE_INFO[grade].PRT_USED)
						{
							case PRT_NO:
								RearLine_Prt[0] = 0;	
								break;				
							
							case PRT_A:
								if(GRADE_INFO[grade].PRT_COUNT == 0)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_1_BURKET_NUM;
								}
								else if(GRADE_INFO[grade].PRT_COUNT >= 1)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_1_BURKET_NUM;
									GRADE_INFO[grade].PRT_COUNT--;							
									if(GRADE_INFO[grade].PRT_COUNT == 1)
									{
										RearLine_Prt[0] = 0;
										GRADE_INFO[grade].PRT_USED = PRT_NO;								
									}
								}
								break;
								
							case PRT_B:
								if(GRADE_INFO[grade].PRT_COUNT == 0)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_2_BURKET_NUM;
								}
								else if(GRADE_INFO[grade].PRT_COUNT >= 1)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_2_BURKET_NUM;
									GRADE_INFO[grade].PRT_COUNT--;							
									if(GRADE_INFO[grade].PRT_COUNT == 1)
									{
										RearLine_Prt[0] = 0;
										GRADE_INFO[grade].PRT_USED = PRT_NO;								
									}
								}
								break;					
							}			
							///////////////SELECT PACKER////////////////////////////////
						  if(GRADE_INFO[grade].PACKER_COUNT > 0)
							{
								SEL_PACKER = GRADE_PACKER[grade][G_PACKER_CNT[grade]];
							}
					}
					else if(resultData <= GRADE_INFO[GRADE_4].HILIMIT &&  resultData >= GRADE_INFO[GRADE_4].LOLIMIT)
					{
						grade = GRADE_4;
						///////////////////////SET MARKING//////////////////////////////////////
						switch(GRADE_INFO[grade].PRT_USED)
						{
							case PRT_NO:
								RearLine_Prt[0] = 0;	
								break;				
							
							case PRT_A:
								if(GRADE_INFO[grade].PRT_COUNT == 0)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_1_BURKET_NUM;
								}
								else if(GRADE_INFO[grade].PRT_COUNT >= 1)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_1_BURKET_NUM;
									GRADE_INFO[grade].PRT_COUNT--;							
									if(GRADE_INFO[grade].PRT_COUNT == 1)
									{
										RearLine_Prt[0] = 0;
										GRADE_INFO[grade].PRT_USED = PRT_NO;								
									}
								}
								break;
								
							case PRT_B:
								if(GRADE_INFO[grade].PRT_COUNT == 0)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_2_BURKET_NUM;
								}
								else if(GRADE_INFO[grade].PRT_COUNT >= 1)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_2_BURKET_NUM;
									GRADE_INFO[grade].PRT_COUNT--;							
									if(GRADE_INFO[grade].PRT_COUNT == 1)
									{
										RearLine_Prt[0] = 0;
										GRADE_INFO[grade].PRT_USED = PRT_NO;								
									}
								}
								break;					
							}			
							///////////////SELECT PACKER////////////////////////////////
						  if(GRADE_INFO[grade].PACKER_COUNT > 0)
							{
								SEL_PACKER = GRADE_PACKER[grade][G_PACKER_CNT[grade]];
							}
						
					}
					else if(resultData <= GRADE_INFO[GRADE_5].HILIMIT && resultData >= GRADE_INFO[GRADE_5].LOLIMIT)
					{
						grade = GRADE_5;
						///////////////////////SET MARKING//////////////////////////////////////
						switch(GRADE_INFO[grade].PRT_USED)
						{
							case PRT_NO:
								RearLine_Prt[0] = 0;	
								break;				
							
							case PRT_A:
								if(GRADE_INFO[grade].PRT_COUNT == 0)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_1_BURKET_NUM;
								}
								else if(GRADE_INFO[grade].PRT_COUNT >= 1)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_1_BURKET_NUM;
									GRADE_INFO[grade].PRT_COUNT--;							
									if(GRADE_INFO[grade].PRT_COUNT == 1)
									{
										RearLine_Prt[0] = 0;
										GRADE_INFO[grade].PRT_USED = PRT_NO;								
									}
								}
								break;
								
							case PRT_B:
								if(GRADE_INFO[grade].PRT_COUNT == 0)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_2_BURKET_NUM;
								}
								else if(GRADE_INFO[grade].PRT_COUNT >= 1)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_2_BURKET_NUM;
									GRADE_INFO[grade].PRT_COUNT--;							
									if(GRADE_INFO[grade].PRT_COUNT == 1)
									{
										RearLine_Prt[0] = 0;
										GRADE_INFO[grade].PRT_USED = PRT_NO;								
									}
								}
								break;					
							}			
							///////////////SELECT PACKER////////////////////////////////
						  if(GRADE_INFO[grade].PACKER_COUNT > 0)
							{
								SEL_PACKER = GRADE_PACKER[grade][G_PACKER_CNT[grade]];
							}
					}
					else if(resultData <= GRADE_INFO[GRADE_6].HILIMIT && resultData >= GRADE_INFO[GRADE_6].LOLIMIT)
					{
						grade = GRADE_6;
						///////////////////////SET MARKING//////////////////////////////////////
						switch(GRADE_INFO[grade].PRT_USED)
						{
							case PRT_NO:
								RearLine_Prt[0] = 0;	
								break;				
							
							case PRT_A:
								if(GRADE_INFO[grade].PRT_COUNT == 0)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_1_BURKET_NUM;
								}
								else if(GRADE_INFO[grade].PRT_COUNT >= 1)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_1_BURKET_NUM;
									GRADE_INFO[grade].PRT_COUNT--;							
									if(GRADE_INFO[grade].PRT_COUNT == 1)
									{
										RearLine_Prt[0] = 0;
										GRADE_INFO[grade].PRT_USED = PRT_NO;								
									}
								}
								break;
								
							case PRT_B:
								if(GRADE_INFO[grade].PRT_COUNT == 0)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_2_BURKET_NUM;
								}
								else if(GRADE_INFO[grade].PRT_COUNT >= 1)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_2_BURKET_NUM;
									GRADE_INFO[grade].PRT_COUNT--;							
									if(GRADE_INFO[grade].PRT_COUNT == 1)
									{
										RearLine_Prt[0] = 0;
										GRADE_INFO[grade].PRT_USED = PRT_NO;								
									}
								}
								break;					
							}			
							///////////////SELECT PACKER////////////////////////////////
						  if(GRADE_INFO[grade].PACKER_COUNT > 0)
							{
								SEL_PACKER = GRADE_PACKER[grade][G_PACKER_CNT[grade]];
							}
					}
					else if(resultData <= GRADE_INFO[GRADE_7].HILIMIT &&  resultData >= GRADE_INFO[GRADE_7].LOLIMIT)
					{
						grade = GRADE_7;
						///////////////////////SET MARKING//////////////////////////////////////
						switch(GRADE_INFO[grade].PRT_USED)
						{
							case PRT_NO:
								RearLine_Prt[0] = 0;	
								break;				
							
							case PRT_A:
								if(GRADE_INFO[grade].PRT_COUNT == 0)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_1_BURKET_NUM;
								}
								else if(GRADE_INFO[grade].PRT_COUNT >= 1)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_1_BURKET_NUM;
									GRADE_INFO[grade].PRT_COUNT--;							
									if(GRADE_INFO[grade].PRT_COUNT == 1)
									{
										RearLine_Prt[0] = 0;
										GRADE_INFO[grade].PRT_USED = PRT_NO;								
									}
								}
								break;
								
							case PRT_B:
								if(GRADE_INFO[grade].PRT_COUNT == 0)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_2_BURKET_NUM;
								}
								else if(GRADE_INFO[grade].PRT_COUNT >= 1)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_2_BURKET_NUM;
									GRADE_INFO[grade].PRT_COUNT--;							
									if(GRADE_INFO[grade].PRT_COUNT == 1)
									{
										RearLine_Prt[0] = 0;
										GRADE_INFO[grade].PRT_USED = PRT_NO;								
									}
								}
								break;					
							}			
							///////////////SELECT PACKER////////////////////////////////

						  if(GRADE_INFO[grade].PACKER_COUNT > 0)
							{
								SEL_PACKER = GRADE_PACKER[grade][G_PACKER_CNT[grade]];
							}
						
					}
					else if(resultData <= GRADE_INFO[GRADE_8].HILIMIT && resultData >= GRADE_INFO[GRADE_8].LOLIMIT)
					{
						grade = GRADE_8;
						///////////////////////SET MARKING//////////////////////////////////////
						switch(GRADE_INFO[GRADE_8].PRT_USED)
						{
							case PRT_NO:
								RearLine_Prt[0] = 0;	
								break;				
							
							case PRT_A:
								if(GRADE_INFO[GRADE_8].PRT_COUNT == 0)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_1_BURKET_NUM;
								}
								else if(GRADE_INFO[GRADE_8].PRT_COUNT >= 1)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_1_BURKET_NUM;
									GRADE_INFO[GRADE_8].PRT_COUNT--;							
									if(GRADE_INFO[GRADE_8].PRT_COUNT == 1)
									{
										RearLine_Prt[0] = 0;
										GRADE_INFO[GRADE_8].PRT_USED = PRT_NO;								
									}
								}
								break;
								
							case PRT_B:
								if(GRADE_INFO[GRADE_8].PRT_COUNT == 0)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_2_BURKET_NUM;
								}
								else if(GRADE_INFO[GRADE_8].PRT_COUNT >= 1)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_2_BURKET_NUM;
									GRADE_INFO[GRADE_8].PRT_COUNT--;							
									if(GRADE_INFO[GRADE_8].PRT_COUNT == 1)
									{
										RearLine_Prt[0] = 0;
										GRADE_INFO[GRADE_8].PRT_USED = PRT_NO;								
									}
								}
								break;					
							}			
							///////////////SELECT PACKER////////////////////////////////
							if(GRADE_INFO[grade].PACKER_COUNT > 0)
							{
								SEL_PACKER = GRADE_PACKER[grade][G_PACKER_CNT[grade]];
							}
					}
					else if((resultData >= GRADE_INFO[ETC].HILIMIT || resultData <= GRADE_INFO[ETC].LOLIMIT) && resultData >= 10)
					{
						grade = ETC;
						///////////////////////SET MARKING//////////////////////////////////////
						switch(GRADE_INFO[ETC].PRT_USED)
						{
							case PRT_NO:
								RearLine_Prt[0] = 0;	
								break;				
							
							case PRT_A:
								if(GRADE_INFO[ETC].PRT_COUNT == 0)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_1_BURKET_NUM;
								}
								else if(GRADE_INFO[ETC].PRT_COUNT >= 1)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_1_BURKET_NUM;
									GRADE_INFO[ETC].PRT_COUNT--;							
									if(GRADE_INFO[ETC].PRT_COUNT == 1)
									{
										RearLine_Prt[0] = 0;
										GRADE_INFO[ETC].PRT_USED = PRT_NO;								
									}
								}
								break;
								
							case PRT_B:
								if(GRADE_INFO[ETC].PRT_COUNT == 0)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_2_BURKET_NUM;
								}
								else if(GRADE_INFO[ETC].PRT_COUNT >= 1)
								{
									RearLine_Prt[0] = MARKING_INFO.MARKING_2_BURKET_NUM;
									GRADE_INFO[ETC].PRT_COUNT--;							
									if(GRADE_INFO[ETC].PRT_COUNT == 1)
									{
										RearLine_Prt[0] = 0;
										GRADE_INFO[ETC].PRT_USED = PRT_NO;								
									}
								}
								break;					
							}			
					}
			}
				
				
		if( i_cnt == MEASUREMENT_INFO.END_TIME+1)
		{																			
			if(PACKER_INFO[SEL_PACKER].SOL_COUNT > 0 && SEL_PACKER != 9)
			{
				  RearLine[0] = PACKER_INFO[SEL_PACKER].SOL_NUMBER[P_SOL_CNT[SEL_PACKER]-1];
				  P_SOL_CNT[SEL_PACKER]--;
				  if(P_SOL_CNT[SEL_PACKER] == 0)
					{
						P_SOL_CNT[SEL_PACKER] = PACKER_INFO[SEL_PACKER].SOL_COUNT;
						
						if(GRADE_INFO[grade].PACKER_COUNT >  1)
						{
							G_PACKER_CNT[grade] +=1 ;						
						}
						
						if(G_PACKER_CNT[grade] > GRADE_INFO[grade].PACKER_COUNT-1)
						{
							G_PACKER_CNT[grade] = 0;
						}
						
					}
				}
			}
			if(i_cnt == MEASUREMENT_INFO.END_TIME+1) // SEND DATA SET
			{
				switch (grade)
				{
					case 0:
						GRADE_DATA.gNumber[GRADE_1]++;
						GRADE_DATA.gWeight[GRADE_1] += resultData; 
						GRADE_DATA.gTWeight += resultData;
						if(GRADE_INFO[GRADE_1].PRT_USED != 0)
						{
							GRADE_DATA.pNumber[GRADE_1]++;
						}
						GRADE_DATA.gTNumber++;					
						break;	
						
					case 1:
						GRADE_DATA.gNumber[GRADE_2]++;
						GRADE_DATA.gWeight[GRADE_2] += resultData; 
						GRADE_DATA.gTWeight += resultData;
						if(GRADE_INFO[GRADE_2].PRT_USED != 0)
						{
							GRADE_DATA.pNumber[GRADE_2]++;
						}
						GRADE_DATA.gTNumber++;
						break;	
						
					case GRADE_3:
						GRADE_DATA.gNumber[GRADE_3]++;
						GRADE_DATA.gWeight[GRADE_3] += resultData; 
						GRADE_DATA.gTWeight += resultData;
						if(GRADE_INFO[GRADE_3].PRT_USED != 0)
						{
							GRADE_DATA.pNumber[GRADE_3]++;
						}
						GRADE_DATA.gTNumber++;
						break;		
						
					case GRADE_4:
						GRADE_DATA.gNumber[GRADE_4]++;
						GRADE_DATA.gWeight[GRADE_4] += resultData; 
						GRADE_DATA.gTWeight += resultData;
						if(GRADE_INFO[GRADE_4].PRT_USED != 0)
						{
							GRADE_DATA.pNumber[GRADE_4]++;
						}
						GRADE_DATA.gTNumber++;
						break;
						
					case 4:
						GRADE_DATA.gNumber[GRADE_5]++;
						GRADE_DATA.gWeight[GRADE_5] += resultData; 
						GRADE_DATA.gTWeight += resultData;
						if(GRADE_INFO[GRADE_5].PRT_USED != 0)
						{
							GRADE_DATA.pNumber[GRADE_5]++;
						}
						GRADE_DATA.gTNumber++;
						break;
						
					case GRADE_6:
						GRADE_DATA.gNumber[GRADE_6]++;
						GRADE_DATA.gWeight[GRADE_6] += resultData; 
						GRADE_DATA.gTWeight += resultData;
						if(GRADE_INFO[GRADE_6].PRT_USED != 0)
						{
							GRADE_DATA.pNumber[GRADE_6]++;
						}
						GRADE_DATA.gTNumber++;
						break;
						
					case GRADE_7:
						GRADE_DATA.gNumber[GRADE_7]++;
						GRADE_DATA.gWeight[GRADE_7] += resultData; 
						GRADE_DATA.gTWeight += resultData;
						if(GRADE_INFO[GRADE_7].PRT_USED != 0)
						{
							GRADE_DATA.pNumber[GRADE_7]++;
						}
						GRADE_DATA.gTNumber++;
						break;
						
					case GRADE_8:
						GRADE_DATA.gNumber[GRADE_8]++;
						GRADE_DATA.gWeight[GRADE_8] += resultData; 
						GRADE_DATA.gTWeight += resultData;
						if(GRADE_INFO[GRADE_8].PRT_USED != 0)
						{
							GRADE_DATA.pNumber[GRADE_8]++;
						}
						GRADE_DATA.gTNumber++;
						break;
						
					case ETC:
						GRADE_DATA.gNumber[ETC]++;
						GRADE_DATA.gWeight[ETC] += resultData;
						GRADE_DATA.gTWeight += resultData;
						if(GRADE_INFO[ETC].PRT_USED != 0)
						{
							GRADE_DATA.pNumber[ETC]++;
						}
						GRADE_DATA.gTNumber++;
						break;							
				}									
				GRADE_DATA.gRCount=RearLine[0];
				GRADE_DATA.gPCount=RearLine_Prt[0];				 
				timerCnt++;
				GRADE_DATA.gSpeed = Grade_speed;
			} 

			
			if(i_cnt == MEASUREMENT_INFO.END_TIME+1) //Rear moving
			{
				memmove(RearLine+1,RearLine,sizeof(uint8_t)*REAR_COUNT-1);
				memmove(RearLine_Prt+1,RearLine_Prt,sizeof(uint8_t)*REAR_COUNT-1); 
			}
			
			if(i_cnt == MEASUREMENT_INFO.END_TIME+1)
			{				
				data[data_count++] = 0x02;
				data[data_count++] = 137; //128
				
				data[data_count++] = (uint8_t)(*((uint32_t*)&resultData) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&resultData) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&resultData) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)&resultData));	
				
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gSpeed) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gSpeed) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gSpeed) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gSpeed));

				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[0]) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[0]) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[0]) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[0]));	
				
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gWeight[0]) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gWeight[0]) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gWeight[0]) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)& GRADE_DATA.gWeight[0]));
				
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[1]) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[1]) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[1]) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[1]));	
				
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gWeight[1]) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gWeight[1]) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gWeight[1]) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)& GRADE_DATA.gWeight[1]));			

				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[2]) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[2]) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[2]) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[2]));	
				
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gWeight[2]) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gWeight[2]) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gWeight[2]) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)& GRADE_DATA.gWeight[2]));		
				
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[3]) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[3]) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[3]) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[3]));	
				
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gWeight[3]) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gWeight[3]) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gWeight[3]) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)& GRADE_DATA.gWeight[3]));		
				
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[4]) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[4]) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[4]) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[4]));	
				
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gWeight[4]) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gWeight[4]) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gWeight[4]) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)& GRADE_DATA.gWeight[4]));		
				
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[5]) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[5]) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[5]) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[5]));	
				
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gWeight[5]) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gWeight[5]) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gWeight[5]) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)& GRADE_DATA.gWeight[5]));		
				
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[6]) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[6]) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[6]) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[6]));	
				
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gWeight[6]) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gWeight[6]) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gWeight[6]) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)& GRADE_DATA.gWeight[6]));	
				
				
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[7]) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[7]) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[7]) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[7]));	
				
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gWeight[7]) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gWeight[7]) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gWeight[7]) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)& GRADE_DATA.gWeight[7]));		
				
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[8]) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[8]) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[8]) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gNumber[8]));	
				
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gWeight[8]) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gWeight[8]) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gWeight[8]) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)& GRADE_DATA.gWeight[8]));		
				
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gTNumber) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gTNumber) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gTNumber) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gTNumber));
				
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gTWeight) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gTWeight) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gTWeight) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gTWeight));
				
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gRCount));
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.gPCount));
								
				data[data_count++] = G_PACKER_CNT[SEL_PACKER];
				data[data_count++] = P_SOL_CNT[SEL_PACKER];
							
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[0]) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[0]) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[0]) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[0]));
				
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[1]) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[1]) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[1]) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[1]));
				
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[2]) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[2]) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[2]) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[2]));
				
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[3]) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[3]) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[3]) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[3]));
				
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[4]) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[4]) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[4]) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[4]));
				
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[5]) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[5]) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[5]) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[5]));
				
			  data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[6]) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[6]) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[6]) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[6]));
				
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[7]) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[7]) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[7]) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[7]));
				
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[8]) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[8]) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[8]) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)&GRADE_DATA.pNumber[8]));
											
				data[data_count++] = GRADE_INFO[0].PRT_USED;							
				data[data_count++] = GRADE_INFO[1].PRT_USED;
				data[data_count++] = GRADE_INFO[2].PRT_USED;
				data[data_count++] = GRADE_INFO[3].PRT_USED;
				data[data_count++] = GRADE_INFO[4].PRT_USED;
				data[data_count++] = GRADE_INFO[5].PRT_USED;
				data[data_count++] = GRADE_INFO[6].PRT_USED;
				data[data_count++] = GRADE_INFO[7].PRT_USED;
				data[data_count++] = GRADE_INFO[8].PRT_USED;	
											
											
				data[data_count++] = 0x03;	
				HAL_UART_Transmit(&huart1,data,data_count,20); 	 
			}								
			DWT_Delay_ms(1);
		}					
	}
	
	else if (RUN_ACTIVE_NUM == MEASURE_RUN_)
	{							      
				int i =0;		  		
				while(i < 250)
				{	
					resultData = (filtereadValue-LOADCELL_INFO.OFFSET)*LOADCELL_INFO.SPAN;
					resultData = ceil(resultData*10)/10;					
					if ( resultData > 20.0 && sendvalue == false && resultData < 100.0 && i <= 50 )
					{							
						sendvalue = true; 
					}      
					data_strem[j++] = (uint8_t)(*((uint32_t*)&resultData ) >> 24);		
					data_strem[j++] = (uint8_t)(*((uint32_t*)&resultData ) >> 16);		
					data_strem[j++] = (uint8_t)(*((uint32_t*)&resultData ) >> 8);
					data_strem[j++] = (uint8_t)(*((uint32_t*)&resultData ));			
					DWT_Delay_ms(1);
					i++;
				}							
				if(sendvalue == true && send_count == true)
				{	
					data_strem[0]= 0x10;
					data_strem[1]= 0x02;
					data_strem[j++] = 0x10;
					data_strem[j++] = 0x03;
					HAL_UART_Transmit(&huart1,data_strem,sizeof(data_strem),100);						
					send_count = false;
					sendvalue = false;
				}
	}
     
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
