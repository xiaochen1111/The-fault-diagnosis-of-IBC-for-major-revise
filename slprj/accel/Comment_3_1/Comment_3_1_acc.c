#include "__cf_Comment_3_1.h"
#include <math.h>
#include "Comment_3_1_acc.h"
#include "Comment_3_1_acc_private.h"
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
boolean_T Comment_3_1_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T * bufSzPtr ,
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
return ( true ) ; } real_T Comment_3_1_acc_rt_TDelayInterpolate ( real_T
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
void Comment_3_1_SampleIL1_Init ( SimStruct * S , B_SampleIL1_Comment_3_1_T *
localB , P_SampleIL1_Comment_3_1_T * localP ) { localB -> B_0_0_0 = localP ->
P_0 ; } void Comment_3_1_SampleIL1 ( SimStruct * S , boolean_T rtu_Trigger ,
real_T rtu_In , B_SampleIL1_Comment_3_1_T * localB ,
DW_SampleIL1_Comment_3_1_T * localDW , ZCE_SampleIL1_Comment_3_1_T * localZCE
) { if ( ssIsMajorTimeStep ( S ) != 0 ) { if ( rtu_Trigger && ( localZCE ->
SampleIL1_Trig_ZCE != POS_ZCSIG ) ) { localB -> B_0_0_0 = rtu_In ; localDW ->
SampleIL1_SubsysRanBC = 4 ; } localZCE -> SampleIL1_Trig_ZCE = rtu_Trigger ;
} } void Comment_3_1_SampleIL1_Term ( SimStruct * const S ) { } static void
mdlOutputs ( SimStruct * S , int_T tid ) { real_T * lastU ; real_T lastTime ;
real_T rtb_B_5_28_0 ; boolean_T rtb_B_5_65_0 ; boolean_T rtb_B_5_64_0 ;
boolean_T rtb_B_5_63_0 ; int32_T isHit ; B_Comment_3_1_T * _rtB ;
P_Comment_3_1_T * _rtP ; X_Comment_3_1_T * _rtX ; PrevZCX_Comment_3_1_T *
_rtZCE ; DW_Comment_3_1_T * _rtDW ; _rtDW = ( ( DW_Comment_3_1_T * )
ssGetRootDWork ( S ) ) ; _rtZCE = ( ( PrevZCX_Comment_3_1_T * )
_ssGetPrevZCSigState ( S ) ) ; _rtX = ( ( X_Comment_3_1_T * ) ssGetContStates
( S ) ) ; _rtP = ( ( P_Comment_3_1_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_Comment_3_1_T * ) _ssGetModelBlockIO ( S ) ) ; _rtB -> B_5_1_0 = rt_Lookup
( _rtP -> P_6 , 6 , ssGetT ( S ) , _rtP -> P_7 ) ; _rtB -> B_5_3_0 =
rt_Lookup ( _rtP -> P_8 , 8 , ssGetT ( S ) , _rtP -> P_9 ) ; if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Abs_MODE = ( _rtB -> B_5_3_0 >= 0.0
) ; } _rtB -> B_5_4_0 = _rtDW -> Abs_MODE > 0 ? _rtB -> B_5_3_0 : - _rtB ->
B_5_3_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if ( _rtB
-> B_5_3_0 > 0.0 ) { _rtDW -> Sign_MODE = 1 ; } else if ( _rtB -> B_5_3_0 <
0.0 ) { _rtDW -> Sign_MODE = - 1 ; } else { _rtDW -> Sign_MODE = 0 ; } if (
_rtDW -> Sign_MODE > _rtP -> P_10 ) { _rtB -> B_5_6_0 = _rtB -> B_5_9_0_p ; }
else { _rtB -> B_5_6_0 = _rtB -> B_5_10_0_c ; } } if ( ssIsMajorTimeStep ( S
) != 0 ) { _rtDW -> Switch_Mode = ( _rtB -> B_5_4_0 > _rtP -> P_11 ) ; } if (
_rtDW -> Switch_Mode ) { lastTime = _rtB -> B_5_3_0 ; } else { lastTime =
_rtB -> B_5_6_0 ; } _rtB -> B_5_8_0 = _rtB -> B_5_8_0_b / lastTime ; isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_5_9_0 = _rtDW ->
UnitDelay_DSTATE ; } _rtB -> B_5_10_0 = _rtB -> B_5_8_0 - _rtB -> B_5_9_0 ;
isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock
( S , 5 , 11 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_5_12_0 = _rtP -> P_61 * _rtB
-> B_5_11_0 [ 16 ] ; ssCallAccelRunBlock ( S , 5 , 13 , SS_CALL_MDL_OUTPUTS )
; _rtB -> B_5_14_0 = _rtP -> P_62 * _rtB -> B_5_11_0 [ 17 ] ;
ssCallAccelRunBlock ( S , 5 , 15 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_5_16_0 =
_rtP -> P_63 * _rtB -> B_5_11_0 [ 15 ] ; ssCallAccelRunBlock ( S , 5 , 17 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 5 , 18 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_5_19_0 = _rtP -> P_64 * _rtB -> B_5_11_0 [
9 ] ; } _rtB -> B_5_24_0 = look1_binlxpw ( muDoubleScalarRem ( ssGetT ( S ) -
_rtB -> B_5_21_0 , _rtB -> B_5_3_0_c ) , _rtP -> P_66 , _rtP -> P_65 , 2U ) ;
_rtB -> B_5_25_0 = _rtB -> B_5_2_0 - _rtB -> B_5_24_0 ; isHit = ssIsSampleHit
( S , 1 , 0 ) ; if ( isHit != 0 ) { if ( ssIsMajorTimeStep ( S ) != 0 ) {
_rtDW -> Compare_Mode = ( _rtB -> B_5_25_0 <= Comment_3_1_rtC ( S ) ->
B_5_3_0 ) ; } _rtB -> B_5_26_0 = _rtDW -> Compare_Mode ;
Comment_3_1_SampleIL1 ( S , _rtB -> B_5_26_0 , _rtB -> B_5_19_0 , & _rtB ->
SampleIL4 , & _rtDW -> SampleIL4 , & _rtZCE -> SampleIL4 ) ; rtb_B_5_28_0 =
_rtB -> B_5_1_0_m - _rtB -> SampleIL4 . B_0_0_0 ; _rtB -> B_5_29_0 = _rtP ->
P_67 * rtb_B_5_28_0 ; } _rtB -> B_5_30_0 = _rtX -> Integrator_CSTATE ; _rtB
-> B_5_31_0 = _rtB -> B_5_29_0 + _rtB -> B_5_30_0 ; isHit = ssIsSampleHit ( S
, 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_5_32_0 = _rtP -> P_69 * _rtB ->
B_5_11_0 [ 11 ] ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
Comment_3_1_SampleIL1 ( S , _rtB -> B_5_26_0 , _rtB -> B_5_32_0 , & _rtB ->
SampleIL1 , & _rtDW -> SampleIL1 , & _rtZCE -> SampleIL1 ) ; } _rtB ->
B_5_34_0 = _rtB -> B_5_31_0 - _rtB -> SampleIL1 . B_0_0_0 ; _rtB -> B_5_36_0
= _rtX -> Integrator_CSTATE_f ; _rtB -> B_5_37_0 = _rtP -> P_70 * _rtB ->
B_5_34_0 + _rtB -> B_5_36_0 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW ->
Saturation_MODE = _rtB -> B_5_37_0 >= _rtP -> P_72 ? 1 : _rtB -> B_5_37_0 >
_rtP -> P_73 ? 0 : - 1 ; } _rtB -> B_5_38_0 = _rtDW -> Saturation_MODE == 1 ?
_rtP -> P_72 : _rtDW -> Saturation_MODE == - 1 ? _rtP -> P_73 : _rtB ->
B_5_37_0 ; ssCallAccelRunBlock ( S , 5 , 39 , SS_CALL_MDL_OUTPUTS ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { Comment_3_1_SampleIL1 ( S ,
_rtB -> B_5_26_0 , _rtB -> B_5_32_0 , & _rtB -> SampleandHold1 , & _rtDW ->
SampleandHold1 , & _rtZCE -> SampleandHold1 ) ; } { real_T * * uBuffer = (
real_T * * ) & _rtDW -> TransportDelay1_PWORK . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK . TUbufferPtrs [
1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP ->
P_74 ; _rtB -> B_5_41_0 = Comment_3_1_acc_rt_TDelayInterpolate ( tMinusDelay
, 0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay1_IWORK .
CircularBufSize , & _rtDW -> TransportDelay1_IWORK . Last , _rtDW ->
TransportDelay1_IWORK . Tail , _rtDW -> TransportDelay1_IWORK . Head , _rtP
-> P_75 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } _rtB -> B_5_42_0 = _rtB
-> B_5_2_0 - _rtB -> B_5_41_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if (
isHit != 0 ) { if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Compare_Mode_n
= ( _rtB -> B_5_42_0 <= Comment_3_1_rtC ( S ) -> B_5_4_0 ) ; } _rtB ->
B_5_43_0 = _rtDW -> Compare_Mode_n ; Comment_3_1_SampleIL1 ( S , _rtB ->
B_5_43_0 , _rtB -> B_5_32_0 , & _rtB -> SampleIL2 , & _rtDW -> SampleIL2 , &
_rtZCE -> SampleIL2 ) ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay2_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay2_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_76 ; _rtB -> B_5_45_0
= Comment_3_1_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay2_IWORK . CircularBufSize , & _rtDW ->
TransportDelay2_IWORK . Last , _rtDW -> TransportDelay2_IWORK . Tail , _rtDW
-> TransportDelay2_IWORK . Head , _rtP -> P_77 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } _rtB -> B_5_46_0 = _rtB -> B_5_2_0 - _rtB -> B_5_45_0 ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if ( ssIsMajorTimeStep ( S
) != 0 ) { _rtDW -> Compare_Mode_i = ( _rtB -> B_5_46_0 <= Comment_3_1_rtC (
S ) -> B_5_5_0 ) ; } _rtB -> B_5_47_0 = _rtDW -> Compare_Mode_i ;
Comment_3_1_SampleIL1 ( S , _rtB -> B_5_47_0 , _rtB -> B_5_32_0 , & _rtB ->
SampleIL3 , & _rtDW -> SampleIL3 , & _rtZCE -> SampleIL3 ) ;
ssCallAccelRunBlock ( S , 5 , 49 , SS_CALL_MDL_OUTPUTS ) ; } _rtB -> B_5_50_0
= _rtP -> P_78 * _rtB -> B_5_45_0 ; ssCallAccelRunBlock ( S , 5 , 51 ,
SS_CALL_MDL_OUTPUTS ) ; isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0
) { ssCallAccelRunBlock ( S , 5 , 52 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 5 , 53 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 5 , 54 , SS_CALL_MDL_OUTPUTS ) ; }
ssCallAccelRunBlock ( S , 5 , 55 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 5 , 56 , SS_CALL_MDL_OUTPUTS ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if ( ssIsMajorTimeStep ( S
) != 0 ) { _rtDW -> Compare_Mode_f = ( _rtB -> B_5_24_0 == Comment_3_1_rtC (
S ) -> B_5_0_0 ) ; _rtDW -> Compare_Mode_a = ( _rtB -> B_5_41_0 ==
Comment_3_1_rtC ( S ) -> B_5_1_0 ) ; } _rtB -> B_5_57_0 = _rtDW ->
Compare_Mode_f ; _rtB -> B_5_58_0 = _rtDW -> Compare_Mode_a ; if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Compare_Mode_m = ( _rtB -> B_5_45_0
== Comment_3_1_rtC ( S ) -> B_5_2_0 ) ; } _rtB -> B_5_59_0 = _rtDW ->
Compare_Mode_m ; ssCallAccelRunBlock ( S , 5 , 60 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 5 , 61 , SS_CALL_MDL_OUTPUTS ) ; }
ssCallAccelRunBlock ( S , 5 , 62 , SS_CALL_MDL_OUTPUTS ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if ( ssIsMajorTimeStep ( S
) != 0 ) { _rtDW -> RelationalOperator_Mode = ( _rtB -> B_5_38_0 > _rtB ->
B_5_24_0 ) ; _rtDW -> RelationalOperator1_Mode = ( _rtB -> B_5_38_0 > _rtB ->
B_5_41_0 ) ; } rtb_B_5_63_0 = _rtDW -> RelationalOperator_Mode ; rtb_B_5_64_0
= _rtDW -> RelationalOperator1_Mode ; if ( ssIsMajorTimeStep ( S ) != 0 ) {
_rtDW -> RelationalOperator2_Mode = ( _rtB -> B_5_38_0 > _rtB -> B_5_45_0 ) ;
} rtb_B_5_65_0 = _rtDW -> RelationalOperator2_Mode ; } _rtB -> B_5_70_0 =
look1_binlxpw ( muDoubleScalarRem ( ssGetT ( S ) - _rtB -> B_5_67_0 , _rtB ->
B_5_4_0_k ) , _rtP -> P_80 , _rtP -> P_79 , 2U ) ; _rtB -> B_5_75_0 =
look1_binlxpw ( muDoubleScalarRem ( ssGetT ( S ) - _rtB -> B_5_72_0 , _rtB ->
B_5_5_0 ) , _rtP -> P_82 , _rtP -> P_81 , 2U ) ; { real_T * * uBuffer = (
real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 1
] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP ->
P_83 ; _rtB -> B_5_76_0 = Comment_3_1_acc_rt_TDelayInterpolate ( tMinusDelay
, 0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK .
CircularBufSize , & _rtDW -> TransportDelay_IWORK . Last , _rtDW ->
TransportDelay_IWORK . Tail , _rtDW -> TransportDelay_IWORK . Head , _rtP ->
P_84 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput
( S ) == ssGetT ( S ) ) ) ) ; } _rtB -> B_5_81_0 = look1_binlxpw (
muDoubleScalarRem ( ssGetT ( S ) - _rtB -> B_5_78_0 , _rtB -> B_5_6_0_c ) ,
_rtP -> P_86 , _rtP -> P_85 , 2U ) ; ssCallAccelRunBlock ( S , 5 , 82 ,
SS_CALL_MDL_OUTPUTS ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0
) { _rtB -> B_5_98_0 = rtb_B_5_63_0 ; _rtB -> B_5_108_0 = rtb_B_5_64_0 ;
_rtDW -> Step_MODE = ( ssGetTaskTime ( S , 1 ) >= _rtP -> P_87 ) ; if ( _rtDW
-> Step_MODE == 1 ) { lastTime = _rtP -> P_89 ; } else { lastTime = _rtP ->
P_88 ; } if ( lastTime > _rtP -> P_90 ) { _rtB -> B_5_128_0 = rtb_B_5_65_0 ;
} else { _rtB -> B_5_128_0 = _rtB -> B_5_7_0 ; } } if ( ( _rtDW -> TimeStampA
>= ssGetT ( S ) ) && ( _rtDW -> TimeStampB >= ssGetT ( S ) ) ) { _rtB ->
B_5_132_0 = 0.0 ; } else { lastTime = _rtDW -> TimeStampA ; lastU = & _rtDW
-> LastUAtTimeA ; if ( _rtDW -> TimeStampA < _rtDW -> TimeStampB ) { if (
_rtDW -> TimeStampB < ssGetT ( S ) ) { lastTime = _rtDW -> TimeStampB ; lastU
= & _rtDW -> LastUAtTimeB ; } } else { if ( _rtDW -> TimeStampA >= ssGetT ( S
) ) { lastTime = _rtDW -> TimeStampB ; lastU = & _rtDW -> LastUAtTimeB ; } }
_rtB -> B_5_132_0 = ( _rtB -> B_5_1_0 - * lastU ) / ( ssGetT ( S ) - lastTime
) ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB ->
B_5_134_0 = _rtP -> P_92 * _rtB -> B_5_11_0 [ 13 ] ; _rtB -> B_5_135_0 = _rtP
-> P_93 * _rtB -> B_5_11_0 [ 12 ] ; _rtB -> B_5_136_0 = _rtP -> P_94 * _rtB
-> B_5_11_0 [ 10 ] ; _rtB -> B_5_137_0 = _rtP -> P_95 * _rtB -> B_5_11_0 [ 14
] ; ssCallAccelRunBlock ( S , 5 , 138 , SS_CALL_MDL_OUTPUTS ) ; } if ( (
_rtDW -> TimeStampA_c >= ssGetT ( S ) ) && ( _rtDW -> TimeStampB_p >= ssGetT
( S ) ) ) { _rtB -> B_5_159_0 = 0.0 ; } else { lastTime = _rtDW ->
TimeStampA_c ; lastU = & _rtDW -> LastUAtTimeA_f ; if ( _rtDW -> TimeStampA_c
< _rtDW -> TimeStampB_p ) { if ( _rtDW -> TimeStampB_p < ssGetT ( S ) ) {
lastTime = _rtDW -> TimeStampB_p ; lastU = & _rtDW -> LastUAtTimeB_k ; } }
else { if ( _rtDW -> TimeStampA_c >= ssGetT ( S ) ) { lastTime = _rtDW ->
TimeStampB_p ; lastU = & _rtDW -> LastUAtTimeB_k ; } } _rtB -> B_5_159_0 = (
_rtB -> B_5_3_0 - * lastU ) / ( ssGetT ( S ) - lastTime ) ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW -> Step2_MODE = (
ssGetTaskTime ( S , 1 ) >= _rtP -> P_97 ) ; ssCallAccelRunBlock ( S , 5 , 180
, SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 5 , 181 ,
SS_CALL_MDL_OUTPUTS ) ; } _rtB -> B_5_182_0 = _rtP -> P_100 * _rtB ->
B_5_34_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB ->
B_5_183_0 = _rtP -> P_101 * rtb_B_5_28_0 ; } _rtB -> B_5_185_0 = rt_Lookup (
_rtP -> P_102 , 8 , ssGetT ( S ) , _rtP -> P_103 ) ; if ( ( _rtDW ->
TimeStampA_b >= ssGetT ( S ) ) && ( _rtDW -> TimeStampB_pj >= ssGetT ( S ) )
) { _rtB -> B_5_186_0 = 0.0 ; } else { lastTime = _rtDW -> TimeStampA_b ;
lastU = & _rtDW -> LastUAtTimeA_fk ; if ( _rtDW -> TimeStampA_b < _rtDW ->
TimeStampB_pj ) { if ( _rtDW -> TimeStampB_pj < ssGetT ( S ) ) { lastTime =
_rtDW -> TimeStampB_pj ; lastU = & _rtDW -> LastUAtTimeB_e ; } } else { if (
_rtDW -> TimeStampA_b >= ssGetT ( S ) ) { lastTime = _rtDW -> TimeStampB_pj ;
lastU = & _rtDW -> LastUAtTimeB_e ; } } _rtB -> B_5_186_0 = ( _rtB ->
B_5_185_0 - * lastU ) / ( ssGetT ( S ) - lastTime ) ; } UNUSED_PARAMETER (
tid ) ; } static void mdlOutputsTID3 ( SimStruct * S , int_T tid ) {
B_Comment_3_1_T * _rtB ; P_Comment_3_1_T * _rtP ; _rtP = ( ( P_Comment_3_1_T
* ) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_Comment_3_1_T * ) _ssGetModelBlockIO
( S ) ) ; memcpy ( & _rtB -> B_5_0_0 [ 0 ] , & _rtP -> P_105 [ 0 ] , 9U *
sizeof ( real_T ) ) ; _rtB -> B_5_1_0_m = _rtP -> P_106 ; _rtB -> B_5_2_0 =
_rtP -> P_107 ; _rtB -> B_5_3_0_c = _rtP -> P_108 ; _rtB -> B_5_4_0_k = _rtP
-> P_109 ; _rtB -> B_5_5_0 = _rtP -> P_110 ; _rtB -> B_5_6_0_c = _rtP ->
P_111 ; _rtB -> B_5_7_0 = _rtP -> P_112 ; _rtB -> B_5_8_0_b = _rtP -> P_113 ;
_rtB -> B_5_9_0_p = _rtP -> P_114 ; _rtB -> B_5_10_0_c = _rtP -> P_115 ;
UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { real_T * lastU ;
int32_T isHit ; B_Comment_3_1_T * _rtB ; P_Comment_3_1_T * _rtP ;
DW_Comment_3_1_T * _rtDW ; _rtDW = ( ( DW_Comment_3_1_T * ) ssGetRootDWork (
S ) ) ; _rtP = ( ( P_Comment_3_1_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_Comment_3_1_T * ) _ssGetModelBlockIO ( S ) ) ; isHit = ssIsSampleHit ( S ,
2 , 0 ) ; if ( isHit != 0 ) { _rtDW -> UnitDelay_DSTATE = _rtB -> B_5_8_0 ;
ssCallAccelRunBlock ( S , 5 , 11 , SS_CALL_MDL_UPDATE ) ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay1_IWORK . Head = ( ( _rtDW -> TransportDelay1_IWORK . Head < (
_rtDW -> TransportDelay1_IWORK . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay1_IWORK . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay1_IWORK . Head == _rtDW -> TransportDelay1_IWORK . Tail ) { if
( ! Comment_3_1_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay1_IWORK . CircularBufSize , & _rtDW -> TransportDelay1_IWORK .
Tail , & _rtDW -> TransportDelay1_IWORK . Head , & _rtDW ->
TransportDelay1_IWORK . Last , simTime - _rtP -> P_74 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay1_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay1_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay1_IWORK . Head ] = _rtB ->
B_5_70_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay2_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay2_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay2_IWORK . Head = ( ( _rtDW ->
TransportDelay2_IWORK . Head < ( _rtDW -> TransportDelay2_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay2_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay2_IWORK . Head == _rtDW ->
TransportDelay2_IWORK . Tail ) { if ( !
Comment_3_1_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay2_IWORK . CircularBufSize , & _rtDW -> TransportDelay2_IWORK .
Tail , & _rtDW -> TransportDelay2_IWORK . Head , & _rtDW ->
TransportDelay2_IWORK . Last , simTime - _rtP -> P_76 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay2_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay2_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay2_IWORK . Head ] = _rtB ->
B_5_75_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * *
) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK . Head = ( ( _rtDW ->
TransportDelay_IWORK . Head < ( _rtDW -> TransportDelay_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay_IWORK . Head == _rtDW -> TransportDelay_IWORK
. Tail ) { if ( ! Comment_3_1_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK . CircularBufSize , & _rtDW -> TransportDelay_IWORK .
Tail , & _rtDW -> TransportDelay_IWORK . Head , & _rtDW ->
TransportDelay_IWORK . Last , simTime - _rtP -> P_83 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] = _rtB ->
B_5_81_0 ; } if ( _rtDW -> TimeStampA == ( rtInf ) ) { _rtDW -> TimeStampA =
ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA ; } else if ( _rtDW ->
TimeStampB == ( rtInf ) ) { _rtDW -> TimeStampB = ssGetT ( S ) ; lastU = &
_rtDW -> LastUAtTimeB ; } else if ( _rtDW -> TimeStampA < _rtDW -> TimeStampB
) { _rtDW -> TimeStampA = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA ; }
else { _rtDW -> TimeStampB = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB ;
} * lastU = _rtB -> B_5_1_0 ; if ( _rtDW -> TimeStampA_c == ( rtInf ) ) {
_rtDW -> TimeStampA_c = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA_f ; }
else if ( _rtDW -> TimeStampB_p == ( rtInf ) ) { _rtDW -> TimeStampB_p =
ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB_k ; } else if ( _rtDW ->
TimeStampA_c < _rtDW -> TimeStampB_p ) { _rtDW -> TimeStampA_c = ssGetT ( S )
; lastU = & _rtDW -> LastUAtTimeA_f ; } else { _rtDW -> TimeStampB_p = ssGetT
( S ) ; lastU = & _rtDW -> LastUAtTimeB_k ; } * lastU = _rtB -> B_5_3_0 ; if
( _rtDW -> TimeStampA_b == ( rtInf ) ) { _rtDW -> TimeStampA_b = ssGetT ( S )
; lastU = & _rtDW -> LastUAtTimeA_fk ; } else if ( _rtDW -> TimeStampB_pj ==
( rtInf ) ) { _rtDW -> TimeStampB_pj = ssGetT ( S ) ; lastU = & _rtDW ->
LastUAtTimeB_e ; } else if ( _rtDW -> TimeStampA_b < _rtDW -> TimeStampB_pj )
{ _rtDW -> TimeStampA_b = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA_fk ;
} else { _rtDW -> TimeStampB_pj = ssGetT ( S ) ; lastU = & _rtDW ->
LastUAtTimeB_e ; } * lastU = _rtB -> B_5_185_0 ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdateTID3 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { B_Comment_3_1_T * _rtB ;
XDot_Comment_3_1_T * _rtXdot ; _rtXdot = ( ( XDot_Comment_3_1_T * ) ssGetdX (
S ) ) ; _rtB = ( ( B_Comment_3_1_T * ) _ssGetModelBlockIO ( S ) ) ; _rtXdot
-> Integrator_CSTATE = _rtB -> B_5_183_0 ; _rtXdot -> Integrator_CSTATE_f =
_rtB -> B_5_182_0 ; }
#define MDL_ZERO_CROSSINGS
static void mdlZeroCrossings ( SimStruct * S ) { B_Comment_3_1_T * _rtB ;
P_Comment_3_1_T * _rtP ; ZCV_Comment_3_1_T * _rtZCSV ; _rtZCSV = ( (
ZCV_Comment_3_1_T * ) ssGetSolverZcSignalVector ( S ) ) ; _rtP = ( (
P_Comment_3_1_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_Comment_3_1_T * )
_ssGetModelBlockIO ( S ) ) ; _rtZCSV -> Abs_AbsZc_ZC = _rtB -> B_5_3_0 ;
_rtZCSV -> Sign_Input_ZC = _rtB -> B_5_3_0 ; _rtZCSV -> Switch_SwitchCond_ZC
= _rtB -> B_5_4_0 - _rtP -> P_11 ; _rtZCSV -> Compare_RelopInput_ZC = _rtB ->
B_5_25_0 - Comment_3_1_rtC ( S ) -> B_5_3_0 ; _rtZCSV -> Saturation_UprLim_ZC
= _rtB -> B_5_37_0 - _rtP -> P_72 ; _rtZCSV -> Saturation_LwrLim_ZC = _rtB ->
B_5_37_0 - _rtP -> P_73 ; _rtZCSV -> Compare_RelopInput_ZC_i = _rtB ->
B_5_42_0 - Comment_3_1_rtC ( S ) -> B_5_4_0 ; _rtZCSV ->
Compare_RelopInput_ZC_e = _rtB -> B_5_46_0 - Comment_3_1_rtC ( S ) -> B_5_5_0
; _rtZCSV -> Compare_RelopInput_ZC_ia = _rtB -> B_5_24_0 - Comment_3_1_rtC (
S ) -> B_5_0_0 ; _rtZCSV -> Compare_RelopInput_ZC_l = _rtB -> B_5_41_0 -
Comment_3_1_rtC ( S ) -> B_5_1_0 ; _rtZCSV -> Compare_RelopInput_ZC_a = _rtB
-> B_5_45_0 - Comment_3_1_rtC ( S ) -> B_5_2_0 ; _rtZCSV ->
RelationalOperator_RelopInput_ZC = _rtB -> B_5_38_0 - _rtB -> B_5_24_0 ;
_rtZCSV -> RelationalOperator1_RelopInput_ZC = _rtB -> B_5_38_0 - _rtB ->
B_5_41_0 ; _rtZCSV -> RelationalOperator2_RelopInput_ZC = _rtB -> B_5_38_0 -
_rtB -> B_5_45_0 ; _rtZCSV -> Step_StepTime_ZC = ssGetT ( S ) - _rtP -> P_87
; _rtZCSV -> HitCrossing_HitNoOutput_ZC = _rtB -> B_5_132_0 - _rtP -> P_91 ;
_rtZCSV -> HitCrossing_HitNoOutput_ZC_i = _rtB -> B_5_159_0 - _rtP -> P_96 ;
_rtZCSV -> Step2_StepTime_ZC = ssGetT ( S ) - _rtP -> P_97 ; _rtZCSV ->
HitCrossing_HitNoOutput_ZC_l = _rtB -> B_5_186_0 - _rtP -> P_104 ; } static
void mdlInitializeSizes ( SimStruct * S ) { ssSetChecksumVal ( S , 0 ,
3599780425U ) ; ssSetChecksumVal ( S , 1 , 1893428137U ) ; ssSetChecksumVal (
S , 2 , 596902360U ) ; ssSetChecksumVal ( S , 3 , 3458970565U ) ; { mxArray *
slVerStructMat = NULL ; mxArray * slStrMat = mxCreateString ( "simulink" ) ;
char slVerChar [ 10 ] ; int status = mexCallMATLAB ( 1 , & slVerStructMat , 1
, & slStrMat , "ver" ) ; if ( status == 0 ) { mxArray * slVerMat = mxGetField
( slVerStructMat , 0 , "Version" ) ; if ( slVerMat == NULL ) { status = 1 ; }
else { status = mxGetString ( slVerMat , slVerChar , 10 ) ; } }
mxDestroyArray ( slStrMat ) ; mxDestroyArray ( slVerStructMat ) ; if ( (
status == 1 ) || ( strcmp ( slVerChar , "10.0" ) != 0 ) ) { return ; } }
ssSetOptions ( S , SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork (
S ) != sizeof ( DW_Comment_3_1_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( B_Comment_3_1_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofY ( S ) != sizeof
( ExtY_Comment_3_1_T ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal ExternalOutputs sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
P_Comment_3_1_T ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetModelRtp ( S , ( real_T *
) & Comment_3_1_rtDefaultP ) ; _ssSetConstBlockIO ( S , &
Comment_3_1_rtInvariant ) ; rt_InitInfAndNaN ( sizeof ( real_T ) ) ; } static
void mdlInitializeSampleTimes ( SimStruct * S ) { slAccRegPrmChangeFcn ( S ,
mdlOutputsTID3 ) ; } static void mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"
