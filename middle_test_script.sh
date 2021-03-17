#!/bin/bash
make
echo "Compiler built"
echo "====================================="
echo "testing array"
PASSED =0
CHECKED =0
suffix="_driver.c"
#for filename in compiler_tests/array/*_driver.c; do &>errors.txt
#	CHECKED=$((${CHECKED}+1)); 
#bin/c_compiler -S "${filename%_*}"".c" -o output.s &>errors.txt 
#mips-linux-gnu-gcc -mfp32 -o output.o -c output.s &>errors.txt
#mips-linux-gnu-gcc -mfp32 -static -o output output.o "${filename%_*}""_driver.c" &>errors.txt
#qemu-mips output
#echo $?
#if [[ $? == 0 ]]; then
#	echo "Passed"
#	PASSED=$((${PASSED}+1));
#else echo "FAILED >>>>>>>>>>>>>>>>>>>>>>>" "$(basename -- $filename)" "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"
#fi
#rm output.o &>errors.txt
#rm output.s &>errors.txt
#rm output &>errors.txt
#done 
echo "====================================="
echo "testing control_flow"
suffix="_driver.c"
for filename in compiler_tests/control_flow/*_driver.c; do &>errors.txt
		CHECKED=$((${CHECKED}+1));
bin/c_compiler -S "${filename%_*}"".c" -o output.s &>errors.txt
mips-linux-gnu-gcc -mfp32 -o output.o -c output.s &>errors.txt
mips-linux-gnu-gcc -mfp32 -static -o output output.o "${filename%_*}""_driver.c" &>errors.txt
qemu-mips output &>errors.txt
#echo $?
if [[ $? == 0 ]]; then
	echo "Passed"
	PASSED=$((${PASSED}+1));
else echo "FAILED >>>>>>>>>>>>>>>>>>>>>>>" "$(basename -- $filename)" "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"
fi
rm output.o &>errors.txt
rm output.s &>errors.txt
rm output &>errors.txt
done 
echo "====================================="
echo "testing default"
suffix="_driver.c"
for filename in compiler_tests/default/*_driver.c; do &>errors.txt
		CHECKED=$((${CHECKED}+1));
bin/c_compiler -S "${filename%_*}"".c" -o output.s &>errors.txt
mips-linux-gnu-gcc -mfp32 -o output.o -c output.s &>errors.txt
mips-linux-gnu-gcc -mfp32 -static -o output output.o "${filename%_*}""_driver.c" &>errors.txt
qemu-mips output &>errors.txt
#echo $?
if [[ $? == 0 ]]; then
	echo "Passed"
	PASSED=$((${PASSED}+1));
else echo "FAILED >>>>>>>>>>>>>>>>>>>>>>>" "$(basename -- $filename)" "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"
fi
rm output.o &>errors.txt
rm output.s &>errors.txt
rm output &>errors.txt
done 
echo "====================================="
echo "testing float"
suffix="_driver.c"
for filename in compiler_tests/float/*_driver.c; do &>errors.txt
		CHECKED=$((${CHECKED}+1));
bin/c_compiler -S "${filename%_*}"".c" -o output.s &>errors.txt
mips-linux-gnu-gcc -mfp32 -o output.o -c output.s &>errors.txt
mips-linux-gnu-gcc -mfp32 -static -o output output.o "${filename%_*}""_driver.c" &>errors.txt
qemu-mips output &>errors.txt
#echo $?
if [[ $? == 0 ]]; then
	echo "Passed"
	PASSED=$((${PASSED}+1));
else echo "FAILED >>>>>>>>>>>>>>>>>>>>>>>" "$(basename -- $filename)" "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"
fi
rm output.o &>errors.txt
rm output.s &>errors.txt
rm output &>errors.txt
done 
echo "====================================="
echo "testing functions"
suffix="_driver.c"
for filename in compiler_tests/functions/*_driver.c; do &>errors.txt
		CHECKED=$((${CHECKED}+1));
bin/c_compiler -S "${filename%_*}"".c" -o output.s &>errors.txt
mips-linux-gnu-gcc -mfp32 -o output.o -c output.s &>errors.txt
mips-linux-gnu-gcc -mfp32 -static -o output output.o "${filename%_*}""_driver.c" &>errors.txt
qemu-mips output &>errors.txt
#echo $?
if [[ $? == 0 ]]; then
	echo "Passed"
	PASSED=$((${PASSED}+1));
else echo "FAILED >>>>>>>>>>>>>>>>>>>>>>>" "$(basename -- $filename)" "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"
fi
rm output.o &>errors.txt
rm output.s &>errors.txt
rm output &>errors.txt
done 
echo "====================================="
echo "testing integer"
suffix="_driver.c"
for filename in compiler_tests/integer/*_driver.c; do &>errors.txt
		CHECKED=$((${CHECKED}+1));
bin/c_compiler -S "${filename%_*}"".c" -o output.s &>errors.txt
mips-linux-gnu-gcc -mfp32 -o output.o -c output.s &>errors.txt
mips-linux-gnu-gcc -mfp32 -static -o output output.o "${filename%_*}""_driver.c" &>errors.txt
qemu-mips output &>errors.txt
#echo $?
if [[ $? == 0 ]]; then
	echo "Passed"
	PASSED=$((${PASSED}+1));
else echo "FAILED >>>>>>>>>>>>>>>>>>>>>>>" "$(basename -- $filename)" "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"
fi
rm output.o &>errors.txt
rm output.s &>errors.txt
rm output &>errors.txt
done 
echo "====================================="
echo "testing local_var"
suffix="_driver.c"
for filename in compiler_tests/local_var/*_driver.c; do &>errors.txt
		CHECKED=$((${CHECKED}+1));
bin/c_compiler -S "${filename%_*}"".c" -o output.s &>errors.txt
mips-linux-gnu-gcc -mfp32 -o output.o -c output.s &>errors.txt
mips-linux-gnu-gcc -mfp32 -static -o output output.o "${filename%_*}""_driver.c" &>errors.txt
qemu-mips output &>errors.txt
#echo $?
if [[ $? == 0 ]]; then
	echo "Passed"
	PASSED=$((${PASSED}+1));
else echo "FAILED >>>>>>>>>>>>>>>>>>>>>>>" "$(basename -- $filename)" "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"
fi
rm output.o &>errors.txt
rm output.s &>errors.txt
rm output &>errors.txt
done 
echo "====================================="
echo "testing misc"
suffix="_driver.c"
for filename in compiler_tests/misc/*_driver.c; do &>errors.txt
		CHECKED=$((${CHECKED}+1));
bin/c_compiler -S "${filename%_*}"".c" -o output.s &>errors.txt
mips-linux-gnu-gcc -mfp32 -o output.o -c output.s &>errors.txt
mips-linux-gnu-gcc -mfp32 -static -o output output.o "${filename%_*}""_driver.c" &>errors.txt
qemu-mips output &>errors.txt
#echo $?
if [[ $? == 0 ]]; then
	echo "Passed"
	PASSED=$((${PASSED}+1));
else echo "FAILED >>>>>>>>>>>>>>>>>>>>>>>" "$(basename -- $filename)" "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"
fi
rm output.o &>errors.txt
rm output.s &>errors.txt
rm output &>errors.txt
done 
echo "====================================="
echo "testing pointer"
suffix="_driver.c"
for filename in compiler_tests/pointer/*_driver.c; do &>errors.txt
		CHECKED=$((${CHECKED}+1));
bin/c_compiler -S "${filename%_*}"".c" -o output.s &>errors.txt
mips-linux-gnu-gcc -mfp32 -o output.o -c output.s &>errors.txt
mips-linux-gnu-gcc -mfp32 -static -o output output.o "${filename%_*}""_driver.c" &>errors.txt
qemu-mips output &>errors.txt
#echo $?
if [[ $? == 0 ]]; then
	echo "Passed"
	PASSED=$((${PASSED}+1));
else echo "FAILED >>>>>>>>>>>>>>>>>>>>>>>" "$(basename -- $filename)" "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"
fi
rm output.o &>errors.txt
rm output.s &>errors.txt
rm output &>errors.txt
done 
echo "====================================="
echo "testing programs"
suffix="_driver.c"
for filename in compiler_tests/programs/*_driver.c; do &>errors.txt
		CHECKED=$((${CHECKED}+1));
bin/c_compiler -S "${filename%_*}"".c" -o output.s &>errors.txt
mips-linux-gnu-gcc -mfp32 -o output.o -c output.s &>errors.txt
mips-linux-gnu-gcc -mfp32 -static -o output output.o "${filename%_*}""_driver.c" &>errors.txt
qemu-mips output &>errors.txt
#echo $?
if [[ $? == 0 ]]; then
	echo "Passed"
	PASSED=$((${PASSED}+1));
else echo "FAILED >>>>>>>>>>>>>>>>>>>>>>>" "$(basename -- $filename)" "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"
fi
rm output.o &>errors.txt
rm output.s &>errors.txt
rm output &>errors.txt
done 
echo "====================================="
echo "testing strings"
suffix="_driver.c"
for filename in compiler_tests/strings/*_driver.c; do &>errors.txt
		CHECKED=$((${CHECKED}+1));
bin/c_compiler -S "${filename%_*}"".c" -o output.s &>errors.txt
mips-linux-gnu-gcc -mfp32 -o output.o -c output.s &>errors.txt
mips-linux-gnu-gcc -mfp32 -static -o output output.o "${filename%_*}""_driver.c" &>errors.txt
qemu-mips output &>errors.txt
#echo $?
if [[ $? == 0 ]]; then
	echo "Passed"
	PASSED=$((${PASSED}+1));
else echo "FAILED >>>>>>>>>>>>>>>>>>>>>>>" "$(basename -- $filename)" "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"
fi
rm output.o &>errors.txt
rm output.s &>errors.txt
rm output &>errors.txt
done 
echo "====================================="
echo "testing struct"
suffix="_driver.c"
for filename in compiler_tests/struct/*_driver.c; do &>errors.txt
		CHECKED=$((${CHECKED}+1));
bin/c_compiler -S "${filename%_*}"".c" -o output.s &>errors.txt
mips-linux-gnu-gcc -mfp32 -o output.o -c output.s &>errors.txt
mips-linux-gnu-gcc -mfp32 -static -o output output.o "${filename%_*}""_driver.c" &>errors.txt
qemu-mips output &>errors.txt
#echo $?
if [[ $? == 0 ]]; then
	echo "Passed"
	PASSED=$((${PASSED}+1));
else echo "FAILED >>>>>>>>>>>>>>>>>>>>>>>" "$(basename -- $filename)" "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"
fi
rm output.o &>errors.txt
rm output.s &>errors.txt
rm output &>errors.txt
done 
echo "====================================="
echo "testing types"
suffix="_driver.c"
for filename in compiler_tests/types/*_driver.c; do &>errors.txt
		CHECKED=$((${CHECKED}+1));
bin/c_compiler -S "${filename%_*}"".c" -o output.s &>errors.txt
mips-linux-gnu-gcc -mfp32 -o output.o -c output.s &>errors.txt
mips-linux-gnu-gcc -mfp32 -static -o output output.o "${filename%_*}""_driver.c" &>errors.txt
qemu-mips output &>errors.txt
#echo $?
if [[ $? == 0 ]]; then
	echo "Passed"
	PASSED=$((${PASSED}+1));
else echo "FAILED >>>>>>>>>>>>>>>>>>>>>>>" "$(basename -- $filename)" "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"
fi
rm output.o &>errors.txt
rm output.s &>errors.txt
rm output &>errors.txt
done 
echo "====================================="
echo "Passed ${PASSED} out of ${CHECKED} checks"
#done
echo "All done"

