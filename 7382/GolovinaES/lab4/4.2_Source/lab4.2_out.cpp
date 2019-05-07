#include <iostream>
#include <string>
#include <vector>
#include <cstddef>
#include <iomanip>

#define GREEN   "\x1b[32m"
#define RESET   "\x1b[0m"

ptrdiff_t knuthMorrisPratt(std::string pattern, std::string text){

	size_t steps=1;

	size_t size_p = pattern.size();
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

	last = first = 0;
	size_t checker=0;
	for (size_t i=0;i<size_p;i++){
		while (pattern[first] == text[last]){
//------------------------------------------------------------------
			if (pattern[first] == text[last]){
				std::cout<<"\n\nSTEP #"<<steps++<<'\n';
				std::cout<< "                 ";
				for (size_t i=0;i<text.size();i++) std::cout<< std::setw(3) << i;
				std::cout<< "\nWord A(text):    ";
				for (size_t i=0;i<text.size();i++){
					if (i==last) std::cout<< GREEN <<std::setw(3)<< text[i] << RESET;
					else std::cout <<std::setw(3)<<text[i];
				}
				std::cout<<"\n                 ";
				for (size_t i=0;i<pattern.size();i++) std::cout <<std::setw(3)<< i;
				std::cout<<"\nWord B(pattern): ";
				for (size_t i=0;i<pattern.size();i++)
					if (i==first) std::cout<<GREEN<<std::setw(3)<< pattern[i] << RESET;
					else std::cout <<std::setw(3)<<pattern[i];
				std::cout<<"\nPrefix function: ";
				for (size_t i=0;i<pattern.size();i++)
					std::cout<<std::setw(3)<<prefix[i];
				std::cout<<'\n';
				std::cout<<"Symbols matched. Going further.\n";
			}
//-------------------------------------------------------------------
			checker++;
			first=(first+1) % size_p;
			last=(last+1) % size_p;
			if (checker == size_p){
				std::cout<< "Cyclic shift found! It starts from index "<< last+size_p-checker <<" in text A.\n";
				return (last+size_p-checker) % size_p;
			}
			i++;
		}
		checker=0;
		if (pattern[first] != text[last]){
//-------------------------------------------------------------------
		std::cout<<"\n\nSTEP #"<<steps++<<'\n';
		std::cout<< "                 ";
		for (size_t i=0;i<text.size();i++) std::cout<< std::setw(3) << i;
		std::cout<< "\nWord A(text):    ";
		for (size_t i=0;i<text.size();i++){
			if (i==last) std::cout<< GREEN <<std::setw(3)<< text[i] << RESET;
			else std::cout <<std::setw(3)<<text[i];
		}
		std::cout<<"\n                 ";
		for (size_t i=0;i<pattern.size();i++) std::cout <<std::setw(3)<< i;
		std::cout<<"\nWord B(pattern): ";
		for (size_t i=0;i<pattern.size();i++)
			if (i==first) std::cout<<GREEN<<std::setw(3)<< pattern[i] << RESET;
			else std::cout <<std::setw(3)<<pattern[i];
		std::cout<<"\nPrefix function: ";
		for (size_t i=0;i<pattern.size();i++)
			std::cout<<std::setw(3)<<prefix[i];
		std::cout<<'\n';
		if (pattern[first] == text[last]) std::cout<<"Symbols matched. Going further.\n";
//------------------------------------------------------------------
			std::cout<<"Symbols not matched. No moving in word A.\n";
			if (first != 0){
				first=prefix[first-1];
				i--;
			}
			else last++;
			std::cout<<"In word B: going to "<<first<<" (prefix function)\n";
		}
	}
	std::cout << "Word B is not a cyclic shift of the word A\n";
	return -1;
}


int main(){
	std::string text1,text2;
	std::cin >> text2 >> text1;
	if (text1.size() != text2.size()){
		std::cout<<"Words have different length.\nWord B can't be cyclic shift of word A\n\nRESULT:\n";
		std::cout << -1;
		return 0;
	}
	std::cout<<"\nRESULT:\n"<< knuthMorrisPratt(text1,text2) <<'\n';

return 0;
}
