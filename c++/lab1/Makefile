# -------------------- Директории и цели --------------------
SRC_DIR = src
BUILD_DIR = build
TEST_DIR = tests

DEBUG_TARGET = $(BUILD_DIR)/debug.out
LEAKS_TARGET = $(BUILD_DIR)/leaks.out

# -------------------- Исходники --------------------
SRCS := $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)

# -------------------- Объекты --------------------
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# -------------------- Создание папки build --------------------
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# -------------------- Команда компиляции .cpp в .o --------------------
BUILD_COMMAND = g++ -g -c -o $@ $<

# -------------------- Частичная сборка объектов --------------------
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(BUILD_COMMAND)

# -------------------- Полная debug сборка --------------------
$(DEBUG_TARGET): $(OBJECTS)
	g++ -g -o $@ $(OBJECTS)

debug: $(DEBUG_TARGET)
	gdb $(DEBUG_TARGET)

# -------------------- Leak сборка --------------------
$(LEAKS_TARGET): $(OBJECTS)
	g++ -g -fsanitize=address -o $@ $(OBJECTS)

leaks: $(LEAKS_TARGET)
	./$(LEAKS_TARGET)

# -------------------- Очистка --------------------
clean:
	rm -rf $(BUILD_DIR)/*

# ==================== ТЕСТЫ ====================
TEST_SRC := $(wildcard $(TEST_DIR)/**/*.cpp) $(wildcard $(TEST_DIR)/*.cpp)
PROJECT_OBJECTS_FOR_TESTS := $(filter-out $(BUILD_DIR)/main.o, $(OBJECTS))
TEST_NAMES := $(patsubst $(TEST_DIR)/%.cpp,%,$(TEST_SRC))


$(BUILD_DIR)/$(TEST_DIR):
	mkdir -p $(BUILD_DIR)/$(TEST_DIR)

$(BUILD_DIR)/$(TEST_DIR)/%.o: $(TEST_DIR)/%.cpp | $(BUILD_DIR)/$(TEST_DIR)
	mkdir -p $(dir $@)
	$(BUILD_COMMAND)

$(BUILD_DIR)/$(TEST_DIR)/%.out: $(BUILD_DIR)/$(TEST_DIR)/%.o $(PROJECT_OBJECTS_FOR_TESTS)
	g++ -g -o $@ $^

$(TEST_NAMES): % : $(BUILD_DIR)/$(TEST_DIR)/%.out
	./$<

test: $(TEST_NAMES)
	@echo "Все тесты пройдены!"