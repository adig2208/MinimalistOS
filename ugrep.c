/*
 * file: ugrep.c - project-1-part2 micro-program
 */

extern void readline(char *buf, int len);
extern void print(char *buf);
extern char *getarg(int i);

/*
 * Crude string functions.
 */
int strings_equal(char *s1, char *s2)
{
	while (*s1 != 0)
		if (*s1 != *s2)
			return 0;
		else
			s1++, s2++;
	return 1;
}

int string_contains(char *pattern, char *str)
{
	while (*str != 0) {
		if (strings_equal(pattern, str))
			return 1;
		str++;
	}
	return 0;
}

int main(void)
{
	char buf[128];
	char *pattern = getarg(1);

	if (pattern == 0 || getarg(2) != 0) {
		print("usage: uprog <pattern>\n");
		return 0;
	}

	print("ugrep: enter blank line to quit\n");

	for (;;) {
		readline(buf, sizeof(buf));
		if (buf[0] == '\n' || buf[0] == 0)
			break;
		if (string_contains(pattern, buf)) {
			print("-- ");
			print(buf);
		}
	}
	return 0;
}

