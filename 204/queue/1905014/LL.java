
public class LL<T> implements QueueADT<T>{

    private Node<T> front;
    private Node<T> rear;
    private int size;

    public LL(){
        front=rear=new Node<T>();
        size=0;
    }

    public LL(T[] ts){
        this();
        for (T i : ts)
            this.enqueue(i);
    }

    @Override
    public void clear() {
        Node<T> curr=front.next;
        while(curr!=null) {
            Node<T> next = curr.next;
            curr.item = null;
            curr.next = null;
            curr = next;
        }
        rear = null;
        size = 0;
    }

    @Override
    public void enqueue(T item) {
        Node<T> newNode = new Node<>(item);
        Node<T> last=rear;
        rear=newNode;
        //if the list is empty, the only node will be rear
        if(last == null)
            front.next = newNode;
        //the next node of previous rear will be the new rear
        else
            last.next = rear;
        size++;
    }

    @Override
    public T dequeue() {
        if(this.length()==0)
            return null;
        T toRemove=front.next.item;
        front.next=front.next.next;
        if(front.next==null)
            rear=front;
        size--;
        return toRemove;
    }

    @Override
    public int length() {
        return size;
    }

    @Override
    public T frontValue() {
        if(this.length()==0)
            return null;
        return front.next.item;
    }

    @Override
    public T rearValue() {
        if(this.length()==0)
            return null;
        return rear.item;
    }

    @Override
    public T leaveQueue() {
        if(this.length()==0)
            return null;
        T toRemove=rear.item;
        Node<T> curr=front.next;
        while(curr.next!=rear){
            curr=curr.next;
        }
        curr.next=null;
        rear=curr;
        size--;
        return toRemove;
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
