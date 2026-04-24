CC = g++
CFLAGS = -std=c++11 -O2 -Wall -Wextra -Wpedantic

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

TARGET = $(BIN_DIR)/tp3.out

SOURCES = $(SRC_DIR)/main.cpp \
          $(SRC_DIR)/util.cpp \
          $(SRC_DIR)/logradouro.cpp \
          $(SRC_DIR)/palavra.cpp \
          $(SRC_DIR)/consulta.cpp

OBJECTS = $(OBJ_DIR)/main.o \
          $(OBJ_DIR)/util.o \
          $(OBJ_DIR)/logradouro.o \
          $(OBJ_DIR)/palavra.o \
          $(OBJ_DIR)/consulta.o

INCLUDES = -I$(INC_DIR)

.PHONY: all clean dirs

all: dirs $(TARGET)

dirs:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(INC_DIR)/util.h $(INC_DIR)/logradouro.h $(INC_DIR)/palavra.h $(INC_DIR)/consulta.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/util.o: $(SRC_DIR)/util.cpp $(INC_DIR)/util.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC_DIR)/util.cpp -o $(OBJ_DIR)/util.o

$(OBJ_DIR)/logradouro.o: $(SRC_DIR)/logradouro.cpp $(INC_DIR)/logradouro.h $(INC_DIR)/util.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC_DIR)/logradouro.cpp -o $(OBJ_DIR)/logradouro.o

$(OBJ_DIR)/palavra.o: $(SRC_DIR)/palavra.cpp $(INC_DIR)/palavra.h $(INC_DIR)/util.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC_DIR)/palavra.cpp -o $(OBJ_DIR)/palavra.o

$(OBJ_DIR)/consulta.o: $(SRC_DIR)/consulta.cpp $(INC_DIR)/consulta.h $(INC_DIR)/palavra.h $(INC_DIR)/logradouro.h $(INC_DIR)/util.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC_DIR)/consulta.cpp -o $(OBJ_DIR)/consulta.o

clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(TARGET)


