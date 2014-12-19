gmsv_pleveldb
=============

Database wrapper for LevelDB by Google


Documentation
=============

<h6>Getters and Setters</h6>

<strong>set</strong> (key:string, value:string) -> bool:success

<strong>get</strong> (key:string) -> bool:success, string:value or error

<strong>setString</strong> alias for set

<strong>getString</strong> alias for get

<strong>setInteger</strong> (key:string, value:integer) -> bool:success

<strong>getInteger</strong> (key:string) -> bool:success, int:value or string:error

<strong>setDouble</strong> (key:string, value:double) -> bool:success

<strong>getDouble</strong> (key:string) -> bool:success, double:value or string:error

<strong>setBool</strong> (key:string, value:bool) -> bool:success

<strong>getBool</strong> (key:string) -> bool:success, bool:value or string:error

<strong>setVector</strong> (key:string, value:Vector) -> bool:success

<strong>getVector</strong> (key:string) -> bool:success, Vector:value or string:error

<strong>setAngle</strong> (key:string, value:Angle) -> bool:success

<strong>getAngle</strong> (key:string) -> bool:success, Angle:value or string:error

```lua
leveldb.setString('helloString', 'hello world');
local succ, value = leveldb.getString('helloString');

leveldb.setDouble('helloDouble', -3.1415926);
local succ, value = leveldb.getDouble('helloDouble);

leveldb.setInteger('helloInteger', -3239);
local succ, value = leveldb.getInteger('helloInteger');

leveldb.setBool('helloBool', true);
local succ, value = leveldb.getDouble('helloBool');

leveldb.setVector('helloVector', Vector(1.3,2.5,3.8));
local succ, value = leveldb.getVector('helloVector');

leveldb.setAngle('helloAngle', Angle(1.3,2.5,3.8));
local succ, value = leveldb.getAngle('helloAngle');
```

<h6>Iteration</h6>
The LevelDB wrapper provides a special iterator for iterating over key blocks in the database. A key block is considdered to be a block of all keys with the same prefix. 

<strong>leveldb.iter</strong> (string:prefix) -> function:iterator

```Lua
for key, value in leveldb.iter('rp:player')do
  print('key: '..key..'   value: '..value);
end
```
Take note that key, value will always be strings even if the datatype of the original data was a vector, double, integer, angle, or bool. The library does however provide a set of functions for converting these strings into usable lua datatypes.

<h6>Converters</h6>

<strong>toInteger</strong> (string:value) -> integer:value

<strong>toDouble</strong> (string:value) -> double:value

<strong>toBool</strong> (string:value) -> bool:value

<strong>toVector</strong> (string:value) -> Vector:value

<strong>toAngle</strong> (string:value) -> Angle:value
