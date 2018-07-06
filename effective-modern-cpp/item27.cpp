//to test the "use tag dispatch " in the item 27

#include<string>
#include<iostream>
#include<type_traits>

using namespace std;

template <typename T>
void LogAndAddImpl(T&& name, std::false_type){
	cout<<"inside the int"<<endl;
}

template <typename T>
void LogAndAddImpl(T&& name, std::true_type){
	cout<<"inside the string"<<endl;
}
 
template <typename T>
void LogAndAdd(T&& name){
//	using remove_ref=std::remove_reference<T>;
	LogAndAddImpl(std::forward<T>(name), std::is_integral<typename std::remove_reference<T>::type>());
}

class Person
{
public:
	//FIXME:: codes below have some errors unclosed
	template <typename T, typename=std::enable_if_t<
		!std::is_base_of<Person, std:;decay_t<T> >::value
		&&
		!std::is_integral<std::remove_reference_t<T>>::value
		>
		>
	explicit Person(T&&	n ){
		static_assert(
		!std::is_constructible<std::string, T>::value,
		"Parameter n can't be used to construct a std::string"
		);

	};
};

class SpecialPerson: public Person {
public:
	SpecialPerson(const SpecialPerson& rhs) // copy ctor; calls
	: Person(rhs) // base class
	{
		std::cout<<"the copy ctor of specialPerson"<<endl;
	}
	SpecialPerson(SpecialPerson&& rhs) // move ctor; calls
	: Person(std::move(rhs)) // base class
	{
		std::cout<<"the move ctor of specialPerson"<<endl;
}
};

int main(void)
{

	string temp("kkkkkkkkkkkkkA");
	auto temp2=32;
	LogAndAdd(temp);
	LogAndAdd(temp2);
	return 0;
}
