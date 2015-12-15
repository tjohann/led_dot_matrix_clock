#
# BSD 3-Clause
# (c) 2015, thorsten.johannvorderbrueggen@t-online.de                        
#


TARGET := libarietta
SRC := libarietta.c daemon.c lcd.c network.c

#
# get version info
#
VERSION = $(shell cat VERSION)
VER_MAYOR:=$(word 1, $(subst ., ,$(VERSION)))
VER_MINOR:=$(word 2, $(subst ., ,$(VERSION)))
VER_BUGFIX:=$(word 3, $(subst ., ,$(VERSION)))

#
# CLFAGS and LDLIBS
#
CFLAGS = -Wall -O2 -fPIC -g 
LDLIBS = -shared -Wl,-soname,$(TARGET).so.$(VER_MAYOR) -lpthread -lc


all: $(TARGET).so.$(VERSION) $(TARGET).a

$(TARGET).so.$(VERSION): $(SRC)
	${CC} $(CFLAGS) -DVERSION=\"$(VERSION)\" -c $(SRC)
	${CC} $(CFLAGS) $(LDLIBS) -o $(TARGET).so.$(VERSION) $(SRC)
	ln -s $(TARGET).so.$(VERSION) $(TARGET).so.$(VER_MAYOR)
	ln -s $(TARGET).so.$(VER_MAYOR)	$(TARGET).so.$(VER_MAYOR).$(VER_MINOR)

$(TARGET).a:  $(SRC)
	${AR} rcs $(TARGET).a $(SRC)

clean:
	rm -f *~ .*~ *.o *.i *.s *.so *.so.* *.a
	rm -f ${TARGET}.so.*
	rm -f man/*~ 
