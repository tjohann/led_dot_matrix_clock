#
# BSD 3-Clause
# (c) 2015, thorsten.johannvorderbrueggen@t-online.de                        
#


TARGET := tempd
SRC := tempd.c 
HEADER := tempd.h 


#
# CLFAGS and LDLIBS
#
CFLAGS := -Wall -O2 -g -I../../include
LDLIBS := -L../../lib -larietta -lpthread -lrt


all: $(TARGET)

$(TARGET): $(SRC) $(HEADER)
	${CC} $(CFLAGS) -o $(TARGET) $(SRC) $(LDLIBS) 

clean:
	rm -f *~ .*~ *.o *.i *.s *.so *.so.* *.a
	rm -f ${TARGET}
	rm -f man/*~ 

install: $(TARGET)
	cp -d $(TARGET) ../../bin

run: $(TARGET)
	LD_LIBRARY_PATH=../../lib ./tempd

.PHONY: clean
