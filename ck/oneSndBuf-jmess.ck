// chuck  --channels:3 oneSndBuf-jmess.ck

"<request> <source new=\"true\" name=\"ps2\" port=\"2\" > <position x=\"1\" y=\"1\"/> </source> </request>" => string blob;
Std.system("echo '"+blob+"' | nc localhost 5000");
Std.system("jmess -D");

SndBuf snd => dac.chan(0);
snd.read("../wav/BongosKongas.mono.wav");
snd.pos((38::second/samp)$int);
snd.gain(1.0);

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
for (0=>int i; i<1000; i++) {
// <request><source id="42"><position x="1.2" y="-2"/></source></request>
  i*0.003 => float x;
  1.5 -=> x;
  5*0.3 => float y;
  "<request> <source id=\"1\" > <position x=\""+x+"\" y=\""+y+"\"/> </source> </request>" 
    => blob;
  Std.system("echo '"+blob+"' | nc localhost 5000 &> /dev/null &");
  10::ms => now;
}

// ecasound -i BongosKongas.c1.wav -o jack_multi,system:playback_1

