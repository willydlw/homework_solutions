CXX := g++ 
CXXFLAGS := -c -Wall -Wextra -Wpedantic -Warray-bounds
LIBS= -lsfml-graphics -lsfml-window -lsfml-system

all: testEntity testEntityManager testGameConfig

Vec2.o: Vec2.cpp Vec2.h
	@echo "** Buiding Vec2.o"
	$(CXX) $(CXXFLAGS) $< -o $@

Entity.o: Entity.cpp Entity.h
	@echo "** Buildng Entity.o"
	$(CXX) $(CXXFLAGS) $< -o $@

EntityManager.o: EntityManager.cpp EntityManager.h Entity.h
	@echo "** Building EntityManager.o"
	$(CXX) $(CXXFLAGS) $< -o $@

Game.o: Game.cpp Game.h EntityManager.h Vec2.h
	@echo "** Building Game.o"
	$(CXX) $(CXXFLAGS) $< -o $@

testUtility.o: testUtility.cpp testUtility.h 
	@echo "** Building testUtility.o"
	$(CXX) $(CXXFLAGS) $< -o $@

# Test Classes
EntityTest.o: EntityTest.cpp EntityTest.h Entity.h
	@echo "** Building EntityTest.o"
	$(CXX) $(CXXFLAGS) $< -o $@ 

EntityManagerTest.o: EntityManagerTest.cpp EntityManagerTest.h 
	@echo "** Building EntityManagerTest.o"
	$(CXX) $(CXXFLAGS) $< -o $@ 

GameTest.o: GameTest.cpp GameTest.h Game.h
	@echo "** Building GameTest.o"
	$(CXX) $(CXXFLAGS) $< -o $@ 

# Test Programs
testEntity.o: testEntity.cpp EntityTest.h testUtility.h 
	@echo "** Building testEntity.o"
	$(CXX) $(CXXFLAGS) $< -o $@

testEntityManager.o: testEntityManager.cpp EntityManagerTest.h  
	@echo "** Building testEntity.o"
	$(CXX) $(CXXFLAGS) $< -o $@

testGameConfig.o: testGameConfig.cpp GameTest.h  
	@echo "** Building testGameConfig.o"
	$(CXX) $(CXXFLAGS) $< -o $@


# Test Targets

# target : prequisites
#	commands  (use tab to indent each command line)
testEntity: testEntity.o testUtility.o EntityTest.o Entity.o
	@echo "** Building testEntity"
	$(CXX) -o testEntity testEntity.o testUtility.o EntityTest.o Entity.o $(LIBS)


testEntityManager: testEntityManager.o EntityManagerTest.o EntityManager.o Entity.o testUtility.o
	@echo "** Building testEntityManager"
	$(CXX) -o testEntityManager testEntityManager.o EntityManagerTest.o EntityManager.o Entity.o testUtility.o $(LIBS)


testGameConfig: testGameConfig.o GameTest.o Game.o EntityManager.o Entity.o Vec2.o
	@echo "** Building testEntity"
	$(CXX) -o testGameConfig testGameConfig.o GameTest.o Game.o EntityManager.o Entity.o Vec2.o $(LIBS)


# inform make about targets that are not files 
.PHONY: all clean #install uninstall 


clean:
	@echo "** Removing object files and executable ..."
	rm -f testEntity testEntityManager testGameConfig *.o 



