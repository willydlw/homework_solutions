# https://en.sfml-dev.org/forums/index.php?topic=9037.0
CXX := g++ 
CFLAGS := -c -Wall 
LIBS= -lsfml-graphics -lsfml-window -lsfml-system

all: testEntity

Entity.o: Entity.cpp Entity.h
	$(CXX) $(CFLAGS) $< -o $@

EntityTest: EntityTest.cpp EntityTest.h 
	$(CXX) $(CFLAGS) $< -o $@ 

testUtility.o: testUtility.cpp testUtility.h 
	$(CXX) $(CFLAGS) $< -o $@

# specify the additional dependencies
testEntity.o: testEntity.cpp Entity.cpp Entity.h
	$(CXX) -c -Wall $< -o $@


testEntity: testEntity.o Entity.o EntityTest.o testUtility.o
	@echo "** Building testEntity"
	$(CXX) -o testEntity testEntity.o Entity.o EntityTest.o testUtility.o $(LIBS)

# inform make about targets that are not files 
.PHONY: all clean #install uninstall 


clean:
	@echo "** Removing object files and executable ..."
	rm -f testEntity *.o 



