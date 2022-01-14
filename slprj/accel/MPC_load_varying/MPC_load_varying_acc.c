#include "__cf_MPC_load_varying.h"
#include <math.h>
#include "MPC_load_varying_acc.h"
#include "MPC_load_varying_acc_private.h"
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
boolean_T MPC_load_varying_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T *
bufSzPtr , int_T * tailPtr , int_T * headPtr , int_T * lastPtr , real_T
tMinusDelay , real_T * * tBufPtr , real_T * * uBufPtr , real_T * * xBufPtr ,
boolean_T isfixedbuf , boolean_T istransportdelay , int_T * maxNewBufSzPtr )
{ int_T testIdx ; int_T tail = * tailPtr ; int_T bufSz = * bufSzPtr ; real_T
* tBuf = * tBufPtr ; real_T * xBuf = ( NULL ) ; int_T numBuffer = 2 ; if (
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
return ( true ) ; } real_T MPC_load_varying_acc_rt_TDelayInterpolate ( real_T
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
void MPC_load_varying_SampleIL1_Init ( SimStruct * S ,
B_SampleIL1_MPC_load_varying_T * localB , P_SampleIL1_MPC_load_varying_T *
localP ) { localB -> B_1_0_0 = localP -> P_0 ; } void
MPC_load_varying_SampleIL1 ( SimStruct * S , boolean_T rtu_Trigger , real_T
rtu_In , B_SampleIL1_MPC_load_varying_T * localB ,
DW_SampleIL1_MPC_load_varying_T * localDW , ZCE_SampleIL1_MPC_load_varying_T
* localZCE ) { if ( ssIsMajorTimeStep ( S ) != 0 ) { if ( ( ! rtu_Trigger )
&& ( localZCE -> SampleIL1_Trig_ZCE != ZERO_ZCSIG ) ) { localB -> B_1_0_0 =
rtu_In ; localDW -> SampleIL1_SubsysRanBC = 4 ; } localZCE ->
SampleIL1_Trig_ZCE = rtu_Trigger ; } } void MPC_load_varying_SampleIL1_Term (
SimStruct * const S ) { } static void mdlOutputs ( SimStruct * S , int_T tid
) { real_T * lastU ; real_T rtb_B_6_13_0 ; real_T rtb_B_6_2_0 ; int32_T isHit
; B_MPC_load_varying_T * _rtB ; P_MPC_load_varying_T * _rtP ;
X_MPC_load_varying_T * _rtX ; PrevZCX_MPC_load_varying_T * _rtZCE ;
DW_MPC_load_varying_T * _rtDW ; _rtDW = ( ( DW_MPC_load_varying_T * )
ssGetRootDWork ( S ) ) ; _rtZCE = ( ( PrevZCX_MPC_load_varying_T * )
_ssGetPrevZCSigState ( S ) ) ; _rtX = ( ( X_MPC_load_varying_T * )
ssGetContStates ( S ) ) ; _rtP = ( ( P_MPC_load_varying_T * ) ssGetModelRtp (
S ) ) ; _rtB = ( ( B_MPC_load_varying_T * ) _ssGetModelBlockIO ( S ) ) ; _rtB
-> B_6_1_0 = rt_Lookup ( _rtP -> P_7 , 6 , ssGetT ( S ) , _rtP -> P_8 ) ;
isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW -> Step2_MODE
= ( ssGetTaskTime ( S , 1 ) >= _rtP -> P_9 ) ; if ( _rtDW -> Step2_MODE == 1
) { rtb_B_6_2_0 = _rtP -> P_11 ; } else { rtb_B_6_2_0 = _rtP -> P_10 ; } if (
! ( muDoubleScalarAbs ( rtb_B_6_2_0 ) > _rtP -> P_12 ) ) { if (
muDoubleScalarSign ( rtb_B_6_2_0 ) > _rtP -> P_0 ) { rtb_B_6_2_0 = _rtB ->
B_6_11_0_c ; } else { rtb_B_6_2_0 = _rtB -> B_6_12_0_f ; } } _rtB -> B_6_6_0
= _rtB -> B_6_10_0_p / rtb_B_6_2_0 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ;
if ( isHit != 0 ) { _rtB -> B_6_7_0 = _rtDW -> UnitDelay_DSTATE ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_6_8_0 = _rtB ->
B_6_6_0 - _rtB -> B_6_7_0 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if (
isHit != 0 ) { ssCallAccelRunBlock ( S , 6 , 9 , SS_CALL_MDL_OUTPUTS ) ; _rtB
-> B_6_10_0 = _rtP -> P_62 * _rtB -> B_6_9_0 [ 9 ] ; _rtB -> B_6_11_0 = _rtP
-> P_63 * _rtB -> B_6_9_0 [ 18 ] ; _rtB -> B_6_12_0 = _rtB -> B_6_19_0 * _rtB
-> B_6_10_0 * _rtB -> B_6_11_0 ; rtb_B_6_13_0 = _rtB -> B_6_1_0_m - _rtB ->
B_6_10_0 ; _rtB -> B_6_14_0 = _rtP -> P_64 * rtb_B_6_13_0 ; } _rtB ->
B_6_15_0 = _rtX -> Integrator_CSTATE ; _rtB -> B_6_16_0 = _rtB -> B_6_14_0 +
_rtB -> B_6_15_0 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW ->
Saturation_MODE = _rtB -> B_6_16_0 >= _rtP -> P_66 ? 1 : _rtB -> B_6_16_0 >
_rtP -> P_67 ? 0 : - 1 ; } _rtB -> B_6_18_0 = ( _rtDW -> Saturation_MODE == 1
? _rtP -> P_66 : _rtDW -> Saturation_MODE == - 1 ? _rtP -> P_67 : _rtB ->
B_6_16_0 ) / _rtB -> B_6_28_0_n ; isHit = ssIsSampleHit ( S , 2 , 0 ) ; if (
isHit != 0 ) { _rtB -> B_6_20_0 = _rtB -> B_6_21_0 * _rtB -> B_6_11_0 * _rtB
-> B_6_1_0_m ; _rtB -> B_6_22_0 = _rtB -> B_6_23_0 * _rtB -> B_6_10_0 * (
_rtP -> P_68 * _rtB -> B_6_9_0 [ 10 ] ) ; } isHit = ssIsSampleHit ( S , 2 , 0
) ; if ( isHit != 0 ) { _rtB -> B_6_25_0 = _rtB -> B_6_10_0 * _rtB ->
B_6_10_0 * _rtB -> B_6_14_0_g * _rtB -> B_6_27_0_m ; } _rtB -> B_6_27_0 = ( (
( _rtB -> B_6_25_0_g * _rtB -> B_6_10_0 * _rtB -> B_6_18_0 + _rtB -> B_6_12_0
) - _rtB -> B_6_20_0 ) - _rtB -> B_6_22_0 ) / _rtB -> B_6_25_0 + _rtB ->
B_6_26_0 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Saturation_MODE_o =
_rtB -> B_6_27_0 >= _rtP -> P_69 ? 1 : _rtB -> B_6_27_0 > _rtP -> P_70 ? 0 :
- 1 ; } _rtB -> B_6_28_0 = _rtDW -> Saturation_MODE_o == 1 ? _rtP -> P_69 :
_rtDW -> Saturation_MODE_o == - 1 ? _rtP -> P_70 : _rtB -> B_6_27_0 ;
ssCallAccelRunBlock ( S , 6 , 29 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 6 , 30 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 6 , 31 , SS_CALL_MDL_OUTPUTS ) ; isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_6_32_0 = _rtP ->
P_71 * _rtB -> B_6_9_0 [ 11 ] ; _rtB -> B_6_33_0 = _rtP -> P_72 * _rtB ->
B_6_9_0 [ 12 ] ; _rtB -> B_6_34_0 = _rtP -> P_73 * _rtB -> B_6_9_0 [ 13 ] ;
ssCallAccelRunBlock ( S , 6 , 35 , SS_CALL_MDL_OUTPUTS ) ; } _rtB -> B_6_36_0
= _rtP -> P_74 * _rtB -> B_6_28_0 ; _rtB -> B_6_41_0 = look1_binlxpw (
muDoubleScalarRem ( ssGetT ( S ) - _rtB -> B_6_38_0 , _rtB -> B_6_5_0 ) ,
_rtP -> P_76 , _rtP -> P_75 , 2U ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if
( isHit != 0 ) { if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW ->
RelationalOperator_Mode = ( _rtB -> B_6_36_0 > _rtB -> B_6_41_0 ) ; } _rtB ->
B_6_42_0 = _rtDW -> RelationalOperator_Mode ; } { real_T * * uBuffer = (
real_T * * ) & _rtDW -> TransportDelay1_PWORK . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK . TUbufferPtrs [
1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP ->
P_77 ; _rtB -> B_6_43_0 = MPC_load_varying_acc_rt_TDelayInterpolate (
tMinusDelay , 0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay1_IWORK .
CircularBufSize , & _rtDW -> TransportDelay1_IWORK . Last , _rtDW ->
TransportDelay1_IWORK . Tail , _rtDW -> TransportDelay1_IWORK . Head , _rtP
-> P_78 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } isHit = ssIsSampleHit (
S , 1 , 0 ) ; if ( isHit != 0 ) { if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW
-> RelationalOperator1_Mode = ( _rtB -> B_6_36_0 > _rtB -> B_6_43_0 ) ; }
_rtB -> B_6_44_0 = _rtDW -> RelationalOperator1_Mode ; } { real_T * * uBuffer
= ( real_T * * ) & _rtDW -> TransportDelay2_PWORK . TUbufferPtrs [ 0 ] ;
real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay2_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_79 ; _rtB -> B_6_45_0 =
MPC_load_varying_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay2_IWORK . CircularBufSize , & _rtDW ->
TransportDelay2_IWORK . Last , _rtDW -> TransportDelay2_IWORK . Tail , _rtDW
-> TransportDelay2_IWORK . Head , _rtP -> P_80 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> RelationalOperator2_Mode = ( _rtB
-> B_6_36_0 > _rtB -> B_6_45_0 ) ; } _rtB -> B_6_46_0 = _rtDW ->
RelationalOperator2_Mode ; } _rtB -> B_6_47_0 = _rtB -> B_6_4_0 - _rtB ->
B_6_41_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { if (
ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Compare_Mode = ( _rtB -> B_6_47_0
<= MPC_load_varying_rtC ( S ) -> B_6_3_0 ) ; } _rtB -> B_6_48_0 = _rtDW ->
Compare_Mode ; ssCallAccelRunBlock ( S , 6 , 49 , SS_CALL_MDL_OUTPUTS ) ; }
ssCallAccelRunBlock ( S , 6 , 50 , SS_CALL_MDL_OUTPUTS ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { MPC_load_varying_SampleIL1
( S , _rtB -> B_6_48_0 , _rtB -> B_6_11_0 , & _rtB -> SampleandHold1 , &
_rtDW -> SampleandHold1 , & _rtZCE -> SampleandHold1 ) ; } _rtB -> B_6_52_0 =
_rtB -> B_6_4_0 - _rtB -> B_6_43_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if
( isHit != 0 ) { if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW ->
Compare_Mode_d = ( _rtB -> B_6_52_0 <= MPC_load_varying_rtC ( S ) -> B_6_4_0
) ; } _rtB -> B_6_53_0 = _rtDW -> Compare_Mode_d ; MPC_load_varying_SampleIL1
( S , _rtB -> B_6_53_0 , _rtB -> B_6_11_0 , & _rtB -> SampleIL2 , & _rtDW ->
SampleIL2 , & _rtZCE -> SampleIL2 ) ; } _rtB -> B_6_55_0 = _rtB -> B_6_4_0 -
_rtB -> B_6_45_0 ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Compare_Mode_b = ( _rtB ->
B_6_55_0 <= MPC_load_varying_rtC ( S ) -> B_6_5_0 ) ; } _rtB -> B_6_56_0 =
_rtDW -> Compare_Mode_b ; MPC_load_varying_SampleIL1 ( S , _rtB -> B_6_56_0 ,
_rtB -> B_6_11_0 , & _rtB -> SampleIL3 , & _rtDW -> SampleIL3 , & _rtZCE ->
SampleIL3 ) ; ssCallAccelRunBlock ( S , 6 , 58 , SS_CALL_MDL_OUTPUTS ) ; }
isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock
( S , 6 , 59 , SS_CALL_MDL_OUTPUTS ) ; } ssCallAccelRunBlock ( S , 6 , 60 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 6 , 61 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 6 , 62 ,
SS_CALL_MDL_OUTPUTS ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0
) { if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW -> Compare_Mode_n = ( _rtB ->
B_6_41_0 == MPC_load_varying_rtC ( S ) -> B_6_0_0 ) ; _rtDW -> Compare_Mode_k
= ( _rtB -> B_6_43_0 == MPC_load_varying_rtC ( S ) -> B_6_1_0 ) ; } _rtB ->
B_6_63_0 = _rtDW -> Compare_Mode_n ; _rtB -> B_6_64_0 = _rtDW ->
Compare_Mode_k ; if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtDW ->
Compare_Mode_f = ( _rtB -> B_6_45_0 == MPC_load_varying_rtC ( S ) -> B_6_2_0
) ; } _rtB -> B_6_65_0 = _rtDW -> Compare_Mode_f ; ssCallAccelRunBlock ( S ,
6 , 66 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 6 , 67 ,
SS_CALL_MDL_OUTPUTS ) ; } ssCallAccelRunBlock ( S , 6 , 68 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_6_73_0 = look1_binlxpw ( muDoubleScalarRem
( ssGetT ( S ) - _rtB -> B_6_70_0 , _rtB -> B_6_6_0_c ) , _rtP -> P_82 , _rtP
-> P_81 , 2U ) ; _rtB -> B_6_78_0 = look1_binlxpw ( muDoubleScalarRem (
ssGetT ( S ) - _rtB -> B_6_75_0 , _rtB -> B_6_7_0_k ) , _rtP -> P_84 , _rtP
-> P_83 , 2U ) ; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * *
) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_85 ; _rtB -> B_6_79_0
= MPC_load_varying_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer ,
* uBuffer , _rtDW -> TransportDelay_IWORK . CircularBufSize , & _rtDW ->
TransportDelay_IWORK . Last , _rtDW -> TransportDelay_IWORK . Tail , _rtDW ->
TransportDelay_IWORK . Head , _rtP -> P_86 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } _rtB -> B_6_84_0 = look1_binlxpw ( muDoubleScalarRem ( ssGetT ( S ) -
_rtB -> B_6_81_0 , _rtB -> B_6_8_0_c ) , _rtP -> P_88 , _rtP -> P_87 , 2U ) ;
ssCallAccelRunBlock ( S , 6 , 85 , SS_CALL_MDL_OUTPUTS ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW -> Step_MODE = (
ssGetTaskTime ( S , 1 ) >= _rtP -> P_89 ) ; if ( _rtDW -> Step_MODE == 1 ) {
rtb_B_6_2_0 = _rtP -> P_91 ; } else { rtb_B_6_2_0 = _rtP -> P_90 ; } if (
rtb_B_6_2_0 > _rtP -> P_92 ) { _rtB -> B_6_117_0 = _rtB -> B_6_42_0 ; } else
{ _rtB -> B_6_117_0 = _rtB -> B_6_9_0_b ; } _rtB -> B_6_118_0 = _rtB ->
B_6_44_0 ; _rtB -> B_6_128_0 = _rtB -> B_6_46_0 ; } if ( ( _rtDW ->
TimeStampA >= ssGetT ( S ) ) && ( _rtDW -> TimeStampB >= ssGetT ( S ) ) ) {
_rtB -> B_6_141_0 = 0.0 ; } else { rtb_B_6_2_0 = _rtDW -> TimeStampA ; lastU
= & _rtDW -> LastUAtTimeA ; if ( _rtDW -> TimeStampA < _rtDW -> TimeStampB )
{ if ( _rtDW -> TimeStampB < ssGetT ( S ) ) { rtb_B_6_2_0 = _rtDW ->
TimeStampB ; lastU = & _rtDW -> LastUAtTimeB ; } } else { if ( _rtDW ->
TimeStampA >= ssGetT ( S ) ) { rtb_B_6_2_0 = _rtDW -> TimeStampB ; lastU = &
_rtDW -> LastUAtTimeB ; } } _rtB -> B_6_141_0 = ( _rtB -> B_6_1_0 - * lastU )
/ ( ssGetT ( S ) - rtb_B_6_2_0 ) ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if
( isHit != 0 ) { _rtB -> B_6_143_0 = _rtP -> P_94 * _rtB -> B_6_9_0 [ 15 ] ;
_rtB -> B_6_144_0 = _rtP -> P_95 * _rtB -> B_6_9_0 [ 16 ] ; _rtB -> B_6_145_0
= _rtP -> P_96 * _rtB -> B_6_9_0 [ 17 ] ; _rtB -> B_6_146_0 = _rtP -> P_97 *
_rtB -> B_6_9_0 [ 14 ] ; ssCallAccelRunBlock ( S , 6 , 147 ,
SS_CALL_MDL_OUTPUTS ) ; } _rtB -> B_6_161_0 = rt_Lookup ( _rtP -> P_98 , 6 ,
ssGetT ( S ) , _rtP -> P_99 ) ; if ( ( _rtDW -> TimeStampA_b >= ssGetT ( S )
) && ( _rtDW -> TimeStampB_f >= ssGetT ( S ) ) ) { _rtB -> B_6_162_0 = 0.0 ;
} else { rtb_B_6_2_0 = _rtDW -> TimeStampA_b ; lastU = & _rtDW ->
LastUAtTimeA_f ; if ( _rtDW -> TimeStampA_b < _rtDW -> TimeStampB_f ) { if (
_rtDW -> TimeStampB_f < ssGetT ( S ) ) { rtb_B_6_2_0 = _rtDW -> TimeStampB_f
; lastU = & _rtDW -> LastUAtTimeB_e ; } } else { if ( _rtDW -> TimeStampA_b
>= ssGetT ( S ) ) { rtb_B_6_2_0 = _rtDW -> TimeStampB_f ; lastU = & _rtDW ->
LastUAtTimeB_e ; } } _rtB -> B_6_162_0 = ( _rtB -> B_6_161_0 - * lastU ) / (
ssGetT ( S ) - rtb_B_6_2_0 ) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if (
isHit != 0 ) { ssCallAccelRunBlock ( S , 6 , 185 , SS_CALL_MDL_OUTPUTS ) ;
MPC_load_varying_SampleIL1 ( S , _rtB -> B_6_48_0 , _rtB -> B_6_11_0 , & _rtB
-> SampleIL1 , & _rtDW -> SampleIL1 , & _rtZCE -> SampleIL1 ) ;
MPC_load_varying_SampleIL1 ( S , _rtB -> B_6_48_0 , _rtB -> B_6_10_0 , & _rtB
-> SampleIL4 , & _rtDW -> SampleIL4 , & _rtZCE -> SampleIL4 ) ; } isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_6_188_0 = _rtP ->
P_101 * rtb_B_6_13_0 ; } UNUSED_PARAMETER ( tid ) ; } static void
mdlOutputsTID3 ( SimStruct * S , int_T tid ) { real_T rtb_B_6_13_0 ;
B_MPC_load_varying_T * _rtB ; P_MPC_load_varying_T * _rtP ; _rtP = ( (
P_MPC_load_varying_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_MPC_load_varying_T * ) _ssGetModelBlockIO ( S ) ) ; memcpy ( & _rtB ->
B_6_0_0 [ 0 ] , & _rtP -> P_102 [ 0 ] , 9U * sizeof ( real_T ) ) ; _rtB ->
B_6_1_0_m = _rtP -> P_103 ; _rtB -> B_6_4_0 = _rtP -> P_106 ; _rtB -> B_6_5_0
= _rtP -> P_107 ; _rtB -> B_6_6_0_c = _rtP -> P_108 ; _rtB -> B_6_7_0_k =
_rtP -> P_109 ; _rtB -> B_6_8_0_c = _rtP -> P_110 ; _rtB -> B_6_9_0_b = _rtP
-> P_111 ; _rtB -> B_6_10_0_p = _rtP -> P_112 ; _rtB -> B_6_11_0_c = _rtP ->
P_113 ; _rtB -> B_6_12_0_f = _rtP -> P_114 ; rtb_B_6_13_0 = _rtP -> P_104 *
_rtP -> P_104 ; _rtB -> B_6_14_0_g = _rtP -> P_105 * _rtP -> P_105 ; _rtB ->
B_6_19_0 = rtb_B_6_13_0 * _rtP -> P_115 - _rtP -> P_116 * _rtB -> B_6_14_0_g
; _rtB -> B_6_21_0 = rtb_B_6_13_0 * _rtP -> P_117 ; _rtB -> B_6_23_0 = _rtP
-> P_118 * _rtB -> B_6_14_0_g ; _rtB -> B_6_25_0_g = _rtP -> P_119 * _rtB ->
B_6_14_0_g ; _rtB -> B_6_26_0 = _rtP -> P_120 ; _rtB -> B_6_27_0_m = _rtP ->
P_121 ; _rtB -> B_6_28_0_n = _rtP -> P_122 ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { real_T * lastU ;
int32_T isHit ; B_MPC_load_varying_T * _rtB ; P_MPC_load_varying_T * _rtP ;
DW_MPC_load_varying_T * _rtDW ; _rtDW = ( ( DW_MPC_load_varying_T * )
ssGetRootDWork ( S ) ) ; _rtP = ( ( P_MPC_load_varying_T * ) ssGetModelRtp (
S ) ) ; _rtB = ( ( B_MPC_load_varying_T * ) _ssGetModelBlockIO ( S ) ) ;
isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtDW ->
UnitDelay_DSTATE = _rtB -> B_6_6_0 ; ssCallAccelRunBlock ( S , 6 , 9 ,
SS_CALL_MDL_UPDATE ) ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay1_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay1_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay1_IWORK . Head = ( ( _rtDW ->
TransportDelay1_IWORK . Head < ( _rtDW -> TransportDelay1_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay1_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay1_IWORK . Head == _rtDW ->
TransportDelay1_IWORK . Tail ) { if ( !
MPC_load_varying_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay1_IWORK . CircularBufSize , & _rtDW -> TransportDelay1_IWORK .
Tail , & _rtDW -> TransportDelay1_IWORK . Head , & _rtDW ->
TransportDelay1_IWORK . Last , simTime - _rtP -> P_77 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay1_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay1_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay1_IWORK . Head ] = _rtB ->
B_6_73_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay2_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay2_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay2_IWORK . Head = ( ( _rtDW ->
TransportDelay2_IWORK . Head < ( _rtDW -> TransportDelay2_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay2_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay2_IWORK . Head == _rtDW ->
TransportDelay2_IWORK . Tail ) { if ( !
MPC_load_varying_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay2_IWORK . CircularBufSize , & _rtDW -> TransportDelay2_IWORK .
Tail , & _rtDW -> TransportDelay2_IWORK . Head , & _rtDW ->
TransportDelay2_IWORK . Last , simTime - _rtP -> P_79 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay2_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay2_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay2_IWORK . Head ] = _rtB ->
B_6_78_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * *
) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK . Head = ( ( _rtDW ->
TransportDelay_IWORK . Head < ( _rtDW -> TransportDelay_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay_IWORK . Head == _rtDW -> TransportDelay_IWORK
. Tail ) { if ( ! MPC_load_varying_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW
-> TransportDelay_IWORK . CircularBufSize , & _rtDW -> TransportDelay_IWORK .
Tail , & _rtDW -> TransportDelay_IWORK . Head , & _rtDW ->
TransportDelay_IWORK . Last , simTime - _rtP -> P_85 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] = _rtB ->
B_6_84_0 ; } if ( _rtDW -> TimeStampA == ( rtInf ) ) { _rtDW -> TimeStampA =
ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA ; } else if ( _rtDW ->
TimeStampB == ( rtInf ) ) { _rtDW -> TimeStampB = ssGetT ( S ) ; lastU = &
_rtDW -> LastUAtTimeB ; } else if ( _rtDW -> TimeStampA < _rtDW -> TimeStampB
) { _rtDW -> TimeStampA = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA ; }
else { _rtDW -> TimeStampB = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB ;
} * lastU = _rtB -> B_6_1_0 ; if ( _rtDW -> TimeStampA_b == ( rtInf ) ) {
_rtDW -> TimeStampA_b = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA_f ; }
else if ( _rtDW -> TimeStampB_f == ( rtInf ) ) { _rtDW -> TimeStampB_f =
ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB_e ; } else if ( _rtDW ->
TimeStampA_b < _rtDW -> TimeStampB_f ) { _rtDW -> TimeStampA_b = ssGetT ( S )
; lastU = & _rtDW -> LastUAtTimeA_f ; } else { _rtDW -> TimeStampB_f = ssGetT
( S ) ; lastU = & _rtDW -> LastUAtTimeB_e ; } * lastU = _rtB -> B_6_161_0 ;
UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdateTID3 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { B_MPC_load_varying_T * _rtB ;
XDot_MPC_load_varying_T * _rtXdot ; _rtXdot = ( ( XDot_MPC_load_varying_T * )
ssGetdX ( S ) ) ; _rtB = ( ( B_MPC_load_varying_T * ) _ssGetModelBlockIO ( S
) ) ; _rtXdot -> Integrator_CSTATE = _rtB -> B_6_188_0 ; }
#define MDL_ZERO_CROSSINGS
static void mdlZeroCrossings ( SimStruct * S ) { B_MPC_load_varying_T * _rtB
; P_MPC_load_varying_T * _rtP ; ZCV_MPC_load_varying_T * _rtZCSV ; _rtZCSV =
( ( ZCV_MPC_load_varying_T * ) ssGetSolverZcSignalVector ( S ) ) ; _rtP = ( (
P_MPC_load_varying_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_MPC_load_varying_T * ) _ssGetModelBlockIO ( S ) ) ; _rtZCSV ->
Step2_StepTime_ZC = ssGetT ( S ) - _rtP -> P_9 ; _rtZCSV ->
Saturation_UprLim_ZC = _rtB -> B_6_16_0 - _rtP -> P_66 ; _rtZCSV ->
Saturation_LwrLim_ZC = _rtB -> B_6_16_0 - _rtP -> P_67 ; _rtZCSV ->
Saturation_UprLim_ZC_b = _rtB -> B_6_27_0 - _rtP -> P_69 ; _rtZCSV ->
Saturation_LwrLim_ZC_h = _rtB -> B_6_27_0 - _rtP -> P_70 ; _rtZCSV ->
RelationalOperator_RelopInput_ZC = _rtB -> B_6_36_0 - _rtB -> B_6_41_0 ;
_rtZCSV -> RelationalOperator1_RelopInput_ZC = _rtB -> B_6_36_0 - _rtB ->
B_6_43_0 ; _rtZCSV -> RelationalOperator2_RelopInput_ZC = _rtB -> B_6_36_0 -
_rtB -> B_6_45_0 ; _rtZCSV -> Compare_RelopInput_ZC = _rtB -> B_6_47_0 -
MPC_load_varying_rtC ( S ) -> B_6_3_0 ; _rtZCSV -> Compare_RelopInput_ZC_l =
_rtB -> B_6_52_0 - MPC_load_varying_rtC ( S ) -> B_6_4_0 ; _rtZCSV ->
Compare_RelopInput_ZC_g = _rtB -> B_6_55_0 - MPC_load_varying_rtC ( S ) ->
B_6_5_0 ; _rtZCSV -> Compare_RelopInput_ZC_n = _rtB -> B_6_41_0 -
MPC_load_varying_rtC ( S ) -> B_6_0_0 ; _rtZCSV -> Compare_RelopInput_ZC_a =
_rtB -> B_6_43_0 - MPC_load_varying_rtC ( S ) -> B_6_1_0 ; _rtZCSV ->
Compare_RelopInput_ZC_b = _rtB -> B_6_45_0 - MPC_load_varying_rtC ( S ) ->
B_6_2_0 ; _rtZCSV -> Step_StepTime_ZC = ssGetT ( S ) - _rtP -> P_89 ; _rtZCSV
-> HitCrossing_HitNoOutput_ZC = _rtB -> B_6_141_0 - _rtP -> P_93 ; _rtZCSV ->
HitCrossing_HitNoOutput_ZC_j = _rtB -> B_6_162_0 - _rtP -> P_100 ; } static
void mdlInitializeSizes ( SimStruct * S ) { ssSetChecksumVal ( S , 0 ,
2057123434U ) ; ssSetChecksumVal ( S , 1 , 2417547017U ) ; ssSetChecksumVal (
S , 2 , 406431199U ) ; ssSetChecksumVal ( S , 3 , 1784812245U ) ; { mxArray *
slVerStructMat = NULL ; mxArray * slStrMat = mxCreateString ( "simulink" ) ;
char slVerChar [ 10 ] ; int status = mexCallMATLAB ( 1 , & slVerStructMat , 1
, & slStrMat , "ver" ) ; if ( status == 0 ) { mxArray * slVerMat = mxGetField
( slVerStructMat , 0 , "Version" ) ; if ( slVerMat == NULL ) { status = 1 ; }
else { status = mxGetString ( slVerMat , slVerChar , 10 ) ; } }
mxDestroyArray ( slStrMat ) ; mxDestroyArray ( slVerStructMat ) ; if ( (
status == 1 ) || ( strcmp ( slVerChar , "10.0" ) != 0 ) ) { return ; } }
ssSetOptions ( S , SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork (
S ) != sizeof ( DW_MPC_load_varying_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( B_MPC_load_varying_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
P_MPC_load_varying_T ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetModelRtp ( S , ( real_T *
) & MPC_load_varying_rtDefaultP ) ; _ssSetConstBlockIO ( S , &
MPC_load_varying_rtInvariant ) ; rt_InitInfAndNaN ( sizeof ( real_T ) ) ; }
static void mdlInitializeSampleTimes ( SimStruct * S ) { slAccRegPrmChangeFcn
( S , mdlOutputsTID3 ) ; } static void mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"
