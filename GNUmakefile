
ifneq ($(shell uname -s),Linux)
ifeq (${HOSTNAME},PC-Denis)
CMAKE='/c/Program Files/CMake/bin/cmake.exe'
#MSBUILD='C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\amd64\MSBuild.exe'
endif

EXEXT=.exe
ECHO=echo -e
else
ECHO=echo
endif

CPPFLAGS += -I .
CXXFLAGS += -std=c++23 -Wall -Wextra -pedantic
LDFLAGS += -L .
LDLIBS += -ledit_cpp
PREFIX=edit_cpp
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
OBJS_TARGET=${PREFIX}.o
OBJS_LIB=$(filter-out ${OBJS_TARGET},${OBJS})
TARGET=${PREFIX}${EXEXT}
STRIP=strip
UPX=upx

all: libedit_cpp.a ${TARGET}

ifeq ($(MSBUILD),)
${TARGET} : ${OBJS_TARGET}

libedit_cpp.a : ${OBJS_LIB}
	ar r $@  $?	

else
${TARGET} : ${SRCS}
	${MSBUILD} ${PREFIX}.sln -p:Configuration=Release
	cp x64/Release/${TARGET} .
endif

strip : $(TARGET)
	@file ${TARGET} | grep stripped >/dev/null || ( $(STRIP) $(TARGET) && echo "Strip OK" )

upx : $(TARGET)
	$(STRIP) $(TARGET) 2>/dev/null || true
	$(UPX) -q $(TARGET) 2>/dev/null || true

cfg :
	@type ${CXX} ${CXX} ${LD} ${GDB} ${STRIP} ${UPX}
	@${ECHO} "CPPFLAGS=${CPPFLAGS}"
	@${ECHO} "CXXFLAGS=${CXXFLAGS}"
	@${ECHO} "LDFLAGS=${LDFLAGS}"
	@${ECHO} "LDLIBS=${LDLIBS}"
	@${ECHO} "SRCS=${SRCS}"
	@${ECHO} "OBJS=${OBJS}"
	@${ECHO} "TARGET=${TARGET}"

clean :
	rm -rf ${OBJS} *.d ${TARGET} libedit_cpp.a x64

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

