CC = clang
OUTPUT_DIR = out
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c)
INC_DIR = -Iinclude/
LIB_DIR = -L"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22621.0\um\x64"
LIB_NAME = -luser32

clean:
	-rm -rf out/*

all:
	${CC} -o ${OUTPUT_DIR}/carfleet_c.exe ${SRC} ${INC_DIR} ${LIB_DIR} ${LIB_NAME}

run:
	./out/carfleet_c.exe