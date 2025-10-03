/* SampledIntoSampledStatus.cpp
 *
 * Copyright (C) 2025 David Weenink
 *
 * This code is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This code is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this work. If not, see <http://www.gnu.org/licenses/>.
 */


#include "SampledIntoSampledStatus.h"

#include "oo_DESTROY.h"
#include "SampledIntoSampledStatus_def.h"
#include "oo_COPY.h"
#include "SampledIntoSampledStatus_def.h"
#include "oo_EQUAL.h"
#include "SampledIntoSampledStatus_def.h"
#include "oo_CAN_WRITE_AS_ENCODING.h"
#include "SampledIntoSampledStatus_def.h"
#include "oo_WRITE_TEXT.h"
#include "SampledIntoSampledStatus_def.h"
#include "oo_WRITE_BINARY.h"
#include "SampledIntoSampledStatus_def.h"
#include "oo_READ_TEXT.h"
#include "SampledIntoSampledStatus_def.h"
#include "oo_READ_BINARY.h"
#include "SampledIntoSampledStatus_def.h"
#include "oo_DESCRIPTION.h"
#include "SampledIntoSampledStatus_def.h"

Thing_implement (SampledIntoSampledStatus, Daata, 0);

void structSampledIntoSampledStatus :: showStatus () {
	MelderInfo_writeLine (U"frame\tinfo\n");
	for (integer i = 1; i <= numberOfFrames; i ++)
		MelderInfo_writeLine (i, U"\t", frameIntoFrameInfo [i]);
	MelderInfo_close ();
}

static void SampledIntoSampledStatus_init (SampledIntoSampledStatus me, integer numberOfFrames) {
	my numberOfFrames = numberOfFrames;
	my frameIntoFrameInfo = zero_INTVEC (numberOfFrames);
}


Thing_implement (SoundIntoSampledStatus, SampledIntoSampledStatus, 0);

void structSoundIntoSampledStatus :: showStatus () {
	
	MelderInfo_writeLine (U"frame\tinfo\tbegin\n");
	for (integer i = 1; i <= numberOfFrames; i ++)
		MelderInfo_writeLine (i, U"\t", frameIntoFrameInfo [i], U"\t", soundFrameBegins [i]);
	MelderInfo_close ();
}

static void SoundIntoSampledStatus_init (SoundIntoSampledStatus me, integer numberOfFrames) {
	SampledIntoSampledStatus_init (me, numberOfFrames);
	my soundFrameBegins = zero_INTVEC (numberOfFrames);
}

Thing_implement (SoundIntoLPCStatus, SoundIntoSampledStatus, 0);

autoSoundIntoLPCStatus SoundIntoLPCStatus_create (integer numberOfFrames) {
	try {
		autoSoundIntoLPCStatus me = Thing_new (SoundIntoLPCStatus);
		SoundIntoSampledStatus_init (me.get(), numberOfFrames);
		return me;
	} catch (MelderError) {
		Melder_throw (U"Cannot create SoundIntoLPCStatus.");
	}
}


Thing_implement (SoundIntoPowerCepstrogramStatus, SoundIntoSampledStatus, 0);

autoSoundIntoPowerCepstrogramStatus SoundIntoPowerCepstrogramStatus_create (integer numberOfFrames) {
	try {
		autoSoundIntoPowerCepstrogramStatus me = Thing_new (SoundIntoPowerCepstrogramStatus);
		SoundIntoSampledStatus_init (me.get(), numberOfFrames);
		return me;
	} catch (MelderError) {
		Melder_throw (U"Cannot create SoundIntoPowerCepstrogramStatus.");
	}
}


Thing_implement (PowerCepstrogramIntoMatrixStatus, SampledIntoSampledStatus, 0);

void structPowerCepstrogramIntoMatrixStatus :: showStatus () {
	
	MelderInfo_writeLine (U"frame\tinfo\tbegin\tslope\tintercept\tntries\n");
	for (integer i = 1; i <= numberOfFrames; i ++)
		MelderInfo_writeLine (i, U"\t", frameIntoFrameInfo [i], U"\t", startFrames [i], U"\t", slopes [i], U"\t", intercepts [i], 
			U"\t", numberOfTries [i] );
	MelderInfo_close ();
}

autoPowerCepstrogramIntoMatrixStatus PowerCepstrogramIntoMatrixStatus_create (integer numberOfFrames) {
	try {
		autoPowerCepstrogramIntoMatrixStatus me = Thing_new (PowerCepstrogramIntoMatrixStatus);
		SampledIntoSampledStatus_init (me.get(), numberOfFrames);
		my slopes = zero_VEC (numberOfFrames);
		my intercepts = zero_VEC (numberOfFrames);
		my startFrames = zero_INTVEC (numberOfFrames);
		my numberOfTries = zero_INTVEC (numberOfFrames);
		return me;
	} catch (MelderError) {
		Melder_throw (U"Cannot create PowerCepstrogramIntoMatrixStatus.");
	}
}


Thing_implement (LPCIntoFormantStatus, SampledIntoSampledStatus, 0);

autoLPCIntoFormantStatus LPCIntoFormantStatus_create (integer numberOfFrames) {
	try {
		autoLPCIntoFormantStatus me = Thing_new (LPCIntoFormantStatus);
		SampledIntoSampledStatus_init (me.get(), numberOfFrames);
		return me;
	} catch (MelderError) {
		Melder_throw (U"Cannot create LPCIntoFormantStatus.");
	}
}


Thing_implement (LPCAndSoundIntoLPCRobustStatus, SampledIntoSampledStatus, 0);

autoLPCAndSoundIntoLPCRobustStatus LPCAndSoundIntoLPCRobustStatus_create (integer numberOfFrames) {
	try {
		autoLPCAndSoundIntoLPCRobustStatus me = Thing_new (LPCAndSoundIntoLPCRobustStatus);
		SampledIntoSampledStatus_init (me.get(), numberOfFrames);
		return me;
	} catch (MelderError) {
		Melder_throw (U"Cannot create LPCAndSoundIntoLPCRobustStatus.");
	}
}


Thing_implement (SoundIntoLPCRobustStatus, SampledIntoSampledStatus, 0);

autoSoundIntoLPCRobustStatus SoundIntoLPCRobustStatus_create (integer numberOfFrames) {
	try {
		autoSoundIntoLPCRobustStatus me = Thing_new (SoundIntoLPCRobustStatus);
		my soundIntoLPCStatus = SoundIntoLPCStatus_create (numberOfFrames);
		my lpcAndSoundIntoLPCRobustStatus = LPCAndSoundIntoLPCRobustStatus_create (numberOfFrames);
		return me;
	} catch (MelderError) {
		Melder_throw (U"Cannot create LPCAndSoundIntoLPCRobustStatus.");
	}
}


Thing_implement (SoundIntoFormantStatus, SampledIntoSampledStatus, 0);

autoSoundIntoFormantStatus SoundIntoFormantStatus_create (integer numberOfFrames) {
	try {
		autoSoundIntoFormantStatus me = Thing_new (SoundIntoFormantStatus);
		my soundIntoLPCStatus = SoundIntoLPCStatus_create (numberOfFrames);
		my lpcIntoFormantStatus = LPCIntoFormantStatus_create (numberOfFrames);
		return me;
	} catch (MelderError) {
		Melder_throw (U"Cannot create LPCAndSoundIntoLPCRobustStatus.");
	}
}


Thing_implement (SoundIntoFormantRobustStatus, SampledIntoSampledStatus, 0);

autoSoundIntoFormantRobustStatus SoundIntoFormantRobustStatus_create (integer numberOfFrames) {
	try {
		autoSoundIntoFormantRobustStatus me = Thing_new (SoundIntoFormantRobustStatus);
		my soundIntoLPCRobustStatus = SoundIntoLPCRobustStatus_create (numberOfFrames);
		my lpcIntoFormantStatus = LPCIntoFormantStatus_create (numberOfFrames);
		return me;
	} catch (MelderError) {
		Melder_throw (U"Cannot create SoundIntoFormantRobustStatus.");
	}
}


Thing_implement (SoundAndLPCIntoFormantRobustStatus, SampledIntoSampledStatus, 0);

autoSoundAndLPCIntoFormantRobustStatus SoundAndLPCIntoFormantRobustStatus_create (integer numberOfFrames) {
	try {
		autoSoundAndLPCIntoFormantRobustStatus me = Thing_new (SoundAndLPCIntoFormantRobustStatus);
		my lpcAndSoundIntoLPCRobustStatus = LPCAndSoundIntoLPCRobustStatus_create (numberOfFrames);
		my lpcIntoFormantStatus = LPCIntoFormantStatus_create (numberOfFrames);
		return me;
	} catch (MelderError) {
		Melder_throw (U"Cannot create SoundAndLPCIntoFormantRobustStatus.");
	}
}

Thing_implement (LPCAndLineSpectralFrequenciesStatus, SampledIntoSampledStatus, 0);

autoLPCAndLineSpectralFrequenciesStatus LPCAndLineSpectralFrequenciesStatus_create (integer numberOfFrames) {
	try {
		autoLPCAndLineSpectralFrequenciesStatus me = Thing_new (LPCAndLineSpectralFrequenciesStatus);
		SampledIntoSampledStatus_init (me.get(), numberOfFrames);
		return me;
	} catch (MelderError) {
		Melder_throw (U"Cannot create LPCAndLineSpectralFrequenciesStatus.");
	}
}

/* End of file SampledIntoSampledStatus.cpp */	
