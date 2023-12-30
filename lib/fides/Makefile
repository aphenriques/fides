FIDES_ROOT_DIR:=../..

include $(FIDES_ROOT_DIR)/common.mk

SRC_DIRS:=. $(wildcard */.)
FILTER_OUT:=
INCLUDE_DIRS:=
SYSTEM_INCLUDE_DIRS:=$(FIDES_SYSTEM_INCLUDE_DIRS)
LIB_DIRS:=$(FIDES_LIB_DIRS)
LDLIBS:=$(FIDES_LDLIBS)

# '-isystem <dir>' supress warnings from included headers in <dir>. These headers are also excluded from dependency generation
CXXFLAGS:=$(FIDES_CXXFLAGS) $(addprefix -I, $(INCLUDE_DIRS)) $(addprefix -isystem , $(SYSTEM_INCLUDE_DIRS))
LDFLAGS:=$(FIDES_SHARED_LDFLAGS) $(addprefix -L, $(LIB_DIRS))
ARFLAGS:=rcs

################################################################################

STATIC_LIB:=$(FIDES_STATIC_LIB)
SHARED_LIB:=$(FIDES_SHARED_LIB)

SRC_DIRS:=$(subst /.,,$(SRC_DIRS))
SRCS:=$(filter-out $(FILTER_OUT), $(wildcard $(addsuffix /*.cpp, $(SRC_DIRS))))
OBJS:=$(addsuffix .o, $(basename $(SRCS)))
DEPS:=$(addsuffix .d, $(basename $(SRCS)))

.PHONY: all static shared clean compile_flags clean_compile_flags

all: static shared

static: $(STATIC_LIB)

shared: $(SHARED_LIB)

$(STATIC_LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

$(SHARED_LIB): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(addsuffix /*.d, $(SRC_DIRS)) $(addsuffix /*.o, $(SRC_DIRS)) $(STATIC_LIB) $(SHARED_LIB)
#	rm -f $(DEPS) $(OBJS) $(STATIC_LIB) $(SHARED_LIB)

%.d: %.cpp
	$(CXX) $(CXXFLAGS) -MP -MM -MF $@ -MT '$@ $(addsuffix .o, $(basename $<))' $<

# for clangd
compile_flags:
	echo $(CXXFLAGS) | tr ' ' '\n' > compile_flags.txt

clean_compile_flags:
	rm -f compile_flags.txt

ifeq (, $(filter $(MAKECMDGOALS), clean compile_flags clean_compile_flags))
-include $(DEPS)
endif
