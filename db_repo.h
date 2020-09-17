#include "model.h"
#include <vector>
#include "sqlite3.h"
#include <string>
#include <unordered_map>
#include <cstdio>

template <class T>
class CLIAppRepo{
protected:
	sqlite3 *db;
	void connect();
	void close();
public: 
	virtual void save(T* data) = 0;
	virtual T remove(T* daa) = 0;
	virtual T update(T* old, T* _new) = 0;
	virtual T find(T* similar) = 0;
	virtual T find(int id) = 0;
	virtual std::vector<T> findAll() = 0;
	virtual int count() = 0;
};

class TodoRepo : public CLIAppRepo<m_todo>{
private:
	std::vector<m_todo> todos;
	char* TAG = "m_todo";
public:
	void save(m_todo* data) override;
	m_todo remove(m_todo* data) override;
	void remove(int);
	m_todo update(m_todo* old, m_todo* _new) override;
	m_todo find(m_todo* similar) override;
	m_todo find(int id) override;
	std::vector<m_todo> findAll() override;
	std::vector<m_todo> find_all_todos(int);
	std::vector<m_todo> find_undone_todos(int);
	std::vector<m_todo> find_all_by_category(int);
	void make_todo_done(int);
	int count() override;
};

void add_category(int, char**, char**, std::vector<category>&);
class CatRepo : public CLIAppRepo<category>{
private:
	char* TAG = "cat";
	std::vector<category> categories;
	friend void add_category(int, char**, char**, std::vector<category>&);
public:
	void save(category* data) override;
	category remove(category* data) override;
	bool remove(int id);
	category update(category* old, category* _new) override;
    category find(category* similar) override;
	category find(int id) override;
	std::vector<category> findAll() override;
	int count() override;	

	// Find category by title - <category-name>
	category find(std::string title);
	category find_best_match(std::string title);
};

class ProjRepo : public CLIAppRepo<project>{
private:
	char* TAG = "proj";
	std::vector<project> projects;
public:
	void save(project* data) override;
	project remove(project* data) override;
	project update(project* old, project* _new) override;
	project find(project* similar) override;
	project find(int id) override;
	project find(std::string);
	std::vector<project> findAll() override;
	int count() override;
	project find_exact_match(std::string);
	void make_status_undone(int);
	void remove(std::string) throw (const char*);
	void update_branch_status();
	void remove_force(std::string);
};

class SettingsRepo : public CLIAppRepo<settings>{
private:
	char* TAG = "settings";
	void save(settings* data) override;
	settings remove(settings* data) override;
	settings update(settings* old, settings* _new) override;
	settings find(settings* similar) override;
	settings find(int id) override;
	settings find(std::string);
	std::vector<settings> findAll() override;
	int count() override;
public:
	int curr_branch();
	void update_curr_branch(int);
};

class LogRepo : public CLIAppRepo<log>{
private:
	char* TAG = "log";
	std::vector<log> logs;

	void save(log* data) override;
	log remove(log* data) override;
	log update(log* old, log* _new) override;
	log find(log* similar) override;
	log find(int id) override;
	log find(std::string);
	int count() override;
public:	
	std::vector<log> findAll() override;
};
struct sql_type_and_vector {
	char* type;
	void* vec;	
};

