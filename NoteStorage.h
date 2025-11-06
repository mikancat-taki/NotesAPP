#pragma once
#include <string>
#include <vector>


struct Note {
int id;
std::string title;
std::string body;
std::string tags; // comma separated
std::string created_at;
std::string updated_at;
};


class NoteStorage {
public:
NoteStorage(const std::string &dbpath);
~NoteStorage();


bool init();
int createNote(const Note &note);
bool updateNote(const Note &note);
bool deleteNote(int id);
std::vector<Note> listNotes();
std::vector<Note> searchNotes(const std::string &query);


private:
struct Impl;
Impl* p;
};
