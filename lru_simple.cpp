#include <iostream>
#include <string>
#include <unordered_map>
#include <list>

using namespace std;

class LRUCache {
private:
    int capacity;
    list<pair<int, int>> cache;
    unordered_map<int, list<pair<int, int>>::iterator> map;
    
public:
    LRUCache(int cap) : capacity(cap) {}
    
    int get(int key) {
        auto it = map.find(key);
        if (it == map.end()) return -1;
        cache.splice(cache.begin(), cache, it->second);
        return it->second->second;
    }
    
    void put(int key, int value) {
        auto it = map.find(key);
        if (it != map.end()) {
            it->second->second = value;
            cache.splice(cache.begin(), cache, it->second);
        } else {
            if (cache.size() == capacity) {
                int lruKey = cache.back().first;
                map.erase(lruKey);
                cache.pop_back();
            }
            cache.push_front({key, value});
            map[key] = cache.begin();
        }
    }
};

int main() {
    int cap, Q;
    cin >> cap >> Q;
    
    LRUCache cache(cap);
    
    for (int i = 0; i < Q; i++) {
        string command;
        cin >> command;
        
        if (command == "SET") {
            int key, value;
            cin >> key >> value;
            cache.put(key, value);
        } else if (command == "GET") {
            int key;
            cin >> key;
            cout << cache.get(key) << endl;
        }
    }
    
    return 0;
}
