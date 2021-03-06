#include "db_repo.h"


template <class T>
void CLIAppRepo<T> :: connect(){
	char text[255];
	FILE *name;
	name = popen("whoami", "r");
	std::fgets(text, sizeof(text), name);
	pclose(name);
	std::string whoami(text); whoami.pop_back(); // remove space character.

	std::string path = "/home/"+whoami+"/cli-todo/init/db_todo_cli";
	int err = sqlite3_open(path.c_str(), &db);
//	if(err){
//		std::cout<<"error happened\n";
//	}
//	else std::cout<<"Successfully joined!\n";
}

template <class T>
void CLIAppRepo<T> :: close(){
//	std::cout<<"Database closed!\n";
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
		m_todo m;
		m.fill_m_todo(map);
		mt->push_back(m);
	}else if(type == "proj"){
		std::vector<project>* pr = static_cast<std::vector<project>*>(stav->vec);
		project p;
		p.fill_project(map);
		pr->push_back(p);
	}else if(type == "log"){
		std::vector<log>* lr = static_cast<std::vector<log>*>(stav->vec);
		log l;
		l.fill_log(map);
		lr->push_back(l);
	}

	return 0;
}

// //////////////////////////////////////////////
// ////////////////// CATEGORY //////////////////
// //////////////////////////////////////////////


void CatRepo :: save(category* data){
	std::string title = data->get_title();
	std::string description = data->get_desc();
//	std::cout<<"title= "<<title<<"\n";
//	std::cout<<"description= "<<description<<"\n";
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

bool CatRepo :: remove(int id){
	char* err;
	this->connect();
	std::string sql = "DELETE FROM CATEGORY WHERE NOT EXISTS (SELECT * FROM M_TODO WHERE M_TODO.category_id=CATEGORY.id AND M_TODO.done=0);";
	int rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &err);
	this->close();	
	ProjRepo* pr = new ProjRepo;
	pr->update_branch_status();	
	return false;
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
	int rc= sqlite3_exec(db, sql.c_str(), callback, convert_to_stav(TAG, this->categories), &err);
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
	int rc = sqlite3_exec(db, sql.c_str(), callback, convert_to_stav(TAG, this->categories), &err);

	this->close();

	if(this->categories.size() > 0) return this->categories[0];
	return *c;
}

category CatRepo :: find_best_match(std::string title){
	char *err = 0;
	this->connect();
	this->categories.clear();	
	std::string sql = "SELECT * FROM CATEGORY WHERE title LIKE '"+title+"%';";
	int rc = sqlite3_exec(db, sql.c_str(), callback, convert_to_stav(TAG, this->categories), &err);
	this->close();

	if(this->categories.size() >0) return this->categories[0];
	category c;
	return c;
}

std::vector<category> CatRepo :: findAll() {
	char *err = 0;
	this->connect();

	std::string sql = "SELECT * FROM CATEGORY;";

	this->categories.clear();
	
	int rc = sqlite3_exec(db, sql.c_str(), callback, convert_to_stav(TAG, this->categories), &err);
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
	std::string sql = "INSERT INTO PROJECT(title, description, uuid, archived, curr, all_done) VALUES ('"+title+"', '"+description+"', '" + uuid + "',"+ std::to_string(archived)+","+ std::to_string(curr)+","+ std::to_string(all_done)+");";
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
	std::string sql = "DELETE FROM PROJECT WHERE id="+data->get_title();
	return *data;
}

void ProjRepo :: make_status_undone(int branch){
	char* err = 0;
	std::string sql = "UPDATE PROJECT SET all_done=0 WHERE id="+std::to_string(branch)+";";

	this->connect();

	int rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &err);
	this->close();
}

void ProjRepo :: remove(std::string title) throw (const char*){
	if(title == "master"){
		throw "You can't delete master branch.\n";
	}
	char* err;
		
	project p = find(title);
	SettingsRepo* sr = new SettingsRepo;
	int current_branch_id = sr->curr_branch();
	if(p.is_archived()) throw "You can't delete archived branch.\n";
	if(!p.is_all_done()) throw "There is unfinished todos in this branch are you really want to delete it?\n";
	if(p.get_id() == current_branch_id) throw "You can't delete the branch you are in. Please change the branch before deleting it.\n";

	this->connect();
	std::string sql = "DELETE FROM PROJECT WHERE title='" + title+"';";	
	int rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &err);
	
	this->close();
}

void ProjRepo :: remove_force(std::string title){
	if(title == "master"){
		throw "You can't delete master branch.\n";
	}
	char* err;
	project p = find(title);
	SettingsRepo* sr = new SettingsRepo;
	int current_branch_id = sr->curr_branch();

	if(p.get_id() == current_branch_id) throw "You can't delete the branch you are in. Please change the branch before deleting it.\n";

	this->connect();
	std::string sql = "DELETE FROM PROJECT WHERE title='" + title+"';";	
	int rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &err);
	this->close();
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
	int rc = sqlite3_exec(db, sql.c_str(), callback, convert_to_stav(TAG, this->projects), &err);

	this->close();
	if(this->projects.size() > 0) return this->projects[0];
	project p;
	return p;
}

project ProjRepo :: find_exact_match(std::string title){
	char* err = 0;
	this->connect();
	this->projects.clear();

	// Use like sql query here.
	std::string sql = "SELECT * FROM PROJECT WHERE title='"+title+"';";
	int rc = sqlite3_exec(db, sql.c_str(), callback, convert_to_stav(TAG, this->projects), &err);
	this->close();

	if(this->projects.size() > 0) return this->projects[0];
	project p;
	return p;
}


project ProjRepo :: find(std::string title){
	
/*	char* err = 0;
	this->connect();
	this->projects.clear();

	// Use like sql query here.
	std::string sql = "SELECT * FROM PROJECT WHERE title LIKE '"+title+"%';";
	int rc = sqlite3_exec(db, sql.c_str(), callback, convert_to_stav(TAG, this->projects), &err);
	this->close();

	if(this->projects.size() > 0) return this->projects[0];
	project p;
	return p;*/
	return find_exact_match(title);
}

std::vector<project> ProjRepo :: findAll(){
	char* err = 0;
	this->connect();
	this->projects.clear();
	std::string sql = "SELECT * FROM PROJECT;";
	int rc = sqlite3_exec(db, sql.c_str(), callback, convert_to_stav(TAG, this->projects), &err);

	this->close(); 	
	return this->projects;
}

int ProjRepo :: count(){
	return -1;
}

void ProjRepo :: update_branch_status(){
	
	char* err = 0;
	this->connect();
	std::string sql = "UPDATE PROJECT SET all_done=1 WHERE NOT EXISTS (SELECT * FROM M_TODO WHERE PROJECT.id=M_TODO.project_id AND TODO.done=0)";
	int rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &err);
	this->close();
}


// ////////////////////////////////////
// //////////   MTODO  //////////////
// ////////////////////////////////////

void TodoRepo :: save(m_todo* data){

//	std::string uuid = data->get_uuid();
	bool done = data->is_done();
	bool archived = data->is_archived();
	int lvl = data->get_importance_lvl();
	std::string todo = data->get_todo();
	std::string desc = data->get_desc();;
	std::string cr_time = data->get_create_time();
	std::string lu_time = data->get_last_update_time();

	SettingsRepo* sr = new SettingsRepo;
	int proj_id = sr->curr_branch();
	int cat_id = data->get_category_id();
	
	std::string sql = "INSERT INTO M_TODO(done, archived, level, todo, description, create_time, last_update_time, project_id, category_id) VALUES ("+std::to_string(done)+","+std::to_string(archived)+","+std::to_string(lvl)+",\""+todo+"\",\""+desc+"\",'"+cr_time+"','"+lu_time+"',"+std::to_string(proj_id)+","+std::to_string(cat_id)+");";

	char* err =0;
	this->connect();
	
	int rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &err);

	this->close();

	ProjRepo* pr = new ProjRepo;
	pr->make_status_undone(proj_id);	
}

m_todo TodoRepo :: remove(m_todo* data){
	return *data;
}

void TodoRepo :: remove(int id){
	char* err = 0;
	this->connect();
	std::string sql = "DELETE FROM M_TODO WHERE id="+std::to_string(id)+";";

	int rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &err);
	this->close();

	// Update branch status after deleting any todos.
	ProjRepo* pr = new ProjRepo;
	pr->update_branch_status();
	delete pr; 

}

m_todo TodoRepo :: update(m_todo* old, m_todo* _new){
	return *old;
}

m_todo TodoRepo :: find(m_todo* similar){
	return *similar;
}

m_todo TodoRepo :: find(int id){
	char* err = 0;
	this->connect();
	this->todos.clear();
	std::string sql = "SELECT * FROM M_TODO WHERE id="+std::to_string(id)+";";
	int rc = sqlite3_exec(db, sql.c_str(), callback, convert_to_stav(TAG, this->todos), &err);
	this->close();

	if(this->todos.size() >0) return this->todos[0];
	m_todo t;
	return t;
}

std::vector<m_todo> TodoRepo :: find_all_by_category(int cat_id){
	char* err =0;
	this->connect();
	this->todos.clear();
	std::string sql = "SELECT * FROM M_TODO WHERE category_id="+std::to_string(cat_id)+";";
	int rc = sqlite3_exec(db, sql.c_str(), callback, convert_to_stav(TAG, this->todos), &err);
	this->close();
	return this->todos;
}

void TodoRepo :: make_todo_done(int id){
	char *err = 0;
	this->connect();
	std::string sql = "UPDATE M_TODO SET done=1 WHERE id="+std::to_string(id)+";";
	int rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &err);
	this->close();

	ProjRepo* pr = new ProjRepo;
	pr->update_branch_status();
	delete pr;
}

std::vector<m_todo> TodoRepo :: findAll(){
	char* err = 0;
	this->connect();
	this->todos.clear();
	std::string sql = "SELECT * FROM M_TODO;";

	int rc = sqlite3_exec(db, sql.c_str(), callback, convert_to_stav(TAG, this->todos), &err);
	this->close();
	return this->todos;	
}

std::vector<m_todo> TodoRepo :: find_undone_todos(int branch){
	char* err = 0;
	this->connect();
	this->todos.clear();
	std::string sql = "SELECT * FROM M_TODO WHERE done=0 AND project_id="+std::to_string(branch)+";";
	
	int rc = sqlite3_exec(db, sql.c_str(), callback, convert_to_stav(TAG, this->todos), &err);
	
	this->close();
	return this->todos;	
}

std::vector<m_todo> TodoRepo :: find_all_todos(int branch){
	char* err = 0;
	this->connect();
	this->todos.clear();
	std::string sql = "SELECT * FROM M_TODO WHERE project_id="+std::to_string(branch)+";";
	int rc = sqlite3_exec(db, sql.c_str(), callback, convert_to_stav(TAG, this->todos), &err);
	this->close(); 	
	return this->todos;
}

int TodoRepo :: count(){
	return -1;
}


// //////////////////////////////////
// ////////// SETTINGS ///////////////
// ///////////////////////////////////

static int settings_callback(void *param, int argc, char **argv, char **azColName){

	int* branch = static_cast<int*>(param);
//	*branch = std::atoi(argv[0]);
	*branch = std::atoi(argv[0]);
	
	return 0;
}


void SettingsRepo :: save(settings* data){}
settings SettingsRepo :: remove(settings* data){return *data;}
settings SettingsRepo :: update(settings* old, settings* _new){return *old;}
settings SettingsRepo :: find(settings* similar){return *similar;}
settings SettingsRepo :: find(int id){settings* todo = nullptr;return *todo;}
std::vector<settings> SettingsRepo :: findAll(){return std::vector<settings>();}
int SettingsRepo :: count(){return -1;}

int SettingsRepo :: curr_branch(){
	
	char* err = 0;
	int branch = -1;

	this->connect();
	std::string sql = "SELECT curr_branch_id FROM SETTINGS WHERE id=1";

	int rc = sqlite3_exec(db, sql.c_str(), settings_callback, static_cast<void*>(&branch), &err);

	this->close();
	return branch;
}

void SettingsRepo :: update_curr_branch(int branch){
	
	char* err = 0;
	this->connect();
	std::string sql = "UPDATE SETTINGS SET curr_branch_id="+std::to_string(branch)+" WHERE id=1";;

	int rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &err);
	this->close();
}


// ////////////////////////////////////
// ////////// LOG ///////////////////
// //////////////////////////////////////

void LogRepo :: save(log* data){}
log LogRepo :: remove(log* data){return *data;}
log LogRepo :: update(log* old, log* _new){return *old;}
log LogRepo :: find(log* similar){return *similar;}
log LogRepo :: find(int id){log* todo = nullptr;return *todo;}
int LogRepo :: count(){return -1;}

std::vector<log> LogRepo :: findAll(){
	char* err = 0;
	this->connect();
	this->logs.clear();
	std::string sql = "SELECT * FROM LOG;";
	int rc = sqlite3_exec(db, sql.c_str(), callback, convert_to_stav(TAG, this->logs), &err);
	this->close();
	return this->logs;
}
