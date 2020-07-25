CC = c++
CFLAGS = -g -Wall
SRCS = Descriptor.cpp
PROG = deny-descriptor

OPENCV = `pkg-config opencv4 --cflags --libs`
LIBS = $(OPENCV)

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)
