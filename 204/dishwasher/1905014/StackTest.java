import java.util.Scanner;

public class StackTest {
    public static void print_stacka(Arr<Integer> s){
        Arr<Integer> temp=new Arr<>(s.length());

        while (s.length()>0)
        {
            temp.push(s.topValue());
            s.pop();
        }
        System.out.print("<");
        while (temp.length()>0)
        {
            int t = temp.topValue();
            System.out.print(t + " ");
            temp.pop();

            s.push(t);
        }
        System.out.println(">");
    }

    public static void print_stackl(LL<Integer> s){
        LL<Integer> temp=new LL<>();

        while (s.length()>0)
        {
            temp.push(s.topValue());
            s.pop();
        }
        System.out.print("<");
        while (temp.length()>0)
        {
            int t = temp.topValue();
            System.out.print(t + " ");
            temp.pop();

            s.push(t);
        }
        System.out.println(">");
    }

    public static void main(String[] args) {
        Scanner scn = new Scanner(System.in);
        int K;
        K = scn.nextInt();
        Integer[] inArr = new Integer[K];
        for (int i = 0; i < K; i++) {
            inArr[i] = scn.nextInt();
        }

        Arr<Integer> Stk=new Arr<>(inArr);
        //LL<Integer> Stk=new LL<>(inArr);

        print_stacka(Stk);
        //print_stackl(Stk);

        int Q, P;
        while (true) {
            Q = scn.nextInt();
            P = scn.nextInt();

            if (Q == 1) {
                Stk.clear();
                print_stacka(Stk);
                //print_stackl(Stk);
                System.out.println("-1");
            } else if (Q == 2) {
                Integer input = P;
                Stk.push(input);
                print_stacka(Stk);
                //print_stackl(Stk);
                System.out.println("-1");
            } else if (Q == 3) {
                int x = Stk.pop();
                print_stacka(Stk);
                //print_stackl(Stk);
                System.out.println(x);
            } else if (Q == 4) {
                print_stacka(Stk);
                //print_stackl(Stk);
                System.out.println(Stk.length());
            } else if (Q == 5) {
                print_stacka(Stk);
                //print_stackl(Stk);
                System.out.println(Stk.topValue());
            } else if(Q==6){
                Stk.setDirection(P);
                print_stacka(Stk);
                //print_stackl(Stk);
                System.out.println("-1");
            }
            else if (Q == 0)
                break;
            else
                System.out.println("Invalid input. 0<=Q<=6");
        }
    }
}
