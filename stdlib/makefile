SOURCEDIR ?= sources
BUILD_DIR ?= build

SOURCES := $(shell find $(SOURCEDIR) -name '*.sgc')
OBJECTS := $(SOURCES:%.sgc=%.o)
OUTPUTS := $(OBJECTS:sources%=build%)

libsgc.a: $(OUTPUTS)
	ar -cr $@ $^

$(BUILD_DIR)/%.o: $(SOURCEDIR)/%.sgc | $(BUILD_DIR)
	sgcc -O3 -o $@ $< -c

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY: clean

clean:
	rm -rf $(BUILD_DIR)
	rm libsgc.a
	