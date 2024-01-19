package IN1010.uke_3.innlevering_0;

public class BilBruk3 {
    public void main(String[] args) {
        //oppretter bil objekt
        Bil3 bil = new Bil3("3");
        //lager variabel med bilnummeret 
        String bilnr = bil.hentNummer();
        //lager person objekt med hentet nummer
        Person person1 = new Person(bilnr);
        //kaller på main funksjonen for å printe bilnr
        person1.main(args);
    }
}
