public interface QueueADT<T> {
    void clear();
    void enqueue(T item);
    T dequeue();
    int length();
    T frontValue();
    T rearValue();
    T leaveQueue();
}
