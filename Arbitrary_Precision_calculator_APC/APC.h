/*
 *	Name		:	Ashith P Amin
 *
 *	Date		:	10 / 12 / 2025
 *
 *	Description	:	Arbitrary Precision Calculator ( APC ) Project :
 *				
 *				- Validation & Conversion :
 *
 *					-> command-line arguments should be exactly 4.
 *					-> 2nd and 4th command-line arguments should be operand, operand can contain '+' or '-' sign in first index.
 *					-> First index of operand can be sign or digit and remaining index should only contain digits.
 *					-> 3rd command-line argument should be any one operator only( '+'/'-'/('X'/'x')/'/'/'%' ).
 *				 	-> Converting operand strings to double linked list.
 *				 	-> Removing extra zero's if present at start.
 *				 	-> Validating operator by comparing the sign's present in operands and operator.
 *					 
 *
 *				1). Addition :
 *
 *					-> Adding data stored in double linked list from last( tail ) of operand-1 ad operand-2.
 *					-> Added data is inserted at first of result list.
 *					-> Carry is used if data added is more than 9. 
 *					
 *				2). Subtraction :
 *
 *					-> First operands are re-arranged such that larger value first & then smaller value  and then values subtracted.
 *					-> Borrow is used to subtract lower digit from higher digit.
 *					-> Subtracted data is inserted at first of result list.
 *
 *				3). Multiplication :
 *
 *					-> Operand-2 one-digit is multiplied by one by one digit of operand-1 using carry.
 *					-> For 2nd result, result starts with 1 zero and 3rd with 2 zero's and so-on.
 *					-> After getting 2 results, then these 2 results are added and then 3rd result added and so-on.
 *					-> Multiplication results are inserted one by one at first of result list.
 *
 *				4). Division :
 *
 *					-> If operand-2 is zero, then print error - division not possible.
 *					-> If operand-1 and operand-2 are equal, then result is 1.
 *					-> If operand-1 is less than operand-2, then result is 0.
 *					-> If operand-1 is greater than operand-2, then division is done by addition method.
 *					-> Zero is added with operand-2 and stored in result.
 *					-> In addition method, operand-2 value is added with result and result updated.
 *					-> Addition is done and count is incremented till result value is equal or less then operand-1.
 *
 *				5). Modulus :
 *
 *					-> If any one of the operand is zero or both are zero, then result is zero.
 *					-> If operand-1 is less than operand-2, then result is operand-1.
 *					-> If operand-1 is equal to operand-2, then result is zero.
 *					-> If operand-1 is greater than operand-2, then division is done by addition method.
 *					-> Similar like division operation, but difference is if operand-2 divides operand-1 exactly then result is zero.
 *					-> And if doesn't divides exactly, then result is subtracted with operand-2 and result is updated.
 *					-> And then updated result is subtracted with operand-1 and final result is obtained.
 *					-> Ex: 21%5 -> 25-5=20 -> 21-20=1 - result. 
 */





#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Macro's defined.

#define SUCCESS 0
#define FAILURE -1


// Double linked list node storing integer data.

typedef int data_t;
typedef struct node
{
        struct node* prev;
        data_t data;
        struct node* next;
}Dlist;



// function prototypes.

data_t validate_args(char *argv[]);
data_t convert_str_to_list(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, data_t *f1, data_t *f2, char *argv[]);
void operation_validation(data_t *f1, data_t *f2, data_t *res_flg, char *op, char *argv[]);
data_t insert_last(Dlist **head, Dlist **tail, data_t data);
data_t insert_first(Dlist **head, Dlist **tail, data_t data);
void print_result(Dlist *head, data_t res_flg);
data_t delete_nodes(Dlist **head, Dlist **tail);
data_t delete_first(Dlist **head);
data_t remove_zeros_from_start(Dlist **head);
data_t Addition(Dlist *h1, Dlist *t1, Dlist *h2, Dlist *t2, Dlist **r_h, Dlist **r_t);
data_t Subtraction(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **r_h, Dlist **r_t, data_t *res_flg);
data_t nums_order_to_sub(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **t1, Dlist **t2, data_t *res_flg);
data_t Multiplication(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **r_h, Dlist **r_t);
data_t Division(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **r_h, Dlist **r_t);
data_t Modulus(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **r_h, Dlist **r_t);
data_t compare_for_division_or_modulus(Dlist *h1, Dlist *t1, Dlist *h2, Dlist *t2, data_t *r);

#endif
