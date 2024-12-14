
import java.util.Scanner;
public class dw {
    public static void main(String[] args) {
        int total=0;//total dishes served
        int[] timekeep;//time of cleaning completion
        int[] timer;//track of time required to clean each dish

        Arr<Integer> full;//id of those who have completed the course

        int[] t_seq;//sequence of time inputs
        int[] s_seq;//sequence of size inputs

        int full_count=0;//number of guests who have completed the course

        Arr<Integer> dirty;
        Arr<Integer> clean;
        //LL<Integer> dirty=new LL<>();
        //LL<Integer> clean=new LL<>();
        //Integer[] stackArray;

        Scanner scn=new Scanner(System.in);
        int n=scn.nextInt();
        int x=scn.nextInt();

        full=new Arr<>(n);

        timer=new int[x];
        for(int i=0; i<x; i++)
            timer[i]=scn.nextInt();

        dirty=new Arr<>(n*x);
        clean=new Arr<>(n*x);

        //stackArray=new Integer[n*x];
        //ArrayImp<Integer> dirty=new Arr<>(stackArray, 1);
        //ArrayImp<Integer> clean=new Arr<>(stackArray, -1);

        timekeep=new int[n*x];

        t_seq=new int[n*x];
        s_seq=new int[n*x];
        int k, t, s;
        int i=0, j=0, temp;

        while((k=scn.nextInt())!=0){
            t= scn.nextInt();
            s= scn.nextInt();

            t_seq[i]=t;
            s_seq[i]=s;
            total++;

            if(s==x) {
                full.push(k);
                full_count++;
            }
            i++;
        }

        i=0;
        int t1=0, l=0;
//i will become the current time, t1 will become the time by which cleaning has ended/to be started
        for(int cleaned=0; cleaned<total;i++){
            if(i == t_seq[l]) {
                dirty.push(s_seq[l]);
                l++;
            }

            if(t1==i && dirty.length()!=0){
                temp=dirty.pop();
                t1+=timer[temp-1];
                timekeep[j++]=t1-1;
                clean.push(temp);
                cleaned++;
            }
            else if(t1<i && dirty.length()!=0){
                t1=i;
                temp=dirty.pop();
                t1+=timer[temp-1];
                timekeep[j++]=t1-1;
                clean.push(temp);
                cleaned++;
            }
        }

        System.out.println(t1-1);

        for (int value : timekeep) {
            if(value!=0)
                System.out.print(value + ",");
            else
                break;
        }
        System.out.println("\b");

        if(full_count==n)
            System.out.println("Y");
        else
            System.out.println("N");
        while(full.length()>0){
            if(full.topValue()!=0)
                System.out.print(full.pop()+",");
        }
        System.out.println("\b");
    }
}
