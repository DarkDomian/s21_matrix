# =============================================================================
# Compiler Configuration
# =============================================================================
CC				::=		gcc
CFLAGS			::=		-Wall -Werror -Wextra -std=c11 -pedantic -I./include -lm
TST_FLAG		::=		$(shell pkg-config --cflags --libs check)
COV_FLAGS		::=		-fprofile-arcs -ftest-coverage
DBG_FLAGS		::=		-g
REL_FLAG		::=		-DNDEBUG -O2

# =============================================================================
# Build Mode Configuration using MAKECMDGOALS
# =============================================================================
ifeq ($(MAKECMDGOALS),gcov_report)
    CFLAGS 		+= 		$(COV_FLAGS)
endif

ifeq ($(MAKECMDGOALS),release)
    CFLAGS 		+= 		$(REL_FLAG)
endif

ifeq ($(MAKECMDGOALS),gdb)
    CFLAGS 		+= 		$(DBG_FLAGS)
endif

ifeq ($(MORE_TESTS),1)
    CFLAGS += -DENABLE_EXTENDED_TESTS
endif

# =============================================================================
# Platform-Specific Configuration
# =============================================================================
ifeq ($(shell uname),Darwin)
    OPENCMD ::= open
else ifneq ($(shell uname -r | grep -i microsoft),)
    ifneq ($(shell which wslview 2>/dev/null),)
        OPENCMD ::= wslview
    else
        OPENCMD ::= cmd.exe /c start
    endif
else
    OPENCMD ::= xdg-open
endif

# =============================================================================
# Directory Structure
# =============================================================================
INCLUDE			::=		./include

OBJ_BUILD		::=		./build

LIB_SOURCE_DIR	::=		./src
OBJ_BUILD_DIR	::=		./build/obj

TST_SOURCE_DIR	::=		./tests
TST_BUILD_DIR	::=		./build/test

COV_REPORT_DIR	::=		./coverage
COV_FRONT_DIR	::=		./coverage/web

# =============================================================================
# Source and Object Files
# =============================================================================
LIB_SOURCE		=		$(wildcard $(LIB_SOURCE_DIR)/*.c)
LIB_OBJECTS		=		$(patsubst $(LIB_SOURCE_DIR)/%.c, $(OBJ_BUILD_DIR)/%.o, $(LIB_SOURCE))

TST_SOURCE		=		$(wildcard $(TST_SOURCE_DIR)/*.c)
TST_OBJECTS		=		$(patsubst $(TST_SOURCE_DIR)/%.c, $(TST_BUILD_DIR)/%.o, $(TST_SOURCE))

# =============================================================================
# Main Targets
# =============================================================================
LIBRARY			::=		s21_matrix.a

.PHONY: all debug release style_format style_check gcov_report clean rebuild gdb

# =============================================================================
# All(general) and Help targets
# =============================================================================
all: style_check gcov_report

# =============================================================================
# Build Rules
# =============================================================================
$(LIBRARY): $(LIB_OBJECTS)
	$(info Assembling all together to static lib...)
	@ar rcs $@ $(LIB_OBJECTS)
	@ranlib $@

$(OBJ_BUILD_DIR)/%.o: $(LIB_SOURCE_DIR)/%.c | $(OBJ_BUILD_DIR)
	$(info Building the $@ object file...)
	@$(CC) $(CFLAGS) -c $< -o $@

# =============================================================================
# Testing Rules
# =============================================================================
test: $(TST_OBJECTS) $(LIBRARY)
	$(info Compile tests and running with valgrind...)
	@$(CC) $(CFLAGS) $(TST_OBJECTS) $(LIBRARY) $(TST_FLAG) -o run.test
	@CK_FORK=no valgrind --tool=memcheck --leak-check=full --track-origins=yes ./run.test

$(TST_BUILD_DIR)/%.o: $(TST_SOURCE_DIR)/%.c | $(TST_BUILD_DIR)
	$(info Building the $@ object file...)
	@$(CC) $(CFLAGS) -c $< $(TST_FLAG) -o $@


%.test: ./run.test
	$(info Runing $*-test with valgrind...)
	@CK_RUN_SUITE="$*" CK_FORK=no valgrind --tool=memcheck --leak-check=full --track-origins=yes ./run.test

# =============================================================================
# Assemble Coverage Data to Web-Page
# =============================================================================
gcov_report: test | $(COV_FRONT_DIR)
	$(info Generating coverage report...)
	@lcov --test-name "s21_matrix" -v --output-file $(COV_REPORT_DIR)/coverage.info --capture --directory $(OBJ_BUILD_DIR)
	@genhtml $(COV_REPORT_DIR)/coverage.info --show-navigation --dark-mode --legend --output-directory $(COV_FRONT_DIR)
	@$(OPENCMD) $(COV_FRONT_DIR)/index.html || true

# =============================================================================
# Code Quality Rules
# =============================================================================
style_format: $(LIB_SOURCE) $(TST_SOURCE)
	$(info Formatting code with clang-format...)
	@clang-format -i --verbose --style="{BasedOnStyle: Google}" ./*/*.[h,c]

style_check: $(LIB_SOURCE) $(TST_SOURCE)
	$(info Checking style with clang-format and cppcheck...)
	@clang-format -n --style="{BasedOnStyle: Google}" --Werror ./*/*.[h,c]
	@cppcheck --enable=all --force --suppress=missingIncludeSystem --check-level=exhaustive --error-exitcode=1 $(LIB_SOURCE) $(TST_SOURCE)
	@echo "Style check passed successfully!"

#  TODO(trelawnm): have a look, does the target-specific call will work
clang_tidy_%: $(LIB_SOURCE) $(TST_SOURCE)
	$(info Checking style with clang-tidy in special files...)
	@clang-tidy src/$*.c --fix -checks=-*,clang-analyzer-*,google-*,performance-*,portability-*,readability-* -- -Iinclude $(LIB_SOURCE) $(TST_SOURCE)

extra_style_format: $(LIB_SOURCE) $(TST_SOURCE)
	$(info Formatting code with clang-tidy...)
	@clang-tidy ./*/*.[h,c] --fix -checks=-*,clang-analyzer-*,google-*,performance-*,portability-*,readability-* -- -Iinclude $(LIB_SOURCE) $(TST_SOURCE)

extra_style_check: $(LIB_SOURCE) $(TST_SOURCE)
	$(info Checking style with clang-tidy...)
	@clang-tidy ./*/*.[h,c] -header-filter=.* -checks=-*,clang-analyzer-*,google-*,performance-*,portability-*,readability-* -- -Iinclude $(LIB_SOURCE) $(TST_SOURCE)

# =============================================================================
# Build Mode Rules
# =============================================================================
release: $(LIBRARY)
	$(info Release build completed.)

gdb: test
	$(info Running with gdb...)
	@CK_FORK=no gdb ./run.test

clean:
	$(info Cleaning the build artifacts...)
	@rm -rf $(OBJ_BUILD) $(LIBRARY) ./*.test ./coverage ./*.log

rebuild: clean all

# =============================================================================
# Directory creation
# =============================================================================
$(OBJ_BUILD_DIR):
	$(info Creating a directory for objective file...)
	@mkdir -p $(OBJ_BUILD) $(OBJ_BUILD_DIR)

$(TST_BUILD_DIR):
	$(info Creating a directory for test-objective file...)
	@mkdir -p $(OBJ_BUILD) $(TST_BUILD_DIR)

$(COV_FRONT_DIR):
	$(info Creating a direcory for coverage report...)
	@mkdir -p $(COV_REPORT_DIR) $(COV_FRONT_DIR)
