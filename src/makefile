#
# build all libs/daemon
#

LIBS = 
DAEMONS = 

all:: 
	for dir in $(LIBS); do (cd $$dir && $(MAKE) $@); done
	for dir in $(DAEMONS); do (cd $$dir && $(MAKE) $@); done

clean::
	rm -f *~ .*~
	for dir in $(LIBS); do (cd $$dir && $(MAKE) $@); done
	for dir in $(DAEMONS); do (cd $$dir && $(MAKE) $@); done	

distclean: clean
