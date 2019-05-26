By: aelouarg <aelouarg@student.1337.ma>


# Description :
Are you tired of ft_putstr and ft_putnbr? Are you not allowed to use printf? Code your own! This will be an opportunity to discover a feature of the C - the variadic functions - and train you to fine management of display options. You will then have the right to use your printf in all your subsequent projects.

# Execution :
* ) Edit the file :  main.c .
* ) make re;gcc main.c libftprintf.a  ./a.out

# Flags : 
* ) conv :
	- diouxX	: The int (or appropriate variant) argument is converted to signed decimal (d and i), unsigned octal (o), unsigned decimal (u), or unsigned hexadecimal (x and X) notation.  The letters ''abcdef'' are used for x conversions; the letters ''ABCDEF'' are used for X conversions.  The precision, if any, gives the minimum number of digits that must appear; if the converted value requires fewer digits, it is padded on the left with zeros.

	- fF		: The double argument is rounded and converted to decimal notation in the style [-]ddd.ddd, where the number of digits after the decimal-point character is equal to the precision specification.  If the precision is missing, it is taken as 6; if the precision is explicitly zero, no decimal-point character appears.  If a decimal point appears, at least one digit appears before it.

	- c		: The int argument is converted to an unsigned char, and the resulting character is written.

	- s		: The char * argument is expected to be a pointer to an array of character type (pointer to a string).  Characters from the array are written up to (but not including) a terminating NUL character; if a precision is specified, no more than the number specified are written.  If a precision is given, no null character need be present; if the precision is not specified, or is greater than the size of the array, the array must contain a terminating NUL character

	- p		: The void * pointer argument is printed in hexadecimal (as if by '%#x' or '%#lx').

	- %		: A '%' is written.  No argument is converted.  The complete conversion specification is '%%'.

* ) flags :
	- [#]: hash.
	- [0]: zero.
	- [ ]: space.
	- [+]: plus.
	- [-]: minus.
	- [.]: precision.
	- [x]: width, (x) being replaced with an int.
* ) bonus :
	- %b : print integer in binary.
	- %t : convert seconds (int) to period (month/days/hours/minutes/seconds).
	- %k : print colour font/background.
			- example:
				ft_printf("This string is written in %kred%k, while this %kbackground is green%k", "red", "end", "GREEN", "end");
	- %n : print non printable characters.

			- example:
				char	*str = "A string\e\twith\nnon_printable\bcharacters.";

				ft_printf("%n", str);
		 

