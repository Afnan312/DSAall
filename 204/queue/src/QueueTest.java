import java.util.Scanner;
public class QueueTest {
    public static void print_queuel(LL<Integer> queue){
        if(queue.length()==0)
            System.out.println("<>");
        else {
            LL<Integer> temp = new LL<>();
            System.out.print("<");
            while (queue.length() > 0) {
                System.out.println("enqueue in temp");
                temp.enqueue(queue.dequeue());
            }
            System.out.println(temp.length());
            while (temp.length() > 0) {
                System.out.print(temp.frontValue() + ",");
                queue.enqueue(temp.dequeue());
            }
            System.out.println("\b>");
        }
    }
    public static void print_queuea(Arr<Integer> queue){
        if(queue.length()==0)
            System.out.println("<>");
        else {
            Arr<Integer> temp = new Arr<>(queue.length());
            System.out.print("<");
            while (queue.length() > 0) {
                temp.enqueue(queue.dequeue());
            }
            while (temp.length() > 0) {
                System.out.print(temp.frontValue() + ",");
                queue.enqueue(temp.dequeue());
            }
            System.out.println("\b>");
        }
    }
    public static void main(String[] args) {
        Scanner scn = new Scanner(System.in);
        int K;
        K = scn.nextInt();
        Integer[] inArr = new Integer[K];
        for (int i = 0; i < K; i++) {
            inArr[i] = scn.nextInt();
        }

        Arr<Integer> que=new Arr<>(inArr, K);
        //LL<Integer> que=new LL<>(inArr);

        print_queuea(que);
        //print_queuel(que);
        int Q, P;
        while (true) {
            Q = scn.nextInt();
            P = scn.nextInt();
            if(Q==1){
                que.clear();
                print_queuea(que);
                //print_queuel(que);
                System.out.println("-1");
            }
            else if(Q==2){
                Integer x=P;
                que.enqueue(x);
                print_queuea(que);
                //print_queuel(que);
                System.out.println("-1");
            }
            else if(Q==3){
                Integer x=que.dequeue();
                print_queuea(que);
                //print_queuel(que);
                System.out.println(x);
            }
            else if(Q==4){
                int x=que.length();
                print_queuea(que);
                //print_queuel(que);
                System.out.println(x);
            }
            else if(Q==5){
                Integer x=que.frontValue();
                print_queuea(que);
                //print_queuel(que);
                System.out.println(x);
            }
            else if(Q==6){
                Integer x=que.rearValue();
                print_queuea(que);
                //print_queuel(que);
                System.out.println(x);
            }
            else if(Q==7){
                Integer x=que.leaveQueue();
                print_queuea(que);
                //print_queuel(que);
                System.out.println(x);
            }
            else if(Q==0)
                break;
            else
                System.out.println("Invalid input. 0<=Q<=7");
        }
    }
}
