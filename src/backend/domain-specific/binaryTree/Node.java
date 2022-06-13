
import java.util.ArrayList;
import java.util.List;
public class Node<K,V> {

    private V data;
    private K key;
    private List<Node<K,V>> children;

    public Node(K key, V data) {
        this.key = key;
        this.data = data;
        children = new ArrayList<>();
    }

    public void addChild(Node<K,V> child) {
        children.add(child);
    }

    public V getData() {
        return data;
    }

    public K getKey() {
        return key;
    }
}