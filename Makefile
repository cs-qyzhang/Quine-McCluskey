#变量声明
objects = main.o \
	  	  item.o \
#######################################
Quine-McCluskey.exe : $(objects)
	g++ -g -o Quine-McCluskey $(objects)

main.o : main.cpp item.h
	g++ -g -c main.cpp

item.o : item.h item.cpp
	g++ -g -c item.cpp
########################################
.PHONY : clean
clean  :
	rm Quine-McCluskey $(objects)