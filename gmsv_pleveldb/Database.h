#pragma once

#include "ILuaInterface.h"
#include "ILuaModuleManager.h"
#include <string>
#include "leveldb/c.h"
#pragma comment(lib, "libleveldb.lib")

using namespace std;

class Database {
private:
	leveldb_t *db;
	leveldb_options_t *options;
	leveldb_readoptions_t *roptions;
	leveldb_writeoptions_t *woptions;
public:
	Database(const char* path);
	~Database();

	inline void put(const string& key, const char* value, size_t length, char* err) {
		err = NULL;
		leveldb_put(db, woptions, key.c_str(), key.length(), value, length, &err);
	}
	inline bool get(const string& key, char** result, size_t& length) {
		char* err = NULL;

		*result = leveldb_get(db, roptions, key.c_str(), key.length(), &length, &err);

		if (err == NULL) {
			leveldb_free(&err);
			return true;
		}
		else {
			leveldb_free(result);
			*result = err;
			length = strlen(err);
			return false;
		}
	}
	bool remove(const string& key);

	inline leveldb_iterator_t* createIterator() {
		return leveldb_create_iterator(db, roptions);
	}

	inline leveldb_t* getDb() {
		return db;
	}
};
