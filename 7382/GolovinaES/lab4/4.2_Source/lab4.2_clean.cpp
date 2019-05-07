#include <iostream>
#include <string>
#include <vector>
#include <cstddef>

ptrdiff_t knuthMorrisPratt(std::string pattern, std::string text){

	size_t size_p = pattern.size();
	std::vector<int> prefix(size_p,0);
	//вычисление префикс функции для всех символов в pattern(text B)
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
	//индексы по словам A и В изначально на нуле
	last = first = 0;
	size_t checker=0;
	for (size_t i=0;i<size_p;i++){
		//если в словах текущие буквы совпали - запуск цикла
		while (pattern[first] == text[last]){
			checker++;
			//переходим вперед без выхода за границы слов
			first=(first+1) % size_p;
			last=(last+1) % size_p;
			//checker считает количество букв и если их
			//становится равно длине слова - B циклический сдвиг А
			if (checker == size_p) return (last+size_p-checker) % size_p;
			//чтоб корректно идти по слову A после выхода из цикла while
			i++;
		}
		checker=0;
		//если текущие буквы в словах не совпали - переход
		//по префикс функции слова B
		if (pattern[first] != text[last]){
			if (first != 0){
				first=prefix[first-1];
				//т.к. не движемся по слову A, для корректности
				i--;
			}
			//если не с чем больше сравнить текущую букву
			//в слове А, движемся по нему вперед
			else last++;
		}
	}
	//если не циклический сдвиг возвращаем -1
	return -1;
}


int main(){
	std::string text1,text2;
	std::cin >> text2 >> text1;
	if (text1.size() != text2.size()){
		std::cout << -1;
		return 0;
	}
	std::cout << knuthMorrisPratt(text1,text2) << '\n';

return 0;
}
