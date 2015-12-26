#
# BSD 3-Clause
# (c) 2015, thorsten.johannvorderbrueggen@t-online.de                        
#


TARGET := clock_broker
SRC := clock_broker.c 
HEADER := clock_broker.h 


#
# CLFAGS and LDLIBS
#
CFLAGS := -Wall -O2 -g -DDEBUG -I../../include `pkg-config --cflags --libs libconfig`
LDLIBS := -L../../lib -larietta -lpthread -lrt


all: $(TARGET)

$(TARGET): $(SRC) $(HEADER)
	${CC} $(CFLAGS) -o $(TARGET) $(SRC) $(LDLIBS) 

clean:
	rm -f *~ .*~ *.o *.i *.s *.so *.so.* *.a
	rm -f ${TARGET}
	rm -f man/*~
	rm -f etc/*~

install: $(TARGET)
	cp -d $(TARGET) ../../bin

run: $(TARGET)
	LD_LIBRARY_PATH=../../lib ./clock_broker -d ~/led_dot_matrix_clock/src/clock_broker/etc/

help: $(TARGET)
	LD_LIBRARY_PATH=../../lib ./clock_broker -h

usage: $(TARGET)
	LD_LIBRARY_PATH=../../lib ./clock_broker

.PHONY: clean
