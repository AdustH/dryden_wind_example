//
// File: wenliu.h
//
// Code generated for Simulink model 'wenliu'.
//
// Model version                  : 1.2
// Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
// C/C++ source code generated on : Wed May 15 18:24:19 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_wenliu_h_
#define RTW_HEADER_wenliu_h_
#include "rtwtypes.h"
#include "rt_logging.h"
#include "wenliu_types.h"
#include <cfloat>

extern "C" {

#include "rt_nonfinite.h"

}
// Macros for accessing real-time model data structure
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

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
#define rtmGetT(rtm)                   ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                (&(rtm)->Timing.taskTime0)
#endif

// Class declaration for model wenliu
class wenliu final
{
  // public data and function members
 public:
  // Block signals (default storage)
  struct B_wenliu_T {
    real_T Sum[2];                     // '<S19>/Sum'
    real_T Sum_l[2];                   // '<S18>/Sum'
    real_T Sum_d[2];                   // '<S17>/Sum'
  };

  // Block states (default storage) for system '<Root>'
  struct DW_wenliu_T {
    real_T UnitDelay_DSTATE[2];        // '<S19>/Unit Delay'
    real_T UnitDelay_DSTATE_a[2];      // '<S18>/Unit Delay'
    real_T UnitDelay_DSTATE_o[2];      // '<S17>/Unit Delay'
    real_T UnitDelay_DSTATE_n[2];      // '<S16>/Unit Delay'
    real_T UnitDelay1_DSTATE[2];       // '<S16>/Unit Delay1'
    real_T UnitDelay_DSTATE_i[2];      // '<S15>/Unit Delay'
    real_T UnitDelay1_DSTATE_d[2];     // '<S15>/Unit Delay1'
    real_T UnitDelay_DSTATE_l[2];      // '<S14>/Unit Delay'
    real_T NextOutput[4];              // '<S13>/White Noise'
    uint32_T PreLookUpIndexSearchprobofexcee;
                           // '<S20>/PreLook-Up Index Search  (prob of exceed)'
    uint32_T PreLookUpIndexSearchaltitude_DW;
                                 // '<S20>/PreLook-Up Index Search  (altitude)'
    uint32_T RandSeed[4];              // '<S13>/White Noise'
    boolean_T Hwgwz_MODE;              // '<S4>/Hwgw(z)'
    boolean_T Hvgwz_MODE;              // '<S4>/Hvgw(z)'
    boolean_T Hugwz_MODE;              // '<S4>/Hugw(z)'
    boolean_T Hrgw_MODE;               // '<S3>/Hrgw'
    boolean_T Hqgw_MODE;               // '<S3>/Hqgw'
    boolean_T Hpgw_MODE;               // '<S3>/Hpgw'
  };

  // Invariant block signals (default storage)
  struct ConstB_wenliu_T {
    real_T UnitConversion;             // '<S2>/Unit Conversion'
    real_T UnitConversion_h;           // '<S12>/Unit Conversion'
    real_T sigma_wg;                   // '<S21>/sigma_wg '
    real_T UnitConversion_l;           // '<S6>/Unit Conversion'
    real_T UnitConversion_i;           // '<S40>/Unit Conversion'
    real_T PreLookUpIndexSearchprobofe;
                           // '<S20>/PreLook-Up Index Search  (prob of exceed)'
    real_T Sqrt[4];                    // '<S13>/Sqrt'
    real_T Sqrt1;                      // '<S13>/Sqrt1'
    real_T Divide[4];                  // '<S13>/Divide'
    real_T Sum;                        // '<S30>/Sum'
    real_T Sum_m;                      // '<S22>/Sum'
    real_T dt1;                        // '<S16>/dt1'
    real_T dt1_j;                      // '<S15>/dt1'
    uint32_T PreLookUpIndexSearchprobo_h;
                           // '<S20>/PreLook-Up Index Search  (prob of exceed)'
  };

  // Constant parameters (default storage)
  struct ConstP_wenliu_T {
    // Expression: h_vec
    //  Referenced by: '<S20>/PreLook-Up Index Search  (altitude)'

    real_T PreLookUpIndexSearchaltitude_Br[12];

    // Expression: sigma_vec'
    //  Referenced by: '<S20>/Medium//High Altitude Intensity'

    real_T MediumHighAltitudeIntensity_Tab[84];

    // Computed Parameter: MediumHighAltitudeIntensity_max
    //  Referenced by: '<S20>/Medium//High Altitude Intensity'

    uint32_T MediumHighAltitudeIntensity_max[2];
  };

  // External inputs (root inport signals with default storage)
  struct ExtU_wenliu_T {
    real_T height;                     // '<Root>/height'
    real_T airspeed;                   // '<Root>/airspeed'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY_wenliu_T {
    real_T Vy;                         // '<Root>/Vy'
    real_T Vz;                         // '<Root>/Vz'
    real_T Vx;                         // '<Root>/Vx'
  };

  // Real-time Model Data Structure
  struct RT_MODEL_wenliu_T {
    const char_T *errorStatus;
    RTWLogInfo *rtwLogInfo;

    //
    //  Timing:
    //  The following substructure contains information regarding
    //  the timing information for the model.

    struct {
      time_T taskTime0;
      uint32_T clockTick0;
      time_T stepSize0;
      struct {
        uint16_T TID[2];
      } TaskCounters;

      time_T tFinal;
      boolean_T stopRequestedFlag;
    } Timing;
  };

  // Copy Constructor
  wenliu(wenliu const&) = delete;

  // Assignment Operator
  wenliu& operator= (wenliu const&) & = delete;

  // Move Constructor
  wenliu(wenliu &&) = delete;

  // Move Assignment Operator
  wenliu& operator= (wenliu &&) = delete;

  // Real-Time Model get method
  wenliu::RT_MODEL_wenliu_T * getRTM();

  // Root inports set method
  void setExternalInputs(const ExtU_wenliu_T *pExtU_wenliu_T)
  {
    wenliu_U = *pExtU_wenliu_T;
  }

  // Root outports get method
  const ExtY_wenliu_T &getExternalOutputs() const
  {
    return wenliu_Y;
  }

  // model initialize function
  void initialize();

  // model step function
  void step();

  // model terminate function
  static void terminate();

  // Constructor
  wenliu();

  // Destructor
  ~wenliu();

  // private data and function members
 private:
  // External inputs
  ExtU_wenliu_T wenliu_U;

  // External outputs
  ExtY_wenliu_T wenliu_Y;

  // Block signals
  B_wenliu_T wenliu_B;

  // Block states
  DW_wenliu_T wenliu_DW;

  // Real-Time Model
  RT_MODEL_wenliu_T wenliu_M;
};

extern const wenliu::ConstB_wenliu_T wenliu_ConstB;// constant block i/o

// Constant parameters (default storage)
extern const wenliu::ConstP_wenliu_T wenliu_ConstP;

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S1>/Cast' : Unused code path elimination
//  Block '<S1>/Cast To Double' : Eliminate redundant data type conversion
//  Block '<S1>/Cast To Double1' : Eliminate redundant data type conversion
//  Block '<S1>/Cast To Double2' : Eliminate redundant data type conversion
//  Block '<S1>/Cast To Double3' : Eliminate redundant data type conversion
//  Block '<S1>/Cast To Double4' : Eliminate redundant data type conversion
//  Block '<S26>/Reshape' : Reshape block reduction
//  Block '<S26>/Reshape1' : Reshape block reduction
//  Block '<S28>/Reshape' : Reshape block reduction
//  Block '<S34>/Reshape' : Reshape block reduction
//  Block '<S34>/Reshape1' : Reshape block reduction
//  Block '<S36>/Reshape' : Reshape block reduction


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'wenliu'
//  '<S1>'   : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))'
//  '<S2>'   : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Angle Conversion'
//  '<S3>'   : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Filters on angular rates'
//  '<S4>'   : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Filters on velocities'
//  '<S5>'   : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Length Conversion'
//  '<S6>'   : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Length Conversion1'
//  '<S7>'   : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/RMS turbulence  intensities'
//  '<S8>'   : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Select angular rates'
//  '<S9>'   : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Select velocities'
//  '<S10>'  : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Turbulence scale lengths'
//  '<S11>'  : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Velocity Conversion'
//  '<S12>'  : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Velocity Conversion2'
//  '<S13>'  : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/White Noise'
//  '<S14>'  : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Filters on angular rates/Hpgw'
//  '<S15>'  : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Filters on angular rates/Hqgw'
//  '<S16>'  : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Filters on angular rates/Hrgw'
//  '<S17>'  : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Filters on velocities/Hugw(z)'
//  '<S18>'  : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Filters on velocities/Hvgw(z)'
//  '<S19>'  : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Filters on velocities/Hwgw(z)'
//  '<S20>'  : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/RMS turbulence  intensities/High Altitude Intensity'
//  '<S21>'  : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/RMS turbulence  intensities/Low Altitude Intensity'
//  '<S22>'  : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Select angular rates/Interpolate  rates'
//  '<S23>'  : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Select angular rates/Low altitude  rates'
//  '<S24>'  : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Select angular rates/Medium//High  altitude rates'
//  '<S25>'  : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Select angular rates/Merge Subsystems'
//  '<S26>'  : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Select angular rates/Interpolate  rates/wind to body transformation'
//  '<S27>'  : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Select angular rates/Interpolate  rates/wind to body transformation/convert to earth coords'
//  '<S28>'  : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Select angular rates/Low altitude  rates/wind to body transformation'
//  '<S29>'  : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Select angular rates/Low altitude  rates/wind to body transformation/convert to earth coords'
//  '<S30>'  : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Select velocities/Interpolate  velocities'
//  '<S31>'  : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Select velocities/Low altitude  velocities'
//  '<S32>'  : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Select velocities/Medium//High  altitude velocities'
//  '<S33>'  : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Select velocities/Merge Subsystems'
//  '<S34>'  : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Select velocities/Interpolate  velocities/wind to body transformation'
//  '<S35>'  : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Select velocities/Interpolate  velocities/wind to body transformation/convert to earth coords'
//  '<S36>'  : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Select velocities/Low altitude  velocities/wind to body transformation'
//  '<S37>'  : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Select velocities/Low altitude  velocities/wind to body transformation/convert to earth coords'
//  '<S38>'  : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Turbulence scale lengths/Low altitude scale length'
//  '<S39>'  : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Turbulence scale lengths/Medium//High altitude scale length'
//  '<S40>'  : 'wenliu/Dryden Wind Turbulence Model  (Discrete (+q +r))/Turbulence scale lengths/Medium//High altitude scale length/Length Conversion'

#endif                                 // RTW_HEADER_wenliu_h_

//
// File trailer for generated code.
//
// [EOF]
//
