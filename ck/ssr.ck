//chuck --chugin-path:../qt/ssr/ --srate:48000 ssr.ck 

ssr s => dac;
dac.gain(0.05);
1::second => now;
s.freq(1500.0);
<<<s.freq()>>>;
1::second => now;
<<<s.checkFreq()>>>;
1::hour => now;
