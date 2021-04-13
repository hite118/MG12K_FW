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


#define MAGIC_NUM 0x00000001
#define nv_items ((NVitemTypeDef*)FLASH_USER_START_ADDR)
#define MEASUREMENT_DELAY 100
#define MEASUREMENT_END 200
#define GRADER_1_UL 79.9
#define GRADER_2_UL 74.9
#define GRADER_3_UL 69.9
#define GRADER_4_UL 64.9
#define GRADER_5_UL 59.9
#define GRADER_6_UL 54.9
#define GRADER_7_UL 49.9 
#define GRADER_8_UL 44.9
#define GRADER_1_LL 75.0
#define GRADER_2_LL 70.0
#define GRADER_3_LL 65.0
#define GRADER_4_LL 60.0
#define GRADER_5_LL 55.0
#define GRADER_6_LL 50.0
#define GRADER_7_LL 45.0 
#define GRADER_8_LL 40.0
#define OFF_SIZE_UL 80.0
#define OFF_SIZE_LL 39.9
#define LOADCELL_ZERO_VALUE 1793 
#define LOADCELL_WEIGHT_VALUE 0.08
#define SOL_ON_TIME 80
#define SOL_OFF_TIME 80
#define PACKER1_CH 1
#define PACKER2_CH 2
#define PACKER3_CH 3
#define PACKER4_CH 4
#define PACKER5_CH 5
#define PACKER6_CH 6
#define PACKER7_CH 7
#define PACKER8_CH 8
#define PACKER1_SOL_CNT 1
#define PACKER2_SOL_CNT 1
#define PACKER3_SOL_CNT 1
#define PACKER4_SOL_CNT 1
#define PACKER5_SOL_CNT 1
#define PACKER6_SOL_CNT 1
#define PACKER7_SOL_CNT 1
#define PACKER8_SOL_CNT 1

#define G1PACKER_CNT 1
#define G2PACKER_CNT 1
#define G3PACKER_CNT 1
#define G4PACKER_CNT 1
#define G5PACKER_CNT 1
#define G6PACKER_CNT 1
#define G7PACKER_CNT 1
#define G8PACKER_CNT 1

#define G1PACKER_NUM 1
#define G2PACKER_NUM 2
#define G3PACKER_NUM 3
#define G4PACKER_NUM 4
#define G5PACKER_NUM 5
#define G6PACKER_NUM 6
#define G7PACKER_NUM 7
#define G8PACKER_NUM 8


#define PACKER1SOL_RUN 8
#define PACKER2SOL_RUN 12
#define PACKER3SOL_RUN 22
#define PACKER4SOL_RUN 26
#define PACKER5SOL_RUN 36
#define PACKER6SOL_RUN 40
#define PACKER7SOL_RUN 50
#define PACKER8SOL_RUN 54

#define PACKER1SOL_CON 1
#define PACKER2SOL_CON 2
#define PACKER3SOL_CON 3
#define PACKER4SOL_CON 4
#define PACKER5SOL_CON 5
#define PACKER6SOL_CON 6
#define PACKER7SOL_CON 7
#define PACKER8SOL_CON 8

#define G1_PRT 0
#define G2_PRT 0
#define G3_PRT 0
#define G4_PRT 0
#define G5_PRT 0
#define G6_PRT 0
#define G7_PRT 0
#define G8_PRT 0
#define OFFSET_PRT 0

#define PRT1_RUN 0
#define PRT2_RUN 0
#define PRT1_CON 0
#define PRT2_CON 0

#define G1_PRT_QT_LIMIT 0
#define G2_PRT_QT_LIMIT 0
#define G3_PRT_QT_LIMIT 0
#define G4_PRT_QT_LIMIT 0
#define G5_PRT_QT_LIMIT 0
#define G6_PRT_QT_LIMIT 0
#define G7_PRT_QT_LIMIT 0
#define G8_PRT_QT_LIMIT 0
#define OFFSET_PRT_QT_LIMIT 0

//uint8_t G1PACKER_NUM = G1PACKER_NUM;
//uint8_t G2PACKER_NUM[PACKER2_SOL_CNT] = {2};
//uint8_t G3PACKER_NUM[PACKER3_SOL_CNT] = {3};
//uint8_t G4PACKER_NUM[PACKER4_SOL_CNT] = {4};
//uint8_t G5PACKER_NUM[PACKER5_SOL_CNT] = {5};
//uint8_t G6PACKER_NUM[PACKER6_SOL_CNT] = {6};
//uint8_t G7PACKER_NUM[PACKER7_SOL_CNT] = {7};
//uint8_t G8PACKER_NUM[PACKER8_SOL_CNT] = {8};

//for(int i =0 ; i <G1PACKER_CNT;i++)
//{
//	
//}

/* ------------------------------MODE-----------------------------------------*/
#define SEND 0x01
#define SET 0x02
#define ACTIVE 0x03
#define MEASUREMENT 0x04
/* ------------------------------END------------------------------------------*/

/* ------------------------------ACTION-----------------------------------------*/
#define RUN_ACTIVE 0x01
#define NORUN_ACTIVE 0x02

#define LOADCELL_SET_SEND 0x03
#define MEASUREMENT_SET 0x04

#define SOLENOIDE_SET_SEND 0x05
#define SOLENOIDE_SET 0x06

#define GRADE_SET_SEND 0x07
#define GRADE_SET 0x08

#define INIT_CFG_SEND 0x09
#define INIT_CFG_SET 0x11

#define LOADCELL_ZERO_MEASUREMENT 0x12
#define LOADCELL_WEIGHT_MEASUREMENT 0x13
#define GRADER_TIMING_MEASUREMENT 0x17

#define SOL_TEST_MEASUREMENT 0x15
#define CURENT_WEIGHT 0x16
#define CURENT_WEIGHT_NOFILTER 0x18
#define CURENT_WEIGHT_FILTER 0x19
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
#define FLASH_USER_START_ADDR  ADDR_FLASH_PAGE_79 // 0x08007C00
#define FLASH_USER_END_ADDR   ADDR_FLASH_PAGE_79 + FLASH_PAGE_SIZE
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


uint32_t SOL_SELECT = 0;

//uint32_t txbuff;
uint32_t filtereadValue=0, sensorValue;
uint32_t msTimer;
uint32_t timerCnt;
uint32_t Grade_speed;
uint32_t interuptCnt=0, startTime=0 , endTime=0;

uint32_t magic_num;

uint32_t Measurement_Delay ;
uint32_t Measurement_EndTime; 

float Grader_1_UL;
float Grader_2_UL;
float Grader_3_UL;
float Grader_4_UL;
float Grader_5_UL;
float Grader_6_UL;
float Grader_7_UL;
float Grader_8_UL;
float Off_size_UL;

float Grader_1_LL;
float Grader_2_LL;
float Grader_3_LL;
float Grader_4_LL;
float Grader_5_LL;
float Grader_6_LL;
float Grader_7_LL;
float Grader_8_LL;
float Off_size_LL;

// Loadcell_Zero;
unsigned int Loadcell_Zero;
float  Loadcell_Weight;

uint8_t SOL_RUN_1 = 8;
uint8_t SOL_RUN_2 = 12;
uint8_t SOL_RUN_3 = 22;
uint8_t SOL_RUN_4 = 26;
uint8_t SOL_RUN_5 = 36;
uint8_t SOL_RUN_6 = 40;
uint8_t SOL_RUN_7 = 54;
uint8_t SOL_RUN_8 = 58;

uint8_t Packer1Sol_Run[6];
uint8_t Packer2Sol_Run[6];
uint8_t Packer3Sol_Run[6];
uint8_t Packer4Sol_Run[6];
uint8_t Packer5Sol_Run[6];
uint8_t Packer6Sol_Run[6];
uint8_t Packer7Sol_Run[6];
uint8_t Packer8Sol_Run[6];

uint8_t Packer1Sol_Con[6];
uint8_t Packer2Sol_Con[6];
uint8_t Packer3Sol_Con[6];
uint8_t Packer4Sol_Con[6];
uint8_t Packer5Sol_Con[6];
uint8_t Packer6Sol_Con[6];
uint8_t Packer7Sol_Con[6];
uint8_t Packer8Sol_Con[6];

uint8_t RearLine [REAR_COUNT];
uint8_t Rear_Count = 1;

uint8_t RearLine_Prt [REAR_COUNT];
uint8_t Rear_Count_Prt = 1;


uint8_t Packer1_sol_cnt;
uint8_t Packer2_sol_cnt; 
uint8_t Packer3_sol_cnt;
uint8_t Packer4_sol_cnt;
uint8_t Packer5_sol_cnt;
uint8_t Packer6_sol_cnt;
uint8_t Packer7_sol_cnt; 
uint8_t Packer8_sol_cnt;
		
uint8_t Packer1_ch;
uint8_t Packer2_ch;
uint8_t Packer3_ch;
uint8_t Packer4_ch;
uint8_t Packer5_ch;
uint8_t Packer6_ch;
uint8_t Packer7_ch;
uint8_t Packer8_ch;

uint8_t G1PACKER_Cnt;
uint8_t G2PACKER_Cnt;
uint8_t G3PACKER_Cnt;
uint8_t G4PACKER_Cnt;
uint8_t G5PACKER_Cnt;
uint8_t G6PACKER_Cnt;
uint8_t G7PACKER_Cnt;
uint8_t G8PACKER_Cnt;

uint8_t G1PACKER_Num[8];
uint8_t G2PACKER_Num[8];
uint8_t G3PACKER_Num[8];
uint8_t G4PACKER_Num[8];
uint8_t G5PACKER_Num[8];
uint8_t G6PACKER_Num[8];
uint8_t G7PACKER_Num[8];
uint8_t G8PACKER_Num[8];


uint8_t G1_Prt;
uint8_t G2_Prt;
uint8_t G3_Prt;
uint8_t G4_Prt;
uint8_t G5_Prt;
uint8_t G6_Prt;
uint8_t G7_Prt;
uint8_t G8_Prt;
uint8_t Offset_Prt;

uint8_t Prt1_run;
uint8_t Prt2_run;
uint8_t Prt1_con;
uint8_t Prt2_con;

uint32_t G1_prt_qt_limit;
uint32_t G2_prt_qt_limit;
uint32_t G3_prt_qt_limit;
uint32_t G4_prt_qt_limit;
uint32_t G5_prt_qt_limit;
uint32_t G6_prt_qt_limit;
uint32_t G7_prt_qt_limit;
uint32_t G8_prt_qt_limit;
uint32_t OFFSET_prt_qt_limit;

uint8_t Sol_on_time;
uint8_t SOl_off_time;

bool send_count = false;
bool sendvalue = false;

uint8_t send_cnt;
uint8_t data_strem[1004]={0};

uint8_t rx_data[150],rx_data_[150],run_data[150], rx_data_tmp[150];
uint8_t txbuff[100];


uint8_t G1_CNT, G2_CNT, G3_CNT, G4_CNT, G5_CNT, G6_CNT, G7_CNT, G8_CNT;
uint8_t P1_CNT, P2_CNT, P3_CNT, P4_CNT, P5_CNT, P6_CNT, P7_CNT, P8_CNT;

typedef struct
{
	uint32_t magic_num;
	
	uint32_t Measurement_Delay ;
	uint32_t Measurement_EndTime; 
	
	float Grader_1_UL;
	float Grader_2_UL;
	float Grader_3_UL;
	float Grader_4_UL;
	float Grader_5_UL;
	float Grader_6_UL;
	float Grader_7_UL;
	float Grader_8_UL;
	float Off_size_UL;

	float Grader_1_LL;
	float Grader_2_LL;
	float Grader_3_LL;
	float Grader_4_LL;
	float Grader_5_LL;
	float Grader_6_LL;
	float Grader_7_LL;
	float Grader_8_LL;
	float Off_size_LL;
	
	unsigned int Loadcell_Zero;
	float Loadcell_Weight;
	
	uint8_t Packer1Sol_Run[6];
	uint8_t Packer2Sol_Run[6];
	uint8_t Packer3Sol_Run[6];
	uint8_t Packer4Sol_Run[6];
	uint8_t Packer5Sol_Run[6];
	uint8_t Packer6Sol_Run[6];
	uint8_t Packer7Sol_Run[6];
	uint8_t Packer8Sol_Run[6];

	uint8_t Packer1Sol_Con[6];
	uint8_t Packer2Sol_Con[6];
	uint8_t Packer3Sol_Con[6];
	uint8_t Packer4Sol_Con[6];
	uint8_t Packer5Sol_Con[6];
	uint8_t Packer6Sol_Con[6];
	uint8_t Packer7Sol_Con[6];
	uint8_t Packer8Sol_Con[6];
	
	uint8_t Packer1_sol_cnt;
	uint8_t Packer2_sol_cnt; 
	uint8_t Packer3_sol_cnt;
	uint8_t Packer4_sol_cnt;
	uint8_t Packer5_sol_cnt;
	uint8_t Packer6_sol_cnt;
	uint8_t Packer7_sol_cnt; 
	uint8_t Packer8_sol_cnt;

	uint8_t Packer1_ch;
	uint8_t Packer2_ch;
	uint8_t Packer3_ch;
	uint8_t Packer4_ch;
	uint8_t Packer5_ch;
	uint8_t Packer6_ch;
	uint8_t Packer7_ch;
	uint8_t Packer8_ch;


  uint8_t G1PACKER_Cnt;
	uint8_t G2PACKER_Cnt;
	uint8_t G3PACKER_Cnt;
	uint8_t G4PACKER_Cnt;
	uint8_t G5PACKER_Cnt;
	uint8_t G6PACKER_Cnt;
	uint8_t G7PACKER_Cnt;
	uint8_t G8PACKER_Cnt;
	
  uint8_t G1PACKER_Num[8];
	uint8_t G2PACKER_Num[8];
	uint8_t G3PACKER_Num[8];
	uint8_t G4PACKER_Num[8];
	uint8_t G5PACKER_Num[8];
	uint8_t G6PACKER_Num[8];
	uint8_t G7PACKER_Num[8];
	uint8_t G8PACKER_Num[8];

  uint8_t G1_Prt;
	uint8_t G2_Prt;
	uint8_t G3_Prt;
	uint8_t G4_Prt;
	uint8_t G5_Prt;
	uint8_t G6_Prt;
	uint8_t G7_Prt;
	uint8_t G8_Prt;
	uint8_t Offset_Prt;
	
	
 	uint8_t Prt1_run;
	uint8_t Prt2_run;
	uint8_t Prt1_con;
	uint8_t Prt2_con;	

  uint32_t G1_prt_qt_limit;
	uint32_t G2_prt_qt_limit;
	uint32_t G3_prt_qt_limit;
	uint32_t G4_prt_qt_limit;
	uint32_t G5_prt_qt_limit;
	uint32_t G6_prt_qt_limit;
	uint32_t G7_prt_qt_limit;
	uint32_t G8_prt_qt_limit;
	uint32_t OFFSET_prt_qt_limit;
  
  uint8_t Sol_on_time;
	uint8_t SOl_off_time;

}NVitemTypeDef;


NVitemTypeDef default_nvitem ={MAGIC_NUM, MEASUREMENT_DELAY, MEASUREMENT_END, GRADER_1_UL, GRADER_2_UL, GRADER_3_UL, GRADER_4_UL, 
 GRADER_5_UL, GRADER_6_UL, GRADER_7_UL, GRADER_8_UL,OFF_SIZE_UL, GRADER_1_LL, GRADER_2_LL, GRADER_3_LL, GRADER_4_LL, GRADER_5_LL, GRADER_6_LL,
 GRADER_7_LL, GRADER_8_LL, OFF_SIZE_LL ,LOADCELL_ZERO_VALUE, LOADCELL_WEIGHT_VALUE, PACKER1_SOL_CNT, PACKER2_SOL_CNT, PACKER3_SOL_CNT, 	
 PACKER4_SOL_CNT, PACKER5_SOL_CNT, PACKER6_SOL_CNT, PACKER7_SOL_CNT, PACKER8_SOL_CNT,  PACKER1_CH, PACKER2_CH, PACKER3_CH, PACKER4_CH,
 PACKER5_CH, PACKER6_CH, PACKER7_CH, PACKER8_CH,G1PACKER_CNT, G2PACKER_CNT, G3PACKER_CNT, G4PACKER_CNT, G5PACKER_CNT, G6PACKER_CNT,
 G7PACKER_CNT, G8PACKER_CNT,G1PACKER_NUM, G2PACKER_NUM, G3PACKER_NUM, G4PACKER_NUM, G5PACKER_NUM, G6PACKER_NUM, G7PACKER_NUM, G8PACKER_NUM, 
 PACKER1SOL_RUN, PACKER2SOL_RUN, PACKER3SOL_RUN, PACKER4SOL_RUN, PACKER5SOL_RUN, PACKER6SOL_RUN, PACKER7SOL_RUN, PACKER8SOL_RUN, G1_PRT, G2_PRT, G3_PRT, G4_PRT, G5_PRT, G6_PRT, G7_PRT, G8_PRT, OFFSET_PRT,
 G1_PRT_QT_LIMIT, G2_PRT_QT_LIMIT, G3_PRT_QT_LIMIT, G4_PRT_QT_LIMIT, G5_PRT_QT_LIMIT, G6_PRT_QT_LIMIT, G7_PRT_QT_LIMIT, G8_PRT_QT_LIMIT, OFFSET_PRT_QT_LIMIT,	
 PACKER1SOL_CON, PACKER2SOL_CON, PACKER3SOL_CON, PACKER4SOL_CON, PACKER5SOL_CON, PACKER6SOL_CON, PACKER7SOL_CON, PACKER8SOL_CON, PRT1_RUN, PRT2_RUN, PRT1_CON, PRT2_CON, SOL_ON_TIME, SOL_OFF_TIME};


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
HAL_StatusTypeDef update_nvitems(void)
{
	uint32_t *ptr ;
	HAL_FLASH_Unlock();
	uint32_t PAGEError = 0;
  uint32_t *Address;
	uint32_t Data;
	uint32_t i,j=0;
	
	FLASH_EraseInitTypeDef EraseInitStruct;
	EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.PageAddress = FLASH_USER_START_ADDR;
	EraseInitStruct.NbPages     = (FLASH_USER_END_ADDR - FLASH_USER_START_ADDR) / FLASH_PAGE_SIZE;
	HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError); 
	
	
	ptr = (uint32_t*)&default_nvitem;
	
	for( i=0 ; i < sizeof(NVitemTypeDef); i++)
	{  
		Address = (uint32_t*)nv_items+i;
		Data = *((uint32_t*)ptr+i);
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,(uint32_t)Address,Data);
		j+=4;
	}
	
  	HAL_FLASH_Lock(); // lock
}



/* ------------------------------ SOL RUN --------------------------------------------  */
//PACKER SOL SELECTE
void SOL_RUN_SELECTE(uint32_t selcte1)
{
  int selcte =(int)selcte1;
	
	switch(selcte)
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
void SOL_RUN_(uint32_t selcte1)
{
 uint32_t selcte = selcte1;
	
	switch(selcte)
	{
		case 1: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
		break;
		
		case 2: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
		break;
		
		case 3: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
		break;
		
		case 4: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
		break;
		
		case 5: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
		break;
		
		case 6: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
		break;
		
		case 7: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
		break;
		
		case 8: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
		break;
		
		case 21: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
		break;
		
		case 22: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);
		break;
		
		case 23: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);
		break;
		
		case 24: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_RESET);
		break;
		
		case 25: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);
		break;
		
		case 26: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
		break;
		
		case 27: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET);
		break;
		
		case 28: 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET);
		break;
		
		case 31: 
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
		break;
		
		case 32: 
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
		break;
		
		case 33: 
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
		break;
		
		case 34: 
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
		break;
		
		case 35: 
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
		break;
		
		case 36: 
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
		break;
		
		case 37: 
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
		break;
		
		case 38: 
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
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
	
	for(int i = 1; i <= Packer1_sol_cnt; i++)
	{
		if(RearLine[Packer1Sol_Run[Packer1_sol_cnt-i]] == Packer1Sol_Run[Packer1_sol_cnt-i])
		{
			SOL_RUN_SELECTE(Packer1Sol_Con[Packer1_sol_cnt-i]);
			RearLine[Packer1Sol_Run[Packer1_sol_cnt-i]] = NORUN;
		}				
	}
	
	for(int i = 1; i <= Packer2_sol_cnt; i++)
	{
		if(RearLine[Packer2Sol_Run[Packer2_sol_cnt-i]] == Packer2Sol_Run[Packer2_sol_cnt-i])
		{
			SOL_RUN_SELECTE(Packer2Sol_Con[Packer2_sol_cnt-i]);
			RearLine[Packer2Sol_Run[Packer2_sol_cnt-i]] = NORUN;
		}		
	}
	
	for(int i = 1; i <= Packer3_sol_cnt; i++)
	{
		if(RearLine[Packer3Sol_Run[Packer3_sol_cnt-i]] == Packer3Sol_Run[Packer3_sol_cnt-i])
		{
			SOL_RUN_SELECTE(Packer3Sol_Con[Packer3_sol_cnt-i]);
			RearLine[Packer3Sol_Run[Packer3_sol_cnt-i]] = NORUN;
		}		
	}
	
	for(int i = 1; i <= Packer4_sol_cnt; i++)
	{
		if(RearLine[Packer4Sol_Run[Packer4_sol_cnt-i]] == Packer4Sol_Run[Packer4_sol_cnt-i])
		{
			SOL_RUN_SELECTE(Packer4Sol_Con[Packer4_sol_cnt-i]);
			RearLine[Packer4Sol_Run[Packer4_sol_cnt-i]] = NORUN;
		}		
	}
	
	for(int i = 1; i <= Packer5_sol_cnt; i++)
	{
		if(RearLine[Packer5Sol_Run[Packer5_sol_cnt-i]] == Packer5Sol_Run[Packer5_sol_cnt-i])
		{
			SOL_RUN_SELECTE(Packer5Sol_Con[Packer5_sol_cnt-i]);
			RearLine[Packer5Sol_Run[Packer5_sol_cnt-i]] = NORUN;
		}		
	}
	
	for(int i = 1; i <= Packer6_sol_cnt; i++)
	{
		if(RearLine[Packer6Sol_Run[Packer6_sol_cnt-i]] == Packer6Sol_Run[Packer6_sol_cnt-i])
		{
			SOL_RUN_SELECTE(Packer6Sol_Con[Packer6_sol_cnt-i]);
			RearLine[Packer6Sol_Run[Packer6_sol_cnt-i]] = NORUN;
		}		
	}
	
	for(int i = 1; i <= Packer7_sol_cnt; i++)
	{
		if(RearLine[Packer7Sol_Run[Packer7_sol_cnt-i]] == Packer7Sol_Run[Packer7_sol_cnt-i])
		{
			SOL_RUN_SELECTE(Packer7Sol_Con[Packer7_sol_cnt-i]);
			RearLine[Packer7Sol_Run[Packer7_sol_cnt-i]] = NORUN;
		}		
	}
	
	for(int i = 1; i <= Packer8_sol_cnt; i++)
	{
		if(RearLine[Packer8Sol_Run[Packer8_sol_cnt-i]] == Packer8Sol_Run[Packer8_sol_cnt-i])
		{
			SOL_RUN_SELECTE(Packer8Sol_Con[Packer8_sol_cnt-i]);
			RearLine[Packer8Sol_Run[Packer8_sol_cnt-i]] = NORUN;
		}		
	}
	
		if(RearLine_Prt[Prt1_run] == Prt1_run)
		{
			SOL_RUN_SELECTE(Prt1_con);
			RearLine_Prt[Prt1_run] = NORUN;
		}		
			
		if(RearLine_Prt[Prt2_run] == Prt2_run)
		{
			SOL_RUN_SELECTE(Prt2_con);
			RearLine_Prt[Prt2_run] = NORUN;
		}		
		
}
//END PACKER SOL 
/* ------------------------------ SOL TEST --------------------------------------------  */
void SOL_TEST_RUN()
{
	/*-------------SOL_1-1-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
//	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);DWT_Delay_ms(100);
//			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	/*-------------SOL_1-2-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
//	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);DWT_Delay_ms(100);
//			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	/*-------------SOL_1-3-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);DWT_Delay_ms(100);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	/*-------------SOL_1-4-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);DWT_Delay_ms(100);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	/*-------------SOL_1-5-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);DWT_Delay_ms(100);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	/*-------------SOL_1-6-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);DWT_Delay_ms(100);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	/*-------------SOL_1-7-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);DWT_Delay_ms(100);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	/*-------------SOL_1-8-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);DWT_Delay_ms(100);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	/*-------------SOL_2-1-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);DWT_Delay_ms(100);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	/*-------------SOL_2-2-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);
	/*-------------SOL_2-3-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);DWT_Delay_ms(100);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	/*-------------SOL_2-4-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);DWT_Delay_ms(100);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	/*-------------SOL_2-5-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);DWT_Delay_ms(100);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	/*-------------SOL_2-6-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);DWT_Delay_ms(100);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	/*-------------SOL_2-7-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);DWT_Delay_ms(100);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	/*-------------SOL_2-8-------------------*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);DWT_Delay_ms(100);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	/*-------------SOL_3-1-------------------*/
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);DWT_Delay_ms(60);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	/*-------------SOL_3-2-------------------*/
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);DWT_Delay_ms(100);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	/*-------------SOL_3-3-------------------*/
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);DWT_Delay_ms(100);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	/*-------------SOL_3-4-------------------*/
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);DWT_Delay_ms(100);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	/*-------------SOL_3-5-------------------*/
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);DWT_Delay_ms(100);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	/*-------------SOL_3-6-------------------*/
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);DWT_Delay_ms(100);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	/*-------------SOL_3-7-------------------*/
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);DWT_Delay_ms(100);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	/*-------------SOL_3-8-------------------*/
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);DWT_Delay_ms(Sol_on_time);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);DWT_Delay_ms(100);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
}

/* ---------------------GRADER_INIT-----------------------*/
void Grader_Cfg_Init(void)
{
	default_nvitem.Grader_1_UL=GRADER_1_UL;
  default_nvitem.Grader_2_UL=GRADER_2_UL;
	default_nvitem.Grader_3_UL=GRADER_3_UL;
	default_nvitem.Grader_4_UL=GRADER_4_UL;
	default_nvitem.Grader_5_UL=GRADER_5_UL;
	default_nvitem.Grader_6_UL=GRADER_6_UL;
	default_nvitem.Grader_7_UL=GRADER_7_UL;
	default_nvitem.Grader_8_UL=GRADER_8_UL;
	default_nvitem.Off_size_UL=OFF_SIZE_UL;
	default_nvitem.Grader_1_LL=GRADER_1_LL;
  default_nvitem.Grader_2_LL=GRADER_2_LL;
	default_nvitem.Grader_3_LL=GRADER_3_LL;
	default_nvitem.Grader_4_LL=GRADER_4_LL;
	default_nvitem.Grader_5_LL=GRADER_5_LL;
	default_nvitem.Grader_6_LL=GRADER_6_LL;
	default_nvitem.Grader_7_LL=GRADER_7_LL;
	default_nvitem.Grader_8_LL=GRADER_8_LL;
	default_nvitem.Off_size_LL=OFF_SIZE_LL;
	
	default_nvitem.Loadcell_Zero=LOADCELL_ZERO_VALUE;
	default_nvitem.Loadcell_Weight=LOADCELL_WEIGHT_VALUE;

	default_nvitem.Packer1_ch = PACKER1_CH;
	default_nvitem.Packer2_ch = PACKER2_CH;
	default_nvitem.Packer3_ch = PACKER3_CH;
	default_nvitem.Packer4_ch = PACKER4_CH;
	default_nvitem.Packer5_ch = PACKER5_CH;
	default_nvitem.Packer6_ch = PACKER6_CH;
	default_nvitem.Packer7_ch = PACKER7_CH;
	default_nvitem.Packer8_ch = PACKER8_CH;
	
	default_nvitem.Packer1_sol_cnt = PACKER1_SOL_CNT;
	default_nvitem.Packer2_sol_cnt = PACKER2_SOL_CNT;
	default_nvitem.Packer3_sol_cnt = PACKER3_SOL_CNT;
	default_nvitem.Packer4_sol_cnt = PACKER4_SOL_CNT;
	default_nvitem.Packer5_sol_cnt = PACKER5_SOL_CNT;
	default_nvitem.Packer6_sol_cnt = PACKER6_SOL_CNT;
	default_nvitem.Packer7_sol_cnt = PACKER7_SOL_CNT;
	default_nvitem.Packer8_sol_cnt = PACKER8_SOL_CNT;
	
	default_nvitem.G1PACKER_Cnt = G1PACKER_CNT;
	default_nvitem.G2PACKER_Cnt = G2PACKER_CNT;
	default_nvitem.G3PACKER_Cnt = G3PACKER_CNT;
	default_nvitem.G4PACKER_Cnt = G4PACKER_CNT;
	default_nvitem.G5PACKER_Cnt = G5PACKER_CNT;
	default_nvitem.G6PACKER_Cnt = G6PACKER_CNT;
	default_nvitem.G7PACKER_Cnt = G7PACKER_CNT;
	default_nvitem.G8PACKER_Cnt = G8PACKER_CNT;
	
	default_nvitem.G1PACKER_Num[0] = G1PACKER_NUM;
	default_nvitem.G2PACKER_Num[0] = G2PACKER_NUM;
	default_nvitem.G3PACKER_Num[0] = G3PACKER_NUM;
	default_nvitem.G4PACKER_Num[0] = G4PACKER_NUM;
	default_nvitem.G5PACKER_Num[0] = G5PACKER_NUM;
	default_nvitem.G6PACKER_Num[0] = G6PACKER_NUM;
	default_nvitem.G7PACKER_Num[0] = G7PACKER_NUM;
	default_nvitem.G8PACKER_Num[0] = G8PACKER_NUM;
	
	default_nvitem.Packer1Sol_Run[0] = PACKER1SOL_RUN;
	default_nvitem.Packer2Sol_Run[0] = PACKER2SOL_RUN;
	default_nvitem.Packer3Sol_Run[0] = PACKER3SOL_RUN;
	default_nvitem.Packer4Sol_Run[0] = PACKER4SOL_RUN;
	default_nvitem.Packer5Sol_Run[0] = PACKER5SOL_RUN;
	default_nvitem.Packer6Sol_Run[0] = PACKER6SOL_RUN;
	default_nvitem.Packer7Sol_Run[0] = PACKER7SOL_RUN;
	default_nvitem.Packer8Sol_Run[0] = PACKER8SOL_RUN;
	
	default_nvitem.Packer1Sol_Con[0] = PACKER1SOL_CON;
	default_nvitem.Packer2Sol_Con[0] = PACKER2SOL_CON;
	default_nvitem.Packer3Sol_Con[0] = PACKER3SOL_CON;
	default_nvitem.Packer4Sol_Con[0] = PACKER4SOL_CON;
	default_nvitem.Packer5Sol_Con[0] = PACKER5SOL_CON;
	default_nvitem.Packer6Sol_Con[0] = PACKER6SOL_CON;
	default_nvitem.Packer7Sol_Con[0] = PACKER7SOL_CON;
	default_nvitem.Packer8Sol_Con[0] = PACKER8SOL_CON;
	
	default_nvitem.G1_Prt = G1_PRT;
	default_nvitem.G2_Prt = G2_PRT;
	default_nvitem.G3_Prt = G3_PRT;
	default_nvitem.G4_Prt = G4_PRT;
	default_nvitem.G5_Prt = G5_PRT;
	default_nvitem.G6_Prt = G6_PRT;
	default_nvitem.G7_Prt = G7_PRT;
	default_nvitem.G8_Prt = G8_PRT;
	default_nvitem.Offset_Prt = OFFSET_PRT;
	
	default_nvitem.Prt1_run = PRT1_RUN;
	default_nvitem.Prt2_run = PRT2_RUN;
	default_nvitem.Prt1_con = PRT1_CON;
	default_nvitem.Prt2_con = PRT2_CON;
	
	default_nvitem.G1_prt_qt_limit = G1_PRT_QT_LIMIT;
	default_nvitem.G2_prt_qt_limit = G2_PRT_QT_LIMIT;
	default_nvitem.G3_prt_qt_limit = G3_PRT_QT_LIMIT;
  default_nvitem.G4_prt_qt_limit = G4_PRT_QT_LIMIT;
	default_nvitem.G5_prt_qt_limit = G5_PRT_QT_LIMIT;
	default_nvitem.G6_prt_qt_limit = G6_PRT_QT_LIMIT;
	default_nvitem.G7_prt_qt_limit = G7_PRT_QT_LIMIT;
	default_nvitem.G8_prt_qt_limit = G8_PRT_QT_LIMIT;
	default_nvitem.OFFSET_prt_qt_limit = OFFSET_PRT_QT_LIMIT;
	
	
	default_nvitem.Sol_on_time=SOL_ON_TIME;
	default_nvitem.SOl_off_time=SOL_OFF_TIME;
	
	
	
	update_nvitems();
}
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
float LOADCELL_WEIGHT(unsigned int ZERO)
{
	int i; 
	//unsigned int avg =0;
	float avg_weight = 0;
	
	for(i = 0; i <= 100; i++)
	{
	//DWT_Delay_ms(1);
		avg_weight += filtereadValue;
		DWT_Delay_ms(1);
	}
	avg_weight = avg_weight/i;
	avg_weight = 50/(avg_weight-ZERO);
	avg_weight = ceil(avg_weight*10000)/10000;
	return avg_weight;
}
/* ---------------------END-----------------------  */
void TxMeurement(float avg_float1)
{
	avg_float = avg_float1;
	txbuff[0] = 0x10;	
	txbuff[1] = 0x02;				
	txbuff[2] = (uint8_t)(*((uint32_t*)&avg_float ) >> 24);		
	txbuff[3] = (uint8_t)(*((uint32_t*)&avg_float ) >> 16);		
	txbuff[4] = (uint8_t)(*((uint32_t*)&avg_float ) >> 8);
	txbuff[5] = (uint8_t)(*((uint32_t*)&avg_float ));	
	txbuff[6] = 0x10;	
	txbuff[7] = 0x03;
	HAL_UART_Transmit(&huart1,txbuff,8,100); 	
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  
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
 
 // Using data stored in flash memory
 if(nv_items->magic_num == MAGIC_NUM) //if you have ever accessed to flash memory
{	
	memcpy(&default_nvitem,nv_items,sizeof(NVitemTypeDef)); //Copy the stored flash memory values to the RAM.
	Measurement_Delay = default_nvitem.Measurement_Delay;
	Measurement_EndTime = default_nvitem.Measurement_EndTime;
	Grader_1_UL = default_nvitem.Grader_1_UL;
	Grader_2_UL = default_nvitem.Grader_2_UL;
	Grader_3_UL = default_nvitem.Grader_3_UL;
	Grader_4_UL = default_nvitem.Grader_4_UL;
	Grader_5_UL = default_nvitem.Grader_5_UL;
	Grader_6_UL = default_nvitem.Grader_6_UL;
	Grader_7_UL = default_nvitem.Grader_7_UL;
	Grader_8_UL = default_nvitem.Grader_8_UL;
	Off_size_UL = default_nvitem.Off_size_UL;
	
	Grader_1_LL = default_nvitem.Grader_1_LL;
	Grader_2_LL = default_nvitem.Grader_2_LL;
	Grader_3_LL = default_nvitem.Grader_3_LL;
	Grader_4_LL = default_nvitem.Grader_4_LL;
	Grader_5_LL = default_nvitem.Grader_5_LL;
	Grader_6_LL = default_nvitem.Grader_6_LL;
	Grader_7_LL = default_nvitem.Grader_7_LL;
	Grader_8_LL = default_nvitem.Grader_8_LL;
	Off_size_LL = default_nvitem.Off_size_LL;
	
	Loadcell_Zero = default_nvitem.Loadcell_Zero;
	Loadcell_Weight = default_nvitem.Loadcell_Weight;

	Packer1_sol_cnt = default_nvitem.Packer1_sol_cnt;
	Packer2_sol_cnt = default_nvitem.Packer2_sol_cnt;
	Packer3_sol_cnt = default_nvitem.Packer3_sol_cnt;
	Packer4_sol_cnt = default_nvitem.Packer4_sol_cnt;
	Packer5_sol_cnt = default_nvitem.Packer5_sol_cnt;
	Packer6_sol_cnt = default_nvitem.Packer6_sol_cnt;
	Packer7_sol_cnt = default_nvitem.Packer7_sol_cnt;
	Packer8_sol_cnt = default_nvitem.Packer8_sol_cnt;
	
	Packer1_ch = default_nvitem.Packer1_ch;
	Packer2_ch = default_nvitem.Packer2_ch;
	Packer3_ch = default_nvitem.Packer3_ch;
	Packer4_ch = default_nvitem.Packer4_ch;
	Packer5_ch = default_nvitem.Packer5_ch;
	Packer6_ch = default_nvitem.Packer6_ch;
	Packer7_ch = default_nvitem.Packer7_ch;
	Packer8_ch = default_nvitem.Packer8_ch;
	
	G1PACKER_Cnt = default_nvitem.G1PACKER_Cnt;
	G2PACKER_Cnt = default_nvitem.G2PACKER_Cnt;
	G3PACKER_Cnt = default_nvitem.G3PACKER_Cnt;
	G4PACKER_Cnt = default_nvitem.G4PACKER_Cnt;
	G5PACKER_Cnt = default_nvitem.G5PACKER_Cnt;
	G6PACKER_Cnt = default_nvitem.G6PACKER_Cnt;
	G7PACKER_Cnt = default_nvitem.G7PACKER_Cnt;
	G8PACKER_Cnt = default_nvitem.G8PACKER_Cnt;
	
	for(int i =0; i <= G1PACKER_Cnt; i++)
	{
		G1PACKER_Num[i]=default_nvitem.G1PACKER_Num[i];
	}
	
  for(int i =0; i <= G2PACKER_Cnt; i++)
	{
		G2PACKER_Num[i]=default_nvitem.G2PACKER_Num[i];
	}	
	
	for(int i =0; i <= G3PACKER_Cnt; i++)
	{
		G3PACKER_Num[i]=default_nvitem.G3PACKER_Num[i];
	}
	
	for(int i =0; i <= G4PACKER_Cnt; i++)
	{
		G4PACKER_Num[i]=default_nvitem.G4PACKER_Num[i];
	}
	
	for(int i =0; i <= G5PACKER_Cnt; i++)
	{
		G5PACKER_Num[i]=default_nvitem.G5PACKER_Num[i];
	}
	
	for(int i =0; i <= G6PACKER_Cnt; i++)
	{
		G6PACKER_Num[i]=default_nvitem.G6PACKER_Num[i];
	}
	
	for(int i =0; i <= G7PACKER_Cnt; i++)
	{
		G7PACKER_Num[i]=default_nvitem.G7PACKER_Num[i];
	}
	
	for(int i =0; i <= G8PACKER_Cnt; i++)
	{
		G8PACKER_Num[i]=default_nvitem.G8PACKER_Num[i];
	}
	
	for(int i =0; i <= Packer1_sol_cnt; i++)
	{
		Packer1Sol_Run[i]=default_nvitem.Packer1Sol_Run[i];
	}
	
	for(int i =0; i <= Packer2_sol_cnt; i++)
	{
		Packer2Sol_Run[i]=default_nvitem.Packer2Sol_Run[i];
	}
	
	for(int i =0; i <= Packer3_sol_cnt; i++)
	{
		Packer3Sol_Run[i]=default_nvitem.Packer3Sol_Run[i];
	}
	
	for(int i =0; i <= Packer4_sol_cnt; i++)
	{
		Packer4Sol_Run[i]=default_nvitem.Packer4Sol_Run[i];
	}
	
	for(int i =0; i <= Packer5_sol_cnt; i++)
	{
		Packer5Sol_Run[i]=default_nvitem.Packer5Sol_Run[i];
	}
	
	for(int i =0; i <= Packer6_sol_cnt; i++)
	{
		Packer6Sol_Run[i]=default_nvitem.Packer6Sol_Run[i];
	}
	
	for(int i =0; i <= Packer7_sol_cnt; i++)
	{
		Packer7Sol_Run[i]=default_nvitem.Packer7Sol_Run[i];
	}
	
	for(int i =0; i <= Packer8_sol_cnt; i++)
	{
		Packer8Sol_Run[i]=default_nvitem.Packer8Sol_Run[i];
	}
		
		for(int i =0; i <= Packer1_sol_cnt; i++)
	{
		Packer1Sol_Con[i]=default_nvitem.Packer1Sol_Con[i];
	}
	
	for(int i =0; i <= Packer2_sol_cnt; i++)
	{
		Packer2Sol_Con[i]=default_nvitem.Packer2Sol_Con[i];
	}
	
	for(int i =0; i <= Packer3_sol_cnt; i++)
	{
		Packer3Sol_Con[i]=default_nvitem.Packer3Sol_Con[i];
	}
	
	for(int i =0; i <= Packer4_sol_cnt; i++)
	{
		Packer4Sol_Con[i]=default_nvitem.Packer4Sol_Con[i];
	}
	
	for(int i =0; i <= Packer5_sol_cnt; i++)
	{
		Packer5Sol_Con[i]=default_nvitem.Packer5Sol_Con[i];
	}
	
	for(int i =0; i <= Packer6_sol_cnt; i++)
	{
		Packer6Sol_Con[i]=default_nvitem.Packer6Sol_Con[i];
	}
	
	for(int i =0; i <= Packer7_sol_cnt; i++)
	{
		Packer7Sol_Con[i]=default_nvitem.Packer7Sol_Con[i];
	}
	
	for(int i =0; i <= Packer8_sol_cnt; i++)
	{
		Packer8Sol_Con[i]=default_nvitem.Packer8Sol_Con[i];
	}
	
	G1_Prt = default_nvitem.G1_Prt; 
	G2_Prt = default_nvitem.G2_Prt; 
	G3_Prt = default_nvitem.G3_Prt; 
	G4_Prt = default_nvitem.G4_Prt; 
	G5_Prt = default_nvitem.G5_Prt; 
	G6_Prt = default_nvitem.G6_Prt; 
	G7_Prt = default_nvitem.G7_Prt; 
	G8_Prt = default_nvitem.G8_Prt; 
	Offset_Prt = default_nvitem.Offset_Prt; 
	
	
	
	Prt1_run = default_nvitem.Prt1_run;
	Prt2_run = default_nvitem.Prt2_run;
	Prt1_con = default_nvitem.Prt1_con;
	Prt2_con = default_nvitem.Prt2_con;
	
	G1_prt_qt_limit = default_nvitem.G1_prt_qt_limit;
	G2_prt_qt_limit = default_nvitem.G2_prt_qt_limit;
	G3_prt_qt_limit = default_nvitem.G3_prt_qt_limit;
  G4_prt_qt_limit = default_nvitem.G4_prt_qt_limit;
	G5_prt_qt_limit = default_nvitem.G5_prt_qt_limit;
	G6_prt_qt_limit = default_nvitem.G6_prt_qt_limit;
	G7_prt_qt_limit = default_nvitem.G7_prt_qt_limit;
	G8_prt_qt_limit = default_nvitem.G8_prt_qt_limit;
	OFFSET_prt_qt_limit = default_nvitem.OFFSET_prt_qt_limit;
	
	Sol_on_time = default_nvitem.Sol_on_time;
	SOl_off_time = default_nvitem.SOl_off_time;
	
	}	
	else
	{
		update_nvitems();
	}
// Using data stored in flash memory end
	
// LED_BUZ RUN (Check whether there is an abnormality by driving LED_BUZ.) 	
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
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET); HAL_Delay(500);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET); HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET); HAL_Delay(200);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET); HAL_Delay(100);
	
// LED_BUZ RUN END (Check whether there is an abnormality by driving LED_BUZ.)

// Number of data to be transmitted	
  int i =0;
	int k =0;	
// Number of data to be transmitted END	
// Number of GRADE and PACKER (Interrupt applied)	
	G1_CNT = G1PACKER_Cnt;
	G2_CNT = G2PACKER_Cnt;
	G3_CNT = G3PACKER_Cnt;
	G4_CNT = G4PACKER_Cnt;
	G5_CNT = G5PACKER_Cnt;
	G6_CNT = G6PACKER_Cnt;
	G7_CNT = G7PACKER_Cnt;
	G8_CNT = G8PACKER_Cnt;	
	
	P1_CNT = Packer1_sol_cnt;
	P2_CNT = Packer2_sol_cnt;
	P3_CNT = Packer3_sol_cnt;
	P4_CNT = Packer4_sol_cnt;
	P5_CNT = Packer5_sol_cnt;
	P6_CNT = Packer6_sol_cnt;
	P7_CNT = Packer7_sol_cnt;
	P8_CNT = Packer8_sol_cnt;

// Number of GRADE and PACKER END (Interrupt applied)	

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */ 
		/*---------------MODE SECTION------------------------*/	
    
	 	switch (run_data[2])  
		{
/*---------------READ SECTION START--------------------------*/				
			case SEND :  
				switch (run_data[3]) 
				{
					case LOADCELL_SET_SEND:	 /* LOADCELL_CONFIG VALUE SEND*/		
						RUN_ACTIVE_NUM = LOADCELL_SET_SEND;		
						memcpy(run_data,init_run_data,sizeof(init_run_data));	
					break;			
					
					case SOLENOIDE_SET_SEND:	   /* SOL_CONFIG VALUE SEND*/	
						RUN_ACTIVE_NUM = SOLENOIDE_SET_SEND;				
						memcpy(run_data,init_run_data,sizeof(init_run_data));		
           				
					break;	
				
					case GRADE_SET_SEND:	 /* SYSTEM_CONFIG VALUE SEND*/	
						RUN_ACTIVE_NUM = GRADE_SET_SEND;			
						memcpy(run_data,init_run_data,sizeof(init_run_data));	
      			
					break;
				
					case INIT_CFG_SEND:	  /* INIT_CONFIG VALUE SEND*/	
						RUN_ACTIVE_NUM = INIT_CFG_SEND;
						memcpy(run_data,init_run_data,sizeof(init_run_data));		
          				
					break;
					
				}
			break;
/*---------------READ SECTION END--------------------------*/		
					
/*---------------SET START--------------------------*/					
			case SET : // WRITE
				switch (run_data[3])	
				{
					case MEASUREMENT_SET: /* LOADCELL_CONFIG VALUE MEMORY SAVE [DELAY TIME/END TIME]*/	
						RUN_ACTIVE_NUM = MEASUREMENT_SET;			  					
            default_nvitem.Measurement_Delay =    (((uint32_t)run_data[4] & 0xFF));
						default_nvitem.Measurement_Delay +=   (((uint32_t)run_data[5] & 0xFF) << 8);
						default_nvitem.Measurement_Delay +=   (((uint32_t)run_data[6] & 0xFF) << 16);
						default_nvitem.Measurement_Delay +=   (((uint32_t)run_data[7] & 0xFF) << 24);		
					
					  default_nvitem.Measurement_EndTime =  (((uint32_t)run_data[8] & 0xFF));
					  default_nvitem.Measurement_EndTime += (((uint32_t)run_data[9] & 0xFF) << 8);
					  default_nvitem.Measurement_EndTime += (((uint32_t)run_data[10] & 0xFF) << 16);
					  default_nvitem.Measurement_EndTime += (((uint32_t)run_data[11] & 0xFF) << 24);
						
					  update_nvitems();			
					  
					  Measurement_Delay = default_nvitem.Measurement_Delay;
					  Measurement_EndTime = default_nvitem.Measurement_EndTime;		
					 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET); HAL_Delay(100);
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET); HAL_Delay(100);
						txbuff[0] = 0x10;	
						txbuff[1] = 0x02;	
						txbuff[2] = (uint8_t)(*((uint32_t*)&Measurement_Delay ) >> 24);		
						txbuff[3] = (uint8_t)(*((uint32_t*)&Measurement_Delay ) >> 16);		
						txbuff[4] = (uint8_t)(*((uint32_t*)&Measurement_Delay ) >> 8);
						txbuff[5] = (uint8_t)(*((uint32_t*)&Measurement_Delay ));	
					  txbuff[6] = (uint8_t)(*((uint32_t*)&Measurement_EndTime ) >> 24);		
						txbuff[7] = (uint8_t)(*((uint32_t*)&Measurement_EndTime ) >> 16);		
						txbuff[8] = (uint8_t)(*((uint32_t*)&Measurement_EndTime ) >> 8);
						txbuff[9] = (uint8_t)(*((uint32_t*)&Measurement_EndTime ));	
						txbuff[10] = 0x10;	
						txbuff[11] = 0x03;	
						HAL_UART_Transmit(&huart1,txbuff,12,10); 					
						memcpy(run_data,init_run_data,sizeof(init_run_data));
					break;
					
					case SOLENOIDE_SET:   /* SOL_CONFIG VALUE MEMORY SAVE[SOL_ON_TIME/SOL_OFF_TIME]*/	
						RUN_ACTIVE_NUM = SOLENOIDE_SET;
		
						i = 4;	
						for(int j = 0 ; j < Packer1_sol_cnt; )
						{
							default_nvitem.Packer1Sol_Run[j]=(((uint8_t)run_data[i++] & 0xFF));
							Packer1Sol_Run[j]=default_nvitem.Packer1Sol_Run[j];
							j++;
						}
						for(int j = 0 ; j < Packer2_sol_cnt; )
						{
							default_nvitem.Packer2Sol_Run[j]=(((uint8_t)run_data[i++] & 0xFF));
							Packer2Sol_Run[j]=default_nvitem.Packer2Sol_Run[j];
							j++;
						}
						for(int j = 0 ; j < Packer3_sol_cnt; )
						{
							default_nvitem.Packer3Sol_Run[j]=(((uint8_t)run_data[i++] & 0xFF));
							Packer3Sol_Run[j]=default_nvitem.Packer3Sol_Run[j];
							j++;
						}
						for(int j = 0 ; j < Packer4_sol_cnt; )
						{
							default_nvitem.Packer4Sol_Run[j]=(((uint8_t)run_data[i++] & 0xFF));
							Packer4Sol_Run[j]=default_nvitem.Packer4Sol_Run[j];
							j++;
						}
						for(int j = 0 ; j < Packer5_sol_cnt; )
						{
							default_nvitem.Packer5Sol_Run[j]=(((uint8_t)run_data[i++] & 0xFF));
							Packer5Sol_Run[j]=default_nvitem.Packer5Sol_Run[j];
							j++;
						}
						for(int j = 0 ; j < Packer6_sol_cnt; )
						{
							default_nvitem.Packer6Sol_Run[j]=(((uint8_t)run_data[i++] & 0xFF));
							Packer6Sol_Run[j]=default_nvitem.Packer6Sol_Run[j];
							j++;
						}
						for(int j = 0 ; j < Packer7_sol_cnt; )
						{
							default_nvitem.Packer7Sol_Run[j]=(((uint8_t)run_data[i++] & 0xFF));
							Packer7Sol_Run[j]=default_nvitem.Packer7Sol_Run[j];
							j++;
						}
						for(int j = 0 ; j < Packer8_sol_cnt; )
						{
							default_nvitem.Packer8Sol_Run[j]=(((uint8_t)run_data[i++] & 0xFF));
							Packer8Sol_Run[j]=default_nvitem.Packer8Sol_Run[j];
							j++;
						}
							for(int j = 0 ; j < Packer1_sol_cnt; )
						{
							default_nvitem.Packer1Sol_Con[j]=(((uint8_t)run_data[i++] & 0xFF));
							Packer1Sol_Con[j]=default_nvitem.Packer1Sol_Con[j];
							j++;
						}
						for(int j = 0 ; j < Packer2_sol_cnt; )
						{
							default_nvitem.Packer2Sol_Con[j]=(((uint8_t)run_data[i++] & 0xFF));
							Packer2Sol_Con[j]=default_nvitem.Packer2Sol_Con[j];
							j++;
						}
						for(int j = 0 ; j < Packer3_sol_cnt; )
						{
							default_nvitem.Packer3Sol_Con[j]=(((uint8_t)run_data[i++] & 0xFF));
							Packer3Sol_Con[j]=default_nvitem.Packer3Sol_Con[j];
							j++;
						}
						for(int j = 0 ; j < Packer4_sol_cnt; )
						{
							default_nvitem.Packer4Sol_Con[j]=(((uint8_t)run_data[i++] & 0xFF));
							Packer4Sol_Con[j]=default_nvitem.Packer4Sol_Con[j];
							j++;
						}
						for(int j = 0 ; j < Packer5_sol_cnt; )
						{
							default_nvitem.Packer5Sol_Con[j]=(((uint8_t)run_data[i++] & 0xFF));
							Packer5Sol_Con[j]=default_nvitem.Packer5Sol_Con[j];
							j++;
						}
						for(int j = 0 ; j < Packer6_sol_cnt; )
						{
							default_nvitem.Packer6Sol_Con[j]=(((uint8_t)run_data[i++] & 0xFF));
							Packer6Sol_Con[j]=default_nvitem.Packer6Sol_Con[j];
							j++;
						}
						for(int j = 0 ; j < Packer7_sol_cnt; )
						{
							default_nvitem.Packer7Sol_Con[j]=(((uint8_t)run_data[i++] & 0xFF));
							Packer7Sol_Con[j]=default_nvitem.Packer7Sol_Con[j];
							j++;
						}
						for(int j = 0 ; j < Packer8_sol_cnt; )
						{
							default_nvitem.Packer8Sol_Con[j]=(((uint8_t)run_data[i++] & 0xFF));
							Packer8Sol_Con[j]=default_nvitem.Packer8Sol_Con[j];
							j++;
						}
						
						default_nvitem.Prt1_run = (((uint8_t)run_data[i++] & 0xFF));
						Prt1_run = default_nvitem.Prt1_run;
						default_nvitem.Prt2_run = (((uint8_t)run_data[i++] & 0xFF));
						Prt2_run = default_nvitem.Prt2_run;
						default_nvitem.Prt1_con = (((uint8_t)run_data[i++] & 0xFF));
						Prt1_con = default_nvitem.Prt1_con;
						default_nvitem.Prt2_con = (((uint8_t)run_data[i++] & 0xFF));
						Prt2_con = default_nvitem.Prt2_con;					
						default_nvitem.Sol_on_time = (((uint8_t)run_data[i++] & 0xFF));
						Sol_on_time = default_nvitem.Sol_on_time;
						
						default_nvitem.G1_prt_qt_limit =    (((uint32_t)run_data[i++] & 0xFF));
						default_nvitem.G1_prt_qt_limit +=   (((uint32_t)run_data[i++] & 0xFF) << 8);
						default_nvitem.G1_prt_qt_limit +=   (((uint32_t)run_data[i++] & 0xFF) << 16);
						default_nvitem.G1_prt_qt_limit +=   (((uint32_t)run_data[i++] & 0xFF) << 24);
						G1_prt_qt_limit = default_nvitem.G1_prt_qt_limit;
						
						default_nvitem.G2_prt_qt_limit =    (((uint32_t)run_data[i++] & 0xFF));
						default_nvitem.G2_prt_qt_limit +=   (((uint32_t)run_data[i++] & 0xFF) << 8);
						default_nvitem.G2_prt_qt_limit +=   (((uint32_t)run_data[i++] & 0xFF) << 16);
						default_nvitem.G2_prt_qt_limit +=   (((uint32_t)run_data[i++] & 0xFF) << 24);
						G2_prt_qt_limit = default_nvitem.G2_prt_qt_limit;
						
						default_nvitem.G3_prt_qt_limit =    (((uint32_t)run_data[i++] & 0xFF));
						default_nvitem.G3_prt_qt_limit +=   (((uint32_t)run_data[i++] & 0xFF) << 8);
						default_nvitem.G3_prt_qt_limit +=   (((uint32_t)run_data[i++] & 0xFF) << 16);
						default_nvitem.G3_prt_qt_limit +=   (((uint32_t)run_data[i++] & 0xFF) << 24);
						G3_prt_qt_limit = default_nvitem.G3_prt_qt_limit;
						
						default_nvitem.G4_prt_qt_limit =    (((uint32_t)run_data[i++] & 0xFF));
						default_nvitem.G4_prt_qt_limit +=   (((uint32_t)run_data[i++] & 0xFF) << 8);
						default_nvitem.G4_prt_qt_limit +=   (((uint32_t)run_data[i++] & 0xFF) << 16);
						default_nvitem.G4_prt_qt_limit +=   (((uint32_t)run_data[i++] & 0xFF) << 24);
						G4_prt_qt_limit = default_nvitem.G4_prt_qt_limit;
						
						default_nvitem.G5_prt_qt_limit =    (((uint32_t)run_data[i++] & 0xFF));
						default_nvitem.G5_prt_qt_limit +=   (((uint32_t)run_data[i++] & 0xFF) << 8);
						default_nvitem.G5_prt_qt_limit +=   (((uint32_t)run_data[i++] & 0xFF) << 16);
						default_nvitem.G5_prt_qt_limit +=   (((uint32_t)run_data[i++] & 0xFF) << 24);
						G5_prt_qt_limit = default_nvitem.G5_prt_qt_limit;
						
						default_nvitem.G6_prt_qt_limit =    (((uint32_t)run_data[i++] & 0xFF));
						default_nvitem.G6_prt_qt_limit +=   (((uint32_t)run_data[i++] & 0xFF) << 8);
						default_nvitem.G6_prt_qt_limit +=   (((uint32_t)run_data[i++] & 0xFF) << 16);
						default_nvitem.G6_prt_qt_limit +=   (((uint32_t)run_data[i++] & 0xFF) << 24);
						G6_prt_qt_limit = default_nvitem.G6_prt_qt_limit;
						
						default_nvitem.G7_prt_qt_limit =    (((uint32_t)run_data[i++] & 0xFF));
						default_nvitem.G7_prt_qt_limit +=   (((uint32_t)run_data[i++] & 0xFF) << 8);
						default_nvitem.G7_prt_qt_limit +=   (((uint32_t)run_data[i++] & 0xFF) << 16);
						default_nvitem.G7_prt_qt_limit +=   (((uint32_t)run_data[i++] & 0xFF) << 24);
						G7_prt_qt_limit = default_nvitem.G7_prt_qt_limit;
						
						default_nvitem.G8_prt_qt_limit =    (((uint32_t)run_data[i++] & 0xFF));
						default_nvitem.G8_prt_qt_limit +=   (((uint32_t)run_data[i++] & 0xFF) << 8);
						default_nvitem.G8_prt_qt_limit +=   (((uint32_t)run_data[i++] & 0xFF) << 16);
						default_nvitem.G8_prt_qt_limit +=   (((uint32_t)run_data[i++] & 0xFF) << 24);
						G8_prt_qt_limit = default_nvitem.G8_prt_qt_limit;
						
						default_nvitem.OFFSET_prt_qt_limit =    (((uint32_t)run_data[i++] & 0xFF));
						default_nvitem.OFFSET_prt_qt_limit +=   (((uint32_t)run_data[i++] & 0xFF) << 8);
						default_nvitem.OFFSET_prt_qt_limit +=   (((uint32_t)run_data[i++] & 0xFF) << 16);
						default_nvitem.OFFSET_prt_qt_limit +=   (((uint32_t)run_data[i++] & 0xFF) << 24);
						OFFSET_prt_qt_limit = default_nvitem.OFFSET_prt_qt_limit;
										
						update_nvitems();	
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET); HAL_Delay(100);
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET); HAL_Delay(100);
						k =0;
						txbuff[k++] = 0x10;	
						txbuff[k++] = 0x02;	
						for(int i =0; i < Packer1_sol_cnt;i++)
						{
							txbuff[k++] = Packer1Sol_Run[i];					
						}									
						for(int i =0; i < Packer2_sol_cnt;i++)
						{
							txbuff[k++] = Packer2Sol_Run[i];					
						}						
						for(int i =0; i < Packer3_sol_cnt;i++)
						{
							txbuff[k++] = Packer3Sol_Run[i];					
						}						
						for(int i =0; i < Packer4_sol_cnt;i++)
						{
							txbuff[k++] = Packer4Sol_Run[i];					
						}						
						for(int i =0; i < Packer5_sol_cnt;i++)
						{
							txbuff[k++] = Packer5Sol_Run[i];					
						}					
						for(int i =0; i < Packer6_sol_cnt;i++)
						{
							txbuff[k++] = Packer6Sol_Run[i];					
						}					
						for(int i =0; i < Packer7_sol_cnt;i++)
						{
							txbuff[k++] = Packer7Sol_Run[i];					
						}						
						for(int i =0; i < Packer8_sol_cnt;i++)
						{
							txbuff[k++] = Packer8Sol_Run[i];					
						}
						
						
						for(int i =0; i < Packer1_sol_cnt;i++)
						{
							txbuff[k++] = Packer1Sol_Con[i];					
						}					
						for(int i =0; i < Packer2_sol_cnt;i++)
						{
							txbuff[k++] = Packer2Sol_Con[i];					
						}						
						for(int i =0; i < Packer3_sol_cnt;i++)
						{
							txbuff[k++] = Packer3Sol_Con[i];					
						}					
						for(int i =0; i < Packer4_sol_cnt;i++)
						{
							txbuff[k++] = Packer4Sol_Con[i];					
						}						
						for(int i =0; i < Packer5_sol_cnt;i++)
						{
							txbuff[k++] = Packer5Sol_Con[i];					
						}					
						for(int i =0; i < Packer6_sol_cnt;i++)
						{
							txbuff[k++] = Packer6Sol_Con[i];					
						}					
						for(int i =0; i < Packer7_sol_cnt;i++)
						{
							txbuff[k++] = Packer7Sol_Con[i];					
						}						
						for(int i =0; i < Packer8_sol_cnt;i++)
						{
							txbuff[k++] = Packer8Sol_Con[i];					
						}
						
						txbuff[k++] = Prt1_run;		
						txbuff[k++] = Prt2_run;		
						txbuff[k++] = Prt1_con;		
						txbuff[k++] = Prt2_con;		
						txbuff[k++] = Sol_on_time;		
					  
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G1_prt_qt_limit ) >> 24);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G1_prt_qt_limit ) >> 16);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G1_prt_qt_limit ) >> 8);
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G1_prt_qt_limit ));	
						
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G2_prt_qt_limit ) >> 24);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G2_prt_qt_limit ) >> 16);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G2_prt_qt_limit ) >> 8);
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G2_prt_qt_limit ));	
						
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G3_prt_qt_limit ) >> 24);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G3_prt_qt_limit ) >> 16);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G3_prt_qt_limit ) >> 8);
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G3_prt_qt_limit ));	
						
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G4_prt_qt_limit ) >> 24);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G4_prt_qt_limit ) >> 16);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G4_prt_qt_limit ) >> 8);
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G4_prt_qt_limit ));	
						
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G5_prt_qt_limit ) >> 24);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G5_prt_qt_limit ) >> 16);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G5_prt_qt_limit ) >> 8);
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G5_prt_qt_limit ));	
						
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G6_prt_qt_limit ) >> 24);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G6_prt_qt_limit ) >> 16);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G6_prt_qt_limit ) >> 8);
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G6_prt_qt_limit ));	
						
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G7_prt_qt_limit ) >> 24);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G7_prt_qt_limit ) >> 16);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G7_prt_qt_limit ) >> 8);
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G7_prt_qt_limit ));	
						
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G8_prt_qt_limit ) >> 24);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G8_prt_qt_limit ) >> 16);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G8_prt_qt_limit ) >> 8);
						txbuff[k++] = (uint8_t)(*((uint32_t*)&G8_prt_qt_limit ));	
						
						txbuff[k++] = (uint8_t)(*((uint32_t*)&OFFSET_prt_qt_limit ) >> 24);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&OFFSET_prt_qt_limit ) >> 16);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&OFFSET_prt_qt_limit ) >> 8);
						txbuff[k++] = (uint8_t)(*((uint32_t*)&OFFSET_prt_qt_limit ));	
									
						txbuff[k++] = 0x10;	
						txbuff[k++] = 0x03;	
						HAL_UART_Transmit(&huart1,txbuff,k,10); 
						
						
//					  Sol_on_time = default_nvitem.Sol_on_time;
//					  SOl_off_time =  default_nvitem.SOl_off_time;				
							
					  memcpy(run_data,init_run_data,sizeof(init_run_data));						
					break;
					
					case GRADE_SET: 	/* SYS_CONFIG VALUE MEMORY SAVE*/	
						RUN_ACTIVE_NUM = GRADE_SET;
					  uint32_t tmp;
				//		run_active(run_data[2],run_data[3]); 	
            i = 4;					
						tmp  =    run_data[i++]&0xFF;
						tmp  +=  ((run_data[i++]&0xFF)<<8);
						tmp  +=  ((run_data[i++]&0xFF)<<16);
						tmp  +=  ((run_data[i++]&0xFF)<<24);
						default_nvitem.Grader_1_UL = *((float*)&tmp);
					  Grader_1_UL = default_nvitem.Grader_1_UL;
					
					  tmp  =    run_data[i++]&0xFF;
						tmp  +=  ((run_data[i++]&0xFF)<<8);
						tmp  +=  ((run_data[i++]&0xFF)<<16);
						tmp  +=  ((run_data[i++]&0xFF)<<24);
						default_nvitem.Grader_2_UL = *((float*)&tmp);
					  Grader_2_UL = default_nvitem.Grader_2_UL;
					
					  tmp  =    run_data[i++]&0xFF;
						tmp  +=  ((run_data[i++]&0xFF)<<8);
						tmp  +=  ((run_data[i++]&0xFF)<<16);
						tmp  +=  ((run_data[i++]&0xFF)<<24);
						default_nvitem.Grader_3_UL = *((float*)&tmp);
					  Grader_3_UL = default_nvitem.Grader_3_UL;
						
						tmp  =    run_data[i++]&0xFF;
						tmp  +=  ((run_data[i++]&0xFF)<<8);
						tmp  +=  ((run_data[i++]&0xFF)<<16);
						tmp  +=  ((run_data[i++]&0xFF)<<24);
						default_nvitem.Grader_4_UL = *((float*)&tmp);
					  Grader_4_UL = default_nvitem.Grader_4_UL;
						
						tmp  =    run_data[i++]&0xFF;
						tmp  +=  ((run_data[i++]&0xFF)<<8);
						tmp  +=  ((run_data[i++]&0xFF)<<16);
						tmp  +=  ((run_data[i++]&0xFF)<<24);
						default_nvitem.Grader_5_UL = *((float*)&tmp);
					  Grader_5_UL = default_nvitem.Grader_5_UL;
						
						tmp  =    run_data[i++]&0xFF;
						tmp  +=  ((run_data[i++]&0xFF)<<8);
						tmp  +=  ((run_data[i++]&0xFF)<<16);
						tmp  +=  ((run_data[i++]&0xFF)<<24);
						default_nvitem.Grader_6_UL = *((float*)&tmp);
					  Grader_6_UL = default_nvitem.Grader_6_UL;
						
						tmp  =    run_data[i++]&0xFF;
						tmp  +=  ((run_data[i++]&0xFF)<<8);
						tmp  +=  ((run_data[i++]&0xFF)<<16);
						tmp  +=  ((run_data[i++]&0xFF)<<24);
						default_nvitem.Grader_7_UL = *((float*)&tmp);
					  Grader_7_UL = default_nvitem.Grader_7_UL;
						
						tmp  =    run_data[i++]&0xFF;
						tmp  +=  ((run_data[i++]&0xFF)<<8);
						tmp  +=  ((run_data[i++]&0xFF)<<16);
						tmp  +=  ((run_data[i++]&0xFF)<<24);
						default_nvitem.Grader_8_UL = *((float*)&tmp);
					  Grader_8_UL = default_nvitem.Grader_8_UL;
						
						tmp  =    run_data[i++]&0xFF;
						tmp  +=  ((run_data[i++]&0xFF)<<8);
						tmp  +=  ((run_data[i++]&0xFF)<<16);
						tmp  +=  ((run_data[i++]&0xFF)<<24);
						default_nvitem.Off_size_UL = *((float*)&tmp);
					  Off_size_UL = default_nvitem.Off_size_UL;
						
						tmp  =    run_data[i++]&0xFF;
						tmp  +=  ((run_data[i++]&0xFF)<<8);
						tmp  +=  ((run_data[i++]&0xFF)<<16);
						tmp  +=  ((run_data[i++]&0xFF)<<24);
						default_nvitem.Grader_1_LL = *((float*)&tmp);
					  Grader_1_LL = default_nvitem.Grader_1_LL;
					
					  tmp  =    run_data[i++]&0xFF;
						tmp  +=  ((run_data[i++]&0xFF)<<8);
						tmp  +=  ((run_data[i++]&0xFF)<<16);
						tmp  +=  ((run_data[i++]&0xFF)<<24);
						default_nvitem.Grader_2_LL = *((float*)&tmp);
					  Grader_2_LL = default_nvitem.Grader_2_LL;
					
					  tmp  =    run_data[i++]&0xFF;
						tmp  +=  ((run_data[i++]&0xFF)<<8);
						tmp  +=  ((run_data[i++]&0xFF)<<16);
						tmp  +=  ((run_data[i++]&0xFF)<<24);
						default_nvitem.Grader_3_LL = *((float*)&tmp);
					  Grader_3_LL = default_nvitem.Grader_3_LL;
						
						tmp  =    run_data[i++]&0xFF;
						tmp  +=  ((run_data[i++]&0xFF)<<8);
						tmp  +=  ((run_data[i++]&0xFF)<<16);
						tmp  +=  ((run_data[i++]&0xFF)<<24);
						default_nvitem.Grader_4_LL = *((float*)&tmp);
					  Grader_4_LL = default_nvitem.Grader_4_LL;
						
						tmp  =    run_data[i++]&0xFF;
						tmp  +=  ((run_data[i++]&0xFF)<<8);
						tmp  +=  ((run_data[i++]&0xFF)<<16);
						tmp  +=  ((run_data[i++]&0xFF)<<24);
						default_nvitem.Grader_5_LL = *((float*)&tmp);
					  Grader_5_LL = default_nvitem.Grader_5_LL;
						
						tmp  =    run_data[i++]&0xFF;
						tmp  +=  ((run_data[i++]&0xFF)<<8);
						tmp  +=  ((run_data[i++]&0xFF)<<16);
						tmp  +=  ((run_data[i++]&0xFF)<<24);
						default_nvitem.Grader_6_LL = *((float*)&tmp);
					  Grader_6_LL = default_nvitem.Grader_6_LL;
						
						tmp  =    run_data[i++]&0xFF;
						tmp  +=  ((run_data[i++]&0xFF)<<8);
						tmp  +=  ((run_data[i++]&0xFF)<<16);
						tmp  +=  ((run_data[i++]&0xFF)<<24);
						default_nvitem.Grader_7_LL = *((float*)&tmp);
					  Grader_7_LL = default_nvitem.Grader_7_LL;
						
						tmp  =    run_data[i++]&0xFF;
						tmp  +=  ((run_data[i++]&0xFF)<<8);
						tmp  +=  ((run_data[i++]&0xFF)<<16);
						tmp  +=  ((run_data[i++]&0xFF)<<24);
						default_nvitem.Grader_8_LL = *((float*)&tmp);
					  Grader_8_LL = default_nvitem.Grader_8_LL;
						
						tmp  =    run_data[i++]&0xFF;
						tmp  +=  ((run_data[i++]&0xFF)<<8);
						tmp  +=  ((run_data[i++]&0xFF)<<16);
						tmp  +=  ((run_data[i++]&0xFF)<<24);
						default_nvitem.Off_size_LL = *((float*)&tmp);
					  Off_size_LL = default_nvitem.Off_size_LL;
						
						
						default_nvitem.G1PACKER_Cnt =(((uint8_t)run_data[i++] & 0xFF));
						G1PACKER_Cnt = default_nvitem.G1PACKER_Cnt;
						for(int j = 0 ; j < G1PACKER_Cnt; )
						{
							default_nvitem.G1PACKER_Num[j]=(((uint8_t)run_data[i++] & 0xFF));
							G1PACKER_Num[j]=default_nvitem.G1PACKER_Num[j];
							j++;
						}
					
						default_nvitem.G2PACKER_Cnt =(((uint8_t)run_data[i++] & 0xFF));
						G2PACKER_Cnt = default_nvitem.G2PACKER_Cnt;
						for(int j=0 ; j < G2PACKER_Cnt; )
						{
							default_nvitem.G2PACKER_Num[j]=(((uint8_t)run_data[i++] & 0xFF));
							G2PACKER_Num[j]=default_nvitem.G2PACKER_Num[j];
							j++;
						}
						
						default_nvitem.G3PACKER_Cnt =(((uint8_t)run_data[i++] & 0xFF));
						G3PACKER_Cnt = default_nvitem.G3PACKER_Cnt;
						for(int j=0 ; j < G3PACKER_Cnt; )
						{
							default_nvitem.G3PACKER_Num[j]=(((uint8_t)run_data[i++] & 0xFF));
							G3PACKER_Num[j]=default_nvitem.G3PACKER_Num[j];
							j++;
						}
						
						default_nvitem.G4PACKER_Cnt =(((uint8_t)run_data[i++] & 0xFF));
						G4PACKER_Cnt = default_nvitem.G4PACKER_Cnt;
						for(int j=0 ; j < G4PACKER_Cnt; )
						{
							default_nvitem.G4PACKER_Num[j]=(((uint8_t)run_data[i++] & 0xFF));
							G4PACKER_Num[j]=default_nvitem.G4PACKER_Num[j];
							j++;
						}
						
						default_nvitem.G5PACKER_Cnt =(((uint8_t)run_data[i++] & 0xFF));
						G5PACKER_Cnt = default_nvitem.G5PACKER_Cnt;
						for(int j=0 ; j < G5PACKER_Cnt; )
						{
							default_nvitem.G5PACKER_Num[j]=(((uint8_t)run_data[i++] & 0xFF));
							G5PACKER_Num[j]=default_nvitem.G5PACKER_Num[j];
							j++;
						}
						
						default_nvitem.G6PACKER_Cnt =(((uint8_t)run_data[i++] & 0xFF));
						G6PACKER_Cnt = default_nvitem.G6PACKER_Cnt;
						for(int j=0 ; j < G6PACKER_Cnt; )
						{
							default_nvitem.G6PACKER_Num[j]=(((uint8_t)run_data[i++] & 0xFF));
							G6PACKER_Num[j]=default_nvitem.G6PACKER_Num[j];
							j++;
						}
						
						default_nvitem.G7PACKER_Cnt =(((uint8_t)run_data[i++] & 0xFF));
						G7PACKER_Cnt = default_nvitem.G7PACKER_Cnt;
						for(int j=0 ; j < G7PACKER_Cnt; )
						{
							default_nvitem.G7PACKER_Num[j]=(((uint8_t)run_data[i++] & 0xFF));
							G7PACKER_Num[j]=default_nvitem.G7PACKER_Num[j];
							j++;
						}
						
						default_nvitem.G8PACKER_Cnt =(((uint8_t)run_data[i++] & 0xFF));
						G8PACKER_Cnt = default_nvitem.G8PACKER_Cnt;
						for(int j=0 ; j < G8PACKER_Cnt; )
						{
							default_nvitem.G8PACKER_Num[j]=(((uint8_t)run_data[i++] & 0xFF));
							G8PACKER_Num[j]=default_nvitem.G8PACKER_Num[j];
							j++;
						}
						
						default_nvitem.Packer1_sol_cnt = (((uint8_t)run_data[i++] & 0xFF));
						Packer1_sol_cnt = default_nvitem.Packer1_sol_cnt;
						
						default_nvitem.Packer2_sol_cnt = (((uint8_t)run_data[i++] & 0xFF));
						Packer2_sol_cnt = default_nvitem.Packer2_sol_cnt;
						
						default_nvitem.Packer3_sol_cnt = (((uint8_t)run_data[i++] & 0xFF));
						Packer3_sol_cnt = default_nvitem.Packer3_sol_cnt;
						
						default_nvitem.Packer4_sol_cnt = (((uint8_t)run_data[i++] & 0xFF));
						Packer4_sol_cnt = default_nvitem.Packer4_sol_cnt;
						
						default_nvitem.Packer5_sol_cnt = (((uint8_t)run_data[i++] & 0xFF));
						Packer5_sol_cnt = default_nvitem.Packer5_sol_cnt;
						
						default_nvitem.Packer6_sol_cnt = (((uint8_t)run_data[i++] & 0xFF));
						Packer6_sol_cnt = default_nvitem.Packer6_sol_cnt;
						
						default_nvitem.Packer7_sol_cnt = (((uint8_t)run_data[i++] & 0xFF));
						Packer7_sol_cnt = default_nvitem.Packer7_sol_cnt;
						
						default_nvitem.Packer8_sol_cnt = (((uint8_t)run_data[i++] & 0xFF));
						Packer8_sol_cnt = default_nvitem.Packer8_sol_cnt;				

						default_nvitem.G1_Prt = (((uint8_t)run_data[i++] & 0xFF));
						G1_Prt = default_nvitem.G1_Prt;		
						
						default_nvitem.G2_Prt = (((uint8_t)run_data[i++] & 0xFF));
						G2_Prt = default_nvitem.G2_Prt;		
						
						default_nvitem.G3_Prt = (((uint8_t)run_data[i++] & 0xFF));
						G3_Prt = default_nvitem.G3_Prt;		
						
						default_nvitem.G4_Prt = (((uint8_t)run_data[i++] & 0xFF));
						G4_Prt = default_nvitem.G4_Prt;		
						
						default_nvitem.G5_Prt = (((uint8_t)run_data[i++] & 0xFF));
						G5_Prt = default_nvitem.G5_Prt;		
						
						default_nvitem.G6_Prt = (((uint8_t)run_data[i++] & 0xFF));
						G6_Prt = default_nvitem.G6_Prt;		
						
						default_nvitem.G7_Prt = (((uint8_t)run_data[i++] & 0xFF));
						G7_Prt = default_nvitem.G7_Prt;		
						
						default_nvitem.G8_Prt = (((uint8_t)run_data[i++] & 0xFF));
						G8_Prt = default_nvitem.G8_Prt;		
						
						default_nvitem.Offset_Prt = (((uint8_t)run_data[i++] & 0xFF));
						Offset_Prt = default_nvitem.Offset_Prt;	
						
  					update_nvitems();	
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET); HAL_Delay(100);
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET); HAL_Delay(100);
					  k =0;
					  txbuff[k++] = 0x10;	
						txbuff[k++] = 0x02;	
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_1_UL) >> 24);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_1_UL) >> 16);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_1_UL) >> 8);
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_1_UL));	
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_2_UL) >> 24);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_2_UL) >> 16);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_2_UL) >> 8);
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_2_UL));
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_3_UL) >> 24);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_3_UL) >> 16);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_3_UL) >> 8);
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_3_UL));
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_4_UL) >> 24);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_4_UL) >> 16);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_4_UL) >> 8);
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_4_UL));
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_5_UL) >> 24);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_5_UL) >> 16);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_5_UL) >> 8);
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_5_UL));
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_6_UL) >> 24);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_6_UL) >> 16);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_6_UL) >> 8);
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_6_UL));
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_7_UL) >> 24);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_7_UL) >> 16);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_7_UL) >> 8);
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_7_UL));
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_8_UL) >> 24);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_8_UL) >> 16);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_8_UL) >> 8);
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_8_UL));
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Off_size_UL) >> 24);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Off_size_UL) >> 16);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Off_size_UL) >> 8);
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Off_size_UL));
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_1_LL) >> 24);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_1_LL) >> 16);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_1_LL) >> 8);
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_1_LL));	
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_2_LL) >> 24);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_2_LL) >> 16);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_2_LL) >> 8);
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_2_LL));
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_3_LL) >> 24);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_3_LL) >> 16);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_3_LL) >> 8);
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_3_LL));
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_4_LL) >> 24);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_4_LL) >> 16);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_4_LL) >> 8);
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_4_LL));
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_5_LL) >> 24);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_5_LL) >> 16);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_5_LL) >> 8);
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_5_LL));
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_6_LL) >> 24);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_6_LL) >> 16);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_6_LL) >> 8);
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_6_LL));
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_7_LL) >> 24);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_7_LL) >> 16);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_7_LL) >> 8);
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_7_LL));
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_8_LL) >> 24);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_8_LL) >> 16);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_8_LL) >> 8);
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Grader_8_LL));
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Off_size_LL) >> 24);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Off_size_LL) >> 16);		
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Off_size_LL) >> 8);
						txbuff[k++] = (uint8_t)(*((uint32_t*)&Off_size_LL));
					
  					txbuff[k++] = G1PACKER_Cnt;		
						for(int i =0; i < G1PACKER_Cnt;i++)
						{
							txbuff[k++] = G1PACKER_Num[i];					
						}
						
						txbuff[k++] = G2PACKER_Cnt;		
						for(int i =0; i < G2PACKER_Cnt;i++)
						{
							txbuff[k++] = G2PACKER_Num[i];					
						}
						
						txbuff[k++] = G3PACKER_Cnt;		
						for(int i =0; i < G3PACKER_Cnt;i++)
						{
							txbuff[k++] = G3PACKER_Num[i];					
						}
						
						txbuff[k++] = G4PACKER_Cnt;		
						for(int i =0; i < G4PACKER_Cnt;i++)
						{
							txbuff[k++] = G4PACKER_Num[i];					
						}
						
						txbuff[k++] = G5PACKER_Cnt;		
						for(int i =0; i < G5PACKER_Cnt;i++)
						{
							txbuff[k++] = G5PACKER_Num[i];					
						}
						
						txbuff[k++] = G6PACKER_Cnt;		
						for(int i =0; i < G6PACKER_Cnt;i++)
						{
							txbuff[k++] = G6PACKER_Num[i];					
						}
						
						txbuff[k++] = G7PACKER_Cnt;		
						for(int i =0; i < G7PACKER_Cnt;i++)
						{
							txbuff[k++] = G7PACKER_Num[i];					
						}
						
						txbuff[k++] = G8PACKER_Cnt;		
						for(int i =0; i < G8PACKER_Cnt;i++)
						{
							txbuff[k++] = G8PACKER_Num[i];					
						}
						
						txbuff[k++] = Packer1_sol_cnt;		
						txbuff[k++] = Packer2_sol_cnt;		
						txbuff[k++] = Packer3_sol_cnt;		
						txbuff[k++] = Packer4_sol_cnt;		
						txbuff[k++] = Packer5_sol_cnt;		
						txbuff[k++] = Packer6_sol_cnt;		
						txbuff[k++] = Packer7_sol_cnt;		
						txbuff[k++] = Packer8_sol_cnt;		
						
						txbuff[k++] = G1_Prt;		
						txbuff[k++] = G2_Prt;		
						txbuff[k++] = G3_Prt;		
						txbuff[k++] = G4_Prt;		
						txbuff[k++] = G5_Prt;		
						txbuff[k++] = G6_Prt;		
						txbuff[k++] = G7_Prt;		
						txbuff[k++] = G8_Prt;	
						txbuff[k++] = Offset_Prt;	
							
						txbuff[k++] = 0x10;	
						txbuff[k++] = 0x03;	
						HAL_UART_Transmit(&huart1,txbuff,k,10); 	
						
						G1_CNT = G1PACKER_Cnt;
						G2_CNT = G2PACKER_Cnt;
						G3_CNT = G3PACKER_Cnt;
						G4_CNT = G4PACKER_Cnt;
						G5_CNT = G5PACKER_Cnt;
						G6_CNT = G6PACKER_Cnt;
						G7_CNT = G7PACKER_Cnt;
						G8_CNT = G8PACKER_Cnt;	
	
						P1_CNT = Packer1_sol_cnt;
						P2_CNT = Packer2_sol_cnt;
						P3_CNT = Packer3_sol_cnt;
						P4_CNT = Packer4_sol_cnt;
						P5_CNT = Packer5_sol_cnt;
						P6_CNT = Packer6_sol_cnt;
						P7_CNT = Packer7_sol_cnt;
						P8_CNT = Packer8_sol_cnt;	

							
						memcpy(run_data,init_run_data,sizeof(init_run_data));
						break;
					
					case INIT_CFG_SET:   /* INIT_CONFIG VALUE MEMORY SAVE*/	
						RUN_ACTIVE_NUM = INIT_CFG_SET;	
						memcpy(run_data,init_run_data,sizeof(init_run_data));	
				//	  Grader_Cfg_Init();
					  	
					break;	
					
				}
			break;
/*---------------WRITE SECTION END--------------------------*/	
				
/*---------------RUN ACTIVE SECTION START--------------------------*/					
			case ACTIVE : 
				switch (run_data[3])	
				{
					case RUN_ACTIVE:	/* RUN_ACTIVE START*/	
						RUN_ACTIVE_NUM = RUN_ACTIVE;
					  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET); HAL_Delay(100);
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET); HAL_Delay(100);
					  memcpy(run_data,init_run_data,sizeof(init_run_data));
					break;	
					
					case NORUN_ACTIVE:	/* RUN_ACTIVE STOP */	
						RUN_ACTIVE_NUM = NORUN_ACTIVE;		
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET); HAL_Delay(100);
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET); HAL_Delay(100);					
					  memcpy(run_data,init_run_data,sizeof(init_run_data));
					break;					
				}	
			break;
/*---------------RUN ACTIVE SECTION END--------------------------*/		
				
/*---------------MEASUREMENT SECTION START--------------------------*/					
			case MEASUREMENT : 
				switch (run_data[3])	
				{
					case LOADCELL_ZERO_MEASUREMENT: 	/* LOADCELL_ZERO_MEASUREMENT START*/	
						RUN_ACTIVE_NUM = LOADCELL_ZERO_MEASUREMENT;
						memcpy(run_data,init_run_data,sizeof(init_run_data));
					  for(int i =0; i<5;i++)
					  {
					  default_nvitem.Loadcell_Zero=LOADCELL_ZERO();
						}
						
						Loadcell_Zero = default_nvitem.Loadcell_Zero;
					  update_nvitems();  
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET); HAL_Delay(100);
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET); HAL_Delay(100);	
						txbuff[0] = 0x10;	
						txbuff[1] = 0x02;	
						txbuff[2] = (uint8_t)(*((uint32_t*)&Loadcell_Zero ) >> 24);		
						txbuff[3] = (uint8_t)(*((uint32_t*)&Loadcell_Zero ) >> 16);		
						txbuff[4] = (uint8_t)(*((uint32_t*)&Loadcell_Zero ) >> 8);
						txbuff[5] = (uint8_t)(*((uint32_t*)&Loadcell_Zero ));	
						txbuff[6] = 0x10;	
						txbuff[7] = 0x03;	
						HAL_UART_Transmit(&huart1,txbuff,8,10); 					     			
					break;	
					
					case LOADCELL_WEIGHT_MEASUREMENT: 	/* LOADCELL_WEIGHT_MEASUREMENT START */	
						RUN_ACTIVE_NUM = LOADCELL_WEIGHT_MEASUREMENT;	
						memcpy(run_data,init_run_data,sizeof(init_run_data));
					  for(int i =0; i<5;i++)
					  {
					   default_nvitem.Loadcell_Weight=LOADCELL_WEIGHT(Loadcell_Zero);		
						}
					  Loadcell_Weight = default_nvitem.Loadcell_Weight;
					  update_nvitems();
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET); HAL_Delay(100);
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET); HAL_Delay(100);
						txbuff[0] = 0x10;	
						txbuff[1] = 0x02;	
						txbuff[2] = (uint8_t)(*((uint32_t*)&Loadcell_Weight ) >> 24);		
						txbuff[3] = (uint8_t)(*((uint32_t*)&Loadcell_Weight ) >> 16);		
						txbuff[4] = (uint8_t)(*((uint32_t*)&Loadcell_Weight ) >> 8);
						txbuff[5] = (uint8_t)(*((uint32_t*)&Loadcell_Weight ));	
						txbuff[6] = 0x10;	
						txbuff[7] = 0x03;	
						HAL_UART_Transmit(&huart1,txbuff,8,10); 	
					break;		
					
					case GRADER_TIMING_MEASUREMENT:	/* LOADCELL_WEIGHT_MEASUREMENT START */	
						RUN_ACTIVE_NUM = GRADER_TIMING_MEASUREMENT;	
					  send_count = true;
					  sendvalue = false;
					  send_cnt =0;
					  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET); HAL_Delay(100);
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET); HAL_Delay(100);
					  memset (data_strem, 0, sizeof(data_strem));
						memcpy(run_data,init_run_data,sizeof(init_run_data));
					break;
					
					case SOL_TEST_MEASUREMENT:	/* SOL_TEST START */	
						RUN_ACTIVE_NUM = SOL_TEST_MEASUREMENT;			  
					  SOL_SELECT =    (((uint32_t)run_data[4]));
						SOL_SELECT +=   (((uint32_t)run_data[5])<< 8);
						SOL_SELECT +=   (((uint32_t)run_data[6])<< 16);
						SOL_SELECT +=   (((uint32_t)run_data[7])<< 24);		
					  
					  if (SOL_SELECT < 40)
						{
							SOL_RUN_(SOL_SELECT);
							memcpy(run_data,init_run_data,sizeof(init_run_data)); 
							SOL_SELECT = 0;	
						}
						else if (SOL_SELECT ==41)
						{
							SOL_TEST_RUN();
						}
						else if (SOL_SELECT ==42)
						{			
							memcpy(run_data,init_run_data,sizeof(init_run_data)); 
							SOL_SELECT = 0;	
						}	
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET); HAL_Delay(100);
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET); HAL_Delay(100);
					break;
					
					case CURENT_WEIGHT:	/* SOL_TEST START */	
						RUN_ACTIVE_NUM = CURENT_WEIGHT;	
						//run_active(run_data[2],run_data[3]); 
						memcpy(run_data,init_run_data,sizeof(init_run_data));				
						avg_float = (filtereadValue-Loadcell_Zero)*Loadcell_Weight;		
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET); HAL_Delay(100);
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET); HAL_Delay(100);					
					  txbuff[0] = 0x10;	
						txbuff[1] = 0x02;	
						txbuff[2] = (uint8_t)(*((uint32_t*)&avg_float ) >> 24);		
						txbuff[3] = (uint8_t)(*((uint32_t*)&avg_float ) >> 16);		
						txbuff[4] = (uint8_t)(*((uint32_t*)&avg_float ) >> 8);
						txbuff[5] = (uint8_t)(*((uint32_t*)&avg_float ));	
					  txbuff[6] = 0x10;
						txbuff[7] = 0x03;	
						HAL_UART_Transmit(&huart1,txbuff,8,10); 
						avg_float =0;
					break;
					
					case CURENT_WEIGHT_NOFILTER:	/* SOL_TEST START */	
						RUN_ACTIVE_NUM = CURENT_WEIGHT_NOFILTER;			
            avg_real =    sensorValue;					
					  txbuff[0] = 0x10;	
						txbuff[1] = 0x02;	
						txbuff[2] = (uint8_t)(*((uint32_t*)&avg_real ) >> 24);		
						txbuff[3] = (uint8_t)(*((uint32_t*)&avg_real ) >> 16);		
						txbuff[4] = (uint8_t)(*((uint32_t*)&avg_real ) >> 8);
						txbuff[5] = (uint8_t)(*((uint32_t*)&avg_real ));	
						txbuff[6] = 0x10;
						txbuff[7] = 0x03;	
						HAL_UART_Transmit(&huart1,txbuff,8,10); 
					  memcpy(run_data,init_run_data,sizeof(init_run_data));		
						avg_float =0;
					break;
					
					case CURENT_WEIGHT_FILTER:	/* SOL_TEST START */	
						RUN_ACTIVE_NUM = CURENT_WEIGHT;		
						avg_real = 	filtereadValue;
					  txbuff[0] = 0x10;	
						txbuff[1] = 0x02;	
						txbuff[2] = (uint8_t)(*((uint32_t*)&avg_real ) >> 24);		
						txbuff[3] = (uint8_t)(*((uint32_t*)&avg_real ) >> 16);		
						txbuff[4] = (uint8_t)(*((uint32_t*)&avg_real ) >> 8);
						txbuff[5] = (uint8_t)(*((uint32_t*)&avg_real ));	
					  txbuff[6] = 0x10;
						txbuff[7] = 0x03;	
						HAL_UART_Transmit(&huart1,txbuff,8,10); 
					  memcpy(run_data,init_run_data,sizeof(init_run_data));			
						avg_real =0;
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
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6 
                          |GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
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

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 4, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{		
	uint32_t Sol_run_Start = 1;
	uint8_t data[16];
	uint32_t i_cnt =0, i=0, j =2;
	uint8_t j_cnt =0;
	avg = 0;
	float resultData =0;
	uint32_t grade =0;
	uint8_t prt = 0; 
	uint8_t data_count =0;
	uint8_t avg_cnt =0;
//	msTimer = 0;
	
	if (RUN_ACTIVE_NUM == RUN_ACTIVE)
	{
		for (i_cnt = 0; i_cnt <= 255; i_cnt++)
		{
			if (i_cnt == Sol_run_Start)
			{
					SOL_RUN();
			}
			
			if (i_cnt == (Sol_run_Start+Sol_on_time))
			{
					SOL_RUN_OFF();
			}
			
			if ( i_cnt >=  Measurement_Delay && i_cnt <= Measurement_EndTime )
			{
				avg += filtereadValue;
				avg_cnt++;
			}
			
			if(i_cnt == Measurement_EndTime)
			{
				resultData = avg/avg_cnt;
				resultData = (resultData-Loadcell_Zero)*Loadcell_Weight;
				resultData = ceil(resultData*10)/10;
			}
			
			if(i_cnt == Measurement_EndTime+1)
			{
				if(resultData <= Grader_1_UL && resultData >= Grader_1_LL)
				{				
					switch(G1_Prt)
					{
						case 0:
						RearLine_Prt[0] = 0;	
					  prt = 0;
						break;
					
						case 1:
							if(G1_prt_qt_limit == 0)
							{
								RearLine_Prt[0] = Prt1_run;	
								prt = 1;
							}
							else if(G1_prt_qt_limit == 1)
							{
								RearLine_Prt[0] = 0;	
								prt = 0;
							}
							else if(G1_prt_qt_limit > 1)
							{
								RearLine_Prt[0] = Prt1_run;		
								prt = 1;
								G1_prt_qt_limit--;
							}					
							break;
					
						case 2:
							if(G1_prt_qt_limit == 0)
							{
								RearLine_Prt[0] = Prt2_run;	
								prt = 2;
							}
							else if(G1_prt_qt_limit == 1)
							{
								RearLine_Prt[0] = 0;	
								prt = 0;
							}
							else if(G1_prt_qt_limit > 1)
							{
								RearLine_Prt[0] = Prt2_run;		
								prt = 2;
								G1_prt_qt_limit--;
							}
							break;
					}
					
				if(G1_CNT > 0)
				{
					switch(G1PACKER_Num[G1_CNT-1])
					{
						case 1:																													
								if(P1_CNT > 0)
								{
									RearLine[0] = Packer1Sol_Run[P1_CNT-1];	
									grade = 1;
									P1_CNT--;
									G1_CNT--;
								}														
						break;
						
						case 2:																														
								if(P2_CNT > 0)
								{
									RearLine[0] = Packer2Sol_Run[P2_CNT-1];	
									grade = 1;
									P2_CNT--;
									G1_CNT--;
								}														
						break;
							
						case 3:																											
								if(P3_CNT > 0)
								{
									RearLine[0] = Packer3Sol_Run[P3_CNT-1];	
									grade = 1;
									P3_CNT--;
									G1_CNT--;
								}														
						break;	
							
						case 4:																														
								if(P4_CNT > 0)
								{
									RearLine[0] = Packer4Sol_Run[P4_CNT-1];	
									grade = 1;
									P4_CNT--;
									G1_CNT--;
								}														
						break;	
							
						case 5:
								if(P5_CNT > 0)
								{
									RearLine[0] = Packer5Sol_Run[P5_CNT-1];		
									grade = 1;
									P5_CNT--;
									G1_CNT--;
								}														
						break;
							
						case 6:
								if(P6_CNT > 0)
								{
									RearLine[0] = Packer6Sol_Run[P6_CNT-1];	
										grade = 1;
									P6_CNT--;
									G1_CNT--;
								}														
						break;
								
						case 7:
								if(P7_CNT > 0)
								{
									RearLine[0] = Packer7Sol_Run[P7_CNT-1];	
									grade = 1;
									P7_CNT--;
									G1_CNT--;
								}														
						break;	
								
						case 8:																														
								if(P8_CNT > 0)
								{
									RearLine[0] = Packer8Sol_Run[P8_CNT-1];	
									grade = 1;
									P8_CNT--;
									G1_CNT--;
								}														
						break;						
						}			 	
				}
				else
				{
					RearLine[0]=NORUN;
					grade = 0;
				}
			}
			
			else if(resultData <= Grader_2_UL && resultData >= Grader_2_LL)
			{
				switch(G2_Prt)
				{
					case 0:
						RearLine_Prt[0] = 0;	
					  prt = 0;
					break;
					
					case 1:
						if(G2_prt_qt_limit == 0)
						{
							RearLine_Prt[0] = Prt1_run;	
							prt = 1;
						}
						else if(G2_prt_qt_limit == 1)
						{
							RearLine_Prt[0] = 0;	
							prt = 0;
						}
						else if(G2_prt_qt_limit > 1)
						{
							RearLine_Prt[0] = Prt1_run;		
							prt = 1;
							G2_prt_qt_limit--;
						}					
						break;
					
					case 2:
						if(G2_prt_qt_limit == 0) //PRT No Limit
						{
							RearLine_Prt[0] = Prt2_run;	
							prt = 2;
						}
						else if(G2_prt_qt_limit == 1) //PRT STOP
						{
							RearLine_Prt[0] = 0;	
							prt = 0;
						}
						else if(G2_prt_qt_limit > 1) //PRT   < Limit
						{
							RearLine_Prt[0] = Prt2_run;		
							prt = 2;
							G2_prt_qt_limit--;
						}
						break;
				}
						
				if(G2_CNT > 0)
				{
					switch(G2PACKER_Num[G2_CNT-1])
					{
						case 1:																														
								if(P1_CNT > 0)
								{
									RearLine[0] = Packer1Sol_Run[P1_CNT-1];	
									grade = 2;	
									P2_CNT--;
									G2_CNT--;
								}														
						break;
						
						case 2:
								if(P2_CNT > 0)
								{
									RearLine[0] = Packer2Sol_Run[P2_CNT-1];	
									grade = 2;	
									P2_CNT--;
									G2_CNT--;
								}														
						break;
							
						case 3:
								if(P3_CNT > 0)
								{
									RearLine[0] = Packer3Sol_Run[P3_CNT-1];	
									grade = 2;	
									P2_CNT--;
									G2_CNT--;
								}														
						break;	
							
						case 4:
								if(P4_CNT > 0)
								{
									RearLine[0] = Packer4Sol_Run[P4_CNT-1];	
									grade = 2;	
									P2_CNT--;
									G2_CNT--;
								}														
						break;	
							
						case 5:																														
								if(P5_CNT > 0)
								{
									RearLine[0] = Packer5Sol_Run[P5_CNT-1];	
									grade = 2;	
									P2_CNT--;
									G2_CNT--;
								}														
						break;
							
						case 6:
								if(P6_CNT > 0)
								{
									RearLine[0] = Packer6Sol_Run[P6_CNT-1];	
									grade = 2;	
									P2_CNT--;
									G2_CNT--;
								}														
						break;
					
						case 7:
								if(P7_CNT > 0)
								{
									RearLine[0] = Packer7Sol_Run[P7_CNT-1];	
								  grade = 2;	
									P2_CNT--;
									G2_CNT--;
								}														
						break;	

						case 8:
								if(P8_CNT > 0)
								{
									RearLine[0] = Packer8Sol_Run[P8_CNT-1];	
									grade = 2;	
									P2_CNT--;
									G2_CNT--;
								}														
							break;						
					}				
				}
				else
				{
					RearLine[0]=NORUN;
					grade = 0;
				}
			}		 
			
			else if(resultData <= Grader_3_UL && resultData >= Grader_3_LL)
			{			
				switch(G3_Prt)
				{
					case 0:
						RearLine_Prt[0] = 0;	
					  prt = 0;
						break;
					
					case 1:
						if(G3_prt_qt_limit == 0)
						{
							RearLine_Prt[0] = Prt1_run;	
							prt = 1;
						}
						else if(G3_prt_qt_limit == 1)
						{
							RearLine_Prt[0] = 0;	
							prt = 0;
						}
						else if(G3_prt_qt_limit > 1)
						{
							RearLine_Prt[0] = Prt1_run;		
							prt = 1;
							G3_prt_qt_limit--;
						}					
						break;
					
					case 2:
						if(G3_prt_qt_limit == 0) //PRT No Limit
						{
							RearLine_Prt[0] = Prt2_run;	
							prt = 2;
						}
						else if(G3_prt_qt_limit == 1) //PRT STOP
						{
							RearLine_Prt[0] = 0;	
							prt = 0;
						}
						else if(G3_prt_qt_limit > 1) //PRT   < Limit
						{
							RearLine_Prt[0] = Prt2_run;		
							prt = 2;
							G3_prt_qt_limit--;
						}
						break;
				}
				
				
				if(G3_CNT > 0)
				{			
					switch(G3PACKER_Num[G3_CNT-1])
					{
						case 1:																						
								if(P1_CNT > 0)
								{
									RearLine[0] = Packer1Sol_Run[P1_CNT-1];		
									grade = 3;
									P3_CNT--; G3_CNT--;
								}							
							break;
						
						case 2:																						
							if(P2_CNT > 0)
							{
								RearLine[0] = Packer2Sol_Run[P2_CNT-1];	
								grade = 3;
								P3_CNT--; G3_CNT--;
							}							
							break;
							
						case 3:																					
							if(P3_CNT > 0)
							{
								RearLine[0] = Packer3Sol_Run[P3_CNT-1];		
								grade = 3;
								P3_CNT--; G3_CNT--;
							}							
							break;	
							
						case 4:																							
							if(P4_CNT > 0)
							{
								RearLine[0] = Packer4Sol_Run[P4_CNT-1];	
								grade = 3;
								P3_CNT--; G3_CNT--;
							}
							break;	
							
						case 5:																						
							if(P5_CNT > 0)
							{
								RearLine[0] = Packer5Sol_Run[P5_CNT-1];	
								grade = 3;
								P3_CNT--; G3_CNT--;
							}							
							break;
							
						case 6:
							if(P6_CNT > 0)
							{
								RearLine[0] = Packer6Sol_Run[P6_CNT-1];	
								grade = 3;
								P3_CNT--; G3_CNT--;
							}							
							break;
					
						case 7:																							
								if(P7_CNT > 0)
								{
									RearLine[0] = Packer7Sol_Run[P7_CNT-1];	
									grade = 3;
									P3_CNT--; G3_CNT--;
								}											
						break;	

						case 8:																						
								if(P8_CNT > 0)
								{
									RearLine[0] = Packer8Sol_Run[P8_CNT-1];		
									grade = 3;
									P3_CNT--; G3_CNT--;
								}														
						break;						
						}				
				}
				else
				{
					RearLine[0]=NORUN;
					grade = 0;
				}
			}
			
			else if(resultData <= Grader_4_UL && resultData >= Grader_4_LL)
			{				
				switch(G4_Prt)
				{
					case 0:
						RearLine_Prt[0] = 0;	
					  prt = 0;
					break;
					
					case 1:
						if(G4_prt_qt_limit == 0)
						{
							RearLine_Prt[0] = Prt1_run;	
							prt = 1;
						}
						else if(G4_prt_qt_limit == 1)
						{
							RearLine_Prt[0] = 0;	
							prt = 0;
						}
						else if(G4_prt_qt_limit > 1)
						{
							RearLine_Prt[0] = Prt1_run;		
							prt = 1;
							G4_prt_qt_limit--;
						}					
						break;
					
					case 2:
						if(G4_prt_qt_limit == 0) //PRT No Limit
						{
							RearLine_Prt[0] = Prt2_run;	
							prt = 2;
						}
						else if(G4_prt_qt_limit == 1) //PRT STOP
						{
							RearLine_Prt[0] = 0;	
							prt = 0;
						}
						else if(G4_prt_qt_limit > 1) //PRT   < Limit
						{
							RearLine_Prt[0] = Prt2_run;		
							prt = 2;
							G4_prt_qt_limit--;
						}
						break;
				}
				
				
				if(G4_CNT > 0)
				{
					switch(G4PACKER_Num[G4_CNT-1])
					{
						case 1:																					
								if(P1_CNT >= 0)
								{
									RearLine[0] = Packer1Sol_Run[P1_CNT-1];	
									grade = 4;
									P4_CNT--; G4_CNT--;
								}														
						break;
						
						case 2:																						
								if(P2_CNT >= 0) 
								{
									RearLine[0] = Packer2Sol_Run[P2_CNT-1];	
									grade = 4;
									P4_CNT--; G4_CNT--;
								}														
						break;
							
						case 3:															
								if(P3_CNT >= 0)
								{
									RearLine[0] = Packer3Sol_Run[P3_CNT-1];	
									grade = 4;
									P4_CNT--; G4_CNT--;
								}														
						break;	
							
						case 4:																						
								if(P4_CNT > 0)
								{
									RearLine[0] = Packer4Sol_Run[P4_CNT-1];
									grade = 4;
									P4_CNT--; G4_CNT--;
								}											
						break;	
							
						case 5:																							
								if(P5_CNT > 0)
								{
									RearLine[0] = Packer5Sol_Run[P5_CNT-1];	
									grade = 4;
									P4_CNT--; G4_CNT--;
								}														
						break;
							
						case 6:																							
								if(P6_CNT > 0)
								{
									RearLine[0] = Packer6Sol_Run[P6_CNT-1];	
									grade = 4;
									P4_CNT--; G4_CNT--;
								}														
						break;
					
						case 7:																						
								if(P7_CNT > 0)
								{
									RearLine[0] = Packer7Sol_Run[P7_CNT-1];	
									grade = 4;
									P4_CNT--; G4_CNT--;
								}													
						break;	

						case 8:																						
								if(P8_CNT > 0)
								{
									RearLine[0] = Packer8Sol_Run[P8_CNT-1];	
									grade = 4;
									P4_CNT--; G4_CNT--;
								}													
						break;						
						}				
				}
				else
				{
					RearLine[0]=NORUN;
					grade = 0;
				}
			}
			
			else if(resultData <= Grader_5_UL && resultData >= Grader_5_LL)
			{				
				switch(G5_Prt)
				{
					case 0:
						RearLine_Prt[0] = 0;	
					  prt = 0;
					break;
					
					case 1:
						if(G5_prt_qt_limit == 0)
						{
							RearLine_Prt[0] = Prt1_run;	
							prt = 1;
						}
						else if(G5_prt_qt_limit == 1)
						{
							RearLine_Prt[0] = 0;	
							prt = 0;
						}
						else if(G5_prt_qt_limit > 1)
						{
							RearLine_Prt[0] = Prt1_run;		
							prt = 1;
							G5_prt_qt_limit--;
						}					
						break;
					
					case 2:
						if(G5_prt_qt_limit == 0) //PRT No Limit
						{
							RearLine_Prt[0] = Prt2_run;	
							prt = 2;
						}
						else if(G5_prt_qt_limit == 1) //PRT STOP
						{
							RearLine_Prt[0] = 0;	
							prt = 0;
						}
						else if(G5_prt_qt_limit > 1) //PRT   < Limit
						{
							RearLine_Prt[0] = Prt2_run;		
							prt = 2;
							G5_prt_qt_limit--;
						}
						break;
				}				
				if(G5_CNT > 0)
				{
					switch(G5PACKER_Num[G5_CNT-1])
					{
						case 1:																						
								if(P1_CNT > 0)
								{
									RearLine[0] = Packer1Sol_Run[P1_CNT-1];	
									grade = 5;
									P5_CNT--; G5_CNT--;
								}														
						break;
						
						case 2:																					
								if(P2_CNT > 0)
								{
									RearLine[0] = Packer2Sol_Run[P2_CNT-1];	
									grade = 5;
									P5_CNT--; G5_CNT--;
								}														
						break;
							
						case 3:																						
								if(P3_CNT > 0)
								{
									RearLine[0] = Packer3Sol_Run[P3_CNT-1];	
									grade = 5;
									P5_CNT--; G5_CNT--;
								}													
						break;	
							
						case 4:																						
								if(P4_CNT > 0)
								{
									RearLine[0] = Packer4Sol_Run[P4_CNT-1];	
									grade = 5;
									P5_CNT--; G5_CNT--;
								}													
						break;	
							
						case 5:																						
								if(P5_CNT > 0)
								{
									RearLine[0] = Packer5Sol_Run[P5_CNT-1];	
									grade = 5;
									P5_CNT--; G5_CNT--;
								}													
						break;
							
						case 6:																						
								if(P6_CNT > 0)
								{
									RearLine[0] = Packer6Sol_Run[P6_CNT-1];	
									grade = 5;
									P5_CNT--; G5_CNT--;
								}													
						break;
					
						case 7:																					
								if(P7_CNT > 0)
								{
									RearLine[0] = Packer7Sol_Run[P7_CNT-1];	
									grade = 5;
									P5_CNT--; G5_CNT--;
								}														
						break;	

						case 8:																							
								if(P8_CNT > 0)
								{
									RearLine[0] = Packer8Sol_Run[P8_CNT-1];	
									grade = 5;
									P5_CNT--; G5_CNT--;
								}														
						break;						
						}				
				}
				else
				{
					RearLine[0]=NORUN;
					grade = 0;
				}
			}
			
			else if(resultData <= Grader_6_UL && resultData >= Grader_6_LL)
			{		
			switch(G6_Prt)
				{
					case 0:
						RearLine_Prt[0] = 0;	
					  prt = 0;
					break;
					
					case 1:
						if(G6_prt_qt_limit == 0)
						{
							RearLine_Prt[0] = Prt1_run;	
							prt = 1;
						}
						else if(G6_prt_qt_limit == 1)
						{
							RearLine_Prt[0] = 0;	
							prt = 0;
						}
						else if(G6_prt_qt_limit > 1)
						{
							RearLine_Prt[0] = Prt1_run;		
							prt = 1;
							G6_prt_qt_limit--;
						}					
						break;
					
					case 2:
						if(G6_prt_qt_limit == 0) //PRT No Limit
						{
							RearLine_Prt[0] = Prt2_run;	
							prt = 2;
						}
						else if(G6_prt_qt_limit == 1) //PRT STOP
						{
							RearLine_Prt[0] = 0;	
							prt = 0;
						}
						else if(G6_prt_qt_limit > 1) //PRT   < Limit
						{
							RearLine_Prt[0] = Prt2_run;		
							prt = 2;
							G6_prt_qt_limit--;
						}
						break;
				}
				
				if(G6_CNT > 0)
				{
					switch(G6PACKER_Num[G6_CNT-1])
					{
						case 1:																					
							if(P1_CNT > 0)
							{
								RearLine[0] = Packer1Sol_Run[P1_CNT-1];	
								grade = 6; 
								P6_CNT--; G6_CNT--;
							}														
							break;
						
						case 2:																				
							if(P2_CNT > 0)
							{
								RearLine[0] = Packer2Sol_Run[P2_CNT-1];		
								grade = 6; 
								P6_CNT--; G6_CNT--;
							}							
							break;
							
						case 3:
							if(P3_CNT > 0)
							{
								RearLine[0] = Packer3Sol_Run[P3_CNT-1];	
								grade = 6; 
								P6_CNT--; G6_CNT--;
							}							
							break;	
							
						case 4:
							if(P4_CNT > 0)
							{
								RearLine[0] = Packer4Sol_Run[P4_CNT-1];		
								grade = 6; 
								P6_CNT--; G6_CNT--;
							}							
							break;	
							
						case 5:
							if(P5_CNT > 0)
							{
								RearLine[0] = Packer5Sol_Run[P5_CNT-1];	
								grade = 6; 
								P6_CNT--; G6_CNT--;
							}							
							break;
							
						case 6:
							if(P6_CNT > 0)
							{
								RearLine[0] = Packer6Sol_Run[P6_CNT-1];	
								grade = 6; 
								P6_CNT--; G6_CNT--;
							}							
							break;
					
						case 7:
							if(P7_CNT > 0)
							{
								RearLine[0] = Packer7Sol_Run[P7_CNT-1];	
								grade = 6; 
								P6_CNT--; G6_CNT--;
							}													
							break;	

						case 8:							
							if(P8_CNT > 0)
							{
								RearLine[0] = Packer8Sol_Run[P8_CNT-1];	
								grade = 6; 
								P6_CNT--; G6_CNT--;
							}													
							break;						
						}				
				}
				else
				{
					RearLine[0]=NORUN;
					grade = 0;
				}
			}
			
			else if(resultData <= Grader_7_UL && resultData >= Grader_7_LL)
			{		
			switch(G7_Prt)
				{
					case 0:
						RearLine_Prt[0] = 0;	
					  prt = 0;
						break;
					case 1:
						if(G7_prt_qt_limit == 0)
						{
							RearLine_Prt[0] = Prt1_run;	
							prt = 1;
						}
						else if(G7_prt_qt_limit == 1)
						{
							RearLine_Prt[0] = 0;	
							prt = 0;
						}
						else if(G7_prt_qt_limit > 1)
						{
							RearLine_Prt[0] = Prt1_run;		
							prt = 1;
							G7_prt_qt_limit--;
						}					
						break;
					case 2:
						if(G7_prt_qt_limit == 0) //PRT No Limit
						{
							RearLine_Prt[0] = Prt2_run;	
							prt = 2;
						}
						else if(G7_prt_qt_limit == 1) //PRT STOP
						{
							RearLine_Prt[0] = 0;	
							prt = 0;
						}
						else if(G7_prt_qt_limit > 1) //PRT   < Limit
						{
							RearLine_Prt[0] = Prt2_run;		
							prt = 2;
							G7_prt_qt_limit--;
						}
						break;
				}
				if(G7_CNT > 0)
				{
					switch(G7PACKER_Num[G7_CNT-1])
					{
						case 1:						
							if(P1_CNT > 0)
							{
								RearLine[0] = Packer1Sol_Run[P1_CNT-1];		
								grade = 7; 
								P7_CNT--; G7_CNT--;
							}														
							break;
						case 2:
							if(P2_CNT > 0)
							{
								RearLine[0] = Packer2Sol_Run[P2_CNT-1];	
								grade = 7; 
								P7_CNT--; G7_CNT--;
							}														
							break;
						case 3:
							if(P3_CNT > 0)
							{
								RearLine[0] = Packer3Sol_Run[P3_CNT-1];		
								grade = 7; 
								P7_CNT--; G7_CNT--;
							}													
							break;	
						case 4:
							if(P4_CNT > 0)
							{
								RearLine[0] = Packer4Sol_Run[P4_CNT-1];		
								grade = 7; 
								P7_CNT--; G7_CNT--;
							}														
							break;	
						case 5:
							if(P5_CNT > 0)
							{
								RearLine[0] = Packer5Sol_Run[P5_CNT-1];	
								grade = 7; 
								P7_CNT--; G7_CNT--;
							}							
							break;
						case 6:
							if(P6_CNT > 0)
							{
								RearLine[0] = Packer6Sol_Run[P6_CNT-1];		
								grade = 7; 
								P7_CNT--; G7_CNT--;
							}													
							break;
						case 7:
							if(P7_CNT > 0)
							{
								RearLine[0] = Packer7Sol_Run[P7_CNT-1];	
								grade = 7; 
								P7_CNT--; G7_CNT--;
							}														
							break;	
						case 8:
							if(P8_CNT > 0)
							{
								RearLine[0] = Packer8Sol_Run[P8_CNT-1];	
								grade = 7; 
								P7_CNT--; G7_CNT--;
							}														
							break;						
						}				
				}	
				else
				{
					RearLine[0]=NORUN;
					grade = 0;
				}
			}
			
			else if(resultData <= Grader_8_UL && resultData >=Grader_8_LL)
			{
				switch(G8_Prt)
				{
					case 0:
						RearLine_Prt[0] = 0;	
					  prt = 0;
						break;
					case 1:
						if(G8_prt_qt_limit == 0)
						{
							RearLine_Prt[0] = Prt1_run;	
							prt = 1;
						}
						else if(G8_prt_qt_limit == 1)
						{
							RearLine_Prt[0] = 0;	
							prt = 0;
						}
						else if(G8_prt_qt_limit > 1)
						{
							RearLine_Prt[0] = Prt1_run;		
							prt = 1;
							G8_prt_qt_limit--;
						}					
						break;
					case 2:
						if(G8_prt_qt_limit == 0) //PRT No Limit
						{
							RearLine_Prt[0] = Prt2_run;	
							prt = 2;
						}
						else if(G8_prt_qt_limit == 1) //PRT STOP
						{
							RearLine_Prt[0] = 0;	
							prt = 0;
						}
						else if(G8_prt_qt_limit > 1) //PRT   < Limit
						{
							RearLine_Prt[0] = Prt2_run;		
							prt = 2;
							G8_prt_qt_limit--;
						}
						break;
				}
				
				if(G8_CNT > 0)
				{
					switch(G8PACKER_Num[G8_CNT-1])
					{
						case 1:																													
							if(P1_CNT > 0)
							{
								RearLine[0] = Packer1Sol_Run[P1_CNT-1];	
								grade = 8;
								P8_CNT--; G8_CNT--;
							}													
							break;
						case 2:																													
							if(P2_CNT > 0)
							{
								RearLine[0] = Packer2Sol_Run[P2_CNT-1];	
								grade = 8;
								P8_CNT--; G8_CNT--;
							}														
							break;
						case 3:																														
							if(P3_CNT > 0)
							{
								RearLine[0] = Packer3Sol_Run[P3_CNT-1];	
								grade = 8;
								P8_CNT--; G8_CNT--;
							}							
							break;								
						case 4:																														
							if(P4_CNT > 0)
							{
								RearLine[0] = Packer4Sol_Run[P4_CNT-1];	
								grade = 8;
								P8_CNT--; G8_CNT--;
							}														
							break;	
						case 5:																												
							if(P5_CNT > 0)
							{
								RearLine[0] = Packer5Sol_Run[P5_CNT-1];	
								grade = 8;
								P8_CNT--; G8_CNT--;
							}							
							break;							
						case 6:																												
							if(P6_CNT > 0)
							{
								RearLine[0] = Packer6Sol_Run[P6_CNT-1];	
								grade = 8;
								P8_CNT--; G8_CNT--;
							}													
							break;
						case 7:																												
							if(P7_CNT > 0)
							{
								RearLine[0] = Packer7Sol_Run[P7_CNT-1];	
								grade = 8;
								P8_CNT--; G8_CNT--;
							}													
							break;	
						case 8:
							grade = 8;																			
							if(P8_CNT > 0)
							{
								RearLine[0] = Packer8Sol_Run[P8_CNT-1];	
								grade = 8;
								P8_CNT--; G8_CNT--;
							}												
						 break;									
						}																								
					}			
				else
				{
					RearLine[0]=NORUN;
					grade = 0;
				}				
			}
		
      else if((Off_size_UL >= resultData || resultData <= Off_size_LL) && resultData >= 10)
			{
				grade = 9;
				RearLine[0]=NORUN;
				switch(Offset_Prt)
				{
					case 0:
						RearLine_Prt[0] = 0;	
					  prt = 0;
					  break;
					case 1:
						if(OFFSET_prt_qt_limit == 0)
						{
							RearLine_Prt[0] = Prt1_run;	
							prt = 1;
						}
						else if(OFFSET_prt_qt_limit == 1)
						{
							RearLine_Prt[0] = 0;	
							prt = 0;
						}
						else if(OFFSET_prt_qt_limit > 1)
						{
							RearLine_Prt[0] = Prt1_run;		
							prt = 1;
							G4_prt_qt_limit--;
						}					
						break;
					case 2:
						if(OFFSET_prt_qt_limit == 0) //PRT No Limit
						{
							RearLine_Prt[0] = Prt2_run;	
							prt = 2;
						}
						else if(OFFSET_prt_qt_limit == 1) //PRT STOP
						{
							RearLine_Prt[0] = 0;	
							prt = 0;
						}
						else if(OFFSET_prt_qt_limit > 1) //PRT   < Limit
						{
							RearLine_Prt[0] = Prt2_run;		
							prt = 2;
							OFFSET_prt_qt_limit--;
						}
						break;
				}		
			}
			else
				{
					RearLine[0]=NORUN;
					grade = 0;
				}
			}
			
		if( i_cnt == Measurement_EndTime+1)
		{
			if(Rear_Count >= REAR_COUNT)
			{
				Rear_Count = 0;
			}
			 		 
			if(P1_CNT < 1  )
			{
				P1_CNT = Packer1_sol_cnt;
			}
			if(P2_CNT < 1  )
			{
				P2_CNT = Packer2_sol_cnt;
			}
			if(P3_CNT < 1 )
			{
				P3_CNT = Packer3_sol_cnt;
			}
			if(P4_CNT < 1 )
			{
				P4_CNT = Packer4_sol_cnt;
			}
			if(P5_CNT < 1 )
			{
				P5_CNT = Packer5_sol_cnt;
			}
			if(P6_CNT < 1 )
			{
				P6_CNT = Packer6_sol_cnt;
			}
			if(P7_CNT < 1 )
			{
				P7_CNT = Packer7_sol_cnt;
			}
			if(P8_CNT < 1 )
			{
				P8_CNT = Packer8_sol_cnt;
			}

			if(G1_CNT <  1 )
			{	
				G1_CNT = G1PACKER_Cnt;
			}
			if(G2_CNT < 1 )
			{
				G2_CNT = G2PACKER_Cnt;
			}
			if(G3_CNT < 1 )
			{
				G3_CNT = G3PACKER_Cnt;
			}
			if(G4_CNT < 1 )
			{
				G4_CNT = G4PACKER_Cnt;
			}
			if(G5_CNT < 1 )
			{
				G5_CNT = G5PACKER_Cnt;
			}
			if(G6_CNT < 1 )
			{
				G6_CNT = G6PACKER_Cnt;
			}
			if(G7_CNT < 1 )
			{
				G7_CNT = G7PACKER_Cnt;
			}
			if(G8_CNT < 1 )
			{
				G8_CNT = G8PACKER_Cnt;
			}					
		}
		
			if(i_cnt == Measurement_EndTime+2 ) //Rear moving
			{
				memmove(RearLine+1,RearLine,sizeof(uint8_t)*REAR_COUNT-1);
				memmove(RearLine_Prt+1,RearLine_Prt,sizeof(uint8_t)*REAR_COUNT-1); 
			}
			
			if(i_cnt == Measurement_EndTime+1)
			{
				timerCnt++;
				data[data_count++] = 0x10;	
				data[data_count++] = 0x02;	
				data[data_count++] = (uint8_t)(*((uint32_t*)&resultData) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&resultData) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&resultData) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)&resultData));	
				data[data_count++] = (uint8_t)(*((uint32_t*)&grade) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&grade) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&grade) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)&grade));		
				data[data_count++] = (uint8_t)(*((uint32_t*)&Grade_speed) >> 24);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&Grade_speed) >> 16);		
				data[data_count++] = (uint8_t)(*((uint32_t*)&Grade_speed) >> 8);
				data[data_count++] = (uint8_t)(*((uint32_t*)&Grade_speed));	
				data[data_count++] = 0x10;	
				data[data_count++] = 0x03;	
				HAL_UART_Transmit(&huart1,data,data_count,10); 	 
			}			
			DWT_Delay_ms(1);
		}
					
	}
	
	else if (RUN_ACTIVE_NUM == GRADER_TIMING_MEASUREMENT)
	{							      
				int i =0;		   
				while(i < 250)
				{	
					resultData = (filtereadValue-Loadcell_Zero)*Loadcell_Weight;
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
