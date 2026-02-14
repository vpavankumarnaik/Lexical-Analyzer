#include "header.h"

int main(int argc, char *argv[]) 
{
	char ch, next;
	char buffer[100];
	int i = 0;
	int paranthesis = 0, curly = 0, line = 1;

	FILE *fp = fopen(argv[1], "r");

    	if(fp == NULL)
    	{
        	printf(RED"ERROR: File not found!\n"RESET);
        	return 1;
    	}

    	printf(MAGENTA"--------------- LEXICAL ANALYZER STARTED ---------------\n\n"RESET);
	printf(YELLOW"--------------------------------------------------------\n"RESET);
	printf(BLUE"%-8s| %-23s | %s\n", "Line No.", "TOKEN TYPE", "LEXEMES"RESET);
	printf(YELLOW"--------------------------------------------------------\n"RESET);
    	while((ch = fgetc(fp)) != EOF) 
    	{
		if(ch == '#')
	    	{
			buffer[i++] = ch;
		    	while((ch = fgetc(fp)) != '\n')
		    	{
				buffer[i++] = ch;
		    	}
		    	buffer[i] = '\0';
		    	printf(CYAN"Line %2d : %-23s : %s\n"RESET, line, "Preprocessor directive", buffer);
		    	i = 0;
			line++;
		    	continue;
	    	}

		if(ch == '/')			//for comments 
		{
            		next = fgetc(fp);

            		if(next == '/')		// Remove Single Line Comment 
	    		{
                		while((ch = fgetc(fp)) != '\n');
                		line++;
				continue;
            		}
            		else if(next == '*')	// Remove Multi Line Comment 
	    		{
				while(1)
				{
                    			ch = fgetc(fp);
                    			next = fgetc(fp);

                    			if(ch == '*' && next == '/')
        	                		break;
                		}
                		continue;
            		}
            		else 
	    		{
                		ungetc(next, fp);
                		printf(CYAN"Line %2d : %-23s : /\n"RESET, line, "Operator");
            		}
        	}
	
        	/* Remove String Literals */
        	if(ch == '"') 
		{
			buffer[i++] = '"';
			while((ch = fgetc(fp)) != EOF && ch != '"')
			{
				if(ch == '\n')
				{
					printf(RED"Error: Double Quotes Missing\n"RESET);
					fclose(fp);
					return 1;
				}
				else
				{
					buffer[i++] = ch;
				}
			}
			buffer[i++] = '"';
			buffer[i] = '\0';

			printf(CYAN"Line %2d : %-23s : %s\n"RESET, line, "String Literal", buffer);
			i = 0;
            		continue;
        	}

        	/* Build identifiers / keywords / numbers */
        	if(isalnum(ch) || ch == '_') 
		{
            		buffer[i++] = ch;
        	}
        	else if(ch == '.' && i > 0)	/* Float numbers */ 
		{
            		buffer[i++] = ch;
        	}
        	else						/* When separator */ 
		{
            		buffer[i] = '\0';

            		if(i > 0) 
	    		{
                		if(iskeyword(buffer))
                    			printf(CYAN"Line %2d : %-23s : %s\n"RESET, line, "Reserve Keyword", buffer);

				else if(iskeyword_non(buffer))
                    			printf(CYAN"Line %2d : %-23s : %s\n"RESET, line, "Non Reserve Keyword", buffer);
                
				else if(isdigit(buffer[0]))
                	    		printf(CYAN"Line %2d : %-23s : %s\n"RESET, line, "Constant", buffer);

                		else
                    			printf(CYAN"Line %2d : %-23s : %s\n"RESET, line, "Identifier", buffer);
            		}

            		i = 0;

            		/* Double Operators */
            		if(ch == '=' || ch == '>' || ch == '<' || ch == '!') 
	    		{
                		next = fgetc(fp);

                		if(next == '=') 
				{
                    			printf(CYAN"Line %2d : %-23s : %c=\n"RESET, line, "Operator", ch);
                		}
                		else 
				{
                    			ungetc(next, fp);
                    			printf(CYAN"Line %2d : %-23s : %c\n"RESET, line, "Operator", ch);
                		}
            		}
            		else if(isoperator(ch)) /* Single Operators */
	    		{
                		printf(CYAN"Line %2d : %-23s : %c\n"RESET, line, "Operator", ch);
            		}
            		else if(issymbol(ch)) /* Special Symbols */ 
	    		{
                		printf(CYAN"Line %2d : %-23s : %c\n"RESET, line, "Symbol", ch);
            		}
        	}

		if(ch == '(')
			paranthesis++;
		else if(ch == ')')
			paranthesis--;
		else if(ch == '{')
			curly++;
		else if(ch == '}')
			curly--;
		
		if(paranthesis < 0)
		{
			printf(RED"Error: Parenthesis not balanced\n"RESET);
    			fclose(fp);
			return 1;
		}
		if(curly < 0)
		{
			printf(RED"Error: Curly Brackets not balanced\n"RESET);
    			fclose(fp);
			return 1;
		}
		
		if(ch == '\n')
		{
			line++;
		}
    	}

	if(i > 0)
	{
    		buffer[i] = '\0';

    		if(iskeyword(buffer))
      	  		printf(CYAN"Line %2d : %-23s : %s\n"RESET, line, "Reserve Keyword", buffer);
    	
		else if(iskeyword_non(buffer))
        		printf(CYAN"Line %2d : %-23s : %s\n"RESET, line, "Non Reserve Keyword", buffer);
    	
		else if(isdigit(buffer[0]))
        		printf(CYAN"Line %2d : %-23s : %s\n"RESET, line, "Constant", buffer);
    	
		else
        		printf(CYAN"Line %2d : %-23s : %s\n"RESET, line, "Identifier", buffer);
	}

    	fclose(fp);

	if(paranthesis != 0)
	{
		printf(RED"Error: Parenthesis not balanced\n"RESET);
		return 1;
	}
	if(curly != 0)
	{
		printf(RED"Error: Curly Brackets not balanced\n"RESET);
		return 1;
	}
	
    	printf(GREEN"---------------- COMPLETED SUCCESSFULLY ----------------\n\n"RESET);
    	return 0;
}
