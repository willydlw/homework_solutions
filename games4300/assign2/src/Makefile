# https://en.sfml-dev.org/forums/index.php?topic=9037.0
CXX := g++ 
CXXFLAGS := -c -Wall -Wextra -Wpedantic -Warray-bounds -Weffc++ -Werror
LIBS= -lsfml-graphics -lsfml-window -lsfml-system

all: testEntity

Entity.o: Entity.cpp Entity.h
	$(CXX) $(CXXFLAGS) $< -o $@

EntityTest: EntityTest.cpp EntityTest.h 
	$(CXX) $(CXXFLAGS) $< -o $@ 

testUtility.o: testUtility.cpp testUtility.h 
	$(CXX) $(CXXFLAGS) $< -o $@

# specify the additional dependencies
testEntity.o: testEntity.cpp Entity.cpp Entity.h
	$(CXX) $(CXXFLAGS) $< -o $@


testEntity: testEntity.o Entity.o EntityTest.o testUtility.o
	@echo "** Building testEntity"
	$(CXX) -o testEntity testEntity.o Entity.o EntityTest.o testUtility.o $(LIBS)

# inform make about targets that are not files 
.PHONY: all clean #install uninstall 


clean:
	@echo "** Removing object files and executable ..."
	rm -f testEntity *.o 



