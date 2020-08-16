#include "db_repo.h"
#include <unordered_map>

#ifndef iostream
#include <iostream>
#endif


void help();
void version();
void about();
void execute_branch(int, char**);
void execute_note(int, char**);
void execute_category(int, char**);

void about_note();
void about_branch();
void about_category();

void add_new_branch(std::string);
void show_all_branches();
void delete_branch(std::string) throw (std::string); // it needs to throw an exception

int main(int argc, char** argv){

//	CatRepo* rep = new CatRepo;
//	category* cat = new category("pc", "computer related stuff.");
//	rep->save(cat);
//	std::cout<< rep->count()<<"\n";

	// application started without parameters
	if(argc == 1) about();
	
	std::string action = argv[1];
	// Help called
	if(action == "--help" || action == "-h") help();
	if(action == "--version" || action == "-v") version();
	/*
	 * <command> [<args>]
	 * [--<help>, -h], [--version, -v]
	 *
	 * */

	if(action == "branch" && argc>=3) execute_branch(argc, argv); else about_branch();
	else if(action == "note" && argc>=3) execute_note(argc, argv); else about_note();
	else if(action == "category" && argc>=3) execute_category(argc, argv); else about_category();

	return 0;
}


void help(){
	std::cout<<"Help message\n";
	exit(1);
}

void about(){
	std::cout<<"About this [X]\n";
	exit(1);
}

void about_branch(){}
void about_note(){}
void about_category(){}

void version(){
	std::cout<<"cli-todo_1.0.0\n";
	exit(1);
}

void execute_branch(int argc, char** argv){
	// branch name is a must
	// argv <options>, [-a, --all, -d, --delete]
	// argv [--name]
	if(argv[2] == "-a" || argv[2] == "-all")
		show_all_branches();

	if(argv[2] == "-d" || argv[2] == "--delete"){
		// expect a @param
		// param should be the branch name will be deleted.
		if(argc < 4) exit(1); // print a message

		std::string branch_name_to_delete = argv[3];
		std::unordered_map<std::string, bool> branch_map;
		if(branch_map.find(branch_name_to_delete) != branch_map.end() && !branch_map[branch_name_to_delete]){
			// branch exists and ready to delete.
			// Check if there are any unfinished todo exists.
			// If exists ask for permission to delete.
			try{
				delete_branch(branch_name_to_delete);
			}catch(std::string err){
				std::cout<<err;
				exit(1);
			}
		}
	}

	std::string new_branch = argv[2];
	// add brnch here.
	add_new_branch(new_branch);
}

void add_new_branch(std::string name){
	// TODO Add branch code goes here.
}

void delete_branch(std::string name) throw (std::string){
	// TODO Delete branch code goes here.
}

void show_all_branches(){
	// TODO show all branches
}

void execute_note(int argc, char** argv){
}

void execute_category(int argc, char** argv){

}
