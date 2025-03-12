PROTO_DIR = .
CPP_OUT_DIR = ../cpp/protobuf
PYTHON_OUT_DIR = ../zmq_experiment/protobuf
PROTOC = protoc

PROTO_FILES = $(wildcard $(PROTO_DIR)/*.proto)

# Derived names for output files
CPP_OUTPUTS = $(patsubst $(PROTO_DIR)/%.proto, $(CPP_OUT_DIR)/%.pb.cc, $(PROTO_FILES))
CPP_HEADERS = $(patsubst $(PROTO_DIR)/%.proto, $(CPP_OUT_DIR)/%.pb.h, $(PROTO_FILES))
PYTHON_OUTPUTS = $(patsubst $(PROTO_DIR)/%.proto, $(PYTHON_OUT_DIR)/%.pb2.py, $(PROTO_FILES))
PYTHON_STUBS = $(patsubst $(PROTO_DIR)/%.proto, $(PYTHON_OUT_DIR)/%.pb2.pyi, $(PROTO_FILES))

# Default target
all: $(CPP_OUTPUTS) $(CPP_HEADERS) $(PYTHON_OUTPUTS) $(PYTHON_STUBS)

# Rule for generating C++ protobuf files
$(CPP_OUT_DIR)/%.pb.cc $(CPP_OUT_DIR)/%.pb.h: $(PROTO_DIR)/%.proto
	mkdir -p $(CPP_OUT_DIR)
	$(PROTOC) --cpp_out=$(CPP_OUT_DIR) --proto_path=$(PROTO_DIR) $<

# Rule for generating Python protobuf files
$(PYTHON_OUT_DIR)/%.pb2.py $(PYTHON_OUT_DIR)/%.pb2.pyi: $(PROTO_DIR)/%.proto
	mkdir -p $(PYTHON_OUT_DIR)
	$(PROTOC) --python_out=$(PYTHON_OUT_DIR) --pyi_out=$(PYTHON_OUT_DIR) --proto_path=$(PROTO_DIR) $<

# Clean generated files
clean:
	rm -f $(CPP_OUTPUTS) $(CPP_HEADERS) $(PYTHON_OUTPUTS) $(PYTHON_STUBS)

.PHONY: all clean
