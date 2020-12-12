setup:
	@gcc cripto.c -o cripto -lm -std=c99 -Wall -Werror -pedantic && gcc geranum.c -o geranum -lm -std=c99 -Wall -Werror -pedantic