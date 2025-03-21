PROTO_DIR = .
C_OUT_DIR = ../cpp/protobuf
PYTHON_OUT_DIR = ../zmq_experiment/protobuf
PROTOC = protoc

PROTO_FILES = $(wildcard $(PROTO_DIR)/*.proto)

# Derived names for output files
C_OUTPUTS = $(patsubst $(PROTO_DIR)/%.proto, $(C_OUT_DIR)/%.pb.c, $(PROTO_FILES))
C_HEADERS = $(patsubst $(PROTO_DIR)/%.proto, $(C_OUT_DIR)/%.pb.h, $(PROTO_FILES))
PYTHON_OUTPUTS = $(patsubst $(PROTO_DIR)/%.proto, $(PYTHON_OUT_DIR)/%_pb2.py, $(PROTO_FILES))
PYTHON_STUBS = $(patsubst $(PROTO_DIR)/%.proto, $(PYTHON_OUT_DIR)/%_pb2.pyi, $(PROTO_FILES))

# Default target
all: $(C_OUTPUTS) $(C_HEADERS) $(PYTHON_OUTPUTS) $(PYTHON_STUBS)

# Rule for generating C++ protobuf files
$(C_OUT_DIR)/%.pb.c $(C_OUT_DIR)/%.pb.h: $(PROTO_DIR)/%.proto
	mkdir -p $(C_OUT_DIR)
	$(PROTOC) --c_out=$(C_OUT_DIR) --proto_path=$(PROTO_DIR) $<

# Rule for generating Python protobuf files
$(PYTHON_OUT_DIR)/%_pb2.py $(PYTHON_OUT_DIR)/%_pb2.pyi: $(PROTO_DIR)/%.proto
	mkdir -p $(PYTHON_OUT_DIR)
	$(PROTOC) --python_out=$(PYTHON_OUT_DIR) --pyi_out=$(PYTHON_OUT_DIR) --proto_path=$(PROTO_DIR) $<

# Clean generated files
clean:
	rm -f $(C_OUTPUTS) $(C_HEADERS) $(PYTHON_OUTPUTS) $(PYTHON_STUBS)

.PHONY: all clean
