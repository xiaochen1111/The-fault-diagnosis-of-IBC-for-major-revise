#include "__cf_OCF_Comment_2_5_SMC.h"
#ifndef RTW_HEADER_OCF_Comment_2_5_SMC_acc_private_h_
#define RTW_HEADER_OCF_Comment_2_5_SMC_acc_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "OCF_Comment_2_5_SMC_acc.h"
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
#ifndef UCHAR_MAX
#include <limits.h>
#endif
#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error Code was generated for compiler with different sized uchar/char. \Consider adjusting Test hardware word size settings on the \Hardware Implementation pane to match your compiler word sizes as \defined in limits.h of the compiler. Alternatively, you can \select the Test hardware is the same as production hardware option and \select the Enable portable word sizes option on the Code Generation > \Verification pane for ERT based targets, which will disable the \preprocessor word size checks.
#endif
#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \Consider adjusting Test hardware word size settings on the \Hardware Implementation pane to match your compiler word sizes as \defined in limits.h of the compiler. Alternatively, you can \select the Test hardware is the same as production hardware option and \select the Enable portable word sizes option on the Code Generation > \Verification pane for ERT based targets, which will disable the \preprocessor word size checks.
#endif
#if ( UINT_MAX != (0xFFFFFFFFU) ) || ( INT_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized uint/int. \Consider adjusting Test hardware word size settings on the \Hardware Implementation pane to match your compiler word sizes as \defined in limits.h of the compiler. Alternatively, you can \select the Test hardware is the same as production hardware option and \select the Enable portable word sizes option on the Code Generation > \Verification pane for ERT based targets, which will disable the \preprocessor word size checks.
#endif
#if ( ULONG_MAX != (0xFFFFFFFFU) ) || ( LONG_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized ulong/long. \Consider adjusting Test hardware word size settings on the \Hardware Implementation pane to match your compiler word sizes as \defined in limits.h of the compiler. Alternatively, you can \select the Test hardware is the same as production hardware option and \select the Enable portable word sizes option on the Code Generation > \Verification pane for ERT based targets, which will disable the \preprocessor word size checks.
#endif
#ifndef __RTW_UTFREE__
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T OCF_Comment_2_5_SMC_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T *
bufSzPtr , int_T * tailPtr , int_T * headPtr , int_T * lastPtr , real_T
tMinusDelay , real_T * * tBufPtr , real_T * * uBufPtr , real_T * * xBufPtr ,
boolean_T isfixedbuf , boolean_T istransportdelay , int_T * maxNewBufSzPtr )
; real_T OCF_Comment_2_5_SMC_acc_rt_TDelayInterpolate ( real_T tMinusDelay ,
real_T tStart , real_T * tBuf , real_T * uBuf , int_T bufSz , int_T * lastIdx
, int_T oldestIdx , int_T newIdx , real_T initOutput , boolean_T discrete ,
boolean_T minorStepAndTAtLastMajorOutput ) ; void
OCF_Comment_2_5_SMC_SampleandHold_Init ( SimStruct * S ,
B_SampleandHold_OCF_Comment_2_5_SMC_T * localB ,
P_SampleandHold_OCF_Comment_2_5_SMC_T * localP ) ; void
OCF_Comment_2_5_SMC_SampleandHold ( SimStruct * S , real_T rtu_Trigger ,
real_T rtu_In , B_SampleandHold_OCF_Comment_2_5_SMC_T * localB ,
DW_SampleandHold_OCF_Comment_2_5_SMC_T * localDW ,
ZCE_SampleandHold_OCF_Comment_2_5_SMC_T * localZCE ) ;
#endif
