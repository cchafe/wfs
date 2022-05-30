//chuck --chugin-path:../qt/ssrChugClient/ --srate:48000 ssrChugClient-test.ck
// odd behavior from chugins -- they also load any .ck in the directory

ssrChugClient s => dac.chan(0);
dac.gain(0.05);
//s.freq(1000.0);
1::hour => now;
