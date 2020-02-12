CXX = g++
CXXFLAG = -fopenmp  # for debugging
OUTPUT = chol_omp_gnu
SRC = chol_omp
default: begin main end

begin:
	@echo "Building Exercise for Lab1&2-Introduction and Multithread [OpenMP    ]"

main: $(SRC).o
	$(CXX) $(CXXFLAG) $(SRC).o -o $(OUTPUT)

$(SRC).o: $(SRC).cpp
	$(CXX) $(CXXFLAG) -c $<

clean:
	rm -f $(SRC).o $(OUTPUT)

end:
	@echo "Done"