# C-EASY-3

## step1

### 1

#### 树

树是一种非常重要的非线性数据结构，可以用来表示具有层次关系的数据
定义：树是由 n（n >= 0）个有限节点组成一个具有层次关系的集合

当 n=0 时称为空树。在任意一棵非空树中，有且仅有一个特定的节点称为根节点。其余节点可分为 m（m > 0）个互不相交的有限集合，每个集合本身又是一棵树，称为根的子树。



#### 二叉树

二叉树是树的一种特殊形式，它的特点是每个节点最多只有两个子节点（即每个节点的度不超过2），并且这两个子节点有左右之分，次序不能颠倒
定义：二叉树是 n（n >= 0）个节点的有限集合，该集合或者为空集（空二叉树），或者由一个根节点和两棵互不相交的、分别称为根节点的左子树和右子树的二叉树组成。



### 2

#### 二叉树在C语言中存储

顺序存储（数组表示法）：使用一组连续的内存单元（数组）来存储二叉树的节点。通常按照完全二叉树的节点编号顺序，将节点存入数组中。如果节点为空，则数组中对应位置留空或使用特殊标记。这种方式适合存储完全二叉树，因为不会浪费太多空间。但对于一般的二叉树，可能会造成大量的空间浪费。
链式存储（链表表示法）：使用指针来表示节点之间的逻辑关系。每个节点通常包含三个部分：数据域（存储数据）、左指针域（指向左孩子）、右指针域（指向右孩子）。

如果是一棵极其稀疏的普通二叉树，使用数组存储会导致数组中大量位置为空，此时空间浪费会非常严重，这种情况下通常更推荐使用链式存储



#### 二叉树特点

每个节点最多有两棵子树
左子树和右子树是有顺序的，次序不能任意颠倒。
即使树中某节点只有一棵子树，也要区分它是左子树还是右子树



思考过程

init_tree(SeqBiTree *tree)初始化时将树的容量size设为MAX_TREE_SIZE。同时遍历整个nodes数组，将所有节点的used标志位设置为false，将data也初始化为0。

 set_root(SeqBiTree *tree, int value)根节点固定在数组下标1处。在设置前检查下标1是否越界。若无误则将nodes[1].data赋值为value，并将nodes[1].used置为true。

 set_left_child(SeqBiTree *tree, int parent_node, int value)左孩子的下标left_index = parent_node * 2。 安全校验，父节点parent_node必须大于等于1且小于tree->size，且父节点必须已经被创建。越界检查计算出的left_index不能超过数组容量tree->size - 1。校验通过后，更新左孩子节点的data和used状态 

set_right_child(SeqBiTree *tree, int parent_node, int value) 与设置左孩子类似，下标为right_index = parent_node * 2 + 1。进行父节点合法性检查以及数组越界检查，然后写入数据并标记used。 

level_order(SeqBiTree *tree)层序遍历需要按数组下标顺序输出。首先需要找到树中最大的有效下标max_index避免遍历整个MAX_TREE_SIZE的无效空间。从下标1遍历到max_index。如果used为true，打印节点数据，否则打印-1。第level层结束于下标2^level - 1。使用变量level_end记录当前层结束的下标，每层循环开始时更新level_end = (1 << level) - 1，当遍历到i == level_end时输出一个换行符

 主函数测试验证

## step 2

for无法实现打印函数

树是一种非线性的数据结构，而 for 循环是线性的。链表、数组等线性结构，每个节点只有一个“下一站”，所以用 for 循环顺着链子往下走就能遍历完。二叉树有左孩子和右孩子，当走到一个节点时，for 循环无法决定接下来是先去探索左子树，还是先去探索右子树。且探索完左子树后，难以回来继续探索右子树。需要使用递归才能遍历整棵二叉树

## step 3

前序遍历 根->左->右

中序遍历 左->根->右

后序遍历 左->右->根



改变  p r i n t f  的位置就能改变遍历顺序原因

在于函数调用栈的阻塞机制。当函数执行到  traverse(root->left)  时，当前函数的执行会被立刻暂停，直到左子树的整个递归调用链全部完成并返回后，程序才会继续往下执行



前序遍历执行过程推演

进入节点1，程序执行到 printf("%d ", root->data);，打印 1。接着遇到 preorder_traversal(root->left);，暂停节点1的后续工作，进入节点 2

进入节点 2执行 printf("%d ", root->data);，打印 2。遇到 preorder_traversal(root->left);，暂停节点2的后续工作，进入节点 4

进入节点 4执行 printf("%d ", root->data);，打印 4。遇到 preorder_traversal(root->left);，进入 4 的左孩子NULL，直接返回。接着执行 preorder_traversal(root->right);，进入 4 的右孩子NULL，也返回

节点 4 的整个任务结束了，控制权交还给节点 2。节点 2 继续执行它之前被暂停的 preorder_traversal(root->right);，进入节点 5

进入节点 5打印 5，左右孩子都是 NULL，返回

节点 2 的左右子树都处理完了，控制权交还给节点 1。节点 1 继续执行它之前被暂停的 preorder_traversal(root->right);，进入节点 3，直到全部完成。 最终打印结果1 2 4 5 3 6 7 



树深度统计函数

```c
int depth(TreeNode *root, int current_depth, int max_depth) {
    if (root == NULL) {
        return current_depth > max_depth ? current_depth : max_depth; 
    }    	
    current_depth++;    
    if (current_depth > max_depth) {
        max_depth = current_depth;  
    }    
    int left_max = depth(root->left, current_depth, max_depth);   
    int right_max = depth(root->right, current_depth, max_depth);  
    return left_max > right_max ? left_max : right_max; } 
```



后两个int不用指针原因

因为参数是值传递。每次递归调用都会在栈帧中拷贝独立副本，当前层的 current_depth 和 max_depth 修改只作用于本层，天然隔离了左右子树的遍历状态，不会互相干扰