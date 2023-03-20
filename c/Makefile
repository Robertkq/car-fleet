CC = clang
OUTPUT_DIR = out
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c)
INC_DIR = include

clean:
	-rm -rf out

all:
	-mkdir out
	${CC} -o ${OUTPUT_DIR}/carfleet_c.exe ${SRC} -I${INC_DIR}/ -L"C:/Program Files (x86)/Windows Kits/10/Lib/10.0.19041.0/um/x64/" -luser32 

run:
	./out/carfleet_c