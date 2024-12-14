package ListADT;

public class MyArrayList<T> implements CustomList<T>{
    private T[] arr;
    private int size=0;
    private int pos=0;
    private int capacity;
    private int new_capacity;

    @SuppressWarnings("unchecked")
    public MyArrayList(int capacity){
        this.capacity=capacity;
        arr=(T[])new Object[capacity];
    }

    @SuppressWarnings("unchecked")
    public MyArrayList(T[] ts, int capacity){
        this.capacity=capacity;
        arr= (T[]) new Object[capacity];
        size=ts.length;
        for(int i=0; i<size; i++)
            arr[i]=ts[i];
    }

    @Override
    public void clear() {
        for(int i=0; i<size; i++)
            arr[i]=null;
        size=0;
        pos=0;
        capacity=0;
    }

    @SuppressWarnings("unchecked")
    private void grow(){
        new_capacity=size+capacity;
        T[] temp=(T[]) new Object[new_capacity];
        for(int i=0; i<size; i++)
            temp[i]=arr[i];
        arr=temp;
    }

    @Override
    public void insert(T t) {
        if(size==new_capacity)
            grow();
        for(int i=size-1; i>=pos; i--)
            arr[i+1]=arr[i];
        arr[pos]=t;
        size++;
    }

    @Override
    public void append(T t) {
        if(size==new_capacity)
            grow();
        arr[size]=t;
        size++;
    }

    @Override
    public T remove() {
        T var= arr[pos];
        //System.arraycopy(arr, pos+1, arr, pos, size-pos-1);
        for(int i=pos; i<size-1; i++)
            arr[i]=arr[i+1];
        size--;
        arr[size]=null;
        return var;
    }

    @Override
    public void moveToStart() {
        pos=0;
    }

    @Override
    public void moveToEnd() {
        pos=size-1;
    }

    @Override
    public void prev() {
        if(pos>0)
            pos--;
    }

    @Override
    public void next() {
        if(pos<size-1)
            pos++;
    }

    @Override
    public int length() {
        return size;
    }

    @Override
    public int currPos() {
        return pos;
    }

    @Override
    public void moveToPos(int pos) {
        this.pos=pos;
    }

    @Override
    public T getValue() {
        return arr[pos];
    }

    @Override
    public int Search(T t) {
        for(int i=0; i<size; i++)
            if(t.equals(arr[i]))
                return i;
        return -1;
    }
}
