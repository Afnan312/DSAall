import java.io.*;
import java.util.ArrayList;

public class Main {
    public static void main(String[] args) throws IOException {
        int n;
        int X;
        int l;
        int s;
        int t;
        ArrayList<ArrayList<Integer>> adjacent;
        ArrayList<Integer> ladder;
        ArrayList<Integer> snake;

        System.setIn(new FileInputStream("input.txt"));
        System.setOut(new PrintStream("output.txt"));
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));


        String line = br.readLine();
        t = (Integer.parseInt(line));
        for (int i = 1; i <= t; i++) {
            line = br.readLine();
            String[] tokens = line.split(" ");
            n = Integer.parseInt(tokens[0]);
            X = Integer.parseInt(tokens[1]);
            adjacent = new ArrayList<>(X);
            for (int j = 0; j < X; j++)
                adjacent.add(new ArrayList<Integer>());
            line = br.readLine();
            l = Integer.parseInt(line);
            ladder = new ArrayList<>(l);
            int start, end;
            for (int j = 0; j < l; j++) {
                line = br.readLine();
                tokens = line.split(" ");
                start = Integer.parseInt(tokens[0]);
                end = Integer.parseInt(tokens[1]);
                ladder.add(start);
                adjacent.get(start).add(end);
            }
            line = br.readLine();
            s = Integer.parseInt(line);
            snake = new ArrayList<>(s);
            for (int j = 0; j < s; j++) {
                line = br.readLine();
                tokens = line.split(" ");
                start = Integer.parseInt(tokens[0]);
                end = Integer.parseInt(tokens[1]);
                snake.add(start);
                adjacent.get(start).add(end);
            }

            Graph call = new Graph(adjacent, ladder, snake, n, X);
            call.find_least_path();
        }
        br.close();

    }
}
