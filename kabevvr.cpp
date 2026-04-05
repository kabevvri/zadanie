#include <iostream>
#include <winsqlite/winsqlite3.h>
#pragma comment(lib, "winsqlite3.lib")
using namespace std;
int callback(void*, int argc, char** argv, char**) {
	for (int i = 0; i < argc; i++) {
		cout << (argv[i] ? argv[i] : "NULL") << " ";
	}
	cout << endl;
	return 0;
}
int main() {
	sqlite3* db;
	sqlite3_stmt* stmt;
	int rc = sqlite3_open("example.db", &db);
	if (rc != SQLITE_OK) {
		cout << "Error" << endl;
		return 1;
	}   
	const char* createTable = "CREATE TABLE IF NOT EXISTS users ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT ,"
		"name TEXT NOT NULL,"
		"age INTEGER,"
		"email TEXT UNIQUE);";
	rc = sqlite3_exec(db, createTable, nullptr, nullptr, nullptr);
	const char* sql = "INSERT INTO users (name, age, email) VALUES (?, ?, ?)";
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
	string name = "Alex";
	int age = 22;
	string email = "alex@mail.com";
	sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_int(stmt, 2, age);
	sqlite3_bind_text(stmt, 3, email.c_str(), -1, SQLITE_STATIC);
	rc = sqlite3_step(stmt);
	const char* selectSql = "SELECT * FROM users;";
	rc = sqlite3_exec(db, selectSql, callback, nullptr, nullptr);
	sqlite3_close(db);
}