BUILDDIR = $(ROOTDIR)/build

all: release debug

mmake: 
	@$(ROOTDIR)/build/mmake
    
release: mmake	
	@$(MAKE) --no-print-directory -f $(BUILDDIR)/target.mk all ROOTDIR=$(ROOTDIR) CONFIG=Release \
	MOREFLAGS="-O3"

debug: mmake
	@$(MAKE) --no-print-directory -f $(BUILDDIR)/target.mk all ROOTDIR=$(ROOTDIR) CONFIG=Debug \
	MOREFLAGS="-D_DEBUG -g -O0"

coverage: mmake
	@$(MAKE) --no-print-directory -f $(BUILDDIR)/target.mk all ROOTDIR=$(ROOTDIR) CONFIG=Coverage \
	MOREFLAGS="-O3 -ftest-coverage -fprofile-arcs" \
	MORELIBS="-lgcov"

clean: release-clean debug-clean coverage-clean

release-clean:
	@$(MAKE) --no-print-directory -f $(BUILDDIR)/target.mk clean ROOTDIR=$(ROOTDIR) CONFIG=Release 

debug-clean:
	@$(MAKE) --no-print-directory -f $(BUILDDIR)/target.mk clean ROOTDIR=$(ROOTDIR) CONFIG=Debug 

coverage-clean: 
	@$(MAKE) --no-print-directory -f $(BUILDDIR)/target.mk clean ROOTDIR=$(ROOTDIR) CONFIG=Coverage 

.PHONY: all clean mmake release debug coverage release-clean debug-clean coverage-clean 
