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
