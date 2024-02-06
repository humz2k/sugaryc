SOURCEDIR ?= sources
BUILD_DIR ?= build

SOURCES := $(shell find $(SOURCEDIR) -name '*.sgc') $(shell find $(SOURCEDIR) -name '*.c') $(shell find $(SOURCEDIR) -name '*.cpp')
OBJECTS_0 := $(SOURCES:%.sgc=%.o)
OBJECTS_1 := $(OBJECTS_0:%.cpp=%.o)
OBJECTS := $(OBJECTS_1:%.c=%.o)
OUTPUTS := $(OBJECTS:sources%=build%)

libmpisgc.a: $(OUTPUTS)
	echo $(OUTPUTS)
	ar -cr $@ $^

$(BUILD_DIR)/%.o: $(SOURCEDIR)/%.sgc | $(BUILD_DIR)
	mpisgcc -O3 -o $@ $< -c

$(BUILD_DIR)/%.o: $(SOURCEDIR)/%.c | $(BUILD_DIR)
	mpicc -O3 -o $@ $< -c

$(BUILD_DIR)/%.o: $(SOURCEDIR)/%.cpp | $(BUILD_DIR)
	mpicxx -O3 -o $@ $< -c

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY: clean

clean:
	rm -rf $(BUILD_DIR)
	rm libmpisgc.a
