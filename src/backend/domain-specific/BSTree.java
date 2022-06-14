public class BSTree<E extends Comparable<? super E>> {

    // TODO: HACER SIZE Y PRINT
    private Node<E> root;

    public BSTree(Node<E> root) {
        this.root = root;
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
        if(data.compareTo(root.getData()) < 0) {
            node.setLeft(recursiveAddNode(node,data));
        } else if(data.compareTo(root.getData()) > 0){
            node.setRight(recursiveAddNode(node,data));
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

}