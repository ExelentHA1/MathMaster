CC = g++
CFLAGS = -g -std=c++17 -m64 -Iinclude -Wall # -Werror
# LFLAGS = 

BINDIR = bin
SRCDIR = src
INCDIR = include
LIBDIR = lib

# Locate files
SRC := $(wildcard $(SRCDIR)/*.cpp)
OBJ := $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%.o,$(SRC))


TARGET = $(BINDIR)/app

all: $(TARGET)

# Build Rules
$(TARGET) : $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -L$(LIBDIR) -lmingw32 -lSDL2main -lSDL2 -lSDL2_test -lSDL2_mixer -lSDL2_image -lSDL2_ttf

$(BINDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ 

clean: 
	rm $(BINDIR)/*.o -rf

run: $(BINDIR)/app.exe
	./$(BINDIR)/app.exe

