/*
 * bouncing_ball_GT_sf.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "bouncing_ball_GT_sf".
 *
 * Model version              : 12.4
 * Simulink Coder version : 24.2 (R2024b) 21-Jun-2024
 * C source code generated on : Wed Apr 16 18:57:52 2025
 *
 * Target selection: rtwsfcn.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Emulation hardware selection:
 *    Differs from embedded hardware (MATLAB Host)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "bouncing_ball_GT_sf.h"
#include "rtwtypes.h"
#include "bouncing_ball_GT_sf_private.h"
#include "simstruc.h"
#include "fixedpoint.h"
#if defined(RT_MALLOC) || defined(MATLAB_MEX_FILE)

extern void *bouncing_ball_GT_malloc(SimStruct *S);

#endif

#ifndef __RTW_UTFREE__
#if defined (MATLAB_MEX_FILE)

extern void * utMalloc(size_t);
extern void utFree(void *);

#endif
#endif                                 /* #ifndef __RTW_UTFREE__ */

#if defined(MATLAB_MEX_FILE)
#include "rt_nonfinite.c"
#endif

static const char_T *RT_MEMORY_ALLOCATION_ERROR =
  "memory allocation error in generated S-Function";

/* System initialize for root system: '<Root>' */
#define MDL_INITIALIZE_CONDITIONS

static void mdlInitializeConditions(SimStruct *S)
{
  if (ssIsFirstInitCond(S)) {
    X_bouncing_ball_GT_T *_rtX;
    _rtX = ((X_bouncing_ball_GT_T *) ssGetContStates(S));

    /* InitializeConditions for Memory: '<Root>/Memory' */
    ((real_T *)ssGetDWork(S, 0))[0] = 0.0;

    /* InitializeConditions for SecondOrderIntegrator: '<Root>/Second-Order  Integrator' */
    _rtX->Position[0] = 25.0;
    ((int_T *)ssGetDWork(S, 1))[0] = 0;
    ((boolean_T *)ssGetDWork(S, 3))[0] = true;
  } else {
    X_bouncing_ball_GT_T *_rtX;
    _rtX = ((X_bouncing_ball_GT_T *) ssGetContStates(S));

    /* InitializeConditions for Memory: '<Root>/Memory' */
    ((real_T *)ssGetDWork(S, 0))[0] = 0.0;

    /* InitializeConditions for SecondOrderIntegrator: '<Root>/Second-Order  Integrator' */
    _rtX->Position[0] = 25.0;
    ((int_T *)ssGetDWork(S, 1))[0] = 0;
    ((boolean_T *)ssGetDWork(S, 3))[0] = true;
  }
}

/* Start for root system: '<Root>' */
#define MDL_START

static void mdlStart(SimStruct *S)
{
  /* instance underlying S-Function data */
#if defined(RT_MALLOC) || defined(MATLAB_MEX_FILE)
#if defined(MATLAB_MEX_FILE)

  /* non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* Check for invalid switching between solver types */
  if (ssIsVariableStepSolver(S)) {
    ssSetErrorStatus(S, "This Simulink Coder generated "
                     "S-Function cannot be used in a simulation with "
                     "a solver type of variable-step "
                     "because this S-Function was created from a model with "
                     "solver type of fixed-step and it has continuous time blocks. "
                     "See the Solver page of the simulation parameters dialog.");
    return;
  }

  if (fabs(ssGetFixedStepSize(S) - 0.5) > mxGetEps()*100*0.5) {
    ssSetErrorStatus(S, "This Simulink Coder generated "
                     "S-Function cannot be used in a simulation with "
                     "the current fixed step size "
                     "because this S-Function was created from a model with "
                     "a fixed step size of 0.5 and had both "
                     "continuous blocks and discrete blocks running at this rate. "
                     "See the Solver page of the simulation parameters dialog.");
    return;
  }

#endif

  bouncing_ball_GT_malloc(S);
  if (ssGetErrorStatus(S) != (NULL) ) {
    return;
  }

#endif

  {
    B_bouncing_ball_GT_T *_rtB;
    _rtB = ((B_bouncing_ball_GT_T *) ssGetLocalBlockIO(S));

    /* Start for InitialCondition: '<Root>/Initial Velocity (IC) ' */
    ((boolean_T *)ssGetDWork(S, 2))[0] = true;
  }
}

/* Outputs for root system: '<Root>' */
static void mdlOutputs(SimStruct *S, int_T tid)
{
  B_bouncing_ball_GT_T *_rtB;
  X_bouncing_ball_GT_T *_rtX;
  boolean_T tmp;
  boolean_T tmp_0;
  _rtX = ((X_bouncing_ball_GT_T *) ssGetContStates(S));
  _rtB = ((B_bouncing_ball_GT_T *) ssGetLocalBlockIO(S));
  tmp = ssIsSampleHit(S, 1, 0);
  if (tmp) {
    /* {S!d44}InitialCondition: '<Root>/Initial Velocity (IC) ' */
    if (((boolean_T *)ssGetDWork(S, 2))[0]) {
      ((boolean_T *)ssGetDWork(S, 2))[0] = false;

      /* {S!d40}InitialCondition: '<Root>/Initial Velocity (IC) ' */
      _rtB->InitialVelocityIC = 0.0;
    } else {
      /* {S!d42}InitialCondition: '<Root>/Initial Velocity (IC) ' incorporates:
       *  Gain: '<Root>/Coefficient of  Restitution'
       *  Memory: '<Root>/Memory'
       */
      _rtB->InitialVelocityIC = -0.8 * ((real_T *)ssGetDWork(S, 0))[0];
    }

    /* {E!d44}End of InitialCondition: '<Root>/Initial Velocity (IC) ' */
  }

  tmp_0 = 1;
  if (tmp_0) {
    /* {S!d50}SecondOrderIntegrator: '<Root>/Second-Order  Integrator' */
    if (((boolean_T *)ssGetDWork(S, 3))[0]) {
      _rtX->Position[1] = _rtB->InitialVelocityIC;
    }

    if (ssIsModeUpdateTimeStep(S)) {
      switch (((int_T *)ssGetDWork(S, 1))[0]) {
       case 0:
        if (_rtX->Position[0] <= 0.0) {
          _rtX->Position[0] = 0.0;
          if (_rtX->Position[1] > 0.0) {
            ((int_T *)ssGetDWork(S, 1))[0] = 0;
          } else {
            _rtX->Position[1] = 0.0;
            ((int_T *)ssGetDWork(S, 1))[0] = 1;
          }

          if (_rtB->InitialVelocityIC > 0.0) {
            _rtX->Position[1] = _rtB->InitialVelocityIC;
            ((int_T *)ssGetDWork(S, 1))[0] = 0;
          }

          ssSetBlockStateForSolverChangedAtMajorStep(S);
        }

        if (_rtX->Position[0] >= (rtInf)) {
          _rtX->Position[0] = (rtInf);
          if (_rtX->Position[1] < 0.0) {
            ((int_T *)ssGetDWork(S, 1))[0] = 0;
          } else {
            _rtX->Position[1] = 0.0;
            ((int_T *)ssGetDWork(S, 1))[0] = 2;
          }

          if (_rtB->InitialVelocityIC < 0.0) {
            _rtX->Position[1] = _rtB->InitialVelocityIC;
            ((int_T *)ssGetDWork(S, 1))[0] = 0;
          }

          ssSetBlockStateForSolverChangedAtMajorStep(S);
        }
        break;

       case 1:
        if (_rtX->Position[0] > 0.0) {
          if (_rtX->Position[0] >= (rtInf)) {
            ((int_T *)ssGetDWork(S, 1))[0] = 2;
            _rtX->Position[0] = (rtInf);
          } else {
            ((int_T *)ssGetDWork(S, 1))[0] = 0;
          }
        } else {
          _rtX->Position[0] = 0.0;
          _rtX->Position[1] = 0.0;
        }
        break;

       case 2:
        if (_rtX->Position[0] < (rtInf)) {
          if (_rtX->Position[0] <= 0.0) {
            ((int_T *)ssGetDWork(S, 1))[0] = 1;
            _rtX->Position[0] = 0.0;
          } else {
            ((int_T *)ssGetDWork(S, 1))[0] = 0;
          }
        } else {
          _rtX->Position[0] = (rtInf);
          _rtX->Position[1] = 0.0;
        }
        break;
      }
    }

    if (_rtX->Position[0] < 0.0) {
      /* {S!d46}SecondOrderIntegrator: '<Root>/Second-Order  Integrator' */
      _rtB->Position = 0.0;
    } else {
      /* {S!d48}SecondOrderIntegrator: '<Root>/Second-Order  Integrator' */
      _rtB->Position = _rtX->Position[0];
    }

    /* {S!d52}SecondOrderIntegrator: '<Root>/Second-Order  Integrator' */
    _rtB->Velocity = _rtX->Position[1];
  }

  if (tmp) {
  }

  if (tmp_0) {
  }

  UNUSED_PARAMETER(tid);
}

/* Update for root system: '<Root>' */
#define MDL_UPDATE

static void mdlUpdate(SimStruct *S, int_T tid)
{
  B_bouncing_ball_GT_T *_rtB;
  int32_T uMode;
  _rtB = ((B_bouncing_ball_GT_T *) ssGetLocalBlockIO(S));
  if (ssIsSampleHit(S, 1, 0)) {
    /* {S!d60}Update for Memory: '<Root>/Memory' */
    ((real_T *)ssGetDWork(S, 0))[0] = _rtB->Velocity;
  }

  if (1) {
    /* {S!d62}Update for SecondOrderIntegrator: '<Root>/Second-Order  Integrator' */
    ((boolean_T *)ssGetDWork(S, 3))[0] = false;
    uMode = ((int_T *)ssGetDWork(S, 1))[0];
    if (((int_T *)ssGetDWork(S, 1))[0] == 2) {
      uMode = 0;
    }

    if (((int_T *)ssGetDWork(S, 1))[0] != uMode) {
      ((int_T *)ssGetDWork(S, 1))[0] = uMode;
      ssSetBlockStateForSolverChangedAtMajorStep(S);
    }

    /* {E!d62}End of Update for SecondOrderIntegrator: '<Root>/Second-Order  Integrator' */
  }

  UNUSED_PARAMETER(tid);
}

/* Derivatives for root system: '<Root>' */
#define MDL_DERIVATIVES

static void mdlDerivatives(SimStruct *S)
{
  XDot_bouncing_ball_GT_T *_rtXdot;
  X_bouncing_ball_GT_T *_rtX;
  _rtXdot = ((XDot_bouncing_ball_GT_T *) ssGetdX(S));
  _rtX = ((X_bouncing_ball_GT_T *) ssGetContStates(S));

  /* {S!d64}Derivatives for SecondOrderIntegrator: '<Root>/Second-Order  Integrator' incorporates:
   *  Constant: '<Root>/Gravitational acceleration'
   */
  switch (((int_T *)ssGetDWork(S, 1))[0]) {
   case 0:
    _rtXdot->Position[0] = _rtX->Position[1];
    _rtXdot->Position[1] = -9.81;
    break;

   case 1:
    _rtXdot->Position[0] = 0.0;
    _rtXdot->Position[1] = 0.0;
    break;

   case 2:
    _rtXdot->Position[0] = 0.0;
    _rtXdot->Position[1] = 0.0;
    break;
  }

  /* {E!d64}End of Derivatives for SecondOrderIntegrator: '<Root>/Second-Order  Integrator' */
}

/* Termination for root system: '<Root>' */
static void mdlTerminate(SimStruct *S)
{
  UNUSED_PARAMETER(S);

#if defined(RT_MALLOC) || defined(MATLAB_MEX_FILE)

  if (ssGetUserData(S) != (NULL) ) {
    rt_FREE(ssGetLocalBlockIO(S));
  }

  rt_FREE(ssGetUserData(S));

#endif

}

#if defined(RT_MALLOC) || defined(MATLAB_MEX_FILE)
#include "bouncing_ball_GT_mid.h"
#endif

/* Function to initialize sizes. */
static void mdlInitializeSizes(SimStruct *S)
{
  ssSetNumSampleTimes(S, 2);           /* Number of sample times */
  ssSetNumContStates(S, 2);            /* Number of continuous states */
  ssSetNumPeriodicContStates(S, 0);   /* Number of periodic continuous states */
  ssSetNumNonsampledZCs(S, 0);         /* Number of nonsampled ZCs */

  /* Number of output ports */
  if (!ssSetNumOutputPorts(S, 0))
    return;

  /* Number of input ports */
  if (!ssSetNumInputPorts(S, 0))
    return;
  ssSetRTWGeneratedSFcn(S, 1);         /* Generated S-function */

  /* DWork */
  if (!ssSetNumDWork(S, 4)) {
    return;
  }

  /* '<Root>/Memory': PreviousInput */
  ssSetDWorkName(S, 0, "DWORK0");
  ssSetDWorkWidth(S, 0, 1);

  /* '<Root>/Second-Order  Integrator': MODE */
  ssSetDWorkName(S, 1, "DWORK1");
  ssSetDWorkWidth(S, 1, 1);
  ssSetDWorkDataType(S, 1, SS_INTEGER);

  /* '<Root>/Initial Velocity (IC) ': FirstOutputTime */
  ssSetDWorkName(S, 2, "DWORK2");
  ssSetDWorkWidth(S, 2, 1);
  ssSetDWorkDataType(S, 2, SS_BOOLEAN);

  /* '<Root>/Second-Order  Integrator': DWORK1 */
  ssSetDWorkName(S, 3, "DWORK3");
  ssSetDWorkWidth(S, 3, 1);
  ssSetDWorkDataType(S, 3, SS_BOOLEAN);

  /* Tunable Parameters */
  ssSetNumSFcnParams(S, 0);

  /* Number of expected parameters */
#if defined(MATLAB_MEX_FILE)

  if (ssGetNumSFcnParams(S) == ssGetSFcnParamsCount(S)) {

#if defined(MDL_CHECK_PARAMETERS)

    mdlCheckParameters(S);

#endif                                 /* MDL_CHECK_PARAMETERS */

    if (ssGetErrorStatus(S) != (NULL) ) {
      return;
    }
  } else {
    return;                /* Parameter mismatch will be reported by Simulink */
  }

#endif                                 /* MATLAB_MEX_FILE */

  /* Options */
  ssSetOptions(S, (SS_OPTION_RUNTIME_EXCEPTION_FREE_CODE |
                   SS_OPTION_PORT_SAMPLE_TIMES_ASSIGNED ));

#if SS_SFCN_FOR_SIM

  {
    ssSupportsMultipleExecInstances(S, false);
    ssRegisterMsgForNotSupportingMultiExecInst(S,
      "<diag_root><diag id=\"Simulink:blocks:ImplicitIterSS_SignalViewNotSupportedInside\" pr=\"d\"><arguments><arg type=\"numeric\">1</arg><arg type=\"encoded\">YgBvAHUAbgBjAGkAbgBnAF8AYgBhAGwAbABfAEcAVAAvAFMAZQBjAG8AbgBkAC0ATwByAGQAZQByACAAIABJAG4AdABlAGcAcgBhAHQAbwByAAAA</arg><arg type=\"encoded\">PABfAF8AaQBpAFMAUwBfAF8APgA8AC8AXwBfAGkAaQBTAFMAXwBfAD4AAAA=</arg><arg type=\"encoded\">PABfAF8AaQB0AGUAcgBCAGwAawBfAF8APgA8AC8AXwBfAGkAdABlAHIAQgBsAGsAXwBfAD4AAAA=</arg></arguments><hs><h>AAAAAAHQc0Ag</h></hs></diag></diag_root>");
    ssHasStateInsideForEachSS(S, false);
  }

#endif

}

/* Function to initialize sample times. */
static void mdlInitializeSampleTimes(SimStruct *S)
{
  /* task periods */
  ssSetSampleTime(S, 0, 0.0);
  ssSetSampleTime(S, 1, 0.5);

  /* task offsets */
  ssSetOffsetTime(S, 0, 0.0);
  ssSetOffsetTime(S, 1, 0.0);
}

#if defined(MATLAB_MEX_FILE)
#include "fixedpoint.c"
#include "simulink.c"
#else
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME                bouncing_ball_GT_sf
#include "cg_sfun.h"
#endif                                 /* defined(MATLAB_MEX_FILE) */
