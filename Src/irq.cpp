#include "core.hpp"

#ifdef __cplusplus
extern "C" {
#endif

/* Configurable Fault Status Register */
typedef struct {
    uint32_t IACCVIOL   : 1;    //!<Instruction access violation
    uint32_t DACCVIOL   : 1;    //!<Data access violation
    uint32_t reserved1  : 1;
    uint32_t MUNSTKERR  : 1;    //!<Unstacking error
    uint32_t MSTKERR    : 1;    //!<Stacking error
    uint32_t MLSPERR    : 1;    //!<Floating point lazy stacking error
    uint32_t reserved2  : 1;
    uint32_t MMARVALID  : 1;    //!<Indicates the MMFAR is valid
    uint32_t reserved3  : 24;
} __attribute__((packed)) SCB_CFSR;

void MemManage_Handler(void)
{
    uint32_t scbCfsr = SCB->CFSR; //snapshot of reg state
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
    uint32_t scbMmfar = SCB->MMFAR;
#pragma GCC diagnostic pop
    SCB_CFSR * scb_cfsr = (SCB_CFSR *)&(scbCfsr);
    PRINT_ERR(  "Instruction access violation (IACCVIOL)  : %lu \r\n"
                "Data access violation (DACCVIOL)         : %lu \r\n"
                "Unstacking error (MUNSTKERR)             : %lu \r\n"
                "Stacking error (MSTKERR)                 : %lu \r\n"
                "FP lazy stacking error (MLSPERR)         : %lu \r\n"
                "Address intercepted (MMARVALID)          : %lu \r\n",
                scb_cfsr->IACCVIOL,
                scb_cfsr->DACCVIOL,
                scb_cfsr->MUNSTKERR,
                scb_cfsr->MSTKERR,
                scb_cfsr->MLSPERR,
                scb_cfsr->MMARVALID
            );
    if(scb_cfsr->MMARVALID)
    {
        PRINT_ERR("MMFAR = 0x%lx\r\n", scbMmfar);
    }
    else
    {
        PRINT_ERR("No memory location info.\r\n");
    }
    ::LaOS::Core& instance = ::LaOS::Core::getInstance();
    PRINT_ERR("Fault context : %s\r\n", instance.current->name);
    __DMB();
    SCB->AIRCR = SCB_AIRCR_SYSRESETREQ_Msk |
            0x5FAUL << SCB_AIRCR_VECTKEY_Pos;
    while (1)
    {}
}

void SysTick_Handler(void)
{
    //wake up system
    __SEV(); //just in case - bug in M3
}


#ifdef __cplusplus
}
#endif
