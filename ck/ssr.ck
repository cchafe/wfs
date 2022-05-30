//chuck --chugin-path:../qt/ssr/ --srate:48000 ssr.ck 

ssr s => dac;
dac.gain(0.05);
//s.freq(1000.0);
1::hour => now;
