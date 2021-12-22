# Details

Date : 2021-12-12 21:02:26

Directory /Users/yiyinshen/Documents/764/Educational-Database-Prototype/badgerDB

Total : 65 files,  1950 codes, 527 comments, 502 blanks, all 2979 lines

[summary](results.md)

## Files
| filename | language | code | comment | blank | total |
| :--- | :--- | ---: | ---: | ---: | ---: |
| [Makefile](/Makefile) | Makefile | 12 | 5 | 7 | 24 |
| [include/buffer.hpp](/include/buffer.hpp) | C++ | 25 | 1 | 4 | 30 |
| [include/buffer_manager.hpp](/include/buffer_manager.hpp) | C++ | 27 | 0 | 3 | 30 |
| [include/concurrency_manager.hpp](/include/concurrency_manager.hpp) | C++ | 12 | 0 | 5 | 17 |
| [include/db_client.hpp](/include/db_client.hpp) | C++ | 12 | 0 | 3 | 15 |
| [include/db_server.hpp](/include/db_server.hpp) | C++ | 22 | 8 | 6 | 36 |
| [include/field_info.hpp](/include/field_info.hpp) | C++ | 14 | 0 | 5 | 19 |
| [include/file_block_idx.hpp](/include/file_block_idx.hpp) | C++ | 12 | 0 | 4 | 16 |
| [include/file_manager.hpp](/include/file_manager.hpp) | C++ | 27 | 0 | 6 | 33 |
| [include/layout.hpp](/include/layout.hpp) | C++ | 21 | 0 | 4 | 25 |
| [include/lock_table.hpp](/include/lock_table.hpp) | C++ | 18 | 0 | 3 | 21 |
| [include/messages.hpp](/include/messages.hpp) | C++ | 59 | 18 | 25 | 102 |
| [include/page.hpp](/include/page.hpp) | C++ | 14 | 0 | 4 | 18 |
| [include/parse/create_table_data.hpp](/include/parse/create_table_data.hpp) | C++ | 14 | 0 | 4 | 18 |
| [include/parse/delete_data.hpp](/include/parse/delete_data.hpp) | C++ | 14 | 0 | 4 | 18 |
| [include/parse/drop_table_data.hpp](/include/parse/drop_table_data.hpp) | C++ | 11 | 0 | 3 | 14 |
| [include/parse/insert_data.hpp](/include/parse/insert_data.hpp) | C++ | 15 | 0 | 4 | 19 |
| [include/parse/lexer.hpp](/include/parse/lexer.hpp) | C++ | 37 | 0 | 6 | 43 |
| [include/parse/parser.hpp](/include/parse/parser.hpp) | C++ | 38 | 0 | 9 | 47 |
| [include/parse/select_data.hpp](/include/parse/select_data.hpp) | C++ | 17 | 0 | 4 | 21 |
| [include/parse/update_data.hpp](/include/parse/update_data.hpp) | C++ | 20 | 0 | 4 | 24 |
| [include/predicate.hpp](/include/predicate.hpp) | C++ | 41 | 0 | 10 | 51 |
| [include/query/constant.hpp](/include/query/constant.hpp) | C++ | 22 | 0 | 4 | 26 |
| [include/query/expression.hpp](/include/query/expression.hpp) | C++ | 17 | 0 | 4 | 21 |
| [include/query/predicate1.hpp](/include/query/predicate1.hpp) | C++ | 8 | 0 | 3 | 11 |
| [include/query/term.hpp](/include/query/term.hpp) | C++ | 8 | 0 | 3 | 11 |
| [include/query_executor.hpp](/include/query_executor.hpp) | C++ | 48 | 2 | 11 | 61 |
| [include/record.hpp](/include/record.hpp) | C++ | 16 | 0 | 5 | 21 |
| [include/schema.hpp](/include/schema.hpp) | C++ | 20 | 0 | 4 | 24 |
| [include/table.hpp](/include/table.hpp) | C++ | 25 | 0 | 7 | 32 |
| [include/transaction.hpp](/include/transaction.hpp) | C++ | 21 | 0 | 3 | 24 |
| [include/update_record.hpp](/include/update_record.hpp) | C++ | 9 | 1 | 2 | 12 |
| [src/buffer.cpp](/src/buffer.cpp) | C++ | 39 | 4 | 10 | 53 |
| [src/buffer_manager.cpp](/src/buffer_manager.cpp) | C++ | 96 | 7 | 12 | 115 |
| [src/concurrency_manager.cpp](/src/concurrency_manager.cpp) | C++ | 13 | 0 | 3 | 16 |
| [src/db_client.cpp](/src/db_client.cpp) | C++ | 54 | 7 | 12 | 73 |
| [src/db_server.cpp](/src/db_server.cpp) | C++ | 75 | 14 | 15 | 104 |
| [src/file_block_idx.cpp](/src/file_block_idx.cpp) | C++ | 14 | 0 | 3 | 17 |
| [src/file_manager.cpp](/src/file_manager.cpp) | C++ | 81 | 6 | 24 | 111 |
| [src/layout.cpp](/src/layout.cpp) | C++ | 37 | 0 | 6 | 43 |
| [src/lock_table.cpp](/src/lock_table.cpp) | C++ | 16 | 0 | 4 | 20 |
| [src/page.cpp](/src/page.cpp) | C++ | 25 | 1 | 3 | 29 |
| [src/parse/create_table_data.cpp](/src/parse/create_table_data.cpp) | C++ | 11 | 0 | 5 | 16 |
| [src/parse/delete_data.cpp](/src/parse/delete_data.cpp) | C++ | 10 | 0 | 4 | 14 |
| [src/parse/drop_table_data.cpp](/src/parse/drop_table_data.cpp) | C++ | 8 | 0 | 5 | 13 |
| [src/parse/insert_data.cpp](/src/parse/insert_data.cpp) | C++ | 11 | 0 | 5 | 16 |
| [src/parse/lexer.cpp](/src/parse/lexer.cpp) | C++ | 78 | 0 | 17 | 95 |
| [src/parse/parser.cpp](/src/parse/parser.cpp) | C++ | 123 | 20 | 26 | 169 |
| [src/parse/select_data.cpp](/src/parse/select_data.cpp) | C++ | 15 | 0 | 8 | 23 |
| [src/parse/update_data.cpp](/src/parse/update_data.cpp) | C++ | 17 | 0 | 6 | 23 |
| [src/query/constant.cpp](/src/query/constant.cpp) | C++ | 48 | 0 | 10 | 58 |
| [src/query/expression.cpp](/src/query/expression.cpp) | C++ | 13 | 0 | 6 | 19 |
| [src/query/predicate1.cpp](/src/query/predicate1.cpp) | C++ | 1 | 0 | 1 | 2 |
| [src/query/term.cpp](/src/query/term.cpp) | C++ | 0 | 0 | 1 | 1 |
| [src/query_executor.cpp](/src/query_executor.cpp) | C++ | 69 | 397 | 66 | 532 |
| [src/record.cpp](/src/record.cpp) | C++ | 11 | 4 | 3 | 18 |
| [src/schema.cpp](/src/schema.cpp) | C++ | 30 | 2 | 6 | 38 |
| [src/table.cpp](/src/table.cpp) | C++ | 166 | 17 | 32 | 215 |
| [src/transaction.cpp](/src/transaction.cpp) | C++ | 42 | 5 | 8 | 55 |
| [tests/lexer_test.cpp](/tests/lexer_test.cpp) | C++ | 20 | 0 | 4 | 24 |
| [tests/parser_test.cpp](/tests/parser_test.cpp) | C++ | 69 | 0 | 11 | 80 |
| [tests/test_buffer.cpp](/tests/test_buffer.cpp) | C++ | 26 | 6 | 4 | 36 |
| [tests/test_client.cpp](/tests/test_client.cpp) | C++ | 7 | 0 | 1 | 8 |
| [tests/test_server.cpp](/tests/test_server.cpp) | C++ | 7 | 0 | 1 | 8 |
| [tests/test_transaction.cpp](/tests/test_transaction.cpp) | C++ | 42 | 2 | 7 | 51 |

[summary](results.md)