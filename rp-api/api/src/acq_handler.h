/**
 * $Id: $
 *
 * @brief Red Pitaya library Acquire signal handler interface
 *
 * @Author Red Pitaya
 *
 * (c) Red Pitaya  http://www.redpitaya.com
 *
 * This part of code is written in C programming language.
 * Please visit http://en.wikipedia.org/wiki/C_(programming_language)
 * for more details on the language used herein.
 */

#ifndef SRC_ACQ_HANDLER_H_
#define SRC_ACQ_HANDLER_H_

#include <stdint.h>
#include <stdbool.h>
#include "rp_cross.h"
#include "calib.h"

#define ADC_SAMPLE_PERIOD_DEF ((double)1e9/(double)ADC_SAMPLE_RATE)

int acq_SetArmKeep(bool enable);
int acq_GetArmKeep(bool* state);
int acq_GetBufferFillState(bool* state);
int acq_SetGain(rp_channel_t channel, rp_pinState_t state);
int acq_GetGain(rp_channel_t channel, rp_pinState_t* state);
int acq_GetGainV(rp_channel_t channel, float* voltage);
int acq_SetDecimation(rp_acq_decimation_t decimation);
int acq_GetDecimation(rp_acq_decimation_t* decimation);
int acq_SetDecimationFactor(uint32_t decimation);
int acq_GetDecimationFactor(uint32_t* decimation);
int acq_ConvertFactorToDecimation(uint32_t factor,rp_acq_decimation_t* decimation);
int acq_SetSamplingRate(rp_acq_sampling_rate_t sampling_rate);
int acq_GetSamplingRate(rp_acq_sampling_rate_t* sampling_rate);
int acq_GetSamplingRateHz(float* sampling_rate);
int acq_SetAveraging(bool enable);
int acq_GetAveraging(bool* enable);
int acq_SetTriggerSrc(rp_acq_trig_src_t source);
int acq_GetTriggerSrc(rp_acq_trig_src_t* source);
int acq_GetTriggerState(rp_acq_trig_state_t* state);
int acq_SetTriggerDelay(int32_t decimated_data_num, bool updateMaxValue);
int acq_GetTriggerDelay(int32_t* decimated_data_num);
int acq_SetTriggerDelayNs(int64_t time_ns, bool updateMaxValue);
int acq_GetTriggerDelayNs(int64_t* time_ns);
int acq_SetTriggerLevel(rp_channel_trigger_t channel, float voltage);
int acq_GetTriggerLevel(rp_channel_trigger_t channel, float *voltage);
int acq_GetPreTriggerCounter(uint32_t* value);
int acq_SetChannelThreshold(rp_channel_t channel, float voltage);
int acq_GetChannelThreshold(rp_channel_t channel, float* voltage);
int acq_SetTriggerHyst(float voltage);
int acq_GetTriggerHyst(float *voltage);
int acq_SetChannelThresholdHyst(rp_channel_t channel, float voltage);
int acq_GetChannelThresholdHyst(rp_channel_t channel, float* voltage);
int acq_GetWritePointer(uint32_t* pos);
int acq_GetWritePointerAtTrig(uint32_t* pos);
int acq_Start();
int acq_Stop();
int acq_Reset();
int acq_ResetFpga();

int acq_GetDataPosRaw(rp_channel_t channel, uint32_t start_pos, uint32_t end_pos, int16_t* buffer, uint32_t *buffer_size);
int acq_GetDataPosV(rp_channel_t channel, uint32_t start_pos, uint32_t end_pos, float* buffer, uint32_t *buffer_size);
int acq_GetDataRaw(rp_channel_t channel, uint32_t pos, uint32_t* size, int16_t* buffer);
int acq_GetOldestDataRaw(rp_channel_t channel, uint32_t* size, int16_t* buffer);
int acq_GetLatestDataRaw(rp_channel_t channel, uint32_t* size, int16_t* buffer);
int acq_GetDataV(rp_channel_t channel, uint32_t pos, uint32_t* size, float* buffer);
int acq_GetOldestDataV(rp_channel_t channel, uint32_t* size, float* buffer);
int acq_GetLatestDataV(rp_channel_t channel, uint32_t* size, float* buffer);

int acq_GetBufferSize(uint32_t *size);
int acq_SetDefault();

uint32_t acq_GetNormalizedDataPos(uint32_t pos);

#if defined Z10 || defined Z20_125 || defined Z20 || defined Z20_250_12
int acq_GetDataRawV2(uint32_t pos, uint32_t* size, uint16_t* buffer, uint16_t* buffer2);
int acq_GetDataV2(uint32_t pos, uint32_t* size, float* buffer1, float* buffer2);
int acq_GetDataV2D(uint32_t pos, uint32_t* size, double* buffer1, double* buffer2);
#endif

#if defined Z20_125_4CH
int acq_GetDataRawV2(uint32_t pos, uint32_t* size, uint16_t* buffer, uint16_t* buffer2, uint16_t* buffer3, uint16_t* buffer4);
int acq_GetDataV2(uint32_t pos, uint32_t* size, float* buffer1, float* buffer2, float* buffer3, float* buffer4);
int acq_GetDataV2D(uint32_t pos, uint32_t* size, double* buffer1, double* buffer2, double* buffer3, double* buffer4);
#endif

#if defined Z20_250_12
int acq_SetAC_DC(rp_channel_t channel,rp_acq_ac_dc_mode_t mode);
int acq_GetAC_DC(rp_channel_t channel,rp_acq_ac_dc_mode_t *status);
#endif

#if defined Z10 || defined Z20_125 || defined Z20_125_4CH
int acq_UpdateAcqFilter(rp_channel_t channel);
int acq_GetFilterCalibValue(rp_channel_t channel,uint32_t* coef_aa, uint32_t* coef_bb, uint32_t* coef_kk, uint32_t* coef_pp);
#endif

#endif /* SRC_ACQ_HANDLER_H_ */
