/*----------------------------------------------------------------------------
 ChucK scc Unit Generator
 
 Implements efficient sine oscillator using the iterative "magic circle" 
 algorithm, at the expensive of not being able to set the phase (for now at 
 least). Uses 4 multiplies + 2 adds per sample. 
 
 scc is about 25% faster when running a fixed freq sine wave, so its 
 main use is when you need a lot of sine waves and are hitting a performance
 bottleneck. 
 
 Copyright (c) 2012 Spencer Salazar.  All rights reserved.
 
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 U.S.A.
 -----------------------------------------------------------------------------*/

#include "chuck_dl.h"
#include "chuck_def.h"

#include <stdio.h>
#include <limits.h>
#include <math.h>


CK_DLL_CTOR(scc_ctor);
CK_DLL_DTOR(scc_dtor);

CK_DLL_MFUN(scc_setFreq);
CK_DLL_MFUN(scc_getFreq);

CK_DLL_TICK(scc_tick);

t_CKINT scc_data_offset = 0;


class scc
{
public:
    
    scc(float fs)
    {
        m_fs = fs;
        setFreq(1440);
        fprintf(stderr,"xxxxxxxxxxxxxxxxxx  %g\n",fs);
        m_x = 1;
        m_y = 0;
    }
    
    SAMPLE tick(SAMPLE in)
    {
        m_x = m_x + m_epsilon*m_y;
        m_y = -m_epsilon*m_x + m_y;
        return m_y;
    }
    
    t_CKFLOAT setFreq(t_CKFLOAT f)
    {
        m_freq = f;
        m_epsilon = 2.0*sin(2.0*ONE_PI*(m_freq/m_fs)/2.0);
        return m_freq;
    }
    
    t_CKFLOAT getFreq() { return m_freq; }
    
private:
    
    SAMPLE m_x, m_y;
    t_CKFLOAT m_fs;
    t_CKFLOAT m_freq;
    t_CKFLOAT m_epsilon;
};

CK_DLL_QUERY(scc)
{
    QUERY->setname(QUERY, "scc");
    
    QUERY->begin_class(QUERY, "scc", "UGen");
    QUERY->doc_class(QUERY, "Fast, recursive sine wave generator using the so-called &quot;magic circle&quot; algorithm (see <a href=\"https://ccrma.stanford.edu/~jos/pasp/Digital_Sinusoid_Generators.html\">https://ccrma.stanford.edu/~jos/pasp/Digital_Sinusoid_Generators.html</a>). "
        "Can be 30-40% faster than regular SinOsc. "
        "Frequency modulation will negate this performance benefit; most useful when pure sine tones are desired or for additive synthesis. ");
    
    QUERY->add_ctor(QUERY, scc_ctor);
    QUERY->add_dtor(QUERY, scc_dtor);
    
    QUERY->add_ugen_func(QUERY, scc_tick, NULL, 1, 1);
    
    QUERY->add_mfun(QUERY, scc_setFreq, "float", "freq");
    QUERY->add_arg(QUERY, "float", "arg");
    QUERY->doc_func(QUERY, "Oscillator frequency [Hz]. ");
    
    QUERY->add_mfun(QUERY, scc_getFreq, "float", "freq");
    QUERY->doc_func(QUERY, "Oscillator frequency [Hz]. ");
    
    scc_data_offset = QUERY->add_mvar(QUERY, "int", "@scc_data", false);
    
    QUERY->end_class(QUERY);

    return TRUE;
}


CK_DLL_CTOR(scc_ctor)
{
    OBJ_MEMBER_INT(SELF, scc_data_offset) = 0;
    
    scc * bcdata = new scc(API->vm->get_srate(API, SHRED));
    
    OBJ_MEMBER_INT(SELF, scc_data_offset) = (t_CKINT) bcdata;
}

CK_DLL_DTOR(scc_dtor)
{
    scc * bcdata = (scc *) OBJ_MEMBER_INT(SELF, scc_data_offset);
    if(bcdata)
    {
        delete bcdata;
        OBJ_MEMBER_INT(SELF, scc_data_offset) = 0;
        bcdata = NULL;
    }
}

CK_DLL_TICK(scc_tick)
{
    scc * c = (scc *) OBJ_MEMBER_INT(SELF, scc_data_offset);
    
    if(c) *out = c->tick(in);

    return TRUE;
}

CK_DLL_MFUN(scc_setFreq)
{
    scc * bcdata = (scc *) OBJ_MEMBER_INT(SELF, scc_data_offset);
    // TODO: sanity check
    RETURN->v_float = bcdata->setFreq(GET_NEXT_FLOAT(ARGS));
}

CK_DLL_MFUN(scc_getFreq)
{
    scc * bcdata = (scc *) OBJ_MEMBER_INT(SELF, scc_data_offset);
    RETURN->v_float = bcdata->getFreq();
}

