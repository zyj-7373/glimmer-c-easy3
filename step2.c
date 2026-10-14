#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;                       // 节点存储的数据
    struct TreeNode *left;          // 左子树指针
    struct TreeNode *right;         // 右子树指针
} TreeNode;


TreeNode* create_node(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int main() {
    TreeNode* node1 = create_node(1);
    TreeNode* node2 = create_node(2);
    TreeNode* node3 = create_node(3);
    TreeNode* node4 = create_node(4);
    TreeNode* node5 = create_node(5);
    TreeNode* node6 = create_node(6);
    TreeNode* node7 = create_node(7);

    node1->left = node2;
    node1->right = node3;
    
    node2->left = node4;
    node2->right = node5;
    
    node3->left = node6;
    node3->right = node7;

    free(node4);
    free(node5);
    free(node2);
    free(node6);
    free(node7);
    free(node3);
    free(node1);

    return 0;
}