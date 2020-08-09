#include <sqlite3.h>
#include <fstream>
#include <iostream>
#include <string>


const char* DB_NAME =  "db_todo_cli";

int main(){


	std::ifstream file("init-db.sql");
	std::string content;
	content.assign( (std::istreambuf_iterator<char>(file)),
				(std::istreambuf_iterator<char>()));

	const char* sql_query = content.c_str();
	for(int i=0;i<content.length(); ++i)
		std::cout<<sql_query[i];

	file.close();

	// Connect db and execute init-sql queries to initialize todo database.
	sqlite3 *db;
	char *err_msg = 0;

	int connection_result = 0;
	connection_result = sqlite3_open(DB_NAME, &db);
	if(connection_result){
	       	std::cout<<"DB Connection error :: database couldn't initialize -- "<< sqlite3_errmsg(db)<<"\n";
		exit(1);
	} else std::cout<<"Database connection successfull!\n";

	int exec_result = sqlite3_exec(db, sql_query, NULL, 0, &err_msg);

	if(exec_result != SQLITE_OK){
		std::cout<<"SQL execution error --- Error Message -> " << err_msg<<"\n";
		sqlite3_free(err_msg);
	}else std::cout<<"SQL execution completed successfully!\n";

	sqlite3_close(db);


	return 0;
}
