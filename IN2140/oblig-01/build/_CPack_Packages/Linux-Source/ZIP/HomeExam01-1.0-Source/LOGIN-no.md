# Pålogging

Det er ikke lenger mulig å logge inn
direkte til login.ifi.uio.no.
Det kreves i stedet å bruke en såkalt jumphost.
Denne jumphosten er login.uio.no.

Hvis du bruker ssh til å logge inn fra en kommandolinje (f.eks. fra Terminal), kan du gjøre dette ved å skrive:
```
ssh -J <ditt-brukernavn>@login.uio.no <ditt-brukernavn>@login.ifi.uio.no
```

I dette øyeblikket, er dokumentasjonen
([no](https://www.uio.no/tjenester/it/maskin/linux/hjelp/tips/login.html),
[no](https://www.uio.no/tjenester/it/maskin/linux/hjelp/tips/en/login.html))
_ikke_ oppdatert.
