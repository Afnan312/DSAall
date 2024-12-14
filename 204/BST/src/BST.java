public class BST {
    private bstNode root;

    public BST() {
        root = null;
    }

    public void insert(int item) {
        root = insertHelp(root, item);
    }

    private bstNode insertHelp(bstNode root, int item) {
        if (root == null) {
            root = new bstNode(item);
        } else {
            if (item < root.value)
                root.leftChild = insertHelp(root.leftChild, item);
            else if (item > root.value)
                root.rightChild = insertHelp(root.rightChild, item);
        }
        return root;
    }

    public void delete(int item) {
        root = deleteHelp(root, item);
    }

    private bstNode deleteHelp(bstNode root, int item) {
        if (root == null) {
            return root;
        }
        if((item<root.value && (root.leftChild==null || item>root.leftChild.value)) || (item>root.value && (root.rightChild==null || item<root.rightChild.value ))){
            System.out.println("Invalid Operation");
            return root;
        }
        else if (item < root.value) {
            root.leftChild = deleteHelp(root.leftChild, item);
            return root;
        }
        else if (item > root.value) {
            root.rightChild = deleteHelp(root.rightChild, item);
            return root;
        }
        else {
            if (root.leftChild == null) {
                return root.rightChild;
            }
            else if (root.rightChild == null) {
                return root.leftChild;
            }
            else {
                bstNode predParent=root;
                bstNode pred=root.leftChild;
                while(pred.rightChild!=null){
                    predParent=pred;
                    pred=pred.rightChild;
                }
                if(predParent!=root)
                    predParent.rightChild=pred.leftChild;
                else
                    predParent.leftChild=pred.leftChild;
                root.value=pred.value;
                return root;
            }
        }
        //return root;
    }

    public void find(int item) {
        if(findHelp(root, item)==null)
            System.out.println("False");
        else
            System.out.println("True");
    }

    private bstNode findHelp(bstNode root, int item) {
        if (root == null || root.value == item)
            return root;
        if (item > root.value)
            return findHelp(root.rightChild, item);
        return findHelp(root.leftChild, item);
    }

    public void preOrder() {
        preOrderHelp(root);
        System.out.println();
    }

    public void inOrder() {
        inOrderHelp(root);
        System.out.println();
    }

    public void postOrder() {
        postOrderHelp(root);
        System.out.println();
    }

    public void printBST() {
        printHelp(root);
        System.out.println();
    }

    private void preOrderHelp(bstNode root) {
        if (root != null) {
            System.out.print(root.value + " ");
            preOrderHelp(root.leftChild);
            preOrderHelp(root.rightChild);
        }
        //System.out.println();
    }

    private void inOrderHelp(bstNode root) {
        if (root != null) {
            inOrderHelp(root.leftChild);
            System.out.print(root.value + " ");
            inOrderHelp(root.rightChild);
        }
        //System.out.println();
    }

    private void postOrderHelp(bstNode root) {
        if (root != null) {
            postOrderHelp(root.leftChild);
            postOrderHelp(root.rightChild);
            System.out.print(root.value + " ");
        }
        //System.out.println();
    }

    private void printHelp(bstNode root) {
        if (root == null)
            return;
        System.out.print(root.value);
        if (!root.isLeaf()) {
            System.out.print("(");
            printHelp(root.leftChild);
            System.out.print(")(");
            printHelp(root.rightChild);
            System.out.print(")");
        }
    }

    private static class bstNode {
        private int value;
        bstNode leftChild;
        bstNode rightChild;

        public bstNode(int value) {
            this.value = value;
            leftChild = null;
            rightChild = null;
        }

        public boolean isLeaf() {
            return this.rightChild == null && this.leftChild == null;
        }
    }
}
