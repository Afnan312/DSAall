
public class Arr1<T> implements StackADT<T>{

    private T[] arrSt;
    private int top;
    private final int chunk;
    private int capacity;
    private int direction;
    Arr1<T> arrSt2=new Arr1<>(10);

    @SuppressWarnings("unchecked")
    public Arr1(int capacity){
        arrSt=(T[])new Object[capacity];
        this.chunk=this.capacity=capacity;
        this.direction=1;
        top=-1;
    }

    @SuppressWarnings("unchecked")
    public Arr1(T[] ts){
        this.chunk=this.capacity=ts.length;
        this.direction=1;
        top=-1;
        arrSt=(T[])new Object[capacity];
        for (T t : ts) this.push(t);
    }

    @SuppressWarnings("unchecked")
    public Arr1(T[] ts, int direction){
        this.chunk=this.capacity=ts.length;
        this.direction=direction;
        arrSt= (T[])new Object[capacity];
        if(direction==1)
            top=-1;
        else if(direction==-1)
            top=capacity;
    }

    @Override
    public void clear() {
        if(direction==1) {
            for (int i = 0; i <= top; i++)
                arrSt[i] = null;
            top = -1;
        }
        else if(direction==-1){
            for(int i=top; i<capacity; i++)
                arrSt[i]=null;
            top=capacity;
        }
    }

    @SuppressWarnings("unchecked")
    private void grow_up() {
        capacity = capacity + chunk;
        T[] temp = (T[]) new Object[capacity];

        for (int i = 0; i <= top; i++)
            temp[i] = arrSt[i];
        arrSt=temp;
    }

    @SuppressWarnings("unchecked")
    private void grow_down(){
        capacity = capacity + chunk;
        T[] temp = (T[]) new Object[capacity];
        for(int i=0, j=chunk; j<capacity; i++, j++)
            temp[j]=arrSt[i];
        top=chunk;
        arrSt=temp;
    }

    @Override
    public void push(T t) {
        if(direction==1) {
            if (top == capacity-1)
                grow_up();
            arrSt[++top] = t;
        }
        else if(direction==-1){
            if(top==0)
                grow_down();
            arrSt[--top]=t;
        }
    }

    @Override
    public T pop() {
        if(direction==-1)
            return arrSt[top++];
        return arrSt[top--];
    }

    @Override
    public int length() {
        if(direction==-1)
            return capacity-top;
        return top+1;
    }

    @Override
    public T topValue() {
        if(top==-1 || top==capacity)
            return null;
        return arrSt[top];
    }

    @Override
    public void setDirection(int direction) {
        if (top == -1 && direction == -1)
            top=capacity;
        else if(top==capacity && direction==1)
            top=-1;

    }

    public void insert(T item, int offset){
        if((this.length()-1-offset)<0){
            int top=this.length()-1;
            System.out.println("Invalid value of offset. The maximum value is "+ top);
        }
        while(arrSt2.length()<=this.length()-1-offset){
            arrSt2.push(this.pop());
        }
        this.push(item);
        while(arrSt2.length()>0){
            this.push(arrSt2.pop());
        }
    }
    public T remove(int offset){
        if((this.length()-1-offset)<0){
            int top=this.length()-1;
            System.out.println("Invalid value of offset. The maximum value is "+ top);
        }
        while(arrSt2.length()<this.length()-1-offset){
            arrSt2.push(this.pop());
        }
        T toRemove=this.pop();
        while(arrSt2.length()>0){
            this.push(arrSt2.pop());
        }
        return toRemove;
    }
}
