#include <unordered_map>
#include <string>

using namespace std;

class inMemoryDb {

  public: 
    int get(string key);
    void put(string key, int val);
    void begin_transaction();
    void commit();
    void rollback();

  private:
    unordered_map<string, int> db;
    bool inProgress = false;
    unordered_map<string, int> tempDb;
};
