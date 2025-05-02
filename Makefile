all:
	@echo This file contains auxiliary targets.
	@echo Such as dot image generation or launching clang

DOT_DIR_PATH=./doc/dot
DOT_SRC_FULL_PATH = $(shell find $(DOT_DIR_PATH)/ -name "*.dot")
generate_dot: $(DOT_SRC_FULL_PATH:.dot=.png)

$(DOT_DIR_PATH)/%.png: $(DOT_DIR_PATH)/%.dot
	dot -Tpng $< -o $@

LL_DIR_PATH=./doc/IR
LL_BIN_PATH=./bin/IR
LL_SRC_FULL_PATH = $(shell find $(LL_DIR_PATH)/ -name "*.ll")
LL_SRC = $(notdir $(LL_SRC_FULL_PATH))
launch_llvm: binir $(addprefix $(LL_BIN_PATH)/, $(LL_SRC:.ll=))

$(LL_BIN_PATH)/%: $(LL_DIR_PATH)/%.ll
	clang $< -o $@

binir:
	@mkdir -p bin
	@mkdir -p bin/IR