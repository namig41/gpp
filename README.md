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

## How to use it

Using ``make`` will create the ``gpp`` executable.

Simply run it with:

```
./gpp flie_input
```
