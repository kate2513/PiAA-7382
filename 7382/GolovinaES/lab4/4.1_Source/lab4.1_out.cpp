#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <iomanip>

#define GREEN   "\x1b[32m"
#define RESET   "\x1b[0m"

void knuthMorrisPratt(std::string pattern){
	std::cout << "START OF THE ALGORITHM";
	std::string text;
	std::vector<int> result;
	size_t steps=1;

	size_t size_p = pattern.size();
	char sym;
	bool one_found=false;
	size_t counter=0;
	std::vector<int> prefix(size_p,0);
	//вычисление префикс функции для всех символов в pattern
	size_t first=0,last=1;
	while (last<size_p){
		if (pattern[first] == pattern[last]){
			prefix[last]=first+1;
			first++;
			last++;
		}
		else{
			if (first==0){
				prefix[last]=0;
				last++;
			}
			else first=prefix[first-1];
		}
	}
	counter = first = 0;
	std::cin>>sym;

	text.push_back(sym);

	while (1){
//---------------------------------------------------
		std::cout<<"\n\nSTEP #"<<steps++<<'\n';
		std::cout<< "                 ";
		for (size_t i=0;i<text.size();i++) std::cout<< std::setw(3) << i;
		std::cout<< "\nRecieved text:   ";
		for (size_t i=0;i<text.size();i++){
			if (i==counter) std::cout<< GREEN <<std::setw(3)<< text[i] << RESET;
			else std::cout <<std::setw(3)<<text[i];
		}
		std::cout<<"\n                 ";
		for (size_t i=0;i<pattern.size();i++) std::cout <<std::setw(3)<< i;
		std::cout<<"\nPattern:         ";
		for (size_t i=0;i<pattern.size();i++)
			if (i==first) std::cout<<GREEN<<std::setw(3)<< pattern[i] << RESET;
			else std::cout <<std::setw(3)<<pattern[i];
		std::cout<<"\nPrefix function: ";
		for (size_t i=0;i<pattern.size();i++)
			std::cout<<std::setw(3)<<prefix[i];
		std::cout<<'\n';
//---------------------------------------------------
		if (pattern[first] == sym ){
			std::cout<<"Symbols matched. Going further.\n";
			first++;
			counter++;
			if (first == size_p){
				std::cout<< "Pattern found! It starts from index "<< counter-size_p <<" in text.\n";
//				if (!one_found){
//					std::cout<<counter-size_p;
//					one_found=true;
//				}
//				else std::cout<<", "<<counter-size_p;
				result.push_back(counter-size_p);
				first = prefix[first-1];
				std::cout<<"In pattern: going to "<<first<<" (prefix function)\n";
			}
			if (!(std::cin >> sym)) break;
			text.push_back(sym);
		}
		else{
			std::cout<<"Symbols not matched.\n";
			if (first != 0) first=prefix[first-1];
			else{
				counter++;
				if (!(std::cin >> sym)) break;
				text.push_back(sym);
			}
			std::cout<<"In pattern: going to "<<first<<" (prefix function)\n";
		}
	}
//	if (!one_found) std::cout<<-1;
	std::cout<<"\n\nRESULT:\n";
	if (result.empty()) std::cout<<-1<<'\n';
	else{
		std::cout<<result[0];
		for (int i=1;i<result.size();i++) std::cout<<","<<result[i];
		std::cout<<'\n';
	}
}


int main(){
	std::string pattern;
//	pattern.reserve(15000);

	std::cin >> pattern;
	knuthMorrisPratt(pattern);

return 0;
}
