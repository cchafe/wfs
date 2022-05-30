// chuck --chugin-path:/home/cc/git-iceCore/dsp/ --srate:48000 ck/miami6min2.ck
// /tmp/dat/NASSAU_AIRPORT_NEW  5anaM  .dat
// NASSAU_AIRPORT_NEW  -qcfM  .dat
// CAMAGUEYCAMAGUEY-qcfM.dat
0.5::minute => dur lengthMinutes;
stereoFreeverb r => dac;
dac => WvOut2 w => blackhole;
w.wavFilename("/tmp/miami6min2.wav");
r.gain(1.5);
false => int quit;
1900.0 => float startYear => float year;
2021.9 => float endYear;
[-0.75, 0.75, -0.95, 0.95] @=> float azis[];
//[100.0, 40.0, 80.0, 20.0] @=> float foff[];
//[-60.0, 60.0, -60.0, 60.0] @=> float fscl[];
[70.0, 50.0, 80.0, 20.0] @=> float foff[];
[-20.0, 20.0, -60.0, 60.0] @=> float fscl[];
Player p[4];
//p[0].open("/tmp/dat/CAMAGUEYCAMAGUEY5anaM.dat", 0);
//p[1].open("/tmp/dat/CAMAGUEYCAMAGUEY-qcfM.dat", 1);
//p[2].open("/tmp/dat/NASSAU_AIRPORT_NEW5anaM.dat", 2);

//p[0].opena("/tmp/dat/CAMAGUEYCAMAGUEY-qcfA.dat", 0);
//p[0].open("/tmp/dat/CAMAGUEYCAMAGUEY-qcfM.dat", 0);

//p[0].opena("/tmp/dat/CANAL_POINT_USDA-qcfA.dat", 0);
//p[0].open("/tmp/dat/CANAL_POINT_USDA-qcfM.dat", 0);

//p[0].opena("/tmp/dat/GUANTANAMO_BAY_NAS-qcfA.dat", 0);
//p[0].open("/tmp/dat/GUANTANAMO_BAY_NAS-qcfM.dat", 0);

//p[0].opena("/tmp/dat/FT_LAUDERDALE-qcfA.dat", 0);
//p[0].open("/tmp/dat/FT_LAUDERDALE-qcfM.dat", 0);

p[1].opena("/tmp/dat/GUANTANAMO_BAY_NAS-qcfA.dat", 1);
p[1].open("/tmp/dat/GUANTANAMO_BAY_NAS-qcfM.dat", 1);

go(startYear) ;
1::second => now;
  <<<"done">>>;
  me.exit();

//p[1].open("/tmp/dat/CAMAGUEYCAMAGUEY-qcfM.dat", 1);
//p[3].open("/tmp/dat/NASSAU_AIRPORT_NEW-qcfM.dat", 0);
//go(startYear) ;
/////////////////////////////

1.0 => float tempo;
fun void go(float y) {
  y => year;
  while (!quit) {
// <<<p[0].nextYear,year>>>;
    1/48000.0 +=> year;
    tempo::samp  => now;
  }
  <<<"done go">>>;
}

class Player {
  TempData td;
  TempData tda;
  float v[2];
  float va[2];
  0.0 => float nextYear;
  Impulse imp => 
  Djembe djembe => r; 
  fun void open(string f, int p) {
    td.reset();
    f => td.finName;
    td.countRows();
    td.parse();
    td.check(); // and scale
<<<"read", td.rows, "rows temperature data">>>;
    0.0 => nextYear;
    0.0 => v[0];
    0.0 => v[1];
    spork ~go(p);
  }
  
  SinOsc osc; 
  fun void opena(string f, int p) {
    osc.gain( ); 
//osc => pan => r;
     tda.reset();
    f => tda.finName;
    tda.countRows();
    tda.parse();
    tda.check(); // and scale
<<<"read", tda.rows, "rows temperature data">>>;
    0.0 => nextYear;
    0.0 => va[0];
    0.0 => va[1];
    spork ~goa(p);
  }

  fun void goa(int p) {
    do {
      tda.next(va);
    } while (va[0] < year);
    
    while (!tda.finishedOneShot) {
//      <<<"\t----------", va[0], va[1], year>>>;
      
osc.freq( Std.mtof( 60 + va[1] * 40));
osc.gain( Std.dbtorms(50 + va[1] * 20) );
osc.gain( 0 );    

      <<<tempo, va[0],va[1]>>>;
      tempo::second => now;
      while (!tda.next(va)) {
        (tempo/2.0)::second => now;
        continue;
      }
    }
//  <<<"done while">>>;
  }

  fun void go(int p) {
//    pan.pan(azis[p]);
    do {
      td.next(v);
    } while (v[0] < year);
    
    0=> int lastYear;
    1.0 => float scl;
    while (!td.finishedOneShot) {
      if (!td.next(v)) {
//      if ((!td.next(v)) || (v[0]<year)) {
//<<<"\t",v[0],v[1],year>>>;
        continue;
      }
      Math.floor(v[0])$int => int newYear;
      v[0] => nextYear;
      if(newYear != lastYear) {
<<<"\t---- ",newYear>>>;
        0.0 => float sum;
        for (td.ptr => int i; i<(td.ptr+12); i++) {
          if (i > td.anom.cap()-1) {
            break;
          }
          tempero(td.anom[i], va[1]) +=> sum;
        }
        sum => tempo;
        newYear => lastYear;
      }
      
      imp.next(1.0);
      djembe.freq(Std.mtof( 1 + (va[1]+v[1]) * 35));
      djembe.gain( Std.dbtorms(80 + v[1] * 20) ); // 80 20
      djembe.sharp(2.0 * Std.dbtorms(40 + va[1] * 60)); // 40 50
      djembe.pos(va[1]);

      tempero(v[1], va[1])::second => now;
    }
<<<"done while">>>;
w.closeFile();
    true => quit;
  }
}
          
fun float tempero(float t, float e) {
//Math.pow(e,2.0)=>e;

  t => float tmp;
  0.3 *=> tmp;
  return tmp;
}

/////////////////////////////

class TempData
{
  string finName;
  FileIO fin;
  int rows;
  float years[];
  float anom[];
  int mode[];
  2 => int dim;
  int ptr;
  int finishedOneShot;
  fun void reset()
  {
    0 => ptr;
    0 => finishedOneShot;
  }

  fun float nextVal()
  {
    anom[ptr] => float tmp;
    1+=>ptr;
    rows%=>ptr;
    !ptr => finishedOneShot;
    return tmp;
  }

  fun int next(float byReference[])
  {
//  <<<years[ptr],anom[ptr]>>>;
    mode[ptr] => int isGood;
    if (isGood) {
      years[ptr] => byReference[0];
      anom[ptr] => byReference[1];
    }
    ptr++;
    rows%=>ptr;
    !ptr => finishedOneShot;
    return isGood;
  }

  fun int isFinished()
  {
    return finishedOneShot;
  }

  fun void open(string n)
  {
    n => finName;
    fin.open(finName,FileIO.READ);
    if( !fin.good() )
    {
      <<< "can't open file: ",finName," for reading...">>>;
      me.exit();
    }
  }

  fun int countRows()
  {  
    fin.open(finName,FileIO.READ);
    string str;
    0 => rows;
    while(!fin.eof())
    {
      fin.readLine() => str;
      if(str!="") rows++; // extra lines at end
    }
    fin.close();
    return rows;
  }

  fun void parse()
  {
      new float [rows] @=> years;
      new float [rows] @=> anom;
      new int [rows] @=> mode;
    fin.open(finName,FileIO.READ);
    StringTokenizer tok;
    0.0 => float lastGood;
    for (0=>int i; i<rows; i++)
    {
      fin.readLine() => string str;
      tok.set( str );
      tok.next() => string yearString; // decimal
      Std.atof(yearString) => years[i];
      tok.next() => string anomString;
      if(anomString == "?") {
      // should do prediction!!
        lastGood => anom[i];
        0 => mode[i];
      } else {
        Std.atof(anomString) => anom[i];
        anom[i] => lastGood;
        1 => mode[i];
      }
//      if (Std.atof(yearString) < 1900.0) 0 => mode[i];
//      <<<i,"\t",str,"\n",anomString,lastGood,anom[i]>>>;
    }
    fin.close();
  }

  fun void check()
  {
    years[0] => float lastYear;
    99999.0 => float minAnom;
    -minAnom => float maxAnom;
    for (1=>int i; i<rows; i++)
    {
      years[i] => float thisYear;
      if(thisYear <= lastYear) <<<lastYear,thisYear,"non-monotonic year at",i>>>;
      thisYear => lastYear;
      if (anom[i] < minAnom) anom[i] => minAnom;
      if (anom[i] > maxAnom) anom[i] => maxAnom;
    }
maxAnom - minAnom => float scl;
1.0 / scl => scl;
    for (1=>int i; i<rows; i++)
    {
      anom[i] - minAnom => anom[i];
      scl *=> anom[i];
    }
  }

}

