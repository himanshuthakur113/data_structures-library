# Day 6 Journal

## Section 1 — Design and Testing Progress

### Task 1: RedisLite Design Proposal

I started by designing the **RedisLite** project. Before writing any code, I spent time understanding how Redis works internally and how I could build a simplified version using my own data structure library. Creating the design proposal helped me identify the major components of the project and gave me a clear implementation roadmap.

### Task 2: Hash Function Improvements

While working on the design, I also explored several C++ concepts that would improve my hash function implementation, particularly type casting and writing portable hashing code.

### Task 3: Google Test Integration

After finishing the design work, I integrated Google Test into the project and configured the build system to support automated unit testing.

### Task 4: Building the Test Suite

The remainder of the day was spent writing comprehensive unit tests for `DynamicArray` and `LinkedList`, fixing bugs that the tests revealed, and improving the implementation.

---

## Section 2 — Investigation and Understanding

While designing RedisLite, I spent time learning how Redis stores and retrieves data efficiently using a hash table. This helped me understand how my existing data structure library could be reused instead of writing everything from scratch.

While studying the hashing implementation, I learned the difference between `reinterpret_cast` and `static_cast`. I discovered that `reinterpret_cast` does not modify the underlying bits stored in memory; it simply tells the compiler to interpret those bits as another type. In contrast, `static_cast` performs an actual value conversion, meaning the resulting bit representation may change.

I also learned more about `size_t`. I found that its size depends on the target architecture—32 bits on a 32-bit system and 64 bits on a 64-bit system. Since a `double` occupies 64 bits, I first converted it into a `uint64_t` before hashing it. However, I realized that directly returning this value as a `size_t` on a 32-bit system would discard the upper 32 bits. To make the hash function portable, I added a helper function that folds the upper half into the lower half using an XOR operation whenever `sizeof(uint64_t)` and `sizeof(size_t)` are different.

Next, I integrated Google Test into the project. I initially experimented with CMake's `FetchContent`, but eventually switched to using the system-installed version through `find_package(GTest REQUIRED)` because it fit my development environment better. I also created a separate `unit_tests` executable, enabled CTest, and configured automatic test discovery.

While writing tests for `DynamicArray::insert()`, I spent some time thinking about why `insert(size(), value)` is valid while `get(size())` is not. After working through several examples, I understood that `insert()` inserts **before** a given position, so inserting at `size()` simply appends a new element after the last existing one. In contrast, `get()` and `operator[]` access existing elements, so `size()` is already outside the valid range.

To make unit testing possible, I replaced all `exit()` calls in both `DynamicArray` and `LinkedList` with `std::out_of_range` exceptions. This allowed Google Test to verify error conditions using `EXPECT_THROW` instead of terminating the test program.

While expanding the DynamicArray test suite, I began testing with `std::string` in addition to `int`. This exposed a bug in `insert()`. The implementation was assigning into memory that had been allocated but never constructed. The issue remained hidden when storing primitive types but immediately appeared when storing objects like `std::string`. I fixed the bug by constructing the new object with placement `new` before shifting the existing elements and kept the test as a regression test for future development.

I also noticed that both `append()` and `insert()` contained duplicate resizing logic, so I refactored the code by moving the resizing implementation into a private `grow()` helper function.

Later, while completing the LinkedList test suite, I found that `insert()` failed to reject negative indices. Calling `insert(-1, value)` incorrectly inserted an element instead of throwing an exception. I fixed the bounds checking logic to validate both negative indices and indices larger than the list size.

Finally, I discovered that my iterator only implemented `operator!=`. Because of this, using `EXPECT_EQ` on iterators resulted in a compilation error. Rather than modifying the tests, I implemented `operator==`, making the iterator interface more complete and compatible with standard testing patterns.

---

## Section 3 — Memory Diagram

### Portable Hashing for `double`

```text
double
   │
reinterpret_cast
   │
uint64_t
   │
   ├── 64-bit system
   │       │
   │       ▼
   │    size_t (64 bits)
   │
   └── 32-bit system
           │
           ▼
Upper 32 bits XOR Lower 32 bits
           │
           ▼
     size_t (32 bits)
```

This ensures that information from both halves of the original 64-bit value contributes to the final hash on both 32-bit and 64-bit systems.

---

### DynamicArray::insert()

**Incorrect implementation**

```text
Raw Memory
    │
Assignment
    │
❌ Object never constructed
```

**Correct implementation**

```text
Raw Memory
    │
placement new
    │
Constructed Object
    │
Shift Elements
    │
Insert New Value
```

---

### DynamicArray Growth

```text
Old Array
│
├── Element
├── Element
└── Element

        │
        ▼

Allocate Larger Array
        │
Construct New Objects
        │
Copy Existing Elements
        │
Destroy Old Objects
        │
Free Old Memory
```

---

## Section 4 — Work Completed

**Work Completed**

- Completed the RedisLite design proposal.
- Learned how Redis stores data internally.
- Studied `reinterpret_cast` and `static_cast`.
- Improved the portability of the `double` hash function.
- Integrated Google Test using `find_package(GTest REQUIRED)`.
- Configured CTest and automatic test discovery.
- Created a separate `unit_tests` executable.
- Wrote comprehensive unit tests for `DynamicArray`.
- Replaced `exit()` with `std::out_of_range` exceptions.
- Fixed the `DynamicArray::insert()` object lifetime bug.
- Refactored duplicate resizing code into `grow()`.
- Completed the `LinkedList` test suite.
- Fixed bounds checking for negative indices.
- Added `operator==` to the iterator.
- Corrected an incorrect test case.
- Successfully passed **135 Google Test cases** across **21 test files**.

---

## Section 5 — Learning Reflection

Today made me realize how valuable unit testing is. While writing the tests, I wasn't just checking whether my code worked—I was also finding bugs that I probably wouldn't have discovered during normal usage. Testing with `std::string` instead of only `int` exposed an object lifetime bug that had been hidden for a long time. It showed me that testing with different types is just as important as testing different inputs.

I also understood why exceptions are preferred over terminating the program when building a reusable library. Replacing `exit()` with exceptions made the library much easier to test and also gave users of the library more control over how they want to handle errors.

Another interesting thing I learned was that writing tests often helps clarify the expected behavior of a function. The confusion I had about `insert(size(), value)` and `get(size())` disappeared once I thought about what each function is actually supposed to do. In a way, writing the tests improved my understanding of the interface as much as it verified the implementation.

Finally, today reinforced the idea that good software isn't finished when the implementation works—it becomes reliable when it has a strong set of tests behind it. By the end of the day, having all 135 tests pass gave me much more confidence that the data structures behave correctly, even in edge cases that are easy to overlook during development.