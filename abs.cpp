

// even without `using namespace std` my compiler still gets angry about redifintion of `abs`, so now it's absolute
long long absolute(long long in){
	// the 64th bit (the leftmost) contains the signature, if this bit is TRUE, the value is negative, if this is FALSE, the value is positive
	if (in & (1 << 64)){

		// by XOR'ing the whole number with 2^64, we turn around the negating bit, and turn around the rest of the number, the rest of the number is turend around because of the two's complement 
		in ^= 0xFFFFFFFFFFFFFFFF;
	}
	return in;
}