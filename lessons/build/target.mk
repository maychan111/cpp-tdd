#####################################################################
# usually common macros, can be overrided by project.mk
#####################################################################
GCC = g++

INCLUDEDIR += 
GCC_DEFINES += 
GCC_FLAGS += -std=c++1y -flto -c $(shell pwd)/"$<" -Wall -Werror -fPIC -o "$@" -MMD -MF"$(@:%.o=%.d)" $(GCC_DEFINES) $(MOREFLAGS)
LINK_FLAGS += -static-libstdc++ -flto $(MOREFLAGS)

#######################################################
# standard includes
#######################################################
-include project.mk
-include objects.mk
-include exclude.mk

#######################################################
# target directories
#######################################################
TARGETCONFIG = $(shell echo $(CONFIG) | tr A-Z a-z)
BINDIR = $(ROOTDIR)/bin/$(CONFIG)
TEMPDIR = $(BINDIR)/objs/$(PROJECTDIR)
TARGETPATH = $(BINDIR)/$(TARGET)

#######################################################
# transform
#######################################################
OBJS := $(addprefix $(TEMPDIR)/, $(OBJS))
DEPS := $(addprefix $(TEMPDIR)/, $(DEPS))
LIBFILES = $(foreach L,$(BUILDLIBS),lib$La)
LIBPATHS := $(addprefix $(BINDIR)/, $(LIBFILES))
$(shell mkdir -p $(TEMPDIR))

#######################################################
# targets
#######################################################
all: print-message $(TARGETPATH)

print-message:
	-@echo 'Building $(TARGETPATH)'

$(TARGETPATH): $(OBJS) $(LIBPATHS)
ifeq ($(suffix $(TARGETPATH)),.a)
	@gcc-ar -r $(TARGETPATH) $(OBJS)	
else
ifeq ($(suffix $(TARGETPATH)),.so)
	@$(GCC) -shared -o $(TARGETPATH) -L$(BINDIR) $(LINK_FLAGS) $(OBJS) $(LIBS) $(MORELIBS)
else
	@$(GCC) -o $(TARGETPATH) -L$(BINDIR) $(LINK_FLAGS) $(OBJS) $(LIBS) $(MORELIBS)
endif
ifneq ($(CONFIG),Debug)
	@strip $(TARGETPATH)
endif
endif
ifneq ($(POST_BUILD),)
	$(POST_BUILD)
endif
	-@echo 'Built $@'

clean:
	-rm -rf $(TARGETPATH) $(TEMPDIR)

#######################################################
# rules
#######################################################

-include $(DEPS)

$(TEMPDIR)/%.o: %.cpp
	-@echo 'Compiling $<'
	@$(GCC) $(GCC_FLAGS) $(INCLUDEDIR) 

ifneq ($(LIBPATHS),)
$(LIBPATHS): buildlibs

buildlibs:
	@for i in $(LIBDEP); do $(MAKE) -C $$i $(TARGETCONFIG) || exit 1; done
endif

.PHONY: all clean debug release coverage buildlibs print-message
.SECONDARY: $(DEPS)
