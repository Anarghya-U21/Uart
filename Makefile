BINDIR = $(PWD)
SRC_DIR = $(PWD)
OBJ = $(PWD)/Uart2_test.c

CC= $(CROSS_COMPILE)arm-poky-linux-gnueabi-gcc --sysroot=$(SDKTARGETSYSROOT)

TARGET = Uart2_test.out

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $(BINDIR)/$(TARGET) $(OBJ) -mfloat-abi=hard

.PHONY: clean
clean:
	rm -f ./src/*.o
	rm -f ./*.out
