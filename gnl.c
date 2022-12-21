#include "stdio.h"
#include "fcntl.h"
#include "stdlib.h"
#include "unistd.h"

// char *get_next_line(int fd)
// {
//     int 	i = 0;
//     int 	rd = 0;
//     char	character;
//     char 	*buffer = malloc(10000);

//     while ((rd = read(fd, &character, 1)) > 0)
//     {
//         buffer[i++] = character;
//         if (character == '\n')
//             break;
//     }
//     if ((!buffer[i - 1] && !rd) || rd == -1)
//     {
//         free(buffer);
//         return (NULL);
//     }
//     buffer[i] =  '\0';
//     return(buffer);
// }

char *get_next_line(int fd)
{
	char *string = malloc(10000), *copy = string;
	while (read(fd, copy, 1) > 0 && *copy++ != '\n');
	return (copy > string) ? (*copy = 0, string) : (free(string), NULL);
}

int main()
{
	int fd = open("./t.txt", O_RDONLY);
	char *s = get_next_line(fd);
	printf("%s", s);
	while (s)
	{
		s = get_next_line(fd);
		printf("%s", s);
	}
		
	return(1);
}