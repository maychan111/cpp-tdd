#####################################################################
# project specific
#####################################################################
PROJECTDIR = Lesson2
TARGET = Lesson2

BUILDLIBS = gtest

LIBDEP = \
../gtest \

LIBS = $(foreach L,$(BUILDLIBS),-l$L) -lrt -pthread
