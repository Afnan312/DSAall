package ListADT;
public class MyLinkedList<T> implements CustomList<T> {

    private int size;

    private Node<T> head;
    private Node<T> tail;
    //the node prev is taken previous to the current node
    private Node<T> prev;

    public MyLinkedList() {
        //all nodes are initialized to null
        head=tail=prev= new Node<>();
        size=0;
    }

    public MyLinkedList(T[] ts) {
        this();
        for (T i : ts)
            this.append(i);
    }

    @Override
    public void clear() {
        //change current node to head to clear all nodes from the beginning
        prev = head;
        //unlink the nodes and set the data to null to help in garbage collection up to the tail;
        while (prev != tail) {
            Node<T> next = prev.next;
            prev.item = null;
            prev.next = null;
            prev = next;
        }
        //all nodes will be pointing to null
        head = tail = prev = null;
        size = 0;
    }

    @Override
    public void insert(T t) {
        Node<T> newNode = new Node<>(t);
        newNode.next = prev.next;
        prev.next = newNode;
        size++;
    }

    @Override
    public void append(T t) {
        Node<T> newNode = new Node<>(t);
        Node<T> last=tail;
        tail=newNode;
        if(last == null)
            prev.next = head.next = newNode;
        else
            last.next = tail;
        size++;
    }

    @Override
    public T remove() {
        Node<T> toRemove = prev.next;
        //if the prev node is before the tail node, the prev node becomes tail, the former tail node is removed
        //and the prev node is shifted to the left
        if (prev.next == tail) {
            tail = prev;
            prev.next = prev.next.next;
            prev();
        }
        else
            prev.next = prev.next.next;
        size--;
        return toRemove.item;
    }

    @Override
    public void moveToStart() {
        prev = head;
    }

    @Override
    public void moveToEnd() {
        prev = head;
        for (int i = 0; i < size-1; i++)
            prev = prev.next;
    }

    @Override
    public void prev() {
        if (prev == head)
            return;
        Node<T> temp = head;
        while (temp.next != prev)
            temp = temp.next;
        prev = temp;
    }

    @Override
    public void next() {
        if (prev.next == tail)
            return;
        prev = prev.next;
    }

    @Override
    public int length() {
        return size;
    }

    @Override
    public int currPos() {
        int i;
        Node<T> temp = head;
        for (i = 0; temp != prev; i++)
            temp = temp.next;
        return i;
    }

    @Override
    public void moveToPos(int pos) {
        prev = head;
        for (int i = 0; i < pos; i++)
            prev = prev.next;
    }

    @Override
    public T getValue() {
        return prev.next.item;
    }

    @Override
    public int Search(T t) {
        int found = -1;
        int SearchPos = 0;
        Node<T> temp = head;
        for (int i = 0; i < size - 1; i++) {
            temp = temp.next;
            if (temp.item == t) {
                found=1;
                break;
            }
            SearchPos++;
        }
        if(found==1)
            return SearchPos;
        else
            return -1;

    }

    private static class Node<T> {
        T item;
        Node<T> next;

        Node(T data) {
            item = data;
            next = null;
        }

        public Node() {
            item=null;
            next=null;
        }
    }
}
