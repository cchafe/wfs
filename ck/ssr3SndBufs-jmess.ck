// chuck  --channels:3 --chugin-path:../qt/ssr/  --caution-to-the-wind ssr3SndBufs-jmess.ck
3 => int nSrcs;
vec4 src[nSrcs];
ssr s => dac; // it's also an osc
dac.gain(0.05);
s.connect();
s.gain(0.0001);
s.freq(100.0);
<<<s.freq()>>>;

SndBuf snd[nSrcs];
snd[0].read("../wav/BongosKongas.mono.wav");
snd[1].read("../wav/meer.wav");
snd[2].read("../wav/birdsWFS.wav");
for (0=>int i; i<nSrcs; i++) {
  snd[i] => dac.chan(i);
//snd[i].pos((38::second/samp)$int);
  snd[i].gain(1.0);
  i => src[i].w;
  i => src[i].y;
  s.addSrc(src[i].w);
}

1::second => now;
Std.system("jmess -D");
Std.system("jmess -c ../jmess/bin3Srcs.xml");
while (true)
for (0=>int i; i<100; i++) {
// <<<src[0], src[0].x>>>;
  i*0.03 => float x;
  1.5 -=> x;
  x => src[0].x;
  5*0.3 => float y;
  s.mvSrcV(src[i % nSrcs]);
  150::ms => now;
}

