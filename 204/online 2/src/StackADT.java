public interface StackADT<T> {
    void clear();
    void push(T t);
    T pop();
    int length();
    T topValue();
    default void setDirection(int direction){
        direction=1;
    }
}
