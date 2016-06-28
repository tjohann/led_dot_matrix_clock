#
# makefile
#

MODULES = Documentation src driver bin

all:
	@echo "+-------------------------------------------+"
	@echo "|         Build all components              |"
	@echo "+-------------------------------------------+"
	(cd src && $(MAKE) $@)

install:
	(cd src && $(MAKE) $@)

uninstall:
	(cd src && $(MAKE) $@)

clean:
	rm -f *~ .*~
	for dir in $(MODULES); do (cd $$dir && $(MAKE) $@); done

.PHONY:
	all install uninstall clean


