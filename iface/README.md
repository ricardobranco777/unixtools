# iface

`Usage: iface [-4|-6] TARGET`

According to Richard W. Stevens's UNIX Network Programming Vol. 1 3rd Ed:

> Calling connect on a UDP socket does not send anything to that host;
> it is entirely a local operation that saves the peer's IP address and port.
> We also see that calling connect on an unbound UDP socket also assigns an
> ephemeral port to the socket.
> Unfortunately, this technique does not work on all implementations, mostly
> SVR4-derived kernels. For example, this does not work on Solaris 2.5, but it
> works on AIX, HP-UX 11, MacOS X, FreeBSD, Linux, and Solaris 2.6 and later."

Verified to work on Linux, FreeBSD, NetBSD, OpenBSD, DragonflyBSD, Illumos & MacOSX.
