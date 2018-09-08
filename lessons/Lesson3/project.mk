#####################################################################
# project specific
#####################################################################
PROJECTDIR = Lesson3
TARGET = Lesson3

BUILDLIBS = gtest

LIBDEP = \
../gtest \

LIBS = $(foreach L,$(BUILDLIBS),-l$L) -lrt -pthread
