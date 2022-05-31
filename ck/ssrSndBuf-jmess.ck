// chuck  --channels:3 --chugin-path:../qt/ssr/  --caution-to-the-wind ssrSndBuf-jmess.ck

ssr s => dac;
dac.gain(0.05);
s.connect();
s.gain(0.0001);
s.freq(100.0);
<<<s.freq()>>>;
Std.system("jmess -D");

SndBuf snd => dac.chan(0);
snd.read("../wav/BongosKongas.mono.wav");
//snd.pos((38::second/samp)$int);
snd.gain(0.0);
SinOsc tri => dac.chan(0);
tri.freq(1000.0);
tri.gain(0.1);


SndBuf snd1 => dac.chan(1);
snd1.read("../wav/meer.wav");
snd1.pos((8::second/samp)$int);
snd1.gain(0.0);
/*
SndBuf snd2 => dac.chan(2);
snd2.read("birdsWFS.wav");
snd2.pos((18::second/samp)$int);
snd2.gain(0.6);
*/
1::second => now;
Std.system("jmess -c ../jmess/binOneSrc.xml");
while (true)
for (0=>int i; i<100; i++) {
// <request><source id="42"><position x="1.2" y="-2"/></source></request>
  i*0.03 => float x;
  1.5 -=> x;
  5*0.3 => float y;
//  Std.system("echo '"+blob+"' | nc localhost 5000 &> /dev/null &");
  s.checkConnection();
  150::ms => now;
}

// ecasound -i BongosKongas.c1.wav -o jack_multi,system:playback_1

