#include <stdio.h>


void fa(int a) {
	printf("%s: %d\n", "function a", a);
}

void fb(int b) {
	printf("%s: %d\n", "function b", b);
}

// pointer to function returning void
void (*signal_1) (int); 

// function prototype
void (*signal_2(int a, void (*func) (int))) (int);

// function definition
// function(signal_2) returning a pointer to fucntion, 
// signal_2 takes two arguments, one is an int, the other
// is a pointer to function
void (*signal_2(int a, void (*func) (int))) (int) {
	func(11111);
 	return fb;
 }

// error: ¡®signal_3¡¯ declared as function returning a function 
// void (signal_3(int a, void (*func) (int))) (int);

// error: ¡®signal_4¡¯ declared as function returning a function
// void (*signal_4)(int a, void (*func) (int)) (int);

// error: ¡®signal_5¡¯ declared as function returning a function
// void ((*signal_5)(int a, void (*func) (int))) (int);

// #########################################################
// so function cannot return a function,
// but function can return a pointer to function
// function is a address constant, but function pointer is a variable.
// ###################################################################

// pointer to function which returns a pointer to function
void (*(*signal_6)(int a, void (*func) (int))) (int);


int main() {
	signal_1 = fa;
	signal_1(1);

	signal_1 = signal_2(1, fa);
	signal_1(2);

	signal_6 = signal_2;
	signal_1 = signal_6(1, fa);
	signal_1(2);

	return 0;
}
