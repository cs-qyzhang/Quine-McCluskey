#变量声明
objects = main.o \
	  item.o \
	  function.o
#######################################
Quine-McCluskey.exe : $(objects)
	g++ -g -o Quine-McCluskey.exe $(objects)

main.o : main.cpp item.h
	g++ -g -c main.cpp

item.o : item.h item.cpp
	g++ -g -c item.cpp

function.o : function.cpp
	g++ -g -c function.cpp
########################################
.PHONY : clean
clean  :
	rm Quine-McCluskey.exe $(objects)