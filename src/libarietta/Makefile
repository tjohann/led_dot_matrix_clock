#
# BSD 3-Clause
# (c) 2015, thorsten.johannvorderbrueggen@t-online.de                        
#

PREFIX ?= $(HOME)
#PREFIX = /usr/local

TARGET := libarietta
SRC := $(TARGET).c daemon.c lcd.c network.c
HEADER := $(TARGET).h

#
# get version info
#
VERSION = $(shell cat VERSION)
VER_MAYOR:=$(word 1, $(subst ., ,$(VERSION)))
VER_MINOR:=$(word 2, $(subst ., ,$(VERSION)))
VER_BUGFIX:=$(word 3, $(subst ., ,$(VERSION)))

#
# create VERSION define
#
VERSION_DEFINES = -DVER_MAYOR=$(VER_MAYOR) -DVER_MINOR=$(VER_MINOR) -DVER_BUGFIX=$(VER_BUGFIX)

#
# CLFAGS and LDLIBS
#
CFLAGS = -Wall -O2 -fPIC -g 
LDLIBS = -shared -Wl,-soname,$(TARGET).so.$(VER_MAYOR) -pthread  


all: $(TARGET).so.$(VERSION) $(TARGET).a

$(TARGET).so.$(VERSION): $(SRC) $(HEADER)
	${CC} $(CFLAGS) $(VERSION_DEFINES) -c $(SRC)
	${CC} $(CFLAGS) $(VERSION_DEFINES) $(LDLIBS) -o $(TARGET).so.$(VERSION) $(SRC)

$(TARGET).a: $(SRC) $(HEADER)
	${AR} rcs $(TARGET).a $(SRC)

clean:
	rm -f *~ .*~ *.o *.i *.s *.so *.so.* *.a
	rm -f ${TARGET}.so.*
	rm -f man/*~ 

install: $(TARGET).so.$(VERSION) $(TARGET).a
	install $(TARGET).a $(PREFIX)/lib/
	install $(TARGET).so.$(VERSION) $(PREFIX)/lib/
	ln -sf $(PREFIX)/lib/$(TARGET).so.$(VERSION)  $(PREFIX)/lib/$(TARGET).so.$(VER_MAYOR)
	ln -sf $(PREFIX)/lib/$(TARGET).so.$(VER_MAYOR) $(PREFIX)/lib/$(TARGET).so.$(VER_MAYOR).$(VER_MINOR)
	install $(HEADER) $(PREFIX)/include/


.PHONY: clean
