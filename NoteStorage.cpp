#include "NoteStorage.h"
#include <sqlite3.h>
#include <iostream>
#include <ctime>


struct NoteStorage::Impl {
sqlite3* db = nullptr;
std::string path;
};


NoteStorage::NoteStorage(const std::string &dbpath) { p = new Impl(); p->path = dbpath; }
NoteStorage::~NoteStorage(){ if(p){ if(p->db) sqlite3_close(p->db); delete p; }}


bool NoteStorage::init(){
if(sqlite3_open(p->path.c_str(), &p->db) != SQLITE_OK) return false;
const char* sql =
"CREATE TABLE IF NOT EXISTS notes ("
"id INTEGER PRIMARY KEY AUTOINCREMENT,"
"title TEXT,"
"body TEXT,"
"tags TEXT,"
"created_at TEXT,"
"updated_at TEXT);";
char* err = nullptr;
if(sqlite3_exec(p->db, sql, nullptr, nullptr, &err) != SQLITE_OK){
std::cerr << "SQLite error: " << err << std::endl;
sqlite3_free(err);
return false;
}
return true;
}


int NoteStorage::createNote(const Note &note){
const char* sql = "INSERT INTO notes (title, body, tags, created_at, updated_at) VALUES (?, ?, ?, datetime('now'), datetime('now'));";
sqlite3_stmt* stmt;
if(sqlite3_prepare_v2(p->db, sql, -1, &stmt, nullptr) != SQLITE_OK) return -1;
sqlite3_bind_text(stmt, 1, note.title.c_str(), -1, SQLITE_TRANSIENT);
sqlite3_bind_text(stmt, 2, note.body.c_str(), -1, SQLITE_TRANSIENT);
sqlite3_bind_text(stmt, 3, note.tags.c_str(), -1, SQLITE_TRANSIENT);
if(sqlite3_step(stmt) != SQLITE_DONE){ sqlite3_finalize(stmt); return -1; }
int id = (int)sqlite3_last_insert_rowid(p->db);
sqlite3_finalize(stmt);
return id;
}


// 他メソッド（update/delete/list/search）は同様に実装してください。
