#include <memory>
#include <string>
#include <iostream>

// two ways to print sp and bp

void func2(int64_t c)
{
	int32_t a;
	register int sp asm ("sp");
	register int bp asm ("bp");
	printf("bp=%x sp=%x\n", bp, sp);
	printf("%p\n", __builtin_frame_address(0));
	printf("%p\n", __builtin_frame_address(1));
	printf("%p\n", __builtin_frame_address(2));
}

int func(int64_t c)
{
	int64_t a;
	register int sp asm ("sp");
	register int bp asm ("bp");
	printf("bp=%x sp=%x\n", bp, sp);
	func2(a);
}

int main()
{
	int64_t a;
	register int sp asm ("sp");
	register int bp asm ("bp");
	printf("bp=%x sp=%x\n", bp, sp);
	func(a);
}


