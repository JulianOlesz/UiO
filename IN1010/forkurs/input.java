package IN1010.forkurs;
import java.util.Scanner;

public class input {
    static void main(String[] args){
        Scanner input = new Scanner(System.in);
        System.out.println("Skriv noe:");
        String noe = input.nextLine();
        input.close();
        System.out.println("Du skrev: " + noe);
    }
}
