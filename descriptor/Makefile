#
# (c) 2020 iomonad - <iomonad@riseup.net>
# See: https://github.com/iomonad/deny-toolkit
#

CC = c++
CFLAGS = -g -Wall
SRCS = main.cpp Descriptor.cpp Arguments.cpp
TARGET = deny-descriptor

OPENCV = `pkg-config opencv4 --cflags --libs`
LIBS = $(OPENCV)

$(TARGET):$(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LIBS)

clean:
	@rm -f $(TARGET)

.PHONY: clean
