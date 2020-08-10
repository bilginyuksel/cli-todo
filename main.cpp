#include "db_repo.h"


int main(){
	CatRepo* rep = new CatRepo;
	std::cout<<"Hello world\n";
	std::cout<< rep->count()<<"\n";
	return 0;
}
