
SRCS := $(wildcard src/*.cpp)

OBJS := $(patsubst %.cpp,%.o,$(SRCS))

BIN := dones

all: $(BIN)

CXXFLAGS := $(CXXFLAGS) -Ivendor -Isrc -Idocumentation -Wall -Wextra -Wno-missing-field-initializers -pedantic --std=c++11

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(OBJS) -lpython3.8
	chmod +x src/PythonMain.py

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(wildcard src/*.so)