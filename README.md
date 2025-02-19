# AutO-RekO {Currently in development}

```
     _        _____           ____      _     ___  
    / \  _   |_   _|__       |  _ \ ___| | __/ _ \ 
   / _ \| | | || |/ _ \ _____| |_) / _ \ |/ / | | |
  / ___ \ |_| || | (_) |_____|  _ <  __/   <| |_| |
 /_/   \_\__,_||_|\___/      |_| \_\___|_|\_\\___/ 
                                                  
```

**AutO-RekO** is an automatic enumeration tool designed to accelerate and optimize the reconnaissance phase during penetration tests.

---

## ⚙️ Development Status {Currently in development}

AutO-RekO is currently under development and will be available soon. Stay tuned for updates!

---

## ✨ Features

- **Automated Enumeration:** Efficient and quick reconnaissance.
- **Customizable Workflows:** Adapt to your specific testing needs.
- **Multi-Platform Support:** Seamless operation across environments.

---

## 🚀 Usage

### Quick Start

To get started with **AutO-RekO**, simply run it without any options:

```bash
./autoreko  #Without make install
autoreko
```

When executed without options, AutO-RekO will guide you step by step, asking for the necessary parameters like the target, scan intensity, and output preferences.

### Advanced Usage

For those who prefer specifying options directly, here are some examples:

#### Basic Enumeration

Run a standard enumeration with the following command:

```bash
autoreko -t <target_ip> -i <intensity_level> -o <output_file>
```

- `-t` specifies the target IP address (IPv4 or IPv6).
- `-i` specifies the intensity level of the scan, ranging from 1 (low) to 4 (high). Note: Intensity levels 2, 3, and 4 require `root` privileges.
- `-u` specifies a target URL for enumeration.
- `-o` specifies the output file (e.g., `results.txt`) where the scan results will be saved.
- `-w` specifies a wordlist file to use for fuzzing operations, such as Gobuster-style brute-forcing.

#### Additional Options

Explore more capabilities:

```bash
autoreko -h
```

#### Example Usage

Save results to a text file with detailed logging enabled:

```bash
autoreko -t 192.168.1.1 -i 3 -o /home/results.txt 
```

Alternatively, specify a URL:

```bash
autoreko -u https://example.com -i 2 
```

Use a custom wordlist for fuzzing:

```bash
autoreko -u https://example.com -i 2 -w /path/to/wordlist.txt
```

---

## 👥 Authors

This project is developed and maintained by:

- **@Rattus**
- **@BrB93** 

Feel free to reach out for suggestions, bug reports, or contributions!


![Logo](logo.svg)
