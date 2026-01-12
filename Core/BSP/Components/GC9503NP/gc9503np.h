
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef GC9503NP_H
#define GC9503NP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <lcd.h>

#define GC9503NP_OK                      (0)
#define GC9503NP_ERROR                   (-1)

#define GC9503NP_DEV_ID_1  0x00
#define GC9503NP_DEV_ID_2  0x95
#define GC9503NP_DEV_ID_3  0x40

typedef int32_t (*GC950NP_Init_Func) (void);
typedef int32_t (*GC950NP_DeInit_Func) (void);
typedef int32_t (*GC950NP_GetTick_Func)(void);
typedef int32_t (*GC950NP_Delay_Func) (uint32_t);
typedef int32_t (*GC950NP_WriteReg_Func)(uint16_t,uint8_t*, uint16_t);
typedef int32_t (*GC950NP_ReadReg_Func) (uint16_t, uint8_t*, uint16_t);
typedef int32_t (*GC9503NP_DeviceReadyFunc) (uint16_t DevAddr, uint32_t Trials);

typedef int32_t (*GC950NP_Write_Func)(void *, uint8_t, uint8_t*, uint16_t);
typedef int32_t (*GC950NP_Read_Func) (void *, uint8_t, uint8_t*, uint16_t);


typedef struct{
	GC950NP_Write_Func WriteReg;
	GC950NP_Read_Func ReadReg;
    void *handle;
}GC950NP_ctx_t;


typedef struct{
	GC950NP_Init_Func   Init;
	GC950NP_DeInit_Func DeInit;
	uint16_t                   Address;
	GC950NP_WriteReg_Func      WriteReg;
	GC950NP_ReadReg_Func       ReadReg;
	GC950NP_GetTick_Func       GetTick;
	GC9503NP_DeviceReadyFunc DevRead;
}GC950NP_IO_t;

typedef struct {
	GC950NP_IO_t IO;
	GC950NP_ctx_t  Ctx;
	 uint8_t IsInitialized;
}GC950NP_Object_t;



typedef struct
{
  /* Control functions */
  int32_t (*Init             )(GC950NP_Object_t*, uint32_t, uint32_t);
  int32_t (*DeInit           )(GC950NP_Object_t*);
  int32_t (*ReadID           )(GC950NP_Object_t*, uint32_t*);
  int32_t (*DisplayOn        )(GC950NP_Object_t*);
  int32_t (*DisplayOff       )(GC950NP_Object_t*);
  int32_t (*SetBrightness    )(GC950NP_Object_t*, uint32_t);
  int32_t (*GetBrightness    )(GC950NP_Object_t*, uint32_t*);
  int32_t (*SetOrientation   )(GC950NP_Object_t*, uint32_t);
  int32_t (*GetOrientation   )(GC950NP_Object_t*, uint32_t*);

  /* Drawing functions*/
  int32_t ( *SetCursor       ) (GC950NP_Object_t*, uint32_t, uint32_t);
  int32_t ( *DrawBitmap      ) (GC950NP_Object_t*, uint32_t, uint32_t, uint8_t *);
  int32_t ( *FillRGBRect     ) (GC950NP_Object_t*, uint32_t, uint32_t, uint8_t*, uint32_t, uint32_t);
  int32_t ( *DrawHLine       ) (GC950NP_Object_t*, uint32_t, uint32_t, uint32_t, uint32_t);
  int32_t ( *DrawVLine       ) (GC950NP_Object_t*, uint32_t, uint32_t, uint32_t, uint32_t);
  int32_t ( *FillRect        ) (GC950NP_Object_t*, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
  int32_t ( *GetPixel        ) (GC950NP_Object_t*, uint32_t, uint32_t, uint32_t*);
  int32_t ( *SetPixel        ) (GC950NP_Object_t*, uint32_t, uint32_t, uint32_t);
  int32_t ( *GetXSize        ) (GC950NP_Object_t*, uint32_t *);
  int32_t ( *GetYSize        ) (GC950NP_Object_t*, uint32_t *);
}GC950NP_Drv_t;



int32_t GC9503NP_RegisterBusIO (GC950NP_Object_t *pObj, GC950NP_IO_t *pIO);
int32_t GC9503NP_Init(GC950NP_Object_t *pObj,uint32_t dat1, uint32_t data2);
int32_t GC9503NP_DeInit(GC950NP_Object_t *pObj);
int32_t GC9503NP_ReadID(GC950NP_Object_t *pObj,uint32_t* dat1);
int32_t GC9503NP_DisplayOn(GC950NP_Object_t *pObj);
int32_t GC9503NP_DisplayOff(GC950NP_Object_t *pObj);

int32_t GC9503NP_SetBrightness(GC950NP_Object_t *pObj,uint32_t);
int32_t GC9503NP_GetBrightness(GC950NP_Object_t *pObj,uint32_t*);
int32_t GC9503NP_SetOrientation(GC950NP_Object_t *pObj,uint32_t);
int32_t GC9503NP_GetOrientation (GC950NP_Object_t *pObj,uint32_t*);
int32_t GC9503NP_SetCursor (GC950NP_Object_t *pObj,uint32_t,uint32_t);
int32_t GC9503NP_DrawBitmap(GC950NP_Object_t *pObj,uint32_t,uint32_t,uint8_t*);
int32_t GC9503NP_FillRGBRect (GC950NP_Object_t *pObj,uint32_t,uint32_t,uint8_t*,uint32_t,uint32_t);
int32_t GC9503NP_DrawHLine(GC950NP_Object_t *pObj,uint32_t,uint32_t,uint32_t,uint32_t);
int32_t GC9503NP_DrawVLine (GC950NP_Object_t *pObj,uint32_t,uint32_t,uint32_t,uint32_t);
int32_t GC9503NP_FillRect(GC950NP_Object_t *pObj,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t);
int32_t GC9503NP_GetPixel(GC950NP_Object_t *pObj,uint32_t,uint32_t,uint32_t*);
int32_t GC9503NP_SetPixel (GC950NP_Object_t *pObj,uint32_t,uint32_t,uint32_t);
int32_t GC9503NP_GetXSize (GC950NP_Object_t *pObj,uint32_t*);
int32_t GC9503NP_GetYSize(GC950NP_Object_t *pObj,uint32_t*);

extern GC950NP_Drv_t GC9503np_Driver;

int8_t GC9503NP_DriverInit();


#ifdef __cplusplus
}
#endif
#endif /* TGC9503NP_H */
