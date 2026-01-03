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


// function for multiplication. 

data_t Multiplication(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **r_h, Dlist **r_t)
{
	Dlist *res_head = NULL;
	Dlist *res_tail = NULL;
	Dlist *hr1 = NULL;
	Dlist *tr1 = NULL;
	Dlist *hr2 = NULL;
	Dlist *tr2 = NULL;
	data_t carry = 0;
	data_t count = 0;
	Dlist *c_h = NULL;
	Dlist *c_t = NULL;
	data_t data;
	
	Dlist *t2 = tail2;
	while(t2 != NULL)
	{
		Dlist *t1 = tail1;
		carry = 0;
		while(t1 != NULL)
		{
			data = ((t1->data) * (t2->data)) + carry;
			t1 = t1->prev;
			if(data > 9)		// if data is greater than 9.
			{
				carry = data / 10;
				data = data % 10;
			}
			else			// if data is less than 10.
			{
				carry = 0;
			}
			
			if(count == 0)		// if count is 0.
			{
				// function insert first is called.
				if(insert_first(&res_head, &res_tail, data) == FAILURE)
				{
					return FAILURE;
				}
				if(t1 == NULL && carry != 0)
				{
					// function insert first is called.
					if(insert_first(&res_head, &res_tail, carry) == FAILURE)
					{
						return FAILURE;
					}
				}
			}
			else			// if count is not 0.
			{
				// function insert first is called.
				if(insert_first(&hr1, &tr1, data) == FAILURE)
				{
					return FAILURE;
				}
				if(t1 == NULL && carry != 0)
				{
					// function insert first is called.
					if(insert_first(&hr1, &tr1, carry) == FAILURE)
					{
						return FAILURE;
					}
				}
			}
		}
		if(res_tail != NULL && tr1 != NULL)		// if res_tail and tr1 is not NULL.
		{
			// function for addition is called.
			if(Addition(res_head, res_tail, hr1, tr1, &hr2, &tr2) == FAILURE)
			{
				return FAILURE;
			}
			// function for delete nodes is called.
			if(delete_nodes(&res_head, &res_tail) == FAILURE)
			{
				return FAILURE;
			}
			// function for delete nodes is called.
			if(delete_nodes(&hr1, &tr1) == FAILURE)
			{
				return FAILURE;
			}
			res_head = hr2;
			res_tail = tr2;
			hr2 = NULL;
			tr2 = NULL;
		}
		count = 1;
		// function insert first is called.
		if(insert_first(&c_h, &c_t, 0) == FAILURE)
		{
			return FAILURE;
		}
		Dlist *temp = c_t;
		while(temp != NULL)				// insert zeros starting from 1 from 2nd result list.
		{
			int c_data = temp->data;
			// function insert first is called.
			if(insert_first(&hr1, &tr1, c_data) == FAILURE)
			{
				return FAILURE;
			}
			temp = temp->prev;
		}
		t2 = t2->prev;
	}
	// function for delete nodes is called.
	if(delete_nodes(&c_h, &c_t) == FAILURE)
	{
		return FAILURE;
	}
	// function for delete nodes is called.
	if(delete_nodes(&hr1, &tr1) == FAILURE)
	{
		return FAILURE;
	}
	*r_h = res_head;
	*r_t = res_tail;
	res_head = NULL;
	res_tail = NULL;
	// function for remove zeros from start is called.
	if(remove_zeros_from_start(r_h) == FAILURE)
        {
                return FAILURE;
        }
	return SUCCESS;
}



