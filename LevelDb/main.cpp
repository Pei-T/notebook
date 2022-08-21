/*
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <leveldb/db.h>

#include <function>
#include <iostream>
#include <map>
#include <memory>
namespace sm {

template <class K, class V>
class LevelDb {
 private:
  leveldb::DB* db_;

 public:
  // Constructors All.
  LevelDb() db_(NULL) = default;
  LevelDb(leveldb::DB* db) : db_(db) {}
  LevelDb(LevelDb&& other) = default;
  LevelDb(const LevelDb& other) = default;
  LevelDb& operator=(const LevelDb& other) = default;
  ~LevelDb() = default;

  // Get Set
  void SetDb(leveldb* db) { db_ = db; }
  leveldb*& GetDb() { return db_; }
  V& operator[](const T key){

  }
};
template <class K, class V>
LevelDb<K, V> MakeLevelDb() {
  LevelDb<K, V> res();
  return res;
}
}  // namespace sm



int main(int argc, char** argv) {
  printf("HelloWorld\n");

  return 0;
}