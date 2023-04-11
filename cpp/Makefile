FILE ?=

CXX = g++
CXXFLAGS = -std=c++17 -m64 -DSFML_STATIC
SRC_DIR = src
OUTPUT_DIR = out
APP_NAME = application.exe

SFML_DIR = C:\Users\rvuia\Libraries\SFML-2.5.1
IMGUI_DIR = C:\Users\rvuia\Libraries\imgui
IMGUI-SFML_DIR = C:\Users\rvuia\Libraries\imgui-sfml
WIN_DIR="C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22000.0\um"

INCLUDE_DIR = -Iinclude/ \
	-I${SFML_DIR}/include/ \
	-I${IMGUI_DIR}/ \
	-I${IMGUI-SFML_DIR}/

LIB_DIR = -L${SFML_DIR}/lib/ \
	-L${WIN_DIR}/x64/

LIB_LINK = -lsfml-graphics-s \
	-lsfml-window-s \
	-lsfml-system-s \
	-lwinmm \
	-lopengl32 \
	-lfreetype \
	-luser32 \
	-lgdi32


# we use wildcards to gather all .cpp files from all the directories that have sources
SRCS := $(wildcard ${SRC_DIR}/*.cpp) \
	$(wildcard ${IMGUI_DIR}/*.cpp) \
	$(wildcard ${IMGUI-SFML_DIR}/*.cpp)

#we add the prefix ${OUTPUT_DIR} to the *FILANAME* from ${SRCS} with extension .o
OBJS := $(addprefix $(OUTPUT_DIR)/, $(notdir $(SRCS:.cpp=.o)))

.PHONY = clean all run

clean:
	rm -rf ${OUTPUT_DIR}/*

all: ${OUTPUT_DIR}/${APP_NAME}

# linkage, requires all .o to be made before, at this tage we link the libs

${OUTPUT_DIR}/${APP_NAME}: ${OBJS}
	${CXX} ${CXXFLAGS} -o $@ $^ ${LIB_DIR} ${LIB_LINK}

# compilation, each .o requires the corespondent .cpp, only include path is needed at compilation time
# we also use 3 targets that look the same but use different pattern in recipes because some .o files have their .cpp corespondents in different directories we know the names of
${OUTPUT_DIR}/%.o: ${SRC_DIR}/%.cpp
	${CXX} ${CXXFLAGS} ${INCLUDE_DIR} -c -o $@ $<

${OUTPUT_DIR}/%.o: ${IMGUI_DIR}/%.cpp
	${CXX} ${CXXFLAGS} ${INCLUDE_DIR} -c -o $@ $<

${OUTPUT_DIR}/%.o: ${IMGUI-SFML_DIR}/%.cpp
	${CXX} ${CXXFLAGS} ${INCLUDE_DIR} -c -o $@ $<


run: ${OUTPUT_DIR}/${APP_NAME}
	./${OUTPUT_DIR}/${APP_NAME} ${FILE}

