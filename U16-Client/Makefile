SRCS = main.cpp
SRCS += ./client/Client.cpp
CPPVER =c++14
PROGRAM	= u16-client

.PHONY: all
all: $(PROGRAM)

$(PROGRAM): $(SRCS)
	g++ $(SRCS) -I./client/asio-1.10.8/ -std=$(CPPVER) -o $(PROGRAM)

.PHONY: clean
clean:;	rm -f *.o *~ $(PROGRAM)
