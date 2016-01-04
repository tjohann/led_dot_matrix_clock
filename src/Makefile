#
# BSD 3-Clause
# (c) 2015, thorsten.johannvorderbrueggen@t-online.de                        
#

PREFIX ?= $(HOME)
#PREFIX = /usr/local

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
# CLFAGS and LDLIBS for libarietta
#
LIB_CFLAGS = -Wall -O2 -fPIC -g 
LIB_LDLIBS = -shared -Wl,-soname,$(LIB).so.$(VER_MAYOR) -pthread  

#
# CLFAGS and LDLIBS for all progs
#
CFLAGS := `pkg-config --cflags libconfig` -Wall -O2 -g -DDEBUG  -I.
LDLIBS := `pkg-config --libs libconfig` -L. -l:libarietta.so.$(VERSION) -lpthread 


#
# ------ libarietta
#
LIB        := libarietta
LIB_SRC    := $(LIB).c daemon.c lcd.c network.c
LIB_HEADER := $(LIB).h

#
# ------ clock_brokerd
#
CLOCK_BROKERD        := clock_brokerd
CLOCK_BROKERD_SRC    := $(CLOCK_BROKERD).c 
CLOCK_BROKERD_HEADER := $(CLOCK_BROKERD).h 
COMMON_CONF          := common.conf

#
# ------ tempd
#
TEMPD        := tempd
TEMPD_SRC    := $(TEMPD).c 
TEMPD_HEADER := $(TEMPD).h 


# ------ ...
all: $(LIB).so.$(VERSION) $(CLOCK_BROKERD) $(TEMPD)


# ------ libarietta
$(LIB).so.$(VERSION): $(LIB_SRC) $(LIB_HEADER)
	@echo "+-------------------------------------------+"
	@echo "|         Build $(LIB).so.$(VERSION)         |"
	@echo "+-------------------------------------------+"	
	${CC} $(LIB_CFLAGS) $(VERSION_DEFINES) -c $(LIB_SRC)
	${CC} $(LIB_CFLAGS) $(VERSION_DEFINES) $(LIB_LDLIBS) -o $(LIB).so.$(VERSION) $(LIB_SRC)


# ------ clock_broker
$(CLOCK_BROKERD): $(CLOCK_BROKERD_SRC) $(CLOCK_BROKERD_HEADER)
	@echo "+-------------------------------------------+"
	@echo "|         Build $(CLOCK_BROKERD)                |"
	@echo "+-------------------------------------------+"	
	${CC} $(CFLAGS) -o $(CLOCK_BROKERD) $(CLOCK_BROKERD_SRC) $(LDLIBS) 

$(CLOCK_BROKERD)_run: $($(CLOCK_BROKERD))
	LD_LIBRARY_PATH=$(PREFIX)/lib $(PREFIX)/bin/$(CLOCK_BROKERD) -d $(PREFIX)/etc/

$(CLOCK_BROKERD)_help: $($(CLOCK_BROKERD))
	LD_LIBRARY_PATH=$(PREFIX)/lib $(PREFIX)/bin/$(CLOCK_BROKERD) -h

$(CLOCK_BROKERD)_usage: $($(CLOCK_BROKERD))
	LD_LIBRARY_PATH=$(PREFIX)/lib $(PREFIX)/bin/$(CLOCK_BROKERD)


# ------ tempd
$(TEMPD): $(TEMPD_SRC) $(TEMPD_HEADER)
	@echo "+-------------------------------------------+"
	@echo "|         Build $(TEMPD)                       |"
	@echo "+-------------------------------------------+"	
	${CC} $(CFLAGS) -o $(TEMPD) $(TEMPD_SRC) $(LDLIBS) 

$(TEMPD)_run: $($(TEMPD))
	LD_LIBRARY_PATH=$(PREFIX)/lib $(PREFIX)/bin/$(TEMPD) -d $(PREFIX)/etc/

$(TEMPD)_help: $($(TEMPD))
	LD_LIBRARY_PATH=$(PREFIX)/lib $(PREFIX)/bin/$(TEMPD) -h

$(TEMPD)_usage: $($(TEMPD))
	LD_LIBRARY_PATH=$(PREFIX)/lib $(PREFIX)/bin/$(TEMPD)


# ------ common parts
clean:
	rm -f *~ .*~ *.o *.i *.s *.so *.so.* *.a
	rm -f man/*~ 
	rm -f $(LIB).so.*
	rm -f $(CLOCK_BROKERD)
	rm -f $(TEMPD)

install: all
	install $(LIB).so.$(VERSION) $(PREFIX)/lib/
	ln -sf $(PREFIX)/lib/$(LIB).so.$(VERSION)  $(PREFIX)/lib/$(LIB).so.$(VER_MAYOR)
	ln -sf $(PREFIX)/lib/$(LIB).so.$(VER_MAYOR) $(PREFIX)/lib/$(LIB).so.$(VER_MAYOR).$(VER_MINOR)
	install $(LIB_HEADER) $(PREFIX)/include/

	install $(CLOCK_BROKERD) $(PREFIX)/bin
	install -m 644 $(COMMON_CONF) $(PREFIX)/etc

	install $(TEMPD) $(PREFIX)/bin
	install -m 644 $(TEMPD).conf $(PREFIX)/etc

uninstall:
	rm -f $(PREFIX)/lib/$(LIB).so.$(VER_MAYOR).$(VER_MINOR)
	rm -f $(PREFIX)/lib/$(LIB).so.$(VER_MAYOR)
	rm -f $(PREFIX)/lib/$(LIB).so.$(VERSION)
	rm -f $(PREFIX)/include/$(LIB_HEADER)

	rm -f $(PREFIX)/bin/$(CLOCK_BROKERD)
	rm -f $(PREFIX)/etc/$(COMMON_CONF)

	rm -f $(PREFIX)/bin/$(TEMPD)
	rm -f $(PREFIX)/etc/$(TEMPD).conf

.PHONY: clean uninstall

