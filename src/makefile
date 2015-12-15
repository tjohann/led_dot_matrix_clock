#
# BSD 3-Clause
# (c) 2015, thorsten.johannvorderbrueggen@t-online.de                        
#


#
# the build order is important
#
#MODULES = $(shell ls -d */ | cut -f1 -d'/')
MODULES = libarietta


.PHONY: all
all:
	@echo "+-------------------------------------------------+"
	@echo "|              build all in ./src                 |"
	@echo "+-------------------------------------------------+"
	for dir in $(MODULES); do (cd $$dir && $(MAKE) $@); done

.PHONY: clean
clean:
	rm -f *~
	for dir in $(MODULES); do (cd $$dir && $(MAKE) $@); done

distclean: clean
