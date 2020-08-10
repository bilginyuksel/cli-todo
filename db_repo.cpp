#include "db_repo.h"


// //////////////////////////////////////////////
// ////////////////// CATEGORY //////////////////
// //////////////////////////////////////////////


void CatRepo :: save(category* data){

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
