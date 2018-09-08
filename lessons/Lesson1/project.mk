#####################################################################
# project specific
#####################################################################
PROJECTDIR = Lesson1
TARGET = Lesson1

BUILDLIBS = gtest

LIBDEP = \
../gtest \

LIBS = $(foreach L,$(BUILDLIBS),-l$L) -lrt -pthread
