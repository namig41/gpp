# gpp 

A simple compiler for a very simple toy language. This is a learning project that focuses on simplicity to keep things easy to understand. There will be things that could be done more efficiently, but that's not the point.

## The language grammar

### Type specifier
```
INT
STRING
```

### Variable definition
```c
var a = 3;
var abc = "Hello World!";
var isValue = 1234535;
```

### Funciton definition
```c
def main(a, b) {
	def println(a, b) {
		print(a);
		print(" ");
		print(b);
	};
	println(a, b);
};

main("Hello", "World!");
```

### Assignment
```c
var a = 3;

a = "Hello World";
```
### Evaluate arithmetic expression
```c
def main() {
	def println(x) {
		print(x);	
		print("\n");	
	};
	var a = 2 * 3 + 4 * 5 + 2 * (1 + 3);
	var b = 3 / 3 + 4 / 2;

	println(a);
	println(b);

	a = a + b;

	println(a);
};

main();

output:
34
3
37
```
### If expression
```c
var a = 0;

it (a < 10) {
	print("Hello, World!\n");
};
```
### While loop
```c
var a = 0;

while (a < 10) {
	print(a);
	print("\n");
	a = a + 1;
};
```

## How to use it

Using ``make`` will create the ``gpp`` executable.

Simply run it with:

```
./gpp file_input
```
