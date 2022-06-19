public class BSTree<E extends Comparable<? super E>> {

    private Node<E> root;

    public BSTree(Node<E> root) {
        this.root = root;
    }

    public int size(){
        return size(root);
    }

    private int size(Node<E> root){

        if(root==null || root.getData() == null)
            return 0;
        return 1 + size(root.left) + size(root.right);
    }

    public BSTree() {
        this.root = null;
    }

    public void addNode(E data) {
        root = recursiveAddNode(root,data);
    }

    private Node<E> recursiveAddNode(Node<E> node, E data) {
        if(node == null) {
            node = new Node<E>(data);
            return node;
        }
        if(data.compareTo(node.getData()) < 0) {
            node.setLeft(recursiveAddNode(node.getLeft(),data));
        } else if(data.compareTo(node.getData()) > 0){
            node.setRight(recursiveAddNode(node.getRight(),data));
        } else {
            return node;
        }
        return node;
    }

    public void deleteNode(E data) {
        root = recursiveDeleteNode(root, data);
    }

    Node<E> recursiveDeleteNode(Node<E> root, E data)  {
        if (root == null)
            return null;
        if (data.compareTo(root.getData()) < 0)
            root.setLeft(recursiveDeleteNode(root.getLeft(), data));
        else if (data.compareTo(root.getData()) > 0)
            root.setRight(recursiveDeleteNode(root.getRight(), data));
        else  {
            if (root.getLeft() == null)
                return root.getRight();
            else if (root.getRight() == null)
                return root.getLeft();
            root.setData(minValue(root.getRight()));
            root.setRight(recursiveDeleteNode(root.getRight(),data));
        }
        return root;
    }

    E minValue(Node<E> root)  {
        E minval = root.getData();
        while (root.getLeft() != null)  {
            minval = root.getLeft().getData();
            root = root.getLeft();
        }
        return minval;
    }

    public void print() {
        BTreePrinter.printNode(root);
    }
    
    public BSTree<E> filter(E data) {
        BSTree<E> toReturn = new BSTree<E>();
        recursiveFilter(toReturn, root, data);
        return toReturn;
    }

    private void recursiveFilter(BSTree<E> tree, Node<E> node, E data) {
        if(node != null && node.getData() != null){
         if(node.getData().equals(data)) {
            tree.addNode(data);
         }
            recursiveFilter(tree, node.getLeft(), data);
            recursiveFilter(tree, node.getRight(), data);
        }         
    }

    public Node<E> findNode(E key) {
        if (key == null || root == null) {
            return null;
        }
        return recursiveFind(root, key, key.compareTo(root.getData()));
    }

    private Node<E> recursiveFind(Node<E> node, E key, int cmp) {
        if (node == null) {
            return null;
        }

        if (cmp == 0) {
            return node;
        }

        return recursiveFind(
                (node = cmp > 0 ? node.getRight() : node.getLeft()),
                key,
                node == null ? 0 : key.compareTo(node.getData()));
    }

    public AVLTree<E> balanced() {
        AVLTree<E> avl = new AVLTree<>();
        addForBalanced(root, avl);
        return avl;
    }

    
    public void addForBalanced(Node<E> root, AVLTree<E> avl){
        if(root==null || root.getData() == null)
            return;
        avl.addNode(root.getData());
        addForBalanced(root.getLeft(), avl);
        addForBalanced(root.getRight(), avl);
    }

    

}