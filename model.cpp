#include "model.h"

// ///////////////////////////
// ///////  PROJECT  ////////
// //////////////////////////

int project :: get_id(){
	return id;
}

std::string project :: get_title(){
	return title;
}  

std::string project :: get_desc(){
	return description;
}


// /////////////////////////////
// ///////  CATEGORY  /////////////
// ////////////////////////////
int category :: get_id(){
	return id;
}

std::string category :: get_title(){
	return title;
}

std::string category :: get_desc(){
	return description;
}


// ///////////////////////////////
// ////////  MTODO  /////////////
// /////////////////////////////////
int m_todo :: get_id(){
	return id;
}

bool m_todo :: is_done(){
	return done;
}

bool m_todo :: is_archived(){
	return archived;
}

int m_todo :: get_importance_lvl(){
	return lvl;
}

std::string m_todo :: get_create_time(){
	return ctime(&create_time);
}

std::string m_todo :: get_last_update_time(){
	return ctime(&last_update_time);
}

project* m_todo :: get_proj(){
	return nullptr;
}
category* m_todo :: get_cat(){
	return nullptr;
}

/*
class m_todo :: builder {
private:
	m_todo* td;
public:
	builder(std::string todo){
		td = new m_todo(todo);
	}

	builder& project_id(int proj_id){
		td->proj_id = proj_id;
		return *this;
	}

	builder& project(project *p){
		td->proj = p;
		return *this;
	}

	builder& category_id(int cat_id){
		td->cat_id = cat_id;
		return *this;
	}

	builder& category(category *c){
		td->cat = c;
		return *this;
	}

	builder& level(int lvl){
		td->lvl = lvl;
		return *this;
	}

	builder& description(std::string desc){
		td->description = desc;
		return *this;
	}

	builder& last_update_time(std::string last_update_time){
		
		return *this;
	}

	// Find out how to turn this string time to real time_t or 
	// the other one. Find the best suits for the job.
	builder& create_time(std::string create_time){
		return *this;
	}

	m_todo build(){
		return *td;
	}
};
*/
// ////////////////////////////////////
// //////////////  LOG  ///////////////////
// /////////////////////////////////////

int log :: get_id(){
	return id;
}

std::string log :: get_log_type(){
	return log_type;
}

std::string log :: get_desc(){
	return description;
}
