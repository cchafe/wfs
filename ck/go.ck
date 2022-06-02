// chuck  --channels:3 --chugin-path:../qt/ssr/  --caution-to-the-wind go.ck
Std.system("cd ../run; ssr-binaural  --hrirs xxx.wav bin.asd --end-of-message-character=10 --ip-server=5000 &");
1::second => now;
ssr ck2ssr => dac; // it's also an osc
ck2ssr.connect();
ck2ssr.gain(0.000);
ck2ssr.freq(100.0);
<<<ck2ssr.freq()>>>;

class sndSrc {
  int myID;
  SndBuf snd;
  vec4 pos;
  fun void setup (int id, string sndFile[]) {
    id => myID;
    snd.read(sndFile[0]);
    snd => dac.chan(myID);
    snd.gain(Std.atof(sndFile[1]));
    snd.pos( ((Std.atof(sndFile[2]))::second/samp)$int );
    snd.loop(true);
    myID => pos.w;
    myID => pos.y;
    1 +=> pos.y;
    2 *=> pos.y;
    ck2ssr.addSrc(myID);
  }
}

[["../wav/BongosKongas.mono.wav","0.15","30.0"], 
 ["../wav/birdsWFS.wav","0.1","0.0"],
 ["../wav/meer.wav","0.01","18.0"]
 ] @=> string sndFiles[][];
sndFiles.cap() => int nSrcs;
sndSrc ss[nSrcs];
for (0=>int i; i<nSrcs; i++) {
  ss[i].setup(i, sndFiles[i]); 
}

1::second => now;
Std.system("jmess -D");
Std.system("jmess -c ../jmess/bin3Srcs.xml");
while (true)
for (0=>int i; i<100; i++) {
  i*0.1 => float x;
  5 -=> x;
  x => ss[i % nSrcs].pos.x;
  ck2ssr.mvSrcV(ss[i % nSrcs].pos);
  150::ms => now;
}

