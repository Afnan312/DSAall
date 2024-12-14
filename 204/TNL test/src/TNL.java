import java.util.Scanner;

import ListADT.*;

public class TNL {

    public static void print_list(CustomList<Integer> t, int x){
        for(int i=0; i<x; i++){
            if(i==x-1)
                System.out.println(t.getValue());
            else{
                if(t.getValue()==i) {
                    System.out.print(t.getValue() + ",");
                    t.next();
                }
                else
                    System.out.print(",");

            }
        }
    }

    public static void main(String[] args) {
        Scanner scn = new Scanner(System.in);
        int r, b, t;

        r=scn.nextInt();
        Integer [] r_arr=new Integer[r];
        for(int i=0; i<r; i++){
            r_arr[i]=i;
        }

        b=scn.nextInt();
        Integer [] b_arr=new Integer[b];
        for(int i = 0;i<b; i++){
            b_arr[i]= scn.nextInt();
        }

        t=scn.nextInt();
        Integer [] t_arr=new Integer[t];
        for(int i=0; i<t; i++){
            t_arr[i]= scn.nextInt();
        }

        int task=scn.nextInt();

        MyArrayList<Integer> rs=new MyArrayList<>(r_arr, r);
        MyArrayList<Integer> bs=new MyArrayList<>(b_arr, b);
        MyArrayList<Integer> ts=new MyArrayList<>(t_arr, t);

        /*MyLinkedList<Integer> rs=new MyLinkedList<>(r_arr);
        MyLinkedList<Integer> bs=new MyLinkedList<>(b_arr);
        MyLinkedList<Integer> ts=new MyLinkedList<>(t_arr);*/

        print_list(rs, r);
        print_list(bs, r);
        print_list(ts, r);

    }
}
