//------------------------------------------------------------------------
// Copyright(c) 2023 yg331.
//------------------------------------------------------------------------

#include "MeowMucontroller.h"
#include "MeowMucids.h"
#include "vstgui/plugin-bindings/vst3editor.h"
#include "C:\VST_make\VST_SDK\vst3sdk\vstgui4\vstgui\plugin-bindings\vst3editor.h"
#include "vstgui4/vstgui/plugin-bindings/vst3editor.h"
#include "public.sdk/source/vst/vsteditcontroller.h"

#include "pluginterfaces/base/ustring.h"
#include "base/source/fstreamer.h"


using namespace Steinberg;

namespace yg331 {

	//------------------------------------------------------------------------
	// MeowMuController Implementation
	//------------------------------------------------------------------------
	tresult PLUGIN_API MeowMuController::initialize(FUnknown* context)
	{
		// Here the Plug-in will be instantiated

		//---do not forget to call parent ------
		tresult result = EditControllerEx1::initialize(context);
		if (result != kResultOk)
		{
			return result;
		}

		// Here you could register some parameters
		int32 stepCount;
		int32 flags;
		int32 tag;
		Vst::ParamValue defaultVal;
		Vst::ParamValue minPlain;
		Vst::ParamValue maxPlain;
		Vst::ParamValue defaultPlain;

		flags = Vst::ParameterInfo::kCanAutomate;
		minPlain = -12.0;
		maxPlain = 12.0;
		defaultPlain = 0.0;

		tag = kParamInput;
		auto* gainParamIn = new SliderParameter(USTRING("Input"), tag, STR16("dB"), minPlain, maxPlain, defaultPlain, 0, flags);
		parameters.addParameter(gainParamIn);
		tag = kParamOutput;
		auto* gainParamOut = new SliderParameter(USTRING("Output"), tag, STR16("dB"), minPlain, maxPlain, defaultPlain, 0, flags);
		parameters.addParameter(gainParamOut);

		flags = Vst::ParameterInfo::kIsReadOnly;
		minPlain = -60;
		maxPlain = 0;
		defaultPlain = -18;

		tag = kParamInVuPPM;
		auto* InVuPPM = new VuPPMParameter(USTRING("InVuPPM"), flags, tag, STR16("dB"), minPlain, maxPlain, defaultPlain);
		parameters.addParameter(InVuPPM);
		tag = kParamOutVuPPM;
		auto* OutVuPPM = new VuPPMParameter(USTRING("OutVuPPM"), flags, tag, STR16("dB"), minPlain, maxPlain, defaultPlain);
		parameters.addParameter(OutVuPPM);
		tag = kParamGRVuPPM;
		auto* GRVuPPM = new VuPPMParameter(STR16("GRVuPPM"), flags, tag, STR16("dB"), minPlain, maxPlain, defaultPlain);
		parameters.addParameter(GRVuPPM);


		tag = kParamComp;
		stepCount = 0;
		defaultVal = 0.2;
		flags = Vst::ParameterInfo::kCanAutomate;
		parameters.addParameter(STR16("Comp"), nullptr, stepCount, defaultVal, flags, tag);

		tag = kParamSpeed;
		stepCount = 0;
		defaultVal = 0.6;
		flags = Vst::ParameterInfo::kCanAutomate;
		parameters.addParameter(STR16("Speed"), nullptr, stepCount, defaultVal, flags, tag);

		tag = kParamGain;
		stepCount = 0;
		defaultVal = 0.0;
		flags = Vst::ParameterInfo::kCanAutomate;
		parameters.addParameter(STR16("Gain"), nullptr, stepCount, defaultVal, flags, tag);

		tag = kParamMix;
		stepCount = 0;
		defaultVal = 1.0;
		flags = Vst::ParameterInfo::kCanAutomate;
		parameters.addParameter(STR16("Mix"), nullptr, stepCount, defaultVal, flags, tag);

		tag = kParamBypass;
		stepCount = 1;
		defaultVal = 0;
		flags = Vst::ParameterInfo::kCanAutomate | Vst::ParameterInfo::kIsBypass;
		parameters.addParameter(STR16("Bypass"), nullptr, stepCount, defaultVal, flags, tag);

		 


		return result;
	}

	//------------------------------------------------------------------------
	tresult PLUGIN_API MeowMuController::terminate()
	{
		// Here the Plug-in will be de-instantiated, last possibility to remove some memory!

		//---do not forget to call parent ------
		return EditControllerEx1::terminate();
	}

	//------------------------------------------------------------------------
	tresult PLUGIN_API MeowMuController::setComponentState(IBStream* state)
	{
		// Here you get the state of the component (Processor part)
		if (!state)
			return kResultFalse;

		IBStreamer streamer(state, kLittleEndian);

		float savedInput = 0.f;
		if (streamer.readFloat(savedInput) == false)
			return kResultFalse;
		setParamNormalized(kParamInput, savedInput);

		float savedOutput = 0.f;
		if (streamer.readFloat(savedOutput) == false)
			return kResultFalse;
		setParamNormalized(kParamOutput, savedOutput);

		float savedComp = 0.f;
		if (streamer.readFloat(savedComp) == false)
			return kResultFalse;
		setParamNormalized(kParamComp, savedComp);

		float savedSpeed = 0.f;
		if (streamer.readFloat(savedSpeed) == false)
			return kResultFalse;
		setParamNormalized(kParamSpeed, savedSpeed);

		float savedGain = 0.f;
		if (streamer.readFloat(savedGain) == false)
			return kResultFalse;
		setParamNormalized(kParamGain, savedGain);

		float savedMix = 0.f;
		if (streamer.readFloat(savedMix) == false)
			return kResultFalse;
		setParamNormalized(kParamMix, savedMix);

		int32 bypassState = 0;
		if (streamer.readInt32(bypassState) == false)
			return kResultFalse;
		setParamNormalized(kParamBypass, bypassState ? 1 : 0);



		return kResultOk;
	}

	//------------------------------------------------------------------------
	tresult PLUGIN_API MeowMuController::setState(IBStream* state)
	{
		// Here you get the state of the controller

		return kResultTrue;
	}

	//------------------------------------------------------------------------
	tresult PLUGIN_API MeowMuController::getState(IBStream* state)
	{
		// Here you are asked to deliver the state of the controller (if needed)
		// Note: the real state of your plug-in is saved in the processor

		return kResultTrue;
	}

	//------------------------------------------------------------------------
	IPlugView* PLUGIN_API MeowMuController::createView(FIDString name)
	{
		// Here the Host wants to open your editor (if you have one)
		if (FIDStringsEqual(name, Vst::ViewType::kEditor))
		{
			// create your editor here and return a IPlugView ptr of it
			auto* view = new VSTGUI::VST3Editor(this, "view", "MeowMueditor.uidesc");
			return view;
		}
		return nullptr;
	}

	//------------------------------------------------------------------------
	tresult PLUGIN_API MeowMuController::setParamNormalized(Vst::ParamID tag, Vst::ParamValue value)
	{
		// called by host to update your parameters
		tresult result = EditControllerEx1::setParamNormalized(tag, value);
		return result;
	}

	//------------------------------------------------------------------------
	tresult PLUGIN_API MeowMuController::getParamStringByValue(Vst::ParamID tag, Vst::ParamValue valueNormalized, Vst::String128 string)
	{
		// called by host to get a string for given normalized value of a specific parameter
		// (without having to set the value!)
		return EditControllerEx1::getParamStringByValue(tag, valueNormalized, string);
	}

	//------------------------------------------------------------------------
	tresult PLUGIN_API MeowMuController::getParamValueByString(Vst::ParamID tag, Vst::TChar* string, Vst::ParamValue& valueNormalized)
	{
		// called by host to get a normalized value from a string representation of a specific parameter
		// (without having to set the value!)
		return EditControllerEx1::getParamValueByString(tag, string, valueNormalized);
	}



	//------------------------------------------------------------------------
	// GainParameter Implementation
	//------------------------------------------------------------------------
	SliderParameter::SliderParameter(
		const Vst::TChar* title,
		int32 tag,
		const Vst::TChar* units,
		Vst::ParamValue minPlain,
		Vst::ParamValue maxPlain,
		Vst::ParamValue defaultValuePlain,
		int32 stepCount,
		int32 flags,
		Vst::UnitID unitID
	)
	{
		UString(info.title, str16BufferSize(Vst::String128)).assign(title);
		if (units)
			UString(info.units, str16BufferSize(Vst::String128)).assign(units);

		setMin(minPlain);
		setMax(maxPlain);

		info.flags = flags;
		info.id = tag;
		info.stepCount = stepCount;
		info.defaultNormalizedValue = valueNormalized = toNormalized(defaultValuePlain);
		info.unitId = Vst::kRootUnitId;
	}
	//------------------------------------------------------------------------
	void SliderParameter::toString(Vst::ParamValue normValue, Vst::String128 string) const
	{
		Vst::ParamValue plainValue = SliderParameter::toPlain(normValue);

		char text[32];
		snprintf(text, 32, "%.2f", plainValue);

		Steinberg::UString(string, 128).fromAscii(text);
	}
	//------------------------------------------------------------------------
	bool SliderParameter::fromString(const Vst::TChar* string, Vst::ParamValue& normValue) const
	{
		String wrapper((Vst::TChar*)string); // don't know buffer size here!
		Vst::ParamValue plainValue;
		if (wrapper.scanFloat(plainValue))
		{
			normValue = SliderParameter::toNormalized(plainValue);
			return true;
		}
		return false;

	}
	//------------------------------------------------------------------------



	VuPPMParameter::VuPPMParameter(
		const Vst::TChar* title,
		int32 flags,
		int32 tag,
		const Vst::TChar* units,
		Vst::ParamValue minPlain,
		Vst::ParamValue maxPlain,
		Vst::ParamValue defaultValuePlain,
		Vst::UnitID unitID
	)
	{

		UString(info.title, str16BufferSize(Vst::String128)).assign(title);
		if (units)
			UString(info.units, str16BufferSize(Vst::String128)).assign(units);

		setMin(minPlain);
		setMax(maxPlain);

		midValue = defaultValuePlain;

		info.stepCount = 0;
		info.defaultNormalizedValue = valueNormalized = toNormalized(defaultValuePlain);
		info.flags = flags;
		info.id = tag;
		info.unitId = unitID;
	}

	Vst::ParamValue VuPPMParameter::toPlain(Vst::ParamValue normValue) const
	{
		Vst::ParamValue plainValue;
		/*
		normValue	: dB		: gain
		1.0 ~ 0.0	:   0 ~ -36	: 1.0 ~ 0.015849
		1.0 ~ 0.5	:   0 ~ -18 : 1.0 ~ 0.12589254117941673
		0.5 ~ 0.0	: -18 ~ -60 : 0.12589254117941673 ~
		1.0 ~ 0.0	: +24 ~ -60

		1. normValue -> dB
		1.0 ~ 0.5	: y = (36 * y) - 36;
		0.5 ~ 0.0	: y = (84 * x) - 60;
		*/
		if (normValue > 0.5) plainValue = (2 * (getMax() - midValue) * normValue) + (2 * midValue - getMax());
		else plainValue = (2 * (midValue - getMin()) * normValue) + getMin();

		return plainValue;
	}

	Vst::ParamValue VuPPMParameter::toNormalized(Vst::ParamValue plainValue) const
	{
		double dB = 20.0 * log10(plainValue);
		double normValue;
		/*
		   db     : normValue
		0   ~ -36 : 1.0 ~ 0.0
		0   ~ -18 : 1.0 ~ 0.5   <-
		-18 ~ -60 : 0.5 ~ 0.0   <-
		+24 ~ -60 : 1.0 ~ 0.0

		1. param(gain) -> dB
		2.	if (dB > 0.0) y = 1.0;
			if (dB > -18) y = (x + 36) / 36;
			if (dB > -60) y = (x + 60) / 84;
			if (-60 > dB) y = 0.0;

		*/

		if (dB > 0.0) normValue = 1.0;
		else if (dB > -18.0) normValue = (dB + 36) / 36;
		else if (dB > -60.0) normValue = (dB + 60) / 84;
		else normValue = 0.0;

		return normValue;
	}

	//------------------------------------------------------------------------
	void VuPPMParameter::toString(Vst::ParamValue normValue, Vst::String128 string) const
	{
		Vst::ParamValue plainValue = VuPPMParameter::toPlain(normValue);

		char text[32];
		snprintf(text, 32, "%.2f", plainValue);

		Steinberg::UString(string, 128).fromAscii(text);
	}

	//------------------------------------------------------------------------
	bool VuPPMParameter::fromString(const Vst::TChar* string, Vst::ParamValue& normValue) const
	{
		String wrapper((Vst::TChar*)string); // don't know buffer size here!
		Vst::ParamValue plainValue;
		if (wrapper.scanFloat(plainValue))
		{
			normValue = VuPPMParameter::toNormalized(plainValue);
			return true;
		}
		return false;
	}


} // namespace yg331
