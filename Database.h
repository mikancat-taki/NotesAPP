#pragma once
#include <string>
#include <vector>

struct Note {
    int id;
    std::string title;
    std::string body;
    std::string translated;
    std::string category;
};

class Database {
public:
    Database(const std::string& dbPath);
    void saveNote(const Note& note);
    std::vector<Note> getNotes(const std::string& keyword = "");
    void deleteNoteById(int id);

private:
    std::string path;
    void exec(const std::string& sql);
};
