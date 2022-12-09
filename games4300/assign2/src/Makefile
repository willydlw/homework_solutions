# https://en.sfml-dev.org/forums/index.php?topic=9037.0
CXX := g++ 
LIBS= -lsfml-graphics -lsfml-window -lsfml-system

all: testEntity

Entity.o: Entity.cpp Entity.h
	$(CXX) -c -Wall $< -o $@

# specify the additional dependencies
testEntity.o: testEntity.cpp Entity.cpp Entity.h
	$(CXX) -c -Wall $< -o $@


testEntity: testEntity.o Entity.o
	@echo "** Building testEntity"
	$(CXX) -o testEntity testEntity.o Entity.o $(LIBS)

# inform make about targets that are not files 
.PHONY: all clean #install uninstall 


clean:
	@echo "** Removing object files and executable ..."
	rm -f testEntity *.o 



