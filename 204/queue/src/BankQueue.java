import java.util.Scanner;
public class BankQueue {
    public static void main(String[] args) {
        Arr<Integer> queue1;
        Arr<Integer> queue2;
        //LL<Integer> queue1=new LL<>();
        //LL<Integer> queue2=new LL<>();
        int[] t_enter_array;
        int[] t_serve_array;
        int timer, served=0;
        int j=0;
        int qt1=0, qt2=0;

        Scanner scn=new Scanner(System.in);

        int total=scn.nextInt();

        queue1=new Arr<>(total);
        queue2=new Arr<>(total);

        t_enter_array=new int[total];
        t_serve_array=new int[total];

        for(int i=0; i<total; i++){
            t_enter_array[i]=scn.nextInt();
            t_serve_array[i]=scn.nextInt();
        }

        for(timer=0; served<total; timer++){
            //this if block is for new customers
            if(j<total && timer==t_enter_array[j]){//current time matches with time of entry
                if(queue1.length()==queue2.length()) {
                    if(queue1.length()==0 && qt1==timer) { //queue1 and service are empty
                        queue1.enqueue(t_serve_array[j]);
                        System.out.println("Customer " + (j+1) +" entered booth 1 at t=" + timer);
                    }
                    else if(queue2.length()==0 && qt2==timer) { //queue2 and service are empty
                        queue2.enqueue(t_serve_array[j]);
                        System.out.println("Customer " + (j+1) +" entered booth 2 at t=" + timer);
                    }
                    else { //service area is not empty. default queue in queue1
                        queue1.enqueue(t_serve_array[j]);
                        System.out.println("Customer " + (j+1) +" entered queue 1 at t=" + timer);
                    }
                }
                else {//new customer takes place in the smallest queue
                    if(queue1.length()<queue2.length()) {
                        queue1.enqueue(t_serve_array[j]);
                        System.out.println("Customer " + (j+1) +" entered queue 1 at t=" + timer);
                    }
                    else {
                        queue2.enqueue(t_serve_array[j]);
                        System.out.println("Customer " + (j+1) +" entered queue 2 at t=" + timer);
                    }
                }
                j++;
            }

            //this if-else block is for service in booth 1
            if(qt1==timer && queue1.length()!=0){//provides service to the 1st in queue 1
                qt1+=queue1.dequeue();
                if(j==1){
                    System.out.print("Service started in Booth 1. ");
                }
                else
                    System.out.print("Previous service of Booth 1 ended. Next ");
                System.out.println("Service at booth 1 will end at t=" + qt1);
                served++;
            }
            else if(qt1==timer && queue1.length()==0 && queue2.length()!=0 && qt1!=qt2){//both the queue and service area are empty
                //provides service to the 1st in the other queue
                queue1.enqueue(queue2.dequeue());
                qt1+=queue1.dequeue();
                System.out.print("Previous service of Booth 1 ended. Queue 1 is empty. ");
                System.out.println("Switched from front of queue 2 to booth 1. Service at booth 1 will end at t=" + qt1);
                served++;
            }

            //this if-else block is for service in booth 2
            if(qt2==timer && queue2.length()!=0){//provides service to the 1st in queue 2
                if(j==2){
                    System.out.print("Service started in Booth 2. ");
                }
                else
                    System.out.print("Previous service of Booth 2 ended. Next ");
                qt2+=queue2.dequeue();
                System.out.println("Service at booth 2 will end at t=" + qt2);
                served++;
            }
            else if(qt2==timer && queue2.length()==0 &&queue1.length()!=0 && qt1!=qt2){//both the queue and service area are empty
                //provides service to the 1st in the other queue
                queue2.enqueue(queue1.dequeue());
                qt2+=queue2.dequeue();
                System.out.print("Previous service of Booth 2 ended. Queue 2 is empty. ");
                System.out.println("Switched from front of queue 1 to booth 2. Service at booth 2 will end at t=" + qt2);
                served++;
            }

            //this block is for switching queues
            if(queue1.length()<queue2.length()-1) {
                queue1.enqueue(queue2.leaveQueue());
                System.out.println("Last customer of queue 2 switched to queue 1 at t=" + timer);
            }
            else if(queue2.length()<queue1.length()-1) {
                queue2.enqueue(queue1.leaveQueue());
                System.out.println("Last customer of queue 1 switched to queue 2 at t=" + timer);
            }

            if(qt1<=timer && queue1.length()==0)
                qt1++;
            if(qt2<=timer && queue2.length()==0)
                qt2++;
        }
        System.out.println("Booth 1 finishes service at t=" + qt1);
        System.out.println("Booth 2 finishes service at t=" + qt2);
    }
}
