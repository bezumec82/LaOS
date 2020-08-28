#include "core.hpp"
#include "debug.hpp"

#ifdef __cplusplus
extern "C" {
#endif


/*!
 * For future used - currently tied to asm SVC_Handler
 * but unused.
 * @param svc_num - number of SVC call
 * number 0 is already taken by privilege change routine
 */
__weak void SVC_Handler_C(uint32_t svc_num)
{
//	PRINTF("SVC exception number : %lu", svc_num);
	switch(svc_num)
	{
	    case 0:
	    {
	        __asm__ volatile (
	                "mrs r1, control  \n"
	                "bic r1, #1       \n"
	                "msr control, r1  \n"
	                :
	                :
	                :"r1");
	        break;
	    }
	    default:
	        break;
	}
}

#ifdef __cplusplus
}
#endif
