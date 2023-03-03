//------------------------------------------------------------------------
// Copyright(c) 2023 yg331.
//------------------------------------------------------------------------

#pragma once

#include "public.sdk/source/vst/vstaudioeffect.h"

using namespace Steinberg;

namespace yg331 {

//------------------------------------------------------------------------
//  MeowMuProcessor
//------------------------------------------------------------------------
class MeowMuProcessor : public Steinberg::Vst::AudioEffect
{
public:
	MeowMuProcessor ();
	~MeowMuProcessor () SMTG_OVERRIDE;

    // Create function
	static Steinberg::FUnknown* createInstance (void* /*context*/) 
	{ 
		return (Steinberg::Vst::IAudioProcessor*)new MeowMuProcessor; 
	}

	//--- ---------------------------------------------------------------------
	// AudioEffect overrides:
	//--- ---------------------------------------------------------------------
	/** Called at first after constructor */
	Steinberg::tresult PLUGIN_API initialize (Steinberg::FUnknown* context) SMTG_OVERRIDE;
	
	/** Called at the end before destructor */
	Steinberg::tresult PLUGIN_API terminate () SMTG_OVERRIDE;

	Steinberg::tresult PLUGIN_API setBusArrangements(
		Steinberg::Vst::SpeakerArrangement* inputs, Steinberg::int32 numIns,
		Steinberg::Vst::SpeakerArrangement* outputs, Steinberg::int32 numOuts
	) SMTG_OVERRIDE;
	
	/** Switch the Plug-in on/off */
	Steinberg::tresult PLUGIN_API setActive (Steinberg::TBool state) SMTG_OVERRIDE;

	/** Will be called before any process call */
	Steinberg::tresult PLUGIN_API setupProcessing (Steinberg::Vst::ProcessSetup& newSetup) SMTG_OVERRIDE;
	
	/** Asks if a given sample size is supported see SymbolicSampleSizes. */
	Steinberg::tresult PLUGIN_API canProcessSampleSize (Steinberg::int32 symbolicSampleSize) SMTG_OVERRIDE;

	/** Here we go...the process call */
	Steinberg::tresult PLUGIN_API process (Steinberg::Vst::ProcessData& data) SMTG_OVERRIDE;
		
	/** For persistence */
	Steinberg::tresult PLUGIN_API setState (Steinberg::IBStream* state) SMTG_OVERRIDE;
	Steinberg::tresult PLUGIN_API getState (Steinberg::IBStream* state) SMTG_OVERRIDE;

//------------------------------------------------------------------------
protected:

	Vst::Sample64 norm_to_gain(Vst::Sample64 plainValue);
	Vst::Sample64 VuPPMconvert(Vst::Sample64 plainValue);

	template <typename SampleType>
	void processAudio(SampleType** inputs, SampleType** outputs, Vst::Sample64 getSampleRate, int32 sampleFrames, int32 precision);

	template <typename SampleType>
	void processVuPPM(SampleType** inputs, int32 sampleFrames);


	Vst::Sample64 muVaryL;
	Vst::Sample64 muAttackL;
	Vst::Sample64 muNewSpeedL;
	Vst::Sample64 muSpeedAL;
	Vst::Sample64 muSpeedBL;
	Vst::Sample64 muCoefficientAL;
	Vst::Sample64 muCoefficientBL;
	Vst::Sample64 previousL;

	Vst::Sample64 muVaryR;
	Vst::Sample64 muAttackR;
	Vst::Sample64 muNewSpeedR;
	Vst::Sample64 muSpeedAR;
	Vst::Sample64 muSpeedBR;
	Vst::Sample64 muCoefficientAR;
	Vst::Sample64 muCoefficientBR;
	Vst::Sample64 previousR;
	bool flip;

	uint32_t fpdL = 1;
	uint32_t fpdR = 1;
	//default stuff
	Vst::Sample64 In_db = 1.0;
	Vst::Sample64 Out_db = 1.0;
	Vst::Sample32 fParamInput = 0.0;
	Vst::Sample32 fParamOutput = 0.0;
	Vst::Sample32 fParamComp;
	Vst::Sample32 fParamSpeed;
	Vst::Sample32 fParamGain;
	Vst::Sample32 fParamMix;
	Vst::Sample32 fInVuPPM;
	Vst::Sample32 fOutVuPPM;
	Vst::Sample32 fGRVuPPM;
	Vst::Sample32 fInVuPPMOld;
	Vst::Sample32 fOutVuPPMOld;
	Vst::Sample32 fGRVuPPMOld;
	bool bBypass = false;

};

//------------------------------------------------------------------------
} // namespace yg331
