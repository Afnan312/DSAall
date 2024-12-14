public class Arr<T> implements QueueADT<T>{

    private int front, rear;
    private int chunk, capacity;
    private T[] arr;

    public Arr(){
        this(10);
    }
    @SuppressWarnings("unchecked")
    public Arr(int capacity){
        this.chunk=this.capacity=capacity;
        rear=0;
        front=1;
        arr=(T[]) new Object[capacity+1];
    }
    @SuppressWarnings("unchecked")
    public Arr(T[] ts){
        this.chunk=this.capacity=ts.length-1;
        rear=0;
        front=1;
        arr=(T[])new Object[ts.length];
    }

    @SuppressWarnings("unchecked")
    public Arr(T[] ts, int size){
        this.chunk=this.capacity=size;
        rear=0;
        front=1;
        arr=(T[])new Object[size+1];
        for(T x:ts)
            this.enqueue(x);
    }

    @Override
    public void clear() {
        rear=0;
        front=1;
    }

    @SuppressWarnings("unchecked")
    private void grow(){
        if(rear==capacity || rear==capacity-1){
            capacity=capacity+chunk;
            T[] temp=(T[]) new Object[capacity+1];
            for(int i=0; i<=rear; i++)
                temp[i]=arr[i];
            arr=temp;
        }
       else if(rear<capacity){
            capacity=capacity+chunk;
            T[] temp=(T[]) new Object[capacity+1];
            for(int i=0; i<=rear; i++)
                temp[i]=arr[i];
            for(int i=front; i<=capacity-chunk; i++)
                temp[i+chunk]=arr[i];
            front+=chunk;
            arr=temp;
        }
    }

    @Override
    public void enqueue(T item) {
        if(this.length()==capacity)
            grow();
        rear = (rear+1)%(capacity+1);
        arr[rear]=item;
    }

    @Override
    public T dequeue() {
        if(this.length()==0)
            return null;
        T toRemove=arr[front];
        front=(front+1)%(capacity+1);
        return toRemove;
    }

    @Override
    public int length() {
        return (rear+(capacity+1)-front+1)%(capacity+1) ;
    }

    @Override
    public T frontValue() {
        if(this.length()==0)
            return null;
        return arr[front];
    }

    @Override
    public T rearValue() {
        if(this.length()==0)
            return null;
        return arr[rear];
    }

    @Override
    public T leaveQueue() {
        if(this.length()==0)
            return null;
        T toRemove=arr[rear];
        if(rear>0)
            rear--;
        else
            rear=capacity;
        return toRemove;
    }
}
