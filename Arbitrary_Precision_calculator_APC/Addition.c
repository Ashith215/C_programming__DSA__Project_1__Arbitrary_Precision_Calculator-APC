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


// function for addition.

data_t Addition(Dlist *h1, Dlist *t1, Dlist *h2, Dlist *t2, Dlist **r_h, Dlist **r_t)
{
	data_t data;
	data_t carry = 0;
	while(t1 != NULL || t2 != NULL)
	{
		// if first pointer reaches NULL and second pointer is not NULL.
		if(t1 == NULL)
		{
			data = t2->data + carry;
			t2 = t2->prev;
			if(carry == 1)		// if carry is 1.
			{
				if(data > 9)	// if data is greater than 9.
				{
					data = data % 10;
					if(insert_first(r_h, r_t, data) == FAILURE)
					{
						return FAILURE;
					}
						// if t2 is NULL
					if(t2 == NULL)
					{
						if(insert_first(r_h, r_t, 1) == FAILURE)
						{
							return FAILURE;
						}
						carry = 0;
					}
				}
				else		// if data less than 10.
				{
					if(insert_first(r_h, r_t, data) == FAILURE)
					{
						return FAILURE;
					}
					carry = 0;
				}
			}
			else			// if carry is 0.
			{
				if(insert_first(r_h, r_t, data) == FAILURE)
				{
					return FAILURE;
				}
				carry = 0;
			}
		}
		else if(t2 == NULL) 		// if second pointer reaches NULL and first pointer is not NULL.
		{
			data = t1->data + carry;
			t1 = t1->prev;
			if(carry == 1)		// if carry is 1.
			{
				if(data > 9)	// if data is greater than 9.
				{
					data = data % 10;
					if(insert_first(r_h, r_t, data) == FAILURE)
					{
						return FAILURE;
					}
						// if t1 is NULL.
					if(t1 == NULL)
					{
						if(insert_first(r_h, r_t, 1) == FAILURE)
						{
							return FAILURE;
						}
						carry = 0;
					}
				}
				else		// if data is less than 10.
				{
					if(insert_first(r_h, r_t, data) == FAILURE)
					{
						return FAILURE;
					}
					carry = 0;
				}
			}
			else			// if carry is 0.
			{
				if(insert_first(r_h, r_t, data) == FAILURE)
				{
					return FAILURE;
				}
			}
		}
		else				// if both are not NULL.
		{
			data = (t1->data) + (t2->data) + carry;
			t1 = t1->prev;
			t2 = t2->prev;

			if(data < 10)		// if data is less than 10.
			{
				carry = 0;
			}
			else			// if data is greater than 9.
			{
				carry = 1;
				data = data % 10;
			}
			if(insert_first(r_h, r_t, data) == FAILURE)
			{
				return FAILURE;
			}
		}
	}
	if(carry == 1)				// if carry is 1.
	{
		if(insert_first(r_h, r_t, 1) == FAILURE)
		{
			return FAILURE;
		}
	}
	return SUCCESS;
}
