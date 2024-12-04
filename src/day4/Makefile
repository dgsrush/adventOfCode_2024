OBJS=\
	main.o\
	StrUtils.o\
	ReadFile.o

CFLGS=-c -mconsole -O2

LIBS=

day4.exe : $(OBJS) $(INCS)
	g++ -o day4.exe -mconsole $(OBJS) $(LIBS)

main.o : main.cpp $(INCS)
	g++ $(CFLGS) main.cpp

ReadFile.o : ReadFile.cpp $(INCS)
	g++ $(CFLGS) ReadFile.cpp

StrUtils.o : StrUtils.cpp $(INCS)
	g++ $(CFLGS) StrUtils.cpp

clean :
	rm *.o
