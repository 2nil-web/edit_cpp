
ifneq ($(shell uname -s),Linux)
EXEXT=.exe
ECHO=echo -e
else
ECHO=echo
endif

CPPFLAGS += -I .
CXXFLAGS += -std=c++23 -Wall -Wextra -pedantic
PREFIX=testwined
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
TARGET=${PREFIX}${EXEXT}

all: ${TARGET}

${TARGET} : ${OBJS}

clean :
	rm -f ${OBJS} *.d *.exe

ifneq ($(MAKECMDGOALS),clean)
%.exe: %.o
	$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

%.exe: %.cpp
	$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

#	@${ECHO} "Building "$@" from "$<
%.d: %.cpp
	@${ECHO} Checking header dependencies from $<
	@$(COMPILE.cpp) -isystem /usr/include -MM -MG $< > $@
# Inclusion des fichiers de dépendance .d
ifdef OBJS
-include $(OBJS:.o=.d)
endif
endif

