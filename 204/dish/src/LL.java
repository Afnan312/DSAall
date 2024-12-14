public class LL<T> implements StackADT<T> {

    Node<T> top;
    int tos;

    public LL(){
        top=new Node<>();
        tos=0;
    }

    @Override
    public void clear() {
        for(int i=0; i<tos; i++) {
            Node<T> temp=top.next;
            top.item=null;
            top.next=null;
            top=temp;
        }
        top=null;
        tos=0;
    }

    @Override
    public void push(T t) {
        Node<T> n_top=new Node<>(t);
        if(top!=null)
            n_top.next = top;
        top=n_top;
        tos++;
    }

    @Override
    public T pop() {
        if(top==null)
            return null;
        Node<T> toRemove=top;
        top=top.next;
        tos--;
        return toRemove.item;
    }

    @Override
    public int length() {
        return tos;
    }

    @Override
    public T topValue() {
        return top.item;
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
