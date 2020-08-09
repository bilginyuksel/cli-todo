#include <sqlite3.h>
// This is for debugging purposes #include <iostream>
// Import todo file here.
// Or it will be non compound app.

// Todo db operations class
class tododb{
public:
	const void add_todo(todo *t);
	const todo rm_todo();
	const todo update_todo();
};
