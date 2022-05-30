declare name "Djembe";
import("stdfaust.lib");
freq = hslider("freq",72,50,128,0.01);
gain = hslider("gain",0.5,0,1,0.01);
pos = hslider("pos",0.3,0,1,0.01);
sharp = hslider("sharp",0.4,0,1,0.01);
process = pm.djembe(freq, pos, sharp, gain);
// process = ba.pulsen(1, 5000) : pm.djembe(72, 0.3, 0.4, 1);
