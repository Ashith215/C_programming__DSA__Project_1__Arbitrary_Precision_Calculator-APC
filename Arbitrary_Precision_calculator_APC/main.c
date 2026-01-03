/*
 *      Name            :       Ashith P Amin
 *
 *      Date            :       10 / 12 / 2025
 *
 *      Description     :       Arbitrary Precision Calculator ( APC ) Project :
 *
 *                              - Validation & Conversion :
 *
 *                                      -> command-line arguments should be exactly 4.
 *                                      -> 2nd and 4th command-line arguments should be operand, operand can contain '+' or '-' sign in first index.
 *                                      -> First index of operand can be sign or digit and remaining index should only contain digits.
 *                                      -> 3rd command-line argument should be any one operator only( '+'/'-'/('X'/'x')/'/'/'%' ).
 *                                      -> Converting operand strings to double linked list.
 *                                      -> Removing extra zero's if present at start.
 *                                      -> Validating operator by comparing the sign's present in operands and operator.
 *
 *
 *                              1). Addition :
 *
 *                                      -> Adding data stored in double linked list from last( tail ) of operand-1 ad operand-2.
 *                                      -> Added data is inserted at first of result list.
 *                                      -> Carry is used if data added is more than 9.
 *
 *                              2). Subtraction :
 *
 *                                      -> First operands are re-arranged such that larger value first & then smaller value  and then values subtracted.
 *                                      -> Borrow is used to subtract lower digit from higher digit.
 *                                      -> Subtracted data is inserted at first of result list.
 *
 *                              3). Multiplication :
 *
 *                                      -> Operand-2 one-digit is multiplied by one by one digit of operand-1 using carry.
 *                                      -> For 2nd result, result starts with 1 zero and 3rd with 2 zero's and so-on.
 *                                      -> After getting 2 results, then these 2 results are added and then 3rd result added and so-on.
 *                                      -> Multiplication results are inserted one by one at first of result list.
 *
 *                              4). Division :
 *
 *                                      -> If operand-2 is zero, then print error - division not possible.
 *                                      -> If operand-1 and operand-2 are equal, then result is 1.
 *                                      -> If operand-1 is less than operand-2, then result is 0.
 *                                      -> If operand-1 is greater than operand-2, then division is done by addition method.
 *                                      -> Zero is added with operand-2 and stored in result.
 *                                      -> In addition method, operand-2 value is added with result and result updated.
 *                                      -> Addition is done and count is incremented till result value is equal or less then operand-1.
 *
 *                              5). Modulus :
 *
 *                                      -> If any one of the operand is zero or both are zero, then result is zero.
 *                                      -> If operand-1 is less than operand-2, then result is operand-1.
 *                                      -> If operand-1 is equal to operand-2, then result is zero.
 *                                      -> If operand-1 is greater than operand-2, then division is done by addition method.
 *                                      -> Similar like division operation, but difference is if operand-2 divides operand-1 exactly then result is zero.
 *                                      -> And if doesn't divides exactly, then result is subtracted with operand-2 and result is updated.
 *                                      -> And then updated result is subtracted with operand-1 and final result is obtained.
 *                                      -> Ex: 21%5 -> 25-5=20 -> 21-20=1 - result.
 */



#include "APC.h"

data_t main(data_t argc, char *argv[])
{
	if(argc == 4)
	{
		// validate args.
		if(validate_args(argv) == FAILURE)
		{
			printf("\n-----------------------------------------------------------------------------------------------------\n");
			printf("\nERROR: ");
                	for(int i=0; i<argc; i++)
                	{
                	        printf("%s ", argv[i]);                                              // prints command-line arguments user entered.
                	}
                	printf(": INVALID ARGUMENTS\nUSAGE:\n");
                	printf("Addition 	: ./a.out <operand1> < operator ( + )   > <operand2>\n");
                	printf("Subtraction 	: ./a.out <operand1> < operator ( - )   > <operand2>\n");
                	printf("Multiplication 	: ./a.out <operand1> < operator ( x/X ) > <operand2>\n");
                	printf("Division 	: ./a.out <operand1> < operator ( / )   > <operand2>\n");
                	printf("Modulus 	: ./a.out <operand1> < operator ( %% )   > <operand2>\n");
			printf("\n-----------------------------------------------------------------------------------------------------\n\n");
			return FAILURE;
		}

		data_t flag1 = 0;
		data_t flag2 = 0;
		data_t res_flag = 0;

		Dlist *head1 = NULL;
		Dlist *tail1 = NULL;
		Dlist *head2 = NULL;
		Dlist *tail2 = NULL;
		Dlist *res_h = NULL;
		Dlist *res_t = NULL;

		if(convert_str_to_list(&head1, &tail1, &head2, &tail2, &flag1, &flag2, argv) == FAILURE)
		{
			printf("ERROR: Failed to Convert string to Double Linked List.\n");
			return FAILURE;
		}

		if(remove_zeros_from_start(&head1) == FAILURE)
		{
			return FAILURE;
		}
		if(remove_zeros_from_start(&head2) == FAILURE)
		{
			return FAILURE;
		}

		char op;
		operation_validation(&flag1, &flag2, &res_flag, &op, argv);

		switch(op)
		{
			case '+':
				if(Addition(head1, tail1, head2, tail2, &res_h, &res_t) == FAILURE)
				{
					printf("ERROR: Addition Failed!\n");
					return FAILURE;
				}
				break;
			case '-':
				if(Subtraction(head1, tail1, head2, tail2, &res_h, &res_t, &res_flag) == FAILURE)
				{
					printf("ERROR: Subtraction Failed!\n");
					return FAILURE;
				}
				break;
			case 'X':
			case 'x':
				if(Multiplication(head1, tail1, head2, tail2, &res_h, &res_t) == FAILURE)
				{
					printf("ERROR: Multiplication Failed!\n");
					return FAILURE;
				}
				break;
			case '/':
				if(Division(head1, tail1, head2, tail2, &res_h, &res_t) == FAILURE)
				{
					printf("ERROR: Division Failed!\n");
					return FAILURE;
				}
				break;
			case '%':
				if(Modulus(head1, tail1, head2, tail2, &res_h, &res_t) == FAILURE)
				{
					printf("ERROR: Modulus Failed!\n");
					return FAILURE;
				}
				break;
			default:
				printf("Invalid Operator!\n");
		}

		// if result is zero, then sign is removed.
		if(res_h == res_t)
		{
			if(res_h->data == 0)
			{
				res_flag = 0;
			}
		}

		printf("|-------------------------------------------------------------------------------------------------------------|\n\n");
		if(argv[2][0] == '+')
		{
			printf(" Addition of Two Numbers \n\n");
		}
		else if(argv[2][0] == '-')
		{
			printf(" Subtraction of Two Numbers \n\n");
		}
		else if(argv[2][0] == 'X' || argv[2][0] == 'x')
		{
			printf(" Multiplication of Two Numbers \n\n");
		}
		else if(argv[2][0] == '/')
		{
			printf(" Division of Two Numbers \n\n");
		}
		else if(argv[2][0] == '%')
		{
			printf(" Modulus of Two Numbers \n\n");
		}
		printf("|-------------------------------------------------------------------------------------------------------------|\n\n");
		printf(" Operand-1  	->	%s\n\n", argv[1]);
		printf(" Operator  	-> 	%c\n\n", argv[2][0]);
		printf(" Operand-2  	-> 	%s\n\n", argv[3]);
		printf("|-------------------------------------------------------------------------------------------------------------|\n\n");
		printf(" Result  	-> 	");
		print_result(res_h, res_flag);
		printf("\n\n");
		printf("|-------------------------------------------------------------------------------------------------------------|\n");
		if(delete_nodes(&head1, &tail1) == FAILURE)
		{
			return FAILURE;
		}
		if(delete_nodes(&head2, &tail2) == FAILURE)
		{
			return FAILURE;
		}
		if(delete_nodes(&res_h, &res_t) == FAILURE)
		{
			return FAILURE;
		}
		head1 = tail1 = head2 = tail2 = res_h = res_t = NULL;
	}
	else
	{
		printf("\n-----------------------------------------------------------------------------------------------------\n");
		printf("\nERROR: ");
                for(int i=0; i<argc; i++)
                {
                        printf("%s ", argv[i]);                                                         // prints command-line arguments user entered.
                }
                printf(": INVALID ARGUMENTS\nUSAGE:\n");
                printf("Addition 	: ./a.out <operand1> < operator ( + )   > <operand2>\n");
                printf("Subtraction 	: ./a.out <operand1> < operator ( - )   > <operand2>\n");
                printf("Multiplication 	: ./a.out <operand1> < operator ( x/X ) > <operand2>\n");
                printf("Division 	: ./a.out <operand1> < operator ( / )   > <operand2>\n");
                printf("Modulus 	: ./a.out <operand1> < operator ( %% )   > <operand2>\n");
		printf("\n-----------------------------------------------------------------------------------------------------\n\n");
	}
	return FAILURE;
}
