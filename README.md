<div align="center">

# 🐚 Minishell

### *As beautiful as a shell*

[![42 School Project](https://img.shields.io/badge/42-Project-00babc?style=flat-square&logo=42)](https://42.fr)
[![Norminette](https://img.shields.io/badge/Norminette-passing-success?style=flat-square)](https://github.com/42School/norminette)
[![Language](https://img.shields.io/badge/Language-C-blue?style=flat-square&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))

</div>

---

## 📋 Description

Minishell is a minimal bash-like shell that handles basic command execution, pipes, redirections, and environment variables. This project provides a deeper understanding of processes and file descriptors.

> *"The existence of a shell is to launch commands. So let's create our own!"*

---

## ✨ Features

| Feature | Description |
|---------|-------------|
| 🎯 **Prompt** | Display a prompt and wait for user input |
| 📚 **History** | Command history navigation |
| ⚙️ **Execution** | Execute commands with absolute/relative paths or using PATH |
| 💬 **Quotes** | Handle single `'` and double `"` quotes |
| 📂 **Redirections** | `<` `>` `<<` `>>` |
| 🔄 **Pipes** | Connect commands with `\|` |
| 🌍 **Variables** | Environment variables (`$VAR`) and exit status (`$?`) |
| ⌨️ **Signals** | Handle `ctrl-C`, `ctrl-D`, and `ctrl-\` |

---

## 🛠️ Built-in Commands

```
┌─────────┬──────────────────────────────────┐
│ Command │ Description                      │
├─────────┼──────────────────────────────────┤
│ echo    │ Display text (with -n option)    │
│ cd      │ Change directory                 │
│ pwd     │ Print working directory          │
│ export  │ Set environment variable         │
│ unset   │ Unset environment variable       │
│ env     │ Display environment variables    │
│ exit    │ Exit the shell                   │
└─────────┴──────────────────────────────────┘
```

---

## 🚀 Installation

```bash
# Clone the repository
git clone https://github.com/pmoreira-og/42_Minishell.git

# Navigate to directory
cd 42_Minishell

# Compile
make
make val (to launch the program with valgrind)
make banner (to launch the program with valgrind and our custom banner)
make debug (to launch the program with valgrind and with debug mode ON)
```

---

## 💻 Usage

```bash
./minishell
```

### Example commands: 

```bash
minishell$ echo "Hello World"
Hello World

minishell$ ls -la | grep minishell
-rwxr-xr-x  1 user  staff  123456
