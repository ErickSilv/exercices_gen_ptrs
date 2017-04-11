#include <iostream> //cout, cin, endl
#include <iomanip> //setW
#include <cstring> 
#include <iterator> // begin, end
using byte = unsigned char;

typedef struct Student {
	std::string name;
	float grades[3];
	int year;
} Student;

//Test function (predicates)
void printAllStudents ( Student *first, Student *last ) {

	std::cout << "Students = [\n";
	while ( first != last ){
		std::cout << "{ ";
		std::cout << std::setw(13) << std::left << first->name << ", {";
		for ( auto i=0; i < 3; ++i ) {
			std::cout << std::setw(3) << first->grades[i];
		}
		std::cout << "}, Y=" << std::setw(5) << first->year << " }," << std::endl;
		first++;
	}
	std::cout << std::setw (42) << std::right << " ]\n";
}

void printOneStudent ( Student * est ) {

	std::cout << "Student = [ ";
		std::cout << est->name << ", { ";
		for ( auto i=0; i < 3; ++i ) {
			std::cout << est->grades[i] << " ";
		}
		std::cout << "}, Y=" << est->year;
	std::cout << "] \n";
}

bool menor_media ( const void * a_, const void *b_ ) {

	auto a = (Student *) a_;
	auto b = (Student *) b_;

	float media_a=0;
	float media_b=0;
	for ( auto i=0; i < 3; ++i ) {
		media_a += a->grades[i];
		media_b += b->grades[i];
	}

	if ( media_a/3 < media_b/3 ) {
		return true;
	}

	return false;
}

bool comparByName_Student ( const void *a_, const void *b_ ) {

	auto a = (Student *) a_;
	auto b = (Student *) b_;
	
	if ( a->name == b->name ) {
		return true;
	}
	return false;
}


// Generic Functions with generic pointers
using UnaryPredicate = bool (*) ( const void * );
void * Find_If ( const void * first_, const void * last_, UnaryPredicate p , size_t size ){

	auto first = (byte *) first_;
	auto last = (byte *) last_;

	for ( /*Empty*/; first != last; first += size) {
		
		if ( p ( first ) ) {
			return first;
		}

	}

	return last;

}



using Compare = bool (*)( const void * , const void * );
void * Min ( const void * first_ , const void * last_ , Compare cmp , size_t size ) {

	auto first = (byte *) first_;
	auto last = (byte *) last_;

	auto min = first;
	for ( /*Empty*/; first != last; first += size) {
		//IF min < first
		if ( cmp ( first, min ) ) {
			min = first;
		}

	}

	return min;

}



void * Copy ( const void * first_ , const void * last_ , const void * c_first_ , size_t size ) {

	auto first = (byte *) first_;
	auto last = (byte *) last_;
	auto c_first = (byte *) c_first_;

	for ( /*Empty*/; first != last; first += size ) {
		std::memcpy ( c_first, first, size );
		c_first += size;
	}

	return c_first;
}

using Condition = bool (*)( const void * );
void * Remove_If ( const void * first_ , const void * last_ , Condition con , size_t size ) {

	auto first = (byte *) first_;
	auto last  = (byte *) last_;

	auto iSlow = first;
	auto iFast = first;

	for ( /*Empty*/; iFast != last; iFast += size ) { 
		if ( con(iFast) ) {
			std::memmove( iSlow, iFast, size );
			iSlow += size;
		}
	}
	
	return iSlow;
}

using Igualdade = bool (*)( const void *, const void * );
void * Unique ( const void * first_ , const void * last_ , Igualdade igul , size_t size ) {

	auto first = (byte *) first_;
	auto last  = (byte *) last_;

	auto iSlow = first;
	auto iFast = first;

	for ( /*Empty*/; iFast != last; iFast += size) {

		auto compar = false;
		first = (byte *)first_;
		for ( /*Empty*/; first != iSlow; first += size ) {
			compar = igul ( first, iFast );

			if ( compar ) {

				break;

			}

		}

		//If anyone comparation returns true so move the value at address referencied by pointer iFast to a 
		//	address referencied by pointer iSlow.
		if ( !compar ) {
			
			//Move the value to a address.
			std::memmove( iSlow, iFast, size );
			// 'Walk' one -size- of bytes if iFast refer to a unique value.
			iSlow += size;

		}

	}

	//Returning 'iSlow' because him is a pointer to a immediate address after the last valid element of the array.  
	return iSlow;

}


int main () {

	Student arr[] = { { "Leonidas" ,  7.5, 3.2, 6.7, 20142 },
                      { "Musashi"  ,  9.5, 8.2, 8.7, 20131 },
                      { "Spartacus",  2.1, 3.5, 5.5, 20123 },
                      { "Miltiades",  0.1, 5.6, 4.4, 20151 },
                      { "Aquiles"  ,  6.5, 7.1, 8.6, 20141 },
                      { "Thor"     ,  4.5, 6.2, 2.1, 20132 },
                      { "Lancelot" ,  6.5, 6.0, 7.4, 20122 },
                      { "Ragnar"   ,  2.1, 6.6, 4.7, 20131 },
                      { "Ragnar"   ,  1.1, 6.6, 4.7, 20131 }
    };

    //auto arrSz = sizeof(arr)/sizeof(Student);

    Student c_arr[9];



    auto ptr_ = (Student *) Copy ( std::begin(arr), std::end(arr), std::begin(c_arr), sizeof(Student) );

    printAllStudents ( std::begin(c_arr), ptr_ );
    
    ptr_ = (Student *) Unique( std::begin(c_arr), std::end(c_arr), comparByName_Student, sizeof(Student) );

	printAllStudents ( std::begin(c_arr), ptr_ );

	
}
