RM =rm
CP =cp
CC =g++
CLR=/usr/bin/clear

IDIR =./include
CXXFLAGS =-std=c++11 -Wall -O3 -I$(IDIR)
LINK = $(CXX) $(CXXFLAGS)
COMPILE = $(CXX) $(LIBS) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -c

TERMITE = termite

INSTALLDIR = /usr/local/bin

.PHONY : clearscr fresh clean all

all: $(TERMITE)

install:
	@echo \#\#\# Installing binaries to $(INSTALLDIR)/...
	$(CP) $(TERMITE) $(INSTALLDIR)/
	
uninstall:
	@echo \#\#\# Uninstalling binaries from $(INSTALLDIR)/...
	$(RM) -r $(INSTALLDIR)/$(TERMITE)


# link
$(TERMITE): termite.o tools.o terminus.o gene.o 
	$(LINK) termite.o tools.o terminus.o gene.o -o termite

# compile different units
tools.o: ./src/tools.cpp
	$(COMPILE) -o tools.o ./src/tools.cpp
terminus.o: ./src/terminus.cpp
	$(COMPILE) -o terminus.o ./src/terminus.cpp
gene.o: ./src/gene.cpp
	$(COMPILE) -o gene.o ./src/gene.cpp
termite.o: ./src/main.cpp
	$(COMPILE) -o termite.o ./src/main.cpp


clean:
	rm -f *.o

fresh : clean clearscr all

clearscr: 
	$(CLR)

