#ifdef __cplusplus
extern "C" {
#endif

#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_tim.h"

/*! HAL almost always forget
 * to create ISR for its timebase timer */
#define FORGET_TO_GENERATE_TIM_HANDLER  true

/* Sometimes you generate one configuration in
 * CubeMX -> Pinout & Configuration -> SYS -> Timebase Source == TIM1
 * and receive some Indian java shit in return.
 * This is remedy :
 * -    exclude from build file :
 *      Application->User->***_hal_timebase_tim.c from build,
 * -    un-fold this code. */
#define WRONG_TIMER_CONFIGURATION       true

#if(WRONG_TIMER_CONFIGURATION)
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority);
void HAL_SuspendTick(void);
void HAL_ResumeTick(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
#endif

#if(FORGET_TO_GENERATE_TIM_HANDLER)
void TIM1_UP_IRQHandler(void);
#endif

#ifdef __cplusplus
}
#endif
