# https://en.sfml-dev.org/forums/index.php?topic=9037.0
CXX := g++ 
CXXFLAGS := -c -Wall -Wextra -Wpedantic -Warray-bounds -Weffc++ -Werror
LIBS= -lsfml-graphics -lsfml-window -lsfml-system

all: testEntity testEntityManager


Entity.o: Entity.cpp Entity.h
	@echo "** Buildng Entity.o"
	$(CXX) $(CXXFLAGS) $< -o $@

EntityManager.o: EntityManager.cpp EntityManager.h Entity.h
	@echo "** Buildng EntityManager.o"
	$(CXX) $(CXXFLAGS) $< -o $@

testUtility.o: testUtility.cpp testUtility.h 
	@echo "** Building testUtility.o"
	$(CXX) $(CXXFLAGS) $< -o $@

EntityTest.o: EntityTest.cpp EntityTest.h Entity.h
	@echo "** Building EntityTest.o"
	$(CXX) $(CXXFLAGS) $< -o $@ 

EntityManagerTest.o: EntityManagerTest.cpp EntityManagerTest.h 
	@echo "** Building EntityManagerTest.o"
	$(CXX) $(CXXFLAGS) $< -o $@ 

# specify the additional dependencies
testEntity.o: testEntity.cpp EntityTest.h testUtility.h 
	@echo "** Building testEntity.o"
	$(CXX) $(CXXFLAGS) $< -o $@

# specify the additional dependencies
testEntityManager.o: testEntityManager.cpp EntityManagerTest.h  
	@echo "** Building testEntity.o"
	$(CXX) $(CXXFLAGS) $< -o $@


# target : prequisites
#	commands  (use tab to indent each command line)
testEntity: testEntity.o testUtility.o EntityTest.o Entity.o
	@echo "** Building testEntity"
	$(CXX) -o testEntity testEntity.o testUtility.o EntityTest.o Entity.o $(LIBS)


testEntityManager: testEntityManager.o EntityManagerTest.o EntityManager.o Entity.o testUtility.o
	@echo "** Building testEntityManager"
	$(CXX) -o testEntityManager testEntityManager.o EntityManagerTest.o EntityManager.o Entity.o testUtility.o $(LIBS)

# inform make about targets that are not files 
.PHONY: all clean #install uninstall 


clean:
	@echo "** Removing object files and executable ..."
	rm -f testEntity *.o 



