declare name "ccNylon";
declare description "nylon guitar with adjustable hf damp and T60";
declare license "MIT";
declare copyright "(c)Romain Michon, CCRMA (Stanford University), GRAME";

import("stdfaust.lib");

ccNuts(hf, t60) = pm.lTermination(-tmp,pm.basicBlock)
with{
    tmp = pm.bridgeFilter(hf,t60); // can't compile "-pm..."
};

ccBridge(hf, t60) = pm.rTermination(pm.basicBlock,-tmp) : _,transmittance,_
with{
    tmp = pm.bridgeFilter(hf,t60); // can't compile "-pm..."
    transmittance = _; 
};

ccNylon(length,pluckPosition, hf, t60, excitation) = pm.endChain(egChain)
with{
  maxStringLength = maxLength; // meters
	lengthTuning = 0.11;
	stringL = length-lengthTuning;
  egChain = pm.chain(ccNuts(hf, t60) : pm.nylonString(stringL,pluckPosition,excitation) :
	ccBridge(hf, t60) : pm.guitarBody : pm.out);
};

ks = ccNylon( (freq : pm.f2l), pos, hf, t60)
with{
	freq = hslider("freq",440,50,1000,0.01);
	pos = hslider("pos",0.9,0,1,0.01);
	hf = hslider("hf",0.4,0,1,0.01);
	t60 = hslider("t60",0.5,0,20,0.01);
};

process = _ : ks <: _,_;

/*
Impulse imp => ccNylonPulse ks => dac;
0.0 => float pos;
while (true)
{
    imp.next(1.0);
    1::second => now;
    ks.pos(pos);
    0.1+=>pos;
    1.0%=>pos;
}
*/
