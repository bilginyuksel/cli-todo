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


struct type_repo{
	std::string type;
	void* repo_obj;
};

static int callback(void *param, int argc, char **argv, char **azColName){
	
	// you can callback other functons here.
	// like if(type_repo->type == "category") cat->callback();
	// or just fill it here! according to your needs.
	type_repo* t_rep = static_cast<type_repo*>(param);
	if(t_rep -> type == "category"){
		std::cout<<"Category found!\n";
		category* c = static_cast<category*>(t_rep->repo_obj);
			
	}


	for(int i=0; i<argc; ++i){
		std::cout<<azColName[i]<<"= "<<(argv[i] ? argv[i] : "NULL")<<"\n";
	}
	std::cout<<"\n";
	// Try to solve is return type matters.
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
	
	type_repo* t = new type_repo;
	t->type = "category";
	t->repo_obj = static_cast<void*>(c);

	int rc= sqlite3_exec(db, sql.c_str(), callback, t, &err);
	//std::cout<<"\nerror= "<<err<<"\n";

	this->close();

	return *c;
}


std::vector<category> CatRepo :: findAll() {
	char *err = 0;
	this->connect();

	std::cout<<"Inside find all\n";
	std::string sql = "SELECT * FROM CATEGORY;";

	category* c = new category("my-branch", "come_on_description");

	type_repo* t = new type_repo;

	t->type = "category";
	t->repo_obj = static_cast<void*>(c);
	int rc = sqlite3_exec(db, sql.c_str(), callback, t, &err);
	//std::cout<<"\nerror= "<<err<<"\n";

	this->close();
	return std::vector<category>();
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
