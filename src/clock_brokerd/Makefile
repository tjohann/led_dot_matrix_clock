#
# BSD 3-Clause
# (c) 2015, thorsten.johannvorderbrueggen@t-online.de                        
#

PREFIX ?= $(HOME)
#PREFIX = /usr/local

TARGET := clock_broker
SRC    := $(TARGET).c 
HEADER := $(TARGET).h 
CONF_F := common.conf

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
	install $(TARGET) $(PREFIX)/bin
	install -m 644 $(CONF_F) $(PREFIX)/etc

run: $(TARGET)
	LD_LIBRARY_PATH=../../lib ./$(TARGET) -d $(PREFIX)/etc/

help: $(TARGET)
	LD_LIBRARY_PATH=../../lib ./$(TARGET) -h

usage: $(TARGET)
	LD_LIBRARY_PATH=../../lib ./$(TARGET)

.PHONY: clean
