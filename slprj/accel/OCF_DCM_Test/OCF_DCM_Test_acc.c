#include "__cf_OCF_DCM_Test.h"
#include <math.h>
#include "OCF_DCM_Test_acc.h"
#include "OCF_DCM_Test_acc_private.h"
#include <stdio.h>
#include "slexec_vm_simstruct_bridge.h"
#include "slexec_vm_zc_functions.h"
#include "slexec_vm_lookup_functions.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "simtarget/slSimTgtMdlrefSfcnBridge.h"
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
#include "simtarget/slAccSfcnBridge.h"
#ifndef __RTW_UTFREE__  
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T OCF_DCM_Test_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T * bufSzPtr ,
int_T * tailPtr , int_T * headPtr , int_T * lastPtr , real_T tMinusDelay ,
real_T * * tBufPtr , real_T * * uBufPtr , real_T * * xBufPtr , boolean_T
isfixedbuf , boolean_T istransportdelay , int_T * maxNewBufSzPtr ) { int_T
testIdx ; int_T tail = * tailPtr ; int_T bufSz = * bufSzPtr ; real_T * tBuf =
* tBufPtr ; real_T * xBuf = ( NULL ) ; int_T numBuffer = 2 ; if (
istransportdelay ) { numBuffer = 3 ; xBuf = * xBufPtr ; } testIdx = ( tail <
( bufSz - 1 ) ) ? ( tail + 1 ) : 0 ; if ( ( tMinusDelay <= tBuf [ testIdx ] )
&& ! isfixedbuf ) { int_T j ; real_T * tempT ; real_T * tempU ; real_T *
tempX = ( NULL ) ; real_T * uBuf = * uBufPtr ; int_T newBufSz = bufSz + 1024
; if ( newBufSz > * maxNewBufSzPtr ) { * maxNewBufSzPtr = newBufSz ; } tempU
= ( real_T * ) utMalloc ( numBuffer * newBufSz * sizeof ( real_T ) ) ; if (
tempU == ( NULL ) ) { return ( false ) ; } tempT = tempU + newBufSz ; if (
istransportdelay ) tempX = tempT + newBufSz ; for ( j = tail ; j < bufSz ; j
++ ) { tempT [ j - tail ] = tBuf [ j ] ; tempU [ j - tail ] = uBuf [ j ] ; if
( istransportdelay ) tempX [ j - tail ] = xBuf [ j ] ; } for ( j = 0 ; j <
tail ; j ++ ) { tempT [ j + bufSz - tail ] = tBuf [ j ] ; tempU [ j + bufSz -
tail ] = uBuf [ j ] ; if ( istransportdelay ) tempX [ j + bufSz - tail ] =
xBuf [ j ] ; } if ( * lastPtr > tail ) { * lastPtr -= tail ; } else { *
lastPtr += ( bufSz - tail ) ; } * tailPtr = 0 ; * headPtr = bufSz ; utFree (
uBuf ) ; * bufSzPtr = newBufSz ; * tBufPtr = tempT ; * uBufPtr = tempU ; if (
istransportdelay ) * xBufPtr = tempX ; } else { * tailPtr = testIdx ; }
return ( true ) ; } real_T OCF_DCM_Test_acc_rt_TDelayInterpolate ( real_T
tMinusDelay , real_T tStart , real_T * tBuf , real_T * uBuf , int_T bufSz ,
int_T * lastIdx , int_T oldestIdx , int_T newIdx , real_T initOutput ,
boolean_T discrete , boolean_T minorStepAndTAtLastMajorOutput ) { int_T i ;
real_T yout , t1 , t2 , u1 , u2 ; if ( ( newIdx == 0 ) && ( oldestIdx == 0 )
&& ( tMinusDelay > tStart ) ) return initOutput ; if ( tMinusDelay <= tStart
) return initOutput ; if ( ( tMinusDelay <= tBuf [ oldestIdx ] ) ) { if (
discrete ) { return ( uBuf [ oldestIdx ] ) ; } else { int_T tempIdx =
oldestIdx + 1 ; if ( oldestIdx == bufSz - 1 ) tempIdx = 0 ; t1 = tBuf [
oldestIdx ] ; t2 = tBuf [ tempIdx ] ; u1 = uBuf [ oldestIdx ] ; u2 = uBuf [
tempIdx ] ; if ( t2 == t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; } else {
yout = u1 ; } } else { real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 ) ;
real_T f2 = 1.0 - f1 ; yout = f1 * u1 + f2 * u2 ; } return yout ; } } if (
minorStepAndTAtLastMajorOutput ) { if ( newIdx != 0 ) { if ( * lastIdx ==
newIdx ) { ( * lastIdx ) -- ; } newIdx -- ; } else { if ( * lastIdx == newIdx
) { * lastIdx = bufSz - 1 ; } newIdx = bufSz - 1 ; } } i = * lastIdx ; if (
tBuf [ i ] < tMinusDelay ) { while ( tBuf [ i ] < tMinusDelay ) { if ( i ==
newIdx ) break ; i = ( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } } else { while
( tBuf [ i ] >= tMinusDelay ) { i = ( i > 0 ) ? i - 1 : ( bufSz - 1 ) ; } i =
( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } * lastIdx = i ; if ( discrete ) {
double tempEps = ( DBL_EPSILON ) * 128.0 ; double localEps = tempEps *
muDoubleScalarAbs ( tBuf [ i ] ) ; if ( tempEps > localEps ) { localEps =
tempEps ; } localEps = localEps / 2.0 ; if ( tMinusDelay >= ( tBuf [ i ] -
localEps ) ) { yout = uBuf [ i ] ; } else { if ( i == 0 ) { yout = uBuf [
bufSz - 1 ] ; } else { yout = uBuf [ i - 1 ] ; } } } else { if ( i == 0 ) {
t1 = tBuf [ bufSz - 1 ] ; u1 = uBuf [ bufSz - 1 ] ; } else { t1 = tBuf [ i -
1 ] ; u1 = uBuf [ i - 1 ] ; } t2 = tBuf [ i ] ; u2 = uBuf [ i ] ; if ( t2 ==
t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; } else { yout = u1 ; } } else {
real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 ) ; real_T f2 = 1.0 - f1 ; yout
= f1 * u1 + f2 * u2 ; } } return ( yout ) ; } real_T look1_binlxpw ( real_T
u0 , const real_T bp0 [ ] , const real_T table [ ] , uint32_T maxIndex ) {
real_T frac ; uint32_T iRght ; uint32_T iLeft ; uint32_T bpIdx ; if ( u0 <=
bp0 [ 0U ] ) { iLeft = 0U ; frac = ( u0 - bp0 [ 0U ] ) / ( bp0 [ 1U ] - bp0 [
0U ] ) ; } else if ( u0 < bp0 [ maxIndex ] ) { bpIdx = maxIndex >> 1U ; iLeft
= 0U ; iRght = maxIndex ; while ( iRght - iLeft > 1U ) { if ( u0 < bp0 [
bpIdx ] ) { iRght = bpIdx ; } else { iLeft = bpIdx ; } bpIdx = ( iRght +
iLeft ) >> 1U ; } frac = ( u0 - bp0 [ iLeft ] ) / ( bp0 [ iLeft + 1U ] - bp0
[ iLeft ] ) ; } else { iLeft = maxIndex - 1U ; frac = ( u0 - bp0 [ maxIndex -
1U ] ) / ( bp0 [ maxIndex ] - bp0 [ maxIndex - 1U ] ) ; } return ( table [
iLeft + 1U ] - table [ iLeft ] ) * frac + table [ iLeft ] ; } void
rt_ssGetBlockPath ( SimStruct * S , int_T sysIdx , int_T blkIdx , char_T * *
path ) { _ssGetBlockPath ( S , sysIdx , blkIdx , path ) ; } void
rt_ssSet_slErrMsg ( SimStruct * S , void * diag ) { if ( !
_ssIsErrorStatusAslErrMsg ( S ) ) { _ssSet_slErrMsg ( S , diag ) ; } else {
_ssDiscardDiagnostic ( S , diag ) ; } } void rt_ssReportDiagnosticAsWarning (
SimStruct * S , void * diag ) { _ssReportDiagnosticAsWarning ( S , diag ) ; }
void OCF_DCM_Test_SampleIL1_Init ( SimStruct * S , B_SampleIL1_OCF_DCM_Test_T
* localB , P_SampleIL1_OCF_DCM_Test_T * localP ) { localB -> B_2_0_0 = localP
-> P_0 ; } void OCF_DCM_Test_SampleIL1 ( SimStruct * S , boolean_T
rtu_Trigger , real_T rtu_In , B_SampleIL1_OCF_DCM_Test_T * localB ,
DW_SampleIL1_OCF_DCM_Test_T * localDW , ZCE_SampleIL1_OCF_DCM_Test_T *
localZCE ) { if ( ssIsMajorTimeStep ( S ) != 0 ) { if ( rtu_Trigger && (
localZCE -> SampleIL1_Trig_ZCE != POS_ZCSIG ) ) { localB -> B_2_0_0 = rtu_In
; localDW -> SampleIL1_SubsysRanBC = 4 ; } localZCE -> SampleIL1_Trig_ZCE =
rtu_Trigger ; } } void OCF_DCM_Test_SampleIL1_Term ( SimStruct * const S ) {
} static void mdlOutputs ( SimStruct * S , int_T tid ) { real_T * lastU ;
real_T rtb_B_7_41_0 ; real_T rtb_B_7_2_0 ; boolean_T rtb_B_7_68_0 ; boolean_T
rtb_B_7_67_0 ; boolean_T rtb_B_7_66_0 ; int32_T isHit ; B_OCF_DCM_Test_T *
_rtB ; P_OCF_DCM_Test_T * _rtP ; X_OCF_DCM_Test_T * _rtX ;
PrevZCX_OCF_DCM_Test_T * _rtZCE ; DW_OCF_DCM_Test_T * _rtDW ; _rtDW = ( (
DW_OCF_DCM_Test_T * ) ssGetRootDWork ( S ) ) ; _rtZCE = ( (
PrevZCX_OCF_DCM_Test_T * ) _ssGetPrevZCSigState ( S ) ) ; _rtX = ( (
X_OCF_DCM_Test_T * ) ssGetContStates ( S ) ) ; _rtP = ( ( P_OCF_DCM_Test_T *
) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_OCF_DCM_Test_T * ) _ssGetModelBlockIO
( S ) ) ; _rtB -> B_7_1_0 = rt_Lookup ( _rtP -> P_7 , 6 , ssGetT ( S ) , _rtP
-> P_8 ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW ->
Step2_MODE = ( ssGetTaskTime ( S , 1 ) >= _rtP -> P_9 ) ; if ( _rtDW ->
Step2_MODE == 1 ) { rtb_B_7_2_0 = _rtP -> P_11 ; } else { rtb_B_7_2_0 = _rtP
-> P_10 ; } if ( ! ( muDoubleScalarAbs ( rtb_B_7_2_0 ) > _rtP -> P_12 ) ) {
if ( muDoubleScalarSign ( rtb_B_7_2_0 ) > _rtP -> P_0 ) { rtb_B_7_2_0 = _rtB
-> B_7_9_0_b ; } else { rtb_B_7_2_0 = _rtB -> B_7_10_0_p ; } } _rtB ->
B_7_6_0 = _rtB -> B_7_8_0_c / rtb_B_7_2_0 ; } isHit = ssIsSampleHit ( S , 2 ,
0 ) ; if ( isHit != 0 ) { _rtB -> B_7_7_0 = _rtDW -> UnitDelay_DSTATE ; }
isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_7_8_0 =
_rtB -> B_7_6_0 - _rtB -> B_7_7_0 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ;
if ( isHit != 0 ) { ssCallAccelRunBlock ( S , 7 , 9 , SS_CALL_MDL_OUTPUTS ) ;
_rtB -> B_7_10_0 = _rtP -> P_62 * _rtB -> B_7_9_0 [ 10 ] ;
ssCallAccelRunBlock ( S , 7 , 11 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_7_12_0 =
_rtP -> P_63 * _rtB -> B_7_9_0 [ 11 ] ; ssCallAccelRunBlock ( S , 7 , 13 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_7_14_0 = _rtP -> P_64 * _rtB -> B_7_9_0 [
12 ] ; ssCallAccelRunBlock ( S , 7 , 15 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
B_7_16_0 = _rtP -> P_65 * _rtB -> B_7_9_0 [ 17 ] ; } _rtB -> B_7_21_0 =
look1_binlxpw ( muDoubleScalarRem ( ssGetT ( S ) - _rtB -> B_7_18_0 , _rtB ->
B_7_3_0 ) , _rtP -> P_67 , _rtP -> P_66 , 2U ) ; _rtB -> B_7_22_0 = _rtB ->
B_7_21_0 - _rtB -> B_7_2_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit
!= 0 ) { if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Compare_Mode = ( _rtB
-> B_7_22_0 <= OCF_DCM_Test_rtC ( S ) -> B_7_3_0 ) ; } _rtB -> B_7_23_0 =
_rtDW -> Compare_Mode ; OCF_DCM_Test_SampleIL1 ( S , _rtB -> B_7_23_0 , _rtB
-> B_7_16_0 , & _rtB -> SampleandHold1 , & _rtDW -> SampleandHold1 , & _rtZCE
-> SampleandHold1 ) ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay1_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay1_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_68 ; _rtB -> B_7_25_0
= OCF_DCM_Test_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay1_IWORK . CircularBufSize , & _rtDW ->
TransportDelay1_IWORK . Last , _rtDW -> TransportDelay1_IWORK . Tail , _rtDW
-> TransportDelay1_IWORK . Head , _rtP -> P_69 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } _rtB -> B_7_26_0 = _rtB -> B_7_25_0 - _rtB -> B_7_2_0 ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if ( ssIsMajorTimeStep ( S
) != 0 ) { _rtDW -> Compare_Mode_n = ( _rtB -> B_7_26_0 <= OCF_DCM_Test_rtC (
S ) -> B_7_4_0 ) ; } _rtB -> B_7_27_0 = _rtDW -> Compare_Mode_n ;
OCF_DCM_Test_SampleIL1 ( S , _rtB -> B_7_27_0 , _rtB -> B_7_16_0 , & _rtB ->
SampleIL2 , & _rtDW -> SampleIL2 , & _rtZCE -> SampleIL2 ) ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay2_PWORK . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay2_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_70 ; _rtB -> B_7_29_0 =
OCF_DCM_Test_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay2_IWORK . CircularBufSize , & _rtDW ->
TransportDelay2_IWORK . Last , _rtDW -> TransportDelay2_IWORK . Tail , _rtDW
-> TransportDelay2_IWORK . Head , _rtP -> P_71 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } _rtB -> B_7_30_0 = _rtB -> B_7_29_0 - _rtB -> B_7_2_0 ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if ( ssIsMajorTimeStep ( S
) != 0 ) { _rtDW -> Compare_Mode_i = ( _rtB -> B_7_30_0 <= OCF_DCM_Test_rtC (
S ) -> B_7_5_0 ) ; } _rtB -> B_7_31_0 = _rtDW -> Compare_Mode_i ;
OCF_DCM_Test_SampleIL1 ( S , _rtB -> B_7_31_0 , _rtB -> B_7_16_0 , & _rtB ->
SampleIL3 , & _rtDW -> SampleIL3 , & _rtZCE -> SampleIL3 ) ; _rtB -> B_7_33_0
= _rtP -> P_72 * _rtB -> SampleandHold1 . B_2_0_0 ; _rtB -> B_7_34_0 = _rtP
-> P_73 * _rtB -> SampleIL2 . B_2_0_0 ; _rtB -> B_7_35_0 = _rtP -> P_74 *
_rtB -> SampleIL3 . B_2_0_0 ; ssCallAccelRunBlock ( S , 1 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 7 , 37 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 7 , 38 ,
SS_CALL_MDL_OUTPUTS ) ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit !=
0 ) { _rtB -> B_7_39_0 = _rtP -> P_75 * _rtB -> B_7_9_0 [ 9 ] ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { OCF_DCM_Test_SampleIL1 ( S
, _rtB -> B_7_23_0 , _rtB -> B_7_39_0 , & _rtB -> SampleIL4 , & _rtDW ->
SampleIL4 , & _rtZCE -> SampleIL4 ) ; rtb_B_7_41_0 = _rtB -> B_7_11_0 - _rtB
-> SampleIL4 . B_2_0_0 ; _rtB -> B_7_42_0 = _rtP -> P_76 * rtb_B_7_41_0 ; }
_rtB -> B_7_43_0 = _rtX -> Integrator_CSTATE ; _rtB -> B_7_44_0 = _rtB ->
B_7_42_0 + _rtB -> B_7_43_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if (
isHit != 0 ) { OCF_DCM_Test_SampleIL1 ( S , _rtB -> B_7_23_0 , _rtB ->
B_7_16_0 , & _rtB -> SampleIL1 , & _rtDW -> SampleIL1 , & _rtZCE -> SampleIL1
) ; } _rtB -> B_7_46_0 = _rtB -> B_7_44_0 - _rtB -> SampleIL1 . B_2_0_0 ;
_rtB -> B_7_48_0 = _rtX -> Integrator_CSTATE_f ; _rtB -> B_7_49_0 = _rtP ->
P_78 * _rtB -> B_7_46_0 + _rtB -> B_7_48_0 ; if ( ssIsMajorTimeStep ( S ) !=
0 ) { _rtDW -> Saturation_MODE = _rtB -> B_7_49_0 >= _rtP -> P_80 ? 1 : _rtB
-> B_7_49_0 > _rtP -> P_81 ? 0 : - 1 ; } _rtB -> B_7_50_0 = _rtDW ->
Saturation_MODE == 1 ? _rtP -> P_80 : _rtDW -> Saturation_MODE == - 1 ? _rtP
-> P_81 : _rtB -> B_7_49_0 ; ssCallAccelRunBlock ( S , 7 , 51 ,
SS_CALL_MDL_OUTPUTS ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0
) { ssCallAccelRunBlock ( S , 7 , 52 , SS_CALL_MDL_OUTPUTS ) ; } _rtB ->
B_7_53_0 = _rtP -> P_82 * _rtB -> B_7_29_0 ; ssCallAccelRunBlock ( S , 7 , 54
, SS_CALL_MDL_OUTPUTS ) ; isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit !=
0 ) { ssCallAccelRunBlock ( S , 7 , 55 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 7 , 56 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 7 , 57 , SS_CALL_MDL_OUTPUTS ) ; }
ssCallAccelRunBlock ( S , 7 , 58 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 7 , 59 , SS_CALL_MDL_OUTPUTS ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if ( ssIsMajorTimeStep ( S
) != 0 ) { _rtDW -> Compare_Mode_f = ( _rtB -> B_7_21_0 == OCF_DCM_Test_rtC (
S ) -> B_7_0_0 ) ; _rtDW -> Compare_Mode_a = ( _rtB -> B_7_25_0 ==
OCF_DCM_Test_rtC ( S ) -> B_7_1_0 ) ; } _rtB -> B_7_60_0 = _rtDW ->
Compare_Mode_f ; _rtB -> B_7_61_0 = _rtDW -> Compare_Mode_a ; if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Compare_Mode_m = ( _rtB -> B_7_29_0
== OCF_DCM_Test_rtC ( S ) -> B_7_2_0 ) ; } _rtB -> B_7_62_0 = _rtDW ->
Compare_Mode_m ; ssCallAccelRunBlock ( S , 7 , 63 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 7 , 64 , SS_CALL_MDL_OUTPUTS ) ; }
ssCallAccelRunBlock ( S , 7 , 65 , SS_CALL_MDL_OUTPUTS ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if ( ssIsMajorTimeStep ( S
) != 0 ) { _rtDW -> RelationalOperator_Mode = ( _rtB -> B_7_1_0_m > _rtB ->
B_7_21_0 ) ; _rtDW -> RelationalOperator1_Mode = ( _rtB -> B_7_1_0_m > _rtB
-> B_7_25_0 ) ; } rtb_B_7_66_0 = _rtDW -> RelationalOperator_Mode ;
rtb_B_7_67_0 = _rtDW -> RelationalOperator1_Mode ; if ( ssIsMajorTimeStep ( S
) != 0 ) { _rtDW -> RelationalOperator2_Mode = ( _rtB -> B_7_1_0_m > _rtB ->
B_7_29_0 ) ; } rtb_B_7_68_0 = _rtDW -> RelationalOperator2_Mode ; } _rtB ->
B_7_73_0 = look1_binlxpw ( muDoubleScalarRem ( ssGetT ( S ) - _rtB ->
B_7_70_0 , _rtB -> B_7_4_0 ) , _rtP -> P_84 , _rtP -> P_83 , 2U ) ; _rtB ->
B_7_78_0 = look1_binlxpw ( muDoubleScalarRem ( ssGetT ( S ) - _rtB ->
B_7_75_0 , _rtB -> B_7_5_0 ) , _rtP -> P_86 , _rtP -> P_85 , 2U ) ; { real_T
* * uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_87 ; _rtB -> B_7_79_0 =
OCF_DCM_Test_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay_IWORK . CircularBufSize , & _rtDW ->
TransportDelay_IWORK . Last , _rtDW -> TransportDelay_IWORK . Tail , _rtDW ->
TransportDelay_IWORK . Head , _rtP -> P_88 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } _rtB -> B_7_84_0 = look1_binlxpw ( muDoubleScalarRem ( ssGetT ( S ) -
_rtB -> B_7_81_0 , _rtB -> B_7_6_0_c ) , _rtP -> P_90 , _rtP -> P_89 , 2U ) ;
ssCallAccelRunBlock ( S , 7 , 85 , SS_CALL_MDL_OUTPUTS ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_7_101_0 =
rtb_B_7_66_0 ; _rtB -> B_7_111_0 = rtb_B_7_67_0 ; _rtDW -> Step_MODE = (
ssGetTaskTime ( S , 1 ) >= _rtP -> P_91 ) ; if ( _rtDW -> Step_MODE == 1 ) {
rtb_B_7_2_0 = _rtP -> P_93 ; } else { rtb_B_7_2_0 = _rtP -> P_92 ; } if (
rtb_B_7_2_0 > _rtP -> P_94 ) { _rtB -> B_7_131_0 = rtb_B_7_68_0 ; } else {
_rtB -> B_7_131_0 = _rtB -> B_7_7_0_k ; } } if ( ( _rtDW -> TimeStampA >=
ssGetT ( S ) ) && ( _rtDW -> TimeStampB >= ssGetT ( S ) ) ) { _rtB ->
B_7_135_0 = 0.0 ; } else { rtb_B_7_2_0 = _rtDW -> TimeStampA ; lastU = &
_rtDW -> LastUAtTimeA ; if ( _rtDW -> TimeStampA < _rtDW -> TimeStampB ) { if
( _rtDW -> TimeStampB < ssGetT ( S ) ) { rtb_B_7_2_0 = _rtDW -> TimeStampB ;
lastU = & _rtDW -> LastUAtTimeB ; } } else { if ( _rtDW -> TimeStampA >=
ssGetT ( S ) ) { rtb_B_7_2_0 = _rtDW -> TimeStampB ; lastU = & _rtDW ->
LastUAtTimeB ; } } _rtB -> B_7_135_0 = ( _rtB -> B_7_1_0 - * lastU ) / (
ssGetT ( S ) - rtb_B_7_2_0 ) ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if (
isHit != 0 ) { _rtB -> B_7_137_0 = _rtP -> P_96 * _rtB -> B_7_9_0 [ 14 ] ;
_rtB -> B_7_138_0 = _rtP -> P_97 * _rtB -> B_7_9_0 [ 15 ] ; _rtB -> B_7_139_0
= _rtP -> P_98 * _rtB -> B_7_9_0 [ 16 ] ; _rtB -> B_7_140_0 = _rtP -> P_99 *
_rtB -> B_7_9_0 [ 13 ] ; ssCallAccelRunBlock ( S , 7 , 141 ,
SS_CALL_MDL_OUTPUTS ) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit !=
0 ) { ssCallAccelRunBlock ( S , 7 , 180 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 7 , 181 , SS_CALL_MDL_OUTPUTS ) ; } _rtB ->
B_7_182_0 = _rtP -> P_100 * _rtB -> B_7_46_0 ; isHit = ssIsSampleHit ( S , 1
, 0 ) ; if ( isHit != 0 ) { _rtB -> B_7_183_0 = _rtP -> P_101 * rtb_B_7_41_0
; } UNUSED_PARAMETER ( tid ) ; } static void mdlOutputsTID3 ( SimStruct * S ,
int_T tid ) { B_OCF_DCM_Test_T * _rtB ; P_OCF_DCM_Test_T * _rtP ; _rtP = ( (
P_OCF_DCM_Test_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_OCF_DCM_Test_T * )
_ssGetModelBlockIO ( S ) ) ; memcpy ( & _rtB -> B_7_0_0 [ 0 ] , & _rtP ->
P_102 [ 0 ] , 9U * sizeof ( real_T ) ) ; _rtB -> B_7_1_0_m = _rtP -> P_103 ;
_rtB -> B_7_2_0 = _rtP -> P_104 ; _rtB -> B_7_3_0 = _rtP -> P_105 ; _rtB ->
B_7_4_0 = _rtP -> P_106 ; _rtB -> B_7_5_0 = _rtP -> P_107 ; _rtB -> B_7_6_0_c
= _rtP -> P_108 ; _rtB -> B_7_7_0_k = _rtP -> P_109 ; _rtB -> B_7_8_0_c =
_rtP -> P_110 ; _rtB -> B_7_9_0_b = _rtP -> P_111 ; _rtB -> B_7_10_0_p = _rtP
-> P_112 ; _rtB -> B_7_11_0 = _rtP -> P_113 ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { real_T * lastU ;
int32_T isHit ; B_OCF_DCM_Test_T * _rtB ; P_OCF_DCM_Test_T * _rtP ;
DW_OCF_DCM_Test_T * _rtDW ; _rtDW = ( ( DW_OCF_DCM_Test_T * ) ssGetRootDWork
( S ) ) ; _rtP = ( ( P_OCF_DCM_Test_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_OCF_DCM_Test_T * ) _ssGetModelBlockIO ( S ) ) ; isHit = ssIsSampleHit ( S ,
2 , 0 ) ; if ( isHit != 0 ) { _rtDW -> UnitDelay_DSTATE = _rtB -> B_7_6_0 ;
ssCallAccelRunBlock ( S , 7 , 9 , SS_CALL_MDL_UPDATE ) ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay1_IWORK . Head = ( ( _rtDW -> TransportDelay1_IWORK . Head < (
_rtDW -> TransportDelay1_IWORK . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay1_IWORK . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay1_IWORK . Head == _rtDW -> TransportDelay1_IWORK . Tail ) { if
( ! OCF_DCM_Test_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay1_IWORK . CircularBufSize , & _rtDW -> TransportDelay1_IWORK .
Tail , & _rtDW -> TransportDelay1_IWORK . Head , & _rtDW ->
TransportDelay1_IWORK . Last , simTime - _rtP -> P_68 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay1_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay1_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay1_IWORK . Head ] = _rtB ->
B_7_73_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay2_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay2_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay2_IWORK . Head = ( ( _rtDW ->
TransportDelay2_IWORK . Head < ( _rtDW -> TransportDelay2_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay2_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay2_IWORK . Head == _rtDW ->
TransportDelay2_IWORK . Tail ) { if ( !
OCF_DCM_Test_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay2_IWORK . CircularBufSize , & _rtDW -> TransportDelay2_IWORK .
Tail , & _rtDW -> TransportDelay2_IWORK . Head , & _rtDW ->
TransportDelay2_IWORK . Last , simTime - _rtP -> P_70 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay2_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay2_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay2_IWORK . Head ] = _rtB ->
B_7_78_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * *
) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK . Head = ( ( _rtDW ->
TransportDelay_IWORK . Head < ( _rtDW -> TransportDelay_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay_IWORK . Head == _rtDW -> TransportDelay_IWORK
. Tail ) { if ( ! OCF_DCM_Test_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK . CircularBufSize , & _rtDW -> TransportDelay_IWORK .
Tail , & _rtDW -> TransportDelay_IWORK . Head , & _rtDW ->
TransportDelay_IWORK . Last , simTime - _rtP -> P_87 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] = _rtB ->
B_7_84_0 ; } if ( _rtDW -> TimeStampA == ( rtInf ) ) { _rtDW -> TimeStampA =
ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA ; } else if ( _rtDW ->
TimeStampB == ( rtInf ) ) { _rtDW -> TimeStampB = ssGetT ( S ) ; lastU = &
_rtDW -> LastUAtTimeB ; } else if ( _rtDW -> TimeStampA < _rtDW -> TimeStampB
) { _rtDW -> TimeStampA = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA ; }
else { _rtDW -> TimeStampB = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB ;
} * lastU = _rtB -> B_7_1_0 ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdateTID3 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { B_OCF_DCM_Test_T * _rtB ;
XDot_OCF_DCM_Test_T * _rtXdot ; _rtXdot = ( ( XDot_OCF_DCM_Test_T * ) ssGetdX
( S ) ) ; _rtB = ( ( B_OCF_DCM_Test_T * ) _ssGetModelBlockIO ( S ) ) ;
_rtXdot -> Integrator_CSTATE = _rtB -> B_7_183_0 ; _rtXdot ->
Integrator_CSTATE_f = _rtB -> B_7_182_0 ; }
#define MDL_ZERO_CROSSINGS
static void mdlZeroCrossings ( SimStruct * S ) { B_OCF_DCM_Test_T * _rtB ;
P_OCF_DCM_Test_T * _rtP ; ZCV_OCF_DCM_Test_T * _rtZCSV ; _rtZCSV = ( (
ZCV_OCF_DCM_Test_T * ) ssGetSolverZcSignalVector ( S ) ) ; _rtP = ( (
P_OCF_DCM_Test_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_OCF_DCM_Test_T * )
_ssGetModelBlockIO ( S ) ) ; _rtZCSV -> Step2_StepTime_ZC = ssGetT ( S ) -
_rtP -> P_9 ; _rtZCSV -> Compare_RelopInput_ZC = _rtB -> B_7_22_0 -
OCF_DCM_Test_rtC ( S ) -> B_7_3_0 ; _rtZCSV -> Compare_RelopInput_ZC_i = _rtB
-> B_7_26_0 - OCF_DCM_Test_rtC ( S ) -> B_7_4_0 ; _rtZCSV ->
Compare_RelopInput_ZC_e = _rtB -> B_7_30_0 - OCF_DCM_Test_rtC ( S ) ->
B_7_5_0 ; _rtZCSV -> Saturation_UprLim_ZC = _rtB -> B_7_49_0 - _rtP -> P_80 ;
_rtZCSV -> Saturation_LwrLim_ZC = _rtB -> B_7_49_0 - _rtP -> P_81 ; _rtZCSV
-> Compare_RelopInput_ZC_ia = _rtB -> B_7_21_0 - OCF_DCM_Test_rtC ( S ) ->
B_7_0_0 ; _rtZCSV -> Compare_RelopInput_ZC_l = _rtB -> B_7_25_0 -
OCF_DCM_Test_rtC ( S ) -> B_7_1_0 ; _rtZCSV -> Compare_RelopInput_ZC_a = _rtB
-> B_7_29_0 - OCF_DCM_Test_rtC ( S ) -> B_7_2_0 ; _rtZCSV ->
RelationalOperator_RelopInput_ZC = _rtB -> B_7_1_0_m - _rtB -> B_7_21_0 ;
_rtZCSV -> RelationalOperator1_RelopInput_ZC = _rtB -> B_7_1_0_m - _rtB ->
B_7_25_0 ; _rtZCSV -> RelationalOperator2_RelopInput_ZC = _rtB -> B_7_1_0_m -
_rtB -> B_7_29_0 ; _rtZCSV -> Step_StepTime_ZC = ssGetT ( S ) - _rtP -> P_91
; _rtZCSV -> HitCrossing_HitNoOutput_ZC = _rtB -> B_7_135_0 - _rtP -> P_95 ;
} static void mdlInitializeSizes ( SimStruct * S ) { ssSetChecksumVal ( S , 0
, 33501599U ) ; ssSetChecksumVal ( S , 1 , 3004784592U ) ; ssSetChecksumVal (
S , 2 , 3727891204U ) ; ssSetChecksumVal ( S , 3 , 2289226808U ) ; { mxArray
* slVerStructMat = NULL ; mxArray * slStrMat = mxCreateString ( "simulink" )
; char slVerChar [ 10 ] ; int status = mexCallMATLAB ( 1 , & slVerStructMat ,
1 , & slStrMat , "ver" ) ; if ( status == 0 ) { mxArray * slVerMat =
mxGetField ( slVerStructMat , 0 , "Version" ) ; if ( slVerMat == NULL ) {
status = 1 ; } else { status = mxGetString ( slVerMat , slVerChar , 10 ) ; }
} mxDestroyArray ( slStrMat ) ; mxDestroyArray ( slVerStructMat ) ; if ( (
status == 1 ) || ( strcmp ( slVerChar , "10.0" ) != 0 ) ) { return ; } }
ssSetOptions ( S , SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork (
S ) != sizeof ( DW_OCF_DCM_Test_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( B_OCF_DCM_Test_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofY ( S ) != sizeof
( ExtY_OCF_DCM_Test_T ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal ExternalOutputs sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
P_OCF_DCM_Test_T ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetModelRtp ( S , ( real_T *
) & OCF_DCM_Test_rtDefaultP ) ; _ssSetConstBlockIO ( S , &
OCF_DCM_Test_rtInvariant ) ; rt_InitInfAndNaN ( sizeof ( real_T ) ) ; }
static void mdlInitializeSampleTimes ( SimStruct * S ) { { SimStruct * childS
; SysOutputFcn * callSysFcns ; childS = ssGetSFunction ( S , 0 ) ;
callSysFcns = ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ]
= ( SysOutputFcn ) ( NULL ) ; } slAccRegPrmChangeFcn ( S , mdlOutputsTID3 ) ;
} static void mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"
