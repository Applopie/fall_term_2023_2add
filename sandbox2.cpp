#include <memory>

template <typename element_t>
struct TreeNode final
{
    explicit TreeNode(element_t const &element) : TreeNode(element, nullptr, nullptr) {}
    TreeNode(element_t const &element, std::unique_ptr<TreeNode<element_t>> left_tree, std::unique_ptr<TreeNode<element_t>> right_tree) : element(element), left_tree(std::move(left_tree)), right_tree(std::move(right_tree)) {}

    element_t const element;
    std::unique_ptr<TreeNode<element_t>> left_tree;
    std::unique_ptr<TreeNode<element_t>> right_tree;
};

template <typename element_t>
std::unique_ptr<TreeNode<element_t>> flat_tree(std::unique_ptr<TreeNode<element_t>> root)
{
    if (!root)
    {
        return nullptr;
    }
    auto left = flat_tree(std::move(root->left_tree));
    auto right = flat_tree(std::move(root->right_tree));

    if (left)
    {
        auto current = left.get();
        while (current->right_tree)
        {
            current = current->right_tree.get();
        }
        current->right_tree = std::move(root);
        current->right_tree->right_tree = std::move(right);
        return left;
    }
    else
    {
        root->right_tree = std::move(right);
        return root;
    }
}