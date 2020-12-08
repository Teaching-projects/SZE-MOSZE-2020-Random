SRC_DIR := sources
OBJ_DIR := objects

CXX := g++-9

EXE := a.out
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEP := $(OBJ:.o=.d)
DOX := doxconf

IO_TEST_DIR		:= io_test
UNIT_TEST_DIR	:= unit_test
JSON_FILE_DIR	:= json_files

CPPFLAGS := -MMD -MP
CXXFLAGS := -std=c++17 -Wall -g

.PHONY: all clean documentation io-test unit-test static-code-analysis memory-leak-test

all: $(EXE)

$(EXE): $(OBJ) $(DEP)
	$(CXX) $(OBJ) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.d: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $(subst .d,.o, $@)

$(OBJ_DIR):
	mkdir -p $@

-include $(DEP)

clean:
	$(RM) -rv $(OBJ_DIR)
	$(RM) -rv $(EXE)

documentation:
	doxygen $(DOX)

io-test: all
	@cd $(JSON_FILE_DIR) && \
	../$(EXE) gameconfig1.json < ../io_test/inputs.txt > ../$(IO_TEST_DIR)/current_output1.txt && \
	../$(EXE) gameconfig2.json < ../io_test/inputs.txt > ../$(IO_TEST_DIR)/current_output2.txt
	@cd $(IO_TEST_DIR) && \
	diff output1.txt current_output1.txt && \
	diff output2.txt current_output2.txt && \
	echo "I/O test succesful!"

unit-test:
	cd $(UNIT_TEST_DIR) && \
	cmake CMakeLists.txt && \
	$(MAKE) && \
	./runTests

static-code-analysis:
	cppcheck --enable=warning --error-exitcode=1 $(SRC_DIR)/*.cpp
	cppcheck --enable=performance,style --output-file=cppcheck_report.txt $(SRC_DIR)/*.cpp

memory-leak-test: all
	cd $(JSON_FILE_DIR) && \
	valgrind --leak-check=full --track-origins=yes --error-exitcode=1 ./../$(EXE) gameconfig1.json < ../io_test/inputs.txt && \
	valgrind --leak-check=full --track-origins=yes --error-exitcode=1 ./../$(EXE) gameconfig2.json < ../io_test/inputs.txt
