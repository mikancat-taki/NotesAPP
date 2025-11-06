#include "Database.h"
#include <sqlite3.h>
#include <iostream>

Database::Database(const std::string& dbPath) : path(dbPath) {
    sqlite3* db;
    if (sqlite3_open(path.c_str(), &db) == SQLITE_OK) {
        const char* sql = "CREATE TABLE IF NOT EXISTS notes("
                          "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                          "title TEXT,"
                          "body TEXT,"
                          "translated TEXT,"
                          "category TEXT);";
        sqlite3_exec(db, sql, nullptr, nullptr, nullptr);
    }
    sqlite3_close(db);
}

void Database::saveNote(const Note& note) {
    sqlite3* db;
    sqlite3_open(path.c_str(), &db);
    std::string sql = "INSERT INTO notes (title, body, translated, category) VALUES ('" +
        note.title + "','" + note.body + "','" + note.translated + "','" + note.category + "');";
    sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    sqlite3_close(db);
}

std::vector<Note> Database::getNotes(const std::string& keyword) {
    sqlite3* db;
    sqlite3_open(path.c_str(), &db);
    std::vector<Note> notes;
    std::string sql = "SELECT id, title, body, translated, category FROM notes";
    if (!keyword.empty())
        sql += " WHERE title LIKE '%" + keyword + "%' OR body LIKE '%" + keyword + "%';";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Note n;
        n.id = sqlite3_column_int(stmt, 0);
        n.title = (const char*)sqlite3_column_text(stmt, 1);
        n.body = (const char*)sqlite3_column_text(stmt, 2);
        n.translated = (const char*)sqlite3_column_text(stmt, 3);
        n.category = (const char*)sqlite3_column_text(stmt, 4);
        notes.push_back(n);
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return notes;
}

void Database::deleteNoteById(int id) {
    sqlite3* db;
    sqlite3_open(path.c_str(), &db);
    std::string sql = "DELETE FROM notes WHERE id = " + std::to_string(id) + ";";
    sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
    sqlite3_close(db);
}
