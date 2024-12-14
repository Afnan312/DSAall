package ListADT;

public interface CustomList<T> {
    void clear();
    void insert(T t);
    void append(T t);
    T remove();
    void moveToStart();
    void moveToEnd();
    void prev();
    void next();
    int length();
    int currPos();
    void moveToPos(int pos);
    T getValue();
    int Search(T t);
}
