package IN1010.forkurs;

public class forlokke {
    static void main(String[] args){
        int[] tallArray;
        tallArray = new int[5];
        tallArray[0] = 10;
        tallArray[1] = 20;
        tallArray[2] = 30;
        tallArray[3] = 40;
        tallArray[4] = 50;

        for(int i=0; i < 5; i++){
            System.out.println(tallArray[i]);
        }
    }
}
