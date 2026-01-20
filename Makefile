# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -I. -Inew_structures -Iwrappers -Wall -Wextra

# Исходные файлы для структур данных
STACK_SRC = new_structures/stack/stack.cpp
QUEUE_SRC = new_structures/queue/queue.cpp
ARRAY_SRC = new_structures/array/array.cpp
LIST1_SRC = new_structures/1list/1list.cpp
LIST2_SRC = new_structures/2list/2list.cpp
HASHTABLE_SRC = new_structures/hashtable/hashtable.cpp
HASHTABLE_OPEN_SRC = new_structures/open_hash/open_hash.cpp
TREE_SRC = new_structures/tree/fullbintree.cpp

# Все исполняемые файлы
TASKS = task1.exe task2.exe task3.exe task4.exe task5.exe task6.exe

all: $(TASKS)

# Задание 1: использует стек
task1.exe: tasks/task1_infix_to_postfix.cpp $(STACK_SRC)
	$(CXX) $(CXXFLAGS) tasks/task1_infix_to_postfix.cpp $(STACK_SRC) -o task1.exe

# Задание 2: использует хеш-таблицу
task2.exe: tasks/task2_set_operations.cpp $(HASHTABLE_SRC)
	$(CXX) $(CXXFLAGS) tasks/task2_set_operations.cpp $(HASHTABLE_SRC) -o task2.exe

# Задание 3: использует хеш-таблицу
task3.exe: tasks/task3_set_extended_operations.cpp $(HASHTABLE_SRC)
	$(CXX) $(CXXFLAGS) tasks/task3_set_extended_operations.cpp $(HASHTABLE_SRC) -o task3.exe

# Задание 4: использует массив
task4.exe: tasks/task4_subarrays.cpp $(ARRAY_SRC)
	$(CXX) $(CXXFLAGS) tasks/task4_subarrays.cpp $(ARRAY_SRC) -o task4.exe

# Задание 5: использует дерево
task5.exe: tasks/task5_tree_height.cpp $(TREE_SRC)
	$(CXX) $(CXXFLAGS) tasks/task5_tree_height.cpp $(TREE_SRC) -o task5.exe

# Задание 6: самописное дерево (никакие структуры не нужны)
task6.exe: tasks/task6_hash.cpp $(HASHTABLE_OPEN_SRC)
	$(CXX) $(CXXFLAGS) tasks/task6_hash.cpp $(HASHTABLE_OPEN_SRC) -o task6.exe

task7.exe: tasks/task6_hashtble.cpp $(HASHTABLE_SRC)
	$(CXX) $(CXXFLAGS) tasks/task6_hashtble.cpp $(HASHTABLE_SRC) -o task7.exe

clean:
	rm -f $(TASKS) *.o

.PHONY: all clean

task7.exe: tasks/task7_compare_hash.cpp new_structures/hashtable/hashtable.cpp new_structures/open_hash/open_hash.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) tasks/task7_compare_hash.cpp new_structures/hashtable/hashtable.cpp new_structures/open_hash/open_hash.cpp -o task7.exe

all: task1.exe task2.exe task3.exe task4.exe task5.exe task6.exe task7.exe
