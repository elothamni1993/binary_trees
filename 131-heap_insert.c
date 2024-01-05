#include "binary_trees.h"

/**
 * binary_tree_size - Measures the size of a binary tree
 * @tree: Pointer to the root node of the tree
 * Return: Size of the tree
 */
size_t binary_tree_size(const binary_tree_t *tree)
{
    if (tree == NULL)
        return (0);

    return (1 + binary_tree_size(tree->left) + binary_tree_size(tree->right));
}

/**
 * binary_tree_insert - Inserts a node at a specific level in the tree
 * @root: Pointer to the root node of the tree
 * @value: Value to insert
 * @index: Current index in the tree
 * @size: Size of the tree
 * Return: Pointer to the created node, or NULL on failure
 */
binary_tree_t *binary_tree_insert(binary_tree_t *root, int value, size_t index, size_t size)
{
    binary_tree_t *new_node;

    if (index >= size)
        return (NULL);

    new_node = binary_tree_node(NULL, value);
    if (!new_node)
        return (NULL);

    if (index == size - 1)
        return (new_node);

    if (index < size / 2)
        new_node->left = binary_tree_insert(root, value, 2 * index + 1, size);
    else
        new_node->right = binary_tree_insert(root, value, 2 * index + 2, size);

    return (new_node);
}

/**
 * heap_insert - Inserts a value into a Max Binary Heap
 * @root: Pointer to the root node of the heap
 * @value: Value to insert
 * Return: Pointer to the created node, or NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
    size_t size;

    if (!root)
        return (NULL);

    size = binary_tree_size(*root);

    if (*root == NULL)
    {
        *root = binary_tree_node(NULL, value);
        return (*root);
    }

    binary_tree_insert(*root, value, 0, size);

    return (*root);
}

