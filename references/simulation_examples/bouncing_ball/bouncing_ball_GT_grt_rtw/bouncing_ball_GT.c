/*
 * bouncing_ball_GT.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "bouncing_ball_GT".
 *
 * Model version              : 12.4
 * Simulink Coder version : 24.2 (R2024b) 21-Jun-2024
 * C source code generated on : Wed Apr 16 17:00:43 2025
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Emulation hardware selection:
 *    Differs from embedded hardware (MATLAB Host)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "bouncing_ball_GT.h"
#include "rtwtypes.h"
#include "bouncing_ball_GT_private.h"
#include <string.h>
#include "rt_nonfinite.h"

/* Block signals (default storage) */
B_bouncing_ball_GT_T bouncing_ball_GT_B;

/* Continuous states */
X_bouncing_ball_GT_T bouncing_ball_GT_X;

/* Disabled State Vector */
XDis_bouncing_ball_GT_T bouncing_ball_GT_XDis;

/* Block states (default storage) */
DW_bouncing_ball_GT_T bouncing_ball_GT_DW;

/* Real-time model */
static RT_MODEL_bouncing_ball_GT_T bouncing_ball_GT_M_;
RT_MODEL_bouncing_ball_GT_T *const bouncing_ball_GT_M = &bouncing_ball_GT_M_;

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
  bouncing_ball_GT_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  bouncing_ball_GT_step();
  bouncing_ball_GT_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  bouncing_ball_GT_step();
  bouncing_ball_GT_derivatives();

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
void bouncing_ball_GT_step(void)
{
  if (rtmIsMajorTimeStep(bouncing_ball_GT_M)) {
    /* set solver stop time */
    if (!(bouncing_ball_GT_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&bouncing_ball_GT_M->solverInfo,
                            ((bouncing_ball_GT_M->Timing.clockTickH0 + 1) *
        bouncing_ball_GT_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&bouncing_ball_GT_M->solverInfo,
                            ((bouncing_ball_GT_M->Timing.clockTick0 + 1) *
        bouncing_ball_GT_M->Timing.stepSize0 +
        bouncing_ball_GT_M->Timing.clockTickH0 *
        bouncing_ball_GT_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(bouncing_ball_GT_M)) {
    bouncing_ball_GT_M->Timing.t[0] = rtsiGetT(&bouncing_ball_GT_M->solverInfo);
  }

  {
    boolean_T tmp;
    tmp = rtmIsMajorTimeStep(bouncing_ball_GT_M);
    if (tmp) {
      /* InitialCondition: '<Root>/Initial Velocity (IC) ' */
      if (bouncing_ball_GT_DW.InitialVelocityIC_FirstOutputTi) {
        bouncing_ball_GT_DW.InitialVelocityIC_FirstOutputTi = false;

        /* InitialCondition: '<Root>/Initial Velocity (IC) ' */
        bouncing_ball_GT_B.InitialVelocityIC =
          bouncing_ball_GT_P.InitialVelocityIC_Value;
      } else {
        /* InitialCondition: '<Root>/Initial Velocity (IC) ' incorporates:
         *  Gain: '<Root>/Coefficient of  Restitution'
         *  Memory: '<Root>/Memory'
         */
        bouncing_ball_GT_B.InitialVelocityIC =
          bouncing_ball_GT_P.CoefficientofRestitution_Gain *
          bouncing_ball_GT_DW.Memory_PreviousInput;
      }

      /* End of InitialCondition: '<Root>/Initial Velocity (IC) ' */
    }

    /* SecondOrderIntegrator: '<Root>/Second-Order  Integrator' */
    if (bouncing_ball_GT_DW.SecondOrderIntegrator_DWORK1) {
      bouncing_ball_GT_X.Position[1] = bouncing_ball_GT_B.InitialVelocityIC;
    }

    if (rtsiIsModeUpdateTimeStep(&bouncing_ball_GT_M->solverInfo)) {
      switch (bouncing_ball_GT_DW.SecondOrderIntegrator_MODE) {
       case 0:
        if (bouncing_ball_GT_X.Position[0] <=
            bouncing_ball_GT_P.SecondOrderIntegrator_LowerLimi) {
          bouncing_ball_GT_X.Position[0] =
            bouncing_ball_GT_P.SecondOrderIntegrator_LowerLimi;
          if (bouncing_ball_GT_X.Position[1] > 0.0) {
            bouncing_ball_GT_DW.SecondOrderIntegrator_MODE = 0;
          } else {
            bouncing_ball_GT_X.Position[1] = 0.0;
            bouncing_ball_GT_DW.SecondOrderIntegrator_MODE = 1;
          }

          if (bouncing_ball_GT_B.InitialVelocityIC > 0.0) {
            bouncing_ball_GT_X.Position[1] =
              bouncing_ball_GT_B.InitialVelocityIC;
            bouncing_ball_GT_DW.SecondOrderIntegrator_MODE = 0;
          }

          rtsiSetBlockStateForSolverChangedAtMajorStep
            (&bouncing_ball_GT_M->solverInfo, true);
        }

        if (bouncing_ball_GT_X.Position[0] >=
            bouncing_ball_GT_P.SecondOrderIntegrator_UpperLimi) {
          bouncing_ball_GT_X.Position[0] =
            bouncing_ball_GT_P.SecondOrderIntegrator_UpperLimi;
          if (bouncing_ball_GT_X.Position[1] < 0.0) {
            bouncing_ball_GT_DW.SecondOrderIntegrator_MODE = 0;
          } else {
            bouncing_ball_GT_X.Position[1] = 0.0;
            bouncing_ball_GT_DW.SecondOrderIntegrator_MODE = 2;
          }

          if (bouncing_ball_GT_B.InitialVelocityIC < 0.0) {
            bouncing_ball_GT_X.Position[1] =
              bouncing_ball_GT_B.InitialVelocityIC;
            bouncing_ball_GT_DW.SecondOrderIntegrator_MODE = 0;
          }

          rtsiSetBlockStateForSolverChangedAtMajorStep
            (&bouncing_ball_GT_M->solverInfo, true);
        }
        break;

       case 1:
        if (bouncing_ball_GT_X.Position[0] >
            bouncing_ball_GT_P.SecondOrderIntegrator_LowerLimi) {
          if (bouncing_ball_GT_X.Position[0] >=
              bouncing_ball_GT_P.SecondOrderIntegrator_UpperLimi) {
            bouncing_ball_GT_DW.SecondOrderIntegrator_MODE = 2;
            bouncing_ball_GT_X.Position[0] =
              bouncing_ball_GT_P.SecondOrderIntegrator_UpperLimi;
          } else {
            bouncing_ball_GT_DW.SecondOrderIntegrator_MODE = 0;
          }
        } else {
          bouncing_ball_GT_X.Position[0] =
            bouncing_ball_GT_P.SecondOrderIntegrator_LowerLimi;
          bouncing_ball_GT_X.Position[1] = 0.0;
        }
        break;

       case 2:
        if (bouncing_ball_GT_X.Position[0] <
            bouncing_ball_GT_P.SecondOrderIntegrator_UpperLimi) {
          if (bouncing_ball_GT_X.Position[0] <=
              bouncing_ball_GT_P.SecondOrderIntegrator_LowerLimi) {
            bouncing_ball_GT_DW.SecondOrderIntegrator_MODE = 1;
            bouncing_ball_GT_X.Position[0] =
              bouncing_ball_GT_P.SecondOrderIntegrator_LowerLimi;
          } else {
            bouncing_ball_GT_DW.SecondOrderIntegrator_MODE = 0;
          }
        } else {
          bouncing_ball_GT_X.Position[0] =
            bouncing_ball_GT_P.SecondOrderIntegrator_UpperLimi;
          bouncing_ball_GT_X.Position[1] = 0.0;
        }
        break;
      }
    }

    if (bouncing_ball_GT_X.Position[0] <
        bouncing_ball_GT_P.SecondOrderIntegrator_LowerLimi) {
      /* SecondOrderIntegrator: '<Root>/Second-Order  Integrator' */
      bouncing_ball_GT_B.Position =
        bouncing_ball_GT_P.SecondOrderIntegrator_LowerLimi;
    } else if (bouncing_ball_GT_X.Position[0] >
               bouncing_ball_GT_P.SecondOrderIntegrator_UpperLimi) {
      /* SecondOrderIntegrator: '<Root>/Second-Order  Integrator' */
      bouncing_ball_GT_B.Position =
        bouncing_ball_GT_P.SecondOrderIntegrator_UpperLimi;
    } else {
      /* SecondOrderIntegrator: '<Root>/Second-Order  Integrator' */
      bouncing_ball_GT_B.Position = bouncing_ball_GT_X.Position[0];
    }

    /* SecondOrderIntegrator: '<Root>/Second-Order  Integrator' */
    bouncing_ball_GT_B.Velocity = bouncing_ball_GT_X.Position[1];
    if (tmp) {
    }
  }

  if (rtmIsMajorTimeStep(bouncing_ball_GT_M)) {
    /* Matfile logging */
    rt_UpdateTXYLogVars(bouncing_ball_GT_M->rtwLogInfo,
                        (bouncing_ball_GT_M->Timing.t));
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(bouncing_ball_GT_M)) {
    int32_T uMode;
    if (rtmIsMajorTimeStep(bouncing_ball_GT_M)) {
      /* Update for Memory: '<Root>/Memory' */
      bouncing_ball_GT_DW.Memory_PreviousInput = bouncing_ball_GT_B.Velocity;
    }

    /* Update for SecondOrderIntegrator: '<Root>/Second-Order  Integrator' incorporates:
     *  Constant: '<Root>/Gravitational acceleration'
     */
    bouncing_ball_GT_DW.SecondOrderIntegrator_DWORK1 = false;
    uMode = bouncing_ball_GT_DW.SecondOrderIntegrator_MODE;
    if (((bouncing_ball_GT_DW.SecondOrderIntegrator_MODE == 1) &&
         (bouncing_ball_GT_P.Gravitationalacceleration_Value > 0.0)) ||
        ((bouncing_ball_GT_DW.SecondOrderIntegrator_MODE == 2) &&
         (bouncing_ball_GT_P.Gravitationalacceleration_Value < 0.0))) {
      uMode = 0;
    }

    if (bouncing_ball_GT_DW.SecondOrderIntegrator_MODE != uMode) {
      bouncing_ball_GT_DW.SecondOrderIntegrator_MODE = uMode;
      rtsiSetBlockStateForSolverChangedAtMajorStep
        (&bouncing_ball_GT_M->solverInfo, true);
    }

    /* End of Update for SecondOrderIntegrator: '<Root>/Second-Order  Integrator' */
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(bouncing_ball_GT_M)) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal(bouncing_ball_GT_M)!=-1) &&
          !((rtmGetTFinal(bouncing_ball_GT_M)-
             (((bouncing_ball_GT_M->Timing.clockTick1+
                bouncing_ball_GT_M->Timing.clockTickH1* 4294967296.0)) * 0.5)) >
            (((bouncing_ball_GT_M->Timing.clockTick1+
               bouncing_ball_GT_M->Timing.clockTickH1* 4294967296.0)) * 0.5) *
            (DBL_EPSILON))) {
        rtmSetErrorStatus(bouncing_ball_GT_M, "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&bouncing_ball_GT_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++bouncing_ball_GT_M->Timing.clockTick0)) {
      ++bouncing_ball_GT_M->Timing.clockTickH0;
    }

    bouncing_ball_GT_M->Timing.t[0] = rtsiGetSolverStopTime
      (&bouncing_ball_GT_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.5s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.5, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      bouncing_ball_GT_M->Timing.clockTick1++;
      if (!bouncing_ball_GT_M->Timing.clockTick1) {
        bouncing_ball_GT_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void bouncing_ball_GT_derivatives(void)
{
  XDot_bouncing_ball_GT_T *_rtXdot;
  _rtXdot = ((XDot_bouncing_ball_GT_T *) bouncing_ball_GT_M->derivs);

  /* Derivatives for SecondOrderIntegrator: '<Root>/Second-Order  Integrator' incorporates:
   *  Constant: '<Root>/Gravitational acceleration'
   */
  switch (bouncing_ball_GT_DW.SecondOrderIntegrator_MODE) {
   case 0:
    _rtXdot->Position[0] = bouncing_ball_GT_X.Position[1];
    _rtXdot->Position[1] = bouncing_ball_GT_P.Gravitationalacceleration_Value;
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

  /* End of Derivatives for SecondOrderIntegrator: '<Root>/Second-Order  Integrator' */
}

/* Model initialize function */
void bouncing_ball_GT_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  bouncing_ball_GT_P.SecondOrderIntegrator_UpperLimi = rtInf;

  /* initialize real-time model */
  (void) memset((void *)bouncing_ball_GT_M, 0,
                sizeof(RT_MODEL_bouncing_ball_GT_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&bouncing_ball_GT_M->solverInfo,
                          &bouncing_ball_GT_M->Timing.simTimeStep);
    rtsiSetTPtr(&bouncing_ball_GT_M->solverInfo, &rtmGetTPtr(bouncing_ball_GT_M));
    rtsiSetStepSizePtr(&bouncing_ball_GT_M->solverInfo,
                       &bouncing_ball_GT_M->Timing.stepSize0);
    rtsiSetdXPtr(&bouncing_ball_GT_M->solverInfo, &bouncing_ball_GT_M->derivs);
    rtsiSetContStatesPtr(&bouncing_ball_GT_M->solverInfo, (real_T **)
                         &bouncing_ball_GT_M->contStates);
    rtsiSetNumContStatesPtr(&bouncing_ball_GT_M->solverInfo,
      &bouncing_ball_GT_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&bouncing_ball_GT_M->solverInfo,
      &bouncing_ball_GT_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&bouncing_ball_GT_M->solverInfo,
      &bouncing_ball_GT_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&bouncing_ball_GT_M->solverInfo,
      &bouncing_ball_GT_M->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&bouncing_ball_GT_M->solverInfo, (boolean_T**)
      &bouncing_ball_GT_M->contStateDisabled);
    rtsiSetErrorStatusPtr(&bouncing_ball_GT_M->solverInfo, (&rtmGetErrorStatus
      (bouncing_ball_GT_M)));
    rtsiSetRTModelPtr(&bouncing_ball_GT_M->solverInfo, bouncing_ball_GT_M);
  }

  rtsiSetSimTimeStep(&bouncing_ball_GT_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&bouncing_ball_GT_M->solverInfo, false);
  rtsiSetIsContModeFrozen(&bouncing_ball_GT_M->solverInfo, false);
  bouncing_ball_GT_M->intgData.y = bouncing_ball_GT_M->odeY;
  bouncing_ball_GT_M->intgData.f[0] = bouncing_ball_GT_M->odeF[0];
  bouncing_ball_GT_M->intgData.f[1] = bouncing_ball_GT_M->odeF[1];
  bouncing_ball_GT_M->intgData.f[2] = bouncing_ball_GT_M->odeF[2];
  bouncing_ball_GT_M->contStates = ((X_bouncing_ball_GT_T *) &bouncing_ball_GT_X);
  bouncing_ball_GT_M->contStateDisabled = ((XDis_bouncing_ball_GT_T *)
    &bouncing_ball_GT_XDis);
  bouncing_ball_GT_M->Timing.tStart = (0.0);
  rtsiSetSolverData(&bouncing_ball_GT_M->solverInfo, (void *)
                    &bouncing_ball_GT_M->intgData);
  rtsiSetSolverName(&bouncing_ball_GT_M->solverInfo,"ode3");
  rtmSetTPtr(bouncing_ball_GT_M, &bouncing_ball_GT_M->Timing.tArray[0]);
  rtmSetTFinal(bouncing_ball_GT_M, 25.0);
  bouncing_ball_GT_M->Timing.stepSize0 = 0.5;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (NULL);
    bouncing_ball_GT_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(bouncing_ball_GT_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(bouncing_ball_GT_M->rtwLogInfo, (NULL));
    rtliSetLogT(bouncing_ball_GT_M->rtwLogInfo, "");
    rtliSetLogX(bouncing_ball_GT_M->rtwLogInfo, "");
    rtliSetLogXFinal(bouncing_ball_GT_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(bouncing_ball_GT_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(bouncing_ball_GT_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(bouncing_ball_GT_M->rtwLogInfo, 0);
    rtliSetLogDecimation(bouncing_ball_GT_M->rtwLogInfo, 1);
    rtliSetLogY(bouncing_ball_GT_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(bouncing_ball_GT_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(bouncing_ball_GT_M->rtwLogInfo, (NULL));
  }

  /* block I/O */
  (void) memset(((void *) &bouncing_ball_GT_B), 0,
                sizeof(B_bouncing_ball_GT_T));

  /* states (continuous) */
  {
    (void) memset((void *)&bouncing_ball_GT_X, 0,
                  sizeof(X_bouncing_ball_GT_T));
  }

  /* disabled states */
  {
    (void) memset((void *)&bouncing_ball_GT_XDis, 0,
                  sizeof(XDis_bouncing_ball_GT_T));
  }

  /* states (dwork) */
  (void) memset((void *)&bouncing_ball_GT_DW, 0,
                sizeof(DW_bouncing_ball_GT_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(bouncing_ball_GT_M->rtwLogInfo, 0.0,
    rtmGetTFinal(bouncing_ball_GT_M), bouncing_ball_GT_M->Timing.stepSize0,
    (&rtmGetErrorStatus(bouncing_ball_GT_M)));

  /* Start for InitialCondition: '<Root>/Initial Velocity (IC) ' */
  bouncing_ball_GT_DW.InitialVelocityIC_FirstOutputTi = true;

  /* InitializeConditions for Memory: '<Root>/Memory' */
  bouncing_ball_GT_DW.Memory_PreviousInput =
    bouncing_ball_GT_P.Memory_InitialCondition;

  /* InitializeConditions for SecondOrderIntegrator: '<Root>/Second-Order  Integrator' */
  bouncing_ball_GT_X.Position[0] = bouncing_ball_GT_P.SecondOrderIntegrator_ICX;
  bouncing_ball_GT_DW.SecondOrderIntegrator_MODE = 0;
  bouncing_ball_GT_DW.SecondOrderIntegrator_DWORK1 = true;
}

/* Model terminate function */
void bouncing_ball_GT_terminate(void)
{
  /* (no terminate code required) */
}
