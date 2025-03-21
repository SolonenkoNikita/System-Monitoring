# PROCESS MONITORING SYSTEM

## OVERVIEW

The **Process Monitoring System** is a powerful tool designed to provide detailed insights into system processes on Unix-like operating systems. It offers comprehensive information about running processes, including memory usage, CPU utilization, and other critical metrics. This system is ideal for system administrators and developers who need to monitor and analyze process behavior in real-time.

## FEATURES

- **Real-Time Process Monitoring**: Track active processes with up-to-date information.
- **Detailed Metrics**: View memory usage, CPU utilization, process priority, and more.
- **User-Friendly Interface**: Navigate through processes using an intuitive terminal-based interface.
- **Cross-Platform Compatibility**: Designed for Unix-like systems, ensuring broad compatibility.

## INSTALLATION

### PREREQUISITES

Before building and running the project, ensure you have the following dependencies installed:

1. **`<curses.h>`**: A library for terminal handling and text-based user interfaces.
2. **`<fmt/core.h>`**: A modern formatting library for C++.

To install these dependencies on a Debian-based system (e.g., Ubuntu), run:

```bash
sudo apt-get install libncurses-dev libfmt-dev
