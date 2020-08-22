#include "db_repo.h"


template <class T>
void CLIAppRepo<T> :: connect(){
	int err = sqlite3_open("db_todo_cli", &db);
	if(err){
		std::cout<<"error happened\n";
	}
	else std::cout<<"Successfully joined!\n";
}

template <class T>
void CLIAppRepo<T> :: close(){
	std::cout<<"Database closed!\n";
	sqlite3_close(db);
}


template <typename T>
void* convert_to_stav(char* type, std::vector<T>& vec){

	struct sql_type_and_vector* stav = new sql_type_and_vector;
	stav->type = type;
	stav->vec = static_cast<void*>(&vec);
	
	return static_cast<void*>(stav);
}

static int callback(void *param, int argc, char **argv, char **azColName){

	std::unordered_map<std::string, char*> map;
	for(int i=0; i<argc; ++i)
		map[azColName[i]] = argv[i]? argv[i]: nullptr;

	struct sql_type_and_vector* stav = static_cast<struct sql_type_and_vector*>(param);
	std::string type = stav->type;

	if(type == "cat"){
		std::vector<category>* ct = static_cast<std::vector<category>*>(stav->vec);
		category c;
		c.fill_category(map);
		ct->push_back(c);
	}else if(type == "m_todo"){	
		std::vector<m_todo>* mt = static_cast<std::vector<m_todo>*>(stav->vec);
	}else if(type == "proj"){
		std::vector<project>* pr = static_cast<std::vector<project>*>(stav->vec);
	}

	return 0;
}

// //////////////////////////////////////////////
// ////////////////// CATEGORY //////////////////
// //////////////////////////////////////////////


void CatRepo :: save(category* data){
	std::string title = data->get_title();
	std::string description = data->get_desc();
	std::cout<<"title= "<<title<<"\n";
	std::cout<<"description= "<<description<<"\n";
	std::string sql = "INSERT INTO CATEGORY(title, description) VALUES ('"+title+"', '"+description+"');";
	this->connect();
	char* err = 0;
	// db, sql, callback, (void*)data, errMsg
	int rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &err);
	//std::cout<<"error --> "<<*err<<"\n";
	// Check rc
	// if(rc != SQLite.OK) -> .....
	this->close();
} 

category CatRepo :: remove(category* data) {
	return *data;
}


category CatRepo :: update(category* old, category* _new) {
	return *old;
}

category CatRepo :: find(category* similar) {
	char* err = 0;
	
	return *similar;
}

category CatRepo :: find(int id) {
	char* err = 0;

	this->connect();
//	std::cout<<"inside category\n";
	std::string sql = "SELECT * FROM CATEGORY WHERE id="+std::to_string(id)+";";
	category* c = new category;
	

	this->categories.clear();
	int rc= sqlite3_exec(db, sql.c_str(), callback, convert_to_stav("cat", this->categories), &err);
	//std::cout<<"\nerror= "<<err<<"\n";

	this->close();

	// if exists return first element if not return NULL
	if(this->categories.size() > 0) return this->categories[0];
	return *c;
}

category CatRepo :: find(std::string title){

	char* err = 0;

	this->connect();
	std::string sql = "SELECT * FROM CATEGORY WHERE title='" + title + "';";
	category* c = new category;

	this->categories.clear();
	int rc = sqlite3_exec(db, sql.c_str(), callback, convert_to_stav("cat", this->categories), &err);

	this->close();

	if(this->categories.size() > 0) return this->categories[0];
	return *c;
}

std::vector<category> CatRepo :: findAll() {
	char *err = 0;
	this->connect();

	std::string sql = "SELECT * FROM CATEGORY;";

	this->categories.clear();
	
	int rc = sqlite3_exec(db, sql.c_str(), callback, convert_to_stav("cat", this->categories), &err);
	//std::cout<<"\nerror= "<<err<<"\n";

	this->close();
	return this->categories;
} 


int CatRepo :: count() {
	return -1;
}

/////////////////////////////////////////////
// /////////   PROJECT  //////////////////////
// /////////////////////////////////////////

void ProjRepo :: save(project* data){

	std::string title = data->get_title();
	std::string uuid = data->get_uuid();
	std::string description = data->get_desc();
	bool archived = data->is_archived();
	bool curr = data->is_curr();	
	bool all_done = data->is_all_done();
	
	std::string sql = "INSERT INTO PROJECT(title, description, uuid, archived, curr) VALUES ('"+title+"', '"+description+"', '" + uuid + "');";
	this->connect();
	char* err = 0;
	int rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &err);
	//std::cout<<"error --> "<<*err<<"\n";
	// Check rc
	// if(rc != SQLite.OK) -> .....
	this->close();
}

project ProjRepo :: remove(project* data){
	
	// delete according to every important content
	// it doesn't matter what info they're about to give us.
	// try to find best matching part, i mean uuid's, or names.
	// names are important for projects so make name column unique.
	std::string sql = "DELETE FROM PROJECT WHERE id=";
	return *data;
}

// Not important maybe edit in the future if you need this feature.
project ProjRepo :: update(project* old, project* _new){
	return *old;
}


project ProjRepo :: find(project* similar){
	return *similar;
}

project ProjRepo :: find(int id){

	char *err = 0;
	this->connect();
	this->projects.clear();

	std::string sql = "SELECT * FROM PROJECT WHERE id="+std::to_string(id)+";";
	int rc = sqlite3_exec(db, sql.c_str(), callback, convert_to_stav("proj", this->projects), &err);

	this->close();
	if(this->projects.size() > 0) return this->projects[0];
	project p;
	return p;
}

project ProjRepo :: find(std::string title){
	
	char* err = 0;
	this->connect();
	this->projects.clear();

	// Use like sql query here.
	std::string sql = "SELECT * FROM PROJECT WHERE title LIKE '"+title+"'%;";
	int rc = sqlite3_exec(db, sql.c_str(), callback, convert_to_stav("proj", this->projects), &err);
	this->close();

	if(this->projects.size() > 0) return this->projects[0];
	project p;
	return p;
}

std::vector<project> ProjRepo :: findAll(){
	char* err = 0;
	this->connect();
	this->projects.clear();
	std::string sql = "SELECT * FROM PROJECT;";
	int rc = sqlite3_exec(db, sql.c_str(), callback, convert_to_stav("proj", this->projects), &err);

	this->close(); 	
	return this->projects;
}

int ProjRepo :: count(){
	return -1;
}


// ////////////////////////////////////
// //////////   MTODO  //////////////
// ////////////////////////////////////

void TodoRepo :: save(m_todo* data){
	const char* sql = "INSERT INTO TODO (val, val, val, val) VALUES ()";
	
}

m_todo TodoRepo :: remove(m_todo* data){
	return *data;
}

m_todo TodoRepo :: update(m_todo* old, m_todo* _new){
	return *old;
}

m_todo TodoRepo :: find(m_todo* similar){
	return *similar;
}

m_todo TodoRepo :: find(int id){
	m_todo* todo = nullptr;
	return *todo;
}

std::vector<m_todo> TodoRepo :: findAll(){
	return std::vector<m_todo>();
}

int TodoRepo :: count(){
	return -1;
}
