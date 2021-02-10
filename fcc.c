#include <stdio.h>
#include <string.h>

const int oddPosTable[26] = {1, 0, 5, 7, 9, 13, 15, 17, 19, 21, 2, 4, 18, \
	20, 11, 3, 6, 8, 12, 14, 16, 10, 22, 25, 24, 23};

void
lowercase(char *c) {
	// Both lowercase letters and numbers in the ASCII table
	// 	always have the 3rd most significant bit set to 1.
	// Indeed by or-ing the character with 0x20 [00100000]
	// 	this function leaves numbers and lowercase letters 
	// 	untouched, but adds the 3rd m.s.b. to the uppercase 
	// 	letters, making them lowercase.
	*c |= 0x20;
}

int
isLetter(char c) {
	// Every letter in the ASCII table has got the 2nd m.s.b. set to 1. 
	// This function checks the presence of this bit by and-ing
	// 	the character with 0x40 [01000000] and checks if the result is
	// 	all leading zeros [00000000].
	return ((c & 0x40) != 0);
}

int
evenPosValues(char c) {
	// On even positions, the rule follows alphabetical order.
	// This function spits out the corresponding number by subtracting the
	//  0x61 offset from the ASCII value, returning a value between 0 and 25.
	// If the character is a number, this function subtracts the offset
	// 	0x30 [48], returning a value between 0 and 9.
	return isLetter(c) ? (c - 0x61) : (c - 0x30);
}

int
oddPosValues(char c) {
	// On odd positions, the rule follows an arbitrary table, indexed
	// 	alphabetically. This function spits the right number by subtracting
	// 	the 0x61 offset to get a value between 0 and 25.
	// If the character is a number, this function subtracts 0x30, to get
	// 	values between 0 and 9.
	return isLetter(c) ? (oddPosTable[c - 0x61]) : (oddPosTable[c - 0x30]);
}

int
main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Error: no code given.\n");
		return 1;
	}

	if (strlen(argv[1]) != 16) {
		fprintf(stderr, "Error: invalid code.\n");
		return 2;
	}

	char *code = argv[1];
	int check = 0;

	for (int i = 0; i < 15; i++) {
		lowercase(&code[i]);

		if (i % 2)
			check += evenPosValues(code[i]);
		else
			check += oddPosValues(code[i]);
	}

	check %= 26;

	// Add offset to get the letter
	char digit = check + 0x61;

	// Make last letter lowercase -- skipped by the loop
	lowercase(&code[15]);
	
	if (digit == code[15]) {
		printf("%s\n", code);
		return 0;
	} else {
		fprintf(stderr, "Error: invalid check digit.\n");
		return 3;
	}
}
