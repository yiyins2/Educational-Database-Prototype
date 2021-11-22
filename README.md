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

## Compile
1. in directory badgerDB/
	Run Makefile to generate object file: server1 and client1
2. Run these two objective files
3. in client1, you can type in commands:
	Successfully connected to server
	SQL> CREATE TABLE t1 f1
	SUCCESS
	SQL> INSERT INTO TABLE t1 3
	SUCCESS
	SQL> exit
4. Notice: Currently there is still something wrong with file operation: if you insert two records, the first one will be overwritten
	I'll fix it asap.
