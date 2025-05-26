/*
 * bouncing_ball_GT_sid.h
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
 *
 * SOURCES: bouncing_ball_GT_sf.c
 */

/* statically allocated instance data for model: bouncing_ball_GT */
{
  {
    /* Local SimStruct for the generated S-Function */
    static LocalS slS;
    LocalS *lS = &slS;
    ssSetUserData(rts, lS);

    /* block I/O */
    {
      static B_bouncing_ball_GT_T sfcnB;
      void *b = (real_T *) &sfcnB;
      ssSetLocalBlockIO(rts, b);
      (void) memset(b, 0,
                    sizeof(B_bouncing_ball_GT_T));
    }

    /* model checksums */
    ssSetChecksumVal(rts, 0, 522743239U);
    ssSetChecksumVal(rts, 1, 68571262U);
    ssSetChecksumVal(rts, 2, 1454303353U);
    ssSetChecksumVal(rts, 3, 2148741027U);
  }
}
