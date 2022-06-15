public class Node<E extends Comparable<? super E>> {

    E data;
    Node<E> left;
    Node<E> right;
    int h;
    Node<E> parent; // for RB
    int color; // for RB


    public Node(E data) {
        this.data = data;
        h = 0;
    }

    public Node() {
        this.data = null;
        this.h = 0;
        this.color = 0;
        this.left = null;
        this.right = null;
    }

    public int getH() {
        return h;
    }

    public void setH(int h) {
        this.h = h;
    }

    public E getData() {
        return data;
    }

    public void setData(E data) {
        this.data = data;
    }

    public Node<E> getLeft() {
        return left;
    }

    public Node<E> getRight() {
        return right;
    }

    public void setLeft(Node<E> left) {
        this.left = left;
    }

    public void setRight(Node<E> right) {
        this.right = right;
    }

}