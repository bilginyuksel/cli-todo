#include "model.h"
#include <vector>
#include <sqlite3.h>
#include <string>
#include <unordered_map>

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
public:
	void save(m_todo* data) override;
	m_todo remove(m_todo* data) override;
	m_todo update(m_todo* old, m_todo* _new) override;
	m_todo find(m_todo* similar) override;
	m_todo find(int id) override;
	std::vector<m_todo> findAll() override;
	int count() override;
};

void add_category(int, char**, char**, std::vector<category>&);
class CatRepo : public CLIAppRepo<category>{
private:
	std::vector<category> categories;
	friend void add_category(int, char**, char**, std::vector<category>&);
public:
	void save(category* data) override;
	category remove(category* data) override;
	category update(category* old, category* _new) override;
    category find(category* similar) override;
	category find(int id) override;
	std::vector<category> findAll() override;
	int count() override;	

	// Find category by title - <category-name>
	category find(std::string title);
};

class ProjRepo : public CLIAppRepo<project>{
private:
	std::vector<project> projects;
public:
	void save(project* data) override;
	project remove(project* data) override;
	project update(project* old, project* _new) override;
	project find(project* similar) override;
	project find(int id) override;
	std::vector<project> findAll() override;
	int count() override;
};


struct sql_type_and_vector {
	char* type;
	void* vec;	
};

