#####################################
# You may edit this makefile        #
# Do not replace tabs with spaces   #
#####################################

CWD := $(shell	pwd)

LIBRARIES := \
test\gtest \

BINARIES := \
Lesson1 \
Lesson2 \
Lesson3 \
Lesson4 \
Lesson5 \
Lesson6 \
Lesson7 

#####################################
# Targets 
#####################################
all release debug coverage: 
	@date 1>&2
	@for i in $(BINARIES); do $(MAKE) -C $(CWD)/$$i --no-print-directory $@ || exit 1; done

clean release-clean debug-clean coverage-clean: 
	@date 1>&2
	@for i in $(LIBRARIES); do $(MAKE) -C $(CWD)/$$i --no-print-directory $@ || exit 1; done
	@for i in $(BINARIES); do $(MAKE) -C $(CWD)/$$i --no-print-directory $@ || exit 1; done

coverage-run:
	@(cd bin/Coverage; \
	./Lesson1; \
	./Lesson2; \
	./Lesson3; \
	./Lesson4; \
	./Lesson5; \
	./Lesson6; \
	) 
	
coverage-gen:
	rm -rf bin/CoverageInfo
	mkdir -p bin/CoverageInfo
	@(cd bin/CoverageInfo; \
	lcov -c -d ../Coverage/objs -b ../../source -o coverage.info --no-checksum --rc lcov_branch_coverage=1; \
	lcov -r coverage.info "/usr/*" "gtest*" "/test*" "*tinyxml*" "rapidjson*" "*json/internal*" --rc lcov_branch_coverage=1 > new.info; \
	genhtml new.info --rc lcov_branch_coverage=1 --rc genhtml_hi_limit=75 --rc genhtml_med_limit=50 --rc geninfo_gcov_all_blocks=1)

coverage-all: coverage coverage-run coverage-gen
	
.PHONY : all clean debug release coverage debug-clean release-clean coverage-clean coverage-all coverage-run coverage-gen 

