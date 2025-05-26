/*
 * bouncing_ball_GT_sf.h
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

#ifndef bouncing_ball_GT_sf_h_
#define bouncing_ball_GT_sf_h_
#ifndef bouncing_ball_GT_sf_COMMON_INCLUDES_
#define bouncing_ball_GT_sf_COMMON_INCLUDES_
#include <stdlib.h>
#define S_FUNCTION_NAME                bouncing_ball_GT_sf
#define S_FUNCTION_LEVEL               2
#ifndef RTW_GENERATED_S_FUNCTION
#define RTW_GENERATED_S_FUNCTION
#endif

#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#if !defined(MATLAB_MEX_FILE)
#include "rt_matrx.h"
#endif

#if !defined(RTW_SFUNCTION_DEFINES)
#define RTW_SFUNCTION_DEFINES

typedef struct {
  void *blockIO;
  void *defaultParam;
  void *nonContDerivSig;
} LocalS;

#define ssSetLocalBlockIO(S, io)       ((LocalS *)ssGetUserData(S))->blockIO = ((void *)(io))
#define ssGetLocalBlockIO(S)           ((LocalS *)ssGetUserData(S))->blockIO
#define ssSetLocalDefaultParam(S, paramVector) ((LocalS *)ssGetUserData(S))->defaultParam = (paramVector)
#define ssGetLocalDefaultParam(S)      ((LocalS *)ssGetUserData(S))->defaultParam
#define ssSetLocalNonContDerivSig(S, pSig) ((LocalS *)ssGetUserData(S))->nonContDerivSig = (pSig)
#define ssGetLocalNonContDerivSig(S)   ((LocalS *)ssGetUserData(S))->nonContDerivSig
#endif
#endif                                /* bouncing_ball_GT_sf_COMMON_INCLUDES_ */

#include "bouncing_ball_GT_sf_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"
#include <string.h>
#include <math.h>
#include <stddef.h>
#include "rt_defines.h"

/* Block signals (default storage) */
typedef struct {
  /*@[8957*/

  /*@[8951*/
  /*@[8952*/
  real_T InitialVelocityIC;            /* '<Root>/Initial Velocity (IC) ' */

  /*@]*/
  /*@]*/

  /*@[8953*/
  /*@[8954*/
  real_T Position;                     /* '<Root>/Second-Order  Integrator' */

  /*@]*/
  /*@]*/

  /*@[8955*/
  /*@[8956*/
  real_T Velocity;                     /* '<Root>/Second-Order  Integrator' */

  /*@]*/
  /*@]*/

  /*@]*/
} B_bouncing_ball_GT_T;

/* Continuous states (default storage) */
typedef struct {
  /*@[8958*/
  real_T Position[2];                  /* '<Root>/Second-Order  Integrator' */

  /*@]*/
} X_bouncing_ball_GT_T;

/* State derivatives (default storage) */
typedef struct {
  /*@[8959*/
  real_T Position[2];                  /* '<Root>/Second-Order  Integrator' */

  /*@]*/
} XDot_bouncing_ball_GT_T;

/* State disabled  */
typedef struct {                       /*@[895a*/
  boolean_T Position[2];               /* '<Root>/Second-Order  Integrator' */

  /*@]*/
} XDis_bouncing_ball_GT_T;

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
 * '<Root>' : 'bouncing_ball_GT_sf'
 */
#endif                                 /* bouncing_ball_GT_sf_h_ */
