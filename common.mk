FIDES:=fides

FIDES_LIB_ROOT_DIR:=lib
FIDES_LIB_DIR:=$(FIDES_LIB_ROOT_DIR)/$(FIDES)
FIDES_BIN_DIR:=sample
FIDES_DEPENDENCIES_DIR:=dependencies
FIDES_STATIC_LIB:=lib$(FIDES).a

# FIDES_ROOT_DIR is defined later. That's why = is used instead of :=
FIDES_EXCEPTION_INCLUDE_DIR=$(FIDES_ROOT_DIR)/$(FIDES_DEPENDENCIES_DIR)/exception/include
FIDES_STATIC_LIB_INCLUDE_DIR=$(FIDES_ROOT_DIR)/$(FIDES_LIB_ROOT_DIR)
FIDES_STATIC_LIB_LDLIB=$(FIDES_ROOT_DIR)/$(FIDES_LIB_DIR)/$(FIDES_STATIC_LIB)

# extra flags may be added here or in make invocation. E.g: make EXTRA_CXXFLAGS=-g
EXTRA_CXXFLAGS:=
EXTRA_LDFLAGS:=

ifeq ($(OPTIMIZED), y)
OPTIMIZATION_FLAGS:=-O3 -march=native -flto
else ifeq ($(or $(OPTIMIZED), n), n)
OPTIMIZATION_FLAGS:=-O0 -g
else
$(error Invalid parameter value)
endif

ifeq ($(SANITIZED), y)
ifneq ($(OPTIMIZED), y)
SANITIZE_FLAGS:=-fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined
else
$(error Cannot have SANITIZED=y and OPTIMIZED=y)
endif
else ifneq ($(or $(SANITIZED), n), n)
$(error Invalid parameter value)
endif

ifeq ($(WITH_FPIC), n)
FPIC_FLAG:=
else ifeq ($(or $(WITH_FPIC), y), y)
FPIC_FLAG:=-fPIC
else
$(error Invalid parameter value)
endif

ifeq ($(shell uname -s), Darwin)
SHARED_LIB_EXTENSION:=dylib
else
SHARED_LIB_EXTENSION:=so
endif

FIDES_SHARED_LIB:=lib$(FIDES).$(SHARED_LIB_EXTENSION)

FIDES_CXXFLAGS:=$(EXTRA_CXXFLAGS) -std=c++2b -Werror -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic $(OPTIMIZATION_FLAGS) $(SANITIZE_FLAGS) $(FPIC_FLAG) $(PTHREAD_FLAG)

FIDES_COMMON_LDFLAGS:=$(EXTRA_LDFLAGS) $(OPTIMIZATION_FLAGS) $(SANITIZE_FLAGS) $(PTHREAD_FLAG)
FIDES_SHARED_LDFLAGS:=$(FIDES_COMMON_LDFLAGS) -shared
FIDES_EXECUTABLE_LDFLAGS:=$(FIDES_COMMON_LDFLAGS)

FIDES_SYSTEM_INCLUDE_DIRS:=$(FIDES_EXCEPTION_INCLUDE_DIR) /usr/local/opt/openssl/include /usr/local/include
FIDES_LIB_DIRS:=/usr/local/opt/openssl/lib /usr/local/lib
FIDES_LDLIBS:=-lssl -lcrypto
