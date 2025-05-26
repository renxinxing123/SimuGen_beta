/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: bouncing_ball_GT.h
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

#ifndef bouncing_ball_GT_h_
#define bouncing_ball_GT_h_
#ifndef bouncing_ball_GT_COMMON_INCLUDES_
#define bouncing_ball_GT_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* bouncing_ball_GT_COMMON_INCLUDES_ */

#include "bouncing_ball_GT_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"
#include <string.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

#ifndef rtmGetTStart
#define rtmGetTStart(rtm)              ((rtm)->Timing.tStart)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T InitialVelocityIC;            /* '<Root>/Initial Velocity (IC) ' */
  real_T Velocity;                     /* '<Root>/Second-Order  Integrator' */
} B_bouncing_ball_GT_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Memory_PreviousInput;         /* '<Root>/Memory' */
  int_T SecondOrderIntegrator_MODE;    /* '<Root>/Second-Order  Integrator' */
  boolean_T InitialVelocityIC_FirstOutputTi;/* '<Root>/Initial Velocity (IC) ' */
  boolean_T SecondOrderIntegrator_DWORK1;/* '<Root>/Second-Order  Integrator' */
} DW_bouncing_ball_GT_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Position[2];                  /* '<Root>/Second-Order  Integrator' */
} X_bouncing_ball_GT_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Position[2];                  /* '<Root>/Second-Order  Integrator' */
} XDot_bouncing_ball_GT_T;

/* State disabled  */
typedef struct {
  boolean_T Position[2];               /* '<Root>/Second-Order  Integrator' */
} XDis_bouncing_ball_GT_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Real-time Model Data Structure */
struct tag_RTM_bouncing_ball_GT_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_bouncing_ball_GT_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_bouncing_ball_GT_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[2];
  real_T odeF[3][2];
  ODE3_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    time_T tStart;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block signals (default storage) */
extern B_bouncing_ball_GT_T bouncing_ball_GT_B;

/* Continuous states (default storage) */
extern X_bouncing_ball_GT_T bouncing_ball_GT_X;

/* Disabled states (default storage) */
extern XDis_bouncing_ball_GT_T bouncing_ball_GT_XDis;

/* Block states (default storage) */
extern DW_bouncing_ball_GT_T bouncing_ball_GT_DW;

/* Model entry point functions */
extern void bouncing_ball_GT_initialize(void);
extern void bouncing_ball_GT_step(void);
extern void bouncing_ball_GT_terminate(void);

/* Real-time Model object */
extern RT_MODEL_bouncing_ball_GT_T *const bouncing_ball_GT_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Scope1' : Unused code path elimination
 * Block '<Root>/Scope2' : Unused code path elimination
 * Block '<Root>/Scope' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'bouncing_ball_GT'
 */
#endif                                 /* bouncing_ball_GT_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
