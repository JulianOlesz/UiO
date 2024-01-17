package IN1010.uke_3.innlevering_0;
public class Bil3 {
    String bilnummer;

    Bil3(String nummer){
        bilnummer = nummer;
    }

    public void hentNummer(String bilnummer){
        System.out.println(bilnummer);
    }

    public void skrivUt(){
        System.out.println("Jeg er bil nr."+bilnummer);
    }
}