ifeq ($(shell uname -s),Linux)
  CC=clang-11
  CXX=clang-11
else
  CC=clang
  CXX=clang
endif

INCLUDE_DIRS= include test/include external/fmt/include
INC_PARAMS=$(foreach d, $(INCLUDE_DIRS), -I$d)

$(info +---------------------------------------------------------------------)
ifdef FIXTURES
  $(info | Environment detected AS CodeGrade)
  MC_EXPORT="-fsanitize=address"
  ASAN_EXPORT="symbolize=0"
  CFLAGS=-x c++ -c -Wall -Wpedantic -Werror -std=c++20 $(MC_FLAGS) $(INC_PARAMS) -O1
  LDFLAGS=-lstdc++ -lm -fuse-ld=lld $(MC_FLAGS)
  LINTER=clang-tidy-10
else
  $(info | Environment detected as NOT CodeGrade)
  MC_EXPORT="-fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls"
  ASAN_EXPORT="symbolize=1 ASAN_SYMBOLIZER_PATH=$(shell which llvm-symbolizer)"
  CFLAGS=-x c++ -c -Wall  -Wpedantic -Werror -std=c++20 $(MC_FLAGS) $(INC_PARAMS) -g -D_GLIBCXX_DEBUG -O0 -fno-elide-constructors
  LDFLAGS=-lstdc++ -lm -fuse-ld=lld $(MC_FLAGS)
  LINTER=clang-tidy
endif

$(info | * compiler: $(CC))
$(info | * linker: $(CXX))
$(info | * linter: $(LINTER))
$(info | * home: $(HOME))
$(info | * fixtures: $(FIXTURES))
$(info | * memcheck compile and link flags set to: $(MC_EXPORT))
$(info | * asan flags set to: $(ASAN_EXPORT))
$(info +---------------------------------------------------------------------)

SRC:=$(shell find src -name '*.cpp')
OBJECTS=$(SRC:.cpp=.o)

TEST_SRC=$(shell find test -name '*.cpp')
TEST_OBJECTS=$(TEST_SRC:.cpp=.o)
TEST_EXECUTABLE=runtests

APP_SRC=main.cpp
APP_OBJECTS=$(APP_SRC:.cpp=.o)
APP_EXECUTABLE=app

ZIP_FILE=assignment2-media-manager.zip

all: $(SRC) $(APP_SRC) $(APP_EXECUTABLE) $(TEST_SRC) $(TEST_EXECUTABLE)

$(TEST_EXECUTABLE): $(TEST_OBJECTS) $(OBJECTS)
	$(CXX) $(LDFLAGS) $(TEST_OBJECTS) $(OBJECTS) -o $@

$(APP_EXECUTABLE): $(APP_OBJECTS) $(OBJECTS)
	$(CXX) $(LDFLAGS) $(APP_OBJECTS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	-rm -f $(APP_EXECUTABLE)
	-rm -f $(TEST_EXECUTABLE)
	-rm -f $(ZIP_FILE)
	find . -name "*.gcda" -print0 | xargs -0 rm -f
	find . -name "*.gcno" -print0 | xargs -0 rm -f
	find . -name "*.o" -print0 | xargs -0 rm -f

.PHONY: test
test: all
	./$(TEST_EXECUTABLE)

.PHONY: memcheck
memcheck:
	MC_FLAGS=$(MC_EXPORT) $(MAKE) clean all
	ASAN_OPTIONS=$(ASAN_EXPORT) ./$(TEST_EXECUTABLE)

.PHONY: static-code-analysis
static-code-analysis:
	$(LINTER) --header-filter=".*.hpp" --warnings-as-errors='*' --checks="cppcoreguidelines-*, bugprone*, diagnostic-*, -clang-diagnostic-c++20-extensions, analyzer-*, readability-*" ${SRC} ${APP_SRC} -- ${INC_PARAMS}

.PHONY: zip
zip:
	${MAKE} clean
	${MAKE} all
	${MAKE} test
	${MAKE} clean
	${MAKE} $(ZIP_FILE)

$(ZIP_FILE):
	zip -r  $(ZIP_FILE) . -x '*.git*' -x '*.vscode*'  -x '*.zip'

RED=\033[0;31m
GREEN=\033[0;32m
NC=\033[0m
TMP_CHECK_NOT_OK=FAIL! Replace the test file with the one from the instructions!
TMP_CHECK_OK=PASS!
.PHONY: check-tampering
check-tampering:
	@echo "Checking for tampering"
	@sha1sum 'test/tests-main.cpp' | grep -q '464ee9dbd4705e79ad15a772ffd2dc065ff6f33a'; \
		if [ $$? -eq 0 ]; then \
			echo "${GREEN}$(TMP_CHECK_OK)${NC}";\
			exit 0;\
		else \
			echo "${RED}$(TMP_CHECK_NOT_OK)${NC}";\
			exit 1;\
		fi
