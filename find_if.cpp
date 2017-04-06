#include <iostream>
#include <cstring>
using byte = unsigned char;


void print ( int *first, int *last ) {

	std::cout << " = [ ";
	while (first != last){
		std::cout << *first << " ";
		first++;
	}
	std::cout << "] \n";
}


bool menor ( const void *a, const void *b ) {
	
	auto num1 = (int * ) a;
	auto num2 = (int * ) b;

	if ( *num1 < *num2 ) {
		return true;
	}
	return false;
}


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
		
		if ( menor ( first, min ) ) {
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





int main () {

	int A[11] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, -1 };
	int B[11];

	auto ptr_ = (int *) Copy(std::begin(A), std::end(A), std::begin(B), sizeof(int) );


	std::cout << " B";
	print( std::begin(B), ptr_ );

}