/* @file    stm32h743i_eval_lcd.c
  * @author
  * @brief   This file provides a set of functions needed to manage the GC9503NP
  *              LCD Driver.*/


#include "stm32h743i_eval_lcd.h"
#include "stm32h743i_eval_io.h"
#include "stm32h743i_eval_bus.h"

#include "../../../Drivers/stm32h7xx_HAL_Driver/inc/stm32h7xx_hal_spi.h"
#include "../GC9503NP/gc9503np.h"

extern SPI_HandleTypeDef hbus_spi2;


#define USE_GC9503_NP_DRIVER 1U
#define GC9503_INSTANCES_NBR 1U

void *GC9503NP_CompObj[GC9503_INSTANCES_NBR];

static LCD_Drv_t  *gc9503np_Drv = NULL;

#if(USE_GC9503_NP_DRIVER == 1U)
static int32_t GC9503NP_Probe(uint32_t INstance);
#endif


int8_t GC9503NP_DriverInit();

int32_t BSP_GC9503NP_Init(uint32_t Instance)
{

	GC9503NP_DriverInit();

#if 0
	int32_t ret = BSP_ERROR_NONE;

	  if(Instance > 0)
	  {
	    ret = BSP_ERROR_WRONG_PARAM;
	  }
	  else
	  {
	#if (USE_GC9503_NP_DRIVER == 1U)
	    ret = GC9503NP_Probe(Instance);
	#endif
	  }

	  if(ret != BSP_ERROR_NONE)
	  {
	      ret = BSP_ERROR_UNKNOWN_COMPONENT;
	   }
	  else
	  {
		  GC9503NP_DriverInit();
	  }
#endif
	  return 0;

}

#if 1
int32_t GC9503_ResetSeq1()
{
	/*  LCD Initialization  */

	EwBsp_GC9503_NSS_PinInit();
	EwBsp_GC9503_ResetPin_Init();

	EwBsp_GC9503_NSS(0);
	EwBsp_GC9503_Reset(1);
	HAL_Delay(100);
	EwBsp_GC9503_Reset(0);
	HAL_Delay(800);
	EwBsp_GC9503_Reset(1);
    HAL_Delay(800);
    EwBsp_GC9503_NSS(1);
    return 0;
}

/**
  * @brief  Initializing the LCD Driver GC9503
  * @param  Instance LCD Driver instance.
  * @retval BSP status
  */

void GC9503NP_WriteComm(uint8_t command)
//void SPI_WriteComm(uint8_t command)
{
	uint16_t frame;
	uint8_t data;
	frame = ((0<<8)|(command & 0xFF));
	EwBsp_GC9503_NSS(0);
	//BSP_SPI2_WriteReg(frame,&data,1);
    //HAL_SPI_Transmit(&hbus_spi2, (uint8_t*)&frame, 1, 100);
	BSP_SPI2_WriteReg(frame,&data,1);
    EwBsp_GC9503_NSS(1);
}

//void SPI_WriteData(uint8_t data)
void GC9503NP_WriteData(uint8_t data)
{
	    uint16_t frame;
		uint8_t data1;
		frame = ((1<<8)|(data & 0xFF));
		EwBsp_GC9503_NSS(0);
		//HAL_SPI_Transmit(&hbus_spi2, (uint8_t*)&frame, 1, 100);
		BSP_SPI2_WriteReg(frame,&data1,1);
	    EwBsp_GC9503_NSS(1);
}

void GC9503NP_ReadDeviceID(uint8_t command)
{
    uint16_t frame;
    uint8_t data1;
	frame = ((0<<8)|(command & 0xFF));
	EwBsp_GC9503_NSS(0);

	//HAL_SPI_Transmit(&hbus_spi2, (uint8_t*)&frame, 1, 100);
	//BSP_SPI2_WriteReg(frame,&data1,1);
	BSP_SPI2_ReadReg(frame,&data1,1);
	//HAL_SPI_Receive(&hbus_spi2, &data1, 1, 100);

	EwBsp_GC9503_NSS(1);

}

#endif



/**
  * @brief  Register Bus IOs if component ID is OK
  * @param  Instance LCD Driver instance. Could be only 0.
  * @retval BSP status
  */

static int32_t GC9503NP_Probe(uint32_t Instance)
{
  int32_t ret = BSP_ERROR_NONE;
  GC950NP_IO_t IOCtx;
  static GC950NP_Object_t GC9503NPObj;
  uint32_t GC9503NP_id;

  /* Configure the touch screen driver */
  IOCtx.Address      =  GC9503NP_DEV_ID_2;      // Set the I2C Address of the TSC2007
  IOCtx.Init             =  BSP_SPI2_Init;
  IOCtx.DeInit         =  BSP_SPI2_DeInit;
  IOCtx.ReadReg     =  BSP_SPI2_ReadReg;
  IOCtx.WriteReg    =  BSP_SPI2_WriteReg;
  IOCtx.GetTick      =  BSP_GetTick;

  if(GC9503NP_RegisterBusIO(&GC9503NPObj, &IOCtx))
  {
	ret = BSP_ERROR_BUS_FAILURE;
  }

  else if (GC9503NP_ReadID(&GC9503NPObj,&GC9503NP_id) != GC9503NP_OK)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    GC9503NP_CompObj[Instance] = &GC9503NPObj;
    gc9503np_Drv = (LCD_Drv_t *) &GC9503np_Driver;

    	if(gc9503np_Drv->Init(GC9503NP_CompObj[Instance],0,0) != GC9503NP_OK)
    	{
    			ret = BSP_ERROR_COMPONENT_FAILURE;
    	}
  }

  return ret;

}

#if 1

/**
  * @brief  Driver Init Function for GC9503NP
  * @param  Void
  * @retval BSP status
  */


int8_t GC9503NP_DriverInit()
{
#if 1
	    BSP_SPI2_Init();
	    EwBsp_GC9503_NSS_PinInit();
		EwBsp_GC9503_ResetPin_Init();

		EwBsp_GC9503_NSS(0);
		EwBsp_GC9503_Reset(1);
		HAL_Delay(100);
		EwBsp_GC9503_Reset(0);
		HAL_Delay(800);
		EwBsp_GC9503_Reset(1);
	    HAL_Delay(800);
	    EwBsp_GC9503_NSS(1);

	    //GC9503NP_ReadDeviceID(0xDB);
//#if 0
		     //GC9503_LCD_Parameter_Init();
		     GC9503NP_WriteComm(0xF0);    //EXTC Command Set enable register
		     GC9503NP_WriteData(0x55);   //Default
		     GC9503NP_WriteData(0xAA);   //Default
		     GC9503NP_WriteData(0x52);   //Default
		     GC9503NP_WriteData(0x08);   //Default
		     GC9503NP_WriteData(0x00);   //Default

			  GC9503NP_WriteComm(0xF6);    //OTP_CTL
			  GC9503NP_WriteData(0x5A);   //Default
			  GC9503NP_WriteData(0x87);   //Default

			  GC9503NP_WriteComm(0xC1);
			  GC9503NP_WriteData(0x3F);

			  GC9503NP_WriteComm(0xCD);
			  GC9503NP_WriteData(0x25);

			  GC9503NP_WriteComm(0xC9);
			  GC9503NP_WriteData(0x10);    //Sleep In

			  GC9503NP_WriteComm(0xF8);
			  GC9503NP_WriteData(0x8A);

			  GC9503NP_WriteComm(0xAC);
			  GC9503NP_WriteData(0x45);

			  GC9503NP_WriteComm(0xA7);
			  GC9503NP_WriteData(0x47);

			  GC9503NP_WriteComm(0xA0);    // CHP_CTL5
			  GC9503NP_WriteData(0xCC);

			  GC9503NP_WriteComm(0x86);   // CHP_CTL1
			  GC9503NP_WriteData(0x99);    //VREG_CTL3
			  GC9503NP_WriteData(0xA3);    //Default
			  GC9503NP_WriteData(0xA3);    //Default
			  GC9503NP_WriteData(0x31);

			  GC9503NP_WriteComm(0xFA);
			  GC9503NP_WriteData(0x08);
			  GC9503NP_WriteData(0x08);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x04);     //Read Display ID

			  GC9503NP_WriteComm(0xA3);    //Default
			  GC9503NP_WriteData(0x6E);

			  GC9503NP_WriteComm(0xFD);
			  GC9503NP_WriteData(0x28);    //Display OFF
			  GC9503NP_WriteData(0x3C);
			  GC9503NP_WriteData(0x00);    //Default

			  GC9503NP_WriteComm(0x9A);   // VREG_CTL4
			  GC9503NP_WriteData(0x4a);

			  GC9503NP_WriteComm(0x9B);   // VREG_CTL5
			  GC9503NP_WriteData(0x22);    //All Pixel OFF

			  GC9503NP_WriteComm(0x82);    // VREG_CTL1
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x00);

			  GC9503NP_WriteComm(0x80);    //VRGEG_CTRL0
			  GC9503NP_WriteData(0x4a);

			  GC9503NP_WriteComm(0xB1);    //Display CTL
			  GC9503NP_WriteData(0x10);
			  GC9503NP_WriteData(0x00);

			  GC9503NP_WriteComm(0x7A);
			  GC9503NP_WriteData(0x0F);
			  GC9503NP_WriteData(0x13);    //Normal Display Mode ON

			  GC9503NP_WriteComm(0x7B);
			  GC9503NP_WriteData(0x0F);
			  GC9503NP_WriteData(0x13);    //Normal Display Mode ON

			  GC9503NP_WriteComm(0x6D);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x1e);
			  GC9503NP_WriteData(0x02);
			  GC9503NP_WriteData(0x08);
			  GC9503NP_WriteData(0x1a);
			  GC9503NP_WriteData(0x19);
			  GC9503NP_WriteData(0x0d);    //Read Display Image Mode
			  GC9503NP_WriteData(0x11);    //Sleep Out
			  GC9503NP_WriteData(0x12);    //Partial Mode ON
			  GC9503NP_WriteData(0x13);    //Normal Mode ON
			  GC9503NP_WriteData(0x14);
			  GC9503NP_WriteData(0x1E);
			  GC9503NP_WriteData(0x1E);
			  GC9503NP_WriteData(0x1E);
			  GC9503NP_WriteData(0x1E);
			  GC9503NP_WriteData(0x1E);
			  GC9503NP_WriteData(0x1E);
			  GC9503NP_WriteData(0x1E);
			  GC9503NP_WriteData(0x1E);
			  GC9503NP_WriteData(0x0c);     //Read Display Pixel Format
			  GC9503NP_WriteData(0x0b);     //Read Display MADCTL
			  GC9503NP_WriteData(0x0a);     //Read Display Power Mode
			  GC9503NP_WriteData(0x09);
			  GC9503NP_WriteData(0x0d);
			  GC9503NP_WriteData(0x19);
			  GC9503NP_WriteData(0x1a);
			  GC9503NP_WriteData(0x07);
			  GC9503NP_WriteData(0x01);
			  GC9503NP_WriteData(0x1E);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x03);

			  GC9503NP_WriteComm(0x64);
			  GC9503NP_WriteData(0x38);
			  GC9503NP_WriteData(0x04);      //Read Display ID
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0xc4);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x38);
			  GC9503NP_WriteData(0x02);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0xc6);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x2C);
			  GC9503NP_WriteData(0x7A);
			  GC9503NP_WriteData(0x2C);
			  GC9503NP_WriteData(0x7A);

			  GC9503NP_WriteComm(0x65);
			  GC9503NP_WriteData(0x38);
			  GC9503NP_WriteData(0x08);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0xc0);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x38);
			  GC9503NP_WriteData(0x06);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0xc2);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x2C);
			  GC9503NP_WriteData(0x7A);
			  GC9503NP_WriteData(0x2C);
			  GC9503NP_WriteData(0x7A);

			  GC9503NP_WriteComm(0x66);
			  GC9503NP_WriteData(0x83);
			  GC9503NP_WriteData(0xd0);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0xc4);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x83);
			  GC9503NP_WriteData(0xd0);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0xc4);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x2C);
			  GC9503NP_WriteData(0x7A);
			  GC9503NP_WriteData(0x2C);
			  GC9503NP_WriteData(0x7A);

			  GC9503NP_WriteComm(0x60);
			  GC9503NP_WriteData(0x38);
			  GC9503NP_WriteData(0x0c);     //Read Display Pixel Format
			  GC9503NP_WriteData(0x3c);
			  GC9503NP_WriteData(0x3c);
			  GC9503NP_WriteData(0x38);
			  GC9503NP_WriteData(0x0b);     //Read Display MADCTL
			  GC9503NP_WriteData(0x3c);
			  GC9503NP_WriteData(0x3c);

			  GC9503NP_WriteComm(0x61);
			  GC9503NP_WriteData(0xb3);
			  GC9503NP_WriteData(0xc4);
			  GC9503NP_WriteData(0x3c);
			  GC9503NP_WriteData(0x3c);
			  GC9503NP_WriteData(0xb3);
			  GC9503NP_WriteData(0xc4);
			  GC9503NP_WriteData(0x3c);
			  GC9503NP_WriteData(0x3c);

			  GC9503NP_WriteComm(0x62);
			  GC9503NP_WriteData(0xb3);
			  GC9503NP_WriteData(0xc4);
			  GC9503NP_WriteData(0x3c);
			  GC9503NP_WriteData(0x3c);
			  GC9503NP_WriteData(0xb3);
			  GC9503NP_WriteData(0xc4);
			  GC9503NP_WriteData(0x3c);
			  GC9503NP_WriteData(0x3c);

			  GC9503NP_WriteComm(0x63);
			  GC9503NP_WriteData(0x38);
			  GC9503NP_WriteData(0x0a);     //Read Display Power Mode
			  GC9503NP_WriteData(0x3c);
			  GC9503NP_WriteData(0x3c);
			  GC9503NP_WriteData(0x38);
			  GC9503NP_WriteData(0x09);
			  GC9503NP_WriteData(0x3c);
			  GC9503NP_WriteData(0x3c);

			  GC9503NP_WriteComm(0x68);
			  GC9503NP_WriteData(0x77);
			  GC9503NP_WriteData(0x08);
			  GC9503NP_WriteData(0x0a);     //Read Display Power Mode
			  GC9503NP_WriteData(0x08);
			  GC9503NP_WriteData(0x09);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x18);
			  GC9503NP_WriteData(0x0a);     //Read Display Power Mode
			  GC9503NP_WriteData(0x08);
			  GC9503NP_WriteData(0x09);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x00);

			  GC9503NP_WriteComm(0x69);
			  GC9503NP_WriteData(0x14);
			  GC9503NP_WriteData(0x22);    //All Pixel OFF
			  GC9503NP_WriteData(0x14);
			  GC9503NP_WriteData(0x22);    //All Pixel OFF
			  GC9503NP_WriteData(0x44);
			  GC9503NP_WriteData(0x22);    //All Pixel OFF
			  GC9503NP_WriteData(0x08);

			  GC9503NP_WriteComm(0x6B);
			  GC9503NP_WriteData(0x07);

			  GC9503NP_WriteComm(0xD1);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x10);      //Sleep IN
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x22);      //All Pixel OFF
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x2c);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x2e);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x56);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x58);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x7c);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x9a);     //VREG_CTL4
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0xce);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0xfa);
			  GC9503NP_WriteData(0x01);
			  GC9503NP_WriteData(0x4c);
			  GC9503NP_WriteData(0x01);
			  GC9503NP_WriteData(0x94);
			  GC9503NP_WriteData(0x01);
			  GC9503NP_WriteData(0x96);
			  GC9503NP_WriteData(0x01);
			  GC9503NP_WriteData(0xda);
			  GC9503NP_WriteData(0x02);
			  GC9503NP_WriteData(0x32);
			  GC9503NP_WriteData(0x02);
			  GC9503NP_WriteData(0x76);
			  GC9503NP_WriteData(0x02);
			  GC9503NP_WriteData(0xcc);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x18);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x55);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x6b);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x9b);     //VREG_CTL5
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0xac);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0xb8);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0xe0);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0xFF);

			  GC9503NP_WriteComm(0xD2);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x10);     //Sleep IN
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x22);     //All Pixel OFF
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x2c);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x2e);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x56);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x58);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x7c);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x9a);     //VREG_CTL4
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0xce);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0xfa);
			  GC9503NP_WriteData(0x01);
			  GC9503NP_WriteData(0x4c);
			  GC9503NP_WriteData(0x01);
			  GC9503NP_WriteData(0x94);
			  GC9503NP_WriteData(0x01);
			  GC9503NP_WriteData(0x96);
			  GC9503NP_WriteData(0x01);
			  GC9503NP_WriteData(0xda);
			  GC9503NP_WriteData(0x02);
			  GC9503NP_WriteData(0x32);
			  GC9503NP_WriteData(0x02);
			  GC9503NP_WriteData(0x76);
			  GC9503NP_WriteData(0x02);
			  GC9503NP_WriteData(0xcc);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x18);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x55);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x6b);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x9b);     //VREG_CTL5
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0xac);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0xb8);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0xe0);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0xFF);

			  GC9503NP_WriteComm(0xD3);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x10);      //Sleep IN
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x22);      //All Pixel OFF
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x2c);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x2e);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x56);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x58);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x7c);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x9a);      //VREG_CTL4
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0xce);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0xfa);
			  GC9503NP_WriteData(0x01);
			  GC9503NP_WriteData(0x4c);
			  GC9503NP_WriteData(0x01);
			  GC9503NP_WriteData(0x94);
			  GC9503NP_WriteData(0x01);
			  GC9503NP_WriteData(0x96);
			  GC9503NP_WriteData(0x01);
			  GC9503NP_WriteData(0xda);
			  GC9503NP_WriteData(0x02);
			  GC9503NP_WriteData(0x32);
			  GC9503NP_WriteData(0x02);
			  GC9503NP_WriteData(0x76);
			  GC9503NP_WriteData(0x02);
			  GC9503NP_WriteData(0xcc);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x18);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x55);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x6b);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x9b);     //VREG_CTL5
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0xac);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0xb8);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0xe0);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0xFF);

			  GC9503NP_WriteComm(0xD4);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x10);      //Sleep IN
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x22);      //All Pixel OFF
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x2c);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x2e);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x56);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x58);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x7c);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x9a);     //VREG_CTL4
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0xce);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0xfa);
			  GC9503NP_WriteData(0x01);
			  GC9503NP_WriteData(0x4c);
			  GC9503NP_WriteData(0x01);
			  GC9503NP_WriteData(0x94);
			  GC9503NP_WriteData(0x01);
			  GC9503NP_WriteData(0x96);
			  GC9503NP_WriteData(0x01);
			  GC9503NP_WriteData(0xda);
			  GC9503NP_WriteData(0x02);
			  GC9503NP_WriteData(0x32);
			  GC9503NP_WriteData(0x02);
			  GC9503NP_WriteData(0x76);
			  GC9503NP_WriteData(0x02);
			  GC9503NP_WriteData(0xcc);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x18);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x55);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x6b);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x9b);      //VREG_CTL5
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0xac);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0xb8);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0xe0);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0xFF);

			  GC9503NP_WriteComm(0xD5);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x10);     //Sleep IN
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x22);     //All Pixel OFF
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x2c);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x2e);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x56);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x58);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x7c);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x9a);    //VREG_CTL4
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0xce);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0xfa);
			  GC9503NP_WriteData(0x01);
			  GC9503NP_WriteData(0x4c);
			  GC9503NP_WriteData(0x01);
			  GC9503NP_WriteData(0x94);
			  GC9503NP_WriteData(0x01);
			  GC9503NP_WriteData(0x96);
			  GC9503NP_WriteData(0x01);
			  GC9503NP_WriteData(0xda);
			  GC9503NP_WriteData(0x02);
			  GC9503NP_WriteData(0x32);
			  GC9503NP_WriteData(0x02);
			  GC9503NP_WriteData(0x76);
			  GC9503NP_WriteData(0x02);
			  GC9503NP_WriteData(0xcc);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x18);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x55);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x6b);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x9b);      //VREG_CTL5
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0xac);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0xb8);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0xe0);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0xFF);

			  GC9503NP_WriteComm(0xD6);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x10);     //Sleep IN
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x22);     //All Pixel OFF
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x2c);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x2e);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x56);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x58);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x7c);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x9a);      //VREG_CTL4
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0xce);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0xfa);
			  GC9503NP_WriteData(0x01);
			  GC9503NP_WriteData(0x4c);
			  GC9503NP_WriteData(0x01);
			  GC9503NP_WriteData(0x94);
			  GC9503NP_WriteData(0x01);
			  GC9503NP_WriteData(0x96);
			  GC9503NP_WriteData(0x01);
			  GC9503NP_WriteData(0xda);
			  GC9503NP_WriteData(0x02);
			  GC9503NP_WriteData(0x32);
			  GC9503NP_WriteData(0x02);
			  GC9503NP_WriteData(0x76);
			  GC9503NP_WriteData(0x02);
			  GC9503NP_WriteData(0xcc);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x18);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x55);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x6b);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0x9b);      //VREG_CTL5
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0xac);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0xb8);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0xe0);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0xFF);

			  GC9503NP_WriteComm(0x3A);        // Selecting the Pixel Format
			  GC9503NP_WriteData(0x77);         // 16 Bit format

			  //GC9503NP_WriteComm(0xB0);       // 0000 0000
			  //GC9503NP_WriteData(0x00);

			  GC9503NP_WriteComm(0x2A);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x3C);
			  GC9503NP_WriteData(0x01);
			  GC9503NP_WriteData(0xA3);

			  GC9503NP_WriteComm(0x2B);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x00);
			  GC9503NP_WriteData(0x03);
			  GC9503NP_WriteData(0xBF);

			  GC9503NP_WriteComm(0x11);
			  GC9503NP_WriteComm(0x29);
#endif
			  return 0;
}
#endif





