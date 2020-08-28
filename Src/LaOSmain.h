#pragma once

#ifdef __cplusplus
extern "C" {
#endif
#include "stm32_hal_crutch.h"

#define UNPRIVILEGED_DATA   __attribute__(( section (".unprivileged_data") ))
#define UNPRIVILEGED_BSS    __attribute__(( section (".unprivileged_bss") ))

/*!
 * Incompatible with other embedded OS in one application.
 * In freeRTOS, for example, this handler is defined as 'vPortSVCHandler'. */
void SVC_Handler(void); //reside in asm
void SVC_Handler_C(uint32_t svc_num); //can be redefined
void MemManage_Handler(void);
void PendSV_Handler(void);

/* Startup routines */
void zeroOutSection(uint32_t * , uint32_t * );
void copySection(uint32_t * ,
        uint32_t * , uint32_t * );

/* Heap facility */
#include <stdio.h>
caddr_t _sbrk(int incr);
void * upMalloc(size_t size);
void upFree (void * ptr);


/* Tests */
int test();
void preemptTest();

/* Your cpp functions should be exported to C code from here */
int _main( void );

#ifdef __cplusplus
}
#endif
