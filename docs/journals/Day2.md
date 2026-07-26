# Day 2 Journal

## Section 1 — Design Challenges

### Design Challenge 1: Hashing Generic Types

While working on the Hash Map Design Proposal, I realized that the most difficult part of designing a generic Hash Map is not storing key-value pairs, but generating correct and consistent hash values for every possible key type.

### Design Challenge 2: Choosing a Hashing Strategy

I explored several possible approaches for generating hash values, including hashing object addresses and hashing raw memory, but discovered that both approaches have significant limitations.

### Design Challenge 3: Supporting User-Defined Types

While studying the STL, I learned how generic hash tables handle custom data types and what requirements should be placed on user-defined keys.

---

## Section 2 — Investigation and Understanding

Initially, I considered generating the hash value using the memory address of an object. After thinking about it more carefully, I realized this approach is incorrect because two different objects can store the same value while occupying different memory locations. Since equal keys must always produce the same hash value, hashing addresses cannot satisfy this requirement.

Next, I investigated hashing the raw bytes of an object. This also proved to be unreliable. Types such as `std::string` and `std::vector` internally contain pointers to dynamically allocated memory. Two strings containing identical text may store their data at different memory locations, causing their raw byte representations to differ even though the values are equal. I also learned that compiler-inserted padding and implementation-specific object layouts make raw memory hashing unsuitable for generic programming.

These observations made me realize that a generic library cannot automatically determine which member variables represent the logical identity of a user-defined object. Only the user understands which data members should participate in generating the hash value.

While reading about the C++ Standard Library, I found that `std::unordered_map` solves this problem by allowing users to provide custom hash functions for user-defined types. I also learned that custom key types should implement `operator==` because after multiple keys are placed into the same bucket, the hash table still needs a reliable way to determine whether two keys are actually equal.

I have not finalized the implementation yet because I am still studying **function objects (functors)** and **template specialization**. I want to understand how the STL designs its hashing mechanism before implementing my own version.

---

## Section 3 — Work Completed

**Work Completed**

- Completed the Hash Map Design Proposal.
- Investigated different strategies for hashing generic types.
- Identified the limitations of address-based hashing.
- Explored the problems with hashing raw object memory.
- Studied how `std::unordered_map` supports user-defined types.
- Began learning about function objects (functors) and template specialization.

---

## Section 4 — Learning Reflection

Today I learned that designing a generic Hash Map is much more challenging than implementing containers such as a Dynamic Array or Linked List. The primary challenge is creating a hashing mechanism that works correctly for a wide variety of data types while maintaining the fundamental requirement that equal keys always produce identical hash values.

I also learned why hashing memory addresses or raw object bytes is not a reliable solution. Objects can represent the same logical value while having different memory layouts, internal pointers, or padding bytes. This helped me better understand the difference between an object's **representation in memory** and its **logical value**.

Finally, I gained a better understanding of how the C++ Standard Library approaches generic programming. Instead of attempting to automatically hash every possible user-defined type, `std::unordered_map` allows users to supply custom hash functions and relies on `operator==` to compare keys within the same bucket. This design showed me how templates can provide flexibility while still supporting efficient implementations.