/*
*   basado en: https://github.com/Bibeknam/algorithmtutorprograms/blob/master/data-structures/red-black-trees/RedBlackTree.java
*/
public class RedBlackTree<T extends Comparable<? super T>> {
	private Node<T> root;
    private Node<T> TNULL;

    public RedBlackTree() {
		TNULL = new Node<T>();
		TNULL.color = 0;
		TNULL.left = null;
		TNULL.right = null;
		root = TNULL;
	}

	private void preOrderHelper(Node<T> node) {
		if (node != TNULL) {
			System.out.print(node.getData() + " ");
			preOrderHelper(node.getLeft());
			preOrderHelper(node.getRight());
		} 
	}

	private void inOrderHelper(Node<T> node) {
		if (node != TNULL) {
			inOrderHelper(node.getLeft());
			System.out.print(node.getData() + " ");
			inOrderHelper(node.getRight());
		} 
	}

	private void postOrderHelper(Node<T> node) {
		if (node != TNULL) {
			postOrderHelper(node.getLeft());
			postOrderHelper(node.getRight());
			System.out.print(node.getData() + " ");
		} 
	}

	private Node<T> searchTreeHelper(Node<T> node, T key) {
		if (node == TNULL || key.compareTo( node.getData()) == 0) {
			return node;
		}

		if (key.compareTo( node.getData()) < 0) {
			return searchTreeHelper(node.getLeft(), key);
		} 
		return searchTreeHelper(node.getRight(), key);
	}

	// fix the rb tree modified by the delete operation
	private void fixDelete(Node<T> x) {
		Node<T> s;
		while (x != root && x.color == 0) {
			if (x == x.parent.getLeft()) {
				s = x.parent.getRight();
				if (s.color == 1) {
					// case 3.1
					s.color = 0;
					x.parent.color = 1;
					leftRotate(x.parent);
					s = x.parent.getRight();
				}

				if (s.getLeft().color == 0 && s.getRight().color == 0) {
					// case 3.2
					s.color = 1;
					x = x.parent;
				} else {
					if (s.getRight().color == 0) {
						// case 3.3
						s.getLeft().color = 0;
						s.color = 1;
						rightRotate(s);
						s = x.parent.getRight();
					} 

					// case 3.4
					s.color = x.parent.color;
					x.parent.color = 0;
					s.getRight().color = 0;
					leftRotate(x.parent);
					x = root;
				}
			} else {
				s = x.parent.getLeft();
				if (s.color == 1) {
					// case 3.1
					s.color = 0;
					x.parent.color = 1;
					rightRotate(x.parent);
					s = x.parent.getLeft();
				}

				if (s.getRight().color == 0) {
					// case 3.2
					s.color = 1;
					x = x.parent;
				} else {
					if (s.getLeft().color == 0) {
						// case 3.3
						s.getRight().color = 0;
						s.color = 1;
						leftRotate(s);
						s = x.parent.getLeft();
					} 

					// case 3.4
					s.color = x.parent.color;
					x.parent.color = 0;
					s.getLeft().color = 0;
					rightRotate(x.parent);
					x = root;
				}
			} 
		}
		x.color = 0;
	}


	private void rbTransplant(Node<T> u, Node<T> v){
		if (u.parent == TNULL) {
			root = v;
		} else if (u == u.parent.getLeft()){
			u.parent.setLeft(v);
		} else {
			u.parent.setRight(v);
		}
		v.parent = u.parent;
	}

	private void deleteNodeHelper(Node<T> node, T key) {
		// find the node containing key
		Node<T> z = TNULL;
		Node<T> x, y;
		while (node != TNULL){
			if (node.getData().compareTo(key) == 0) {
				z = node;
			}

			if (node.getData().compareTo(key) <= 0) {
				node = node.getRight();
			} else {
				node = node.getLeft();
			}
		}

		if (z == TNULL) {
			System.out.println("Couldn't find key in the tree");
			return;
		} 

		y = z;
		int yOriginalColor = y.color;
		if (z.left == TNULL) {
			x = z.right;
			rbTransplant(z, z.right);
		} else if (z.right == TNULL) {
			x = z.left;
			rbTransplant(z, z.left);
		} else {
			y = minimum(z.right);
			yOriginalColor = y.color;
			x = y.right;
			if (y.parent == z) {
				x.parent = y;
			} else {
				rbTransplant(y, y.right);
				y.right = z.right;
				y.right.parent = y;
			}

			rbTransplant(z, y);
			y.left = z.left;
			y.left.parent = y;
			y.color = z.color;
		}
		if (yOriginalColor == 0){
			fixDelete(x);
		}
	}
	
	// fix the red-black tree
	private void fixInsert(Node<T> k){
		Node<T> u;
		while (k.parent.color == 1) {
			if (k.parent == k.parent.parent.right) {
				u = k.parent.parent.left; // uncle
				if (u.color == 1) {
					// case 3.1
					u.color = 0;
					k.parent.color = 0;
					k.parent.parent.color = 1;
					k = k.parent.parent;
				} else {
					if (k == k.parent.left) {
						// case 3.2.2
						k = k.parent;
						rightRotate(k);
					}
					// case 3.2.1
					k.parent.color = 0;
					k.parent.parent.color = 1;
					leftRotate(k.parent.parent);
				}
			} else {
				u = k.parent.parent.right; // uncle

				if (u.color == 1) {
					// mirror case 3.1
					u.color = 0;
					k.parent.color = 0;
					k.parent.parent.color = 1;
					k = k.parent.parent;	
				} else {
					if (k == k.parent.right) {
						// mirror case 3.2.2
						k = k.parent;
						leftRotate(k);
					}
					// mirror case 3.2.1
					k.parent.color = 0;
					k.parent.parent.color = 1;
					rightRotate(k.parent.parent);
				}
			}
			if (k == root) {
				break;
			}
		}
		root.color = 0;
	}

	// Pre-Order traversal
	// Node.Left Subtree.Right Subtree
	public void preorder() {
		preOrderHelper(this.root);
	}

	// In-Order traversal
	// Left Subtree . Node . Right Subtree
	public void inorder() {
		inOrderHelper(this.root);
	}

	// Post-Order traversal
	// Left Subtree . Right Subtree . Node
	public void postorder() {
		postOrderHelper(this.root);
	}

	// search the tree for the key k
	// and return the corresponding node
	public Node<T> searchTree(T k) {
		return searchTreeHelper(this.root, k);
	}

	// find the node with the minimum key
	public Node<T> minimum(Node<T> node) {
		while (node.left != TNULL) {
			node = node.left;
		}
		return node;
	}

	// find the node with the maximum key
	public Node<T> maximum(Node<T> node) {
		while (node.right != TNULL) {
			node = node.right;
		}
		return node;
	}

	// find the successor of a given node
	public Node<T> successor(Node<T> x) {
		// if the right subtree is not null,
		// the successor is the leftmost node in the
		// right subtree
		if (x.right != TNULL) {
			return minimum(x.right);
		}

		// else it is the lowest ancestor of x whose
		// left child is also an ancestor of x.
		Node<T> y = x.parent;
		while (y != TNULL && x == y.right) {
			x = y;
			y = y.parent;
		}
		return y;
	}

	// find the predecessor of a given node
	public Node<T> predecessor(Node<T> x) {
		// if the left subtree is not null,
		// the predecessor is the rightmost node in the 
		// left subtree
		if (x.left != TNULL) {
			return maximum(x.left);
		}

		Node<T> y = x.parent;
		while (y != TNULL && x == y.left) {
			x = y;
			y = y.parent;
		}

		return y;
	}

	// rotate left at node x
	public void leftRotate(Node<T> x) {
		Node<T> y = x.right;
		x.right = y.left;
		if (y.left != TNULL) {
			y.left.parent = x;
		}
		y.parent = x.parent;
		if (x.parent == TNULL) {
			this.root = y;
		} else if (x == x.parent.left) {
			x.parent.left = y;
		} else {
			x.parent.right = y;
		}
		y.left = x;
		x.parent = y;
	}

	// rotate right at node x
	public void rightRotate(Node<T> x) {
		Node<T> y = x.left;
		x.left = y.right;
		if (y.right != TNULL) {
			y.right.parent = x;
		}
		y.parent = x.parent;
		if (x.parent == TNULL) {
			this.root = y;
		} else if (x == x.parent.right) {
			x.parent.right = y;
		} else {
			x.parent.left = y;
		}
		y.right = x;
		x.parent = y;
	}

	// insert the key to the tree in its appropriate position
	// and fix the tree
	public void addNode(T key) {
		// Ordinary Binary Search Insertion
		Node<T> node = new Node<T>(key);
		node.parent = TNULL;
		node.data = key;
		node.left = TNULL;
		node.right = TNULL;
		node.color = 1; // new node must be red

		Node<T> y = TNULL;
		Node<T> x = this.root;

		while (x != TNULL) {
			y = x;
            
			if (node.data.compareTo(x.data) < 0) {
				x = x.left;
			} else {
				x = x.right;
			}
		}

		// y is parent of x
		node.parent = y;
		if (y == TNULL) {
			root = node;
		} else if (node.data.compareTo(y.data) < 0) {
			y.left = node;
		} else {
			y.right = node;
		}

		// if new node is a root node, simply return
		if (node.parent == TNULL){
			node.color = 0;
			return;
		}

		// if the grandparent is null, simply return
		if (node.parent.parent == TNULL) {
			return;
		}

		// Fix the tree
		fixInsert(node);
	}

	public Node<T> getRoot(){
		return this.root;
	}

	public void print() {
        TreePrinter.printNode(root);
    }
	
	// delete the node from the tree
	public void deleteNode(T data) {
		deleteNodeHelper(this.root, data);
	}

	public int size(){
        return size(root);
    }

    private int size(Node<T> root){

        if(root==null || root.getData() == null)
            return 0;
        return 1 + size(root.left) + size(root.right);
    }

	public RedBlackTree<T> filter(T data) {
        RedBlackTree<T> toReturn = new RedBlackTree<T>();
        recursiveFilter(toReturn, root, data);
        return toReturn;
    }

    private void recursiveFilter(RedBlackTree<T> tree, Node<T> node, T data) {
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

	public RedBlackTree<T> mul(int times) {
        RedBlackTree<T> toReturn = new RedBlackTree<>();
        recursiveMul(toReturn, root, times);
        return toReturn;
    }

    //  Java does not have this feature. 
    @SuppressWarnings("unchecked")
    private void recursiveMul(RedBlackTree<T> tree, Node<T> node, int times) {
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