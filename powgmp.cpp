#include <vector>
#include <gmpxx.h>
#include <iostream>
mpz_class sqrt(mpz_class a){
	mpz_class sqrt = 0;
	mpz_class tmp = 1;
	while (a > 0){
		a -= tmp;
		tmp += 2;
		sqrt++;
	}
	return sqrt;
}



// yes, this uses vectors until i have a better way to manage memory

std::vector <mpz_class> getFactors(mpz_class input){
	mpz_class maxIterator = sqrt(input);
	std::vector <mpz_class> tmp;

	// start at 2, starting at 1 might result in an endless loop
	for (mpz_class i = 2; i < maxIterator; i++){
		// eww, goto statements
		// first time i ever use them
		retry:
		if (input % i == 0){
			tmp.push_back(i);
			input /= i;

			// this 'optimization' will break things, it might be made to work in the future but i think it works well enough
			//maxIterator /= i;
			goto retry;
		}


	}
	return tmp;
}




// calculates a^b by (multiplying by a and decrementing b, until b == 0)
mpz_class normalPow(mpz_class a, mpz_class b){
	if (b == 0){
		return 1;
	}
	if (b == 1){
		return a;
	}

	mpz_class tmp = a;
	while (b > 1){
		tmp *= a;
		b--;
	}
	return tmp;
}

// calculates a^b by splitting the exponent, see EXP.txt for explanation
mpz_class fastpow(mpz_class a, mpz_class b){
	std::vector<mpz_class> factors = getFactors(b);
	// get all divisionable factors from b
	mpz_class tmp = a;
	for (int i = factors.size() - 1; i >= 0; i--){
		tmp = normalPow(tmp,factors[i]);
	}
	return tmp;
}

// same as fastpow, but starts with small exponents instead of large exponents, see EXP.txt for explanation
mpz_class fastpow0(mpz_class a, mpz_class b){
	std::vector<mpz_class> factors = getFactors(b);
	// get all divisionable factors from b
	mpz_class tmp = a;
	for (int i = 0; i < factors.size(); i++){
		tmp = normalPow(tmp,factors[i]);
	}
	return tmp;
}

// NOT IMPLEMENTED YET
// same as fastpow, but checks if the exponent has a low amount of divisors, this can optimize even further if it's not too time expensive
mpz_class fastpow2(mpz_class a, mpz_class b){
	std::vector<mpz_class> factors = getFactors(b);
	// get all divisionable factors from b
	mpz_class tmp = a;
	for (int i = factors.size() - 1; i >= 0; i--){
		tmp = normalPow(tmp,factors[i]);
	}
	return tmp;
}


