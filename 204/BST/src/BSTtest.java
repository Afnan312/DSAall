import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class BSTtest {
    public static void main(String[] args) throws IOException {
        BST bst=new BST();
        BufferedReader br = new BufferedReader(new FileReader("Input.txt"));
        while (true) {
            String line = br.readLine();
            if (line == null || (line.length() == 0 && br.readLine() == null)) break;
            String[] tokens = line.split(" ");
            if(tokens[0].equalsIgnoreCase("I")){
                bst.insert(Integer.parseInt(tokens[1]));
                bst.printBST();
            }
            else if(tokens[0].equalsIgnoreCase("D")){
                bst.delete(Integer.parseInt(tokens[1]));
                bst.printBST();
            }
            else if(tokens[0].equalsIgnoreCase("F")){
                bst.find(Integer.parseInt(tokens[1]));
            }
            else if(tokens[0].equalsIgnoreCase("T")){
                if(tokens[1].equalsIgnoreCase("In"))
                    bst.inOrder();
                else if(tokens[1].equalsIgnoreCase("Pre"))
                    bst.preOrder();
                else if(tokens[1].equalsIgnoreCase("Post"))
                    bst.postOrder();
            }
        }
    }
}
