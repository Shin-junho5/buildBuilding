CROSS= 
CC=$(CROSS)g++
EXE=main
DEFINES= #-DDEBUG
CFLGS=-I./include $(DEFINES)
LDFLAGS= -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf
C_SRC = $(wildcard *.cpp)
OBJ = $(C_SRC:.cpp=.o)
DEPS = *.h
all: $(EXE)
	echo completed!
# $(EXE) : $(OBJ)
# 	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# 각 오브젝트 파일에 대한 규칙, 헤더 파일 의존성 포함
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm *.o
	rm test


