public class LL1<T> implements StackADT<T> {

    Node<T> top;
    int tos;
    LL1<T> St2=new LL1<>();

    public LL1(){
        top=new Node<>();
        tos=0;
    }

    public LL1(T[] ts){
        this();
        for(T value : ts)
            this.push(value);
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

    public void insert(T item, int offset){
        if((this.length()-1-offset)<0){
            int top=this.length()-1;
            System.out.println("Invalid value of offset. The maximum value is "+ top);
        }
        while(St2.length()<=this.length()-1-offset){
            St2.push(this.pop());
        }
        this.push(item);
        while(St2.length()>0){
            this.push(St2.pop());
        }
    }
    public T remove(int offset){
        if((this.length()-1-offset)<0){
            int top=this.length()-1;
            System.out.println("Invalid value of offset. The maximum value is "+ top);
        }
        while(St2.length()<this.length()-1-offset){
            St2.push(this.pop());
        }
        T toRemove=this.pop();
        while(St2.length()>0){
            this.push(St2.pop());
        }
        return toRemove;
    }
}
