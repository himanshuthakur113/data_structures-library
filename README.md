# Data Structures Library

A header-only C++20 library of core data structures, written from scratch with manual memory management and no use of the STL containers. It also includes **RedisLite**, a small in-memory key-value store built on top of the library.

This is **Stage 1** of a larger project: build a search engine from the ground up.

```
Data Structures Library  ->  Web Crawler + Indexer  ->  Search Engine
      (this repo)                  (next)                  (later)
```

## What's inside

| Structure | Header | Notes |
|---|---|---|
| `DA<T>` (Dynamic Array) | `include/dynamic_array.h` | Growable array, `shrink()`, `clear()`, const and non-const `operator[]` |
| `LinkedList<T>` | `include/linked_list.h` | Singly linked list with iterators, `find`, insert/delete at front, back or index |
| `HashMap<K, V, H>` | `include/hash_map.h` | Separate chaining, automatic rehashing, custom hash functor, `keys()` |
| `queue<T>` | `include/queue.h` | FIFO queue built on `LinkedList` |
| `RedisLite` | `include/redis_lite.h` | Command-line key-value store built on `HashMap` |

All containers follow the Rule of Three (copy constructor, copy assignment, destructor) and are checked with Valgrind.

## RedisLite

A REPL that stores string keys and values in the library's own `HashMap`. Commands are case-insensitive.

| Command | Description |
|---|---|
| `SET key value` | Store a value |
| `GET key` | Read a value |
| `DEL key` | Delete a key (`1` if removed, `0` if it did not exist) |
| `EXISTS key` | `1` if the key exists, otherwise `0` |
| `COUNT` | Number of stored keys |
| `CLEAR` | Remove everything |
| `EXIT` | Quit |

```
Enter the command:
>SET name Himanshu
Ok
Enter the command:
>GET name
Himanshu
```

## HashMap with your own types

Keys of any type work if they define `operator==`. For types where the default hash is not suitable, pass your own hash functor:

```cpp
struct Point {
    int x, y;
    bool operator==(const Point& o) const { return x == o.x && y == o.y; }
};

struct PointHash {
    size_t operator()(const Point& p) const { return p.x * 31 + p.y; }
};

HashMap<Point, std::string, PointHash> map;
map.insert({1, 2}, "A");
```

## Build and test

Requirements: a C++20 compiler, CMake 3.15+, GoogleTest, and optionally Valgrind.

```bash
# Fedora
sudo dnf install gcc-c++ cmake gtest-devel valgrind
# Ubuntu / Debian
sudo apt install g++ cmake libgtest-dev valgrind
```

```bash
cmake -S . -B build
cmake --build build
./build/unit_tests      # run all unit tests
./build/ds              # start RedisLite
cmake --build build --target valgrind   # run tests under Valgrind
```

## Using it in another project

The library is header-only, so you can pull it in with CMake `FetchContent`. Tests and the demo are only built when this is the top-level project, so GoogleTest is not needed by the consumer.

```cmake
include(FetchContent)
FetchContent_Declare(dslib
    GIT_REPOSITORY https://github.com/himanshuthakur113/data_structures-library.git
    GIT_TAG main)
FetchContent_MakeAvailable(dslib)

target_link_libraries(my_app PRIVATE DataStructuresLibrary)
```

## Project layout

```
include/   public headers
src/       template implementations (.tpp) and redis_lite.cpp
test/      Google Test suites for each structure
docs/      design proposals, memory diagrams, build logs and daily journals
```

## Documentation

The `docs/` folder records how the project was designed and built:

- `docs/design/` - design proposals and memory diagrams for each structure
- `docs/build_logs/` and `docs/journals/` - what was built and learned each day

## Roadmap

- [x] Dynamic Array, Linked List, Hash Map, Queue
- [x] RedisLite v1
- [ ] Web crawler and indexer, using this library for the frontier, seen set and page store
- [ ] Search engine
