#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char op;              // '+', '*', or 0 if number
    int value;           // used only if it's a number

    struct Node* left;
    struct Node* right;
} Node;

Node* create_number(int value) {
    Node* node = malloc(sizeof(Node));

    node -> value = value;
    node -> op = '0';
    node -> left = NULL;
    node -> right = NULL;

    return node;
}

Node* create_op(char op, Node* left, Node* right) {
    Node* node = malloc(sizeof(Node));

    node -> op = op;
    node -> left = left;
    node -> right = right;

    return node;
}

int evaluate(Node* node) {
    // Base case: If it's a number node (op is 0)
    if (node->op == 0) {
        return node->value;
    }

    // Recursive case: It's an operator node
    int left_val = evaluate(node->left);
    int right_val = evaluate(node->right);

    if (node->op == '+') return left_val + right_val;
    if (node->op == '*') return left_val * right_val;
    
    return 0; // Default fallback
}

int main() {
    // 1. Build the leaves (the numbers)
    Node* three = create_number(3);
    Node* five = create_number(5);
    Node* two = create_number(2);

    // 2. Build the branches (the operators)
    // This creates (3 + 5)
    Node* sum = create_op('+', three, five);
    
    // This creates (sum * 2)
    Node* root = create_op('*', sum, two);

    // 3. Test it!
    int result = evaluate(root);
    printf("The result of (3 + 5) * 2 is: %d\n", result);

    // Note: In a real app, you'd create a function to free() all these nodes!
    return 0;
}