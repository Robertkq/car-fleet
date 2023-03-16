CC = clang
OUTPUT_DIR = out
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c)
INC_DIR = include

clean:
	-rm -rf out

all:
	-mkdir out
	echo ${SRC}
	${CC} -o ${OUTPUT_DIR}/carfleet_c ${SRC} -I${INC_DIR}/

run:
	./out/carfleet_c