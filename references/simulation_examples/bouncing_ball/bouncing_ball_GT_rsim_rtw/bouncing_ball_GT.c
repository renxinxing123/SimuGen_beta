/*
 * bouncing_ball_GT.c
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

#include "bouncing_ball_GT.h"
#include "rtwtypes.h"
#include "bouncing_ball_GT_private.h"
#include "bouncing_ball_GT_dt.h"

/* user code (top of parameter file) */
const int_T gblNumToFiles = 0;
const int_T gblNumFrFiles = 0;
const int_T gblNumFrWksBlocks = 0;
const char *gblSlvrJacPatternFileName =
  "bouncing_ball_GT_rsim_rtw//bouncing_ball_GT_Jpattern.mat";

/* Root inports information  */
const int_T gblNumRootInportBlks = 0;
const int_T gblNumModelInputs = 0;
extern rtInportTUtable *gblInportTUtables;
extern const char *gblInportFileName;
const int_T gblInportDataTypeIdx[] = { -1 };

const int_T gblInportDims[] = { -1 } ;

const int_T gblInportComplex[] = { -1 };

const int_T gblInportInterpoFlag[] = { -1 };

const int_T gblInportContinuous[] = { -1 };

#include "simstruc.h"
#include "fixedpoint.h"

/* Block signals (default storage) */
B rtB;

/* Continuous states */
X rtX;

/* Disabled State Vector */
XDis rtXDis;

/* Block states (default storage) */
DW rtDW;

/* Parent Simstruct */
static SimStruct model_S;
SimStruct *const rtS = &model_S;

/* System initialize for root system: '<Root>' */
void MdlInitialize(void)
{
  /* InitializeConditions for Memory: '<Root>/Memory' */
  rtDW.Memory_PreviousInput = rtP.Memory_InitialCondition;

  /* InitializeConditions for SecondOrderIntegrator: '<Root>/Second-Order  Integrator' */
  rtX.Position[0] = rtP.SecondOrderIntegrator_ICX;
  rtDW.SecondOrderIntegrator_MODE = 0;
  rtDW.SecondOrderIntegrator_DWORK1 = true;
}

/* Start for root system: '<Root>' */
void MdlStart(void)
{
  /* Start for InitialCondition: '<Root>/Initial Velocity (IC) ' */
  rtDW.InitialVelocityIC_FirstOutputTi = true;
  MdlInitialize();
}

/* Outputs for root system: '<Root>' */
void MdlOutputs(int_T tid)
{
  boolean_T tmp;
  tmp = ssIsSampleHit(rtS, 1, 0);
  if (tmp) {
    /* InitialCondition: '<Root>/Initial Velocity (IC) ' */
    if (rtDW.InitialVelocityIC_FirstOutputTi) {
      rtDW.InitialVelocityIC_FirstOutputTi = false;

      /* InitialCondition: '<Root>/Initial Velocity (IC) ' */
      rtB.InitialVelocityIC = rtP.InitialVelocityIC_Value;
    } else {
      /* InitialCondition: '<Root>/Initial Velocity (IC) ' incorporates:
       *  Gain: '<Root>/Coefficient of  Restitution'
       *  Memory: '<Root>/Memory'
       */
      rtB.InitialVelocityIC = rtP.CoefficientofRestitution_Gain *
        rtDW.Memory_PreviousInput;
    }

    /* End of InitialCondition: '<Root>/Initial Velocity (IC) ' */
  }

  /* SecondOrderIntegrator: '<Root>/Second-Order  Integrator' */
  if (rtDW.SecondOrderIntegrator_DWORK1) {
    rtX.Position[1] = rtB.InitialVelocityIC;
  }

  if (ssIsModeUpdateTimeStep(rtS)) {
    switch (rtDW.SecondOrderIntegrator_MODE) {
     case 0:
      if (rtX.Position[0] <= rtP.SecondOrderIntegrator_LowerLimi) {
        rtX.Position[0] = rtP.SecondOrderIntegrator_LowerLimi;
        if (rtX.Position[1] > 0.0) {
          rtDW.SecondOrderIntegrator_MODE = 0;
        } else {
          rtX.Position[1] = 0.0;
          rtDW.SecondOrderIntegrator_MODE = 1;
        }

        if (rtB.InitialVelocityIC > 0.0) {
          rtX.Position[1] = rtB.InitialVelocityIC;
          rtDW.SecondOrderIntegrator_MODE = 0;
        }

        ssSetBlockStateForSolverChangedAtMajorStep(rtS);
      }

      if (rtX.Position[0] >= rtP.SecondOrderIntegrator_UpperLimi) {
        rtX.Position[0] = rtP.SecondOrderIntegrator_UpperLimi;
        if (rtX.Position[1] < 0.0) {
          rtDW.SecondOrderIntegrator_MODE = 0;
        } else {
          rtX.Position[1] = 0.0;
          rtDW.SecondOrderIntegrator_MODE = 2;
        }

        if (rtB.InitialVelocityIC < 0.0) {
          rtX.Position[1] = rtB.InitialVelocityIC;
          rtDW.SecondOrderIntegrator_MODE = 0;
        }

        ssSetBlockStateForSolverChangedAtMajorStep(rtS);
      }
      break;

     case 1:
      if (rtX.Position[0] > rtP.SecondOrderIntegrator_LowerLimi) {
        if (rtX.Position[0] >= rtP.SecondOrderIntegrator_UpperLimi) {
          rtDW.SecondOrderIntegrator_MODE = 2;
          rtX.Position[0] = rtP.SecondOrderIntegrator_UpperLimi;
        } else {
          rtDW.SecondOrderIntegrator_MODE = 0;
        }
      } else {
        rtX.Position[0] = rtP.SecondOrderIntegrator_LowerLimi;
        rtX.Position[1] = 0.0;
      }
      break;

     case 2:
      if (rtX.Position[0] < rtP.SecondOrderIntegrator_UpperLimi) {
        if (rtX.Position[0] <= rtP.SecondOrderIntegrator_LowerLimi) {
          rtDW.SecondOrderIntegrator_MODE = 1;
          rtX.Position[0] = rtP.SecondOrderIntegrator_LowerLimi;
        } else {
          rtDW.SecondOrderIntegrator_MODE = 0;
        }
      } else {
        rtX.Position[0] = rtP.SecondOrderIntegrator_UpperLimi;
        rtX.Position[1] = 0.0;
      }
      break;
    }
  }

  if (rtX.Position[0] < rtP.SecondOrderIntegrator_LowerLimi) {
    /* SecondOrderIntegrator: '<Root>/Second-Order  Integrator' */
    rtB.Position = rtP.SecondOrderIntegrator_LowerLimi;
  } else if (rtX.Position[0] > rtP.SecondOrderIntegrator_UpperLimi) {
    /* SecondOrderIntegrator: '<Root>/Second-Order  Integrator' */
    rtB.Position = rtP.SecondOrderIntegrator_UpperLimi;
  } else {
    /* SecondOrderIntegrator: '<Root>/Second-Order  Integrator' */
    rtB.Position = rtX.Position[0];
  }

  /* SecondOrderIntegrator: '<Root>/Second-Order  Integrator' */
  rtB.Velocity = rtX.Position[1];
  if (tmp) {
  }

  UNUSED_PARAMETER(tid);
}

/* Update for root system: '<Root>' */
void MdlUpdate(int_T tid)
{
  int32_T uMode;
  if (ssIsSampleHit(rtS, 1, 0)) {
    /* Update for Memory: '<Root>/Memory' */
    rtDW.Memory_PreviousInput = rtB.Velocity;
  }

  /* Update for SecondOrderIntegrator: '<Root>/Second-Order  Integrator' incorporates:
   *  Constant: '<Root>/Gravitational acceleration'
   */
  rtDW.SecondOrderIntegrator_DWORK1 = false;
  uMode = rtDW.SecondOrderIntegrator_MODE;
  if (((rtDW.SecondOrderIntegrator_MODE == 1) &&
       (rtP.Gravitationalacceleration_Value > 0.0)) ||
      ((rtDW.SecondOrderIntegrator_MODE == 2) &&
       (rtP.Gravitationalacceleration_Value < 0.0))) {
    uMode = 0;
  }

  if (rtDW.SecondOrderIntegrator_MODE != uMode) {
    rtDW.SecondOrderIntegrator_MODE = uMode;
    ssSetBlockStateForSolverChangedAtMajorStep(rtS);
  }

  /* End of Update for SecondOrderIntegrator: '<Root>/Second-Order  Integrator' */
  UNUSED_PARAMETER(tid);
}

/* Derivatives for root system: '<Root>' */
void MdlDerivatives(void)
{
  XDot *_rtXdot;
  _rtXdot = ((XDot *) ssGetdX(rtS));

  /* Derivatives for SecondOrderIntegrator: '<Root>/Second-Order  Integrator' incorporates:
   *  Constant: '<Root>/Gravitational acceleration'
   */
  switch (rtDW.SecondOrderIntegrator_MODE) {
   case 0:
    _rtXdot->Position[0] = rtX.Position[1];
    _rtXdot->Position[1] = rtP.Gravitationalacceleration_Value;
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

/* Projection for root system: '<Root>' */
void MdlProjection(void)
{
}

/* Termination for root system: '<Root>' */
void MdlTerminate(void)
{
}

/* Function to initialize sizes */
void MdlInitializeSizes(void)
{
  ssSetNumContStates(rtS, 2);          /* Number of continuous states */
  ssSetNumPeriodicContStates(rtS, 0); /* Number of periodic continuous states */
  ssSetNumY(rtS, 0);                   /* Number of model outputs */
  ssSetNumU(rtS, 0);                   /* Number of model inputs */
  ssSetDirectFeedThrough(rtS, 0);      /* The model is not direct feedthrough */
  ssSetNumSampleTimes(rtS, 2);         /* Number of sample times */
  ssSetNumBlocks(rtS, 8);              /* Number of blocks */
  ssSetNumBlockIO(rtS, 3);             /* Number of block outputs */
  ssSetNumBlockParams(rtS, 7);         /* Sum of parameter "widths" */
}

/* Function to initialize sample times. */
void MdlInitializeSampleTimes(void)
{
  /* task periods */
  ssSetSampleTime(rtS, 0, 0.0);
  ssSetSampleTime(rtS, 1, 0.5);

  /* task offsets */
  ssSetOffsetTime(rtS, 0, 0.0);
  ssSetOffsetTime(rtS, 1, 0.0);
}

/* Function to register the model */
/* Turns off all optimizations on Windows because of issues with VC 2015 compiler.
   This function is not performance-critical, hence this is not a problem.
 */
#if defined(_MSC_VER)

#pragma optimize( "", off )

#endif

SimStruct * bouncing_ball_GT(void)
{
  static struct _ssMdlInfo mdlInfo;
  static struct _ssBlkInfo2 blkInfo2;
  static struct _ssBlkInfoSLSize blkInfoSLSize;
  (void) memset((char_T *)rtS, 0,
                sizeof(SimStruct));
  (void) memset((char_T *)&mdlInfo, 0,
                sizeof(struct _ssMdlInfo));
  (void) memset((char_T *)&blkInfo2, 0,
                sizeof(struct _ssBlkInfo2));
  (void) memset((char_T *)&blkInfoSLSize, 0,
                sizeof(struct _ssBlkInfoSLSize));
  ssSetBlkInfo2Ptr(rtS, &blkInfo2);
  ssSetBlkInfoSLSizePtr(rtS, &blkInfoSLSize);
  ssSetMdlInfoPtr(rtS, &mdlInfo);

  /* timing info */
  {
    static time_T mdlPeriod[NSAMPLE_TIMES];
    static time_T mdlOffset[NSAMPLE_TIMES];
    static time_T mdlTaskTimes[NSAMPLE_TIMES];
    static int_T mdlTsMap[NSAMPLE_TIMES];
    static int_T mdlSampleHits[NSAMPLE_TIMES];

    {
      int_T i;
      for (i = 0; i < NSAMPLE_TIMES; i++) {
        mdlPeriod[i] = 0.0;
        mdlOffset[i] = 0.0;
        mdlTaskTimes[i] = 0.0;
        mdlTsMap[i] = i;
        mdlSampleHits[i] = 1;
      }
    }

    ssSetSampleTimePtr(rtS, &mdlPeriod[0]);
    ssSetOffsetTimePtr(rtS, &mdlOffset[0]);
    ssSetSampleTimeTaskIDPtr(rtS, &mdlTsMap[0]);
    ssSetTPtr(rtS, &mdlTaskTimes[0]);
    ssSetSampleHitPtr(rtS, &mdlSampleHits[0]);
  }

  ssSetSolverMode(rtS, SOLVER_MODE_SINGLETASKING);

  /*
   * initialize model vectors and cache them in SimStruct
   */

  /* block I/O */
  {
    ssSetBlockIO(rtS, ((void *) &rtB));
    (void) memset(((void *) &rtB), 0,
                  sizeof(B));
  }

  /* states (continuous)*/
  {
    real_T *x = (real_T *) &rtX;
    ssSetContStates(rtS, x);
    (void) memset((void *)x, 0,
                  sizeof(X));
  }

  /* states (dwork) */
  {
    void *dwork = (void *) &rtDW;
    ssSetRootDWork(rtS, dwork);
    (void) memset(dwork, 0,
                  sizeof(DW));
  }

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    ssSetModelMappingInfo(rtS, &dtInfo);
    dtInfo.numDataTypes = 23;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Model specific registration */
  ssSetRootSS(rtS, rtS);
  ssSetVersion(rtS, SIMSTRUCT_VERSION_LEVEL2);
  ssSetModelName(rtS, "bouncing_ball_GT");
  ssSetPath(rtS, "bouncing_ball_GT");
  ssSetTStart(rtS, 0.0);
  ssSetTFinal(rtS, 25.0);
  ssSetStepSize(rtS, 0.5);
  ssSetFixedStepSize(rtS, 0.5);

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (NULL);
    ssSetRTWLogInfo(rtS, &rt_DataLoggingInfo);
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(ssGetRTWLogInfo(rtS), (NULL));
    rtliSetLogXSignalPtrs(ssGetRTWLogInfo(rtS), (NULL));
    rtliSetLogT(ssGetRTWLogInfo(rtS), "");
    rtliSetLogX(ssGetRTWLogInfo(rtS), "");
    rtliSetLogXFinal(ssGetRTWLogInfo(rtS), "");
    rtliSetLogVarNameModifier(ssGetRTWLogInfo(rtS), "rt_");
    rtliSetLogFormat(ssGetRTWLogInfo(rtS), 0);
    rtliSetLogMaxRows(ssGetRTWLogInfo(rtS), 0);
    rtliSetLogDecimation(ssGetRTWLogInfo(rtS), 1);
    rtliSetLogY(ssGetRTWLogInfo(rtS), "");
    rtliSetLogYSignalInfo(ssGetRTWLogInfo(rtS), (NULL));
    rtliSetLogYSignalPtrs(ssGetRTWLogInfo(rtS), (NULL));
  }

  {
    static struct _ssStatesInfo2 statesInfo2;
    ssSetStatesInfo2(rtS, &statesInfo2);
  }

  {
    static ssPeriodicStatesInfo periodicStatesInfo;
    ssSetPeriodicStatesInfo(rtS, &periodicStatesInfo);
  }

  {
    static ssJacobianPerturbationBounds jacobianPerturbationBounds;
    ssSetJacobianPerturbationBounds(rtS, &jacobianPerturbationBounds);
  }

  ssSetChecksumVal(rtS, 0, 1620168392U);
  ssSetChecksumVal(rtS, 1, 3990897944U);
  ssSetChecksumVal(rtS, 2, 459595645U);
  ssSetChecksumVal(rtS, 3, 2128925529U);

  /* non-finite (run-time) assignments */
  rtP.SecondOrderIntegrator_UpperLimi = rtInf;
  return rtS;
}

/* When you use the on parameter, it resets the optimizations to those that you
   specified with the /O compiler option. */
#if defined(_MSC_VER)

#pragma optimize( "", on )

#endif
