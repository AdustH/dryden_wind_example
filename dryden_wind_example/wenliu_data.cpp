//
// File: wenliu_data.cpp
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
#include "wenliu.h"

// Invariant block signals (default storage)
const wenliu::ConstB_wenliu_T wenliu_ConstB{
  0.0
  ,                                    // '<S2>/Unit Conversion'
  49.212598425196845
  ,                                    // '<S12>/Unit Conversion'
  4.9212598425196852
  ,                                    // '<S21>/sigma_wg '
  32.808398950131227
  ,                                    // '<S6>/Unit Conversion'
  1749.9999999999998
  ,                                    // '<S40>/Unit Conversion'
  0.0
  ,                        // '<S20>/PreLook-Up Index Search  (prob of exceed)'

  {
    0.31622776601683794,
    0.31622776601683794,
    0.31622776601683794,
    0.31622776601683794
  }
  ,                                    // '<S13>/Sqrt'
  0.31622776601683794
  ,                                    // '<S13>/Sqrt1'

  {
    1.0,
    1.0,
    1.0,
    1.0
  }
  ,                                    // '<S13>/Divide'
  1000.0
  ,                                    // '<S30>/Sum'
  1000.0
  ,                                    // '<S22>/Sum'
  31.329713207066007
  ,                                    // '<S16>/dt1'
  41.772950942754676
  ,                                    // '<S15>/dt1'
  2U
  // '<S20>/PreLook-Up Index Search  (prob of exceed)'
};

// Constant parameters (default storage)
const wenliu::ConstP_wenliu_T wenliu_ConstP{
  // Expression: h_vec
  //  Referenced by: '<S20>/PreLook-Up Index Search  (altitude)'

  { 500.0, 1750.0, 3750.0, 7500.0, 15000.0, 25000.0, 35000.0, 45000.0, 55000.0,
    65000.0, 75000.0, 80000.0 },

  // Expression: sigma_vec'
  //  Referenced by: '<S20>/Medium//High Altitude Intensity'

  { 3.2, 2.2, 1.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 4.2, 3.6, 3.3,
    1.6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 6.6, 6.9, 7.4, 6.7, 4.6, 2.7,
    0.4, 0.0, 0.0, 0.0, 0.0, 0.0, 8.6, 9.6, 10.6, 10.1, 8.0, 6.6, 5.0, 4.2, 2.7,
    0.0, 0.0, 0.0, 11.8, 13.0, 16.0, 15.1, 11.6, 9.7, 8.1, 8.2, 7.9, 4.9, 3.2,
    2.1, 15.6, 17.6, 23.0, 23.6, 22.1, 20.0, 16.0, 15.1, 12.1, 7.9, 6.2, 5.1,
    18.7, 21.5, 28.4, 30.2, 30.7, 31.0, 25.2, 23.1, 17.5, 10.7, 8.4, 7.2 },

  // Computed Parameter: MediumHighAltitudeIntensity_max
  //  Referenced by: '<S20>/Medium//High Altitude Intensity'

  { 11U, 6U }
};

//
// File trailer for generated code.
//
// [EOF]
//
