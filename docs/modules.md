# Modules

These aren't really modules, just more name mangling. You declare a module with `module module_name;`. Then, anywhere with `module_name.something` will be replaced with something like `module_name__something`. Nothing smarter than that.