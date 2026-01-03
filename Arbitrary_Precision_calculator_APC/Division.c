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


// function for division.

data_t Division(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **r_h, Dlist **r_t)
{
	// if single node present and data of that node is zero.
	if(head2 == tail2 && head2->data == 0)
	{
		printf("ERROR: Cannot divide by zero(0).\n");
		return FAILURE;
	}

	data_t r = 1;
	
	// function compare for modulus is called.
	if(compare_for_division_or_modulus(head1, tail1, head2, tail2, &r) == FAILURE)
	{
		return FAILURE;
	}
	if(r == -1)	// if r is -1, that is if list-2 is greater.
	{
		// function insert first is called.
		if(insert_first(r_h, r_t, 0) == FAILURE)
		{
			return FAILURE;
		}
		return SUCCESS;
	}
	if(r == 0)	// if r is 0, that is if list-1 and list-2 are equal.
	{
		// function insert first is called.
		if(insert_first(r_h, r_t, 1) == FAILURE)
		{
			return FAILURE;
		}
		return SUCCESS;
	}


	Dlist *count_h = NULL;
	Dlist *count_t = NULL;
	// function insert first is called.
	if(insert_first(&count_h, &count_t, 1) == FAILURE)
	{
		return FAILURE;
	}
	Dlist *inc_h = NULL;
	Dlist *inc_t = NULL;
	// function insert first is called.
	if(insert_first(&inc_h, &inc_t, 1) == FAILURE)
	{
		return FAILURE;
	}
	
	
	Dlist *h2 = NULL;
	Dlist *t2 = NULL;
	// function insert first is called.
	if(insert_first(&h2, &t2, 0) == FAILURE)
	{
		return FAILURE;
	}
	// function for addition is called. 
	if(Addition(h2, t2, head2, tail2, r_h, r_t) == FAILURE)
	{
		return FAILURE;
	}
	// function delete nodes is called.
	if(delete_nodes(&h2, &t2) == FAILURE)
	{
		return FAILURE;
	}

	h2 = *r_h;
	t2 = *r_t;
	*r_h = NULL;
	*r_t = NULL;
	
	while(r)
	{
		// function for addition is called. 
		if(Addition(h2, t2, head2, tail2, r_h, r_t) == FAILURE)
		{
			return FAILURE;
		}
		// function delete nodes is called.
		if(delete_nodes(&h2, &t2) == FAILURE)
		{
			return FAILURE;
		}
		h2 = *r_h;
		t2 = *r_t;
		*r_h = NULL;
		*r_t = NULL;
		// function compare for division is called.
		if(compare_for_division_or_modulus(head1, tail1, h2, t2, &r) == FAILURE)
		{
			return FAILURE;
		}
		if(r == -1)
		{
			break;
		}
		if(r == 0)
		{
			r = 1;
		}

		// function for addition is called. 
		if(Addition(count_h, count_t, inc_h, inc_t, r_h, r_t) == FAILURE)
		{
			return FAILURE;
		}
		// function delete nodes is called.
		if(delete_nodes(&count_h, &count_t) == FAILURE)
		{
			return FAILURE;
		}
		count_h = *r_h;
		count_t = *r_t;
		*r_h = NULL;
		*r_t = NULL;
	}
	// function delete nodes is called.
	if(delete_nodes(&inc_h, &inc_t) == FAILURE)
	{
		return FAILURE;
	}
	*r_h = count_h;
	*r_t = count_t;
	count_h = NULL;
	count_t = NULL;
	return SUCCESS;
}


