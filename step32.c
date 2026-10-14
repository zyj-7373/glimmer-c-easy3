#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// 定义栈结构体
typedef struct Stack {
    TreeNode **arr; // 存放树节点指针的数组
    int top;        // 栈顶指针，代表目前最后一个有效元素在数组的哪个位置，-1表示空栈
    int capacity;   // 栈的最大容量
} Stack;

// 创建并初始化栈
Stack *createStack(int capacity) {
    Stack *stack = malloc(sizeof(Stack)); // 申请一块内存放这个栈结构体
    stack->arr = malloc(sizeof(TreeNode *) * capacity); // 申请一块连续内存作为存放树节点的数组
    stack->top = -1;        // 初始化栈顶为-1，代表栈是空的
    stack->capacity = capacity; // 记录最大容量
    return stack;           // 把创建好的栈地址返回去
}

// 判断栈是否为空
int isEmpty(Stack *stack) {
    // 如果top是-1，说明没放过任何东西，返回真(1)，否则返回假(0)
    return stack->top == -1; 
}

// 入栈
void push(Stack *stack, TreeNode *node) {
    if (stack->top == stack->capacity - 1) {
        return; // 栈满了，直接返回
    }
    stack->arr[++stack->top] = node; //栈顶指针先向上移动一格，然后再把节点存进去
}

// 出栈
TreeNode *pop(Stack *stack) {
    if (isEmpty(stack)) {
        return NULL;     //栈空返null
    }
    return stack->arr[stack->top--];//先返回当前栈顶位置的元素，然后栈顶指针再向下移动一格
}

void preorderTraversal(TreeNode *root) {
    if (root == NULL) {
        return;
    }

    Stack *stack = createStack(10000);
    push(stack, root);

    while (!isEmpty(stack)) {
        TreeNode *current = pop(stack);
        printf("%d ", current->val);

        if (current->right != NULL) {
            push(stack, current->right);
        }
        if (current->left != NULL) {
            push(stack, current->left);
        }
    }

    free(stack->arr);
    free(stack);
}

int main() {
    TreeNode *n1 = (TreeNode *)malloc(sizeof(TreeNode)); n1->val = 1;
    TreeNode *n2 = (TreeNode *)malloc(sizeof(TreeNode)); n2->val = 2;
    TreeNode *n3 = (TreeNode *)malloc(sizeof(TreeNode)); n3->val = 3;
    TreeNode *n4 = (TreeNode *)malloc(sizeof(TreeNode)); n4->val = 4;
    TreeNode *n5 = (TreeNode *)malloc(sizeof(TreeNode)); n5->val = 5;

    n1->left = n2;  n1->right = n3;
    n2->left = n4;  n2->right = n5;
    n3->left = NULL; n3->right = NULL;
    n4->left = NULL; n4->right = NULL;
    n5->left = NULL; n5->right = NULL;

    printf("前序遍历结果：");
    preorderTraversal(n1);
    printf("\n");

    return 0;
}