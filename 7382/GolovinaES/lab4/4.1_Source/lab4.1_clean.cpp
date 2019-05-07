#include <iostream>
#include <string>
#include <vector>
#include <cctype>

void knuthMorrisPratt(std::string pattern){
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
	while (1){
		//если символы в строке и шаблоне совпали,
		//двигаемся вперед по строке и по шаблону
		if (pattern[first] == sym ){
			first++;
			counter++;
			//выводим результат, если шаблон найден
			if (first == size_p){
				if (!one_found){
					std::cout<<counter-size_p;
					one_found=true;
				}
				else std::cout<<", "<<counter-size_p;
				first = prefix[first-1];
			}
			if (!(std::cin >> sym)) break;
		}
		else{
			//если символы не совпали переход по префикс функции
			//только если не находимся на начале шаблона
			if (first != 0) first=prefix[first-1];
			else{
				counter++;
				if (!(std::cin >> sym)) break;
			}
		}
	}
	//если не найдено вхождений вывод -1
	if (!one_found) std::cout<<-1;
}


int main(){
	std::string pattern;
	std::cin >> pattern;
	knuthMorrisPratt(pattern);

return 0;
}
