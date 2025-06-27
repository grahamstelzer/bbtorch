NVCC = nvcc
TARGET = add_cuda
SRC = add.cu

all: $(TARGET)

$(TARGET): $(SRC)
	$(NVCC) $< -o $@

clean:
	rm -f $(TARGET) add

.PHONY: all clean
