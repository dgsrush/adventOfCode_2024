OBJS=\
	main.o\
	StrUtils.o\
	ReadFile.o

CFLGS=-c -mconsole -O2

day12.exe : $(OBJS) $(INCS)
	g++ -o day12.exe -mconsole $(OBJS) $(LIBS)

main.o : main.cpp $(INCS)
	g++ $(CFLGS) main.cpp

ReadFile.o : ReadFile.cpp $(INCS)
	g++ $(CFLGS) ReadFile.cpp

StrUtils.o : StrUtils.cpp $(INCS)
	g++ $(CFLGS) StrUtils.cpp

clean :
	rm *.o
