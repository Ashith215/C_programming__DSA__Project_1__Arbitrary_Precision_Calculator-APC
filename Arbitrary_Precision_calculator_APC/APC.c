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

// function to validate command-line arguments.

data_t validate_args(char *argv[])
{
	// if operator => '+' , '-' , 'x' , 'X' , '/' , '%'
	if((strcmp(argv[2], "+") == 0) || (strcmp(argv[2], "-") == 0) || (strcmp(argv[2], "X") == 0) || ((strcmp(argv[2], "x") == 0)) || (strcmp(argv[2], "/") == 0) || (strcmp(argv[2], "%") == 0))
	{
		data_t j = 1;
		while(j <= 3)
		{
			data_t i = 0;
			while(argv[j][i] != '\0')
			{
				if(i == 0)
				{
					// if first character of string is not digit or plus/minus sign. 
					if(!(argv[j][i] >= '0' && argv[j][i] <= '9' || argv[j][i] == '+' || argv[j][i] == '-'))
					{
						return FAILURE;
					}
				}
				else
				{
					// if remaining characters are not digits.
					if(!(argv[j][i] >= '0' && argv[j][i] <= '9'))
					{
						return FAILURE;
					}
				}
				i++;
			}
			j = j + 2;
		}
		return SUCCESS;
	}
	return FAILURE;
}


// function for string to double linked list conversion.

data_t convert_str_to_list(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, data_t *f1, data_t *f2, char *argv[])
{
	data_t data;

	data_t j = 1;
	while(j <= 3)
	{
		data_t i = 0;
		while(argv[j][i] != '\0')
		{
			if(i == 0 && (argv[j][i] == '+' || argv[j][i] == '-'))	// first character of string is plus/minus sign or digit.
			{
				if(argv[j][i] == '+')				// if positive sign, then update corresponding flag value to zero.
				{
					if(j == 1)
					{
						*f1 = 0;
					}
					else
					{
						*f2 = 0;
					}
				}
				else						// if negative sign, then update corresponding flag value to one.
				{
					if(j == 1)
					{
						*f1 = 1;
					}
					else
					{
						*f2 = 1;
					}
				}	
			}
			else							// remaining digits is only digits.						
			{
				data = argv[j][i] - '0';

				if(j == 1)
				{						// insert last function called.
					if(insert_last(head1, tail1, data) == FAILURE)
					{
						return FAILURE;
					}
				}
				else
				{						// insert last function called.
					if(insert_last(head2, tail2, data) == FAILURE)
					{
						return FAILURE;
					}
				}
			}
			i++;
		}
		j = j + 2;
	}
	return SUCCESS;
}


// function for operation validation.

void operation_validation(data_t *f1, data_t *f2, data_t *res_flg, char *op, char *argv[])
{
	// if operator is addition or subtraction.
	if(argv[2][0] == '+' || argv[2][0] == '-')
	{
		if((*f1) == 0 && (*f2) == 0)		// if both operand are positive.
		{
			*op = argv[2][0];
		}
		else if((*f1) == 0 && (*f2) == 1)  	// if operand-1 is positive and operand-2 is negative.
		{
			if((argv[2][0]) == '+')
			{
				*op = '-';
			}
			else
			{
				*op = '+';
			}
		}
		else if((*f1) == 1 && (*f2) == 0)  	// if operand-1 is negative and operand-2 is positive.
		{
			if((argv[2][0]) == '+')
			{
				*op = '-';
				*res_flg = 1;
			}
			else
			{
				*op = '+';
				*res_flg = 1;
			}
		}
		else				  	// if both operands are negative.
		{
			if((argv[2][0]) == '+')
			{
				*op = argv[2][0];
				*res_flg = 1;
			}
			else
			{
				*op = argv[2][0];
				*res_flg = 1;
			}
		}
	}
	else if(argv[2][0] == '%')			// if operator is modulus.
	{
		if(*f1 == 0)
		{
			*res_flg = 0;
		}
		else
		{
			*res_flg = 1;
		}
		*op = argv[2][0];
	}
	else						// if operator is division or multiplication.
	{
							// if both operands are positive or negative. 
		if((*f1 == 0 && *f2 == 0) || (*f1 == 1 && *f2 == 1))
		{
			*res_flg = 0;
		}
		else					// if operand-1 and operand-2 has different signs.
		{
			*res_flg = 1;
		}
		*op = argv[2][0];
	}

}


// function to insert last of list.

data_t insert_last(Dlist **head, Dlist **tail, data_t data)
{
	// node is created.
	Dlist *new = malloc(sizeof(Dlist));
	// if node not created.
	if(new == NULL)
	{
		printf("ERROR: New node is not created.\n");
		return FAILURE;
	}
	new->data = data;
	new->next = NULL;
	new->prev = *tail;
	// if passed list is empty.
	if(*head == NULL)
	{
		*head = new;
		*tail = new;
		return SUCCESS;
	}
	// if passed node is not empty.
	(*tail)->next = new;
	*tail = new;
	return SUCCESS;
}


// function to insert first of list.

data_t insert_first(Dlist **head, Dlist **tail, data_t data)
{
	// node is created.
	Dlist *new = malloc(sizeof(Dlist));
	// if node not created.
	if(new == NULL)
	{
		printf("ERROR: List is Empty.\n");
		return FAILURE;
	}
	new->data = data;
	new->next = *head;
	new->prev = NULL;
	// if passed list is empty.
	if(*head == NULL)
	{
		*tail = new;
		*head = new;
		return SUCCESS;
	}
	// if passed node is not empty.
	(*head)->prev = new;
	*head = new;
	return SUCCESS;
}


// function to print result.

void print_result(Dlist *head, data_t res_flg)
{
	// prints sign if negative.
	if(res_flg == 1)
	{
		printf("-");
	}
	
	// prints data
	while(head != NULL)
	{
		printf("%d", head->data);
		head = head->next;
	}
}


// function to delete all nodes.

data_t delete_nodes(Dlist **head, Dlist **tail)
{
	// if list empty.
	if(*head == NULL)
	{
		printf("ERROR: LIST is Empty.\n");
		return FAILURE;
	}
	// delete all nodes.
	while(*head != NULL)
	{
		*head = (*head)->next;
		// if head reaches NULL.
		if(*head == NULL)
		{
			free(*tail);
			*tail = NULL;
			break;
		}
		free((*head)->prev);
	}
	return SUCCESS;
}


// function to delete first element.

data_t delete_first(Dlist **head)
{
	// if list empty or list has only one node.
	if(*head == NULL || (*head)->next == NULL)
	{
		return FAILURE;
	}
	
	Dlist *temp = *head;
	*head = (*head)->next;
	(*head)->prev = NULL;
	free(temp);
	return SUCCESS;
}


// function to remove zero's from start.

data_t remove_zeros_from_start(Dlist **head)
{
	// if list empty.
	if(*head == NULL)
	{
		printf("ERROR: LIST is Empty.\n");
		return FAILURE;
	}

	Dlist *temp = *head;
	while(temp->next != NULL)
	{
		temp = *head;
		// if zero is present at start then delete that node else break.
		if(temp->data == 0)
		{
			delete_first(head);
		}
		else
		{
			break;
		}
	}
	return SUCCESS;
}
