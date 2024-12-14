import java.util.ArrayList;
import java.util.LinkedList;

public class Graph {
    private ArrayList<ArrayList<Integer>> adjacent;
    private boolean solved;
    private ArrayList<Integer> ladder;
    private ArrayList<Integer> snake;
    private int n;
    private int X;
    private boolean unreachable;

    public Graph(ArrayList<ArrayList<Integer>> adjacent, ArrayList<Integer> ladder, ArrayList<Integer> snake, int n, int X) {
        this.adjacent = adjacent;
        this.ladder = ladder;
        this.snake = snake;
        this.n = n;
        this.X = X;
        solved = false;
        unreachable=false;
    }

    int find_min_visit(int x){//find the minimum square number the ladders can take if they cause unreachable squares
        int min=adjacent.get(x).get(0);
        for(int i=0; i<n-1; i++) {
            x++;
            if (adjacent.get(x).get(0) < min)
                min = adjacent.get(x).get(0);
        }
        return min;
    }

    void find_least_path() {//find the least path using BFS
        int start = 1;

        int[] pred=new int[X+1];
        int[] rolls=new int[X+1];
        boolean[] visited= new boolean[X+1];
        LinkedList<Integer> queue = new LinkedList<>();

        for(int i=1; i<=X; i++){
            pred[i]=0;
            rolls[i]=-1;
            visited[i]=false;
        }
        visited[start]=true;
        rolls[start]=0;
        queue.add(start);

        while(!queue.isEmpty()) {
            int square =queue.remove();
            int max_up;
            int l_continuous =0;
            int s_continuous =0;

            for (int i = square + 1; i <= square +n; i++) {//checking for unreachable squares
                if(ladder.contains(i))
                    l_continuous++;
                else
                    l_continuous=0;
                if(snake.contains(i))
                    s_continuous++;
                else
                    s_continuous=0;
            }
            if(l_continuous==n || s_continuous==n)
                unreachable=true;
            for (int i = square + 1; i <= square +n && i<=X; i++) {//do bfs to assign number of rolls needed
                if(!visited[i]){
                    visited[i]=true;
                    pred[i] = square;
                    rolls[i] = rolls[square] + 1;
                    max_up=i;

                    if(ladder.contains(i)){//find if square is ladder
                        visited[adjacent.get(i).get(0)]=true;
                        pred[adjacent.get(i).get(0)]=i;
                        rolls[adjacent.get(i).get(0)]=rolls[i];
                        max_up=adjacent.get(i).get(0);//the end of ladder
                    }

                    if(snake.contains(i)){//find if the square is snake
                        visited[adjacent.get(i).get(0)]=true;
                        pred[adjacent.get(i).get(0)]=i;
                        rolls[adjacent.get(i).get(0)]=rolls[i];
                        max_up=adjacent.get(i).get(0);//the end of snake
                    }

                    queue.add(max_up);

                }
            }
            
        }
        if(rolls[X]!=-1){
            System.out.println(rolls[X]);
            LinkedList<Integer> least_path=new LinkedList<>();

            int curr=X;//add destination
            least_path.add(curr);
            while(pred[curr]!=0){
                least_path.add(pred[curr]);//find the path by following the predecessor of the square starting from the destination
                curr=pred[curr];
            }
            for(int i=least_path.size()-1; i>=1; i--){
                System.out.print(least_path.get(i) + "->");
            }
            System.out.println(least_path.get(0));

            if(unreachable){
                for(int i=1; i<=X; i++) {
                    if (!visited[i])
                        System.out.print(i + " ");
                }
                System.out.println();
            }
            else
                System.out.println("All reachable");
        }
        else{
            System.out.println(rolls[X]);
            System.out.println("No solution");
            for(int i=1; i<=X; i++) {
                if (!visited[i])
                    System.out.print(i + " ");
            }
            System.out.println();
        }
    }
}
