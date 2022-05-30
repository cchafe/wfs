//chuck --chugin-path:../qt/scc/ --srate:48000 scc.ck

// in ../qt/scc/
// odd behavior from chugins -- they also load any .ck in the directory
// so... rm *.ck from the chugin dir
// to make a new chugin, xxx
// make distclean
// ./clone scc xxx
// cd xxx
// qmake-qt5
// make
// xxx s => dac.chan(0);

scc s => dac.chan(0);
dac.gain(0.05);
while (true) {
  s.freq((now/samp)%5000+1000);
  100::ms => now;
}
