TARGET = STHCW
SRCS = main.c GS.c level_code/lv_startup.c

# --- LINUX CONFIG (Native GCC 13) ---
CC_LINUX = gcc
CFLAGS_LINUX = -O2 -Wall $(shell sdl2-config --cflags)
LDFLAGS_LINUX = $(shell sdl2-config --libs)
OUT_LINUX = build/linux/$(TARGET)

# --- WINDOWS CONFIG (MinGW Cross-Compiler) ---
CC_WIN = x86_64-w64-mingw32-gcc
SDL_WIN_DIR = /DATA/SOFTWARE-LNX/SDL2-2.30.11/x86_64-w64-mingw32
CFLAGS_WIN = -O2 -Wall -I$(SDL_WIN_DIR)/include/SDL2
LDFLAGS_WIN = -L$(SDL_WIN_DIR)/lib -lmingw32 -lSDL2main -lSDL2 -mwindows -Wl,--subsystem,windows:6.01
OUT_WIN = build/win/$(TARGET).exe

# --- TARGETS ---

all: linux win

linux: $(OUT_LINUX)
win: $(OUT_WIN)

# Build Linux Native
$(OUT_LINUX): $(SRCS)
	@mkdir -p build/linux
	$(CC_LINUX) $(SRCS) -o $@ $(CFLAGS_LINUX) $(LDFLAGS_LINUX)
	@echo "-> Built Linux binary: $@"

# Build Windows Cross-Compiled
$(OUT_WIN): $(SRCS)
	@mkdir -p build/win
	$(CC_WIN) $(SRCS) -o $@ $(CFLAGS_WIN) $(LDFLAGS_WIN)
	@echo "-> Built Windows binary: $@"

# Clean everything
clean:
	rm -rf build
	@echo "-> Cleaned build directories."

.PHONY: all linux win clean
