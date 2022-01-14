#include "__cf_IBC_open_basis_test_SMC_False.h"
#include <math.h>
#include "IBC_open_basis_test_SMC_False_acc.h"
#include "IBC_open_basis_test_SMC_False_acc_private.h"
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
boolean_T IBC_open_basis_test_SMC_False_acc_rt_TDelayUpdateTailOrGrowBuf (
int_T * bufSzPtr , int_T * tailPtr , int_T * headPtr , int_T * lastPtr ,
real_T tMinusDelay , real_T * * tBufPtr , real_T * * uBufPtr , real_T * *
xBufPtr , boolean_T isfixedbuf , boolean_T istransportdelay , int_T *
maxNewBufSzPtr ) { int_T testIdx ; int_T tail = * tailPtr ; int_T bufSz = *
bufSzPtr ; real_T * tBuf = * tBufPtr ; real_T * xBuf = ( NULL ) ; int_T
numBuffer = 2 ; if ( istransportdelay ) { numBuffer = 3 ; xBuf = * xBufPtr ;
} testIdx = ( tail < ( bufSz - 1 ) ) ? ( tail + 1 ) : 0 ; if ( ( tMinusDelay
<= tBuf [ testIdx ] ) && ! isfixedbuf ) { int_T j ; real_T * tempT ; real_T *
tempU ; real_T * tempX = ( NULL ) ; real_T * uBuf = * uBufPtr ; int_T
newBufSz = bufSz + 1024 ; if ( newBufSz > * maxNewBufSzPtr ) { *
maxNewBufSzPtr = newBufSz ; } tempU = ( real_T * ) utMalloc ( numBuffer *
newBufSz * sizeof ( real_T ) ) ; if ( tempU == ( NULL ) ) { return ( false )
; } tempT = tempU + newBufSz ; if ( istransportdelay ) tempX = tempT +
newBufSz ; for ( j = tail ; j < bufSz ; j ++ ) { tempT [ j - tail ] = tBuf [
j ] ; tempU [ j - tail ] = uBuf [ j ] ; if ( istransportdelay ) tempX [ j -
tail ] = xBuf [ j ] ; } for ( j = 0 ; j < tail ; j ++ ) { tempT [ j + bufSz -
tail ] = tBuf [ j ] ; tempU [ j + bufSz - tail ] = uBuf [ j ] ; if (
istransportdelay ) tempX [ j + bufSz - tail ] = xBuf [ j ] ; } if ( * lastPtr
> tail ) { * lastPtr -= tail ; } else { * lastPtr += ( bufSz - tail ) ; } *
tailPtr = 0 ; * headPtr = bufSz ; utFree ( uBuf ) ; * bufSzPtr = newBufSz ; *
tBufPtr = tempT ; * uBufPtr = tempU ; if ( istransportdelay ) * xBufPtr =
tempX ; } else { * tailPtr = testIdx ; } return ( true ) ; } real_T
IBC_open_basis_test_SMC_False_acc_rt_TDelayInterpolate ( real_T tMinusDelay ,
real_T tStart , real_T * tBuf , real_T * uBuf , int_T bufSz , int_T * lastIdx
, int_T oldestIdx , int_T newIdx , real_T initOutput , boolean_T discrete ,
boolean_T minorStepAndTAtLastMajorOutput ) { int_T i ; real_T yout , t1 , t2
, u1 , u2 ; if ( ( newIdx == 0 ) && ( oldestIdx == 0 ) && ( tMinusDelay >
tStart ) ) return initOutput ; if ( tMinusDelay <= tStart ) return initOutput
; if ( ( tMinusDelay <= tBuf [ oldestIdx ] ) ) { if ( discrete ) { return (
uBuf [ oldestIdx ] ) ; } else { int_T tempIdx = oldestIdx + 1 ; if (
oldestIdx == bufSz - 1 ) tempIdx = 0 ; t1 = tBuf [ oldestIdx ] ; t2 = tBuf [
tempIdx ] ; u1 = uBuf [ oldestIdx ] ; u2 = uBuf [ tempIdx ] ; if ( t2 == t1 )
{ if ( tMinusDelay >= t2 ) { yout = u2 ; } else { yout = u1 ; } } else {
real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 ) ; real_T f2 = 1.0 - f1 ; yout
= f1 * u1 + f2 * u2 ; } return yout ; } } if ( minorStepAndTAtLastMajorOutput
) { if ( newIdx != 0 ) { if ( * lastIdx == newIdx ) { ( * lastIdx ) -- ; }
newIdx -- ; } else { if ( * lastIdx == newIdx ) { * lastIdx = bufSz - 1 ; }
newIdx = bufSz - 1 ; } } i = * lastIdx ; if ( tBuf [ i ] < tMinusDelay ) {
while ( tBuf [ i ] < tMinusDelay ) { if ( i == newIdx ) break ; i = ( i < (
bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } } else { while ( tBuf [ i ] >= tMinusDelay
) { i = ( i > 0 ) ? i - 1 : ( bufSz - 1 ) ; } i = ( i < ( bufSz - 1 ) ) ? ( i
+ 1 ) : 0 ; } * lastIdx = i ; if ( discrete ) { double tempEps = (
DBL_EPSILON ) * 128.0 ; double localEps = tempEps * muDoubleScalarAbs ( tBuf
[ i ] ) ; if ( tempEps > localEps ) { localEps = tempEps ; } localEps =
localEps / 2.0 ; if ( tMinusDelay >= ( tBuf [ i ] - localEps ) ) { yout =
uBuf [ i ] ; } else { if ( i == 0 ) { yout = uBuf [ bufSz - 1 ] ; } else {
yout = uBuf [ i - 1 ] ; } } } else { if ( i == 0 ) { t1 = tBuf [ bufSz - 1 ]
; u1 = uBuf [ bufSz - 1 ] ; } else { t1 = tBuf [ i - 1 ] ; u1 = uBuf [ i - 1
] ; } t2 = tBuf [ i ] ; u2 = uBuf [ i ] ; if ( t2 == t1 ) { if ( tMinusDelay
>= t2 ) { yout = u2 ; } else { yout = u1 ; } } else { real_T f1 = ( t2 -
tMinusDelay ) / ( t2 - t1 ) ; real_T f2 = 1.0 - f1 ; yout = f1 * u1 + f2 * u2
; } } return ( yout ) ; } void rt_ssGetBlockPath ( SimStruct * S , int_T
sysIdx , int_T blkIdx , char_T * * path ) { _ssGetBlockPath ( S , sysIdx ,
blkIdx , path ) ; } void rt_ssSet_slErrMsg ( SimStruct * S , void * diag ) {
if ( ! _ssIsErrorStatusAslErrMsg ( S ) ) { _ssSet_slErrMsg ( S , diag ) ; }
else { _ssDiscardDiagnostic ( S , diag ) ; } } void
rt_ssReportDiagnosticAsWarning ( SimStruct * S , void * diag ) {
_ssReportDiagnosticAsWarning ( S , diag ) ; } void
IBC_open_basis_test_SMC_False_SampleandHold_Init ( SimStruct * S ,
B_SampleandHold_IBC_open_basis_test_SMC_False_T * localB ,
P_SampleandHold_IBC_open_basis_test_SMC_False_T * localP ) { localB ->
B_1_0_0 = localP -> P_0 ; } void IBC_open_basis_test_SMC_False_SampleandHold
( SimStruct * S , real_T rtu_Trigger , real_T rtu_In ,
B_SampleandHold_IBC_open_basis_test_SMC_False_T * localB ,
DW_SampleandHold_IBC_open_basis_test_SMC_False_T * localDW ,
ZCE_SampleandHold_IBC_open_basis_test_SMC_False_T * localZCE ) { ZCEventType
zcEvent ; if ( ssIsMajorTimeStep ( S ) != 0 ) { zcEvent = rt_ZCFcn (
RISING_ZERO_CROSSING , & localZCE -> SampleandHold_Trig_ZCE , rtu_Trigger ) ;
if ( zcEvent != NO_ZCEVENT ) { localB -> B_1_0_0 = rtu_In ; localDW ->
SampleandHold_SubsysRanBC = 4 ; } } } void
IBC_open_basis_test_SMC_False_SampleandHold_Term ( SimStruct * const S ) { }
static void mdlOutputs ( SimStruct * S , int_T tid ) { real_T * lastU ;
real_T rtb_B_4_2_0 ; uint32_T numCycles ; real_T ratio ; int32_T isHit ;
B_IBC_open_basis_test_SMC_False_T * _rtB ; P_IBC_open_basis_test_SMC_False_T
* _rtP ; PrevZCX_IBC_open_basis_test_SMC_False_T * _rtZCE ;
DW_IBC_open_basis_test_SMC_False_T * _rtDW ; _rtDW = ( (
DW_IBC_open_basis_test_SMC_False_T * ) ssGetRootDWork ( S ) ) ; _rtZCE = ( (
PrevZCX_IBC_open_basis_test_SMC_False_T * ) _ssGetPrevZCSigState ( S ) ) ;
_rtP = ( ( P_IBC_open_basis_test_SMC_False_T * ) ssGetModelRtp ( S ) ) ; _rtB
= ( ( B_IBC_open_basis_test_SMC_False_T * ) _ssGetModelBlockIO ( S ) ) ; _rtB
-> B_4_1_0 = rt_Lookup ( _rtP -> P_1 , 6 , ssGetT ( S ) , _rtP -> P_2 ) ;
isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW -> Step2_MODE
= ( ssGetTaskTime ( S , 1 ) >= _rtP -> P_3 ) ; if ( _rtDW -> Step2_MODE == 1
) { rtb_B_4_2_0 = _rtP -> P_5 ; } else { rtb_B_4_2_0 = _rtP -> P_4 ; } if ( !
( muDoubleScalarAbs ( rtb_B_4_2_0 ) > _rtP -> P_6 ) ) { if (
muDoubleScalarSign ( rtb_B_4_2_0 ) > _rtP -> P_0 ) { rtb_B_4_2_0 = _rtB ->
B_4_3_0 ; } else { rtb_B_4_2_0 = _rtB -> B_4_4_0 ; } } _rtB -> B_4_6_0 = _rtB
-> B_4_2_0 / rtb_B_4_2_0 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit
!= 0 ) { _rtB -> B_4_7_0 = _rtDW -> UnitDelay_DSTATE ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_4_8_0 = _rtB ->
B_4_6_0 - _rtB -> B_4_7_0 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if (
isHit != 0 ) { ssCallAccelRunBlock ( S , 4 , 9 , SS_CALL_MDL_OUTPUTS ) ; _rtB
-> B_4_11_0 = _rtP -> P_57 * _rtB -> B_4_9_0 [ 10 ] ; rtb_B_4_2_0 = ( _rtB ->
B_4_11_0 - _rtP -> P_56 * _rtB -> B_4_9_0 [ 9 ] ) * _rtP -> P_58 ;
rtb_B_4_2_0 = ( ( ( _rtB -> B_4_6_0_c - _rtP -> P_59 * _rtB -> B_4_11_0 ) *
_rtP -> P_60 + rtb_B_4_2_0 ) - _rtP -> P_61 * _rtB -> B_4_9_0 [ 19 ] * _rtP
-> P_62 ) - rtb_B_4_2_0 ; _rtDW -> Relay_Mode = ( ( rtb_B_4_2_0 >= _rtP ->
P_63 ) || ( ( ! ( rtb_B_4_2_0 <= _rtP -> P_64 ) ) && _rtDW -> Relay_Mode ) )
; if ( _rtDW -> Relay_Mode ) { _rtB -> B_4_21_0 = _rtP -> P_65 ; } else {
_rtB -> B_4_21_0 = _rtP -> P_66 ; } } isHit = ssIsSampleHit ( S , 5 , 0 ) ;
if ( isHit != 0 ) { rtb_B_4_2_0 = ssGetTaskTime ( S , 5 ) ; if (
ssGetTNextWasAdjusted ( S , 5 ) != 0 ) { _rtDW -> nextTime =
_ssGetVarNextHitTime ( S , 2 ) ; } if ( _rtDW -> justEnabled != 0 ) { _rtDW
-> justEnabled = 0 ; if ( rtb_B_4_2_0 >= _rtP -> P_70 ) { ratio = (
rtb_B_4_2_0 - _rtP -> P_70 ) / _rtP -> P_68 ; numCycles = ( uint32_T )
muDoubleScalarFloor ( ratio ) ; if ( muDoubleScalarAbs ( ( real_T ) (
numCycles + 1U ) - ratio ) < DBL_EPSILON * ratio ) { numCycles ++ ; } _rtDW
-> numCompleteCycles = numCycles ; ratio = ( ( real_T ) numCycles * _rtP ->
P_68 + _rtP -> P_70 ) + _rtP -> P_69 * _rtP -> P_68 / 100.0 ; if (
rtb_B_4_2_0 < ratio ) { _rtDW -> currentValue = 1 ; _rtDW -> nextTime = ratio
; } else { _rtDW -> currentValue = 0 ; _rtDW -> nextTime = ( real_T ) (
numCycles + 1U ) * _rtP -> P_68 + _rtP -> P_70 ; } } else { _rtDW ->
numCompleteCycles = _rtP -> P_70 != 0.0 ? - 1 : 0 ; _rtDW -> currentValue = 0
; _rtDW -> nextTime = _rtP -> P_70 ; } } else { if ( _rtDW -> nextTime <=
rtb_B_4_2_0 ) { if ( _rtDW -> currentValue == 1 ) { _rtDW -> currentValue = 0
; _rtDW -> nextTime = ( real_T ) ( _rtDW -> numCompleteCycles + 1LL ) * _rtP
-> P_68 + _rtP -> P_70 ; } else { _rtDW -> numCompleteCycles ++ ; _rtDW ->
currentValue = 1 ; _rtDW -> nextTime = ( _rtP -> P_69 * _rtP -> P_68 * 0.01 +
( real_T ) _rtDW -> numCompleteCycles * _rtP -> P_68 ) + _rtP -> P_70 ; } } }
_ssSetVarNextHitTime ( S , 2 , _rtDW -> nextTime ) ; if ( _rtDW ->
currentValue == 1 ) { _rtB -> B_4_22_0 = _rtP -> P_67 ; } else { _rtB ->
B_4_22_0 = 0.0 ; } } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 )
{ _rtB -> B_4_23_0 = ( ( _rtB -> B_4_21_0 != 0.0 ) && ( _rtB -> B_4_22_0 !=
0.0 ) ) ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * *
) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_71 ; _rtB -> B_4_24_0
= IBC_open_basis_test_SMC_False_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0
, * tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK . CircularBufSize , &
_rtDW -> TransportDelay_IWORK . Last , _rtDW -> TransportDelay_IWORK . Tail ,
_rtDW -> TransportDelay_IWORK . Head , _rtP -> P_72 , 1 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } ssCallAccelRunBlock ( S , 4 , 25 , SS_CALL_MDL_OUTPUTS ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_4_26_0 = _rtB ->
B_4_23_0 ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB
-> B_4_27_0 = _rtP -> P_73 * _rtB -> B_4_9_0 [ 11 ] ; _rtB -> B_4_28_0 = _rtP
-> P_74 * _rtB -> B_4_9_0 [ 12 ] ; _rtB -> B_4_29_0 = _rtP -> P_75 * _rtB ->
B_4_9_0 [ 13 ] ; ssCallAccelRunBlock ( S , 4 , 30 , SS_CALL_MDL_OUTPUTS ) ; }
isHit = ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit != 0 ) { rtb_B_4_2_0 =
ssGetTaskTime ( S , 3 ) ; if ( ssGetTNextWasAdjusted ( S , 3 ) != 0 ) { _rtDW
-> nextTime_p = _ssGetVarNextHitTime ( S , 0 ) ; } if ( _rtDW ->
justEnabled_c != 0 ) { _rtDW -> justEnabled_c = 0 ; if ( rtb_B_4_2_0 >= _rtP
-> P_79 ) { ratio = ( rtb_B_4_2_0 - _rtP -> P_79 ) / _rtP -> P_77 ; numCycles
= ( uint32_T ) muDoubleScalarFloor ( ratio ) ; if ( muDoubleScalarAbs ( (
real_T ) ( numCycles + 1U ) - ratio ) < DBL_EPSILON * ratio ) { numCycles ++
; } _rtDW -> numCompleteCycles_e = numCycles ; ratio = ( ( real_T ) numCycles
* _rtP -> P_77 + _rtP -> P_79 ) + _rtP -> P_78 * _rtP -> P_77 / 100.0 ; if (
rtb_B_4_2_0 < ratio ) { _rtDW -> currentValue_i = 1 ; _rtDW -> nextTime_p =
ratio ; } else { _rtDW -> currentValue_i = 0 ; _rtDW -> nextTime_p = ( real_T
) ( numCycles + 1U ) * _rtP -> P_77 + _rtP -> P_79 ; } } else { _rtDW ->
numCompleteCycles_e = _rtP -> P_79 != 0.0 ? - 1 : 0 ; _rtDW -> currentValue_i
= 0 ; _rtDW -> nextTime_p = _rtP -> P_79 ; } } else { if ( _rtDW ->
nextTime_p <= rtb_B_4_2_0 ) { if ( _rtDW -> currentValue_i == 1 ) { _rtDW ->
currentValue_i = 0 ; _rtDW -> nextTime_p = ( real_T ) ( _rtDW ->
numCompleteCycles_e + 1LL ) * _rtP -> P_77 + _rtP -> P_79 ; } else { _rtDW ->
numCompleteCycles_e ++ ; _rtDW -> currentValue_i = 1 ; _rtDW -> nextTime_p =
( _rtP -> P_78 * _rtP -> P_77 * 0.01 + ( real_T ) _rtDW ->
numCompleteCycles_e * _rtP -> P_77 ) + _rtP -> P_79 ; } } }
_ssSetVarNextHitTime ( S , 0 , _rtDW -> nextTime_p ) ; if ( _rtDW ->
currentValue_i == 1 ) { _rtB -> B_4_31_0 = _rtP -> P_76 ; } else { _rtB ->
B_4_31_0 = 0.0 ; } } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 )
{ _rtB -> B_4_32_0 = ( ( _rtB -> B_4_21_0 != 0.0 ) && ( _rtB -> B_4_31_0 !=
0.0 ) ) ; } isHit = ssIsSampleHit ( S , 4 , 0 ) ; if ( isHit != 0 ) {
rtb_B_4_2_0 = ssGetTaskTime ( S , 4 ) ; if ( ssGetTNextWasAdjusted ( S , 4 )
!= 0 ) { _rtDW -> nextTime_h = _ssGetVarNextHitTime ( S , 1 ) ; } if ( _rtDW
-> justEnabled_e != 0 ) { _rtDW -> justEnabled_e = 0 ; if ( rtb_B_4_2_0 >=
_rtP -> P_83 ) { ratio = ( rtb_B_4_2_0 - _rtP -> P_83 ) / _rtP -> P_81 ;
numCycles = ( uint32_T ) muDoubleScalarFloor ( ratio ) ; if (
muDoubleScalarAbs ( ( real_T ) ( numCycles + 1U ) - ratio ) < DBL_EPSILON *
ratio ) { numCycles ++ ; } _rtDW -> numCompleteCycles_i = numCycles ; ratio =
( ( real_T ) numCycles * _rtP -> P_81 + _rtP -> P_83 ) + _rtP -> P_82 * _rtP
-> P_81 / 100.0 ; if ( rtb_B_4_2_0 < ratio ) { _rtDW -> currentValue_k = 1 ;
_rtDW -> nextTime_h = ratio ; } else { _rtDW -> currentValue_k = 0 ; _rtDW ->
nextTime_h = ( real_T ) ( numCycles + 1U ) * _rtP -> P_81 + _rtP -> P_83 ; }
} else { _rtDW -> numCompleteCycles_i = _rtP -> P_83 != 0.0 ? - 1 : 0 ; _rtDW
-> currentValue_k = 0 ; _rtDW -> nextTime_h = _rtP -> P_83 ; } } else { if (
_rtDW -> nextTime_h <= rtb_B_4_2_0 ) { if ( _rtDW -> currentValue_k == 1 ) {
_rtDW -> currentValue_k = 0 ; _rtDW -> nextTime_h = ( real_T ) ( _rtDW ->
numCompleteCycles_i + 1LL ) * _rtP -> P_81 + _rtP -> P_83 ; } else { _rtDW ->
numCompleteCycles_i ++ ; _rtDW -> currentValue_k = 1 ; _rtDW -> nextTime_h =
( _rtP -> P_82 * _rtP -> P_81 * 0.01 + ( real_T ) _rtDW ->
numCompleteCycles_i * _rtP -> P_81 ) + _rtP -> P_83 ; } } }
_ssSetVarNextHitTime ( S , 1 , _rtDW -> nextTime_h ) ; if ( _rtDW ->
currentValue_k == 1 ) { _rtB -> B_4_33_0 = _rtP -> P_80 ; } else { _rtB ->
B_4_33_0 = 0.0 ; } } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 )
{ _rtB -> B_4_34_0 = ( ( _rtB -> B_4_21_0 != 0.0 ) && ( _rtB -> B_4_33_0 !=
0.0 ) ) ; ssCallAccelRunBlock ( S , 4 , 35 , SS_CALL_MDL_OUTPUTS ) ; } isHit
= ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_4_36_0 = _rtP
-> P_84 * _rtB -> B_4_9_0 [ 18 ] ; } { real_T * * uBuffer = ( real_T * * ) &
_rtDW -> TransportDelay3_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = (
real_T * * ) & _rtDW -> TransportDelay3_PWORK . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_85 ; _rtB
-> B_4_37_0 = IBC_open_basis_test_SMC_False_acc_rt_TDelayInterpolate (
tMinusDelay , 0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay3_IWORK .
CircularBufSize , & _rtDW -> TransportDelay3_IWORK . Last , _rtDW ->
TransportDelay3_IWORK . Tail , _rtDW -> TransportDelay3_IWORK . Head , _rtP
-> P_86 , 1 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } isHit = ssIsSampleHit (
S , 1 , 0 ) ; if ( isHit != 0 ) { IBC_open_basis_test_SMC_False_SampleandHold
( S , _rtB -> B_4_37_0 , _rtB -> B_4_36_0 , & _rtB -> SampleandHold , & _rtDW
-> SampleandHold , & _rtZCE -> SampleandHold ) ; } { real_T * * uBuffer = (
real_T * * ) & _rtDW -> TransportDelay1_PWORK . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK . TUbufferPtrs [
1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP ->
P_87 ; _rtB -> B_4_39_0 =
IBC_open_basis_test_SMC_False_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 ,
* tBuffer , * uBuffer , _rtDW -> TransportDelay1_IWORK . CircularBufSize , &
_rtDW -> TransportDelay1_IWORK . Last , _rtDW -> TransportDelay1_IWORK . Tail
, _rtDW -> TransportDelay1_IWORK . Head , _rtP -> P_88 , 1 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
IBC_open_basis_test_SMC_False_SampleandHold ( S , _rtB -> B_4_39_0 , _rtB ->
B_4_36_0 , & _rtB -> SampleandHold1 , & _rtDW -> SampleandHold1 , & _rtZCE ->
SampleandHold1 ) ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay2_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay2_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_89 ; _rtB -> B_4_41_0
= IBC_open_basis_test_SMC_False_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0
, * tBuffer , * uBuffer , _rtDW -> TransportDelay2_IWORK . CircularBufSize ,
& _rtDW -> TransportDelay2_IWORK . Last , _rtDW -> TransportDelay2_IWORK .
Tail , _rtDW -> TransportDelay2_IWORK . Head , _rtP -> P_90 , 1 , ( boolean_T
) ( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S )
) ) ) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
IBC_open_basis_test_SMC_False_SampleandHold ( S , _rtB -> B_4_41_0 , _rtB ->
B_4_36_0 , & _rtB -> SampleandHold2 , & _rtDW -> SampleandHold2 , & _rtZCE ->
SampleandHold2 ) ; ssCallAccelRunBlock ( S , 4 , 43 , SS_CALL_MDL_OUTPUTS ) ;
_rtDW -> Step_MODE = ( ssGetTaskTime ( S , 1 ) >= _rtP -> P_91 ) ; if ( _rtDW
-> Step_MODE == 1 ) { rtb_B_4_2_0 = _rtP -> P_93 ; } else { rtb_B_4_2_0 =
_rtP -> P_92 ; } if ( rtb_B_4_2_0 > _rtP -> P_94 ) { _rtB -> B_4_69_0 = _rtB
-> B_4_23_0 ; } else { _rtB -> B_4_69_0 = _rtB -> B_4_1_0_m ; } _rtB ->
B_4_70_0 = _rtB -> B_4_32_0 ; _rtB -> B_4_80_0 = _rtB -> B_4_34_0 ; } if ( (
_rtDW -> TimeStampA >= ssGetT ( S ) ) && ( _rtDW -> TimeStampB >= ssGetT ( S
) ) ) { _rtB -> B_4_93_0 = 0.0 ; } else { rtb_B_4_2_0 = _rtDW -> TimeStampA ;
lastU = & _rtDW -> LastUAtTimeA ; if ( _rtDW -> TimeStampA < _rtDW ->
TimeStampB ) { if ( _rtDW -> TimeStampB < ssGetT ( S ) ) { rtb_B_4_2_0 =
_rtDW -> TimeStampB ; lastU = & _rtDW -> LastUAtTimeB ; } } else { if ( _rtDW
-> TimeStampA >= ssGetT ( S ) ) { rtb_B_4_2_0 = _rtDW -> TimeStampB ; lastU =
& _rtDW -> LastUAtTimeB ; } } _rtB -> B_4_93_0 = ( _rtB -> B_4_1_0 - * lastU
) / ( ssGetT ( S ) - rtb_B_4_2_0 ) ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ;
if ( isHit != 0 ) { _rtB -> B_4_95_0 = _rtP -> P_96 * _rtB -> B_4_9_0 [ 15 ]
; _rtB -> B_4_96_0 = _rtP -> P_97 * _rtB -> B_4_9_0 [ 16 ] ; _rtB -> B_4_97_0
= _rtP -> P_98 * _rtB -> B_4_9_0 [ 17 ] ; _rtB -> B_4_98_0 = _rtP -> P_99 *
_rtB -> B_4_9_0 [ 14 ] ; ssCallAccelRunBlock ( S , 4 , 99 ,
SS_CALL_MDL_OUTPUTS ) ; } _rtB -> B_4_119_0 = rt_Lookup ( _rtP -> P_100 , 6 ,
ssGetT ( S ) , _rtP -> P_101 ) ; if ( ( _rtDW -> TimeStampA_m >= ssGetT ( S )
) && ( _rtDW -> TimeStampB_d >= ssGetT ( S ) ) ) { _rtB -> B_4_120_0 = 0.0 ;
} else { rtb_B_4_2_0 = _rtDW -> TimeStampA_m ; lastU = & _rtDW ->
LastUAtTimeA_e ; if ( _rtDW -> TimeStampA_m < _rtDW -> TimeStampB_d ) { if (
_rtDW -> TimeStampB_d < ssGetT ( S ) ) { rtb_B_4_2_0 = _rtDW -> TimeStampB_d
; lastU = & _rtDW -> LastUAtTimeB_e ; } } else { if ( _rtDW -> TimeStampA_m
>= ssGetT ( S ) ) { rtb_B_4_2_0 = _rtDW -> TimeStampB_d ; lastU = & _rtDW ->
LastUAtTimeB_e ; } } _rtB -> B_4_120_0 = ( _rtB -> B_4_119_0 - * lastU ) / (
ssGetT ( S ) - rtb_B_4_2_0 ) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if (
isHit != 0 ) { _rtB -> B_4_148_0 = _rtB -> B_4_23_0 ; _rtB -> B_4_149_0 =
_rtB -> B_4_32_0 ; _rtB -> B_4_150_0 = _rtB -> B_4_34_0 ; }
ssCallAccelRunBlock ( S , 4 , 151 , SS_CALL_MDL_OUTPUTS ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_4_152_0 = _rtB ->
B_4_32_0 ; _rtB -> B_4_153_0 = _rtB -> B_4_23_0 ; _rtB -> B_4_154_0 = _rtB ->
B_4_34_0 ; } UNUSED_PARAMETER ( tid ) ; } static void mdlOutputsTID6 (
SimStruct * S , int_T tid ) { B_IBC_open_basis_test_SMC_False_T * _rtB ;
P_IBC_open_basis_test_SMC_False_T * _rtP ; _rtP = ( (
P_IBC_open_basis_test_SMC_False_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_IBC_open_basis_test_SMC_False_T * ) _ssGetModelBlockIO ( S ) ) ; memcpy ( &
_rtB -> B_4_0_0 [ 0 ] , & _rtP -> P_103 [ 0 ] , 9U * sizeof ( real_T ) ) ;
_rtB -> B_4_1_0_m = _rtP -> P_104 ; _rtB -> B_4_2_0 = _rtP -> P_105 ; _rtB ->
B_4_3_0 = _rtP -> P_106 ; _rtB -> B_4_4_0 = _rtP -> P_107 ; _rtB -> B_4_6_0_c
= _rtP -> P_109 * _rtP -> P_108 ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { real_T * lastU ;
int32_T isHit ; B_IBC_open_basis_test_SMC_False_T * _rtB ;
P_IBC_open_basis_test_SMC_False_T * _rtP ; DW_IBC_open_basis_test_SMC_False_T
* _rtDW ; _rtDW = ( ( DW_IBC_open_basis_test_SMC_False_T * ) ssGetRootDWork (
S ) ) ; _rtP = ( ( P_IBC_open_basis_test_SMC_False_T * ) ssGetModelRtp ( S )
) ; _rtB = ( ( B_IBC_open_basis_test_SMC_False_T * ) _ssGetModelBlockIO ( S )
) ; isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtDW ->
UnitDelay_DSTATE = _rtB -> B_4_6_0 ; ssCallAccelRunBlock ( S , 4 , 9 ,
SS_CALL_MDL_UPDATE ) ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * *
) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK . Head = ( ( _rtDW ->
TransportDelay_IWORK . Head < ( _rtDW -> TransportDelay_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay_IWORK . Head == _rtDW -> TransportDelay_IWORK
. Tail ) { if ( !
IBC_open_basis_test_SMC_False_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK . CircularBufSize , & _rtDW -> TransportDelay_IWORK .
Tail , & _rtDW -> TransportDelay_IWORK . Head , & _rtDW ->
TransportDelay_IWORK . Last , simTime - _rtP -> P_71 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] = _rtB ->
B_4_26_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay3_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay3_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay3_IWORK . Head = ( ( _rtDW ->
TransportDelay3_IWORK . Head < ( _rtDW -> TransportDelay3_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay3_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay3_IWORK . Head == _rtDW ->
TransportDelay3_IWORK . Tail ) { if ( !
IBC_open_basis_test_SMC_False_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay3_IWORK . CircularBufSize , & _rtDW -> TransportDelay3_IWORK .
Tail , & _rtDW -> TransportDelay3_IWORK . Head , & _rtDW ->
TransportDelay3_IWORK . Last , simTime - _rtP -> P_85 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay3_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay3_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay3_IWORK . Head ] = _rtB ->
B_4_153_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay1_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay1_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay1_IWORK . Head = ( ( _rtDW ->
TransportDelay1_IWORK . Head < ( _rtDW -> TransportDelay1_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay1_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay1_IWORK . Head == _rtDW ->
TransportDelay1_IWORK . Tail ) { if ( !
IBC_open_basis_test_SMC_False_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay1_IWORK . CircularBufSize , & _rtDW -> TransportDelay1_IWORK .
Tail , & _rtDW -> TransportDelay1_IWORK . Head , & _rtDW ->
TransportDelay1_IWORK . Last , simTime - _rtP -> P_87 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay1_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay1_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay1_IWORK . Head ] = _rtB ->
B_4_152_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay2_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay2_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay2_IWORK . Head = ( ( _rtDW ->
TransportDelay2_IWORK . Head < ( _rtDW -> TransportDelay2_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay2_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay2_IWORK . Head == _rtDW ->
TransportDelay2_IWORK . Tail ) { if ( !
IBC_open_basis_test_SMC_False_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay2_IWORK . CircularBufSize , & _rtDW -> TransportDelay2_IWORK .
Tail , & _rtDW -> TransportDelay2_IWORK . Head , & _rtDW ->
TransportDelay2_IWORK . Last , simTime - _rtP -> P_89 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & _rtDW -> TransportDelay2_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ _rtDW -> TransportDelay2_IWORK . Head ] =
simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay2_IWORK . Head ] = _rtB ->
B_4_154_0 ; } if ( _rtDW -> TimeStampA == ( rtInf ) ) { _rtDW -> TimeStampA =
ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA ; } else if ( _rtDW ->
TimeStampB == ( rtInf ) ) { _rtDW -> TimeStampB = ssGetT ( S ) ; lastU = &
_rtDW -> LastUAtTimeB ; } else if ( _rtDW -> TimeStampA < _rtDW -> TimeStampB
) { _rtDW -> TimeStampA = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA ; }
else { _rtDW -> TimeStampB = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB ;
} * lastU = _rtB -> B_4_1_0 ; if ( _rtDW -> TimeStampA_m == ( rtInf ) ) {
_rtDW -> TimeStampA_m = ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeA_e ; }
else if ( _rtDW -> TimeStampB_d == ( rtInf ) ) { _rtDW -> TimeStampB_d =
ssGetT ( S ) ; lastU = & _rtDW -> LastUAtTimeB_e ; } else if ( _rtDW ->
TimeStampA_m < _rtDW -> TimeStampB_d ) { _rtDW -> TimeStampA_m = ssGetT ( S )
; lastU = & _rtDW -> LastUAtTimeA_e ; } else { _rtDW -> TimeStampB_d = ssGetT
( S ) ; lastU = & _rtDW -> LastUAtTimeB_e ; } * lastU = _rtB -> B_4_119_0 ;
UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdateTID6 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; }
#define MDL_ZERO_CROSSINGS
static void mdlZeroCrossings ( SimStruct * S ) {
B_IBC_open_basis_test_SMC_False_T * _rtB ; P_IBC_open_basis_test_SMC_False_T
* _rtP ; ZCV_IBC_open_basis_test_SMC_False_T * _rtZCSV ; _rtZCSV = ( (
ZCV_IBC_open_basis_test_SMC_False_T * ) ssGetSolverZcSignalVector ( S ) ) ;
_rtP = ( ( P_IBC_open_basis_test_SMC_False_T * ) ssGetModelRtp ( S ) ) ; _rtB
= ( ( B_IBC_open_basis_test_SMC_False_T * ) _ssGetModelBlockIO ( S ) ) ;
_rtZCSV -> Step2_StepTime_ZC = ssGetT ( S ) - _rtP -> P_3 ; _rtZCSV ->
Step_StepTime_ZC = ssGetT ( S ) - _rtP -> P_91 ; _rtZCSV ->
HitCrossing_HitNoOutput_ZC = _rtB -> B_4_93_0 - _rtP -> P_95 ; _rtZCSV ->
HitCrossing_HitNoOutput_ZC_d = _rtB -> B_4_120_0 - _rtP -> P_102 ; } static
void mdlInitializeSizes ( SimStruct * S ) { ssSetChecksumVal ( S , 0 ,
1869436317U ) ; ssSetChecksumVal ( S , 1 , 458929001U ) ; ssSetChecksumVal (
S , 2 , 3880537038U ) ; ssSetChecksumVal ( S , 3 , 2355157939U ) ; { mxArray
* slVerStructMat = NULL ; mxArray * slStrMat = mxCreateString ( "simulink" )
; char slVerChar [ 10 ] ; int status = mexCallMATLAB ( 1 , & slVerStructMat ,
1 , & slStrMat , "ver" ) ; if ( status == 0 ) { mxArray * slVerMat =
mxGetField ( slVerStructMat , 0 , "Version" ) ; if ( slVerMat == NULL ) {
status = 1 ; } else { status = mxGetString ( slVerMat , slVerChar , 10 ) ; }
} mxDestroyArray ( slStrMat ) ; mxDestroyArray ( slVerStructMat ) ; if ( (
status == 1 ) || ( strcmp ( slVerChar , "10.0" ) != 0 ) ) { return ; } }
ssSetOptions ( S , SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork (
S ) != sizeof ( DW_IBC_open_basis_test_SMC_False_T ) ) { ssSetErrorStatus ( S
, "Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( B_IBC_open_basis_test_SMC_False_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
P_IBC_open_basis_test_SMC_False_T ) ) { static char msg [ 256 ] ; sprintf (
msg , "Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetModelRtp ( S , ( real_T *
) & IBC_open_basis_test_SMC_False_rtDefaultP ) ; rt_InitInfAndNaN ( sizeof (
real_T ) ) ; } static void mdlInitializeSampleTimes ( SimStruct * S ) {
slAccRegPrmChangeFcn ( S , mdlOutputsTID6 ) ; } static void mdlTerminate (
SimStruct * S ) { }
#include "simulink.c"
