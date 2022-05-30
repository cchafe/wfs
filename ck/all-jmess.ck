// chuck  --channels:3 all-jmess.ck


SndBuf snd => dac.chan(0);
snd.read("BongosKongas.mono.wav");
snd.pos((38::second/samp)$int);
snd.gain(1.0);
Std.system("jmess -D");

SndBuf snd1 => dac.chan(1);
snd1.read("meer.wav");
snd1.pos((8::second/samp)$int);
snd1.gain(0.3);

SndBuf snd2 => dac.chan(2);
snd2.read("birdsWFS.wav");
snd2.pos((18::second/samp)$int);
snd2.gain(0.6);
1::second => now;
Std.system("jmess -c all.xml");
1::day => now;


// ecasound -i BongosKongas.c1.wav -o jack_multi,system:playback_1

