SOURCES := $(shell find . -name '*.c')
OBJECTS := $(SOURCES:%.c=%.h)

.PHONY: all
all: $(OBJECTS)

%.h: %.o
	./$< > $@

%.o: %.c
	$(CC) $< -o $@

clean:
	rm -rf *.h
	rm -rf *.o