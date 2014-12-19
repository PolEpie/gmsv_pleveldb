// Skip rarely used Windows API functions
#define WIN32_LEAN_AND_MEAN
#define NO_SDK
#include <string>
#include <Windows.h>

#include "main.h"

#include "Database.h"
#include "DatabaseIterator.h"
#include "Vector.h"
#include "Murmer.h"

using namespace GarrysMod::Lua;

GMOD_MODULE(Init, Shutdown);

void println(ILuaInterface& g_Lua, const char* msg) {
	g_Lua.Push(g_Lua.GetGlobal("print"));
	g_Lua.Push(msg);
	g_Lua.Call(1, 0);
}

Database db("garrysmod/x_leveldb");


LUA_FUNCTION(db_set) {
	ILuaInterface* g_Lua = Lua();
	g_Lua->CheckType(1, Type::STRING);

	size_t keyLength;
	const char* key = g_Lua->GetString(1, &keyLength);

	int type = g_Lua->GetType(2);

	char* err = NULL;


	if (type == Type::STRING) {
		size_t valueLength;
		const char* value = g_Lua->GetString(2, &valueLength);
		db.put(key, keyLength, value, valueLength, err);
	}
	else if (type == Type::NUMBER) {
		double value = g_Lua->GetNumber(2);
		db.put(key, keyLength, (char*)&value, sizeof value, err);
	}
	else if (type == Type::VECTOR) {
		Vector* vec = (Vector*)*g_Lua->GetUserDataPtr(2);
		db.put(key, keyLength, (char*) vec, sizeof(Vector), err);
	}
	else if (type == Type::ANGLE) {
		Angle* ang = (Angle*)*g_Lua->GetUserDataPtr(2);
		db.put(key, keyLength, (char*)ang, sizeof(Angle), err);
	}
	else if (type == Type::BOOL) {
		bool value = g_Lua->GetBool(2);
		db.put(key, keyLength, (char*)&value, sizeof value, err);
	}
	else {
		g_Lua->Error("expected data arg #2, got nil");
	}

	if (err != NULL) {
		g_Lua->Push(false);
		g_Lua->Push(err);
		leveldb_free(&err);
		return 2;
	}
	else {
		leveldb_free(&err);
		g_Lua->Push(true);
		return 1;
	}
}

LUA_FUNCTION(db_setString) {
	ILuaInterface* g_Lua = Lua();
	g_Lua->CheckType(1, Type::STRING);
	g_Lua->CheckType(2, Type::STRING);

	size_t keyLength;
	const char* key = g_Lua->GetString(1, &keyLength);

	char* err = NULL;


	size_t valueLength;
	const char* value = g_Lua->GetString(2, &valueLength);
	db.put(key, keyLength, value, valueLength, err);

	if (err != NULL) {
		g_Lua->Push(false);
		g_Lua->Push(err);
		leveldb_free(&err);
		return 2;
	}
	else {
		leveldb_free(&err);
		g_Lua->Push(true);
		return 1;
	}
}

LUA_FUNCTION(db_setDouble) {
	ILuaInterface* g_Lua = Lua();
	g_Lua->CheckType(1, Type::STRING);
	g_Lua->CheckType(2, Type::NUMBER);

	size_t keyLength;
	const char* key = g_Lua->GetString(1, &keyLength);

	char* err = NULL;

	double value = g_Lua->GetNumber(2);
	db.put(key, keyLength, (char*)&value, sizeof(value), err);

	if (err != NULL) {
		g_Lua->Push(false);
		g_Lua->Push(err);
		leveldb_free(&err);
		return 2;
	}
	else {
		leveldb_free(&err);
		g_Lua->Push(true);
		return 1;
	}
}

LUA_FUNCTION(db_setInteger) {
	ILuaInterface* g_Lua = Lua();
	g_Lua->CheckType(1, Type::STRING);
	g_Lua->CheckType(2, Type::NUMBER);

	size_t keyLength;
	const char* key = g_Lua->GetString(1, &keyLength);

	char* err = NULL;

	int value = g_Lua->GetNumber(2);
	db.put(key, keyLength, (char*)&value, sizeof value, err);

	if (err != NULL) {
		g_Lua->Push(false);
		g_Lua->Push(err);
		leveldb_free(&err);
		return 2;
	}
	else {
		leveldb_free(&err);
		g_Lua->Push(true);
		return 1;
	}
}

LUA_FUNCTION(db_setVector) {
	ILuaInterface* g_Lua = Lua();
	g_Lua->CheckType(1, Type::STRING);
	g_Lua->CheckType(2, Type::NUMBER);

	size_t keyLength;
	const char* key = g_Lua->GetString(1, &keyLength);

	char* err = NULL;

	Vector* vec = (Vector*)*g_Lua->GetUserDataPtr(2);
	db.put(key, keyLength, (char*)vec, sizeof(Vector), err);

	if (err != NULL) {
		g_Lua->Push(false);
		g_Lua->Push(err);
		leveldb_free(&err);
		return 2;
	}
	else {
		leveldb_free(&err);
		g_Lua->Push(true);
		return 1;
	}
}

LUA_FUNCTION(db_setAngle) {
	ILuaInterface* g_Lua = Lua();
	g_Lua->CheckType(1, Type::STRING);
	g_Lua->CheckType(2, Type::ANGLE);

	size_t keyLength;
	const char* key = g_Lua->GetString(1, &keyLength);

	char* err = NULL;

	Angle* ang = (Angle*)*g_Lua->GetUserDataPtr(2);
	db.put(key, keyLength, (char*)ang, sizeof(Angle), err);

	if (err != NULL) {
		g_Lua->Push(false);
		g_Lua->Push(err);
		leveldb_free(&err);
		return 2;
	}
	else {
		leveldb_free(&err);
		g_Lua->Push(true);
		return 1;
	}
}

LUA_FUNCTION(db_setBool) {
	ILuaInterface* g_Lua = Lua();
	g_Lua->CheckType(1, Type::STRING);
	g_Lua->CheckType(2, Type::ANGLE);

	size_t keyLength;
	const char* key = g_Lua->GetString(1, &keyLength);

	char* err = NULL;

	bool value = g_Lua->GetBool(2);
	db.put(key, keyLength, (char*)&value, sizeof value, err);

	if (err != NULL) {
		g_Lua->Push(false);
		g_Lua->Push(err);
		leveldb_free(&err);
		return 2;
	}
	else {
		leveldb_free(&err);
		g_Lua->Push(true);
		return 1;
	}
}

LUA_FUNCTION(db_getString) {
	ILuaInterface* g_Lua = Lua();
	g_Lua->CheckType(1, Type::STRING);

	size_t keyLength;
	const char* key = g_Lua->GetString(1, &keyLength);

	char* result = NULL;
	size_t length;
	bool success = db.get(key, keyLength, &result, length);

	g_Lua->Push(success);
	g_Lua->Push(result, length);

	leveldb_free(&result);
	
	return 2;
}

LUA_FUNCTION(db_getDouble) {
	ILuaInterface* g_Lua = Lua();
	g_Lua->CheckType(1, Type::STRING);

	size_t keyLength;
	const char* key = g_Lua->GetString(1, &keyLength);

	char* result = NULL;
	size_t length;
	bool success = db.get(key, keyLength, &result, length);
	
	if (success) {
		if (length == sizeof(double)) {
			double* result_d = (double*) result;
			g_Lua->Push(true);
			g_Lua->Push(*result_d);
		}
		else {
			g_Lua->Push(false);
			g_Lua->Push("value could not be converted to double");
		}
	}
	else {
		g_Lua->Push(false);
		g_Lua->Push(result, length);
	}

	leveldb_free(&result);

	return 2;
}

LUA_FUNCTION(db_getInteger) {
	ILuaInterface* g_Lua = Lua();
	g_Lua->CheckType(1, Type::STRING);

	size_t keyLength;
	const char* key = g_Lua->GetString(1, &keyLength);

	char* result = NULL;
	size_t length;
	bool success = db.get(key, keyLength, &result, length);

	if (success) {
		if (length == sizeof(int)) {
			int* result_i = (int*)result;
			g_Lua->Push(true);
			g_Lua->Push(*result_i);
		}
		else {
			g_Lua->Push(false);
			g_Lua->Push("value could not be converted to double");
		}
	}
	else {
		g_Lua->Push(false);
		g_Lua->Push(result, length);
	}

	leveldb_free(&result);

	return 2;
}

LUA_FUNCTION(db_getBool) {
	ILuaInterface* g_Lua = Lua();
	g_Lua->CheckType(1, Type::STRING);

	size_t keyLength;
	const char* key = g_Lua->GetString(1, &keyLength);

	char* result = NULL;
	size_t length;
	bool success = db.get(key, keyLength, &result, length);

	if (success) {
		if (length == sizeof(bool)){
			bool* result_b = (bool*)result;
			g_Lua->Push(true);
			g_Lua->Push(*result_b);
		}
		else {
			g_Lua->Push(false);
			g_Lua->Push("value could not be converted to bool");
		}
	}
	else {
		g_Lua->Push(false);
		g_Lua->Push(result, length);
	}

	leveldb_free(&result);

	return 2;
}

LUA_FUNCTION(db_getVector) {
	ILuaInterface* g_Lua = Lua();
	g_Lua->CheckType(1, Type::STRING);

	size_t keyLength;
	const char* key = g_Lua->GetString(1, &keyLength);

	char* result = NULL;
	size_t length;
	bool success = db.get(key, keyLength, &result, length);

	if (success) {
		if (length == sizeof(Vector)) {
			Vector* result_v = (Vector*)result;

			g_Lua->Push(true);

			Vector* toPush = new Vector(result_v->x, result_v->y, result_v->z);
			ILuaObject* meta = g_Lua->GetMetaTable("Vector", GLua::TYPE_VECTOR);
				g_Lua->PushUserData(meta, toPush, GLua::TYPE_VECTOR);
			meta->UnReference();
		}
		else {
			g_Lua->Push(false);
			g_Lua->Push("value could not be converted to Vector");
		}
	}
	else {
		g_Lua->Push(false);
		g_Lua->Push(result, length);
	}

	leveldb_free(&result);

	return 2;
}

LUA_FUNCTION(db_getAngle) {
	ILuaInterface* g_Lua = Lua();
	g_Lua->CheckType(1, Type::STRING);

	size_t keyLength;
	const char* key = g_Lua->GetString(1, &keyLength);

	char* result = NULL;
	size_t length;
	bool success = db.get(key, keyLength, &result, length);

	if (success) {
		if (length == sizeof(Angle)) {
			Angle* result_v = (Angle*)result;

			g_Lua->Push(true);

			Angle* toPush = new Angle(result_v->p, result_v->y, result_v->r);
			ILuaObject* meta = g_Lua->GetMetaTable("Angle", GLua::TYPE_ANGLE);
			g_Lua->PushUserData(meta, toPush, GLua::TYPE_ANGLE);
			meta->UnReference();
		}
		else {
			g_Lua->Push(false);
			g_Lua->Push("value could not be converted to Angle");
		}
	}
	else {
		g_Lua->Push(false);
		g_Lua->Push(result, length);
	}

	leveldb_free(&result);

	return 2;
}

LUA_FUNCTION(database_delete) {
	ILuaInterface* g_Lua = Lua();
	g_Lua->CheckType(1, Type::STRING);

	string key = g_Lua->GetString(1);
	bool success = db.remove(key);

	g_Lua->Push(success);
	return 1;
}

/*
	ITERATING
*/
LUA_FUNCTION(fn_iter) {
	ILuaInterface* g_Lua = Lua();

	DatabaseIterator* iter = (DatabaseIterator*)*g_Lua->GetUserDataPtr(lua_upvalueindex(1));
	
	if (iter->valid()) { // check we haven't hit the end of the database
		size_t length;

		const char* key = iter->getKey(&length);
		
		if (iter->inRange(key, length)) { // kill iteration if we've walked off the key range
			g_Lua->Push(key, length);
			const char* value = iter->getValue(&length);
			g_Lua->Push(value, length);

			iter->next();
			return 2;
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}

	return 1;
}

LUA_FUNCTION(new_iter) {
	ILuaInterface* g_Lua = Lua();
	LUA->CheckType(1, Type::STRING);

	string key = LUA->GetString(1);
	
	g_Lua->Push(key.c_str(), key.length());
	LUA->PushCClosure(fn_iter, 1);

	DatabaseIterator* iter = new DatabaseIterator(db.getDb(), key);
	iter->seek(key.c_str(), key.length());

	ILuaObject* iter_obj = g_Lua->NewUserData(g_IterMeta);
		iter_obj->SetUserData(iter, DB_ITER_ID);
		g_Lua->Push(iter_obj);
	iter_obj->UnReference();

	LUA->PushCClosure(fn_iter, 1);

	return 1;
}

/*
STRING CONVERSIONS
*/
LUA_FUNCTION(strToDouble) {
	ILuaInterface* g_Lua = Lua();
	g_Lua->CheckType(1, Type::STRING);

	size_t length;
	const char* val = g_Lua->GetString(1, &length);

	if (length == sizeof(double)){
		double* val_d = (double*) val;
		g_Lua->Push(*val_d);
		return 1;
	}
	else {
		return 0;
	}
}

LUA_FUNCTION(strToInteger) {
	ILuaInterface* g_Lua = Lua();
	g_Lua->CheckType(1, Type::STRING);

	size_t length;
	const char* val = g_Lua->GetString(1, &length);

	if (length == sizeof(int)){
		const int* val_i = (const int*) val;
		g_Lua->Push(*val_i);
		return 1;
	}
	else {
		return 0;
	}
}

LUA_FUNCTION(strToVector) {
	ILuaInterface* g_Lua = Lua();
	g_Lua->CheckType(1, Type::STRING);

	size_t length;
	const char* val = g_Lua->GetString(1, &length);

	if (length == sizeof(Vector)){
		const Vector* val_v = (const Vector*)val;
		Vector* toPush = new Vector(val_v->x, val_v->y, val_v->z);
		ILuaObject* meta = g_Lua->GetMetaTable("Vector", GLua::TYPE_VECTOR);
			g_Lua->PushUserData(meta, toPush, GLua::TYPE_VECTOR);
		meta->UnReference();
		return 1;
	}
	else {
		return 0;
	}
}


LUA_FUNCTION(strToAngle) {
	ILuaInterface* g_Lua = Lua();
	g_Lua->CheckType(1, Type::STRING);

	size_t length;
	const char* val = g_Lua->GetString(1, &length);

	if (length == sizeof(Angle)){
		const Angle* val_a = (const Angle*)val;
		Angle* toPush = new Angle(val_a->p, val_a->y, val_a->r);
		ILuaObject* meta = g_Lua->GetMetaTable("Angle", GLua::TYPE_ANGLE);
		g_Lua->PushUserData(meta, toPush, GLua::TYPE_ANGLE);
		meta->UnReference();
		return 1;
	}
	else {
		return 0;
	}
}

LUA_FUNCTION(strToBool) {
	ILuaInterface* g_Lua = Lua();
	g_Lua->CheckType(1, Type::STRING);

	size_t length;
	const char* val = g_Lua->GetString(1, &length);

	if (length == sizeof(bool)){
		bool* val_b = (bool*) val;
		g_Lua->Push(*val_b);
		return 1;
	}
	else {
		return 0;
	}
}


int Init(lua_State *L)
{
	ILuaInterface* g_Lua = Lua();
	ILuaBase* g_LuaBase = L->luabase;

	println(*g_Lua, "================================================");
	println(*g_Lua, "== Loaded LevelDB interface by thelastpenguin ==");
	println(*g_Lua, "== Running version 1.0.0                      ==");
	println(*g_Lua, "== - thanks to ;Meepen™ for C++ knoledge      ==");
	println(*g_Lua, "================================================");
	println(*g_Lua, "     Compiled on... " __DATE__ ", " __TIME__ "");

	DatabaseIterator::initLua(*g_Lua);


	ILuaObject* funcTable = g_Lua->GetNewTable();

	funcTable->SetMember("set", db_setString);
	funcTable->SetMember("get", db_getString);
	
	funcTable->SetMember("setAny", db_set);

	funcTable->SetMember("setString",	db_setString);
	funcTable->SetMember("setDouble",	db_setDouble);
	funcTable->SetMember("setVector",	db_setVector);
	funcTable->SetMember("setAngle",	db_setAngle);
	funcTable->SetMember("setBool",		db_setBool);
	funcTable->SetMember("setInteger",	db_setInteger);

	funcTable->SetMember("getDouble",	db_getDouble);
	funcTable->SetMember("getString",	db_getString);
	funcTable->SetMember("getVector",	db_getVector);
	funcTable->SetMember("getAngle",	db_getAngle);
	funcTable->SetMember("getBool",		db_getBool);
	funcTable->SetMember("getInteger",	db_getInteger);

	funcTable->SetMember("toDouble", strToDouble);
	funcTable->SetMember("toInteger", strToInteger);
	funcTable->SetMember("toVector", strToVector);
	funcTable->SetMember("toAngle", strToAngle);
	funcTable->SetMember("toBool", strToBool);

	funcTable->SetMember("iter", new_iter);
	
	funcTable->SetMember("mhash", MurmurHash);

	funcTable->SetMember("delete", database_delete);

	g_Lua->SetGlobal("leveldb", funcTable);
	g_Lua->SetGlobal("lvldb", funcTable);
	funcTable->UnReference();


	g_Lua->Push(g_Lua->GetGlobal("RunString"));

	// adds s_ versions of methods. Basically makes them return value or nil on failure, no error returned.
	g_Lua->Push(g_Lua->GetGlobal("RunString"));
	g_Lua->Push(
			"local getInteger=lvldb.getInteger;function lvldb.s_getInteger(a)local b,c=getInteger(a)"
			"return b and c or nil end;local d=lvldb.getDouble;function lvldb.s_getDouble(a)local b,"
			"c=getDouble(a)return b and c or nil end;local d=lvldb.getAngle;function lvldb.s_getAngl"
			"e(a)local b,c=getAngle(a)return b and c or nil end;local d=lvldb.getVector;function lvl"
			"db.s_getVector(a)local b,c=getVector(a)return b and c or nil end;local d=lvldb.getBool;"
			"function lvldb.s_getBool(a)local b,c=getBool(a)return b and c or nil end;local d=lvldb."
			"getString;function lvldb.s_getString(a)local b,c=getString(a)return b and c or nil end"
		);
	g_Lua->Call(1, 0);

	g_Lua->Push(g_Lua->GetGlobal("RunString"));
	g_Lua->Push(
			"local getInteger,setInteger=lvldb.getInteger,lvldb.setInteger;function lvldb.addInteger"
			"(a,b)local c,d=getInteger(a)if c then setInteger(a,d+b)else setInteger(a,b)end end;loca"
			"l getDouble,setDouble=lvldb.getDouble,lvldb.setDouble;function lvldb.addDouble(a,b)loca"
			"l c,d=getDouble(a)if c then setDouble(a,d+b)else setDouble(a,b)end end"
		);
	g_Lua->Call(1, 0);

	return 0;
}

// Shutdown
int Shutdown(lua_State *L)
{
	return 0;
}
