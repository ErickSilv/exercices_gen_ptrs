#include <iostream>
#include <cstring>
using byte = unsigned char;

//Test function (predicates)
void print ( int *first, int *last ) {

	std::cout << " = [ ";
	while ( first != last ){
		std::cout << *first << " ";
		first++;
	}
	std::cout << "] \n";

}

bool positivo ( const void *a ) {
	
	auto num1 = ( int * ) a;
	if ( *num1 >= 0 ) {
		return true;
	}
	return false;

}

bool igual ( const void *a, const void *b ) {
	
	auto num1 = ( int * ) a;
	auto num2 = ( int * ) b;
	if ( *num1 == *num2 ) {
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

	auto iSlow = first+size;
	auto iFast = first+size;

	for ( /*Empty*/; first != last; first += size) {

		auto compar = false;
		auto aux = (byte *) first_; 
		for ( /*Empty*/; aux != iSlow; aux += size ) {
			compar = igul ( aux, iFast );

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

		iFast += size;

	}

	//Returning (iSlow-size) because the pointer 'iSlow' is a reference to value what is memory garbage  
	return iSlow-size;

}


int main () {

	int A[13] = { -1, 2, -3, 4, -5, 6, -7, 8, -9, 10, -11, -1, -9};
	//int B[10] = { 1, 1, 2, 2, 3, 3, 4, 4, 5, 5 };
	auto ptr_ = (int *) Remove_If( std::begin(A), std::end(A), positivo, sizeof(int) );

	std::cout << " A ";
	print( std::begin(A), ptr_ );

}
