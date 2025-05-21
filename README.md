# Silicon Valley Bitcoin Alert
<img src="gilfoyle.jpg" title="Silicon Valley Bitcoin Alert">
<img src="Solution.png" title="Expected">


# Gilfoyle-Bitcoin-Alert : <small>Bitcoin is Really Volatile Today</small>

This programme monitors the price of Bitcoin and issues a sound alert when a new All-Time High (ATH) is reached, or if the price falls below a predefined threshold.

## API: CoinMarketCap
The programme uses the CoinMarketCap API to retrieve the current price of Bitcoin. An API key from CoinMarketCap is required, which you can obtain at [CoinMarketCap API](https://coinmarketcap.com/api/documentation/v1/#).

**Note**: If the programme does not execute correctly, try replacing the API key in the source code with your own API key.

## Features
<ul>
  <li>If Bitcoin reaches a new ATH, the programme will play a sound alert using an audio file (by default, a `.wav` file from Napalm Death).</li>
  <li>If Bitcoin’s price drops below a specified threshold, it also triggers an alert.</li>
  <li>The price is fetched in real-time from the CoinMarketCap API.</li>
  <li>The default currency is USD, but this can be modified in the source code as desired.</li>
  <li>The programme checks the Bitcoin price every minute to provide frequent updates.</li>
</ul>

## Requirements and Installation
This programme is designed to work on Windows, macOS, and Linux.

### Installation
1. Ensure `curl` is installed on your system, as the programme uses it to make HTTP requests.
2. Clone this repository.
3. Compile and run the `Alert.c` file.

## Compiling and Running

This program uses platform-specific features for playing sound.

### Dependencies
- **Windows:** No special dependencies beyond a C compiler (e.g., MinGW or MSVC).
- **macOS:** Requires `afplay` (standard macOS utility).
- **Linux:** Requires `aplay` (part of ALSA utils, usually available, e.g., `sudo apt-get install alsa-utils` on Debian/Ubuntu).

### Compilation
You can compile `Alert.c` using a standard C compiler like GCC:
```bash
gcc Alert.c -o alert 
```
On Windows, if you are using MinGW, you might need to link against the multimedia library:
```bash
gcc Alert.c -o alert.exe -lwinmm
```

### Running the Program
**Important:** The sound file `You-Suffer.wav` must be in the same directory as the compiled `alert` (or `alert.exe`) executable when you run it.

To run the program:
```bash
./alert
```
Or on Windows:
```bash
alert.exe
```

The program will fetch the Bitcoin price every 60 seconds. If the price surpasses the previously recorded highest price (initially $66767), it will play the `You-Suffer.wav` sound.
Error messages will be printed to the console if the sound file cannot be played.
