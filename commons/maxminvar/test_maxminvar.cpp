#include <iostream>

#include "maxminvar.cpp"

int main()
{
	bool res;

	res = ( cmns::max( 3, -3, 2 ) == 3 );
	if( !res ) goto err;
	
	res = ( cmns::min( 3, -3, 2 ) == -3 );
	if( !res ) goto err;
	
	res = ( cmns::max( -45, -3 ) == -3 );
	if( !res ) goto err;

	res = ( cmns::min( -45, -3 ) == -45 );
	if( !res ) goto err;

	res = ( cmns::max( -3 ) == -3 );
	if( !res ) goto err;

	res = ( cmns::min( -3 ) == -3 );
	if( !res ) goto err;

	std::cout << "MaxMinVar test: success!\n";
	return 0;

err:

	std::cout << "MaxMinVar test: fail!\n";
	return 1;

}