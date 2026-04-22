# Identifica o sistema operacional
ifeq ($(OS),Windows_NT)
	TARGET_NAME = benchmark.exe
	EXEC = $(TARGET)
else
	TARGET_NAME = benchmark
	EXEC = ./$(TARGET)
endif

# Compilador e flags
CXX = g++
CXXFLAGS = -Wall -pedantic -O2 -std=c++17 -I./include -pipe

#Diretórios
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

#Encontra os arquivos
SOURCES += $(wildcard $(SRC_DIR)/*.cpp)

OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# Nome do executável final
TARGET = $(BIN_DIR)/$(TARGET_NAME)


# Regra padrão: compilar tudo
all: $(TARGET)

# Linkagem final
$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) resultados.csv grafico*.png

test: $(TARGET)
		$(EXEC) 1000 5000 10000 15000 20000 30000 40000 50000 75000 100000 200000 350000 500000 750000 1000000 2000000 3000000 4000000 5000000