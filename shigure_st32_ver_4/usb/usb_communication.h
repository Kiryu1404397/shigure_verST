#ifndef _usb_communication_header_
#define _usb_communication_header_


#define HSE_VALUE ((uint32_t)8000000) /* STM32 discovery uses a 8Mhz external crystal */

#include "usbd_cdc_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usbd_cdc_vcp.h"
#include "usb_dcd_int.h"

__ALIGN_BEGIN USB_OTG_CORE_HANDLE  USB_OTG_dev __ALIGN_END;



void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void OTG_FS_IRQHandler(void);
void OTG_FS_WKUP_IRQHandler(void);

void Usb_error_do(void);

void Usb_put_char(char c);

void Init_usb(void);


#endif
