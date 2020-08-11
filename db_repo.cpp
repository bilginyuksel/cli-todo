#include "db_repo.h"


template <class T>
void CLIAppRepo<T> :: connect(){
	int err = sqlite3_open("db_todo_cli", &db);
	if(err);
	else;
}

template <class T>
void CLIAppRepo<T> :: close(){
	sqlite3_close(db);
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
	std::cout<<"error --> "<<err<<"\n";
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
	return *similar;
}

category CatRepo :: find(int id) {
	category c;
	return c;
}


std::vector<category> CatRepo :: findAll() {
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
