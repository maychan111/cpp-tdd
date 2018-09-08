#####################################################################
# project specific
#####################################################################
PROJECTDIR = Lesson4
TARGET = Lesson4

BUILDLIBS = gtest

LIBDEP = \
../gtest \

LIBS = $(foreach L,$(BUILDLIBS),-l$L) -lrt -pthread