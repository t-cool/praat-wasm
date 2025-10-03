/* SoundFrameIntoSpectrumFrame_def.h
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

#define ooSTRUCT SoundFrameIntoSpectrumFrame
oo_DEFINE_CLASS (SoundFrameIntoSpectrumFrame, SoundFrameIntoSampledFrame)
	oo_BOOLEAN (fast)
	oo_INTEGER (numberOfFourierSamples)
	oo_VEC (fftData, numberOfFourierSamples)
	oo_OBJECT (NUMFourierTable, 0, fourierTable)
	oo_OBJECT (Spectrum, 2, spectrum)

	#if oo_DECLARING
		void inputFrameToOutputFrame ()
			override;
	#endif
		
oo_END_CLASS (SoundFrameIntoSpectrumFrame)
#undef ooSTRUCT

/* End of file SoundFrameIntoSpectrumFrame_def.h */
