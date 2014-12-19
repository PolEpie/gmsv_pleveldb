#pragma once

#include "ILuaModuleManager.h"
#include "ILuaInterface.h"

typedef unsigned __int64 uint64_t;
extern uint64_t MurmurHash64B(const void * key, int len, unsigned int seed);
extern LUA_FUNCTION(MurmurHash);