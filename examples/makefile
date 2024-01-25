SOURCES := $(shell find . -name '*.sgc')
OBJECTS := $(SOURCES:%.sgc=%.o)

%.o: %.sgc | $(BUILD_DIR)
	sgcc -O3 -o $@ $<

.PHONY: all
all: $(OBJECTS)

.PHONY: clean

clean:
	rm *.o
	