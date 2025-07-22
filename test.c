#include <stdio.h>
#include <unistd.h>


int main()
{

	const char* input = "ls | pwd | echo \"barev"\ ";



	while(input)
	{
		write(1, input, 1);
		input++;
	}
}