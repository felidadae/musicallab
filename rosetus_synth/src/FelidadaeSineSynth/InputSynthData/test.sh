clear;clear;clear;clear;
[[ -e a.out ]] && rm a.out;
g++ -std=c++11 test__InputDataReader.cpp; 
./a.out; 
rm a.out;
