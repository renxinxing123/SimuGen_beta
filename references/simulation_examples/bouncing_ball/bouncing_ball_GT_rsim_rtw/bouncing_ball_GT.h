/*
 * bouncing_ball_GT.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "bouncing_ball_GT".
 *
 * Model version              : 12.3
 * Simulink Coder version : 24.2 (R2024b) 21-Jun-2024
 * C source code generated on : Wed Apr 16 14:19:20 2025
 *
 * Target selection: rsim.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
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
#include <stdlib.h>
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rsim.h"
#include "rt_logging.h"
#include "dt_info.h"
#endif                                 /* bouncing_ball_GT_COMMON_INCLUDES_ */

#include "bouncing_ball_GT_types.h"
#include "rt_defines.h"
#include <stddef.h>
#include <string.h>
#include "rt_nonfinite.h"
#define MODEL_NAME                     bouncing_ball_GT
#define NSAMPLE_TIMES                  (2)                       /* Number of sample times */
#define NINPUTS                        (0)                       /* Number of model inputs */
#define NOUTPUTS                       (0)                       /* Number of model outputs */
#define NBLOCKIO                       (3)                       /* Number of data output port signals */
#define NUM_ZC_EVENTS                  (0)                       /* Number of zero-crossing events */
#ifndef NCSTATES
#define NCSTATES                       (2)                       /* Number of continuous states */
#elif NCSTATES != 2
# error Invalid specification of NCSTATES defined in compiler command
#endif

#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm)         (NULL)
#endif

#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T InitialVelocityIC;            /* '<Root>/Initial Velocity (IC) ' */
  real_T Position;                     /* '<Root>/Second-Order  Integrator' */
  real_T Velocity;                     /* '<Root>/Second-Order  Integrator' */
} B;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Memory_PreviousInput;         /* '<Root>/Memory' */
  struct {
    void *LoggedData;
  } Scope1_PWORK;                      /* '<Root>/Scope1' */

  struct {
    void *LoggedData;
  } Scope2_PWORK;                      /* '<Root>/Scope2' */

  int_T SecondOrderIntegrator_MODE;    /* '<Root>/Second-Order  Integrator' */
  boolean_T InitialVelocityIC_FirstOutputTi;/* '<Root>/Initial Velocity (IC) ' */
  boolean_T SecondOrderIntegrator_DWORK1;/* '<Root>/Second-Order  Integrator' */
} DW;

/* Continuous states (default storage) */
typedef struct {
  real_T Position[2];                  /* '<Root>/Second-Order  Integrator' */
} X;

/* State derivatives (default storage) */
typedef struct {
  real_T Position[2];                  /* '<Root>/Second-Order  Integrator' */
} XDot;

/* State disabled  */
typedef struct {
  boolean_T Position[2];               /* '<Root>/Second-Order  Integrator' */
} XDis;

/* Parameters (default storage) */
struct P_ {
  real_T Memory_InitialCondition;      /* Expression: 0
                                        * Referenced by: '<Root>/Memory'
                                        */
  real_T CoefficientofRestitution_Gain;/* Expression: -0.8
                                        * Referenced by: '<Root>/Coefficient of  Restitution'
                                        */
  real_T InitialVelocityIC_Value;      /* Expression: 0
                                        * Referenced by: '<Root>/Initial Velocity (IC) '
                                        */
  real_T SecondOrderIntegrator_ICX;    /* Expression: 25.0
                                        * Referenced by: '<Root>/Second-Order  Integrator'
                                        */
  real_T SecondOrderIntegrator_UpperLimi;/* Expression: inf
                                          * Referenced by: '<Root>/Second-Order  Integrator'
                                          */
  real_T SecondOrderIntegrator_LowerLimi;/* Expression: 0.0
                                          * Referenced by: '<Root>/Second-Order  Integrator'
                                          */
  real_T Gravitationalacceleration_Value;/* Expression: -9.81
                                          * Referenced by: '<Root>/Gravitational acceleration'
                                          */
};

/* External data declarations for dependent source files */
extern const char_T *RT_MEMORY_ALLOCATION_ERROR;
extern B rtB;                          /* block i/o */
extern X rtX;                          /* states (continuous) */
extern DW rtDW;                        /* states (dwork) */
extern P rtP;                          /* parameters */

/* Simulation Structure */
extern SimStruct *const rtS;

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

/* user code (bottom of header file) */
extern const int_T gblNumToFiles;
extern const int_T gblNumFrFiles;
extern const int_T gblNumFrWksBlocks;
extern rtInportTUtable *gblInportTUtables;
extern const char *gblInportFileName;
extern const int_T gblNumRootInportBlks;
extern const int_T gblNumModelInputs;
extern const int_T gblInportDataTypeIdx[];
extern const int_T gblInportDims[];
extern const int_T gblInportComplex[];
extern const int_T gblInportInterpoFlag[];
extern const int_T gblInportContinuous[];

#endif                                 /* bouncing_ball_GT_h_ */
