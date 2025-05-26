/*
 * bouncing_ball_generated.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "bouncing_ball_generated".
 *
 * Model version              : 1.1
 * Simulink Coder version : 24.2 (R2024b) 21-Jun-2024
 * C source code generated on : Wed Apr 16 16:50:14 2025
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "bouncing_ball_generated.h"
#include "rtwtypes.h"
#include "bouncing_ball_generated_private.h"
#include <string.h>

/* Block signals (default storage) */
B_bouncing_ball_generated_T bouncing_ball_generated_B;

/* Continuous states */
X_bouncing_ball_generated_T bouncing_ball_generated_X;

/* Disabled State Vector */
XDis_bouncing_ball_generated_T bouncing_ball_generated_XDis;

/* Block states (default storage) */
DW_bouncing_ball_generated_T bouncing_ball_generated_DW;

/* Real-time model */
static RT_MODEL_bouncing_ball_genera_T bouncing_ball_generated_M_;
RT_MODEL_bouncing_ball_genera_T *const bouncing_ball_generated_M =
  &bouncing_ball_generated_M_;

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  bouncing_ball_generated_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  bouncing_ball_generated_step();
  bouncing_ball_generated_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  bouncing_ball_generated_step();
  bouncing_ball_generated_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void bouncing_ball_generated_step(void)
{
  boolean_T tmp;
  if (rtmIsMajorTimeStep(bouncing_ball_generated_M)) {
    /* set solver stop time */
    if (!(bouncing_ball_generated_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&bouncing_ball_generated_M->solverInfo,
                            ((bouncing_ball_generated_M->Timing.clockTickH0 + 1)
        * bouncing_ball_generated_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&bouncing_ball_generated_M->solverInfo,
                            ((bouncing_ball_generated_M->Timing.clockTick0 + 1) *
        bouncing_ball_generated_M->Timing.stepSize0 +
        bouncing_ball_generated_M->Timing.clockTickH0 *
        bouncing_ball_generated_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(bouncing_ball_generated_M)) {
    bouncing_ball_generated_M->Timing.t[0] = rtsiGetT
      (&bouncing_ball_generated_M->solverInfo);
  }

  tmp = rtmIsMajorTimeStep(bouncing_ball_generated_M);
  if (tmp) {
    /* InitialCondition: '<Root>/IC' */
    if (bouncing_ball_generated_DW.IC_FirstOutputTime) {
      bouncing_ball_generated_DW.IC_FirstOutputTime = false;

      /* InitialCondition: '<Root>/IC' */
      bouncing_ball_generated_B.IC = bouncing_ball_generated_P.IC_Value;
    } else {
      /* InitialCondition: '<Root>/IC' incorporates:
       *  Gain: '<Root>/Gain'
       *  Memory: '<Root>/Memory'
       */
      bouncing_ball_generated_B.IC = bouncing_ball_generated_P.Gain_Gain *
        bouncing_ball_generated_DW.Memory_PreviousInput;
    }

    /* End of InitialCondition: '<Root>/IC' */
  }

  /* SecondOrderIntegrator: '<Root>/SecondOrderIntegrator' */
  if (bouncing_ball_generated_DW.SecondOrderIntegrator_DWORK1) {
    bouncing_ball_generated_X.SecondOrderIntegrator_CSTATE[1] =
      bouncing_ball_generated_B.IC;
  }

  /* SecondOrderIntegrator: '<Root>/SecondOrderIntegrator' */
  bouncing_ball_generated_B.SecondOrderIntegrator_o1 =
    bouncing_ball_generated_X.SecondOrderIntegrator_CSTATE[0];

  /* SecondOrderIntegrator: '<Root>/SecondOrderIntegrator' */
  bouncing_ball_generated_B.SecondOrderIntegrator_o2 =
    bouncing_ball_generated_X.SecondOrderIntegrator_CSTATE[1];
  if (tmp) {
  }

  if (rtmIsMajorTimeStep(bouncing_ball_generated_M)) {
    /* Matfile logging */
    rt_UpdateTXYLogVars(bouncing_ball_generated_M->rtwLogInfo,
                        (bouncing_ball_generated_M->Timing.t));
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(bouncing_ball_generated_M)) {
    if (rtmIsMajorTimeStep(bouncing_ball_generated_M)) {
      /* Update for Memory: '<Root>/Memory' */
      bouncing_ball_generated_DW.Memory_PreviousInput =
        bouncing_ball_generated_B.SecondOrderIntegrator_o2;
    }

    /* Update for SecondOrderIntegrator: '<Root>/SecondOrderIntegrator' */
    bouncing_ball_generated_DW.SecondOrderIntegrator_DWORK1 = false;
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(bouncing_ball_generated_M)) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal(bouncing_ball_generated_M)!=-1) &&
          !((rtmGetTFinal(bouncing_ball_generated_M)-
             (((bouncing_ball_generated_M->Timing.clockTick1+
                bouncing_ball_generated_M->Timing.clockTickH1* 4294967296.0)) *
              0.2)) > (((bouncing_ball_generated_M->Timing.clockTick1+
                         bouncing_ball_generated_M->Timing.clockTickH1*
                         4294967296.0)) * 0.2) * (DBL_EPSILON))) {
        rtmSetErrorStatus(bouncing_ball_generated_M, "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&bouncing_ball_generated_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++bouncing_ball_generated_M->Timing.clockTick0)) {
      ++bouncing_ball_generated_M->Timing.clockTickH0;
    }

    bouncing_ball_generated_M->Timing.t[0] = rtsiGetSolverStopTime
      (&bouncing_ball_generated_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.2s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.2, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      bouncing_ball_generated_M->Timing.clockTick1++;
      if (!bouncing_ball_generated_M->Timing.clockTick1) {
        bouncing_ball_generated_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void bouncing_ball_generated_derivatives(void)
{
  XDot_bouncing_ball_generated_T *_rtXdot;
  _rtXdot = ((XDot_bouncing_ball_generated_T *)
             bouncing_ball_generated_M->derivs);

  /* Derivatives for SecondOrderIntegrator: '<Root>/SecondOrderIntegrator' incorporates:
   *  Constant: '<Root>/Constant'
   */
  if (bouncing_ball_generated_DW.SecondOrderIntegrator_MODE == 0) {
    _rtXdot->SecondOrderIntegrator_CSTATE[0] =
      bouncing_ball_generated_X.SecondOrderIntegrator_CSTATE[1];
    _rtXdot->SecondOrderIntegrator_CSTATE[1] =
      bouncing_ball_generated_P.Constant_Value;
  }

  /* End of Derivatives for SecondOrderIntegrator: '<Root>/SecondOrderIntegrator' */
}

/* Model initialize function */
void bouncing_ball_generated_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)bouncing_ball_generated_M, 0,
                sizeof(RT_MODEL_bouncing_ball_genera_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&bouncing_ball_generated_M->solverInfo,
                          &bouncing_ball_generated_M->Timing.simTimeStep);
    rtsiSetTPtr(&bouncing_ball_generated_M->solverInfo, &rtmGetTPtr
                (bouncing_ball_generated_M));
    rtsiSetStepSizePtr(&bouncing_ball_generated_M->solverInfo,
                       &bouncing_ball_generated_M->Timing.stepSize0);
    rtsiSetdXPtr(&bouncing_ball_generated_M->solverInfo,
                 &bouncing_ball_generated_M->derivs);
    rtsiSetContStatesPtr(&bouncing_ball_generated_M->solverInfo, (real_T **)
                         &bouncing_ball_generated_M->contStates);
    rtsiSetNumContStatesPtr(&bouncing_ball_generated_M->solverInfo,
      &bouncing_ball_generated_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&bouncing_ball_generated_M->solverInfo,
      &bouncing_ball_generated_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&bouncing_ball_generated_M->solverInfo,
      &bouncing_ball_generated_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&bouncing_ball_generated_M->solverInfo,
      &bouncing_ball_generated_M->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&bouncing_ball_generated_M->solverInfo,
      (boolean_T**) &bouncing_ball_generated_M->contStateDisabled);
    rtsiSetErrorStatusPtr(&bouncing_ball_generated_M->solverInfo,
                          (&rtmGetErrorStatus(bouncing_ball_generated_M)));
    rtsiSetRTModelPtr(&bouncing_ball_generated_M->solverInfo,
                      bouncing_ball_generated_M);
  }

  rtsiSetSimTimeStep(&bouncing_ball_generated_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&bouncing_ball_generated_M->solverInfo,
    false);
  rtsiSetIsContModeFrozen(&bouncing_ball_generated_M->solverInfo, false);
  bouncing_ball_generated_M->intgData.y = bouncing_ball_generated_M->odeY;
  bouncing_ball_generated_M->intgData.f[0] = bouncing_ball_generated_M->odeF[0];
  bouncing_ball_generated_M->intgData.f[1] = bouncing_ball_generated_M->odeF[1];
  bouncing_ball_generated_M->intgData.f[2] = bouncing_ball_generated_M->odeF[2];
  bouncing_ball_generated_M->contStates = ((X_bouncing_ball_generated_T *)
    &bouncing_ball_generated_X);
  bouncing_ball_generated_M->contStateDisabled =
    ((XDis_bouncing_ball_generated_T *) &bouncing_ball_generated_XDis);
  bouncing_ball_generated_M->Timing.tStart = (0.0);
  rtsiSetSolverData(&bouncing_ball_generated_M->solverInfo, (void *)
                    &bouncing_ball_generated_M->intgData);
  rtsiSetSolverName(&bouncing_ball_generated_M->solverInfo,"ode3");
  rtmSetTPtr(bouncing_ball_generated_M,
             &bouncing_ball_generated_M->Timing.tArray[0]);
  rtmSetTFinal(bouncing_ball_generated_M, 10.0);
  bouncing_ball_generated_M->Timing.stepSize0 = 0.2;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (NULL);
    bouncing_ball_generated_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(bouncing_ball_generated_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(bouncing_ball_generated_M->rtwLogInfo, (NULL));
    rtliSetLogT(bouncing_ball_generated_M->rtwLogInfo, "tout");
    rtliSetLogX(bouncing_ball_generated_M->rtwLogInfo, "");
    rtliSetLogXFinal(bouncing_ball_generated_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(bouncing_ball_generated_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(bouncing_ball_generated_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(bouncing_ball_generated_M->rtwLogInfo, 0);
    rtliSetLogDecimation(bouncing_ball_generated_M->rtwLogInfo, 1);
    rtliSetLogY(bouncing_ball_generated_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(bouncing_ball_generated_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(bouncing_ball_generated_M->rtwLogInfo, (NULL));
  }

  /* block I/O */
  (void) memset(((void *) &bouncing_ball_generated_B), 0,
                sizeof(B_bouncing_ball_generated_T));

  /* states (continuous) */
  {
    (void) memset((void *)&bouncing_ball_generated_X, 0,
                  sizeof(X_bouncing_ball_generated_T));
  }

  /* disabled states */
  {
    (void) memset((void *)&bouncing_ball_generated_XDis, 0,
                  sizeof(XDis_bouncing_ball_generated_T));
  }

  /* states (dwork) */
  (void) memset((void *)&bouncing_ball_generated_DW, 0,
                sizeof(DW_bouncing_ball_generated_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(bouncing_ball_generated_M->rtwLogInfo, 0.0,
    rtmGetTFinal(bouncing_ball_generated_M),
    bouncing_ball_generated_M->Timing.stepSize0, (&rtmGetErrorStatus
    (bouncing_ball_generated_M)));

  /* Start for InitialCondition: '<Root>/IC' */
  bouncing_ball_generated_DW.IC_FirstOutputTime = true;

  /* InitializeConditions for Memory: '<Root>/Memory' */
  bouncing_ball_generated_DW.Memory_PreviousInput =
    bouncing_ball_generated_P.Memory_InitialCondition;

  /* InitializeConditions for SecondOrderIntegrator: '<Root>/SecondOrderIntegrator' */
  bouncing_ball_generated_X.SecondOrderIntegrator_CSTATE[0] =
    bouncing_ball_generated_P.SecondOrderIntegrator_ICX;
  bouncing_ball_generated_DW.SecondOrderIntegrator_MODE = 0;
  bouncing_ball_generated_DW.SecondOrderIntegrator_DWORK1 = true;
}

/* Model terminate function */
void bouncing_ball_generated_terminate(void)
{
  /* (no terminate code required) */
}
