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


// function for modulus.

data_t Modulus(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **r_h, Dlist **r_t)
{
	// if second list has one node and data is zero.
        if(head2 == tail2 && head2->data == 0)
	{
		printf("Error: modulus 0 is not possible.\n");
		return FAILURE;
	}
	
	// if first list has one node and data is zero.
        if(head1 == tail1 && head1->data == 0)
        {
		// function to insert first is called.
                if(insert_first(r_h, r_t, 0) == FAILURE)
		{
			return FAILURE;
		}
                return SUCCESS;
        }
        
	data_t r = 1;
	
	// function to compare for modulus is called.
	if(compare_for_division_or_modulus(head1, tail1, head2, tail2, &r) == FAILURE)
        {
                return FAILURE;
        }
	
	//if r is zero, that is both are equal.
        if(r == 0)
        {
		// function to insert first is called and result is zero.
                if(insert_first(r_h, r_t, 0) == FAILURE)
                {
                        return FAILURE;
                }
                return SUCCESS;
        }
	
	// if r is -1, list-1 less than list-2, then result is list-1.
        if(r == -1)
        {
		// result is first node.
		while(tail1 != NULL)
		{
			r = tail1->data;
			// function to insert first is called.
			if(insert_first(r_h, r_t, r) == FAILURE)
			{
				return FAILURE;
			}
			tail1 = tail1->prev;
		}
                return SUCCESS;
        }

        Dlist *h2 = NULL;
        Dlist *t2 = NULL;
	// function to insert first is called.
        if(insert_first(&h2, &t2, 0) == FAILURE)
        {
                return FAILURE;
        }
	// function for addition is called.
        if(Addition(h2, t2, head2, tail2, r_h, r_t) == FAILURE)
        {
                return FAILURE;
        }
	// fuction for delete nodes is called.
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
		// fuction for delete nodes is called.
                if(delete_nodes(&h2, &t2) == FAILURE)
                {
                        return FAILURE;
                }
                h2 = *r_h;
                t2 = *r_t;
                *r_h = NULL;
                *r_t = NULL;
		// function to compare for modulus is called.
                if(compare_for_division_or_modulus(head1, tail1, h2, t2, &r) == FAILURE)
                {
                        return FAILURE;
                }
                if(r == 0)
                {
			// function to insert first is called.
			if(insert_first(r_h, r_t, 0) == FAILURE)
			{
				return FAILURE;
			}
                        break;
                }
		if(r == -1)
		{
			Dlist *temp_h = NULL;
			Dlist *temp_t = NULL;
			// function for subtraction is called.
			if(Subtraction(h2, t2, head2, tail2, &temp_h, &temp_t, &r) == FAILURE)
			{
				return FAILURE;
			}
			// function for subtraction is called.
			if(Subtraction(head1, tail1, temp_h, temp_t, r_h, r_t, &r) == FAILURE)
			{
				return FAILURE;
			}
			break;
		}
        }
        return SUCCESS;
}




// function compare for modulus.

data_t compare_for_division_or_modulus(Dlist *h1, Dlist *t1, Dlist *h2, Dlist *t2, data_t *r)
{
	//if both or either one of the list is empty.
        if(t1 == NULL || t2 == NULL)
        {
		printf("ERROR: Passed List to compare for modulus is empty.\n");
                return FAILURE;
        }

        Dlist *p1 = t1;
        Dlist *p2 = t2;
	// compares size of the 2 lists.
        while(p1 != NULL || p2 != NULL)
        {
		// p1 is not NULL and p2 is NULL, then update r value to 1 and return.
                if(p1 != NULL && p2 == NULL)
                {
                        *r = 1;
                        return SUCCESS;
                }
		// p1 is NULL and p2 is not NULL, then update r value to 1 and return.
                if(p1 == NULL && p2 != NULL)
                {
                        *r = -1;
                        return SUCCESS;
                }
                p1 = p1->prev;
                p2 = p2->prev;
        }

	// if size of both lists are equal.
        while(h1 != NULL)
        {
		// if first list data is greater than second list data, then update r to 1 and return. 
                if(h1->data > h2->data)
                {
                        *r = 1;
                        return SUCCESS;
                }
		// if first list data is less than second list data, then update r to -1 and return. 
                if(h1->data < h2->data)
                {
                        *r = -1;
                        return SUCCESS;
                }
                h1 = h1->next;
                h2 = h2->next;
        }
	// if both lists size and data is equal, then update r to 0 and return.
        *r = 0;
        return SUCCESS;
}



