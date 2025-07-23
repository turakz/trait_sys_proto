FORMAT_DIR := inc
FORMAT_STYLE := llvm
LINT_DIR := inc
BUILD_DIR := build
CXX_LANG_STD := std=c++17

clean:
	@if [ -e compile_commands.json ]; then \
		echo "removing compile_commands.json..."; \
		rm compile_commands.json; \
	fi
	rm -rf build
	rm -rf .cache

format: format.run format.check # should be no errors after format
format.run:
	@if ! command -v clang-format >/dev/null 2>&1; then \
		echo "lint -- error::clang-format is not installed"; \
		exit 1; \
	fi
	@# check if .clang-format exists
	@if [ ! -e .clang-format ]; then \
		echo "creating default .clang-format ($(FORMAT_STYLE))..."; \
		clang-format -style=$(FORMAT_STYLE) -dump-config > .clang-format; \
	else \
		echo ".clang-format already exists"; \
	fi
	@echo "running clang-format on all source files in $(FORMAT_DIR)..."
	@find . -regex '.*\.\(cpp\|cc\|h\|hpp\)' -exec clang-format -i {} +

format.check:
	@echo "checking formatting in $(FORMAT_DIR)..."
	@find $(FORMAT_DIR) -type f \( -name '*.cpp' -o -name '*.cc' -o -name '*.cxx' -o -name '*.h' -o -name '*.hpp' \) | \
	while read file; do \
		clang-format --dry-run --Werror "$$file" || echo "needs formatting: $$file"; \
	done

lint:
	@if ! command -v clang-tidy >/dev/null 2>&1; then \
		echo "lint -- error::clang-tidy is not installed"; \
		exit 1; \
	fi
	@# check if .clang-tidy exists
	@if [ ! -e .clang-tidy ]; then \
		echo "creating default .clang-tidy..."; \
		clang-tidy -dump-config > .clang-tidy; \
	else \
		echo ".clang-tidy already exists"; \
	fi
	@echo "running clang-tidy on all source files in $(LINT_DIR)..."
	@find $(LINT_DIR) -type f \( -name '*.hpp' -o -name '*.cpp' -o -name '*.cc' -o -name '*.cxx' \) | \
	while read file; do \
		echo "checking $$file"; \
		clang-tidy "$$file" -p=$(BUILD_DIR) -- -$(CXX_LANG_STD); \
	done

test:
	@# check if cmake exists
	@if ! command -v cmake >/dev/null 2>&1; then \
		echo "lint -- error::cmake is not installed"; \
		exit 1; \
	fi
	cmake -S. -Bbuild -GNinja
	cmake --build build

.PHONY: app
app: test
	./build/test_main
