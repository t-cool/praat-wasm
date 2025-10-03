# Praat script runAllTests.praat
# Paul Boersma 2020-12-28
# 2024-12-01 writing settings to UTF-8 for Praat 7
# 2025-08-16 make more reproducible
#
# This script runs all Praat scripts in its subdirectories.

Text writing settings: "UTF-8"
if macintosh
	Text reading settings: "try UTF-8, then MacRoman"
elif windows
	Text reading settings: "try UTF-8, then Windows Latin-1"
elif unix
	Text reading settings: "try UTF-8, then ISO Latin-1"
else
	exitScript: "Unknown operating system."
endif

writeInfoLine: "Running all tests..."

memoryReport$ = Report memory use
strings_before = extractNumber (memoryReport$, "Strings:")
arrays_before  = extractNumber (memoryReport$, "Arrays:")
things_before  = extractNumber (memoryReport$, "Things:")
other_before   = extractNumber (memoryReport$, "Other:")

topPath$ = "."
topFolderNames$# = folderNames$# (topPath$)
for topFolder to size (topFolderNames$#)
	topFolderName$ = topFolderNames$# [topFolder]
	if topFolderName$ <> "manually" and topFolderName$ <> "speed"
		topFolderPath$ = topPath$ + "/" + topFolderName$
		@runFilesInFolder: topFolderPath$
		subfolderNames$# = folderNames$# (topFolderPath$ + "/*")
		for subfolder to size (subfolderNames$#)
			subFolderPath$ = topFolderPath$ + "/" + subfolderNames$# [subfolder]
			@runFilesInFolder: subFolderPath$
		endfor
	endif
endfor

procedure runFilesInFolder: .folderPath$
	.fileNames$# = fileNames$# (.folderPath$ + "/*.praat")
	for .file to size (.fileNames$#)
		.filePath$ = .folderPath$ + "/" + .fileNames$# [.file]
		appendInfoLine: "### executing ", .filePath$, ":"
		#
		# The following two lines aim at making the test reproducible.
		# That is, the test should give the same result on different
		# computers and different platforms and at different times.
		# The random seed is allowed to change with the Praat release;
		# just run all the tests if you change the random seed,
		# even if there was no change in the Praat source code.
		# This is because the success of some precision tests
		# has been reported (by maintainers) to depend on the random state.
		# Also make sure that the random seed is the same
		# for the other two "runAlltests" scripts.
		#
		random_initializeWithSeedUnsafelyButPredictably (5489)
		Debug multi-threading: "yes", 8, 0, "no"   ; eight threads for everybody
		runScript: .filePath$
	endfor
	random_initializeSafelyAndUnpredictably()
	Debug multi-threading: "yes", 0, 0, "no"
endproc

writeInfoLine: "                 ALL PRAAT TESTS WENT OK"
appendInfoLine: ""
line$ [5] = "        #####          #####        #####   #####"
line$ [8] = "        #####          #####        #######"
line$ [1] = "               ######               #####           #####"
line$ [2] = "           ##############           #####         #####"
line$ [4] = "        #####          #####        #####     #####"
line$ [7] = "        #####          #####        #########"
line$ [9] = "        #####          #####        #####"
line$ [3] = "         #####        #####         #####       #####"
line$ [6] = "        #####          #####        ##### #####"
for line from 1 to 9
	appendInfoLine: line$ [line]
endfor
for line from 1 to 8
	appendInfoLine: line$ [9 - line]
endfor

memoryReport$ = Report memory use
strings_after = extractNumber (memoryReport$, "Strings:")
arrays_after  = extractNumber (memoryReport$, "Arrays:")
things_after  = extractNumber (memoryReport$, "Things:")
other_after   = extractNumber (memoryReport$, "Other:")

appendInfoLine ()
appendInfoLine: "Leaking:"
appendInfoLine: "   Strings: ", strings_after - strings_before
appendInfoLine: "   Arrays: ", arrays_after - arrays_before
appendInfoLine: "   Things: ", things_after - things_before
appendInfoLine: "   Other: ", other_after - other_before

