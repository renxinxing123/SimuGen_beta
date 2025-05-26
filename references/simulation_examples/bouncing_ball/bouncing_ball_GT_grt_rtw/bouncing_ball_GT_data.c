/*
 * bouncing_ball_GT_data.c
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

/* Block parameters (default storage) */
P_bouncing_ball_GT_T bouncing_ball_GT_P = {
  /* Expression: 0
   * Referenced by: '<Root>/Memory'
   */
  0.0,

  /* Expression: -0.8
   * Referenced by: '<Root>/Coefficient of  Restitution'
   */
  -0.8,

  /* Expression: 0
   * Referenced by: '<Root>/Initial Velocity (IC) '
   */
  0.0,

  /* Expression: 25.0
   * Referenced by: '<Root>/Second-Order  Integrator'
   */
  25.0,

  /* Expression: inf
   * Referenced by: '<Root>/Second-Order  Integrator'
   */
  0.0,

  /* Expression: 0.0
   * Referenced by: '<Root>/Second-Order  Integrator'
   */
  0.0,

  /* Expression: -9.81
   * Referenced by: '<Root>/Gravitational acceleration'
   */
  -9.81
};
