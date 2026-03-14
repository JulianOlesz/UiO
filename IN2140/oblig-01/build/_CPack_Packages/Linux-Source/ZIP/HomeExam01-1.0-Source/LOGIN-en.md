# Logging in

It is no longer possible to log in
directly to login.ifi.uio.no.
It is instead required to use a so-called jumphost.
This jumphost is login.uio.no.

If you use ssh to login in from a command line (e.g. from Terminal), you can do this by writing:
```
ssh -J <your-username>@login.uio.no <your-username>@login.ifi.uio.no
```

At this moment, the documentation
([no](https://www.uio.no/tjenester/it/maskin/linux/hjelp/tips/login.html),
[en](https://www.uio.no/tjenester/it/maskin/linux/hjelp/tips/en/login.html))
is _not_ updated.
