CC       = g++
CFLAGS   = -Wall -O -g
CXXFLAGS = 
INCLUDE  = -I /usr/local/boost/include 
TARGET   = extraction
LIBVAR   = -lboost_regex          
LIBPATH  = -L /usr/local/boost/lib 

OBJS     = main.o noise_remove.o extraction.o parse.o caculation.o

all:$(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(TARGET) $(OBJS) $(LIBPATH) $(LIBVAR)

main.o:main.cpp noise_remove.h
	$(CC) $(CFLAGS) $(INCLUDE) -c main.cpp

noise_remove.o:noise_remove.cpp noise_remove.h
    $(CC) $(CFLAGS) $(INCLUDE) -c noise_remove.cpp

extraction.o:extraction.cpp extraction.h
	$(CC) $(CFLAGS) $(INCLUDE) -c extraction.cpp

parse.o:parse.cpp parse.h
	$(CC) $(CFLAGS) $(INCLUDE) -c parse.cpp

caculation.o:caculation.cpp caculation.h
	$(CC) $(CFLAGS) $(INCLUDE) -c caculation.cpp

clean:
	rm -f *.o
	rm -f $(TARGET)
