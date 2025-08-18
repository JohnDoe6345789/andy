# libIOTCAPIsT Library Overview

## Source Stub (`libIOTCAPIsT.c`)
`libIOTCAPIsT.c` is a generated placeholder that lists the library's entry points. Each function simply tail-calls itself, indicating that the real implementations live elsewhere (the shared object). For example:

```c
int64_t forEachNat()
{
    /* tailcall */
    return forEachNat();
}
```

This pattern is repeated for numerous networking and utility routines.

## Shared Library (`libIOTCAPIsT.so`)
`libIOTCAPIsT.so` is the compiled implementation used by the Android app. It is a 64-bit AArch64 ELF shared object and exports a large set of functions related to TUTK's P2P IoT connection framework, including NAT traversal, UDP/TCP connection tasks, and session management. Example exported symbols include:

- `AddUDPRelayConnectTask`
- `IOTC_Client_Connect_By_Nebula`
- `IOTC_Connect_ByUID`
- `IOTC_Connect_UDP`

These routines allow the application to establish and manage device connections over the TUTK platform.

## Usage
The Android application loads `libIOTCAPIsT.so` at runtime to perform networking operations. The stub C file can be used as a reference for available entry points or for building wrappers during analysis or reverse engineering.
