SOURCEDIR ?= sources
BUILD_DIR ?= build

SOURCES := $(shell find $(SOURCEDIR) -name '*.sgc') $(shell find $(SOURCEDIR) -name '*.c') $(shell find $(SOURCEDIR) -name '*.cpp')
OBJECTS_0 := $(SOURCES:%.sgc=%.o)
OBJECTS_1 := $(OBJECTS_0:%.cpp=%.o)
OBJECTS := $(OBJECTS_1:%.c=%.o)
OUTPUTS := $(OBJECTS:sources%=build%)

libsgc.a: $(OUTPUTS)
	echo $(OUTPUTS)
	ar -cr $@ $^

$(BUILD_DIR)/%.o: $(SOURCEDIR)/%.sgc | $(BUILD_DIR)
	sgcc -O3 -o $@ $< -c

$(BUILD_DIR)/%.o: $(SOURCEDIR)/%.c | $(BUILD_DIR)
	gcc -O3 -o $@ $< -c

$(BUILD_DIR)/%.o: $(SOURCEDIR)/%.cpp | $(BUILD_DIR)
	g++ -O3 -o $@ $< -c

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/np

.PHONY: clean

clean:
	rm -rf $(BUILD_DIR)
	rm libsgc.a
	