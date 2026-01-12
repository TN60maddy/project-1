#include "gc9503np.h"
#include "stddef.h"
#include "../../STM32H743I-EVAL/stm32h743i_eval_io.h"
#include "../../STM32H743I-EVAL/stm32h743i_eval_bus.h"

GC950NP_Drv_t GC9503np_Driver =
{
  /* Control functions */
  GC9503NP_Init,
  GC9503NP_DeInit,
  GC9503NP_ReadID,
  GC9503NP_DisplayOn,
  GC9503NP_DisplayOff,
  GC9503NP_SetBrightness,
  GC9503NP_GetBrightness,
  GC9503NP_SetOrientation,
  GC9503NP_GetOrientation,

  /* Drawing functions*/
  GC9503NP_SetCursor,
  GC9503NP_DrawBitmap,
  GC9503NP_FillRGBRect,
  GC9503NP_DrawHLine,
  GC9503NP_DrawVLine,
  GC9503NP_FillRect,
  GC9503NP_GetPixel,
  GC9503NP_SetPixel,
  GC9503NP_GetXSize,
  GC9503NP_GetYSize
};

static int32_t ReadRegWrap(void *handle, uint8_t Reg, uint8_t* pData, uint16_t Length);
static int32_t WriteRegWrap(void *handle, uint8_t Reg, uint8_t* pData, uint16_t Length);

int32_t GC9503_InitGpio();
int32_t GC9503_ResetSeq1(void);
int32_t GC9503_InitGpio();
void GC9503NP_WriteComm(uint8_t command);
void GC9503NP_WriteData(uint8_t data);


int32_t GC9503NP_RegisterBusIO (GC950NP_Object_t *pObj, GC950NP_IO_t *pIO)
{
  int32_t ret;

  if (pObj == NULL)
  {
    ret = GC9503NP_ERROR;
  }
  else
  {
    pObj->IO.Init         	=  pIO->Init;
    pObj->IO.DeInit         =  pIO->DeInit;
    pObj->IO.Address      =  pIO->Address;
    pObj->IO.WriteReg    =  pIO->WriteReg;
    pObj->IO.ReadReg     =  pIO->ReadReg;
    //pObj->IO.GetTick   =  pIO->GetTick;
   // pObj->IO.DevRed   =  pIO->DevRed;

    pObj->Ctx.ReadReg  = ReadRegWrap;
    pObj->Ctx.WriteReg = WriteRegWrap;
    pObj->Ctx.handle   = pObj;

    if(pObj->IO.Init != NULL)
    {
      GC9503_InitGpio();
      ret = pObj->IO.Init();
    }
    else
    {
    	  ret = GC9503NP_ERROR;
    }
  }

  return ret;
}

/**
  * @brief  Reset Sequence of GC9503NP Driver
  * @ Parameter : Void
  * @retval Component status
  */




#if 0
int32_t GC9503_ResetSeq1(void)
{
	/*  LCD Initialization  */
    EwBsp_GC9503_NSS(0);
	EwBsp_GC9503_Reset(1);
	HAL_Delay(100);
	EwBsp_GC9503_Reset(0);
	HAL_Delay(800);
	EwBsp_GC9503_Reset(1);
    HAL_Delay(800);
    EwBsp_GC9503_NSS(1);
}

int32_t GC9503_InitGpio()
{
	/* Init NSS and RESET PIN as GPIO Pin Output */
	EwBsp_GC9503_NSS_PinInit();
    EwBsp_GC9503_ResetPin_Init();
}



/**
  * @brief  Send a 9 bit command to GC9503
  * @param  Command to be sent
  * @retval BSP status
  */

void GC9503NP_WriteComm(uint8_t command)
//void SPI_WriteComm(uint8_t command)
{
	uint16_t frame;
	uint8_t data;
	frame = ((0<<8)|(command & 0xFF));
	//EwBsp_GC9503_NSS(0);
	 // pObj->IO.ReadReg(data9bit,&data,100);
     BSP_SPI2_WriteReg(frame,&data,1);
    //HAL_SPI_Transmit(&hbus_spi2, (uint8_t*)&frame, 1, 100);
	//BSP_SPI2_WriteReg(frame,&data,1);
    //EwBsp_GC9503_NSS(1);
}

/**
  * @brief  Send a 9 bit Data to GC9503
  * @param  Command to be sent
  * @retval BSP status
  */

void GC9503NP_WriteData(uint8_t data)
{
	    uint16_t frame;
		uint8_t data1;
		frame = ((1<<8)|(data & 0xFF));
	//	EwBsp_GC9503_NSS(0);
		//HAL_SPI_Transmit(&hbus_spi2, (uint8_t*)&frame, 1, 100);
		BSP_SPI2_WriteReg(frame,&data1,1);
	  //  EwBsp_GC9503_NSS(1);
}
#endif

/**
  * @brief  Initialize the GC9503NP communication bus
  *         from MCU to GC9503NP : i.e SPI channel initialization (if required).
  * @param  pObj Component object pointer
  * @retval Component status
  */

int32_t GC9503NP_Init(GC950NP_Object_t *pObj,uint32_t dat1, uint32_t data2)
{

	int32_t ret = GC9503NP_OK;


   if(pObj->IsInitialized == 0U)
  {
    /* Initialize IO BUS layer */
    if(pObj->IO.Init() != GC9503NP_OK)
    {
      ret = GC9503NP_ERROR;
    }
    else
    {

        pObj->IsInitialized = 1;
    }
  }

  return ret;
}

/**
  * @brief  De-Initialize the GC9503NP communication bus
  *         from MCU to GC9503NP : ie SPI channel initialization (if required).
  * @param  pObj Component object pointer
  * @retval Component status
  */
int32_t GC9503NP_DeInit(GC950NP_Object_t *pObj)
{
  int32_t ret = GC9503NP_OK;

  if(pObj->IsInitialized == 1U)
  {
    if(pObj->IO.DeInit() != GC9503NP_OK)
    {
      ret = GC9503NP_ERROR;
    }
    else
    {
      pObj->IsInitialized = 0;
    }
  }

  return ret;
}


/**
  * @brief  Read the GC9503NP device ID, pre initialize I2C in case of need to be
  *         able to read the GC9503NP device ID, and verify this is a GC9503NP.
  * @param  pObj Component object pointer
  * @param  Id Pointer to component ID value
  * @retval Component status
  */
int32_t GC9503NP_ReadID(GC950NP_Object_t *pObj, uint32_t *Id)
{
  int32_t ret = GC9503NP_ERROR;
  /*  Reset the GC9503 Driver before reading the Device ID */
  GC9503_ResetSeq1();
  uint16_t data9bit;
  data9bit = ((0 << 8) | (0xDB & 0xFF));
  uint8_t data;

  if(pObj->IO.ReadReg(data9bit,&data,100) == 0)
  {
    *Id = data;
  }

  if(*Id == GC9503NP_DEV_ID_2)
	  ret = GC9503NP_OK;
  else
	  ret = GC9503NP_ERROR;

  return ret;
}

#if 0
/**
  * @brief  Write a Command to the GC9503NP Driver through I2C Bus
  * @param  handle Component object handle
  * @param  pData Command to written to the LCD Driver
  * @param  Length buffer size of the Command
  * @retval Component status.
  */

int32_t GC9503NP_SendCommand(GC950NP_Object_t *pObj, uint16_t Command, uint16_t length)
{
	      /* Make the GPIO PIN as HIGH */
	      HAL_GPIO_WritePin(GPIOB, SPI_CS_Pin, GPIO_PIN_RESET);

		 // Prepare the 9-bit frame with MSB as 0 (for command)
	      uint16_t frame = (0 << 8) | (Command & 0xFF);  // Command: 0x0F0 -> 0 11110000
	      pObj->IO.ReadReg(frame,&data,100);

	      // Transmit the 9-bit data using HAL_SPI_Transmit
	      HAL_SPI_Transmit(&hspi2, (uint8_t*)&frame, length,100);

	      HAL_GPIO_WritePin(GPIOB, SPI_CS_Pin, GPIO_PIN_SET);
}

/**
  * @brief  Write a Command to the GC9503NP Driver through I2C Bus
  * @param  handle Component object handle
  * @param  pData Command to written to the LCD Driver
  * @param  Length buffer size of the Command
  * @retval Component status.
  */

int32_t GC9503NP_SendData(GC950NP_Object_t *pObj, uint16_t data, uint16_t length)
{
	      /* Make the GPIO PIN as HIGH */
	      HAL_GPIO_WritePin(GPIOB, SPI_CS_Pin, GPIO_PIN_RESET);

		 // Prepare the 9-bit frame with MSB as 0 (for command)
	      uint16_t frame = (0 << 8) | (data & 0xFF);  // Command: 0x0F0 -> 0 11110000
	      pObj->IO.ReadReg(frame,&data,100);

	      // Transmit the 9-bit data using HAL_SPI_Transmit
	      HAL_SPI_Transmit(&hspi2, (uint8_t*)&frame, length,100);

	      HAL_GPIO_WritePin(GPIOB, SPI_CS_Pin, GPIO_PIN_SET);
}

#endif
/**
  * @brief  Wrap IO bus read function to component register red function
  * @param  handle Component object handle
  * @param  Reg The target register address to read
  * @param  pData The target register value to be read
  * @param  Length buffer size to be read
  * @retval Component status.
  */
static int32_t ReadRegWrap(void *handle, uint8_t Reg, uint8_t* pData, uint16_t Length)
{
	//GC950NP_Object_t *pObj = (GC950NP_Object_t *)handle;
  //return pObj->IO.ReadReg(pObj->IO.Address, Reg, pData, Length);
	return 0;
}

/**
  * @brief  Wrap IO bus write function to component register write function
  * @param  handle Component object handle
  * @param  Reg The target register address to write
  * @param  pData The target register value to be written
  * @param  Length buffer size to be written
  * @retval Component status.
  */
static int32_t WriteRegWrap(void *handle, uint8_t Reg, uint8_t* pData, uint16_t Length)
{
	//GC950NP_Object_t *pObj = (GC950NP_Object_t *)handle;

 // return pObj->IO.WriteReg(pObj->IO.Address, Reg, pData, Length);
	return 0;
}

/**
  * @brief  Driver Init Function for GC9503NP
  * @param  Void
  * @retval BSP status
  */

#if 0
int8_t GC9503NP_DriverInit()
{
#if 1
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
}
#endif










int32_t  GC9503NP_DisplayOn (GC950NP_Object_t* obj)
{
     return 0;

}


int32_t GC9503NP_DisplayOff (GC950NP_Object_t* obj)
{
     return 0;
}


int32_t GC9503NP_SetBrightness    (GC950NP_Object_t* Obj, uint32_t Param1)
{
     return 0;
}

int32_t GC9503NP_GetBrightness(GC950NP_Object_t* Obj, uint32_t* Param1)
{
	return 0;
}

int32_t  GC9503NP_SetOrientation (GC950NP_Object_t* Obj, uint32_t Param1)
{
	return 0;
}


int32_t GC9503NP_GetOrientation (GC950NP_Object_t* Obj, uint32_t* Param1)
{
	return 0;
}

  /* Drawing functions*/

int32_t GC9503NP_SetCursor (GC950NP_Object_t* Obj, uint32_t Param1, uint32_t Param2)
{
	return 0;
}


int32_t GC9503NP_DrawBitmap (GC950NP_Object_t* Obj, uint32_t Param1, uint32_t Param2, uint8_t *Param3 )
{

	return 0;
}


int32_t GC9503NP_FillRGBRect (GC950NP_Object_t* Obj, uint32_t Param1,  uint32_t Param2, uint8_t* Param3, uint32_t Param4, uint32_t Param5)
{
	return 0;
}

int32_t GC9503NP_DrawHLine (GC950NP_Object_t* Obj, uint32_t Param1, uint32_t Param2, uint32_t Param3, uint32_t Param4)
{
	return 0;

}


int32_t GC9503NP_DrawVLine (GC950NP_Object_t* Obj, uint32_t Param1, uint32_t Param2, uint32_t Param3, uint32_t Param4)
{

	return 0;
}


int32_t GC9503NP_FillRect (GC950NP_Object_t* Obj, uint32_t Param1, uint32_t Param2, uint32_t Param3, uint32_t Param4, uint32_t Param5)
{

	return 0;
}


int32_t GC9503NP_GetPixel (GC950NP_Object_t* Obj, uint32_t Param1, uint32_t Param2, uint32_t* Param3)
{
	return 0;
}


int32_t GC9503NP_SetPixel (GC950NP_Object_t* Obj, uint32_t Param1, uint32_t Param2, uint32_t Param3)
{
	return 0;

}


int32_t GC9503NP_GetXSize (GC950NP_Object_t* Obj, uint32_t *Param1)
{
	return 0;
}


int32_t GC9503NP_GetYSize (GC950NP_Object_t* Obj, uint32_t *Param1)
{
	return 0;
}



