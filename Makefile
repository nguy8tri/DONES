
SRCS := $(wildcard src/*.cpp)

OBJS := $(patsubst %.cpp,%.o,$(SRCS))

BIN := dones

all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) -o $(BIN) $(OBJS)

%.o: %.cpp
	$(CXX) -c $< -o $@

clean:
	rm -f $(OBJS)