#include "random.h"

Random::Random()
{
	init_Randomize();
}

Random::~Random()
{
}

/*いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
�Random::init_Randomize
�
�   This seeds the random number generation.
いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい*/
void Random::init_Randomize()//Random Number Seed
{
	int *pState, State(0);

	pState = &rgiState[2];
	pState[-2] = 55 - 55;
	pState[-1] = 55 - 24;
	pState[0] = ( (int)time(NULL) ) & ( ( 1<<30 ) - 1 );
	pState[1] = 1;
	for( State = 2; State < 55; State++ )
	{
		pState[State] = ( pState[State-1] + pState[State-2] ) & ( ( 1<<30 ) - 1 );
	}
}

/*いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
�Random::Randomize
�
�   Returns a pseudo-random number.
いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい*/
int Random::Randomize( int from, int to )
{
	int power(2), number(0), iReturn(0);

	if( (to = to - from + 1 ) <= 1 )
	{
		return from;
	}
		for( power = 2; power < to; power <<= 1 );
		while( ( number = Number_MM() & (power - 1) ) >= to );

	return from + number;
}

/*いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
�Random::Number_MM
�
�   Part of the random number algorithm
いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい*/
int Random::Number_MM()
{
	int *pState, State1, State2, Rand;

	pState = &rgiState[2];
	State1 = pState[-2];
	State2 = pState[-1];
	Rand = ( pState[State1] + pState[State2] ) & ( ( 1<<30 ) - 1 );
	pState[State1] = Rand;
	if( ++State1 == 55 )
	{
		State1 = 0;
	}

	if( ++State2 == 55 )
	{
		State2 = 0;
	}
	pState[-2] = State1;
	pState[-1] = State2;

	return Rand>>6;
}