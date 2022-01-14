#include "__cf_IBC_open_basis_test_SMC_False.h"
#ifndef RTW_HEADER_IBC_open_basis_test_SMC_False_acc_h_
#define RTW_HEADER_IBC_open_basis_test_SMC_False_acc_h_
#include <stddef.h>
#include <float.h>
#include <string.h>
#ifndef IBC_open_basis_test_SMC_False_acc_COMMON_INCLUDES_
#define IBC_open_basis_test_SMC_False_acc_COMMON_INCLUDES_
#include <stdlib.h>
#define S_FUNCTION_NAME simulink_only_sfcn 
#define S_FUNCTION_LEVEL 2
#define RTW_GENERATED_S_FUNCTION
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif
#include "IBC_open_basis_test_SMC_False_acc_types.h"
#include "multiword_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"
#include "rt_look.h"
#include "rt_look1d.h"
#include "rt_defines.h"
typedef struct { real_T B_1_0_0 ; }
B_SampleandHold_IBC_open_basis_test_SMC_False_T ; typedef struct { int32_T
SampleandHold_sysIdxToRun ; int8_T SampleandHold_SubsysRanBC ; char_T
pad_SampleandHold_SubsysRanBC [ 3 ] ; }
DW_SampleandHold_IBC_open_basis_test_SMC_False_T ; typedef struct { real_T
SampleandHold_Trig_ZC ; } ZCV_SampleandHold_IBC_open_basis_test_SMC_False_T ;
typedef struct { ZCSigState SampleandHold_Trig_ZCE ; }
ZCE_SampleandHold_IBC_open_basis_test_SMC_False_T ; typedef struct { real_T
B_4_1_0 ; real_T B_4_6_0 ; real_T B_4_7_0 ; real_T B_4_8_0 ; real_T B_4_9_0 [
21 ] ; real_T B_4_9_1 [ 9 ] ; real_T B_4_9_2 ; real_T B_4_11_0 ; real_T
B_4_21_0 ; real_T B_4_22_0 ; real_T B_4_24_0 ; real_T B_4_26_0 ; real_T
B_4_27_0 ; real_T B_4_28_0 ; real_T B_4_29_0 ; real_T B_4_31_0 ; real_T
B_4_33_0 ; real_T B_4_36_0 ; real_T B_4_37_0 ; real_T B_4_39_0 ; real_T
B_4_41_0 ; real_T B_4_69_0 ; real_T B_4_70_0 ; real_T B_4_80_0 ; real_T
B_4_93_0 ; real_T B_4_95_0 ; real_T B_4_96_0 ; real_T B_4_97_0 ; real_T
B_4_98_0 ; real_T B_4_119_0 ; real_T B_4_120_0 ; real_T B_4_148_0 ; real_T
B_4_149_0 ; real_T B_4_150_0 ; real_T B_4_152_0 ; real_T B_4_153_0 ; real_T
B_4_154_0 ; real_T B_4_0_0 [ 9 ] ; real_T B_4_1_0_m ; real_T B_4_2_0 ; real_T
B_4_3_0 ; real_T B_4_4_0 ; real_T B_4_6_0_c ; boolean_T B_4_23_0 ; boolean_T
B_4_32_0 ; boolean_T B_4_34_0 ; char_T pad_B_4_34_0 [ 5 ] ;
B_SampleandHold_IBC_open_basis_test_SMC_False_T SampleandHold2 ;
B_SampleandHold_IBC_open_basis_test_SMC_False_T SampleandHold1 ;
B_SampleandHold_IBC_open_basis_test_SMC_False_T SampleandHold ; }
B_IBC_open_basis_test_SMC_False_T ; typedef struct { real_T UnitDelay_DSTATE
; real_T StateSpace_DSTATE [ 4 ] ; real_T nextTime ; real_T nextTime_p ;
real_T nextTime_h ; real_T TimeStampA ; real_T LastUAtTimeA ; real_T
TimeStampB ; real_T LastUAtTimeB ; real_T TimeStampA_m ; real_T
LastUAtTimeA_e ; real_T TimeStampB_d ; real_T LastUAtTimeB_e ; int64_T
numCompleteCycles ; int64_T numCompleteCycles_e ; int64_T numCompleteCycles_i
; real_T StateSpace_RWORK ; struct { real_T modelTStart ; }
TransportDelay_RWORK ; struct { real_T modelTStart ; } TransportDelay3_RWORK
; struct { real_T modelTStart ; } TransportDelay1_RWORK ; struct { real_T
modelTStart ; } TransportDelay2_RWORK ; void * StateSpace_PWORK [ 65 ] ;
struct { void * TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK ; void *
Scope3_PWORK [ 2 ] ; void * Scope1_PWORK [ 3 ] ; void * Scope2_PWORK [ 4 ] ;
struct { void * TUbufferPtrs [ 2 ] ; } TransportDelay3_PWORK ; struct { void
* TUbufferPtrs [ 2 ] ; } TransportDelay1_PWORK ; struct { void * TUbufferPtrs
[ 2 ] ; } TransportDelay2_PWORK ; void * Scope4_PWORK [ 4 ] ; void *
Scope7_PWORK [ 4 ] ; void * Scope4_PWORK_e [ 3 ] ; int32_T justEnabled ;
int32_T currentValue ; int32_T justEnabled_c ; int32_T currentValue_i ;
int32_T justEnabled_e ; int32_T currentValue_k ; int32_T
TmpAtomicSubsysAtSwitchInport3_sysIdxToRun ; int_T StateSpace_IWORK [ 12 ] ;
struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay_IWORK ; struct { int_T Tail ; int_T Head ;
int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay3_IWORK ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay1_IWORK ; struct {
int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay2_IWORK ; int_T Step2_MODE ; int_T Step_MODE
; boolean_T Relay_Mode ; char_T pad_Relay_Mode [ 3 ] ;
DW_SampleandHold_IBC_open_basis_test_SMC_False_T SampleandHold2 ;
DW_SampleandHold_IBC_open_basis_test_SMC_False_T SampleandHold1 ;
DW_SampleandHold_IBC_open_basis_test_SMC_False_T SampleandHold ; }
DW_IBC_open_basis_test_SMC_False_T ; typedef struct { real_T
Step2_StepTime_ZC ; real_T Step_StepTime_ZC ; real_T
HitCrossing_HitNoOutput_ZC ; real_T HitCrossing_HitNoOutput_ZC_d ;
ZCV_SampleandHold_IBC_open_basis_test_SMC_False_T SampleandHold2 ;
ZCV_SampleandHold_IBC_open_basis_test_SMC_False_T SampleandHold1 ;
ZCV_SampleandHold_IBC_open_basis_test_SMC_False_T SampleandHold ; }
ZCV_IBC_open_basis_test_SMC_False_T ; typedef struct { ZCSigState
Step2_StepTime_ZCE ; ZCSigState Step_StepTime_ZCE ; ZCSigState
HitCrossing_HitNoOutput_ZCE ; ZCSigState HitCrossing_HitNoOutput_ZCE_i ;
ZCE_SampleandHold_IBC_open_basis_test_SMC_False_T SampleandHold2 ;
ZCE_SampleandHold_IBC_open_basis_test_SMC_False_T SampleandHold1 ;
ZCE_SampleandHold_IBC_open_basis_test_SMC_False_T SampleandHold ; }
PrevZCX_IBC_open_basis_test_SMC_False_T ; struct
P_SampleandHold_IBC_open_basis_test_SMC_False_T_ { real_T P_0 ; } ; struct
P_IBC_open_basis_test_SMC_False_T_ { real_T P_0 ; real_T P_1 [ 6 ] ; real_T
P_2 [ 6 ] ; real_T P_3 ; real_T P_4 ; real_T P_5 ; real_T P_6 ; real_T P_7 ;
real_T P_8 [ 2 ] ; real_T P_9 ; real_T P_10 [ 2 ] ; real_T P_11 [ 16 ] ;
real_T P_12 [ 2 ] ; real_T P_13 [ 44 ] ; real_T P_14 [ 2 ] ; real_T P_15 [ 84
] ; real_T P_16 [ 2 ] ; real_T P_17 [ 231 ] ; real_T P_18 [ 2 ] ; real_T P_19
[ 4 ] ; real_T P_20 [ 2 ] ; real_T P_21 ; real_T P_22 [ 2 ] ; real_T P_23 [ 3
] ; real_T P_24 [ 2 ] ; real_T P_26 [ 2 ] ; real_T P_27 ; real_T P_28 [ 2 ] ;
real_T P_29 ; real_T P_30 [ 2 ] ; real_T P_32 [ 2 ] ; real_T P_33 ; real_T
P_34 [ 2 ] ; real_T P_35 ; real_T P_36 [ 2 ] ; real_T P_38 [ 2 ] ; real_T
P_39 ; real_T P_40 [ 2 ] ; real_T P_41 ; real_T P_42 [ 2 ] ; real_T P_43 ;
real_T P_44 [ 2 ] ; real_T P_45 ; real_T P_46 [ 2 ] ; real_T P_47 [ 9 ] ;
real_T P_48 [ 2 ] ; real_T P_49 [ 9 ] ; real_T P_50 [ 2 ] ; real_T P_51 [ 9 ]
; real_T P_52 [ 2 ] ; real_T P_53 [ 9 ] ; real_T P_54 [ 2 ] ; real_T P_55 ;
real_T P_56 ; real_T P_57 ; real_T P_58 ; real_T P_59 ; real_T P_60 ; real_T
P_61 ; real_T P_62 ; real_T P_63 ; real_T P_64 ; real_T P_65 ; real_T P_66 ;
real_T P_67 ; real_T P_68 ; real_T P_69 ; real_T P_70 ; real_T P_71 ; real_T
P_72 ; real_T P_73 ; real_T P_74 ; real_T P_75 ; real_T P_76 ; real_T P_77 ;
real_T P_78 ; real_T P_79 ; real_T P_80 ; real_T P_81 ; real_T P_82 ; real_T
P_83 ; real_T P_84 ; real_T P_85 ; real_T P_86 ; real_T P_87 ; real_T P_88 ;
real_T P_89 ; real_T P_90 ; real_T P_91 ; real_T P_92 ; real_T P_93 ; real_T
P_94 ; real_T P_95 ; real_T P_96 ; real_T P_97 ; real_T P_98 ; real_T P_99 ;
real_T P_100 [ 6 ] ; real_T P_101 [ 6 ] ; real_T P_102 ; real_T P_103 [ 9 ] ;
real_T P_104 ; real_T P_105 ; real_T P_106 ; real_T P_107 ; real_T P_108 ;
real_T P_109 ; P_SampleandHold_IBC_open_basis_test_SMC_False_T SampleandHold2
; P_SampleandHold_IBC_open_basis_test_SMC_False_T SampleandHold1 ;
P_SampleandHold_IBC_open_basis_test_SMC_False_T SampleandHold ; } ; extern
P_IBC_open_basis_test_SMC_False_T IBC_open_basis_test_SMC_False_rtDefaultP ;
#endif
