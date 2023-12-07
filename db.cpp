#include "db.h"
#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;

int inMemoryDb::get(string key) {
  return db[key];
}

void inMemoryDb::put(string key, int val) {
  if (!inProgress) {
    throw runtime_error("Exception: no transaction in progress");
  }

  tempDb[key] = val;
}

void inMemoryDb::begin_transaction() {
  inProgress = true;
}

void inMemoryDb::commit() {
  if (!inProgress) {
    throw runtime_error("Exception: no transaction in progress");
  }

  // apply changes from tempDb to db.
  auto it = tempDb.begin();
  while (it != tempDb.end()) {
    db[it->first] = it->second;
    it++;
  }

  inProgress = false;
}

void inMemoryDb::rollback() {
  if (!inProgress) {
    throw runtime_error("Exception: no transaction in progress");
  }

  tempDb.clear();
  inProgress = false;
}

int main() {
  // USE CLASS FUNCTIONS HERE
  inMemoryDb database;

  // throws error because no transaction
  //database.put("A", 1);

  // returns null
  int response = database.get("A");
  cout << "Response: " << response << endl;

  // start transaction
  database.begin_transaction();

  database.put("hello", 13);
  database.commit();

  response = database.get("hello");
  cout << "Response: " << response << endl;
}