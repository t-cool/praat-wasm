/* NUMFourierTable_def.h
 *
 * Copyright (C) 2025 David Weenink
 *
 * This code is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
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

#define ooSTRUCT NUMFourierTable
oo_DEFINE_CLASS (NUMFourierTable, Daata)

	oo_INTEGER (n)
	oo_INTEGER (trigcacheSize)
	oo_INTEGER (splitcacheSize)
	oo_VEC (trigcache, trigcacheSize)
	oo_INTVEC (splitcache, splitcacheSize)

oo_END_CLASS (NUMFourierTable)
#undef ooSTRUCT

/* End of file NUMFourierTable_def.h */
