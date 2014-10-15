#include "usb_communication.h"

#include "stm32f4xx_conf.h"
#include "stm32f4xx.h"

#include "usbd_cdc_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usbd_cdc_vcp.h"
#include "usb_dcd_int.h"



void Usb_error_do(void){
}
void Usb_put_char(char c){
	VCP_put_char((uint8_t)c);
}
void Init_usb(void){
	USBD_Init(&USB_OTG_dev,USB_OTG_FS_CORE_ID,&USR_desc,&USBD_CDC_cb,&USR_cb);
}


void NMI_Handler(void)       {}
void HardFault_Handler(void) { Usb_error_do(); }
void MemManage_Handler(void) { Usb_error_do(); }
void BusFault_Handler(void)  { Usb_error_do(); }
void UsageFault_Handler(void){ Usb_error_do(); }
void SVC_Handler(void)       {}
void DebugMon_Handler(void)  {}
void PendSV_Handler(void)    {}

void OTG_FS_IRQHandler(void)
{
  USBD_OTG_ISR_Handler (&USB_OTG_dev);
}

void OTG_FS_WKUP_IRQHandler(void)
{
  if(USB_OTG_dev.cfg.low_power)
  {
    *(uint32_t *)(0xE000ED10) &= 0xFFFFFFF9 ;
    SystemInit();
    USB_OTG_UngateClock(&USB_OTG_dev);
  }
//  EXTI_ClearITPendingBit(EXTI_Line18);
}
