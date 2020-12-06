ifeq ($(shell uname -s),Linux)
  CC=clang-11
  CXX=clang-11
else
  CC=clang
  CXX=clang
endif

INCLUDE_DIRS= include test/include
INC_PARAMS=$(foreach d, $(INCLUDE_DIRS), -I$d)

CFLAGS=-x c++ -c -Wall -std=c++17 $(INC_PARAMS)
LDFLAGS=-lstdc++ -lm

SRC:=$(shell find src -name '*.cpp')
OBJECTS=$(SRC:.cpp=.o)

TEST_SRC=test/tests-main.cpp
TEST_OBJECTS=$(TEST_SRC:.cpp=.o)
TEST_EXECUTABLE=runtests

APP_SRC=main.cpp
APP_OBJECTS=$(APP_SRC:.cpp=.o)
APP_EXECUTABLE=app

ZIP_FILE=assignment1-DV1626-assembler.zip

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

.PHONY: zip
zip:
	${MAKE} clean
	${MAKE} all
	${MAKE} test
	${MAKE} clean
	${MAKE} $(ZIP_FILE)

$(ZIP_FILE):
	zip -r  $(ZIP_FILE) . -x '*.git*' -x '*.vscode*'  -x '*.zip'

.PHONY: install
install:
	sudo apt-get update -y
	sudo apt-get install zip -y
	sudo apt-get install unzip -y
