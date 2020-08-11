#include "db_repo.h"


int main(){
	CatRepo* rep = new CatRepo;
	category* cat = new category("pc", "computer related stuff.");
	rep->save(cat);
	std::cout<< rep->count()<<"\n";
	return 0;
}
