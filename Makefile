FIDES_ROOT_DIR:=.

include common.mk

INSTALL_TOP:=/usr/local
INSTALL_INC:=$(INSTALL_TOP)/include/$(FIDES)
INSTALL_LIB:=$(INSTALL_TOP)/lib

.PHONY: all, static, shared, samples, exception_install, exception_uninstall, install_static, install_shared, install, uninstall, clean, compile_flags, clean_compile_flags

# Any of the following make rules can be executed with the `-j` option (`make -j`) for parallel compilation 

all:
	cd $(FIDES_LIB_DIR) && $(MAKE) $@

static:
	cd $(FIDES_LIB_DIR) && $(MAKE) $@

shared:
	cd $(FIDES_LIB_DIR) && $(MAKE) $@

samples: static
	cd $(FIDES_BIN_DIR) && $(MAKE) all

exception_install:
	cd $(FIDES_DEPENDENCIES_DIR)/exception && $(MAKE) install

exception_uninstall:
	cd $(FIDES_DEPENDENCIES_DIR)/exception && $(MAKE) uninstall

install_static: exception_install
	mkdir -p $(INSTALL_INC) $(INSTALL_LIB)
	install -p -m 0644 $(FIDES_LIB_DIR)/*.hpp $(INSTALL_INC)
	install -p -m 0644 $(FIDES_LIB_DIR)/$(FIDES_STATIC_LIB) $(INSTALL_LIB)

install_shared: exception_install
	mkdir -p $(INSTALL_INC) $(INSTALL_LIB)
	install -p -m 0644 $(FIDES_LIB_DIR)/*.hpp $(INSTALL_INC)
	install -p -m 0644 $(FIDES_LIB_DIR)/$(FIDES_SHARED_LIB) $(INSTALL_LIB)

install: exception_install
	mkdir -p $(INSTALL_INC) $(INSTALL_LIB)
	install -p -m 0644 $(FIDES_LIB_DIR)/*.hpp $(INSTALL_INC)
	install -p -m 0644 $(FIDES_LIB_DIR)/$(FIDES_STATIC_LIB) $(FIDES_LIB_DIR)/$(FIDES_SHARED_LIB) $(INSTALL_LIB)

uninstall: exception_uninstall
	$(RM) -R $(INSTALL_INC)
	$(RM) $(INSTALL_LIB)/$(FIDES_STATIC_LIB) $(INSTALL_LIB)/$(FIDES_SHARED_LIB)

clean:
	cd $(FIDES_LIB_DIR) && $(MAKE) $@
	cd $(FIDES_BIN_DIR) && $(MAKE) $@

compile_flags:
	cd $(FIDES_LIB_DIR) && $(MAKE) $@
	cd $(FIDES_BIN_DIR) && $(MAKE) $@

clean_compile_flags:
	cd $(FIDES_LIB_DIR) && $(MAKE) $@
	cd $(FIDES_BIN_DIR) && $(MAKE) $@
