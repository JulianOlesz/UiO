package IN1010.uke_3.innlevering_0;

public class Person {
    static String bil;
    
    Person(String bilnummer){
        bil = bilnummer;
    }
    
    public void main(String[] args) {
        System.out.println("Denne personen eier bil nr."+bil);
    }
}
