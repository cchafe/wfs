/* ------------------------------------------------------------
name: "qt"
Code generated with Faust 2.40.0 (https://faust.grame.fr)
Compilation options: -a .faust2ck_tmp/qt.dsp-wrapper.cpp -lang cpp -es 1 -mcd 16 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__


#include "chuck_def.h"
#include "chuck_dl.h"

#include <stdio.h>
#include <string.h>
#include <limits.h>

#include <map>
#include <string>

//-------------------------------------------------------------------
// Generic min and max using C++ inline
//-------------------------------------------------------------------

#ifndef WIN32

inline int      max (unsigned int a, unsigned int b) { return (a>b) ? a : b; }
inline int      max (int a, int b)          { return (a>b) ? a : b; }

inline long     max (long a, long b)        { return (a>b) ? a : b; }
inline long     max (int a, long b)         { return (a>b) ? a : b; }
inline long     max (long a, int b)         { return (a>b) ? a : b; }

inline float    max (float a, float b)      { return (a>b) ? a : b; }
inline float    max (int a, float b)        { return (a>b) ? a : b; }
inline float    max (float a, int b)        { return (a>b) ? a : b; }
inline float    max (long a, float b)       { return (a>b) ? a : b; }
inline float    max (float a, long b)       { return (a>b) ? a : b; }

inline double   max (double a, double b)    { return (a>b) ? a : b; }
inline double   max (int a, double b)       { return (a>b) ? a : b; }
inline double   max (double a, int b)       { return (a>b) ? a : b; }
inline double   max (long a, double b)      { return (a>b) ? a : b; }
inline double   max (double a, long b)      { return (a>b) ? a : b; }
inline double   max (float a, double b)     { return (a>b) ? a : b; }
inline double   max (double a, float b)     { return (a>b) ? a : b; }


inline int      min (int a, int b)          { return (a<b) ? a : b; }

inline long     min (long a, long b)        { return (a<b) ? a : b; }
inline long     min (int a, long b)         { return (a<b) ? a : b; }
inline long     min (long a, int b)         { return (a<b) ? a : b; }

inline float    min (float a, float b)      { return (a<b) ? a : b; }
inline float    min (int a, float b)        { return (a<b) ? a : b; }
inline float    min (float a, int b)        { return (a<b) ? a : b; }
inline float    min (long a, float b)       { return (a<b) ? a : b; }
inline float    min (float a, long b)       { return (a<b) ? a : b; }

inline double   min (double a, double b)    { return (a<b) ? a : b; }
inline double   min (int a, double b)       { return (a<b) ? a : b; }
inline double   min (double a, int b)       { return (a<b) ? a : b; }
inline double   min (long a, double b)      { return (a<b) ? a : b; }
inline double   min (double a, long b)      { return (a<b) ? a : b; }
inline double   min (float a, double b)     { return (a<b) ? a : b; }
inline double   min (double a, float b)     { return (a<b) ? a : b; }

#endif // ndef WIN32

inline int      lsr (int x, int n)          { return int(((unsigned int)x) >> n); }
inline int      int2pow2 (int x)            { int r=0; while ((1<<r)<x) r++; return r; }


/******************************************************************************
 *******************************************************************************
 
 FAUST META DATA
 
 *******************************************************************************
 *******************************************************************************/

struct Meta : std::map<std::string, std::string>
{
    void declare(const char* key, const char* value)
    {
        (*this)[key] = value;
    }
};

/* UI class - do-nothing (from FAUST/minimal.cpp) */

#ifdef WIN32
#ifdef interface
#undef interface
#endif // interface
#endif // WIN32

class UI
{
public:
    virtual ~UI() { }
    
    // active widgets
    virtual void addButton(const char* label, float* zone) = 0;
    virtual void addToggleButton(const char* label, float* zone) = 0;
    virtual void addCheckButton(const char* label, float* zone) = 0;
    virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
    virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
    virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) = 0;
    
    // passive widgets
    virtual void addNumDisplay(const char* label, float* zone, int precision) = 0;
    virtual void addTextDisplay(const char* label, float* zone, char* names[], float min, float max) = 0;
    virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) = 0;
    virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) = 0;
    
    // layout widgets
    virtual void openFrameBox(const char* label) = 0;
    virtual void openTabBox(const char* label) = 0;
    virtual void openHorizontalBox(const char* label) = 0;
    virtual void openVerticalBox(const char* label) = 0;
    virtual void closeBox() = 0;
    
    virtual void declare(float* zone, const char* key, const char* value) {}
};

class dsp
{
public:
    virtual ~dsp();
    virtual int getNumInputs()                                      = 0;
    virtual int getNumOutputs()                                     = 0;
    virtual void buildUserInterface(UI* interface)                  = 0;
    virtual void init(int samplingRate)                             = 0;
    virtual void compute(int len, float** inputs, float** outputs)  = 0;
    
    SAMPLE ** ck_frame_in;
    SAMPLE ** ck_frame_out;

protected:
    int fSamplingFreq;
};

dsp::~dsp() { }

/*
 * FAUST intrinsic
 */

/*
 * FAUST defines UI values as private, but provides no getters/setters.
 * In our particular case it's way more convenient to access them directly
 * than to set up a complicated UI structure.  Also get rid of everything
 * being "virtual", since it may stop the compiler from inlining properly!
 */
#define private public
#define virtual

/* Rename the class the name of our DSP. */
#define mydsp qt

/*
 * FAUST class
 */
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif

static float mydsp_faustpower2_f(float value) {
	return value * value;
}

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	int fSampleRate;
	float fConst1;
	FAUSTFLOAT fHslider1;
	int iRec3[2];
	float fRec2[3];
	float fRec1[3];
	float fConst2;
	FAUSTFLOAT fHslider2;
	float fVec0[2];
	int iRec4[2];
	float fConst4;
	float fConst5;
	FAUSTFLOAT fHslider3;
	float fConst6;
	float fRec0[3];
	float fConst8;
	float fConst9;
	float fRec5[3];
	float fConst11;
	float fConst12;
	float fRec6[3];
	float fConst14;
	float fConst15;
	float fRec7[3];
	float fConst17;
	float fConst18;
	float fRec8[3];
	float fConst20;
	float fConst21;
	float fRec9[3];
	float fConst23;
	float fConst24;
	float fRec10[3];
	float fConst26;
	float fConst27;
	float fRec11[3];
	float fConst29;
	float fConst30;
	float fRec12[3];
	float fConst32;
	float fConst33;
	float fRec13[3];
	float fConst35;
	float fConst36;
	float fRec14[3];
	float fConst38;
	float fConst39;
	float fRec15[3];
	float fConst41;
	float fConst42;
	float fRec16[3];
	float fConst44;
	float fConst45;
	float fRec17[3];
	float fConst47;
	float fConst48;
	float fRec18[3];
	float fConst50;
	float fConst51;
	float fRec19[3];
	float fConst53;
	float fConst54;
	float fRec20[3];
	float fConst56;
	float fConst57;
	float fRec21[3];
	float fConst59;
	float fConst60;
	float fRec22[3];
	float fConst62;
	float fConst63;
	float fRec23[3];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-a .faust2ck_tmp/qt.dsp-wrapper.cpp -lang cpp -es 1 -mcd 16 -single -ftz 0");
		m->declare("envelopes.lib/ar:author", "Yann Orlarey, Stéphane Letz");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "0.1");
		m->declare("filename", "qt.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/highpass:author", "Julius O. Smith III");
		m->declare("filters.lib/highpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "0.3");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.5");
		m->declare("name", "qt");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.3");
		m->declare("physmodels.lib/name", "Faust Physical Models Library");
		m->declare("physmodels.lib/version", "0.1");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "0.2");
	}

	virtual int getNumInputs() {
		return 1;
	}
	virtual int getNumOutputs() {
		return 1;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		float fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = 3.14159274f / fConst0;
		fConst2 = 0.00200000009f * fConst0;
		float fConst3 = std::pow(0.00100000005f, 1.66666663f / fConst0);
		fConst4 = 0.0f - 2.0f * fConst3;
		fConst5 = 6.28318548f / fConst0;
		fConst6 = mydsp_faustpower2_f(fConst3);
		float fConst7 = std::pow(0.00100000005f, 1.75438595f / fConst0);
		fConst8 = 0.0f - 2.0f * fConst7;
		fConst9 = mydsp_faustpower2_f(fConst7);
		float fConst10 = std::pow(0.00100000005f, 1.85185182f / fConst0);
		fConst11 = 0.0f - 2.0f * fConst10;
		fConst12 = mydsp_faustpower2_f(fConst10);
		float fConst13 = std::pow(0.00100000005f, 1.96078432f / fConst0);
		fConst14 = 0.0f - 2.0f * fConst13;
		fConst15 = mydsp_faustpower2_f(fConst13);
		float fConst16 = std::pow(0.00100000005f, 2.08333325f / fConst0);
		fConst17 = 0.0f - 2.0f * fConst16;
		fConst18 = mydsp_faustpower2_f(fConst16);
		float fConst19 = std::pow(0.00100000005f, 2.22222233f / fConst0);
		fConst20 = 0.0f - 2.0f * fConst19;
		fConst21 = mydsp_faustpower2_f(fConst19);
		float fConst22 = std::pow(0.00100000005f, 2.38095236f / fConst0);
		fConst23 = 0.0f - 2.0f * fConst22;
		fConst24 = mydsp_faustpower2_f(fConst22);
		float fConst25 = std::pow(0.00100000005f, 2.56410265f / fConst0);
		fConst26 = 0.0f - 2.0f * fConst25;
		fConst27 = mydsp_faustpower2_f(fConst25);
		float fConst28 = std::pow(0.00100000005f, 2.77777767f / fConst0);
		fConst29 = 0.0f - 2.0f * fConst28;
		fConst30 = mydsp_faustpower2_f(fConst28);
		float fConst31 = std::pow(0.00100000005f, 3.030303f / fConst0);
		fConst32 = 0.0f - 2.0f * fConst31;
		fConst33 = mydsp_faustpower2_f(fConst31);
		float fConst34 = std::pow(0.00100000005f, 3.33333325f / fConst0);
		fConst35 = 0.0f - 2.0f * fConst34;
		fConst36 = mydsp_faustpower2_f(fConst34);
		float fConst37 = std::pow(0.00100000005f, 3.70370364f / fConst0);
		fConst38 = 0.0f - 2.0f * fConst37;
		fConst39 = mydsp_faustpower2_f(fConst37);
		float fConst40 = std::pow(0.00100000005f, 4.16666651f / fConst0);
		fConst41 = 0.0f - 2.0f * fConst40;
		fConst42 = mydsp_faustpower2_f(fConst40);
		float fConst43 = std::pow(0.00100000005f, 4.76190472f / fConst0);
		fConst44 = 0.0f - 2.0f * fConst43;
		fConst45 = mydsp_faustpower2_f(fConst43);
		float fConst46 = std::pow(0.00100000005f, 5.55555534f / fConst0);
		fConst47 = 0.0f - 2.0f * fConst46;
		fConst48 = mydsp_faustpower2_f(fConst46);
		float fConst49 = std::pow(0.00100000005f, 6.66666651f / fConst0);
		fConst50 = 0.0f - 2.0f * fConst49;
		fConst51 = mydsp_faustpower2_f(fConst49);
		float fConst52 = std::pow(0.00100000005f, 8.33333302f / fConst0);
		fConst53 = 0.0f - 2.0f * fConst52;
		fConst54 = mydsp_faustpower2_f(fConst52);
		float fConst55 = std::pow(0.00100000005f, 11.1111107f / fConst0);
		fConst56 = 0.0f - 2.0f * fConst55;
		fConst57 = mydsp_faustpower2_f(fConst55);
		float fConst58 = std::pow(0.00100000005f, 16.666666f / fConst0);
		fConst59 = 0.0f - 2.0f * fConst58;
		fConst60 = mydsp_faustpower2_f(fConst58);
		float fConst61 = std::pow(0.00100000005f, 33.3333321f / fConst0);
		fConst62 = 0.0f - 2.0f * fConst61;
		fConst63 = mydsp_faustpower2_f(fConst61);
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.5f);
		fHslider1 = FAUSTFLOAT(0.29999999999999999f);
		fHslider2 = FAUSTFLOAT(0.40000000000000002f);
		fHslider3 = FAUSTFLOAT(72.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iRec3[l0] = 0;
		}
		for (int l1 = 0; l1 < 3; l1 = l1 + 1) {
			fRec2[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 3; l2 = l2 + 1) {
			fRec1[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fVec0[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			iRec4[l4] = 0;
		}
		for (int l5 = 0; l5 < 3; l5 = l5 + 1) {
			fRec0[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 3; l6 = l6 + 1) {
			fRec5[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 3; l7 = l7 + 1) {
			fRec6[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 3; l8 = l8 + 1) {
			fRec7[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 3; l9 = l9 + 1) {
			fRec8[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 3; l10 = l10 + 1) {
			fRec9[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 3; l11 = l11 + 1) {
			fRec10[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 3; l12 = l12 + 1) {
			fRec11[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 3; l13 = l13 + 1) {
			fRec12[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 3; l14 = l14 + 1) {
			fRec13[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 3; l15 = l15 + 1) {
			fRec14[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 3; l16 = l16 + 1) {
			fRec15[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 3; l17 = l17 + 1) {
			fRec16[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 3; l18 = l18 + 1) {
			fRec17[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 3; l19 = l19 + 1) {
			fRec18[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 3; l20 = l20 + 1) {
			fRec19[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 3; l21 = l21 + 1) {
			fRec20[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 3; l22 = l22 + 1) {
			fRec21[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 3; l23 = l23 + 1) {
			fRec22[l23] = 0.0f;
		}
		for (int l24 = 0; l24 < 3; l24 = l24 + 1) {
			fRec23[l24] = 0.0f;
		}
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp* clone() {
		return new mydsp();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("qt");
		ui_interface->addHorizontalSlider("freq", &fHslider3, FAUSTFLOAT(72.0f), FAUSTFLOAT(50.0f), FAUSTFLOAT(128.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->addHorizontalSlider("gain", &fHslider0, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->addHorizontalSlider("pos", &fHslider1, FAUSTFLOAT(0.300000012f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->addHorizontalSlider("sharp", &fHslider2, FAUSTFLOAT(0.400000006f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = float(fHslider1);
		float fSlow1 = std::tan(fConst1 * (15000.0f * fSlow0 + 500.0f));
		float fSlow2 = 1.0f / fSlow1;
		float fSlow3 = (fSlow2 + 1.41421354f) / fSlow1 + 1.0f;
		float fSlow4 = float(fHslider0) / fSlow3;
		float fSlow5 = std::tan(fConst1 * (500.0f * fSlow0 + 40.0f));
		float fSlow6 = 1.0f / fSlow5;
		float fSlow7 = 1.0f / ((fSlow6 + 1.41421354f) / fSlow5 + 1.0f);
		float fSlow8 = mydsp_faustpower2_f(fSlow5);
		float fSlow9 = 1.0f / fSlow8;
		float fSlow10 = (fSlow6 + -1.41421354f) / fSlow5 + 1.0f;
		float fSlow11 = 2.0f * (1.0f - fSlow9);
		float fSlow12 = 0.0f - 2.0f / fSlow8;
		float fSlow13 = 1.0f / fSlow3;
		float fSlow14 = (fSlow2 + -1.41421354f) / fSlow1 + 1.0f;
		float fSlow15 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fSlow1));
		float fSlow16 = 1.0f / std::max<float>(1.0f, fConst2 * float(fHslider2));
		float fSlow17 = float(fHslider3);
		float fSlow18 = fConst4 * std::cos(fConst5 * fSlow17);
		float fSlow19 = fConst8 * std::cos(fConst5 * (fSlow17 + 200.0f));
		float fSlow20 = fConst11 * std::cos(fConst5 * (fSlow17 + 400.0f));
		float fSlow21 = fConst14 * std::cos(fConst5 * (fSlow17 + 600.0f));
		float fSlow22 = fConst17 * std::cos(fConst5 * (fSlow17 + 800.0f));
		float fSlow23 = fConst20 * std::cos(fConst5 * (fSlow17 + 1000.0f));
		float fSlow24 = fConst23 * std::cos(fConst5 * (fSlow17 + 1200.0f));
		float fSlow25 = fConst26 * std::cos(fConst5 * (fSlow17 + 1400.0f));
		float fSlow26 = fConst29 * std::cos(fConst5 * (fSlow17 + 1600.0f));
		float fSlow27 = fConst32 * std::cos(fConst5 * (fSlow17 + 1800.0f));
		float fSlow28 = fConst35 * std::cos(fConst5 * (fSlow17 + 2000.0f));
		float fSlow29 = fConst38 * std::cos(fConst5 * (fSlow17 + 2200.0f));
		float fSlow30 = fConst41 * std::cos(fConst5 * (fSlow17 + 2400.0f));
		float fSlow31 = fConst44 * std::cos(fConst5 * (fSlow17 + 2600.0f));
		float fSlow32 = fConst47 * std::cos(fConst5 * (fSlow17 + 2800.0f));
		float fSlow33 = fConst50 * std::cos(fConst5 * (fSlow17 + 3000.0f));
		float fSlow34 = fConst53 * std::cos(fConst5 * (fSlow17 + 3200.0f));
		float fSlow35 = fConst56 * std::cos(fConst5 * (fSlow17 + 3400.0f));
		float fSlow36 = fConst59 * std::cos(fConst5 * (fSlow17 + 3600.0f));
		float fSlow37 = fConst62 * std::cos(fConst5 * (fSlow17 + 3800.0f));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			iRec3[0] = 1103515245 * iRec3[1] + 12345;
			fRec2[0] = 4.65661287e-10f * float(iRec3[0]) - fSlow7 * (fSlow10 * fRec2[2] + fSlow11 * fRec2[1]);
			fRec1[0] = fSlow7 * (fSlow9 * fRec2[0] + fSlow12 * fRec2[1] + fSlow9 * fRec2[2]) - fSlow13 * (fSlow14 * fRec1[2] + fSlow15 * fRec1[1]);
			float fTemp0 = float(input0[i0]);
			fVec0[0] = fTemp0;
			iRec4[0] = (iRec4[1] + (iRec4[1] > 0)) * (fTemp0 <= fVec0[1]) + (fTemp0 > fVec0[1]);
			float fTemp1 = fSlow16 * float(iRec4[0]);
			float fTemp2 = fSlow4 * (fRec1[2] + fRec1[0] + 2.0f * fRec1[1]) * std::max<float>(0.0f, std::min<float>(fTemp1, 2.0f - fTemp1));
			fRec0[0] = fTemp2 - (fSlow18 * fRec0[1] + fConst6 * fRec0[2]);
			fRec5[0] = fTemp2 - (fSlow19 * fRec5[1] + fConst9 * fRec5[2]);
			fRec6[0] = fTemp2 - (fSlow20 * fRec6[1] + fConst12 * fRec6[2]);
			fRec7[0] = fTemp2 - (fSlow21 * fRec7[1] + fConst15 * fRec7[2]);
			fRec8[0] = fTemp2 - (fSlow22 * fRec8[1] + fConst18 * fRec8[2]);
			fRec9[0] = fTemp2 - (fSlow23 * fRec9[1] + fConst21 * fRec9[2]);
			fRec10[0] = fTemp2 - (fSlow24 * fRec10[1] + fConst24 * fRec10[2]);
			fRec11[0] = fTemp2 - (fSlow25 * fRec11[1] + fConst27 * fRec11[2]);
			fRec12[0] = fTemp2 - (fSlow26 * fRec12[1] + fConst30 * fRec12[2]);
			fRec13[0] = fTemp2 - (fSlow27 * fRec13[1] + fConst33 * fRec13[2]);
			fRec14[0] = fTemp2 - (fSlow28 * fRec14[1] + fConst36 * fRec14[2]);
			fRec15[0] = fTemp2 - (fSlow29 * fRec15[1] + fConst39 * fRec15[2]);
			fRec16[0] = fTemp2 - (fSlow30 * fRec16[1] + fConst42 * fRec16[2]);
			fRec17[0] = fTemp2 - (fSlow31 * fRec17[1] + fConst45 * fRec17[2]);
			fRec18[0] = fTemp2 - (fSlow32 * fRec18[1] + fConst48 * fRec18[2]);
			fRec19[0] = fTemp2 - (fSlow33 * fRec19[1] + fConst51 * fRec19[2]);
			fRec20[0] = fTemp2 - (fSlow34 * fRec20[1] + fConst54 * fRec20[2]);
			fRec21[0] = fTemp2 - (fSlow35 * fRec21[1] + fConst57 * fRec21[2]);
			fRec22[0] = fTemp2 - (fSlow36 * fRec22[1] + fConst60 * fRec22[2]);
			fRec23[0] = fTemp2 - (fSlow37 * fRec23[1] + fConst63 * fRec23[2]);
			output0[i0] = FAUSTFLOAT(0.0500000007f * ((fRec0[0] + 0.25f * (fRec5[0] - fRec5[2]) + 0.111111112f * (fRec6[0] - fRec6[2]) + 0.0625f * (fRec7[0] - fRec7[2]) + 0.0399999991f * (fRec8[0] - fRec8[2]) + 0.027777778f * (fRec9[0] - fRec9[2]) + 0.0204081628f * (fRec10[0] - fRec10[2]) + 0.015625f * (fRec11[0] - fRec11[2]) + 0.0123456791f * (fRec12[0] - fRec12[2]) + 0.00999999978f * (fRec13[0] - fRec13[2]) + 0.00826446246f * (fRec14[0] - fRec14[2]) + 0.0069444445f * (fRec15[0] - fRec15[2]) + 0.00591715984f * (fRec16[0] - fRec16[2]) + 0.00510204071f * (fRec17[0] - fRec17[2]) + 0.00444444455f * (fRec18[0] - fRec18[2]) + 0.00390625f * (fRec19[0] - fRec19[2]) + 0.00346020772f * (fRec20[0] - fRec20[2]) + 0.00308641978f * (fRec21[0] - fRec21[2]) + 0.00277008303f * (fRec22[0] - fRec22[2]) + 0.00249999994f * (fRec23[0] - fRec23[2])) - fRec0[2]));
			iRec3[1] = iRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fVec0[1] = fVec0[0];
			iRec4[1] = iRec4[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec5[2] = fRec5[1];
			fRec5[1] = fRec5[0];
			fRec6[2] = fRec6[1];
			fRec6[1] = fRec6[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			fRec9[2] = fRec9[1];
			fRec9[1] = fRec9[0];
			fRec10[2] = fRec10[1];
			fRec10[1] = fRec10[0];
			fRec11[2] = fRec11[1];
			fRec11[1] = fRec11[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			fRec13[2] = fRec13[1];
			fRec13[1] = fRec13[0];
			fRec14[2] = fRec14[1];
			fRec14[1] = fRec14[0];
			fRec15[2] = fRec15[1];
			fRec15[1] = fRec15[0];
			fRec16[2] = fRec16[1];
			fRec16[1] = fRec16[0];
			fRec17[2] = fRec17[1];
			fRec17[1] = fRec17[0];
			fRec18[2] = fRec18[1];
			fRec18[1] = fRec18[0];
			fRec19[2] = fRec19[1];
			fRec19[1] = fRec19[0];
			fRec20[2] = fRec20[1];
			fRec20[1] = fRec20[0];
			fRec21[2] = fRec21[1];
			fRec21[1] = fRec21[0];
			fRec22[2] = fRec22[1];
			fRec22[1] = fRec22[0];
			fRec23[2] = fRec23[1];
			fRec23[1] = fRec23[0];
		}
	}

};

#undef private
#undef virtual
#undef mydsp

/*
 * ChucK glue code
 */
static t_CKUINT qt_offset_data = 0;
static int g_sr = 44100;
static int g_nChans = 1;

CK_DLL_CTOR(qt_ctor)
{
    // return data to be used later
    qt *d = new qt;
    OBJ_MEMBER_UINT(SELF, qt_offset_data) = (t_CKUINT)d;
    d->init(g_sr);
    d->ck_frame_in = new SAMPLE*[g_nChans];
    d->ck_frame_out = new SAMPLE*[g_nChans];
}

CK_DLL_DTOR(qt_dtor)
{
    qt *d = (qt*)OBJ_MEMBER_UINT(SELF, qt_offset_data);

    delete[] d->ck_frame_in;
    delete[] d->ck_frame_out;
    
    delete d;
    
    OBJ_MEMBER_UINT(SELF, qt_offset_data) = 0;
}

// mono tick
CK_DLL_TICK(qt_tick)
{
    qt *d = (qt*)OBJ_MEMBER_UINT(SELF, qt_offset_data);
    
    d->ck_frame_in[0] = &in;
    d->ck_frame_out[0] = out;

    d->compute(1, d->ck_frame_in, d->ck_frame_out);
    
    return TRUE;
}

// multichannel tick
CK_DLL_TICKF(qt_tickf)
{
    qt *d = (qt*)OBJ_MEMBER_UINT(SELF, qt_offset_data);
    
    for(int f = 0; f < nframes; f++)
    {
        // fake-deinterleave
        for(int c = 0; c < g_nChans; c++)
        {
            d->ck_frame_in[c] = &in[f*g_nChans+c];
            d->ck_frame_out[c] = &out[f*g_nChans+c];
        }
        
        d->compute(1, d->ck_frame_in, d->ck_frame_out);
    }
    
    return TRUE;
}

CK_DLL_MFUN(qt_ctrl_fHslider3)
{
    qt *d = (qt*)OBJ_MEMBER_UINT(SELF, qt_offset_data);
    d->fHslider3 = (SAMPLE)GET_CK_FLOAT(ARGS);
    RETURN->v_float = (t_CKFLOAT)(d->fHslider3);
}

CK_DLL_MFUN(qt_cget_fHslider3)
{
    qt *d = (qt*)OBJ_MEMBER_UINT(SELF, qt_offset_data);
    RETURN->v_float = (t_CKFLOAT)(d->fHslider3);
}


CK_DLL_MFUN(qt_ctrl_fHslider0)
{
    qt *d = (qt*)OBJ_MEMBER_UINT(SELF, qt_offset_data);
    d->fHslider0 = (SAMPLE)GET_CK_FLOAT(ARGS);
    RETURN->v_float = (t_CKFLOAT)(d->fHslider0);
}

CK_DLL_MFUN(qt_cget_fHslider0)
{
    qt *d = (qt*)OBJ_MEMBER_UINT(SELF, qt_offset_data);
    RETURN->v_float = (t_CKFLOAT)(d->fHslider0);
}


CK_DLL_MFUN(qt_ctrl_fHslider1)
{
    qt *d = (qt*)OBJ_MEMBER_UINT(SELF, qt_offset_data);
    d->fHslider1 = (SAMPLE)GET_CK_FLOAT(ARGS);
    RETURN->v_float = (t_CKFLOAT)(d->fHslider1);
}

CK_DLL_MFUN(qt_cget_fHslider1)
{
    qt *d = (qt*)OBJ_MEMBER_UINT(SELF, qt_offset_data);
    RETURN->v_float = (t_CKFLOAT)(d->fHslider1);
}


CK_DLL_MFUN(qt_ctrl_fHslider2)
{
    qt *d = (qt*)OBJ_MEMBER_UINT(SELF, qt_offset_data);
    d->fHslider2 = (SAMPLE)GET_CK_FLOAT(ARGS);
    RETURN->v_float = (t_CKFLOAT)(d->fHslider2);
}

CK_DLL_MFUN(qt_cget_fHslider2)
{
    qt *d = (qt*)OBJ_MEMBER_UINT(SELF, qt_offset_data);
    RETURN->v_float = (t_CKFLOAT)(d->fHslider2);
}




CK_DLL_QUERY(qt_query)
{
    g_sr = QUERY->srate;

	qt temp; // needed to get IO channel count

    QUERY->setname(QUERY, "qt");
    
    QUERY->begin_class(QUERY, "qt", "UGen");
    
    QUERY->add_ctor(QUERY, qt_ctor);
    QUERY->add_dtor(QUERY, qt_dtor);
    
    g_nChans = max(temp.getNumInputs(), temp.getNumOutputs());
    
    if(g_nChans == 1)
        QUERY->add_ugen_func(QUERY, qt_tick, NULL, g_nChans, g_nChans);
    else
        QUERY->add_ugen_funcf(QUERY, qt_tickf, NULL, g_nChans, g_nChans);

    // add member variable
    qt_offset_data = QUERY->add_mvar( QUERY, "int", "@qt_data", FALSE );
    if( qt_offset_data == CK_INVALID_OFFSET ) goto error;

    
    QUERY->add_mfun( QUERY, qt_cget_fHslider3 , "float", "freq" );
    
    QUERY->add_mfun( QUERY, qt_ctrl_fHslider3 , "float", "freq" );
    QUERY->add_arg( QUERY, "float", "freq" );
    

    QUERY->add_mfun( QUERY, qt_cget_fHslider0 , "float", "gain" );
    
    QUERY->add_mfun( QUERY, qt_ctrl_fHslider0 , "float", "gain" );
    QUERY->add_arg( QUERY, "float", "gain" );
    

    QUERY->add_mfun( QUERY, qt_cget_fHslider1 , "float", "pos" );
    
    QUERY->add_mfun( QUERY, qt_ctrl_fHslider1 , "float", "pos" );
    QUERY->add_arg( QUERY, "float", "pos" );
    

    QUERY->add_mfun( QUERY, qt_cget_fHslider2 , "float", "sharp" );
    
    QUERY->add_mfun( QUERY, qt_ctrl_fHslider2 , "float", "sharp" );
    QUERY->add_arg( QUERY, "float", "sharp" );
    


    // end import
	QUERY->end_class(QUERY);
	
    return TRUE;

error:
    // end import
	QUERY->end_class(QUERY);

    return FALSE;
}

#endif
