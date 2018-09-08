#####################################################################
# project specific
#####################################################################
PROJECTDIR = Lesson5
TARGET = Lesson5

BUILDLIBS = gtest

LIBDEP = \
../gtest \

LIBS = $(foreach L,$(BUILDLIBS),-l$L) -lrt -pthread
