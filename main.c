#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define ARRAY_SIZE 65536

uint8_t data[ARRAY_SIZE] = {0};
uint8_t *data_ptr = data;
uint8_t *data_end = data + sizeof(data);

uint8_t helloworld[] = "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>-"
					   "--.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.";

int main(int argc, char **argv)
{
	uint8_t *prog, *prog_ptr, *end;
	int c, prog_len, brack_cnt = 0;

	if(argc == 1)
	{
		prog = helloworld;
		prog_len = sizeof(helloworld);
	}
	else
	{
		if(argv[1][0] == '-'  && argv[1][1] == 'f')
		{	
			FILE *fp = fopen(argv[2], "r");
			if(fp == NULL)
			{
				printf("Error reading file! %s\n", argv[2]);
				return -1;
			}

			fseek(fp, 0, SEEK_END);
			prog_len = ftell(fp);
			fseek(fp, 0, SEEK_SET);

			prog = malloc(prog_len + 1);
			fread(prog, prog_len, 1, fp);
		}
		else
		{
			prog_len = strlen(argv[1]);
			prog = malloc(prog_len + 1);
			//strcpying like a madman!
			strcpy((char *)prog, argv[1]);
		}
	}

	end = prog + prog_len;
	prog_ptr = prog;

	while(1)
	{
		switch(*prog_ptr)
		{
			//> 	increment the data pointer (to point to the next cell to the right).
			case '>':
				data_ptr++;
				break;
			//< 	decrement the data pointer (to point to the next cell to the left).
			case '<':
				if(data_ptr == data)
					return 0;
				data_ptr--;
				break;
			//+ 	increment (increase by one) the byte at the data pointer.
			case '+':
				if(data_ptr == data_end)
					return 0;
				(*data_ptr)++;
				break;
			//- 	decrement (decrease by one) the byte at the data pointer.
			case '-':
				(*data_ptr)--;
				break;
			//. 	output the byte at the data pointer.
			case '.':
				putchar(*data_ptr);
				break;
			//, 	accept one byte of input, storing its value in the byte at the data pointer.
			case ',':
				c = getchar();
				if(c != EOF)
					*data_ptr= c;
				else
					break;
				break;
			//[ 	if the byte at the data pointer is zero, then instead of moving the instruction
			//		pointer forward to the next command, jump it forward to the command after the 
			//		matching ] command.
			case '[':
				if(*data_ptr == 0)
				{
					brack_cnt = 0;
					do {
						if(*++prog_ptr == ']' && brack_cnt == 0)
							break;
						else if(*prog_ptr == '[')
							brack_cnt++;
						else if(*prog_ptr == ']')
							brack_cnt--;
						if(prog_ptr >= end)
							printf("lulz\n");
					} while(prog_ptr < end);
				}
				break;

			//] 	if the byte at the data pointer is nonzero, then instead of moving the 
			//		instruction pointer forward to the next command, jump it back to the 
			//		command after the matching [ command.
			case ']':
				if(*data_ptr != 0)
				{
					brack_cnt = 0;
					do {
						//printf("] jump\n");
						prog_ptr--;
						if(*prog_ptr == '[' && brack_cnt == 0)
							break;
						else if(*prog_ptr == ']')
							brack_cnt++;
						else if(*prog_ptr == '[')
							brack_cnt--;
					} while(prog_ptr > prog);
				}
				break;
			//Ignore whitespace
			case ' ': case '\t': case '\n': case '\r':
				break;
			//Just exits on comments for now
			case '#': case '\0':
				fflush(stdout);
				goto done;
		}	

		prog_ptr++;

		if(prog_ptr >= end || prog_ptr < prog)
			break;
	}
done:
	fflush(stdout);
	return 0;
}
