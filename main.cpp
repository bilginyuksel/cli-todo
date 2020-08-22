#include "db_repo.h"

#ifndef unordered_map
#include <unordered_map>
#endif

#ifndef iostream
#include <iostream>
#endif


void help();
void version();
void about();
void execute_branch(int, std::vector<std::string>&);
void execute_note(int, std::vector<std::string>&);
void execute_category(int, std::vector<std::string>&);
void execute_checkout(int, std::vector<std::string>&);

void about_note();
void about_branch();
void about_category();
void about_checkout();

void add_new_branch(std::string);
void show_all_branches();
void delete_branch(int, std::vector<std::string>&); // it needs to throw an exception

void show_notes(int, std::vector<std::string>&);
void add_note(int, std::vector<std::string>&);
void delete_note(int, std::vector<std::string>&);

// EMOJI UNICODE START
std::string blue_book = "\xF0\x9F\x93\x98";
std::string left_point = "\xF0\x9F\x91\x88";
std::string right_point = "\xF0\x9F\x91\x89";
std::string poo = "\xF0\x9F\x92\xA9";
std::string confused_face = "\xF0\x9F\x98\x95";
std::string exclamation_mark = "\xE2\x9D\x97";
std::string question_mark = "\xE2\x9D\x93";
std::string cross_mark = "\xE2\x9D\x8C";
std::string check_mark = "\xE2\x9C\x85";
std::string warning_sign = "\xE2\x9A\xA0"; // very tiny
std::string clock_emoji = "\xF0\x9F\x95\x95";
std::string dollar = "\xF0\x9F\x92\xB2";
std::string flame = "\xF0\x9F\x94\xA5";
// EMOJI UNICODE END

CatRepo* rp = new CatRepo;
ProjRepo* pr = new ProjRepo;
SettingsRepo* sr = new SettingsRepo;
TodoRepo* tr = new TodoRepo;

int main(int argc, char** argv){

	std::vector<std::string> cli_arguments;
//	std::cout<<"argc= "<<argc<<"\n";
	for(int i=0; i<argc; ++i)
		cli_arguments.push_back(argv[i]);

	// application started without parameters
	if(argc == 1) about();
	
	std::string action = cli_arguments[1];
	// Help called
	if(action == "--help" || action == "-h") help();
	if(action == "--version" || action == "-v") version();
	/*
	 * <command> [<args>]
	 * [--<help>, -h], [--version, -v]
	 *
	 * */

	// All code will be exited after execution.
	if(action == "branch" && argc>=3) execute_branch(argc, cli_arguments); 
	if(action == "note" && argc>=3) execute_note(argc, cli_arguments); 
	if(action == "category" && argc>=3) execute_category(argc, cli_arguments); 
	if(action == "checkout" && argc>=3) execute_checkout(argc, cli_arguments); 

}

void help(){
	about();
	exit(1);
}

void about(){
	std::cout<<"\n\n"<<flame<<flame<<" Usage "<<poo<<poo<<"\n\n";
	std::cout<<"  "<<dollar<<"tod <command> <options> [<args>]\n";
	std::cout<<"\nGlobal Commands:\n";
	std::cout<<"\n  "<<dollar<<"branch [<options>] [<args>]....................Your notes will be stored at branches to avoid conflicts.";
	std::cout<<"\n  "<<dollar<<"note <options> [<args>]........................You can register, delete, update a note to a branch.";
	std::cout<<"\n  "<<dollar<<"category <options> [<args>]....................Categorize your notes. And get categorized notes of yours.";
	std::cout<<"\n  "<<dollar<<"checkout [<branch-name>].......................Switch your working branches.\n";
//	std::cout<<"\n"<<confused_face<<confused_face<<" Did you try to say ?";
	std::cout<<"\n\n\n\n";

	exit(1);
}

void about_branch(){	
	std::cout<<"\n\n"<<flame<<flame<<" Usage "<<poo<<poo<<"\n\n";
	std::cout<<"  "<<dollar<<"tod branch [<command>] [<args>], --help\n\n";
	std::cout<<"  Description:\n  Use this command to create, delete, list and archive branches. You can save notes in branches and with that way your notes will be structured. When you have unfinished todos in your branch you can't delete it we have covered it up for you and if you have archived your branch also you can't delete it. Recommended way of using this branch system is; You can sync your branches with your projects git branches. That way you can save notes to specific branches of your project. Easy access and beatiful visualization."<<exclamation_mark<<exclamation_mark<<"\n";
	std::cout<<"\n  Example Usage:\n";
	std::cout<<"\n  To create new branches.\n";
	std::cout<<"\n    "<<dollar<<"tod branch my-new-branch\n";
	std::cout<<"\nNOTE: You can't create branches that you have.\n\n\n";
	// You can add all branch functionality and emoji explanations also.
	exit(1);
}
void about_note(){
	exit(1);
}
void about_category(){
	exit(1);
}
void about_checkout(){
	std::cout<<"\n\n"<<flame<<flame<<" Usage "<<poo<<poo<<"\n\n";
	std::cout<<"  "<<dollar<<"tod checkout <branch-name>, --help\n\n";
	std::cout<<"  Description:\n  Use this method to switch between branches.\n";
	std::cout<<"\n  Example Usage:\n";
	std::cout<<"\n    "<<dollar<<"tod checkout master\n";
	std::cout<<"\nWith the command above you have successfully switched to branch master.\n\n\n";
	exit(1);
}

void version(){
	std::cout<<"\ncli-todo_v1.0.0\n";
	exit(1);
}

void execute_checkout(int argc, std::vector<std::string>& argv){
	
	if(argv[2] == "--help" || argv[2] == "-h") about_checkout();
	
	project p = pr-> find(argv[2]);
	if(p.get_id() == -1) {
		std::cout<<"There is no "<<argv[2]<<" branch exist.\n";
		exit(1);
	}

	int curr_branch_id = sr->curr_branch();
//	std::cout<<"curr_branch_id: "<<curr_branch_id<<"\n";
//	std::cout<<"p_get_id: "<<p.get_id()<<"\n";
	if(curr_branch_id == p.get_id()){
		std::cout<<"You are already in branch "<<argv[2]<<".\n";
		exit(1);
	}

	project old = pr->find(curr_branch_id);
	std::cout<<"Changing branch "<<old.get_title()<<" to "<<argv[2]<<".\n";	
	sr->update_curr_branch(p.get_id());
	int updated_branch = sr->curr_branch();

}

void execute_branch(int argc, std::vector<std::string>& argv){
	// branch name is a must
	// argv <options>, [-a, --all, -d, --delete]
	// argv [--name]

	if(argv[2] == "--help" || argv[2] == "-h")
		about_branch();

	if(argv[2] == "-a" || argv[2] == "--all")
		show_all_branches();

	if(argv[2] == "-d" || argv[2] == "--delete")
		delete_branch(argc, argv);

	std::string new_branch = argv[2];
	// add brnch here.
	add_new_branch(new_branch);
}



void add_new_branch(std::string name){
	if(name[0]=='-' || name[0] == '/' || name[0] == '_' || name[0] =='*' || name[0]=='&') {
		std::cout<<"Branch name can't start with special character.\n";
		exit(1);
	}

	// check if we have the branch or not.
	project any_branch = pr->find_exact_match(name);
	if(any_branch.get_id() != -1){
		std::cout<<"There is already a branch "<<any_branch.get_title()<<" exist.\n";
		exit(1);
	}
 
	project* p = new project(name);
	pr->save(p);
	project new_branch = pr->find(name);
	std::cout<<"New branch "<< new_branch.get_title() <<" created.\n";
	exit(1);
}

void delete_branch(int argc, std::vector<std::string>& argv){
		// expect a @param
		// param should be the branch name will be deleted.
		if(argc < 4) {
			std::cout<<"\nPlease enter a branch name to delete.\n";
			exit(1);
		}
	
		std::string branch_name_to_delete = argv[3];
		try{
			pr->remove(branch_name_to_delete);
		}catch(const char* err){
			std::cout<<err;
			exit(1);
		}
		
}

void show_all_branches(){
	std::vector<project> proj = pr->findAll();
	int curr_branch = sr->curr_branch();
	std::cout<<std::endl;
	for(project p : proj){
		if(p.is_archived()) std::cout<<blue_book;
		std::cout<<(p.is_all_done()? check_mark:cross_mark)<<" "<<p.get_title();	
		if(p.get_id() == curr_branch) std::cout<<" "<<left_point;
		std::cout<<std::endl;
	}
	
	std::cout<<std::endl;
	exit(1);
}

void execute_note(int argc, std::vector<std::string>& argv){
	
	if(argv[2] == "--help" || argv[2]=="-h") about_note();	
	if(argv[2] == "--list" || argv[2] == "-l") show_notes(argc, argv);
	if(argv[2] == "--delete" || argv[2] == "-d") delete_note(argc, argv);

	// or add note
	if(argc>4) add_note(argc, argv);
	
	exit(1);
}

void show_notes(int argc, std::vector<std::string>& argv){
	
	int curr_branch = sr->curr_branch();	

	if(!argc>3){
		// list notes here...
		std::vector<m_todo> todos = tr->findAll(curr_branch);
		std::cout<<std::endl;
		for(m_todo tod : todos){
			if(tod.get_importance_lvl()) std::cout<<exclamation_mark;
			std::cout<<(tod.is_done()?check_mark: cross_mark);
			std::cout<<tod.get_todo()<<std::endl;
		}std::cout<<std::endl;
	}

	// Now try to understand commands here. 
	// First look there can be 2 commands here.
	if(!argc>4 && (argv[3]=="--details" || argv[3]=="-d")){
		// list detailed notes here...
	}  

	if(!argc>4 && (argv[3]=="--undone" || argv[3]=="-u")){
		// list only unfinished todos
	}

	if(argc>4 && (argv[3]=="--details" || argv[3]=="-d") && (argv[4]=="--undone" || argv[4]=="-u")){
		// list unfinsihed todos with details.
	}
	
	if(argc>4 && (argv[3]=="--undone" || argv[3]=="-u") && (argv[4]=="--details" || argv[4]=="-d")){
		// list unfinsihed todos with details.
	}

//  print help message here.	
//	about_note();

	exit(1);
}

void delete_note(int argc, std::vector<std::string>& argv){
	
	// notes can be deleted different ways.
	// Get uuid to delete note or give title to delete note.
	// Get id to delete note
	
	
	exit(1);
}

void add_note(int argc, std::vector<std::string>& argv){
	
	// Add note.
	if(argv[3]=="--title" || argv[3]=="-t"){
		std::string title = argv[4];
		m_todo* new_note = new m_todo(title);
		tr->save(new_note);
	}	
	exit(1);
}

void execute_category(int argc, std::vector<std::string>& argv){

}
