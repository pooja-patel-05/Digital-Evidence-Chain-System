# Digital Evidence Chain System

A menu-driven C++ application for registering digital evidence, tracking its
chain of custody, checking file integrity, authenticating users, and recording
audit activity.

## Architecture

The project follows a layered design:

```text
Entity classes
      |
Managers
      |
main.cpp
```

- Entity classes represent evidence, custody records, and users.
- Manager classes contain persistence and business logic.
- `main.cpp` contains only the console menu and user interaction.

## Features

- Role-based login for Admin, Officer, and LabStaff
- Add, list, and search evidence records
- Generate file hashes using `std::hash<std::string>`
- Transfer evidence and view custody history
- Verify whether an evidence file has changed
- Record and view audit activity
- Save records in text files under `data/`
- Store all uploaded or automatically created evidence files under `evidence_files/`

## Run on Windows

The easiest method is to double-click:

```text
run.bat
```

The script automatically:

1. Opens the project directory.
2. Compiles all C++ source files.
3. Creates `DigitalEvidenceChain.exe`.
4. Starts the application.

Make sure the MinGW `g++` compiler is installed and available in your system
`PATH`. Close any running copy of the application before using `run.bat` again.

## Manual build

Run this command from the project root:

```powershell
g++ -std=c++11 -Wall -Wextra -Wpedantic -Iinclude src/main.cpp src/Evidence.cpp src/CustodyRecord.cpp src/EvidenceManager.cpp src/CustodyManager.cpp src/HashManager.cpp src/AuditManager.cpp src/User.cpp -o DigitalEvidenceChain.exe
```

Then start the program:

```powershell
.\DigitalEvidenceChain.exe
```

## Sample accounts

| Username | Password | Role |
|---|---:|---|
| admin | 1234 | Admin |
| officer1 | 1111 | Officer |
| lab1 | 2222 | LabStaff |

## Role permissions

- Admin: all operations, including viewing audit logs
- Officer: evidence and custody operations
- LabStaff: view, search, transfer, history, and integrity verification

## Data format

`evidence.txt`:

```text
evidenceId,fileName,uploadedBy,uploadDate,hashValue
```

`custody.txt`:

```text
evidenceId,fromPerson,toPerson,transferDate
```

`users.txt`:

```text
username,password,role
```

## Version note

Version 1.0 uses `std::hash<std::string>` as requested. It is suitable for a
classroom demonstration, but not for real forensic integrity. A later version
should use SHA-256 and securely hashed user passwords.
