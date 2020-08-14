#include <iostream>
#include <bits/stdc++.h>
#include <vector>

class CombinationIterator{

private:
	void bin(int);			

public:
	CombinationIterator(std::string characters){
		// Lexigrophical
		std::vector<std::string> comb;
		int n = characters.length();
		this->bin(n);	
	}	

	std::string next(){}
	bool hasNext(){}
};


std::vector<int> toBin(int num, int n){
	std::vector<int> res;
	while(num!=0){
		res.push_back(num%2);
		num/=2;
	}

	while(res.size()!=n)
		res.push_back(0);

	return res;
}

void CombinationIterator :: bin(int n){
	std::vector<std::vector<int>> bins;

	for(int i=0; i<pow(2, n); ++i){
		bins.push_back(toBin(i, n));
	}
	
	for(std::vector<int> bin : bins){
		for(int i=0; i<bin.size(); ++i){
			std::cout<<bin[i];
		}std::cout<<"\n";
	}
}

int main(){

	std::string c;
	std::cin>>c;
	CombinationIterator cI(c);
	

}



