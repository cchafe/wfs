declare name "ccNylonPulse";
declare description "Simple call of the Karplus-Strong model for the Faust physical modeling library";
declare license "MIT";
declare copyright "(c)Romain Michon, CCRMA (Stanford University), GRAME";

import("stdfaust.lib");



ks = pm.nylonGuitarModel( (freq : pm.f2l), pos )
with{
	freq = hslider("freq",440,50,1000,0.01);
	pos = hslider("pos",0.9,0,1,0.01);
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
