OBJS=\
	main.o\
	StrUtils.o\
	ReadFile.o

CFLGS=-c -mconsole -O2 -I D:\progs\png\include

LIBS=D:\progs\png\lib\libmypng.a

day16.exe : $(OBJS) $(INCS)
	g++ -o day16.exe -mconsole $(OBJS) $(LIBS) -lpng

main.o : main.cpp $(INCS)
	g++ $(CFLGS) main.cpp

ReadFile.o : ReadFile.cpp $(INCS)
	g++ $(CFLGS) ReadFile.cpp

StrUtils.o : StrUtils.cpp $(INCS)
	g++ $(CFLGS) StrUtils.cpp

clean :
	rm *.o
