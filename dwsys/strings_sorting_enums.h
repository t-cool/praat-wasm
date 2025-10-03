/* strings_sorting_enums.h
 *
 * Copyright (C) 2022 David Weenink
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

enums_begin (kStrings_sorting, 0)
	enums_add (kStrings_sorting, 0, NONE, U"None")
	enums_add (kStrings_sorting, 1, ALPHABETICAL, U"alphabetical")
	enums_add (kStrings_sorting, 2, NUMBER_AWARE, U"number-aware")
enums_end (kStrings_sorting, 2, NUMBER_AWARE)

/* End of file strings_sorting_enums.h */
