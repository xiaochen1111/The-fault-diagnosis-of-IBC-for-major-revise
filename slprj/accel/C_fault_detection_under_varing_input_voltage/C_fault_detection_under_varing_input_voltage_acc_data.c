#include "__cf_C_fault_detection_under_varing_input_voltage.h"
#include "C_fault_detection_under_varing_input_voltage_acc.h"
#include "C_fault_detection_under_varing_input_voltage_acc_private.h"
const ConstB_C_fault_detection_under_varing_input_voltage_T
C_fault_detection_under_varing_input_voltage_rtInvariant = { 0.0 , 0.0 , 0.0
, 0.0 , 0.0 , 0.0 } ; P_C_fault_detection_under_varing_input_voltage_T
C_fault_detection_under_varing_input_voltage_rtDefaultP = { 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , { 0.0 , 0.01 , 0.01 , 0.02 , 0.02 , 1.02 } , { 10.0 ,
10.0 , 14.0 , 14.0 , 14.0 , 14.0 } , 0.1 , 4.0 , 8.0 , 0.001 , 0.0 , { 1.0 ,
1.0 } , 2.5E-8 , { 4.0 , 4.0 } , { - 0.11111111111111101 , 0.0 , 0.0 , 0.0 ,
0.0 , - 0.11111111111111101 , 0.0 , 0.0 , 0.0 , 0.0 , - 0.11111111111111101 ,
0.0 , 0.0 , 0.0 , 0.0 , 1.0 } , { 4.0 , 11.0 } , { 0.0 ,
4.4444444444444433E+7 , 0.0 , 0.0 , 0.0 , 0.0 , 4.4444444444444433E+7 , 0.0 ,
4.4444444444444433E+7 , 0.0 , 0.0 , 0.0 , 4.4444444444444433E+7 , 0.0 , 0.0 ,
2702.7027027027029 , 0.0 , 4.4444444444444433E+7 , 0.0 , 2702.7027027027029 ,
0.0 , 0.0 , 4.4444444444444433E+7 , 2702.7027027027029 , 0.0 , -
4.4444444444444433E+7 , 0.0 , 0.0 , 0.0 , 0.0 , - 4.4444444444444433E+7 , 0.0
, - 4.4444444444444433E+7 , 0.0 , 0.0 , 0.0 , 444.4444444444444 ,
444.4444444444444 , 444.4444444444444 , 0.0 , 0.0 , 0.0 , 0.0 , -
2702.7027027027029 } , { 19.0 , 4.0 } , { 0.0 , 0.0 , 0.0011111111111111111 ,
0.0011111111111111111 , 0.0 , 0.0 , 0.0 , 0.0 , - 0.0011111111111111111 , 0.0
, 1.111111111111111E-8 , 0.0 , 0.0 , 0.0 , 1.111111111111111E-8 , 0.0 , 0.0 ,
1.111111111111111E-8 , 0.0 , 0.0011111111111111111 , 0.0 , 0.0 , 0.0 ,
0.0011111111111111111 , 0.0 , - 0.0011111111111111111 , 0.0 , 0.0 , 0.0 , 0.0
, 1.111111111111111E-8 , 0.0 , 0.0 , 0.0 , 1.111111111111111E-8 , 0.0 ,
1.111111111111111E-8 , 0.0 , 0.0 , 0.0011111111111111111 , 0.0 , 0.0 , 0.0 ,
0.0011111111111111111 , 0.0 , - 0.0011111111111111111 , 0.0 , 0.0 , 0.0 , 0.0
, 1.111111111111111E-8 , 0.0 , 0.0 , 0.0 , 1.111111111111111E-8 ,
1.111111111111111E-8 , 0.0 , 0.0 , 0.0 , 0.0 , - 2.5E-8 , - 2.5E-8 , - 2.5E-8
, 0.0 , 0.0 , 0.0 , 2.5E-8 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
2.5E-8 } , { 19.0 , 11.0 } , { - 44444.444444444445 , 0.0 , 0.0 , 0.0 , -
44444.444444444445 , 0.0 , 44444.444444444445 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.55555555555555536 , 0.0 , 0.0 , 0.0 , 0.55555555555555536 , 0.0 ,
0.55555555555555536 , 0.0 , 0.0 , - 44444.444444444445 , 0.0 , 0.0 , 0.0 , -
44444.444444444445 , 0.0 , 44444.444444444445 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.55555555555555536 , 0.0 , 0.0 , 0.0 , 0.55555555555555536 ,
0.55555555555555536 , 0.0 , 0.0 , 0.0 , - 44444.444444444445 , -
44444.444444444445 , 0.0 , 0.0 , 0.0 , 0.0 , 44444.444444444445 , 0.0 ,
0.55555555555555536 , 0.0 , 0.0 , 0.0 , 0.55555555555555536 , 0.0 , 0.0 ,
0.55555555555555536 , 0.0 , 0.0 , 0.0 , - 44444.444444444445 , -
44444.444478228237 , - 3.3783783783783784E-5 , - 3.3783783783783784E-5 , 0.0
, 0.0 , 44444.444444444445 , 3.3783783783783784E-5 , 0.55555555555555536 ,
0.0 , 0.0 , 1.0 , - 0.44444444444444464 , 0.0 , 0.0 , 0.55555555555555536 ,
3.3783783783783784E-5 , - 44444.444444444445 , 0.0 , 0.0 , -
3.3783783783783784E-5 , - 44444.444478228237 , - 3.3783783783783784E-5 ,
44444.444444444445 , 0.0 , 0.0 , 3.3783783783783784E-5 , 0.0 ,
0.55555555555555536 , 0.0 , 1.0 , 0.0 , - 0.44444444444444464 , 0.0 ,
0.55555555555555536 , 3.3783783783783784E-5 , 0.0 , - 44444.444444444445 ,
0.0 , - 3.3783783783783784E-5 , - 3.3783783783783784E-5 , -
44444.444478228237 , 0.0 , 44444.444444444445 , 0.0 , 3.3783783783783784E-5 ,
0.0 , 0.0 , 0.55555555555555536 , 1.0 , 0.0 , 0.0 , - 0.44444444444444464 ,
0.55555555555555536 , 3.3783783783783784E-5 , 44444.444444444445 , 0.0 , 0.0
, 0.0 , 44444.444444444445 , 0.0 , - 44444.444444444445 , 0.0 , 0.0 , 0.0 ,
0.0 , - 0.55555555555555536 , 0.0 , 0.0 , 0.0 , - 0.55555555555555536 , 0.0 ,
- 0.55555555555555536 , 0.0 , 0.0 , 44444.444444444445 , 0.0 , 0.0 , 0.0 ,
44444.444444444445 , 0.0 , - 44444.444444444445 , 0.0 , 0.0 , 0.0 , 0.0 , -
0.55555555555555536 , 0.0 , 0.0 , 0.0 , - 0.55555555555555536 , -
0.55555555555555536 , 0.0 , 0.0 , 0.0 , 44444.444444444445 ,
44444.444444444445 , 0.0 , 0.0 , 0.0 , 0.0 , - 44444.444444444445 , 0.0 , -
0.55555555555555536 , 0.0 , 0.0 , 0.0 , - 0.55555555555555536 , 0.0 , 0.0 , -
0.55555555555555536 , 0.0 , 0.55555555555555558 , 0.55555555555555558 ,
0.55555555555555558 , 0.55555555555555558 , 0.55555555555555558 ,
0.55555555555555558 , - 0.55555555555555558 , - 0.55555555555555558 , -
0.55555555555555558 , 0.0 , 5.555555555555555E-6 , 5.555555555555555E-6 ,
5.555555555555555E-6 , 0.0 , 5.555555555555555E-6 , 5.555555555555555E-6 ,
5.555555555555555E-6 , 1.6666666666666664E-5 , 0.0 , 0.0 , 0.0 , 0.0 ,
3.3783783783783784E-5 , 3.3783783783783784E-5 , 3.3783783783783784E-5 , 0.0 ,
0.0 , 0.0 , - 3.3783783783783784E-5 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0
, 0.0 , - 3.3783783783783784E-5 } , { 4.0 , 1.0 } , { 0.0 , 0.0 , 0.0 , 0.0 }
, { 1.0 , 1.0 } , 0.0 , { 1.0 , 3.0 } , { 0.0 , 1.0 , 1.0 } , { 0.0 , 0.0 } ,
{ 1.0 , 1.0 } , 11.0 , { 1.0 , 1.0 } , 19.0 , { 1.0 , 0.0 } , { 1.0 , 1.0 } ,
0.0 , { 1.0 , 1.0 } , 0.0 , { 0.0 , 0.0 } , { 1.0 , 1.0 } , 1.0 , { 1.0 , 1.0
} , 0.0001 , { 1.0 , 1.0 } , 100.0 , { 1.0 , 1.0 } , 0.0 , { 1.0 , 9.0 } , {
0.01 , 0.01 , 0.01 , 0.001 , 0.001 , 0.001 , 0.01 , 0.01 , 0.01 } , { 1.0 ,
9.0 } , { 1.0 , 1.0 , 1.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 , 3.0 } , { 9.0 , 1.0
} , { 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 } , { 1.0 , 9.0 } ,
{ 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 } , { 1.0 , 1.0 } , 1.0
, 1.0 , 1.0 , 1.0 , 1.0 , { 0.0 , 1000.0 , 0.0 } , { 0.0 , 5.0E-5 , 0.0001 }
, 0.62718109879312411 , 0.0 , 1.0 , 77.738292364102008 , 0.0 , 1000.0 , 0.0 ,
6.666666666666667E-5 , 0.0 , 3.3333333333333335E-5 , 0.0 , 0.002 , { 0.0 ,
1000.0 , 0.0 } , { 0.0 , 4.9999999999999996E-5 , 0.0001 } , { 0.0 , 1000.0 ,
0.0 } , { 0.0 , 4.9999999999999996E-5 , 9.9999999999999991E-5 } ,
3.3333333333333337E-6 , 0.0 , { 0.0 , 1000.0 , 0.0 } , { 0.0 , 5.0E-6 ,
1.0E-5 } , 0.02499 , 1.0 , 0.0 , 0.5 , 0.0 , 1.0 , 1.0 , 1.0 , 1.0 , { 0.0 ,
0.01 , 0.01 , 0.02 , 0.02 , 1.02 } , { 2.0 , 2.0 , 4.0 , 4.0 , 8.0 , 8.0 } ,
0.0 , 38432.721244442 , 971.09450057614072 , { 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 } , 1.0 , 0.0001 , 0.0001 , 0.0001 , 1.0E-5 , 0.0 , 1.0
, 0.001 , - 0.001 , 24.0 , { 0.0 } , { 0.0 } , { 0.0 } , { 0.0 } , { 0.0 } }
;
