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
local succ, value = leveldb.getInteger('helloInteger);

leveldb.setBool('helloBool', true);
local succ, value = leveldb.getDouble('helloBool');

leveldb.setVector('helloVector', Vector(1.3,2.5,3.8));
local succ, value = leveldb.getVector('helloVector');

leveldb.setAngle('helloAngle', Angle(1.3,2.5,3.8));
local succ, value = leveldb.getAngle('helloAngle');
```

