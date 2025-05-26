

        /*
    * rt_defines.h
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


    #ifndef rt_defines_h_
    #define rt_defines_h_



    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    

    /*===========*
    * Constants *
    *===========*/

    #define RT_PI          3.14159265358979323846
    #define RT_PIF         3.1415927F
    #define RT_LN_10       2.30258509299404568402
    #define RT_LN_10F      2.3025851F
    #define RT_LOG10E      0.43429448190325182765
    #define RT_LOG10EF     0.43429449F
    #define RT_E           2.7182818284590452354
    #define RT_EF          2.7182817F

    /*
    * UNUSED_PARAMETER(x)
    *   Used to specify that a function parameter (argument) is required but not
    *   accessed by the function body.
    */
    #ifndef UNUSED_PARAMETER
    #if defined(__LCC__)
    #define UNUSED_PARAMETER(x)  /* do nothing */
    #else
    /*
    * This is the semi-ANSI standard way of indicating that an
    * unused function parameter is required.
    */
    #define UNUSED_PARAMETER(x) (void) (x)
    #endif
    #endif



    

    

    

    

    

    #endif /* rt_defines_h_ */
