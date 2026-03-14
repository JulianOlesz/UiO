# IN2140 vår 2026

## Oblig 1: Bli kjent med C (norsk)

For english, see [here](README-en.md).


I denne obligen skriver du dine egne funksjoner i en rekke små programmer for å bli bedre kjent med programmeringsspråket C. Du finner utdelingsarkene for denne oppgaven [her](oblig-01.tgz).

Oppgavene skal løses individuelt; man kan diskutere løsningsteknikker med andre studenter, men å dele
kode er ikke lov.
Se [retningslinjene](https://www.uio.no/studier/eksamen/obligatoriske-aktiviteter/mn-ifi-oblig.html)
for obligatoriske oppgaver og andre innleveringer ved Ifi.

Retterne vil teste innleveringer på Ifis Linuxmaskiner, tilgjengelige gjennom login.ifi.uio.no ([hvordan](LOGIN-no.md)).
Programmene dine må kompilere og kjøre på disse maskinene.
Dersom du lurer på noe om oppgavene, spør gruppelæreren din.

**Besvarelse leveres gjennom Devilry innen mandag 23. februar kl. 23.59.
Det er viktig at du leverer som beskrevet i bunnen av denne filen.**

### Oppgave 1: Vokalbytte

I denne oppgaven skal du fullføre et program som bytter ut alle vokalforekomster med en
annen bokstav i en setning.

Programmet tar to argumenter: én setning og én bokstav. Alle fem engelske vokaler i setningen, det vil si
‘a’, ‘e’, ‘i’, ‘o’ og ‘u’ skal byttes ut med bokstaven.
Skriv så ut den forandrede setningen til terminalen.

**Eksempel**
```
$ ./vowelshift "Lorem ipsum dolor sit amet" a
Laram apsam dalar sat amat
```

### Oppgave 2: Strengoperasjoner

Denne oppgaven handler om strenger og diverse strengoperasjoner. Du skal skrive funksjonene i
filen stringops-todo.c

Kodefeil i implementasjonen kan forårsake segmenteringsfeil i programmet. I så fall anbefaler vi at du
bruker Gdb og Valgrind for å finne ut hvor i programmet feilen oppstår.

(a) stringsum

Skriv funksjonen

```
int stringsum (char* s)
```

som tar en char-peker som argument og returnerer
en int-verdi som vi kaller strengsummen. Vi definerer
strengsummen som den akkumulerte verdien av alle
tegn i strengen, hvor verdien tilsvarer alfabetisk posisjon: ‘a’ har verdien 1, ‘b’ har verdien 2 og så videre.
Vi skiller ikke mellom små og store bokstaver. Mellomrom og den avsluttende nullbyten inngår ikke i
summen. Dersom strengen inneholder noen tegn som
ikke er en stor eller liten bokstav eller mellomrom,
så skal funksjonen returnere -1.

Det er flere måter å forenkle denne oppgaven på; det
kan være lurt å lage en enkel løsning før du forbedrer
den så den møter alle kriteriene i oppgaven.

Tips: En char er en énbytes tallverdi, som kan ha
verdier fra -128 til 127, og som oftest tolkes som en
bokstav ved hjelp av ASCII-tabellen. Dette kan man
utnytte for en effektiv løsning – ved å beregne tallverdiene som trenges for å løse oppgaven fra bokstavenes
ASCII-verdier.

(b) distance_between

Skriv funksjonen

```
int distance_between(char* s, char c)
```

som tar en char-peker og en char som argumenter og
returnerer avstanden (altså differansen mellom posisjonene) fra første til siste forekomst av tegnet i
strengen. Dersom tegnet forekommer kun én gang
så skal funksjonen returnere 0. Dersom tegnet ikke
forekommer, så skal funksjonen returnere -1.


(c) string_between

Skriv funksjonen

```
char* string_between(char* s, char c)
```

som tar en char-peker og en char som argumenter
og returnerer delstrengen som befinner seg mellom
første og siste forekomst av tegnet i strengen. Dersom
tegnet forekommer kun én gang, så skal funksjonen
returnere den tomme strengen. Dersom tegnet ikke
forekommer, så skal funksjonen returnere nullpekeren.

Dersom tegnet forekommer minst to ganger skal hverken
den første og heller ikke den siste forekomsten være
med i strengen du returnerer.

Her skal du IKKE allokkere en ny streng, men isteden skal du
forandre inputstrengen, og returnere peker til rett sted.


(d) stringsum2

Skriv funksjonen

```
int stringsum2(char* s, int* res)
```

som fungerer som stringssum, men istedenfor å returnere
strengsummen, legger den resultatet i int-en som res peker på.
Funksjonen returnerer 0 i alle tilfeller da stringsum
ville returnert et tall større enn 0 or -1 ellers.

### Oppgave 3: Marken i eplet

Du har en variabel apple som er definiert i filen [the_apple.c](the_apple.c).
Variablen apple er også deklarert i headerfilen [the_apple.h](the_apple.h).

Main-funksjonene til programmet ligger i filen apple-main.c.
Funksjonene nevnt nedenfor, som du bør implementere, skal være plassert i filen apple-todo.c

Det er bare én mark i eplet, men marken kan vokse
seg stor ved å duplisere sine bokstaver. Da ser den
kanskje slik ut:

```
"leappleappleappleappwwwwoooooooorrrrrr\n"
" rrmmmmmleappleappleappleappleappleap\n"
```

(a) Skriv funksjonen

```
int locateworm(char* apple)
```

som finner marken i eplet ved kun å bruke grunnleggende språkkonstruksjoner som if ... else, for,
while, do og så videre – altså ingen funksjoner som er ment for strengmanipulasjoner, som f.eks.
strcpy, strchr eller strstr.

Nærmere bestemt skal funksjonen returnere tallet
som er den (null-baserte) array-indeksen til den første bokstaven som
tilhører marken, eller -1 hvis marken ikke finnes.


(b) Skriv funksjonen

```
int removeworm(char* apple)
```
som skjærer ut marken av eplet ved å overskrive
den med mellomrom. Funksjonen returnerer markens
lengde (antallet bytes som ble erstattet med mellomrom) eller 0 hvis marken ikke finnes.

### Kompilering

For å kompilere programmene har vi laget en spesifikasjonsfil som heter CMakeLists.txt.
Disse filene leses av en softwarepakke med navn CMake, og den kan lage Makefiler på Linux.
Den kan også lage prosjektfiler for Visual Studio eller XCode, men for IN2140 skal dere bruke terminalvinduer og Makefiler.

Du kan nedlaste og kompilere dette prosjektet som følger:
- åpne en terminal
- i terminalen, pakk opp de utleverte filene:
```
  tar zxvf oblig-01.tgz
```
- gå inn i oblig-01-katalogen
```
cd oblig-01
```
- lag en underkatalog for å bygge programmene fra den utleverte kildekoden
```
mkdir build
```
- gå inn i build-katalogen
```
cd build
```
- bruk CMake til å lage en Makefile som passer din maskin
```
cmake ..
```
- kompilér for å lage eksekverbare filer fra kildekoden
```
make
```
- kjør programmene, f.eks.
```
./vowelshift "This is a text on the command line" u
```

Hvis du har behov til å installere CMake på:
| OS      | Metode  |
|---------|---------|
| MacOS   | Manual: Download from https://cmake.org/download/ |
| MacOS   | With Homebrew: brew install cmake |
| Linux   | Manual: Download from https://cmake.org/download/ |
| Linux   | using Apt: sudo apt-get install cmake |
| Linux   | using Snap: sudo snap install cmake |
| Windows | Manual: Download from Download from https://cmake.org/download/ |
| Windows | For Visual Studio integration see https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170 |

### Levering

Dere skal levere koden deres i [Devilry](https://devilry.ifi.uio.no/) som en arkiv-fil.
Arkiv-filen skal være en Zip-fil og må inneholde alle kildefiler og dokumentasjonsfiler.

Følger dere oppskriften for 'make' under [Kompilering](#Kompilering), kan dere lage arkiv-filen
ved å kalle
```
make package_source
```
Filen heter da `HomeExam01-1.0-Source.zip`.
