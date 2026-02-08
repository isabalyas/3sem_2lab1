CXX = g++
CXXFLAGS = -std=c++17 -I. -Inew_structures -Iwrappers -Wall -Wextra

# Основные цели
all: task6.exe task7.exe

# Задача 6: Hash Table
task6.exe: tasks/task6_hashtble.cpp new_structures/hashtable/hashtable.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

# Задача 7: LRU Cache (нужен open_hash.cpp!)
task7.exe: tasks/task7_cache.cpp new_structures/open_hash/open_hash.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

# Утилиты
clean:
	rm -f *.exe

run6: task6.exe
	./task6.exe

run7: task7.exe
	./task7.exe

run_all: task6.exe task7.exe
	@echo "=== Задача 6 ==="
	@./task6.exe || echo "Задача 6 завершилась"
	@echo -e "\n=== Задача 7 ==="
	@./task7.exe || echo "Задача 7 завершилась"

.PHONY: all clean run6 run7 run_all
