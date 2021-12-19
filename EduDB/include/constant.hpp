#pragma once

#include <string>
using namespace  std;

// Test Server
static const string db_dir = "./db";
static const int server_port = 8085;

/* Test client */
static const int client_port = 8085;
static const string server_address = "127.0.0.1";

/*  db_server relevant message and log */
static const string failed_to_create_socket_msg = "server: create socket failed";
static const string failed_to_attach_socket_msg = "server: failed to attach socket to server fd";
static const string failed_to_bind_socket_msg = "server: failed to bind socket";
static const string failed_to_listen_msg = "sever: failed to listen";
static const string failed_to_accept_msg = "sever: failed to accept socket";
static const string received_request_msg = "Request from %d: %s\n";

/* db_client relevant message and log */
static const string test_connection_cmd = "Hello";
static const string stop_server_cmd = "exit";
static const string connection_failed_msg = "Connection failed";
static const string successfully_connected_msg = "Successfully connected to server";
static const string sql_command_line_info = "SQL >";

static const int CONNECTION_FAILED = -1;

/* query_executor error code */
static const int SUCCESS = 0;
// Predicate
static const int PREDICATE_NUMBER_INVALID = -1;
static const int PREDICARE_FIELD_NOT_FOUND = -2;
static const int PREDICATE_INVALID = -3;
// Insert
static const int TABLE_NOT_EXIST = -4;
static const int TABLE_SCHEMA_NOT_EXIST = -5;
static const int INSERT_RECORD_FIELD_SIZE_INVALID = -6;
// Create table
static const int FAILED_TO_CREATE_TABLE = -7;
static const int DUPLICATE_FIELD = -8;
// Select
static const int OPERATOR_NOT_VALID = -9;

// Messages
static const string predicate_field_not_found_msg = "Predicate field not found";
static const string predicate_field_not_number_msg = "Predicate field not number";
static const string predicate_invalid = "Predicate invalid";
static const string select_field_not_found_msg = "Select field not found";
static const string update_field_not_found_msg = "Update field not found";
static const string success_msg = "SUCCESS";
static const string unhandled_msg = "Unhandled";
static const string insert_record_field_value_not_int_msg = "Failed: field value not int";
static const string table_not_exist_msg = "Failed: table not exist";
static const string schema_not_exist_msg = "Failed: table schema not exist";
static const string failed_to_create_table_msg = "Failed to create table";
static const string command_not_valid_msg = "Failed: Command not valid";
static const string operator_not_valid_msg = "Failed: operator not valid";
static const string duplicate_field_declaration_msg = "Failed: duplicate field declaration";

/* layout */
static const int TABLE_DUPLICATE = -10;
static const string table_duplicate_msg = "Failed: Table exist";

/* Schema */
static const int FIELD_NOT_EXIST = -11;

/* Table */
static const int FAILED_TO_READ_BLOCK = -12;
static const int FAILED_TO_WRITE_BLOCK = -13;
static const string failed_to_read_block_msg = "Failed to read block";
static const string failed_to_write_block_msg = "Failed to write block";