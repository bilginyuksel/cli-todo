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
	std::cout<<"inside category\n";
	std::string sql = "SELECT * FROM CATEGORY WHERE id="+std::to_string(id)+";";
	category* c = new category;
	

	int rc= sqlite3_exec(db, sql.c_str(), callback, nullptr, &err);
	//std::cout<<"\nerror= "<<err<<"\n";

	this->close();

	return *c;
}


std::vector<category> CatRepo :: findAll() {
	char *err = 0;
	this->connect();

	std::string sql = "SELECT * FROM CATEGORY;";

	this->categories.clear();
//	struct cat_node* head = nullptr;
	struct sql_type_and_vector* stav = new sql_type_and_vector;
	stav->type = "cat";
	stav->vec = static_cast<void*>(&this->categories);
	
	int rc = sqlite3_exec(db, sql.c_str(), callback, static_cast<void*>(stav), &err);
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

}

project ProjRepo :: remove(project* data){
	return *data;
}

project ProjRepo :: update(project* old, project* _new){
	return *old;
}

project ProjRepo :: find(project* similar){
	return *similar;
}

project ProjRepo :: find(int id){
	project p;
	return p;
}

std::vector<project> ProjRepo :: findAll(){
	return std::vector<project>();
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
