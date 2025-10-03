/* Artword_Speaker_to_Sound.h
 *
 * Copyright (C) 1992-2005,2011,2015-2017,2021 Paul Boersma
 *
 * This code is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This code is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this work. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Artword.h"
#include "Speaker.h"
#include "Sound.h"

autoSound Artword_Speaker_to_Sound (Artword artword, Speaker speaker,
   double samplingFrequency, integer oversampling,
   autoSound *w1, integer iw1, autoSound *w2, integer iw2, autoSound *w3, integer iw3,
   autoSound *p1, integer ip1, autoSound *p2, integer ip2, autoSound *p3, integer ip3,
   autoSound *v1, integer iv1, autoSound *v2, integer iv2, autoSound *v3, integer iv3);

/* End of file Artword_Speaker_to_Sound.h */
