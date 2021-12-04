/*
 * sfuntmpl_basic.c: Basic 'C' template for a level 2 S-function.
 *
 * Copyright 1990-2018 The MathWorks, Inc.
 */


/*
 * You must specify the S_FUNCTION_NAME as the name of your S-function
 * (i.e. replace sfuntmpl_basic with the name of your S-function).
 */

#define S_FUNCTION_NAME  IBC
#define S_FUNCTION_LEVEL 2
#define unit unsigned int
/*
 * Need to include simstruc.h for the definition of the SimStruct and
 * its associated macro definitions.
 */
#include "simstruc.h"

int global;
float sat(float input,float min,float max);

struct P
{
    unit CNT;  // counter
    unit PRD;  // period
    unit DIR;  // direction
    unit CMP;  // 
    unit y;
}P1,P2,P3,Out;
int carrier_wave(struct P* P_temp);

struct PI
{
    float FB;
    float REF; //reference
    float KP;
    float KI;
    float ERROR;
    float LAST_ERROR;
    float P;
    float I;
    float h;
}V,I;


/* Error handling
 * --------------
 *
 * You should use the following technique to report errors encountered within
 * an S-function:
 *
 *       ssSetErrorStatus(S,"Error encountered due to ...");
 *       return;
 *
 * Note that the 2nd argument to ssSetErrorStatus must be persistent memory.
 * It cannot be a local variable. For example the following will cause
 * unpredictable errors:
 *
 *      mdlOutputs()
 *      {
 *         char msg[256];         {ILLEGAL: to fix use "static char msg[256];"}
 *         sprintf(msg,"Error due to %s", string);
 *         ssSetErrorStatus(S,msg);
 *         return;
 *      }
 *
 */

/*====================*
 * S-function methods *
 *====================*/

/* Function: mdlInitializeSizes ===============================================
 * Abstract:
 *    The sizes information is used by Simulink to determine the S-function
 *    block's characteristics (number of inputs, outputs, states, etc.).
 *      定义输入输出的接口
 */
static void mdlInitializeSizes(SimStruct *S)
{
    ssSetNumSFcnParams(S, 0);  /* Number of expected parameters */
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        /* Return if number of expected != number of actual parameters */
        return;
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

    if (!ssSetNumInputPorts(S, 1)) return;
    ssSetInputPortWidth(S, 0, 1);
    ssSetInputPortRequiredContiguous(S, 0, true); /*direct input signal access*/
    /*
     * Set direct feedthrough flag (1=yes, 0=no).
     * A port has direct feedthrough if the input is used in either
     * the mdlOutputs or mdlGetTimeOfNextVarHit functions.
     */
    ssSetInputPortDirectFeedThrough(S, 0, 1);

    if (!ssSetNumOutputPorts(S, 3)) return;
    ssSetOutputPortWidth(S, 0, 3);
    ssSetOutputPortWidth(S, 1, 1);
    ssSetOutputPortWidth(S, 2, 3);
    ssSetOutputPortWidth(S, 3, 3);
    
    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 0);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    /* Specify the operating point save/restore compliance to be same as a 
     * built-in block */
    ssSetOperatingPointCompliance(S, USE_DEFAULT_OPERATING_POINT);

    ssSetOptions(S, 0);
}



/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    This function is used to specify the sample time(s) for your
 *    S-function. You must register the same number of sample times as
 *    specified in ssSetNumSampleTimes.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, 2.5e-8);
    ssSetOffsetTime(S, 0, 0.0);

}



#define MDL_INITIALIZE_CONDITIONS   /* Change to #undef to remove function */
#if defined(MDL_INITIALIZE_CONDITIONS)
  /* Function: mdlInitializeConditions ========================================
   * Abstract:
   *    In this function, you should initialize the continuous and discrete
   *    states for your S-function block.  The initial states are placed
   *    in the state vector, ssGetContStates(S) or ssGetRealDiscStates(S).
   *    You can also perform any other initialization activities that your
   *    S-function may require. Note, this routine will be called at the
   *    start of simulation and if it is present in an enabled subsystem
   *    configured to reset states, it will be call when the enabled subsystem
   *    restarts execution to reset the states.
   */
  static void mdlInitializeConditions(SimStruct *S)
  {
      P1.CNT = 0;
      P1.PRD = 200;
      P1.DIR = 0;
      P1.CMP = 120;
      I.FB   = 0;
      I.REF  = 20;
      I.KP   = 9.247;
      I.KI   = 63457.581;
      I.ERROR = 0;
      I.LAST_ERROR = 0;
      I.P = 0;
      I.I = 0;
      I.h = 1e-5;
      
      P2.CNT = 133;
      P2.PRD = 200;
      P2.DIR = 1;
      P2.CMP = 120;
      
      Out.CNT = 0;
      Out.CMP = 120;
      Out.y   = 0;
      Out.PRD = 200;
      
      P3.CNT = 133;
      P3.PRD = 200;
      P3.DIR = 1;
      P3.CMP = 120;
  }
#endif /* MDL_INITIALIZE_CONDITIONS */



#define MDL_START  /* Change to #undef to remove function */
#if defined(MDL_START) 
  /* Function: mdlStart =======================================================
   * Abstract:
   *    This function is called once at start of model execution. If you
   *    have states that should be initialized once, this is the place
   *    to do it.
   */
  static void mdlStart(SimStruct *S)
  {
  }
#endif /*  MDL_START */



/* Function: mdlOutputs =======================================================
 * Abstract:
 *    In this function, you compute the outputs of your S-function
 *    block.
 */
  /* 这个方程中计算模型的输出*/
static void mdlOutputs(SimStruct *S, int_T tid)
{
    const real_T *u  = (const real_T*) ssGetInputPortSignal(S,0);
    real_T       *y  = ssGetOutputPortSignal(S,0);
    real_T       *IL = ssGetOutputPortSignal(S,1); // need to replace
    real_T       *y1 = ssGetOutputPortSignal(S,2);
    real_T       *y2 = ssGetOutputPortSignal(S,3);
// First Phase Carry Wave
//     if (P1.DIR == 0 )
//     {
//         P1.CNT ++;
//     }
//     if (P1.DIR ==1 )
//     {
//         P1.CNT--;
//     }
//     if (P1.CNT == P1.PRD)
//     {
//         P1.DIR = !P1.DIR;
//     }
//     else if (P1.CNT ==0)
//     {
//         P1.DIR = !P1.DIR;
//         IL[0]  = u[0];
//         
//         I.FB = IL[0];
//         I.ERROR = I.REF-I.FB;
//         I.P = I.KP*I.ERROR;
//         
//         I.I = I.I+I.KI*I.LAST_ERROR*I.h;
//         I.I = sat(I.I,0,P1.PRD*0.85);
//         
//         P1.CMP = sat(I.I+I.P,0,P1.PRD*0.85);
//         
//         I.LAST_ERROR = I.ERROR;    
//     }
// if (P1.CNT >= 0 && P1.CNT <= P1.CMP)
//     {
//         y[2] = 1;
//     }
//     else
//     {
//         y[2] = 0;
//     }
    
    y[0]  = carrier_wave(&P1);
    y[1]  = Out.y;
    y[2]  = Out.CMP; 
    
    y1[0] = carrier_wave(&P2);
    y1[1] = Out.y;
    y1[2] = Out.CMP;  
}

int carrier_wave(struct P* P_temp)
{
    if (P_temp->DIR == 0 )
    {
        P_temp->CNT ++;
    }
    if (P_temp->DIR == 1 )
    {
        P_temp->CNT--;
    }
    if (P_temp->CNT == Out.PRD)
    {
        P_temp->DIR = (1-P_temp->DIR);
    }
    else if (P_temp->CNT == 0)
    {
        P_temp->DIR = (1-P_temp->DIR);   
    }   
    if (P_temp->CNT >= 0 && P_temp->CNT <= Out.CMP)
    {
        Out.y = 1;
    }
    else
    {
        Out.y = 0;
    }
    
    Out.CNT = P_temp->CNT;
    return P_temp->CNT;
}
float sat(float input,float min,float max)
{
    float output;
    output = input;
    if (input>=max)
    {
        output = max;
    }
    else if (input<=min)
    {
        output = min;
    }
    return output;
}

#define MDL_UPDATE  /* Change to #undef to remove function */
#if defined(MDL_UPDATE)
  /* Function: mdlUpdate ======================================================
   * Abstract:
   *    This function is called once for every major integration time step.
   *    Discrete states are typically updated here, but this function is useful
   *    for performing any tasks that should only take place once per
   *    integration step.
   */
  static void mdlUpdate(SimStruct *S, int_T tid)
  {
  }
#endif /* MDL_UPDATE */



#define MDL_DERIVATIVES  /* Change to #undef to remove function */
#if defined(MDL_DERIVATIVES)
  /* Function: mdlDerivatives =================================================
   * Abstract:
   *    In this function, you compute the S-function block's derivatives.
   *    The derivatives are placed in the derivative vector, ssGetdX(S).
   */
  static void mdlDerivatives(SimStruct *S)
  {
  }
#endif /* MDL_DERIVATIVES */



/* Function: mdlTerminate =====================================================
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
static void mdlTerminate(SimStruct *S)
{
}


/*=============================*
 * Required S-function trailer *
 *=============================*/

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
