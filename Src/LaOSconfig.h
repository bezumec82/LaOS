#pragma once

#define PROTECTED_STACK                     true

#if (PROTECTED_STACK)

//unsuitable with debug
# define USE_WATCHDOG                       false
# define WATCHDOG_TIMEOUT_MS                100

/* To put system in sleep - event driven system.
 * Incompatible with stepped debug. */

# define USE_SYSTICK                        true
#if(USE_SYSTICK)
# define SYSTICK_PERIOD_MS                  10
# define EVENT_DRIVEN_SYSTEM                false
# endif //USE_SYSTICK

# define STATIC_STACK_PROTECTION            true
/* Summary stack size */
# define THREADS_STACK_SIZE_WORDS           16384
/* If stack overflow happens, it flows not immediately to
 * the stack of other thread, but to the protection zone. */
# define PROTECTION_ZONE_WORDS              64
# if (PROTECTION_ZONE_WORDS < 32)
#  error "Protection zone too low"
# endif

//Check 16 bytes alignment for stack
# if( THREAD_STACK_SIZE_WORDS % 16 )
#  error "Stack alignment error"
# endif

# if( PROTECTION_ZONE_WORDS % 16 )
#  error "Protection zone alignment error"
# endif

#define UNPROTECTED_HEAP_SIZE               8192

#endif //PROTECTED_STACK

//Makes colored output
#define LINUX_TERMINAL
//Un-comment to disable core debug
//#define NDEBUG
