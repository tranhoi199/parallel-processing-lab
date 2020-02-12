CC = gcc
CFLAG = -lpthread -g	# for debugging
OUTPUT = mul_mat_pthread_output
SRC = mat_mul_pthread
default: begin main end

begin:
	@echo "Building Exercise for Lab1&2-Introduction and Multithread"

main: $(SRC).o
	$(CC) $(CFLAG) $(SRC).o -o $(OUTPUT)
	
$(SRC).o: $(SRC).c

clean:
	rm -f $(SRC).o $(OUTPUT)

end:
	@echo "Done"