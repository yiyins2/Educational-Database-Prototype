# Educational-Database-Prototype

### Structure

* badgerDB: our implementation
* BUSimpleDB: simpleDB from Boston University(our main reference), written in java
* CPPSimpleDB: c++ version of simpleDB
* mitSimpleDB: simpleDB from MIT, written in java
* leaderBoard: simple leaderboard, written using react and django
* proposal: our proposal



### Progress

* Simple Prototype of FileManager
* Simple Prototype of LeaderBoard
* Simple Prototype of Server (Socket based)
* Simple Prototype of Client UI



Support Operations

* CREATE

  CREATE TABLE t1 f1 f2 f3

  t1: table name

  f1, f2, f3: three field name. They have all integer type

* INSERT

  eg: INSERT INTO TABLE t1 1 4 10

  1 4 10 are for fields f1, f2 and f3

* UPDATE

  UPDATE t1 SET f1 = 7 f2 = 82 WHERE f3 < 100

* DROP

  DROP TABLE t1



## Compile
1. in directory badgerDB/
	Run Makefile to generate object file: server1 and client1
	
2. Run these two objective files

3. in client1, you can type in commands

  ```
  Successfully connected to server
  SQL> CREATE TABLE t1 f1 f2 f3
  SUCCESS
  SQL> INSERT INTO TABLE t1 1 4 10
  SUCCESS
  SQL> UPDATE t1 SET f1 = 7 f2 = 82 WHERE f3 < 100
  COMMAND NOT VALID
  SQL> SELECT * FROM TABLE t1
  --------------
  f1|f2|f3
  7|82|10
  --------------
  
  SQL> INSERT INTO TABLE t1 10 11 12
  SUCCESS
  SQL> SELECT * FROM TABLE t1
  --------------
  f1|f2|f3
  7|82|10
  10|11|12
  --------------
  
  SQL> UPDATE t1 SET f2 = 51 f3 = 92 WHERE f2 > 10                    
  COMMAND NOT VALID
  SQL> SELECT * FROM TABLE t1
  --------------
  f1|f2|f3
  7|51|92
  10|51|92
  --------------
  ```

  
