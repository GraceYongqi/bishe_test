CC       = g++
CFLAGS   = -Wall -O -g
CXXFLAGS = 
INCLUDE  = -I /usr/local/boost/include 
TARGET   = extraction
LIBVAR   = -lboost_regex          
LIBPATH  = -L /usr/local/boost/lib 


OBJS     = main.o extraction.o
extraction.o:extraction.cpp extraction.h
	$(CC) $(CFLAGS) $(INCLUDE) -c extraction.cpp
main.o:main.cpp extraction.h
	$(CC) $(CFLAGS) $(INCLUDE) -c main.cpp

all:$(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(TARGET) $(OBJS) $(LIBPATH) $(LIBVAR)

clean:
	rm -f *.o
	rm -f $(TARGET)
