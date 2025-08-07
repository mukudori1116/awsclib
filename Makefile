CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Isrc
LIBS = -lcurl
TARGET = aws_client
SRCDIR = src
OBJDIR = obj
EXAMPLEDIR = example
SERVICEDIR = $(EXAMPLEDIR)/services

# Source files
CORE_SOURCES = $(SRCDIR)/aws_client.c
SERVICE_SOURCES = $(SERVICEDIR)/aws_sts.c $(SERVICEDIR)/aws_sts_get.c

# Object files
CORE_OBJECTS = $(OBJDIR)/aws_client.o
CORE_LIB_OBJECTS = $(OBJDIR)/aws_client_lib.o
SERVICE_OBJECTS = $(OBJDIR)/aws_sts.o $(OBJDIR)/aws_sts_get.o

# Library objects
CORE_LIB_ONLY = $(CORE_LIB_OBJECTS)
ALL_LIB_OBJECTS = $(CORE_LIB_OBJECTS) $(SERVICE_OBJECTS)

# Default target
all: $(TARGET)

# Build core library
lib: $(CORE_LIB_ONLY)

# Build all libraries including services
lib-all: $(ALL_LIB_OBJECTS)

# Create main executable
$(TARGET): $(CORE_OBJECTS)
	$(CC) $(CORE_OBJECTS) -o $(TARGET) $(LIBS)

# Create object files
$(OBJDIR)/aws_client.o: $(SRCDIR)/aws_client.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/aws_client_lib.o: $(SRCDIR)/aws_client.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -DLIB_MODE -c $< -o $@

$(OBJDIR)/aws_sts.o: $(SERVICEDIR)/aws_sts.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/aws_sts_get.o: $(SERVICEDIR)/aws_sts_get.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Build sample programs
examples: basic sts-example custom get-example

basic: $(ALL_LIB_OBJECTS)
	$(CC) $(CFLAGS) $(EXAMPLEDIR)/basic_usage.c $(ALL_LIB_OBJECTS) -o basic_usage $(LIBS)

sts-example: $(ALL_LIB_OBJECTS)
	$(CC) $(CFLAGS) $(EXAMPLEDIR)/all_services.c $(ALL_LIB_OBJECTS) -o sts_example $(LIBS)

custom: $(CORE_LIB_ONLY)
	$(CC) $(CFLAGS) $(EXAMPLEDIR)/custom_request.c $(CORE_LIB_ONLY) -o custom_request $(LIBS)

get-example: $(ALL_LIB_OBJECTS)
	$(CC) $(CFLAGS) $(EXAMPLEDIR)/get_method_example.c $(ALL_LIB_OBJECTS) -o get_method_example $(LIBS)

# Cleanup
clean:
	rm -rf $(OBJDIR) $(TARGET) basic_usage sts_example custom_request get_method_example

# Run targets
run: $(TARGET)
	./$(TARGET)

run-basic: basic
	./basic_usage

run-sts: sts-example
	./sts_example

run-custom: custom
	./custom_request

run-get: get-example
	./get_method_example

# Debug build
debug: CFLAGS += -g -DDEBUG
debug: all

.PHONY: all lib lib-all examples basic sts-example custom get-example clean run run-basic run-sts run-custom run-get debug
