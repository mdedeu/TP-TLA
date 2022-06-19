/**
 * AVL-Tree
 * basado en: https://developpaper.com/java-implementation-of-avl-tree/
 */
public class AVLTree<T extends Comparable<? super T>> {

    private static final int MAX_HEIGHT_DIFFERENCE = 1;

    private Node<T> root;

    public AVLTree() {
        root = null;
    }

    public T find(T key) {
        if (key == null || root == null) {
            return null;
        }
        return find(root, key, key.compareTo(root.getData()));
    }

    public Node<T> findNode(T key) {
        if (key == null || root == null) {
            return null;
        }
        return recursiveFind(root, key, key.compareTo(root.getData()));
    }

    private Node<T> recursiveFind(Node<T> node, T key, int cmp) {
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

    private T find(Node<T> node, T key, int cmp) {
        if (node == null) {
            return null;
        }

        if (cmp == 0) {
            return node.getData();
        }

        return find(
                (node = cmp > 0 ? node.getRight() : node.getLeft()),
                key,
                node == null ? 0 : key.compareTo(node.getData()));
    }

    public void addNode(T key) {
        if (key == null) {
            throw new NullPointerException();
        }
        root = insert(root, key);
    }

    private Node<T> insert(Node<T> node, T key) {
        if (node == null) {
            return new Node<>(key);
        }

        int cmp = key.compareTo(node.getData());
        if (cmp == 0) {
            return node;
        }
        if (cmp <= 0) {
            node.setLeft(insert(node.getLeft(), key));
        } else {
            node.setRight(insert(node.getRight(), key));
        }

        if (Math.abs(height(node.getLeft()) - height(node.getRight())) > MAX_HEIGHT_DIFFERENCE) {
            node = balance(node);
        }
        refreshHeight(node);
        return node;
    }

    private int height(Node<T> node) {
        if (node == null) {
            return 0;
        }
        return node.getH();
    }

    private void refreshHeight(Node<T> node) {
        node.setH(Math.max(height(node.getLeft()), height(node.getRight())) + 1);
    }

    private Node<T> balance(Node<T> node) {
        Node<T> node1, node2;
        // ll & l
        if (height(node.getLeft()) > height(node.getRight()) &&
                height(node.getLeft().getLeft()) >= height(node.getLeft().getRight())) {
            node1 = node.getLeft();
            node.setLeft(node1.getRight()); 
            node1.setRight(node); 

            refreshHeight(node);
            return node1;
        }
        
        if (height(node.getLeft()) > height(node.getRight()) &&
                height(node.getLeft().getRight()) > height(node.getLeft().getLeft())) {
            node1 = node.getLeft();
            node2 = node.getLeft().getRight();
            node.setLeft(node2.getRight());
            node1.setRight(node2.getLeft());
            node2.setLeft(node1);
            node2.setRight(node);

            refreshHeight(node);
            refreshHeight(node1);
            return node2;
        }
        // rr & r
        
        
        if (height(node.getRight()) > height(node.getLeft()) &&
                height(node.getRight().getRight()) >= height(node.getRight().getLeft())) {
            node1 = node.getRight();
            node.setRight(node1.getLeft()); 
            node1.setLeft(node);

            refreshHeight(node);
            return node1;
        }
        // rl
        if (height(node.getRight()) > height(node.getLeft()) &&
                height(node.getRight().getLeft()) > height(node.getRight().getRight())) {
            node1 = node.getRight();
            node2 = node.getRight().getLeft();
            node.setRight(node2.getLeft());
            node1.setLeft(node2.getRight()); 
            node2.setLeft(node); 
            node2.setRight(node1);

            refreshHeight(node);
            refreshHeight(node1);
            return node2;
        }
        return node;
    }

    public void deleteNode(T key) {
        if (key == null) {
            throw new NullPointerException();
        }
        root = remove(root, key);
    }

    private Node<T> remove(Node<T> node, T key) {
        if (node == null) {
            return null;
        }

        int cmp = key.compareTo(node.getData());
        if (cmp < 0) {
            node.setLeft( remove(node.getLeft(), key));
        }
        if (cmp > 0){
            node.setRight( remove(node.getRight(), key));
        }
        if (cmp == 0) {
            if (node.getLeft() == null || node.getRight() == null) {
                return node.getLeft() == null ? node.getRight() : node.getLeft();
            }
            var successorKey = successorOf(node).getData();
            node = remove(node, successorKey);
            node.setData( successorKey);
        }

        if (Math.abs(height(node.getLeft()) - height(node.getRight())) > MAX_HEIGHT_DIFFERENCE) {
            node = balance(node);
        }
        refreshHeight(node);
        return node;
    }
    
    private Node<T> successorOf(Node<T> node) {
        if (node == null) {
            throw new NullPointerException();
        }
        if (node.getLeft() == null || node.getRight() == null) {
            return node.getLeft() == null ? node.getRight() : node.getLeft();
        }

        return height(node.getLeft()) > height(node.getRight()) ?
                findMax(node.getLeft(), node.getLeft().getRight(), node.getLeft().getRight() == null) :
                findMin(node.getLeft(), node.getRight().getLeft(),  node.getRight().getLeft() == null);
    }

    private Node<T> findMax(Node<T> node, Node<T> right, boolean rightIsNull) {
        if (rightIsNull) {
            return node;
        }
        return findMax((node = right), node.getRight(), node.getRight() == null);
    }

    private Node<T> findMin(Node<T> node, Node<T> left, boolean leftIsNull) {
        if (leftIsNull) {
            return node;
        }
        return findMin((node = left), node.getLeft(), node.getLeft() == null);
    }

    public void print() {
        BTreePrinter.printNode(root);
    }

    public int size(){
        return size(root);
    }

    private int size(Node<T> root){

        if(root==null || root.getData() == null)
            return 0;
        return 1 + size(root.left) + size(root.right);
    }

    public AVLTree<T> filter(T data) {
        AVLTree<T> toReturn = new AVLTree<>();
        recursiveFilter(toReturn, root, data);
        return toReturn;
    }

    private void recursiveFilter(AVLTree<T> tree, Node<T> node, T data) {
        if(node != null && node.getData() != null){
         if(node.getData().equals(data)) {
            tree.addNode(data);
         }
            recursiveFilter(tree, node.getLeft(), data);
            recursiveFilter(tree, node.getRight(), data);
        }         
    }

    public AVLTree<T> balanced() {
        AVLTree<T> avl = new AVLTree<>();
        addForBalanced(root, avl);
        return avl;
    }

    public void addForBalanced(Node<T> root, AVLTree<T> avl){
        if(root==null || root.getData() == null)
            return;
        avl.addNode(root.getData());
        addForBalanced(root.getLeft(), avl);
        addForBalanced(root.getRight(), avl);
    }
    

    public AVLTree<T> mul(int times) {
        AVLTree<T> toReturn = new AVLTree<>();
        recursiveMul(toReturn, root, times);
        return toReturn;
    }

    //  Java does not have this feature. 
    @SuppressWarnings("unchecked")
    private void recursiveMul(AVLTree<T> tree, Node<T> node, int times) {
        if(node != null && node.getData() != null){
            
            if(node.getData() instanceof String) {
                tree.addNode((T) ((String) node.getData()).repeat(times));
            } else {
                Integer a = ((Integer) node.getData())*times;
                tree.addNode( (T) a );
            }  
            recursiveMul(tree, node.getLeft(), times);
            recursiveMul(tree, node.getRight(), times);
        }         
    }

}