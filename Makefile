src = $(shell find ./src -type f -name *.cpp)
objs = $(subst ./src, ./objs, $(src:.cpp=.o))
libs = -lGL -lGLU -lglut
target = project

all: $(target)

$(target): $(objs)
	g++ -o $@ $^ $(libs)

$(objs): ./objs/%.o: ./src/%.cpp
	g++ -c $^ -o $@

.PHONY: clean
clean:
	rm -rf src/*.o