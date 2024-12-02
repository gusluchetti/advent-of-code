CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall

validate_path:
	@if [ -z "$(FILE)" ]; then \
		echo "Error: Please specify .cpp solution file"; \
		exit 1; \
	fi

build: validate_path
	$(CXX) $(CXXFLAGS) $(FILE) -o "$(shell dirname "$(FILE)")/out"

test: build
	@cd $(shell dirname "$(FILE)") && ./out < ./test.txt

run: build
	@cd $(shell dirname "$(FILE)") && ./out < ./input.txt
