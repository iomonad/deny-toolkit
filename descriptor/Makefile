#
# (c) 2020 iomonad - <iomonad@riseup.net>
# See: https://github.com/iomonad/deny-toolkit
#

CC = c++
STD = gnu++14
CFLAGS = -g -Wall -std=$(STD)
SRCS = main.cpp Arguments.cpp Descriptor.cpp \
       Interpolator.cpp ../Commons.cpp
TARGET = deny-descriptor

OPENCV = `pkg-config opencv4 --cflags --libs`
LIBS = $(OPENCV)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LIBS)

clean:
	@rm -f $(TARGET)

.PHONY: clean
