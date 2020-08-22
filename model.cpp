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

std::string project :: get_uuid(){
	return uuid;
}

bool project :: is_archived(){
	return archived;	
}

bool project :: is_all_done(){
	return all_done;
}

bool project :: is_curr(){
	return curr;	
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

int m_todo :: get_project_id(){
	return proj_id;
}

int m_todo :: get_category_id(){
	return cat_id;
}

std::string m_todo :: get_todo(){
	return todo;
}

std::string m_todo :: get_desc(){
	return description;
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


// /////////////////////////////////////////
// ////////////// SETTINGS //////////////////
// ///////////////////////////////////////////

int settings :: get_curr_branch_id() {
	return curr_branch_id;
}

