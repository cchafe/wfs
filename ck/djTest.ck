// chuck --chugin-path:../dsp/ --srate:48000 ck/djTest.ck

stereoFreeverb r => dac;
//dac => WvOut2 w => blackhole;
//w.wavFilename("/tmp/miami6min2.wav");
//r.gain(1.5);

  Impulse imp => 
  dj djembe => r; 
while (true) {    
      imp.next(1.0);
      djembe.freq(Std.mtof( 1 + (1) * 35));
      djembe.gain( Std.dbtorms(80 + 1 * 20) ); // 80 20
      djembe.sharp(2.0 * Std.dbtorms(40 + 1 * 60)); // 40 50
      djembe.pos(1);
1000::ms => now;
    }
<<<"done while">>>;


