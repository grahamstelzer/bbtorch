CC = g++
CFLAGS = -g --std=c++2a -Wall -Werror -pedantic
LIB =
DEPS = tensor.hpp

all: tensortests

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< $(LIB)

tensortests: tensortests.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

run: tensortests
	@echo "Running with Valgrind memory leak check..."
	valgrind --leak-check=full ./tensortests
	@echo "Running with Massif memory profiling..."
	valgrind --tool=massif ./tensortests
	@echo "Massif output saved to massif.out.*"
	@ms_print massif.out.* > massif_output.txt
	@echo "Massif readable output saved to massif_output.txt"

clean:
	rm -f *.o tensortests massif.out.* massif_output.txt
