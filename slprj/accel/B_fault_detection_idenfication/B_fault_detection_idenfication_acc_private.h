#include "__cf_B_fault_detection_idenfication.h"
#ifndef RTW_HEADER_B_fault_detection_idenfication_acc_private_h_
#define RTW_HEADER_B_fault_detection_idenfication_acc_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "B_fault_detection_idenfication_acc.h"
#if !defined(ss_VALIDATE_MEMORY)
#define ss_VALIDATE_MEMORY(S, ptr)   if(!(ptr)) {\
  ssSetErrorStatus(S, RT_MEMORY_ALLOCATION_ERROR);\
  }
#endif
#if !defined(rt_FREE)
#if !defined(_WIN32)
#define rt_FREE(ptr)   if((ptr) != (NULL)) {\
  free((ptr));\
  (ptr) = (NULL);\
  }
#else
#define rt_FREE(ptr)   if((ptr) != (NULL)) {\
  free((void *)(ptr));\
  (ptr) = (NULL);\
  }
#endif
#endif
#ifndef __RTW_UTFREE__
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T B_fault_detection_idenfication_acc_rt_TDelayUpdateTailOrGrowBuf (
int_T * bufSzPtr , int_T * tailPtr , int_T * headPtr , int_T * lastPtr ,
real_T tMinusDelay , real_T * * tBufPtr , real_T * * uBufPtr , real_T * *
xBufPtr , boolean_T isfixedbuf , boolean_T istransportdelay , int_T *
maxNewBufSzPtr ) ; real_T
B_fault_detection_idenfication_acc_rt_TDelayInterpolate ( real_T tMinusDelay
, real_T tStart , real_T * tBuf , real_T * uBuf , int_T bufSz , int_T *
lastIdx , int_T oldestIdx , int_T newIdx , real_T initOutput , boolean_T
discrete , boolean_T minorStepAndTAtLastMajorOutput ) ; extern real_T
look1_binlxpw ( real_T u0 , const real_T bp0 [ ] , const real_T table [ ] ,
uint32_T maxIndex ) ; void B_fault_detection_idenfication_SampleIL1_Init (
SimStruct * S , B_SampleIL1_B_fault_detection_idenfication_T * localB ,
P_SampleIL1_B_fault_detection_idenfication_T * localP ) ; void
B_fault_detection_idenfication_SampleIL1 ( SimStruct * S , boolean_T
rtu_Trigger , real_T rtu_In , B_SampleIL1_B_fault_detection_idenfication_T *
localB , DW_SampleIL1_B_fault_detection_idenfication_T * localDW ,
ZCE_SampleIL1_B_fault_detection_idenfication_T * localZCE ) ;
#endif
