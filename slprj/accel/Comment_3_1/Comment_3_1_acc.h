#include "__cf_Comment_3_1.h"
#ifndef RTW_HEADER_Comment_3_1_acc_h_
#define RTW_HEADER_Comment_3_1_acc_h_
#include <stddef.h>
#include <float.h>
#include <string.h>
#ifndef Comment_3_1_acc_COMMON_INCLUDES_
#define Comment_3_1_acc_COMMON_INCLUDES_
#include <stdlib.h>
#define S_FUNCTION_NAME simulink_only_sfcn 
#define S_FUNCTION_LEVEL 2
#define RTW_GENERATED_S_FUNCTION
#include "sl_AsyncioQueue/AsyncioQueueCAPI.h"
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif
#include "Comment_3_1_acc_types.h"
#include "multiword_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"
#include "rt_look.h"
#include "rt_look1d.h"
#include "rt_defines.h"
typedef struct { real_T B_0_0_0 ; } B_SampleIL1_Comment_3_1_T ; typedef
struct { int32_T SampleIL1_sysIdxToRun ; int8_T SampleIL1_SubsysRanBC ;
char_T pad_SampleIL1_SubsysRanBC [ 3 ] ; } DW_SampleIL1_Comment_3_1_T ;
typedef struct { real_T SampleIL1_Trig_ZC ; } ZCV_SampleIL1_Comment_3_1_T ;
typedef struct { ZCSigState SampleIL1_Trig_ZCE ; }
ZCE_SampleIL1_Comment_3_1_T ; typedef struct { real_T B_5_1_0 ; real_T
B_5_3_0 ; real_T B_5_4_0 ; real_T B_5_6_0 ; real_T B_5_8_0 ; real_T B_5_9_0 ;
real_T B_5_10_0 ; real_T B_5_11_0 [ 19 ] ; real_T B_5_11_1 [ 9 ] ; real_T
B_5_11_2 ; real_T B_5_12_0 ; real_T B_5_14_0 ; real_T B_5_16_0 ; real_T
B_5_19_0 ; real_T B_5_21_0 ; real_T B_5_24_0 ; real_T B_5_25_0 ; real_T
B_5_29_0 ; real_T B_5_30_0 ; real_T B_5_31_0 ; real_T B_5_32_0 ; real_T
B_5_34_0 ; real_T B_5_36_0 ; real_T B_5_37_0 ; real_T B_5_38_0 ; real_T
B_5_41_0 ; real_T B_5_42_0 ; real_T B_5_45_0 ; real_T B_5_46_0 ; real_T
B_5_50_0 ; real_T B_5_67_0 ; real_T B_5_70_0 ; real_T B_5_72_0 ; real_T
B_5_75_0 ; real_T B_5_76_0 ; real_T B_5_78_0 ; real_T B_5_81_0 ; real_T
B_5_98_0 ; real_T B_5_108_0 ; real_T B_5_128_0 ; real_T B_5_132_0 ; real_T
B_5_134_0 ; real_T B_5_135_0 ; real_T B_5_136_0 ; real_T B_5_137_0 ; real_T
B_5_159_0 ; real_T B_5_182_0 ; real_T B_5_183_0 ; real_T B_5_185_0 ; real_T
B_5_186_0 ; real_T B_5_0_0 [ 9 ] ; real_T B_5_1_0_m ; real_T B_5_2_0 ; real_T
B_5_3_0_c ; real_T B_5_4_0_k ; real_T B_5_5_0 ; real_T B_5_6_0_c ; real_T
B_5_7_0 ; real_T B_5_8_0_b ; real_T B_5_9_0_p ; real_T B_5_10_0_c ; boolean_T
B_5_26_0 ; boolean_T B_5_43_0 ; boolean_T B_5_47_0 ; boolean_T B_5_57_0 ;
boolean_T B_5_58_0 ; boolean_T B_5_59_0 ; char_T pad_B_5_59_0 [ 2 ] ;
B_SampleIL1_Comment_3_1_T SampleandHold1 ; B_SampleIL1_Comment_3_1_T
SampleIL4 ; B_SampleIL1_Comment_3_1_T SampleIL3 ; B_SampleIL1_Comment_3_1_T
SampleIL2 ; B_SampleIL1_Comment_3_1_T SampleIL1 ; } B_Comment_3_1_T ; typedef
struct { real_T UnitDelay_DSTATE ; real_T StateSpace_DSTATE [ 4 ] ; real_T
TimeStampA ; real_T LastUAtTimeA ; real_T TimeStampB ; real_T LastUAtTimeB ;
real_T TimeStampA_c ; real_T LastUAtTimeA_f ; real_T TimeStampB_p ; real_T
LastUAtTimeB_k ; real_T TimeStampA_b ; real_T LastUAtTimeA_fk ; real_T
TimeStampB_pj ; real_T LastUAtTimeB_e ; real_T StateSpace_RWORK ; struct {
real_T modelTStart ; } TransportDelay1_RWORK ; struct { real_T modelTStart ;
} TransportDelay2_RWORK ; struct { real_T modelTStart ; }
TransportDelay_RWORK ; void * StateSpace_PWORK [ 65 ] ; void * Scope2_PWORK [
3 ] ; void * Scope3_PWORK [ 3 ] ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay1_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay2_PWORK ; void * Scope5_PWORK [ 4 ] ; void * Scope7_PWORK [ 2 ]
; struct { void * AQHandles ; void * SlioLTF ; }
TAQOutportLogging_InsertedFor_From42_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
TAQOutportLogging_InsertedFor_From43_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
TAQOutportLogging_InsertedFor_From44_at_outport_0_PWORK ; void *
Scope2_PWORK_o ; void * Scope3_PWORK_j [ 3 ] ; void * Scope4_PWORK [ 3 ] ;
void * Scope5_PWORK_h ; void * Scope6_PWORK [ 3 ] ; struct { void *
TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK ; void * Scope1_PWORK [ 2 ] ;
void * Scope7_PWORK_b [ 4 ] ; void * Scope9_PWORK [ 3 ] ; void *
Scope7_PWORK_e ; int_T StateSpace_IWORK [ 12 ] ; struct { int_T Tail ; int_T
Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay1_IWORK ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay2_IWORK ; struct {
int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay_IWORK ; int_T Abs_MODE ; int_T Sign_MODE ;
int_T Saturation_MODE ; int_T Step_MODE ; int_T Step2_MODE ; boolean_T
Switch_Mode ; boolean_T Compare_Mode ; boolean_T Compare_Mode_n ; boolean_T
Compare_Mode_i ; boolean_T Compare_Mode_f ; boolean_T Compare_Mode_a ;
boolean_T Compare_Mode_m ; boolean_T RelationalOperator_Mode ; boolean_T
RelationalOperator1_Mode ; boolean_T RelationalOperator2_Mode ; char_T
pad_RelationalOperator2_Mode [ 6 ] ; DW_SampleIL1_Comment_3_1_T
SampleandHold1 ; DW_SampleIL1_Comment_3_1_T SampleIL4 ;
DW_SampleIL1_Comment_3_1_T SampleIL3 ; DW_SampleIL1_Comment_3_1_T SampleIL2 ;
DW_SampleIL1_Comment_3_1_T SampleIL1 ; } DW_Comment_3_1_T ; typedef struct {
real_T Integrator_CSTATE ; real_T Integrator_CSTATE_f ; } X_Comment_3_1_T ;
typedef struct { real_T Integrator_CSTATE ; real_T Integrator_CSTATE_f ; }
XDot_Comment_3_1_T ; typedef struct { boolean_T Integrator_CSTATE ; boolean_T
Integrator_CSTATE_f ; } XDis_Comment_3_1_T ; typedef struct { real_T
Integrator_CSTATE ; real_T Integrator_CSTATE_f ; } CStateAbsTol_Comment_3_1_T
; typedef struct { real_T Abs_AbsZc_ZC ; real_T Sign_Input_ZC ; real_T
Switch_SwitchCond_ZC ; real_T Compare_RelopInput_ZC ; real_T
Saturation_UprLim_ZC ; real_T Saturation_LwrLim_ZC ; real_T
Compare_RelopInput_ZC_i ; real_T Compare_RelopInput_ZC_e ; real_T
Compare_RelopInput_ZC_ia ; real_T Compare_RelopInput_ZC_l ; real_T
Compare_RelopInput_ZC_a ; real_T RelationalOperator_RelopInput_ZC ; real_T
RelationalOperator1_RelopInput_ZC ; real_T RelationalOperator2_RelopInput_ZC
; real_T Step_StepTime_ZC ; real_T HitCrossing_HitNoOutput_ZC ; real_T
HitCrossing_HitNoOutput_ZC_i ; real_T Step2_StepTime_ZC ; real_T
HitCrossing_HitNoOutput_ZC_l ; ZCV_SampleIL1_Comment_3_1_T SampleandHold1 ;
ZCV_SampleIL1_Comment_3_1_T SampleIL4 ; ZCV_SampleIL1_Comment_3_1_T SampleIL3
; ZCV_SampleIL1_Comment_3_1_T SampleIL2 ; ZCV_SampleIL1_Comment_3_1_T
SampleIL1 ; } ZCV_Comment_3_1_T ; typedef struct { ZCSigState Abs_AbsZc_ZCE ;
ZCSigState Sign_Input_ZCE ; ZCSigState Switch_SwitchCond_ZCE ; ZCSigState
Compare_RelopInput_ZCE ; ZCSigState Saturation_UprLim_ZCE ; ZCSigState
Saturation_LwrLim_ZCE ; ZCSigState Compare_RelopInput_ZCE_i ; ZCSigState
Compare_RelopInput_ZCE_g ; ZCSigState Compare_RelopInput_ZCE_d ; ZCSigState
Compare_RelopInput_ZCE_n ; ZCSigState Compare_RelopInput_ZCE_gu ; ZCSigState
RelationalOperator_RelopInput_ZCE ; ZCSigState
RelationalOperator1_RelopInput_ZCE ; ZCSigState
RelationalOperator2_RelopInput_ZCE ; ZCSigState Step_StepTime_ZCE ;
ZCSigState HitCrossing_HitNoOutput_ZCE ; ZCSigState
HitCrossing_HitNoOutput_ZCE_n ; ZCSigState Step2_StepTime_ZCE ; ZCSigState
HitCrossing_HitNoOutput_ZCE_g ; ZCE_SampleIL1_Comment_3_1_T SampleandHold1 ;
ZCE_SampleIL1_Comment_3_1_T SampleIL4 ; ZCE_SampleIL1_Comment_3_1_T SampleIL3
; ZCE_SampleIL1_Comment_3_1_T SampleIL2 ; ZCE_SampleIL1_Comment_3_1_T
SampleIL1 ; } PrevZCX_Comment_3_1_T ; typedef struct { const real_T B_5_0_0 ;
const real_T B_5_1_0 ; const real_T B_5_2_0 ; const real_T B_5_3_0 ; const
real_T B_5_4_0 ; const real_T B_5_5_0 ; } ConstB_Comment_3_1_T ;
#define Comment_3_1_rtC(S) ((ConstB_Comment_3_1_T *) _ssGetConstBlockIO(S))
typedef struct { real_T * B_1_1 ; real_T * B_1_2 ; real_T * B_1_3 ; }
ExtY_Comment_3_1_T ; struct P_SampleIL1_Comment_3_1_T_ { real_T P_0 ; } ;
struct P_Comment_3_1_T_ { real_T P_0 ; real_T P_1 ; real_T P_2 ; real_T P_3 ;
real_T P_4 ; real_T P_5 ; real_T P_6 [ 6 ] ; real_T P_7 [ 6 ] ; real_T P_8 [
8 ] ; real_T P_9 [ 8 ] ; real_T P_10 ; real_T P_11 ; real_T P_12 ; real_T
P_13 [ 2 ] ; real_T P_14 ; real_T P_15 [ 2 ] ; real_T P_16 [ 16 ] ; real_T
P_17 [ 2 ] ; real_T P_18 [ 44 ] ; real_T P_19 [ 2 ] ; real_T P_20 [ 76 ] ;
real_T P_21 [ 2 ] ; real_T P_22 [ 209 ] ; real_T P_23 [ 2 ] ; real_T P_24 [ 4
] ; real_T P_25 [ 2 ] ; real_T P_26 ; real_T P_27 [ 2 ] ; real_T P_28 [ 3 ] ;
real_T P_29 [ 2 ] ; real_T P_31 [ 2 ] ; real_T P_32 ; real_T P_33 [ 2 ] ;
real_T P_34 ; real_T P_35 [ 2 ] ; real_T P_37 [ 2 ] ; real_T P_38 ; real_T
P_39 [ 2 ] ; real_T P_40 ; real_T P_41 [ 2 ] ; real_T P_43 [ 2 ] ; real_T
P_44 ; real_T P_45 [ 2 ] ; real_T P_46 ; real_T P_47 [ 2 ] ; real_T P_48 ;
real_T P_49 [ 2 ] ; real_T P_50 ; real_T P_51 [ 2 ] ; real_T P_52 [ 9 ] ;
real_T P_53 [ 2 ] ; real_T P_54 [ 9 ] ; real_T P_55 [ 2 ] ; real_T P_56 [ 9 ]
; real_T P_57 [ 2 ] ; real_T P_58 [ 9 ] ; real_T P_59 [ 2 ] ; real_T P_60 ;
real_T P_61 ; real_T P_62 ; real_T P_63 ; real_T P_64 ; real_T P_65 [ 3 ] ;
real_T P_66 [ 3 ] ; real_T P_67 ; real_T P_68 ; real_T P_69 ; real_T P_70 ;
real_T P_71 ; real_T P_72 ; real_T P_73 ; real_T P_74 ; real_T P_75 ; real_T
P_76 ; real_T P_77 ; real_T P_78 ; real_T P_79 [ 3 ] ; real_T P_80 [ 3 ] ;
real_T P_81 [ 3 ] ; real_T P_82 [ 3 ] ; real_T P_83 ; real_T P_84 ; real_T
P_85 [ 3 ] ; real_T P_86 [ 3 ] ; real_T P_87 ; real_T P_88 ; real_T P_89 ;
real_T P_90 ; real_T P_91 ; real_T P_92 ; real_T P_93 ; real_T P_94 ; real_T
P_95 ; real_T P_96 ; real_T P_97 ; real_T P_98 ; real_T P_99 ; real_T P_100 ;
real_T P_101 ; real_T P_102 [ 8 ] ; real_T P_103 [ 8 ] ; real_T P_104 ;
real_T P_105 [ 9 ] ; real_T P_106 ; real_T P_107 ; real_T P_108 ; real_T
P_109 ; real_T P_110 ; real_T P_111 ; real_T P_112 ; real_T P_113 ; real_T
P_114 ; real_T P_115 ; P_SampleIL1_Comment_3_1_T SampleandHold1 ;
P_SampleIL1_Comment_3_1_T SampleIL4 ; P_SampleIL1_Comment_3_1_T SampleIL3 ;
P_SampleIL1_Comment_3_1_T SampleIL2 ; P_SampleIL1_Comment_3_1_T SampleIL1 ; }
; extern P_Comment_3_1_T Comment_3_1_rtDefaultP ; extern const
ConstB_Comment_3_1_T Comment_3_1_rtInvariant ;
#endif
