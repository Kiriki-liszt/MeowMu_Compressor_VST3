//------------------------------------------------------------------------
// Copyright(c) 2023 yg331.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace yg331 {
//------------------------------------------------------------------------
static const Steinberg::FUID kMeowMuProcessorUID (0xB09AE2D4, 0x76BD5511, 0x81B88EC4, 0x658C521C);
static const Steinberg::FUID kMeowMuControllerUID (0x5F4ED30E, 0xD4B0552A, 0x87110FA9, 0xF0317306);

#define MeowMuVST3Category "Fx"

//------------------------------------------------------------------------
} // namespace yg331

enum {
	kParamInput = 0,
	kParamOutput,
	kParamComp,
	kParamSpeed,
	kParamTrim,
	kParamMix,
	kParamInVuPPM,// Input VuPPM
	kParamOutVuPPM,		// Output VuPPM
	kParamGRVuPPM,
	kParamBypass
	// kNumParameters = 7
};