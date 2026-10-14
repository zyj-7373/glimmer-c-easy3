#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_TREE_SIZE 100
/*
 * 顺序存储二叉树结点
 * - data：结点数据
 * - used：当前位置是否有结点
 */
typedef struct {
    int data;
    bool used;
} SeqTreeNode;

/*
 * 顺序存储二叉树
 * - nodes：结点数组
 * - size：数组最大容量
 */
typedef struct {
    SeqTreeNode nodes[MAX_TREE_SIZE];
    int size;
} SeqBiTree;

void init_tree(SeqBiTree *tree) {
    tree->size = MAX_TREE_SIZE;
    for (int i = 0; i < MAX_TREE_SIZE; i++) {
        tree->nodes[i].used = false;
        tree->nodes[i].data = 0;
    }
}

bool set_root(SeqBiTree *tree, int value) {
    if (1 >= tree->size) {
        return false;
    }
    tree->nodes[1].data = value;
    tree->nodes[1].used = true;
    return true;
}

bool set_left_child(SeqBiTree *tree, int parent_node, int value) {
    int left_index = parent_node * 2;
    
    if (parent_node < 1 || parent_node >= tree->size || !tree->nodes[parent_node].used) {
        return false; 
    }
    if (left_index >= tree->size) {
        return false;
    }
    
    tree->nodes[left_index].data = value;
    tree->nodes[left_index].used = true;
    return true;
}

bool set_right_child(SeqBiTree *tree, int parent_node, int value) {
    int right_index = parent_node * 2 + 1;
    
    if (parent_node < 1 || parent_node >= tree->size || !tree->nodes[parent_node].used) {
        return false;
    }
    if (right_index >= tree->size) {
        return false;
    }
    
    tree->nodes[right_index].data = value;
    tree->nodes[right_index].used = true;
    return true;
}

void level_order(SeqBiTree *tree) {
    if (tree->size < 2 || !tree->nodes[1].used) {
        printf("树为空\n");
        return;
    }
    
    int max_index = 1;
    for (int i = 1; i < tree->size; i++) {
        if (tree->nodes[i].used) {
            max_index = i;
        }
    }
    
    int level = 1;
    int level_end = 1;
    
    for (int i = 1; i <= max_index; i++) {
        if (tree->nodes[i].used) {
            printf("%d ", tree->nodes[i].data);
        } else {
            printf("-1 ");
        }
        
        if (i == level_end) {
            printf("\n");
            level++;
            level_end = (1 << level) - 1;
        }
    }
}

int main() {
    SeqBiTree tree;
    
    init_tree(&tree);
    printf("初始化后树大小: %d\n", tree.size);
    
    if (!set_root(&tree, 1)) printf("设置根节点失败\n");
    
    if (!set_left_child(&tree, 1, 2)) printf("设置左孩子失败\n");
    if (!set_right_child(&tree, 1, 3)) printf("设置右孩子失败\n");
    
    if (!set_left_child(&tree, 2, 4)) printf("设置左孩子失败\n");
    if (!set_right_child(&tree, 2, 5)) printf("设置右孩子失败\n");
    if (!set_right_child(&tree, 3, 7)) printf("设置右孩子失败\n");
    
    printf("\n层序遍历结果 (包含空节点 -1):\n");
    level_order(&tree);
    
    return 0;
}