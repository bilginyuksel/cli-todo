#include "model.h"
#include <vector>
#include "db_util.cpp"

template <class T>
class CLIAppRepo{
protected:
	// Create object to make connection example usage ----- db = new DbConn;
	// Delete object to close connection run destructor --- delete db;
	DbConn* db;

public: 
	virtual void save(T* data) = 0;
	virtual T remove(T* data) = 0;
	virtual T update(T* old, T* _new) = 0;
	virtual T find(T* similar) = 0;
	virtual T find(int id) = 0;
	virtual std::vector<T> findAll() = 0;
	virtual int count() = 0;
};

class TodoRepo : public CLIAppRepo<m_todo>{
public:
	void save(m_todo* data) override;
	m_todo remove(m_todo* data) override;
	m_todo update(m_todo* old, m_todo* _new) override;
	m_todo find(m_todo* similar) override;
	m_todo find(int id) override;
	std::vector<m_todo> findAll() override;
	int count() override;
};
class CatRepo : public CLIAppRepo<category>{
public:
	void save(category* data) override;
	category remove(category* data) override;
	category update(category* old, category* _new) override;
       	category find(category* similar) override;
	category find(int id) override;
	std::vector<category> findAll() override;
	int count() override;	
};
class ProjRepo : public CLIAppRepo<project>{
public:
	void save(project* data) override;
	project remove(project* data) override;
	project update(project* old, project* _new) override;
	project find(project* similar) override;
	project find(int id) override;
	std::vector<project> findAll() override;
	int count() override;
};


