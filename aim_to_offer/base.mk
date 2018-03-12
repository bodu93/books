CC := clang++
CXXFLAGS := -std=c++11 -g -Wall
INCLUDES := -I ../include
define COMPILECOMMAND
	$(CC) $(CXXFLAGS) $^ -o $@ $(INCLUDES)
endef

DEBUGFOLDERS := $(patsubst %, %.dSYM, $(TARGETS))
all : $(TARGETS)
clean :
	-rm -rf $(TARGETS) $(DEBUGFOLDERS)

.PHONY : all clean
vpath %.cc ../lib
vpath %.h  ../include
vpath %    .
