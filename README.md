# Bambu Handy Reverse-Engineering Sandbox

This repository collects notes, prototypes, and extracted binaries related to understanding the webcam streaming protocol used by Bambu Lab's "Bambu Handy" application.  It is intended for research and educational purposes.

## Repository layout

| Path | Description |
|------|-------------|
| [`PROTOCOL.md`](PROTOCOL.md) | Step-by-step notes on device discovery, establishing a DTLS-secured P2P session, streaming H.264 frames, and tearing down the connection. |
| [`example.py`](example.py) | Pure-Python proof-of-concept that discovers printers, opens an IOTC session, and writes raw H.264 video to disk. |
| [`AVAPIs.c`](AVAPIs.c) / [`IOTC.c`](IOTC.c) | Decompiled versions of the ThroughTek AV and IOTC Windows libraries exposing functions such as `avClientStart`, `avRecvFrameData2`, and `IOTC_Lan_Search2`. |
| [`AVAPIs.dll`](AVAPIs.dll), [`IOTCAPIs.dll`](IOTCAPIs.dll), [`AVAPIs.lib`](AVAPIs.lib), [`IOTCAPIs.lib`](IOTCAPIs.lib), [`libIOTCAPIsT.so`](libIOTCAPIsT.so) | Prebuilt binaries for the ThroughTek SDK. |
| [`Webcam/`](Webcam) | HTML documentation and DLLs for the AV/IOTC APIs including data structures and macros. |
| [`app/`](app) | Unpacked Android APK for "Bambu Handy" showing how the official app loads the native libraries via an obfuscated `StubApp` class. |
| [`build.gradle`](build.gradle), [`settings.gradle`](settings.gradle) | Gradle configuration files extracted from the Android project. |
| [`dll_strings.txt`](dll_strings.txt), [`ip address breakdown.txt`]("ip address breakdown.txt"), [`public ip list.txt`]("public ip list.txt") | Miscellaneous research notes on server addresses and decompiled strings. |

## Getting started

1. Read [`PROTOCOL.md`](PROTOCOL.md) for an overview of the network workflow.
2. Inspect [`example.py`](example.py) to see a Python reimplementation of the device discovery and streaming process.
3. Consult the decompiled sources (`AVAPIs.c`, `IOTC.c`) or the documents under [`Webcam/`](Webcam) for deeper details on the ThroughTek SDK.
4. Explore the Android project under [`app/`](app) if you are interested in reverse engineering the original mobile application.

## Next steps and ideas

- Add audio support or live playback to `example.py` using tools such as `ffmpeg` or `pyav`.
- Study the security implications of PSK handling and DTLS setup in the prototype.
- Compare the behavior of the decompiled native libraries against the official binaries to understand missing features or edge cases.

## Disclaimer

This project is a learning playground.  It is not affiliated with Bambu Lab, and nothing here should be considered production-ready.

