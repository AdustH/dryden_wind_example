//
// File: wenliu.cpp
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
#include "rtwtypes.h"
#include "wenliu_private.h"
#include <cmath>

extern "C" {

#include "rt_nonfinite.h"

}
  static void rate_scheduler(wenliu::RT_MODEL_wenliu_T *const wenliu_M);

uint32_T plook_bincpa(real_T u, const real_T bp[], uint32_T maxIndex, real_T
                      *fraction, uint32_T *prevIndex)
{
  uint32_T bpIndex;

  // Prelookup - Index and Fraction
  // Index Search method: 'binary'
  // Extrapolation method: 'Clip'
  // Use previous index: 'on'
  // Use last breakpoint for index at or above upper limit: 'on'
  // Remove protection against out-of-range input in generated code: 'off'

  if (u <= bp[0U]) {
    bpIndex = 0U;
    *fraction = 0.0;
  } else if (u < bp[maxIndex]) {
    bpIndex = binsearch_u32d_prevIdx(u, bp, *prevIndex, maxIndex);
    *fraction = (u - bp[bpIndex]) / (bp[bpIndex + 1U] - bp[bpIndex]);
  } else {
    bpIndex = maxIndex;
    *fraction = 0.0;
  }

  *prevIndex = bpIndex;
  return bpIndex;
}

real_T intrp2d_la_pw(const uint32_T bpIndex[], const real_T frac[], const real_T
                     table[], const uint32_T stride, const uint32_T maxIndex[])
{
  real_T y;
  real_T yL_0d0;
  uint32_T offset_1d;

  // Column-major Interpolation 2-D
  // Interpolation method: 'Linear point-slope'
  // Use last breakpoint for index at or above upper limit: 'on'
  // Overflow mode: 'portable wrapping'

  offset_1d = bpIndex[1U] * stride + bpIndex[0U];
  if (bpIndex[0U] == maxIndex[0U]) {
    y = table[offset_1d];
  } else {
    yL_0d0 = table[offset_1d];
    y = (table[offset_1d + 1U] - yL_0d0) * frac[0U] + yL_0d0;
  }

  if (bpIndex[1U] == maxIndex[1U]) {
  } else {
    offset_1d += stride;
    if (bpIndex[0U] == maxIndex[0U]) {
      yL_0d0 = table[offset_1d];
    } else {
      yL_0d0 = table[offset_1d];
      yL_0d0 += (table[offset_1d + 1U] - yL_0d0) * frac[0U];
    }

    y += (yL_0d0 - y) * frac[1U];
  }

  return y;
}

uint32_T binsearch_u32d_prevIdx(real_T u, const real_T bp[], uint32_T startIndex,
  uint32_T maxIndex)
{
  uint32_T bpIndex;
  uint32_T found;
  uint32_T iLeft;
  uint32_T iRght;

  // Binary Search using Previous Index
  bpIndex = startIndex;
  iLeft = 0U;
  iRght = maxIndex;
  found = 0U;
  while (found == 0U) {
    if (u < bp[bpIndex]) {
      iRght = bpIndex - 1U;
      bpIndex = ((bpIndex + iLeft) - 1U) >> 1U;
    } else if (u < bp[bpIndex + 1U]) {
      found = 1U;
    } else {
      iLeft = bpIndex + 1U;
      bpIndex = ((bpIndex + iRght) + 1U) >> 1U;
    }
  }

  return bpIndex;
}

//
//         This function updates active task flag for each subrate.
//         The function is called at model base rate, hence the
//         generated code self-manages all its subrates.
//
static void rate_scheduler(wenliu::RT_MODEL_wenliu_T *const wenliu_M)
{
  // Compute which subrates run during the next base time step.  Subrates
  //  are an integer multiple of the base rate counter.  Therefore, the subtask
  //  counter is reset when it reaches its limit (zero means run).

  (wenliu_M->Timing.TaskCounters.TID[1])++;
  if ((wenliu_M->Timing.TaskCounters.TID[1]) > 999) {// Sample time: [0.1s, 0.0s] 
    wenliu_M->Timing.TaskCounters.TID[1] = 0;
  }
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = (rtNaN);
  } else {
    real_T tmp;
    real_T tmp_0;
    tmp = std::abs(u0);
    tmp_0 = std::abs(u1);
    if (std::isinf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = std::sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > std::floor(u1))) {
      y = (rtNaN);
    } else {
      y = std::pow(u0, u1);
    }
  }

  return y;
}

real_T rt_urand_Upu32_Yd_f_pw_snf(uint32_T *u)
{
  uint32_T hi;
  uint32_T lo;

  // Uniform random number generator (random number between 0 and 1)

  // #define IA      16807                      magic multiplier = 7^5
  // #define IM      2147483647                 modulus = 2^31-1
  // #define IQ      127773                     IM div IA
  // #define IR      2836                       IM modulo IA
  // #define S       4.656612875245797e-10      reciprocal of 2^31-1
  // test = IA * (seed % IQ) - IR * (seed/IQ)
  // seed = test < 0 ? (test + IM) : test
  // return (seed*S)

  lo = *u % 127773U * 16807U;
  hi = *u / 127773U * 2836U;
  if (lo < hi) {
    *u = 2147483647U - (hi - lo);
  } else {
    *u = lo - hi;
  }

  return static_cast<real_T>(*u) * 4.6566128752457969E-10;
}

real_T rt_nrand_Upu32_Yd_f_pw_snf(uint32_T *u)
{
  real_T si;
  real_T sr;
  real_T y;

  // Normal (Gaussian) random number generator
  do {
    sr = 2.0 * rt_urand_Upu32_Yd_f_pw_snf(u) - 1.0;
    si = 2.0 * rt_urand_Upu32_Yd_f_pw_snf(u) - 1.0;
    si = sr * sr + si * si;
  } while (si > 1.0);

  y = std::sqrt(-2.0 * std::log(si) / si) * sr;
  return y;
}

// Model step function
void wenliu::step()
{
  real_T rtb_Product_c[3];
  real_T rtb_VectorConcatenate[3];
  real_T frac[2];
  real_T rtb_PreLookUpIndexSearchaltitud;
  uint32_T bpIndex[2];
  if ((&wenliu_M)->Timing.TaskCounters.TID[1] == 0) {
    real_T Sum_d_tmp;
    real_T Sum_d_tmp_0;
    real_T frac_tmp;
    real_T frac_tmp_0;
    real_T rtb_LimitFunction10ftto1000ft;
    real_T rtb_TrigonometricFunction_o2;
    real_T rtb_UnitConversion;
    real_T rtb_UnitConversion_p;
    real_T rtb_WhiteNoise;
    real_T rtb_WhiteNoise_g;
    real_T rtb_WhiteNoise_kr;
    real_T rtb_sigma_ugsigma_vg;

    // UnitConversion: '<S5>/Unit Conversion' incorporates:
    //   Inport: '<Root>/height'

    // Unit Conversion - from: m to: ft
    // Expression: output = (3.28084*input) + (0)
    rtb_UnitConversion = 3.280839895013123 * wenliu_U.height;

    // UnitConversion: '<S11>/Unit Conversion' incorporates:
    //   Inport: '<Root>/airspeed'

    // Unit Conversion - from: m/s to: ft/s
    // Expression: output = (3.28084*input) + (0)
    rtb_UnitConversion_p = 3.280839895013123 * wenliu_U.airspeed;

    // Saturate: '<S38>/Limit Function 10ft to 1000ft' incorporates:
    //   Saturate: '<S21>/Limit Height h<1000ft'

    if (rtb_UnitConversion > 1000.0) {
      rtb_LimitFunction10ftto1000ft = 1000.0;
      rtb_PreLookUpIndexSearchaltitud = 1000.0;
    } else {
      if (rtb_UnitConversion < 10.0) {
        rtb_LimitFunction10ftto1000ft = 10.0;
      } else {
        rtb_LimitFunction10ftto1000ft = rtb_UnitConversion;
      }

      if (rtb_UnitConversion < 0.0) {
        rtb_PreLookUpIndexSearchaltitud = 0.0;
      } else {
        rtb_PreLookUpIndexSearchaltitud = rtb_UnitConversion;
      }
    }

    // End of Saturate: '<S38>/Limit Function 10ft to 1000ft'

    // Product: '<S21>/sigma_ug, sigma_vg' incorporates:
    //   Fcn: '<S21>/Low Altitude Intensity'

    rtb_sigma_ugsigma_vg = 1.0 / rt_powd_snf(0.000823 *
      rtb_PreLookUpIndexSearchaltitud + 0.177, 0.4) * wenliu_ConstB.sigma_wg;

    // Interpolation_n-D: '<S20>/Medium//High Altitude Intensity' incorporates:
    //   PreLookup: '<S20>/PreLook-Up Index Search  (altitude)'

    bpIndex[0] = plook_bincpa(rtb_UnitConversion,
      wenliu_ConstP.PreLookUpIndexSearchaltitude_Br, 11U,
      &rtb_PreLookUpIndexSearchaltitud,
      &wenliu_DW.PreLookUpIndexSearchaltitude_DW);
    frac[0] = rtb_PreLookUpIndexSearchaltitud;
    frac[1] = wenliu_ConstB.PreLookUpIndexSearchprobofe;
    bpIndex[1] = wenliu_ConstB.PreLookUpIndexSearchprobo_h;
    rtb_PreLookUpIndexSearchaltitud = intrp2d_la_pw(bpIndex, frac,
      wenliu_ConstP.MediumHighAltitudeIntensity_Tab, 12U,
      wenliu_ConstP.MediumHighAltitudeIntensity_max);

    // Product: '<S13>/Product' incorporates:
    //   RandomNumber: '<S13>/White Noise'

    rtb_WhiteNoise = wenliu_ConstB.Divide[0] * wenliu_DW.NextOutput[0];
    rtb_WhiteNoise_g = wenliu_ConstB.Divide[1] * wenliu_DW.NextOutput[1];
    rtb_TrigonometricFunction_o2 = wenliu_ConstB.Divide[2] *
      wenliu_DW.NextOutput[2];
    rtb_WhiteNoise_kr = wenliu_ConstB.Divide[3] * wenliu_DW.NextOutput[3];

    // Outputs for Enabled SubSystem: '<S4>/Hugw(z)' incorporates:
    //   EnablePort: '<S17>/Enable'

    if (!wenliu_DW.Hugwz_MODE) {
      // InitializeConditions for UnitDelay: '<S17>/Unit Delay'
      wenliu_DW.UnitDelay_DSTATE_o[0] = 0.0;
      wenliu_DW.UnitDelay_DSTATE_o[1] = 0.0;
      wenliu_DW.Hugwz_MODE = true;
    }

    // Outputs for Enabled SubSystem: '<S4>/Hvgw(z)' incorporates:
    //   EnablePort: '<S18>/Enable'

    // Product: '<S17>/V//Lug' incorporates:
    //   Fcn: '<S38>/Low Altitude Scale Length'
    //   Product: '<S18>/V//Lvg'
    //   Product: '<S19>/V//Lwg'

    frac_tmp = rtb_UnitConversion_p / (rtb_LimitFunction10ftto1000ft /
      rt_powd_snf(0.000823 * rtb_LimitFunction10ftto1000ft + 0.177, 1.2));

    // Outputs for Enabled SubSystem: '<S4>/Hwgw(z)' incorporates:
    //   EnablePort: '<S19>/Enable'

    frac_tmp_0 = rtb_UnitConversion_p / wenliu_ConstB.UnitConversion_i;

    // End of Outputs for SubSystem: '<S4>/Hwgw(z)'

    // Sum: '<S17>/Sum1' incorporates:
    //   Constant: '<S17>/Constant'
    //   Gain: '<S17>/dt'
    //   Product: '<S17>/V//Lug'
    //   Sum: '<S18>/Sum1'

    Sum_d_tmp = 1.0 - 0.1 * frac_tmp;

    // Sqrt: '<S17>/sqrt' incorporates:
    //   Gain: '<S17>/2'
    //   Product: '<S17>/V//Lug'
    //   Sqrt: '<S18>/sqrt'

    frac_tmp = std::sqrt(0.2 * frac_tmp);

    // End of Outputs for SubSystem: '<S4>/Hvgw(z)'

    // Sum: '<S17>/Sum' incorporates:
    //   Product: '<S17>/Lug//V1'
    //   Product: '<S17>/Lug//V2'
    //   Sqrt: '<S17>/sqrt'
    //   Sum: '<S17>/Sum1'
    //   UnitDelay: '<S17>/Unit Delay'

    wenliu_B.Sum_d[0] = frac_tmp * rtb_WhiteNoise * rtb_sigma_ugsigma_vg +
      Sum_d_tmp * wenliu_DW.UnitDelay_DSTATE_o[0];

    // Outputs for Enabled SubSystem: '<S4>/Hwgw(z)' incorporates:
    //   EnablePort: '<S19>/Enable'

    // Outputs for Enabled SubSystem: '<S4>/Hvgw(z)' incorporates:
    //   EnablePort: '<S18>/Enable'

    // Sum: '<S17>/Sum1' incorporates:
    //   Constant: '<S17>/Constant'
    //   Gain: '<S17>/dt'
    //   Product: '<S17>/V//Lug'
    //   Sum: '<S18>/Sum1'
    //   Sum: '<S19>/Sum1'

    Sum_d_tmp_0 = 1.0 - 0.1 * frac_tmp_0;

    // Sqrt: '<S17>/sqrt' incorporates:
    //   Gain: '<S17>/2'
    //   Product: '<S17>/V//Lug'
    //   Sqrt: '<S18>/sqrt'
    //   Sqrt: '<S19>/sqrt'

    frac_tmp_0 = std::sqrt(0.2 * frac_tmp_0);

    // End of Outputs for SubSystem: '<S4>/Hvgw(z)'
    // End of Outputs for SubSystem: '<S4>/Hwgw(z)'

    // Sum: '<S17>/Sum' incorporates:
    //   Product: '<S17>/Lug//V1'
    //   Product: '<S17>/Lug//V2'
    //   Sqrt: '<S17>/sqrt'
    //   Sum: '<S17>/Sum1'
    //   UnitDelay: '<S17>/Unit Delay'

    wenliu_B.Sum_d[1] = frac_tmp_0 * rtb_WhiteNoise *
      rtb_PreLookUpIndexSearchaltitud + Sum_d_tmp_0 *
      wenliu_DW.UnitDelay_DSTATE_o[1];

    // Update for UnitDelay: '<S17>/Unit Delay'
    wenliu_DW.UnitDelay_DSTATE_o[0] = wenliu_B.Sum_d[0];
    wenliu_DW.UnitDelay_DSTATE_o[1] = wenliu_B.Sum_d[1];

    // End of Outputs for SubSystem: '<S4>/Hugw(z)'

    // Outputs for Enabled SubSystem: '<S4>/Hvgw(z)' incorporates:
    //   EnablePort: '<S18>/Enable'

    if (!wenliu_DW.Hvgwz_MODE) {
      // InitializeConditions for UnitDelay: '<S18>/Unit Delay'
      wenliu_DW.UnitDelay_DSTATE_a[0] = 0.0;
      wenliu_DW.UnitDelay_DSTATE_a[1] = 0.0;
      wenliu_DW.Hvgwz_MODE = true;
    }

    // Sum: '<S18>/Sum' incorporates:
    //   Product: '<S18>/Lug//V1'
    //   Product: '<S18>/Lug//V2'
    //   UnitDelay: '<S18>/Unit Delay'

    wenliu_B.Sum_l[0] = frac_tmp * rtb_WhiteNoise_g * rtb_sigma_ugsigma_vg +
      Sum_d_tmp * wenliu_DW.UnitDelay_DSTATE_a[0];
    wenliu_B.Sum_l[1] = frac_tmp_0 * rtb_WhiteNoise_g *
      rtb_PreLookUpIndexSearchaltitud + Sum_d_tmp_0 *
      wenliu_DW.UnitDelay_DSTATE_a[1];

    // Update for UnitDelay: '<S18>/Unit Delay'
    wenliu_DW.UnitDelay_DSTATE_a[0] = wenliu_B.Sum_l[0];
    wenliu_DW.UnitDelay_DSTATE_a[1] = wenliu_B.Sum_l[1];

    // End of Outputs for SubSystem: '<S4>/Hvgw(z)'

    // Outputs for Enabled SubSystem: '<S4>/Hwgw(z)' incorporates:
    //   EnablePort: '<S19>/Enable'

    if (!wenliu_DW.Hwgwz_MODE) {
      // InitializeConditions for UnitDelay: '<S19>/Unit Delay'
      wenliu_DW.UnitDelay_DSTATE[0] = 0.0;
      wenliu_DW.UnitDelay_DSTATE[1] = 0.0;
      wenliu_DW.Hwgwz_MODE = true;
    }

    // Product: '<S19>/V//Lwg' incorporates:
    //   Gain: '<S10>/Lw'

    rtb_sigma_ugsigma_vg = rtb_UnitConversion_p / rtb_LimitFunction10ftto1000ft;

    // Sum: '<S19>/Sum' incorporates:
    //   Constant: '<S19>/Constant'
    //   Gain: '<S19>/2'
    //   Gain: '<S19>/dt'
    //   Product: '<S19>/Lug//V1'
    //   Product: '<S19>/Lug//V2'
    //   Sqrt: '<S19>/sqrt'
    //   Sum: '<S19>/Sum1'
    //   UnitDelay: '<S19>/Unit Delay'

    wenliu_B.Sum[0] = (1.0 - 0.1 * rtb_sigma_ugsigma_vg) *
      wenliu_DW.UnitDelay_DSTATE[0] + std::sqrt(0.2 * rtb_sigma_ugsigma_vg) *
      rtb_TrigonometricFunction_o2 * wenliu_ConstB.sigma_wg;
    wenliu_B.Sum[1] = frac_tmp_0 * rtb_TrigonometricFunction_o2 *
      rtb_PreLookUpIndexSearchaltitud + Sum_d_tmp_0 *
      wenliu_DW.UnitDelay_DSTATE[1];

    // Update for UnitDelay: '<S19>/Unit Delay'
    wenliu_DW.UnitDelay_DSTATE[0] = wenliu_B.Sum[0];
    wenliu_DW.UnitDelay_DSTATE[1] = wenliu_B.Sum[1];

    // End of Outputs for SubSystem: '<S4>/Hwgw(z)'

    // If: '<S9>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' 
    if (rtb_UnitConversion <= 1000.0) {
      // Outputs for IfAction SubSystem: '<S9>/Low altitude  velocities' incorporates:
      //   ActionPort: '<S31>/Action Port'

      // SignalConversion generated from: '<S36>/Vector Concatenate'
      rtb_Product_c[2] = wenliu_B.Sum[0];

      // Trigonometry: '<S37>/Trigonometric Function' incorporates:
      //   UnitConversion: '<S2>/Unit Conversion'

      rtb_UnitConversion = std::sin(wenliu_ConstB.UnitConversion);
      rtb_sigma_ugsigma_vg = std::cos(wenliu_ConstB.UnitConversion);

      // Sum: '<S37>/Sum' incorporates:
      //   Product: '<S37>/Product1'
      //   Product: '<S37>/Product2'

      rtb_Product_c[0] = wenliu_B.Sum_d[0] * rtb_sigma_ugsigma_vg -
        rtb_UnitConversion * wenliu_B.Sum_l[0];

      // Sum: '<S37>/Sum1' incorporates:
      //   Product: '<S37>/Product1'
      //   Product: '<S37>/Product2'

      rtb_Product_c[1] = rtb_UnitConversion * wenliu_B.Sum_d[0] +
        wenliu_B.Sum_l[0] * rtb_sigma_ugsigma_vg;

      // Reshape: '<S36>/Reshape1' incorporates:
      //   Concatenate: '<S36>/Vector Concatenate'
      //   Product: '<S36>/Product'
      //   SignalConversion generated from: '<S36>/Product'

      for (int32_T i{0}; i < 3; i++) {
        rtb_VectorConcatenate[i] = (0.0 * rtb_Product_c[1] + 0.0 *
          rtb_Product_c[0]) + 0.0 * rtb_Product_c[2];
      }

      // End of Reshape: '<S36>/Reshape1'
      // End of Outputs for SubSystem: '<S9>/Low altitude  velocities'
    } else if (rtb_UnitConversion >= 2000.0) {
      // Outputs for IfAction SubSystem: '<S9>/Medium//High  altitude velocities' incorporates:
      //   ActionPort: '<S32>/Action Port'

      // Gain: '<S32>/Gain'
      rtb_VectorConcatenate[0] = wenliu_B.Sum_d[1];
      rtb_VectorConcatenate[1] = wenliu_B.Sum_l[1];
      rtb_VectorConcatenate[2] = wenliu_B.Sum[1];

      // End of Outputs for SubSystem: '<S9>/Medium//High  altitude velocities'
    } else {
      // Outputs for IfAction SubSystem: '<S9>/Interpolate  velocities' incorporates:
      //   ActionPort: '<S30>/Action Port'

      // Trigonometry: '<S35>/Trigonometric Function' incorporates:
      //   UnitConversion: '<S2>/Unit Conversion'

      rtb_sigma_ugsigma_vg = std::sin(wenliu_ConstB.UnitConversion);
      rtb_TrigonometricFunction_o2 = std::cos(wenliu_ConstB.UnitConversion);

      // Sum: '<S35>/Sum' incorporates:
      //   Product: '<S35>/Product1'
      //   Product: '<S35>/Product2'

      rtb_VectorConcatenate[0] = wenliu_B.Sum_d[0] *
        rtb_TrigonometricFunction_o2 - rtb_sigma_ugsigma_vg * wenliu_B.Sum_l[0];

      // Sum: '<S35>/Sum1' incorporates:
      //   Product: '<S35>/Product1'
      //   Product: '<S35>/Product2'

      rtb_VectorConcatenate[1] = rtb_sigma_ugsigma_vg * wenliu_B.Sum_d[0] +
        wenliu_B.Sum_l[0] * rtb_TrigonometricFunction_o2;

      // SignalConversion generated from: '<S34>/Vector Concatenate'
      rtb_VectorConcatenate[2] = wenliu_B.Sum[0];

      // Product: '<S34>/Product' incorporates:
      //   Concatenate: '<S34>/Vector Concatenate'
      //   SignalConversion generated from: '<S34>/Product'

      for (int32_T i{0}; i < 3; i++) {
        rtb_Product_c[i] = (0.0 * rtb_VectorConcatenate[1] + 0.0 *
                            rtb_VectorConcatenate[0]) + 0.0 *
          rtb_VectorConcatenate[2];
      }

      // End of Product: '<S34>/Product'

      // Sum: '<S30>/Sum3' incorporates:
      //   Constant: '<S30>/max_height_low'
      //   Product: '<S30>/Product1'
      //   Sum: '<S30>/Sum1'
      //   Sum: '<S30>/Sum2'

      rtb_VectorConcatenate[0] = (wenliu_B.Sum_d[1] - rtb_Product_c[0]) *
        (rtb_UnitConversion - 1000.0) / wenliu_ConstB.Sum + rtb_Product_c[0];
      rtb_VectorConcatenate[1] = (wenliu_B.Sum_l[1] - rtb_Product_c[1]) *
        (rtb_UnitConversion - 1000.0) / wenliu_ConstB.Sum + rtb_Product_c[1];
      rtb_VectorConcatenate[2] = (wenliu_B.Sum[1] - rtb_Product_c[2]) *
        (rtb_UnitConversion - 1000.0) / wenliu_ConstB.Sum + rtb_Product_c[2];

      // End of Outputs for SubSystem: '<S9>/Interpolate  velocities'
    }

    // End of If: '<S9>/if Height < Max low altitude  elseif Height > Min isotropic altitude ' 

    // Outport: '<Root>/Vy' incorporates:
    //   UnitConversion: '<S1>/Unit Conversion'

    // Unit Conversion - from: ft/s to: m/s
    // Expression: output = (0.3048*input) + (0)
    wenliu_Y.Vy = 0.3048 * rtb_VectorConcatenate[1];

    // Outport: '<Root>/Vz' incorporates:
    //   UnitConversion: '<S1>/Unit Conversion'

    wenliu_Y.Vz = 0.3048 * rtb_VectorConcatenate[2];

    // Outport: '<Root>/Vx' incorporates:
    //   UnitConversion: '<S1>/Unit Conversion'

    wenliu_Y.Vx = 0.3048 * rtb_VectorConcatenate[0];

    // Outputs for Enabled SubSystem: '<S3>/Hpgw' incorporates:
    //   EnablePort: '<S14>/Enable'

    if (!wenliu_DW.Hpgw_MODE) {
      // InitializeConditions for UnitDelay: '<S14>/Unit Delay'
      wenliu_DW.UnitDelay_DSTATE_l[0] = 0.0;
      wenliu_DW.UnitDelay_DSTATE_l[1] = 0.0;
      wenliu_DW.Hpgw_MODE = true;
    }

    // Product: '<S14>/w2' incorporates:
    //   Gain: '<S10>/Lw'

    rtb_LimitFunction10ftto1000ft *= wenliu_ConstB.UnitConversion_l;

    // Product: '<S14>/w4'
    rtb_UnitConversion = rtb_LimitFunction10ftto1000ft *
      wenliu_ConstB.UnitConversion_l;

    // Product: '<S14>/w1' incorporates:
    //   Constant: '<S14>/Constant2'
    //   Sqrt: '<S14>/sqrt'

    rtb_LimitFunction10ftto1000ft = 2.6 / std::sqrt
      (rtb_LimitFunction10ftto1000ft);

    // Math: '<S14>/Math Function'
    if (rtb_UnitConversion < 0.0) {
      rtb_UnitConversion = -rt_powd_snf(-rtb_UnitConversion, 0.33333333333333331);
    } else {
      rtb_UnitConversion = rt_powd_snf(rtb_UnitConversion, 0.33333333333333331);
    }

    // Update for UnitDelay: '<S14>/Unit Delay' incorporates:
    //   Constant: '<S14>/Constant'
    //   Constant: '<S14>/Constant1'
    //   Gain: '<S14>/2'
    //   Gain: '<S14>/dt'
    //   Product: '<S14>/Lug//V1'
    //   Product: '<S14>/Lug//V2'
    //   Product: '<S14>/w3'
    //   Sqrt: '<S14>/sqrt1'
    //   Sum: '<S14>/Sum'
    //   Sum: '<S14>/Sum1'

    wenliu_DW.UnitDelay_DSTATE_l[0] = 0.95 / rtb_UnitConversion *
      wenliu_ConstB.sigma_wg * std::sqrt(0.2 * rtb_LimitFunction10ftto1000ft) *
      rtb_WhiteNoise_kr + (1.0 - 0.1 * rtb_LimitFunction10ftto1000ft) *
      wenliu_DW.UnitDelay_DSTATE_l[0];

    // Product: '<S14>/w2' incorporates:
    //   Gain: '<S10>/Lw'

    rtb_LimitFunction10ftto1000ft = wenliu_ConstB.UnitConversion_i *
      wenliu_ConstB.UnitConversion_l;

    // Product: '<S14>/w4'
    rtb_UnitConversion = rtb_LimitFunction10ftto1000ft *
      wenliu_ConstB.UnitConversion_l;

    // Product: '<S14>/w1' incorporates:
    //   Constant: '<S14>/Constant2'
    //   Sqrt: '<S14>/sqrt'

    rtb_LimitFunction10ftto1000ft = 2.6 / std::sqrt
      (rtb_LimitFunction10ftto1000ft);

    // Math: '<S14>/Math Function'
    if (rtb_UnitConversion < 0.0) {
      rtb_UnitConversion = -rt_powd_snf(-rtb_UnitConversion, 0.33333333333333331);
    } else {
      rtb_UnitConversion = rt_powd_snf(rtb_UnitConversion, 0.33333333333333331);
    }

    // Update for UnitDelay: '<S14>/Unit Delay' incorporates:
    //   Constant: '<S14>/Constant'
    //   Constant: '<S14>/Constant1'
    //   Gain: '<S14>/2'
    //   Gain: '<S14>/dt'
    //   Product: '<S14>/Lug//V1'
    //   Product: '<S14>/Lug//V2'
    //   Product: '<S14>/w3'
    //   Sqrt: '<S14>/sqrt1'
    //   Sum: '<S14>/Sum'
    //   Sum: '<S14>/Sum1'

    wenliu_DW.UnitDelay_DSTATE_l[1] = 0.95 / rtb_UnitConversion *
      rtb_PreLookUpIndexSearchaltitud * std::sqrt(0.2 *
      rtb_LimitFunction10ftto1000ft) * rtb_WhiteNoise_kr + (1.0 - 0.1 *
      rtb_LimitFunction10ftto1000ft) * wenliu_DW.UnitDelay_DSTATE_l[1];

    // End of Outputs for SubSystem: '<S3>/Hpgw'

    // Outputs for Enabled SubSystem: '<S3>/Hqgw' incorporates:
    //   EnablePort: '<S15>/Enable'

    if (!wenliu_DW.Hqgw_MODE) {
      // InitializeConditions for UnitDelay: '<S15>/Unit Delay'
      wenliu_DW.UnitDelay_DSTATE_i[0] = 0.0;

      // InitializeConditions for UnitDelay: '<S15>/Unit Delay1'
      wenliu_DW.UnitDelay1_DSTATE_d[0] = 0.0;

      // InitializeConditions for UnitDelay: '<S15>/Unit Delay'
      wenliu_DW.UnitDelay_DSTATE_i[1] = 0.0;

      // InitializeConditions for UnitDelay: '<S15>/Unit Delay1'
      wenliu_DW.UnitDelay1_DSTATE_d[1] = 0.0;
      wenliu_DW.Hqgw_MODE = true;
    }

    // Sum: '<S15>/Sum2' incorporates:
    //   Constant: '<S15>/Constant'
    //   Gain: '<S15>/dt'
    //   Product: '<S15>/w1'

    rtb_PreLookUpIndexSearchaltitud = 1.0 - rtb_UnitConversion_p /
      wenliu_ConstB.dt1_j * 0.1;

    // Update for UnitDelay: '<S15>/Unit Delay' incorporates:
    //   Product: '<S15>/Lug//V2'
    //   Product: '<S15>/w2'
    //   Sum: '<S15>/Sum1'
    //   Sum: '<S15>/Sum3'
    //   UnitDelay: '<S15>/Unit Delay1'

    wenliu_DW.UnitDelay_DSTATE_i[0] = (wenliu_B.Sum[0] -
      wenliu_DW.UnitDelay1_DSTATE_d[0]) / wenliu_ConstB.dt1_j +
      rtb_PreLookUpIndexSearchaltitud * wenliu_DW.UnitDelay_DSTATE_i[0];

    // Update for UnitDelay: '<S15>/Unit Delay1'
    wenliu_DW.UnitDelay1_DSTATE_d[0] = wenliu_B.Sum[0];

    // Update for UnitDelay: '<S15>/Unit Delay' incorporates:
    //   Product: '<S15>/Lug//V2'
    //   Product: '<S15>/w2'
    //   Sum: '<S15>/Sum1'
    //   Sum: '<S15>/Sum3'
    //   UnitDelay: '<S15>/Unit Delay1'

    wenliu_DW.UnitDelay_DSTATE_i[1] = (wenliu_B.Sum[1] -
      wenliu_DW.UnitDelay1_DSTATE_d[1]) / wenliu_ConstB.dt1_j +
      rtb_PreLookUpIndexSearchaltitud * wenliu_DW.UnitDelay_DSTATE_i[1];

    // Update for UnitDelay: '<S15>/Unit Delay1'
    wenliu_DW.UnitDelay1_DSTATE_d[1] = wenliu_B.Sum[1];

    // End of Outputs for SubSystem: '<S3>/Hqgw'

    // Outputs for Enabled SubSystem: '<S3>/Hrgw' incorporates:
    //   EnablePort: '<S16>/Enable'

    if (!wenliu_DW.Hrgw_MODE) {
      // InitializeConditions for UnitDelay: '<S16>/Unit Delay'
      wenliu_DW.UnitDelay_DSTATE_n[0] = 0.0;

      // InitializeConditions for UnitDelay: '<S16>/Unit Delay1'
      wenliu_DW.UnitDelay1_DSTATE[0] = 0.0;

      // InitializeConditions for UnitDelay: '<S16>/Unit Delay'
      wenliu_DW.UnitDelay_DSTATE_n[1] = 0.0;

      // InitializeConditions for UnitDelay: '<S16>/Unit Delay1'
      wenliu_DW.UnitDelay1_DSTATE[1] = 0.0;
      wenliu_DW.Hrgw_MODE = true;
    }

    // Sum: '<S16>/Sum2' incorporates:
    //   Constant: '<S16>/Constant'
    //   Gain: '<S16>/dt'
    //   Product: '<S16>/w1'

    rtb_UnitConversion_p = 1.0 - rtb_UnitConversion_p / wenliu_ConstB.dt1 * 0.1;

    // Update for UnitDelay: '<S16>/Unit Delay' incorporates:
    //   Product: '<S16>/Lug//V2'
    //   Product: '<S16>/w2'
    //   Sum: '<S16>/Sum1'
    //   Sum: '<S16>/Sum3'
    //   UnitDelay: '<S16>/Unit Delay1'

    wenliu_DW.UnitDelay_DSTATE_n[0] = (wenliu_B.Sum_l[0] -
      wenliu_DW.UnitDelay1_DSTATE[0]) / wenliu_ConstB.dt1 + rtb_UnitConversion_p
      * wenliu_DW.UnitDelay_DSTATE_n[0];

    // Update for UnitDelay: '<S16>/Unit Delay1'
    wenliu_DW.UnitDelay1_DSTATE[0] = wenliu_B.Sum_l[0];

    // Update for UnitDelay: '<S16>/Unit Delay' incorporates:
    //   Product: '<S16>/Lug//V2'
    //   Product: '<S16>/w2'
    //   Sum: '<S16>/Sum1'
    //   Sum: '<S16>/Sum3'
    //   UnitDelay: '<S16>/Unit Delay1'

    wenliu_DW.UnitDelay_DSTATE_n[1] = (wenliu_B.Sum_l[1] -
      wenliu_DW.UnitDelay1_DSTATE[1]) / wenliu_ConstB.dt1 + rtb_UnitConversion_p
      * wenliu_DW.UnitDelay_DSTATE_n[1];

    // Update for UnitDelay: '<S16>/Unit Delay1'
    wenliu_DW.UnitDelay1_DSTATE[1] = wenliu_B.Sum_l[1];

    // End of Outputs for SubSystem: '<S3>/Hrgw'

    // Update for RandomNumber: '<S13>/White Noise'
    wenliu_DW.NextOutput[0] = rt_nrand_Upu32_Yd_f_pw_snf(&wenliu_DW.RandSeed[0]);
    wenliu_DW.NextOutput[1] = rt_nrand_Upu32_Yd_f_pw_snf(&wenliu_DW.RandSeed[1]);
    wenliu_DW.NextOutput[2] = rt_nrand_Upu32_Yd_f_pw_snf(&wenliu_DW.RandSeed[2]);
    wenliu_DW.NextOutput[3] = rt_nrand_Upu32_Yd_f_pw_snf(&wenliu_DW.RandSeed[3]);
  }

  // Matfile logging
  rt_UpdateTXYLogVars((&wenliu_M)->rtwLogInfo, (&(&wenliu_M)->Timing.taskTime0));

  // signal main to stop simulation
  {                                    // Sample time: [0.0001s, 0.0s]
    if ((rtmGetTFinal((&wenliu_M))!=-1) &&
        !((rtmGetTFinal((&wenliu_M))-(&wenliu_M)->Timing.taskTime0) > (&wenliu_M)
          ->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus((&wenliu_M), "Simulation finished");
    }
  }

  // Update absolute time for base rate
  // The "clockTick0" counts the number of times the code of this task has
  //  been executed. The absolute time is the multiplication of "clockTick0"
  //  and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
  //  overflow during the application lifespan selected.

  (&wenliu_M)->Timing.taskTime0 =
    ((time_T)(++(&wenliu_M)->Timing.clockTick0)) * (&wenliu_M)->Timing.stepSize0;
  rate_scheduler((&wenliu_M));
}

// Model initialize function
void wenliu::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));
  rtmSetTFinal((&wenliu_M), 0.1);
  (&wenliu_M)->Timing.stepSize0 = 0.0001;

  // Setup for data logging
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (nullptr);
    (&wenliu_M)->rtwLogInfo = &rt_DataLoggingInfo;
  }

  // Setup for data logging
  {
    rtliSetLogXSignalInfo((&wenliu_M)->rtwLogInfo, (nullptr));
    rtliSetLogXSignalPtrs((&wenliu_M)->rtwLogInfo, (nullptr));
    rtliSetLogT((&wenliu_M)->rtwLogInfo, "tout");
    rtliSetLogX((&wenliu_M)->rtwLogInfo, "");
    rtliSetLogXFinal((&wenliu_M)->rtwLogInfo, "");
    rtliSetLogVarNameModifier((&wenliu_M)->rtwLogInfo, "rt_");
    rtliSetLogFormat((&wenliu_M)->rtwLogInfo, 4);
    rtliSetLogMaxRows((&wenliu_M)->rtwLogInfo, 0);
    rtliSetLogDecimation((&wenliu_M)->rtwLogInfo, 1);
    rtliSetLogY((&wenliu_M)->rtwLogInfo, "");
    rtliSetLogYSignalInfo((&wenliu_M)->rtwLogInfo, (nullptr));
    rtliSetLogYSignalPtrs((&wenliu_M)->rtwLogInfo, (nullptr));
  }

  // Matfile logging
  rt_StartDataLoggingWithStartTime((&wenliu_M)->rtwLogInfo, 0.0, rtmGetTFinal
    ((&wenliu_M)), (&wenliu_M)->Timing.stepSize0, (&rtmGetErrorStatus((&wenliu_M))));

  // InitializeConditions for RandomNumber: '<S13>/White Noise'
  wenliu_DW.RandSeed[0] = 1529675776U;
  wenliu_DW.NextOutput[0] = rt_nrand_Upu32_Yd_f_pw_snf(&wenliu_DW.RandSeed[0]);
  wenliu_DW.RandSeed[1] = 1529741312U;
  wenliu_DW.NextOutput[1] = rt_nrand_Upu32_Yd_f_pw_snf(&wenliu_DW.RandSeed[1]);
  wenliu_DW.RandSeed[2] = 1529806848U;
  wenliu_DW.NextOutput[2] = rt_nrand_Upu32_Yd_f_pw_snf(&wenliu_DW.RandSeed[2]);
  wenliu_DW.RandSeed[3] = 1529872384U;
  wenliu_DW.NextOutput[3] = rt_nrand_Upu32_Yd_f_pw_snf(&wenliu_DW.RandSeed[3]);
}

// Model terminate function
void wenliu::terminate()
{
  // (no terminate code required)
}

// Constructor
wenliu::wenliu() :
  wenliu_U(),
  wenliu_Y(),
  wenliu_B(),
  wenliu_DW(),
  wenliu_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
wenliu::~wenliu()
{
  // Currently there is no destructor body generated.
}

// Real-Time Model get method
wenliu::RT_MODEL_wenliu_T * wenliu::getRTM()
{
  return (&wenliu_M);
}

//
// File trailer for generated code.
//
// [EOF]
//
