#####################################################################
# project specific
#####################################################################
PROJECTDIR = Lesson6
TARGET = Lesson6

BUILDLIBS = gtest

LIBDEP = \
../gtest \

LIBS = $(foreach L,$(BUILDLIBS),-l$L) -lrt -pthread
