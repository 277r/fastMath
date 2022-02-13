#include <vector>
#include <gmpxx.h>
#include <iostream>



// bad unoptimized, but should give an estimate 
mpz_class sqrt(mpz_class &a){


	mpz_class tmp = a;
	while (tmp * tmp > a){
		tmp <<= 1;
	}
	tmp >>= 1;
	
	return tmp;
}


mpz_class mp_log2(mpz_class a){
	mpz_class tmp = 0;
	while (a >= 2){
		tmp++;
		a>>= 1;
	}
	return tmp;
}

// yes, this uses vectors until i have a better way to manage memory
// algorithm changed to H
std::vector <mpz_class> getFactors(mpz_class input){
	//mpz_class maxIterator = input;
	std::vector <mpz_class> tmp;

	retryFactor2:
		if (input % 2 == 0){
			// remember, ONE bitshift is a factor of TWO
			input >>= 1;
			tmp.push_back(2);
			goto retryFactor2;

		}

	// start at 2, starting at 1 might result in an endless loop
	for (mpz_class i = 3; i <= input; i+= 2){
		// eww, goto statements
		// first time i ever use them
		retry:
		if (input % i == 0){
			tmp.push_back(i);
			input /= i;

			//maxIterator /= i;
			goto retry;
		}


	}
	return tmp;
}




// calculates a^b by (multiplying by a and decrementing b, until b == 0)
mpz_class normalPow(mpz_class &a, mpz_class &b){
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
mpz_class fastpow(mpz_class &a, mpz_class &b){
	if (b == 0){
		return 1;
	}
	if (b == 1){
		return a;
	}

	std::vector<mpz_class> factors = getFactors(b);
	// get all divisionable factors from b
	mpz_class tmp = a;
	for (int i = factors.size() - 1; i >= 0; i--){
		tmp = normalPow(tmp,factors[i]);
	}
	return tmp;
}



// same as fastpow, but removes the largest power of 2
mpz_class fastpow2(mpz_class a, mpz_class b){
	// contains all 2^x values in exponent
	std::vector<mpz_class> factors;
	mpz_class constant2 = 2;


	// get parts
	while (b > 0){
	
		mpz_class factorPart = mp_log2(b);	
		factors.push_back(factorPart);
	
		// need to use normal fastpow bc endless loops
		b -= fastpow(constant2,factorPart);
	}
	

	// calculate all a^(2^n) where n is a number in factors 
	std::vector<mpz_class> temporary_values;
	for (int i = 0; i < factors.size(); i++){
		temporary_values.push_back(a);
		for (int ii = 0; ii < factors[i]; ii++){
			temporary_values[i] *= temporary_values[i];
		}
	}
	

	// combine all previously calculated numbers together
	// could be memory optimized by removing temporary_values[1] after using it and iterating over it
	for (int i = 1; i < temporary_values.size(); i++){
		temporary_values[0] *= temporary_values[i];
	}

	return temporary_values[0];
}


