
## Features

- Real-time monitoring of CPU usage and memory usage.
- Console output is updated every second without printing new lines.
- Uses Windows API to fetch CPU times and memory statistics.
- Compatible with Windows operating systems.

## Requirements

- Windows operating system
- A C compiler that supports Windows API (e.g., Microsoft Visual Studio)

## How to Compile and Run

### 1. Clone the Repository

First, clone this repository to your local machine:

```bash
git clone https://github.com/your-username/system-resource-monitor.git
cd system-resource-monitor
```

### 2. Compile the Program

You need a C compiler that supports the Windows API. Here's how to compile the program:

#### Using GCC (MinGW or Cygwin):

```bash
gcc -o monitor monitor.c -lgdi32
```

#### Using Microsoft Visual Studio:

1. Open the project in Visual Studio.
2. Build the project by selecting `Build` > `Build Solution` from the menu.

This will create an executable file `monitor.exe` in the project directory.

### 3. Run the Program

Once compiled, run the program in your terminal:

#### Windows Command Prompt or PowerShell:

```bash
monitor.exe
```

#### Output:

The program will start displaying real-time CPU and memory usage in the following format:

```
Real-Time System Resource Monitor (Windows)
-------------------------------------------
| CPU Usage  | Memory Usage |
-------------------------------------------
| 45.23%     | 56.78%       |
-------------------------------------------
```

The values will refresh every second, and the console output will be updated in place without adding new lines.

## How It Works

- **CPU Usage**: The program calculates CPU usage by comparing the system's idle, kernel, and user times.
- **Memory Usage**: It calculates memory usage based on total and available physical memory.
- **Console Output**: The data is printed on the same line to avoid clutter, and the line is updated every second.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contributions

Feel free to open issues or submit pull requests if you'd like to contribute to the project.

---

**Note**: This project is designed to run on Windows. It uses Windows-specific API functions, so it may not work on other operating systems.
```

