# compiler
CC:=$(shell which cc)
CC_WIN_32:=$(shell which i686-w64-mingw32-gcc)
CC_WIN_64:=$(shell which x86_64-w64-mingw32-gcc)

# compiler flags
# -g debugging
# -Wall compiler warnings
CFLAGS = -g -Wall -pedantic

OUT_DIR=build

TARGET = cpfile

all: $(TARGET)
	@mkdir -p $(OUT_DIR)/win/
	@mkdir -p $(OUT_DIR)/posix/
	$(CC) $(TARGET).c -o $(OUT_DIR)/posix/$(TARGET)
	$(CC_WIN_32) $(TARGET).c -o $(OUT_DIR)/win/$(TARGET)32
	$(CC_WIN_64) $(TARGET).c -o $(OUT_DIR)/win/$(TARGET)64

clean:
	$(RM) -r $(OUT_DIR)
