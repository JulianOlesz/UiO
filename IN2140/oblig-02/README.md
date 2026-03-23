Hvordan lese MFT fra disken:
- Man starter (normalt) med å lese rot directory, får inn id, navn og id-ene til entries. 
- Så leser man videre i et bestemt format, som er forskjellig for filer og for mapper. 
    - Filer kan allokere blokker, disse er gitt som "entries"
    - Mapper kan også ha egne entries, dette fortsetter rekursivt til det ikke finnes flere entries å lese. 
- Når alle noder er lest så settes pekere til riktige barne-noder (ved bruk av id-er)