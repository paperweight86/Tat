
cpp_files=""
for file in $(find ./ -type f -name '*.cpp')
do
	cpp_files="$cpp_files $file"
done

cpp_files="$cpp_files"| xargs

cpp_inc=""
for dir in ./*/
do
	cpp_inc="$cpp_inc -I$dir"
done

cpp_inc="$cpp_inc"| xargs

fixing_errors=""
#fixing_errors="-Wno-everything"

clang++ -c $fixing_errors -msse4.1 -std=c++1y -DLINUX -DTAT_LIB -m64 -g3 $cpp_files $cpp_inc -I./
ar -rcs tat.a *.o