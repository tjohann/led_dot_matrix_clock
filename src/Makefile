#
# BSD 3-Clause
# (c) 2015, thorsten.johannvorderbrueggen@t-online.de                        
#


#
# the build order is important
#
#MODULES = $(shell ls -d */ | cut -f1 -d'/')
MODULES = libarietta tempd


all:
	@echo "+-------------------------------------------------+"
	@echo "|              build all in ./src                 |"
	@echo "+-------------------------------------------------+"
	for dir in $(MODULES); do (cd $$dir && $(MAKE) $@); done

clean:
	rm -f *~ .*~
	for dir in $(MODULES); do (cd $$dir && $(MAKE) $@); done


install:
	for dir in $(MODULES); do (cd $$dir && $(MAKE) $@); done


distclean: clean

.PHONY:
	clean all install
