
# multithreaded-httpserver

This project is a high-performance, multithreaded HTTP server written in C. It leverages Pthreads for concurrent processing and a thread pool architecture to handle multiple client requests simultaneously while maintaining data integrity and atomic logging.

## Features

- **Thread Pool Design**: Implements a fixed-size thread pool consisting of worker threads and a dispatcher thread. The dispatcher accepts incoming client connections and assigns them to idle worker threads.
- **Concurrency and Synchronization**: Efficiently manages concurrent access to shared resources using mutexes, condition variables, and a thread-safe queue, ensuring atomicity and linearizability.
- **Audit Log**: Maintains a log of client requests, detailing the operation, URI, HTTP status code, and an optional `RequestID` header, if provided by the client.
- **Support for HTTP Methods**: Supports `GET` and `PUT` HTTP methods to retrieve and store resources.
- **Configurable Thread Pool Size**: Allows the number of worker threads to be specified through command-line arguments, enabling control over concurrency levels.
- **Graceful Shutdown**: Ensures a clean shutdown with signal handling to preserve log durability.

## File Overview

- **httpserver.c**: Main file for the HTTP server implementation. Contains the logic for handling incoming requests, spawning and managing threads, and coordinating between the dispatcher and worker threads.
- **queue.c / queue.h**: Implements a thread-safe queue for managing client requests. The dispatcher thread enqueues requests, and worker threads dequeue them for processing.
- **cacher.c / cacher.h**: Manages in-memory caching of resources. Provides functionality to retrieve and store files in a cache, optimizing access times for frequently requested resources.
- **log.c / log.h**: Contains functions to generate and manage the audit log, ensuring atomic logging for each request. The log is written to `stderr` in a specific format to maintain coherence across client interactions.
- **Makefile**: Defines build rules for compiling the HTTP server, creating the executable `httpserver`, and cleaning up generated files. It uses `clang` with flags for strict error handling.
- **README.md**: This file, documenting the project’s structure, features, usage, and development setup.
- **LICENSE**: MIT License file, detailing the terms under which the project can be used, modified, and distributed.

## Installation

1. Clone the repository and navigate to the project directory:
   ```bash
   git clone <repository-url>
   cd multithreaded-httpserver
   ```

2. Build the server with:
   ```bash
   make
   ```

This will generate an executable named `httpserver`.

## Usage

To start the HTTP server, use:

```bash
./httpserver [-t threads] <port>
```

- **port**: The port number the server listens on.
- **-t threads**: Optional argument specifying the number of worker threads. Defaults to 4 if not specified.

### Example

To start the server on port `8080` with `8` worker threads:

```bash
./httpserver -t 8 8080
```

## Audit Log Format

The server generates an audit log in `stderr` for each request processed, formatted as:

```
<Operation>,<URI>,<Status-Code>,<RequestID>
```

- **Operation**: HTTP method used (GET or PUT).
- **URI**: Resource requested.
- **Status-Code**: HTTP status code (e.g., 200, 404).
- **RequestID**: Optional HTTP header value (or `0` if absent).

### Sample Log Output

Example log output for a sequence of requests:

```
GET,/a.txt,200,1
GET,/b.txt,404,2
PUT,/b.txt,201,3
GET,/b.txt,200,0
```

## Implementation Details

1. **Dispatcher Thread**: Acts as the main server loop, accepting incoming client connections and enqueuing requests in the thread-safe queue.
2. **Worker Threads**: Each worker thread waits for requests in the queue, processes them, and then logs the result. Idle worker threads sleep until notified by the dispatcher.
3. **Synchronization**: Uses `pthread` mutexes and condition variables to ensure safe access to shared resources, following atomicity and linearizability requirements.
4. **Request Processing**:
   - **GET**: Retrieves a file if it exists (200) or returns a 404 error.
   - **PUT**: Stores or updates a file and returns a 201 status on success.

## Testing

A set of test scripts is provided to verify the server's functionality, concurrency management, and logging. Use them to ensure the server's behavior meets the expected standards under various scenarios.

### Sample Scenarios

1. **Concurrent GET Requests**: Verifies that different files can be accessed concurrently.
2. **GET and PUT Conflicts**: Ensures consistent logging and file access when requests for the same file occur simultaneously.

## Cleanup

To remove all compiled binaries and clean up the directory:

```bash
make clean
```

## 
_This README is a part of the multithreaded-httpserver Project by Rajat Maheshwari._

