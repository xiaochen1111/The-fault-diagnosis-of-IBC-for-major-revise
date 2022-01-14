#include "__cf_MPC_load_varying.h"
#ifndef RTW_HEADER_MPC_load_varying_acc_h_
#define RTW_HEADER_MPC_load_varying_acc_h_
#include <stddef.h>
#include <float.h>
#include <string.h>
#ifndef MPC_load_varying_acc_COMMON_INCLUDES_
#define MPC_load_varying_acc_COMMON_INCLUDES_
#include <stdlib.h>
#define S_FUNCTION_NAME simulink_only_sfcn 
#define S_FUNCTION_LEVEL 2
#define RTW_GENERATED_S_FUNCTION
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif
#include "MPC_load_varying_acc_types.h"
#include "multiword_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"
#include "rt_look.h"
#include "rt_look1d.h"
#include "rt_defines.h"
typedef struct { real_T B_1_0_0 ; } B_SampleIL1_MPC_load_varying_T ; typedef
struct { int32_T SampleIL1_sysIdxToRun ; int8_T SampleIL1_SubsysRanBC ;
char_T pad_SampleIL1_SubsysRanBC [ 3 ] ; } DW_SampleIL1_MPC_load_varying_T ;
typedef struct { real_T SampleIL1_Trig_ZC ; }
ZCV_SampleIL1_MPC_load_varying_T ; typedef struct { ZCSigState
SampleIL1_Trig_ZCE ; } ZCE_SampleIL1_MPC_load_varying_T ; typedef struct {
real_T B_6_1_0 ; real_T B_6_6_0 ; real_T B_6_7_0 ; real_T B_6_8_0 ; real_T
B_6_9_0 [ 21 ] ; real_T B_6_9_1 [ 9 ] ; real_T B_6_9_2 ; real_T B_6_10_0 ;
real_T B_6_11_0 ; real_T B_6_12_0 ; real_T B_6_14_0 ; real_T B_6_15_0 ;
real_T B_6_16_0 ; real_T B_6_18_0 ; real_T B_6_20_0 ; real_T B_6_22_0 ;
real_T B_6_25_0 ; real_T B_6_27_0 ; real_T B_6_28_0 ; real_T B_6_32_0 ;
real_T B_6_33_0 ; real_T B_6_34_0 ; real_T B_6_36_0 ; real_T B_6_38_0 ;
real_T B_6_41_0 ; real_T B_6_43_0 ; real_T B_6_45_0 ; real_T B_6_47_0 ;
real_T B_6_52_0 ; real_T B_6_55_0 ; real_T B_6_70_0 ; real_T B_6_73_0 ;
real_T B_6_75_0 ; real_T B_6_78_0 ; real_T B_6_79_0 ; real_T B_6_81_0 ;
real_T B_6_84_0 ; real_T B_6_117_0 ; real_T B_6_118_0 ; real_T B_6_128_0 ;
real_T B_6_141_0 ; real_T B_6_143_0 ; real_T B_6_144_0 ; real_T B_6_145_0 ;
real_T B_6_146_0 ; real_T B_6_161_0 ; real_T B_6_162_0 ; real_T B_6_188_0 ;
real_T B_6_0_0 [ 9 ] ; real_T B_6_1_0_m ; real_T B_6_4_0 ; real_T B_6_5_0 ;
real_T B_6_6_0_c ; real_T B_6_7_0_k ; real_T B_6_8_0_c ; real_T B_6_9_0_b ;
real_T B_6_10_0_p ; real_T B_6_11_0_c ; real_T B_6_12_0_f ; real_T B_6_14_0_g
; real_T B_6_19_0 ; real_T B_6_21_0 ; real_T B_6_23_0 ; real_T B_6_25_0_g ;
real_T B_6_26_0 ; real_T B_6_27_0_m ; real_T B_6_28_0_n ; boolean_T B_6_42_0
; boolean_T B_6_44_0 ; boolean_T B_6_46_0 ; boolean_T B_6_48_0 ; boolean_T
B_6_53_0 ; boolean_T B_6_56_0 ; boolean_T B_6_63_0 ; boolean_T B_6_64_0 ;
boolean_T B_6_65_0 ; char_T pad_B_6_65_0 [ 7 ] ;
B_SampleIL1_MPC_load_varying_T SampleandHold1 ;
B_SampleIL1_MPC_load_varying_T SampleIL4 ; B_SampleIL1_MPC_load_varying_T
SampleIL3 ; B_SampleIL1_MPC_load_varying_T SampleIL2 ;
B_SampleIL1_MPC_load_varying_T SampleIL1 ; } B_MPC_load_varying_T ; typedef
struct { real_T UnitDelay_DSTATE ; real_T StateSpace_DSTATE [ 4 ] ; real_T
TimeStampA ; real_T LastUAtTimeA ; real_T TimeStampB ; real_T LastUAtTimeB ;
real_T TimeStampA_b ; real_T LastUAtTimeA_f ; real_T TimeStampB_f ; real_T
LastUAtTimeB_e ; real_T StateSpace_RWORK ; struct { real_T modelTStart ; }
TransportDelay1_RWORK ; struct { real_T modelTStart ; } TransportDelay2_RWORK
; struct { real_T modelTStart ; } TransportDelay_RWORK ; void *
StateSpace_PWORK [ 65 ] ; void * Scope_PWORK ; void * Scope1_PWORK [ 4 ] ;
struct { void * TUbufferPtrs [ 2 ] ; } TransportDelay1_PWORK ; struct { void
* TUbufferPtrs [ 2 ] ; } TransportDelay2_PWORK ; void * Scope2_PWORK [ 5 ] ;
void * Scope3_PWORK ; void * Scope4_PWORK [ 4 ] ; void * Scope5_PWORK [ 2 ] ;
void * Scope6_PWORK [ 2 ] ; void * Scope2_PWORK_a ; void * Scope3_PWORK_g [ 3
] ; void * Scope4_PWORK_l [ 3 ] ; void * Scope5_PWORK_i ; void *
Scope6_PWORK_e [ 3 ] ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay_PWORK ; void * Scope1_PWORK_g [ 2 ] ; void * Scope7_PWORK [ 4
] ; void * Scope9_PWORK [ 3 ] ; int32_T
TmpAtomicSubsysAtSwitchInport3_sysIdxToRun ; int_T StateSpace_IWORK [ 12 ] ;
struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay1_IWORK ; struct { int_T Tail ; int_T Head ;
int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay2_IWORK ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay_IWORK ; int_T
Step2_MODE ; int_T Saturation_MODE ; int_T Saturation_MODE_o ; int_T
Step_MODE ; boolean_T RelationalOperator_Mode ; boolean_T
RelationalOperator1_Mode ; boolean_T RelationalOperator2_Mode ; boolean_T
Compare_Mode ; boolean_T Compare_Mode_d ; boolean_T Compare_Mode_b ;
boolean_T Compare_Mode_n ; boolean_T Compare_Mode_k ; boolean_T
Compare_Mode_f ; char_T pad_Compare_Mode_f [ 7 ] ;
DW_SampleIL1_MPC_load_varying_T SampleandHold1 ;
DW_SampleIL1_MPC_load_varying_T SampleIL4 ; DW_SampleIL1_MPC_load_varying_T
SampleIL3 ; DW_SampleIL1_MPC_load_varying_T SampleIL2 ;
DW_SampleIL1_MPC_load_varying_T SampleIL1 ; } DW_MPC_load_varying_T ; typedef
struct { real_T Integrator_CSTATE ; } X_MPC_load_varying_T ; typedef struct {
real_T Integrator_CSTATE ; } XDot_MPC_load_varying_T ; typedef struct {
boolean_T Integrator_CSTATE ; } XDis_MPC_load_varying_T ; typedef struct {
real_T Integrator_CSTATE ; } CStateAbsTol_MPC_load_varying_T ; typedef struct
{ real_T Step2_StepTime_ZC ; real_T Saturation_UprLim_ZC ; real_T
Saturation_LwrLim_ZC ; real_T Saturation_UprLim_ZC_b ; real_T
Saturation_LwrLim_ZC_h ; real_T RelationalOperator_RelopInput_ZC ; real_T
RelationalOperator1_RelopInput_ZC ; real_T RelationalOperator2_RelopInput_ZC
; real_T Compare_RelopInput_ZC ; real_T Compare_RelopInput_ZC_l ; real_T
Compare_RelopInput_ZC_g ; real_T Compare_RelopInput_ZC_n ; real_T
Compare_RelopInput_ZC_a ; real_T Compare_RelopInput_ZC_b ; real_T
Step_StepTime_ZC ; real_T HitCrossing_HitNoOutput_ZC ; real_T
HitCrossing_HitNoOutput_ZC_j ; ZCV_SampleIL1_MPC_load_varying_T
SampleandHold1 ; ZCV_SampleIL1_MPC_load_varying_T SampleIL4 ;
ZCV_SampleIL1_MPC_load_varying_T SampleIL3 ; ZCV_SampleIL1_MPC_load_varying_T
SampleIL2 ; ZCV_SampleIL1_MPC_load_varying_T SampleIL1 ; }
ZCV_MPC_load_varying_T ; typedef struct { ZCSigState Step2_StepTime_ZCE ;
ZCSigState Saturation_UprLim_ZCE ; ZCSigState Saturation_LwrLim_ZCE ;
ZCSigState Saturation_UprLim_ZCE_p ; ZCSigState Saturation_LwrLim_ZCE_h ;
ZCSigState RelationalOperator_RelopInput_ZCE ; ZCSigState
RelationalOperator1_RelopInput_ZCE ; ZCSigState
RelationalOperator2_RelopInput_ZCE ; ZCSigState Compare_RelopInput_ZCE ;
ZCSigState Compare_RelopInput_ZCE_k ; ZCSigState Compare_RelopInput_ZCE_p ;
ZCSigState Compare_RelopInput_ZCE_i ; ZCSigState Compare_RelopInput_ZCE_l ;
ZCSigState Compare_RelopInput_ZCE_g ; ZCSigState Step_StepTime_ZCE ;
ZCSigState HitCrossing_HitNoOutput_ZCE ; ZCSigState
HitCrossing_HitNoOutput_ZCE_d ; ZCE_SampleIL1_MPC_load_varying_T
SampleandHold1 ; ZCE_SampleIL1_MPC_load_varying_T SampleIL4 ;
ZCE_SampleIL1_MPC_load_varying_T SampleIL3 ; ZCE_SampleIL1_MPC_load_varying_T
SampleIL2 ; ZCE_SampleIL1_MPC_load_varying_T SampleIL1 ; }
PrevZCX_MPC_load_varying_T ; typedef struct { const real_T B_6_0_0 ; const
real_T B_6_1_0 ; const real_T B_6_2_0 ; const real_T B_6_3_0 ; const real_T
B_6_4_0 ; const real_T B_6_5_0 ; } ConstB_MPC_load_varying_T ;
#define MPC_load_varying_rtC(S) ((ConstB_MPC_load_varying_T *) _ssGetConstBlockIO(S))
struct P_SampleIL1_MPC_load_varying_T_ { real_T P_0 ; } ; struct
P_MPC_load_varying_T_ { real_T P_0 ; real_T P_1 ; real_T P_2 ; real_T P_3 ;
real_T P_4 ; real_T P_5 ; real_T P_6 ; real_T P_7 [ 6 ] ; real_T P_8 [ 6 ] ;
real_T P_9 ; real_T P_10 ; real_T P_11 ; real_T P_12 ; real_T P_13 ; real_T
P_14 [ 2 ] ; real_T P_15 ; real_T P_16 [ 2 ] ; real_T P_17 [ 16 ] ; real_T
P_18 [ 2 ] ; real_T P_19 [ 44 ] ; real_T P_20 [ 2 ] ; real_T P_21 [ 84 ] ;
real_T P_22 [ 2 ] ; real_T P_23 [ 231 ] ; real_T P_24 [ 2 ] ; real_T P_25 [ 4
] ; real_T P_26 [ 2 ] ; real_T P_27 ; real_T P_28 [ 2 ] ; real_T P_29 [ 3 ] ;
real_T P_30 [ 2 ] ; real_T P_32 [ 2 ] ; real_T P_33 ; real_T P_34 [ 2 ] ;
real_T P_35 ; real_T P_36 [ 2 ] ; real_T P_38 [ 2 ] ; real_T P_39 ; real_T
P_40 [ 2 ] ; real_T P_41 ; real_T P_42 [ 2 ] ; real_T P_44 [ 2 ] ; real_T
P_45 ; real_T P_46 [ 2 ] ; real_T P_47 ; real_T P_48 [ 2 ] ; real_T P_49 ;
real_T P_50 [ 2 ] ; real_T P_51 ; real_T P_52 [ 2 ] ; real_T P_53 [ 9 ] ;
real_T P_54 [ 2 ] ; real_T P_55 [ 9 ] ; real_T P_56 [ 2 ] ; real_T P_57 [ 9 ]
; real_T P_58 [ 2 ] ; real_T P_59 [ 9 ] ; real_T P_60 [ 2 ] ; real_T P_61 ;
real_T P_62 ; real_T P_63 ; real_T P_64 ; real_T P_65 ; real_T P_66 ; real_T
P_67 ; real_T P_68 ; real_T P_69 ; real_T P_70 ; real_T P_71 ; real_T P_72 ;
real_T P_73 ; real_T P_74 ; real_T P_75 [ 3 ] ; real_T P_76 [ 3 ] ; real_T
P_77 ; real_T P_78 ; real_T P_79 ; real_T P_80 ; real_T P_81 [ 3 ] ; real_T
P_82 [ 3 ] ; real_T P_83 [ 3 ] ; real_T P_84 [ 3 ] ; real_T P_85 ; real_T
P_86 ; real_T P_87 [ 3 ] ; real_T P_88 [ 3 ] ; real_T P_89 ; real_T P_90 ;
real_T P_91 ; real_T P_92 ; real_T P_93 ; real_T P_94 ; real_T P_95 ; real_T
P_96 ; real_T P_97 ; real_T P_98 [ 6 ] ; real_T P_99 [ 6 ] ; real_T P_100 ;
real_T P_101 ; real_T P_102 [ 9 ] ; real_T P_103 ; real_T P_104 ; real_T
P_105 ; real_T P_106 ; real_T P_107 ; real_T P_108 ; real_T P_109 ; real_T
P_110 ; real_T P_111 ; real_T P_112 ; real_T P_113 ; real_T P_114 ; real_T
P_115 ; real_T P_116 ; real_T P_117 ; real_T P_118 ; real_T P_119 ; real_T
P_120 ; real_T P_121 ; real_T P_122 ; P_SampleIL1_MPC_load_varying_T
SampleandHold1 ; P_SampleIL1_MPC_load_varying_T SampleIL4 ;
P_SampleIL1_MPC_load_varying_T SampleIL3 ; P_SampleIL1_MPC_load_varying_T
SampleIL2 ; P_SampleIL1_MPC_load_varying_T SampleIL1 ; } ; extern
P_MPC_load_varying_T MPC_load_varying_rtDefaultP ; extern const
ConstB_MPC_load_varying_T MPC_load_varying_rtInvariant ;
#endif
