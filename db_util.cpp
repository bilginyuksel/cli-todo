#include <sqlite3.h>
#ifndef iostream
#include <iostream>
#endif

#ifndef string
#include <string>
#endif


class DbConn{
private:
	sqlite3 *db;
	char* errMsg = 0;

public:

	DbConn(){
		this->connect();
	}

	~DbConn(){
		this->close();
	}
	int execute(std::string query){
		// Print error message.
		return sqlite3_exec(db, query.c_str(), nullptr, 0, &errMsg);
	}

private:
	void connect(){
		int err = sqlite3_open("cli_todo_db", &db);
		if(err) ;// err
		else; // Not err
	}

	void close(){
		sqlite3_close(db);
	}
};
