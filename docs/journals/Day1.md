# Day 1 Journal

## Section 1 — Design Decisions

### Design Decision 1: `get()` vs `operator[]`

While working on the Dynamic Array design proposal, I spent time deciding whether both `get()` and `operator[]` were necessary. Initially, I thought they served the same purpose since both access elements in the array.

### Design Decision 2: Dynamic Array Resizing

I also spent time deciding how the Dynamic Array should grow when it becomes full. I compared different resizing strategies before choosing the most suitable one.

### Design Decision 3: Memory Management with Templates

While writing the Linked List design proposal, I discovered a problem with using `malloc()` and `free()` together with template classes that may store non-trivial objects such as `std::string`.

---

## Section 2 — Investigation and Understanding

At first, I believed `get()` and `operator[]` were essentially identical because both return an element from the array. After reading about operator overloading, I learned that `operator[]` should return a reference so users can both read and modify elements using syntax such as:

```cpp
arr[i] = value;
```

I decided to keep `get()` as a separate function because it provides a safer interface that can perform bounds checking before returning an element.

While designing the resizing strategy, I compared increasing the capacity by **1.5×**, **2×**, and **2.5×**. After reading about amortized analysis, I understood why most dynamic array implementations double their capacity. Although doubling temporarily allocates more memory than smaller growth factors, it significantly reduces the number of reallocations and provides efficient amortized insertion performance.

During the Linked List design, I initially assumed that `malloc()` could safely allocate memory for every data type. After reading more about object construction, I realized that `malloc()` only allocates raw memory and does not invoke constructors. This becomes a problem for non-trivial types such as `std::string`, whose constructors must be executed before the object can be used safely.

I then learned how **placement new** constructs an object inside already allocated memory. I also learned that when memory is allocated using `malloc()`, destructors must be called explicitly before invoking `free()`, since `free()` only releases memory and does not destroy objects.

---

## Section 3 — Work Completed

**Work Completed**

- Created the GitHub repository for Project 1.
- Set up the initial project folder structure.
- Worked on the Dynamic Array design proposal.
- Finalized the design decision for `get()` and `operator[]`.
- Selected the Dynamic Array resizing strategy.
- Started the Linked List design proposal.
- Documented the memory management approach for template-based containers.

---

## Section 4 — Learning Reflection

Today I learned that **allocating memory** and **constructing an object** are two separate operations. Before today, I assumed that `malloc()` and `new` performed the same task. After studying object construction, I understood that `new` both allocates memory and calls the constructor, whereas `malloc()` only reserves raw memory. When working with non-trivial types such as `std::string`, constructors and destructors must be managed explicitly if raw memory allocation is used.

I also developed a better understanding of C++ operator overloading. Although `get()` and `operator[]` both provide element access, `operator[]` is designed to return a reference so that array elements can be modified naturally through indexing syntax, while `get()` can remain a safer alternative that performs bounds checking.

Finally, I learned why most Dynamic Array implementations **double their capacity** during resizing. Understanding amortized analysis helped me see that doubling provides a good balance between minimizing reallocations and maintaining reasonable memory usage, making insertion operations efficient over time.