/*
 * Demonstration of an expression formatter / evaluator (using tree & stack)
 *      Reads in expressions in pre-fix notation
 *      Formats the expression in in-fix notation with balanced parentheses
 *      Evaluates the expression using an abstract stack machine
 *
 * Program Output:
        Original expression in prefix notation:

            * / - 74 10 32 + 23 17

        Converted to infix notation:

            ((( 74  -  10 ) /  32 ) * ( 23  +  17 ))

        Expression value:

            80
 */
#include <stdio.h>
#include <stdlib.h>

#include "bitree.h"
#include "stack.h"

/*
 * The expression to be evaluated
 */
const char *expression[] =
{
   "*", "/", "-", "74", "10", "32", "+", "23", "17"
};
const int EXPRESSION_LENGTH = sizeof(expression) / sizeof(*expression);

/*
 * Function prototypes - expression formatter
 */
void fatalError(const char *message);
void outputArray(const char *array[], int arrayLength);
const char *getNextToken();
int isOperator(const char *token);
void insertLeftOperand(BiTree *tree, BiTreeNode *parent);
void insertRightOperand(BiTree *tree, BiTreeNode *parent);
void insertPrefixExpressionIntoTree(BiTree *tree);
void doOutputInfixExpression(const BiTreeNode *node);
void outputInfixExpression(const BiTree *tree);

/*
 * Function prototypes - expression evaluator
 */
int evaluate(int *op1, int *op2, const char *operator);
void doEvaluateExpression(Stack *stack, BiTreeNode *node);
int evaluateExpression(BiTree *expressionTree);

/*
 * Function implementations
 */
int main(void)
{
   BiTree expressionTree;
   bitree_init(&expressionTree, NULL);

   /* -------- Expression formatter -------- */
   /* Output the original prefix notation expression */
   printf("Original expression in prefix notation:\n\n\t");
   outputArray(expression, EXPRESSION_LENGTH);

   /* Insert the expression into a binary tree */
   insertPrefixExpressionIntoTree(&expressionTree);

   /* Output the expression in infix notation */
   printf("\n\nConverted to infix notation:\n\n\t");
   outputInfixExpression(&expressionTree);

   /* -------- Expression evaluator -------- */
   printf("\n\n");
   printf("Expression value:\n\n\t%d", evaluateExpression(&expressionTree));

   bitree_destroy(&expressionTree);

   return EXIT_SUCCESS;
}

void fatalError(const char *message)
{
   fprintf(stderr, message);
   exit(EXIT_FAILURE);
}

void outputArray(const char *array[], int arrayLength)
{
   int i;

   for (i = 0; i < arrayLength; ++i)
      printf("%s ", array[i]);
}

const char *getNextToken()
{
   static int tokenIndex;

   if (tokenIndex == EXPRESSION_LENGTH)
      return NULL;

   return expression[tokenIndex++];
}

int isOperator(const char *token)
{
   switch (token[0])
   {
   case '+':
   case '-':
   case '*':
   case '/':
      return 1;
   }
   return 0;
}

void insertLeftOperand(BiTree *tree, BiTreeNode *parent)
{
   const char *token = getNextToken();
   if (token == NULL)
      fatalError("Illegal expression, not enough operands");

   if (bitree_ins_left(tree, parent, token) != 0)
      fatalError("Failed to insert into tree");

   if (isOperator(token))
   {
      insertLeftOperand(tree, bitree_left(parent));
      insertRightOperand(tree, bitree_left(parent));
   }
}

void insertRightOperand(BiTree *tree, BiTreeNode *parent)
{
   const char *token = getNextToken();
   if (token == NULL)
      fatalError("Illegal expression, not enough operands");

   if (bitree_ins_right(tree, parent, token) != 0)
      fatalError("Failed to insert into tree");

   if (isOperator(token))
   {
      insertLeftOperand(tree, bitree_right(parent));
      insertRightOperand(tree, bitree_right(parent));
   }
}

void insertPrefixExpressionIntoTree(BiTree *tree)
{
   const char *token = getNextToken();

   /* Return if empty expression */
   if (token == NULL)
      return;

   /* Insert first token as root */
   if (bitree_ins_left(tree, NULL, token) != 0)
         fatalError("Failed to insert into tree");

   /* Insert operands for this operator */
   if (isOperator(token))
   {
      insertLeftOperand(tree, bitree_root(tree));
      insertRightOperand(tree, bitree_root(tree));
   }
}

void doOutputInfixExpression(const BiTreeNode *node)
{
   const char *token;

   if (node == NULL)
      return;

   token = (const char *)bitree_data(node);

   if (isOperator(token))
      printf("(");

   doOutputInfixExpression(bitree_left(node));     /* Left operand */
   printf(" %s ", token);                         /* Token */
   doOutputInfixExpression(bitree_right(node));    /* Right operand */

   if (isOperator(token))
      printf(")");
}

void outputInfixExpression(const BiTree *tree)
{
   doOutputInfixExpression(bitree_root(tree));
}

int evaluate(int *op1, int *op2, const char *operator)
{
   switch (operator[0])
   {
   case '+':
      return *op1 + *op2;
   case '-':
      return *op1 - *op2;
   case '*':
      return *op1 * *op2;
   case '/':
      return *op1 / *op2;
   default:
      fatalError("Unexpected operator");
      return 0;
   }
}

void doEvaluateExpression(Stack *stack, BiTreeNode *node)
{
   const char *token;
   int *op1, *op2;
   int *value;

   if (node == NULL)
      return;

   /* Postorder traversal so sub-expressions evaluated before operators */
   doEvaluateExpression(stack, bitree_left(node));    /* Left child */
   doEvaluateExpression(stack, bitree_right(node));   /* Right child */

   /* Parent */
   token = (const char *)bitree_data(node);
   if (isOperator(token))
   {
      /* Retrieve operands from stack */
      if (stack_pop(stack, (void **)&op2) != 0)
         fatalError("Failed to pop from stack");
      if (stack_pop(stack, (void **)&op1) != 0)
         fatalError("Failed to pop from stack");

      /* Evaluate expression */
      if ((value = (int *)malloc(sizeof(int))) == NULL)
         fatalError("Out of memory");
      *value = evaluate(op1, op2, token);
      free(op1);
      free(op2);

      /* Push result onto stack */
      if (stack_push(stack, value) != 0)
         fatalError("Failed to push onto stack");
   }
   else
   {
      /* Push operand onto stack */
      if ((value = (int *)malloc(sizeof(int))) == NULL)
         fatalError("Out of memory");
      *value = atoi(token);
      if (stack_push(stack, value) != 0)
         fatalError("Failed to push onto stack");
   }
}

int evaluateExpression(BiTree *expressionTree)
{
   Stack stack;
   int result;

   stack_init(&stack, free);

   /* Top of stack will hold result of expression after call completes */
   doEvaluateExpression(&stack, bitree_root(expressionTree));

   result = *((int *)stack_peek(&stack));

   stack_destroy(&stack);

   return result;
}
