#
# makefile
#

ifeq "${ARMEL_HOME}" ""
    $(error error: please source armel_env first!)
endif

MODULES = Documentation src include lib etc bin

all:
	@echo "+-------------------------------------------+"
	@echo "|         Build all components              |"
	@echo "+-------------------------------------------+"	
	(cd src && $(MAKE) $@)

install:
	(cd src && $(MAKE) $@)

clean:
	rm -f *~ .*~
	for dir in $(MODULES); do (cd $$dir && $(MAKE) $@); done

.PHONY:
	all install clean


