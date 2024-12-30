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
	valgrind --tool=massif --massif-out-file=massif_outputs/massif.out.%p ./tensortests
	@echo "Massif output saved to massif_outputs/massif.out.*"
	@ms_print massif_outputs/massif.out.* > massif_outputs/massif_output.txt
	@echo "Massif readable output saved to massif_outputs/massif_output.txt"

clean:
	rm -f *.o tensortests massif_outputs/massif.out.* massif_outputs/massif_output.txt
