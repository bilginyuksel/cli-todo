#include <iostream>
#include <ctime>

class project;
class category;
class todo;
class log;
class settings;

class project{
private:
	int id;
	std::string title;
	std::string description;

public:
	project(){}
	project(std::string title){
		this->title = title;
	}
	project(std::string title, std::string desc): project(title){
		this->description = desc;
	}

	project(int id, std::string title, std::string desc): project(title, desc){
		this->id = id;
	}

	int get_id();
	std::string get_title();
	std::string get_desc();
};

class category{
private:
	int id;
	std::string title;
	std::string description;

public:
	category(){}
	category(std::string title){
		this->title= title;
	}
	category(std::string title, std::string desc): category(title) {
		this->description = desc;
	}
	category(int id, std::string title, std::string desc): category(title, desc){
		this->id = id;
	}

	int get_id();
	std::string get_title();
	std::string get_desc();
};


class m_todo{
private:
	int id;
	int proj_id, cat_id;
	bool done, archived;
	int lvl;
	std::string todo;
	std::string description;
	time_t create_time;
	time_t last_update_time;
	project* proj;
	category* cat;

	m_todo(std::string todo){
		this->todo = todo;
		this->create_time = time(0);
		this->lvl = 0;
		this->done = false;
		this->archived = false;
		this->last_update_time = time(0);
		this->proj = nullptr;
		this->cat = nullptr;
	}

public:
	class builder;

	int get_id();
	bool is_done();
	bool is_archived();
	int get_importance_lvl();
	std::string get_create_time();
	std::string get_last_update_time();
	project* get_proj();
	category* get_cat();
};

class log{
private:
	int id;
	std::string log_type;
	std::string description;
public:
	int get_id();
	std::string get_log_type();
	std::string get_desc();
};
