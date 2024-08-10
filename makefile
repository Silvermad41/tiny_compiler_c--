CC=g++
CXXFLAGS= -g -Wall

SRC_Directory=src
OBJ_Directory=obj

srcs = $(wildcard $(SRC_Directory)/*.cpp)
objs = $(patsubst $(SRC_Directory)/%.cpp, $(OBJ_Directory)/%.o, $(srcs))
bin = bin/compiler

all: $(bin)

$(bin): $(objs)
	$(CC) $(CXXFLAGS) $(objs) -o  $@ 

obj/%.o: $(SRC_Directory)/%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) -r bin/* obj/*
