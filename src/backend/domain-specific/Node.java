public class Node<E extends Comparable<? super E>> {

    private E data;
    private Node<E> left;
    private Node<E> right;
    private int h;

    public Node(E data) {
        this.data = data;
        h = 0;
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