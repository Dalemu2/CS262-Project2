#Daniel Alemu G00884794
# CS 262, Lab Section 207
# project 2
# The Compiler: gcc for C programs, g++ for C++ programs, etc
CC= gcc
CFLAGS=-g -Wall
TARGET = project2_dalemu2_207
#all=   $(TARGET)
$(TARGET):  $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c
clean:
	rm $(TARGET)
