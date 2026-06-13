
defaut:
	# TODO: Fix this build command, there's not build command that takes
	# a bunch of c source files and convert them into object files
	clang -Wall -Werror -std=c99 -fPIC -c src/*.c -Iinclude -o build/obj/*.o
	clang -shared build/obj/*.o -o build/libsnowflakeid-linux-aarch64.so
