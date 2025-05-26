/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: bouncing_ball_GT.c
 *
 * Code generated for Simulink model 'bouncing_ball_GT'.
 *
 * Model version                  : 12.4
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Wed Apr 16 18:27:09 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Emulation hardware selection:
 *    Differs from embedded hardware (MATLAB Host)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "bouncing_ball_GT.h"
#include "rtwtypes.h"
#include "bouncing_ball_GT_private.h"
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
  int32_T uMode;
  if (rtmIsMajorTimeStep(bouncing_ball_GT_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&bouncing_ball_GT_M->solverInfo,
                          ((bouncing_ball_GT_M->Timing.clockTick0+1)*
      bouncing_ball_GT_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(bouncing_ball_GT_M)) {
    bouncing_ball_GT_M->Timing.t[0] = rtsiGetT(&bouncing_ball_GT_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(bouncing_ball_GT_M)) {
    /* InitialCondition: '<Root>/Initial Velocity (IC) ' */
    if (bouncing_ball_GT_DW.InitialVelocityIC_FirstOutputTi) {
      bouncing_ball_GT_DW.InitialVelocityIC_FirstOutputTi = false;

      /* InitialCondition: '<Root>/Initial Velocity (IC) ' */
      bouncing_ball_GT_B.InitialVelocityIC = 0.0;
    } else {
      /* InitialCondition: '<Root>/Initial Velocity (IC) ' incorporates:
       *  Gain: '<Root>/Coefficient of  Restitution'
       *  Memory: '<Root>/Memory'
       */
      bouncing_ball_GT_B.InitialVelocityIC = -0.8 *
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
      if (bouncing_ball_GT_X.Position[0] <= 0.0) {
        bouncing_ball_GT_X.Position[0] = 0.0;
        if (bouncing_ball_GT_X.Position[1] > 0.0) {
          bouncing_ball_GT_DW.SecondOrderIntegrator_MODE = 0;
        } else {
          bouncing_ball_GT_X.Position[1] = 0.0;
          bouncing_ball_GT_DW.SecondOrderIntegrator_MODE = 1;
        }

        if (bouncing_ball_GT_B.InitialVelocityIC > 0.0) {
          bouncing_ball_GT_X.Position[1] = bouncing_ball_GT_B.InitialVelocityIC;
          bouncing_ball_GT_DW.SecondOrderIntegrator_MODE = 0;
        }

        rtsiSetBlockStateForSolverChangedAtMajorStep
          (&bouncing_ball_GT_M->solverInfo, true);
      }

      if (bouncing_ball_GT_X.Position[0] >= (rtInf)) {
        bouncing_ball_GT_X.Position[0] = (rtInf);
        if (bouncing_ball_GT_X.Position[1] < 0.0) {
          bouncing_ball_GT_DW.SecondOrderIntegrator_MODE = 0;
        } else {
          bouncing_ball_GT_X.Position[1] = 0.0;
          bouncing_ball_GT_DW.SecondOrderIntegrator_MODE = 2;
        }

        if (bouncing_ball_GT_B.InitialVelocityIC < 0.0) {
          bouncing_ball_GT_X.Position[1] = bouncing_ball_GT_B.InitialVelocityIC;
          bouncing_ball_GT_DW.SecondOrderIntegrator_MODE = 0;
        }

        rtsiSetBlockStateForSolverChangedAtMajorStep
          (&bouncing_ball_GT_M->solverInfo, true);
      }
      break;

     case 1:
      if (bouncing_ball_GT_X.Position[0] > 0.0) {
        if (bouncing_ball_GT_X.Position[0] >= (rtInf)) {
          bouncing_ball_GT_DW.SecondOrderIntegrator_MODE = 2;
          bouncing_ball_GT_X.Position[0] = (rtInf);
        } else {
          bouncing_ball_GT_DW.SecondOrderIntegrator_MODE = 0;
        }
      } else {
        bouncing_ball_GT_X.Position[0] = 0.0;
        bouncing_ball_GT_X.Position[1] = 0.0;
      }
      break;

     case 2:
      if (bouncing_ball_GT_X.Position[0] < (rtInf)) {
        if (bouncing_ball_GT_X.Position[0] <= 0.0) {
          bouncing_ball_GT_DW.SecondOrderIntegrator_MODE = 1;
          bouncing_ball_GT_X.Position[0] = 0.0;
        } else {
          bouncing_ball_GT_DW.SecondOrderIntegrator_MODE = 0;
        }
      } else {
        bouncing_ball_GT_X.Position[0] = (rtInf);
        bouncing_ball_GT_X.Position[1] = 0.0;
      }
      break;
    }
  }

  /* SecondOrderIntegrator: '<Root>/Second-Order  Integrator' */
  bouncing_ball_GT_B.Velocity = bouncing_ball_GT_X.Position[1];
  if (rtmIsMajorTimeStep(bouncing_ball_GT_M)) {
    if (rtmIsMajorTimeStep(bouncing_ball_GT_M)) {
      /* Update for Memory: '<Root>/Memory' */
      bouncing_ball_GT_DW.Memory_PreviousInput = bouncing_ball_GT_B.Velocity;
    }

    /* Update for SecondOrderIntegrator: '<Root>/Second-Order  Integrator' */
    bouncing_ball_GT_DW.SecondOrderIntegrator_DWORK1 = false;
    uMode = bouncing_ball_GT_DW.SecondOrderIntegrator_MODE;
    if (bouncing_ball_GT_DW.SecondOrderIntegrator_MODE == 2) {
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
    rt_ertODEUpdateContinuousStates(&bouncing_ball_GT_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++bouncing_ball_GT_M->Timing.clockTick0;
    bouncing_ball_GT_M->Timing.t[0] = rtsiGetSolverStopTime
      (&bouncing_ball_GT_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.5s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.5, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      bouncing_ball_GT_M->Timing.clockTick1++;
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

  /* End of Derivatives for SecondOrderIntegrator: '<Root>/Second-Order  Integrator' */
}

/* Model initialize function */
void bouncing_ball_GT_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

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
  bouncing_ball_GT_M->Timing.stepSize0 = 0.5;

  /* Start for InitialCondition: '<Root>/Initial Velocity (IC) ' */
  bouncing_ball_GT_DW.InitialVelocityIC_FirstOutputTi = true;

  /* InitializeConditions for SecondOrderIntegrator: '<Root>/Second-Order  Integrator' */
  bouncing_ball_GT_X.Position[0] = 25.0;
  bouncing_ball_GT_DW.SecondOrderIntegrator_DWORK1 = true;
}

/* Model terminate function */
void bouncing_ball_GT_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
