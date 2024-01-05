#include "binary_trees.h"

/**
 * heapify_down - Maintains the Max Heap property by moving down the tree
 * @root: Double pointer to the root node of the heap
 */
void heapify_down(heap_t **root)
{
    heap_t *current, *max_child;

    current = *root;

    while (current->left)
    {
        max_child = current->left;

        if (current->right && current->right->n > current->left->n)
            max_child = current->right;

        if (max_child->n <= current->n)
            break;

        if (!max_child->left && !max_child->right)
            break;

        if (!max_child->right || max_child->left->n >= max_child->right->n)
            swap_nodes(current, max_child, root, 1);
        else
            swap_nodes(current, max_child->right, root, 1);
    }
}

/**
 * swap_nodes - Swaps two nodes in a binary tree
 * @parent: Pointer to the parent node
 * @child: Pointer to the child node
 * @root: Double pointer to the root node of the heap
 * @free_child: Flag to determine if the child should be freed
 */
void swap_nodes(heap_t *parent, heap_t *child, heap_t **root, int free_child)
{
    heap_t *parent_right, *parent_left, *child_right, *child_left, *child_parent;

    parent_right = parent->right;
    parent_left = parent->left;
    child_right = child->right;
    child_left = child->left;
    child_parent = child->parent;

    if (parent->parent)
    {
        if (parent->parent->left == parent)
            parent->parent->left = child;
        else
            parent->parent->right = child;
    }
    else
    {
        *root = child;
    }

    child->parent = parent->parent;
    parent->parent = child;

    if (child->left)
        child->left->parent = parent;

    if (child->right)
        child->right->parent = parent;

    if (parent->left == child)
    {
        child->left = parent;
        child->right = parent_right;
    }
    else
    {
        child->right = parent;
        child->left = parent_left;
    }

    if (parent_left)
        parent_left->parent = child;

    if (parent_right)
        parent_right->parent = child;

    if (free_child)
        free(parent);
}

/**
 * get_last_node - Gets the last node in the heap
 * @root: Double pointer to the root node of the heap
 * Return: Pointer to the last node
 */
heap_t *get_last_node(heap_t **root)
{
    heap_t *last_node = NULL;
    size_t size, index;

    if (!root || !*root)
        return (NULL);

    size = binary_tree_size(*root);

    for (index = 0; 1 << (index + 1) <= size + 1; index++)
    {
        if (index > 0 && ((size + 1) & (1 << index)) == 0)
            last_node = last_node->left;
        else if (last_node->right)
            last_node = last_node->right;
        else
            last_node = last_node->left;
    }

    return (last_node);
}

/**
 * heap_extract - Extracts the root node of a Max Binary Heap
 * @root: Double pointer to the root node of the heap
 * Return: Value stored in the root node
 */
int heap_extract(heap_t **root)
{
    int value;
    heap_t *last_node, *extracted_node;

    if (!root || !*root)
        return (0);

    value = (*root)->n;
    last_node = get_last_node(root);
    extracted_node = *root;

    if (last_node)
        swap_nodes(extracted_node, last_node, root, 0);

    if ((*root)->left)
        free((*root)->left);

    if ((*root)->right)
        free((*root)->right);

    return (value);
}

