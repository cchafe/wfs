//chuck --chugin-path:../qt/MagicSine/ --srate:48000 MagicSine-test.ck 

MagicSine s => dac;
dac.gain(0.05);
//s.freq(1000.0);
1::hour => now;
