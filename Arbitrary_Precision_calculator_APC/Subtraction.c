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

data_t Subtraction(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **r_h, Dlist **r_t, data_t *res_flg)
{
	Dlist *t1 = NULL;
	Dlist *t2 = NULL;

	// function for nums order to subtract.
	if(nums_order_to_sub(head1, tail1, head2, tail2, &t1, &t2, res_flg) == FAILURE)
	{
		return FAILURE;
	}
	
	data_t data;
	data_t count = 0;
	data_t borrow = 0;

	while(t1 != NULL)
	{
		if(t2 == NULL)						// if t2 is NULL
		{
			if(borrow == 1 && t1->data != 0)		// if borrow is 1 and data is not 0.
			{
				data = t1->data - 1;
				borrow = 0;
				count = 0;
			}
			else if(borrow == 1 && t1->data == 0)		// if borrow is 1 and data is 0.
			{
				data = t1->data + 10 - 1;
			}
			else						
			{
				data = t1->data;
			}
			t1 = t1->prev;
		}
		else							// if t2 is not NULL.
		{
			if((t1->data) < (t2->data))			// if t1 data is less than t2 data.
			{
				borrow = 1;
				if(count == 0)				// if count is zero.
				{
					data = (t1->data + 10) - t2->data;
				}
				else					// if count is not zero.
				{
					data = (t1->data + 10 - 1) - t2->data;
				}
				count = 1;
			}
			else if(t1->data > t2->data)			// if t1 data is greater than t2 data.
			{
				if(borrow == 1)				// if borrow is 1.
				{
					data = (t1->data - 1) - t2->data;
					borrow = 0;
					count = 0;
				}
				else					// if borrow is 0.
				{
					data = t1->data - t2->data;
				}
			}
			else						// if t1 data is equal to t2 data.
			{
				if(borrow == 1)				// if borrow is 1.
				{
					data = (t1->data + 10 - 1) - t2->data;
				}
				else					// if borrow is 0.
				{
					data = t1->data - t2->data;
				}
			}
			t1 = t1->prev;
			t2 = t2->prev;
		}
		// function for insert first is called.
		if(insert_first(r_h, r_t, data) == FAILURE)
		{
			return FAILURE;
		}
	}
	// function for remove zeros from start is called.
	if(remove_zeros_from_start(r_h) == FAILURE)
	{
		return FAILURE;
	}
	return SUCCESS;
}



data_t nums_order_to_sub(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **t1, Dlist **t2, data_t *res_flg)
{
	// if both or any one input list are empty.
	if(tail1 == NULL || tail2 == NULL)
	{
		printf("ERROR: Passed List for nums order to subtract is empty.\n");
		return FAILURE;
	}
	
	Dlist *p1 = tail1;
	Dlist *p2 = tail2;
	// compares length size of list.
	while(p1 != NULL || p2 != NULL)
	{
		// if p1 not NULL and p2 NULL.
	 	if(p1 != NULL && p2 == NULL)
		{
			*t1 = tail1;
			*t2 = tail2;
			return SUCCESS;
		}
		// if p1 NULL and p2 not NULL.
		if(p1 == NULL && p2 != NULL)
		{
			*t1 = tail2;
			*t2 = tail1;
			if((*res_flg) != 1)
			{
				*res_flg = 1;
			}
			else
			{
				*res_flg = 0;
			}
			return SUCCESS;
		}
	 	p1 = p1->prev;
		p2 = p2->prev;
	}

	// both lists are of equal size.
	while(head1 != NULL)
	{
		// if first list data is greater than second list data.
		if(head1->data > head2->data)
		{
			*t1 = tail1;
			*t2 = tail2;
			return SUCCESS;
		}
		// if first list data is less than second list data.
		if(head1->data < head2->data)
		{
			*t1 = tail2;
			*t2 = tail1;
			if((*res_flg) != 1)
			{
				*res_flg = 1;
			}
			else
			{
				*res_flg = 0;
			}
			return SUCCESS;
		}
		head1 = head1->next;
		head2 = head2->next;
	}	
	// if both list size and data are equal.
	*t1 = tail1;
	*t2 = tail2;
	return SUCCESS;
}



