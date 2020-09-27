
#######################################################################
# Template of for compiling erlang files                              #
#######################################################################
# code to compile
SOURCE = mblas.erl 
NIF_SOURCE = mblas.c
TESTS = mblas_tests.erl

#Where include files are stored ".hrl"
EFLAGS = -I../include 

#Compiles the code into a ebin dir. relative to the source dir. 
EBIN = ebin
SRC = src
TARGETS = $(SOURCE:%.erl=$(EBIN)/%.beam)  $(NIF_SOURCE:%.c=$(EBIN)/%_nif.so) $(TESTS:%.erl=$(EBIN)/%.beam)


$(EBIN)/%.beam: $(SRC)/%.erl
	$(ERLHOME)/bin/erlc  -W -b beam -o $(EBIN) $(EFLAGS) $(WAIT) $<

$(EBIN)/%_nif.so: $(SRC)/%.c
	gcc -fpic -shared  -o $@ $< 

 
all: $(TARGETS)

test: $(EBIN)/mblas_tests.beam
	cd ebin;\
	erl -s mblas_tests test -eval 'init:stop()';\
	cd ..;\
   
clean:
	\rm -f $(TARGETS)


realclean: clean
	\rm -f \.* *~ *\% #*  *.beam *.so

.PHONY: test