# Day 3 Journal

## Section 1 — Implementation Progress

### Task 1: Dynamic Array Implementation

After completing the Dynamic Array design proposal, I began implementing the container. Before writing the code, I spent time learning how to organize a multi-file C++ project using header files, header guards, and CMake.

### Task 2: Linked List Implementation

After finishing the Dynamic Array, I started implementing the Linked List. During this process, I learned how template classes should be organized across header and implementation files using `.tpp` files.

### Task 3: Project Structure

Once both data structures were implemented, I reorganized the project using a proper CMake directory structure to make the library easier to build and maintain.

---

## Section 2 — Implementation and Understanding

Before starting the implementation, I learned how a multi-file C++ project is organized. I understood the purpose of **header guards** in preventing multiple inclusions and learned how **CMake** simplifies building projects containing multiple source files.

While implementing the Dynamic Array, I completed the **Rule of Three**, `append()`, the resizing logic, and `operator[]`. During this process, I gained a better understanding of why the copy assignment operator returns a reference instead of `void`. Returning a reference allows assignment expressions to be chained and matches the behavior of built-in types.

I also learned why `operator[]` should return `T&` instead of `T`. Returning a reference allows elements to be modified directly using syntax such as:

```cpp
array[i] = value;
```

If the operator returned `T` by value, modifications would only affect a temporary copy rather than the actual element stored in the array.

While implementing the Linked List, I learned that template implementations are commonly placed inside a `.tpp` file and included at the end of the corresponding header file. This ensures that template definitions are visible to every translation unit that instantiates the template.

I also understood that constructing a `Node` using **placement new** automatically constructs its member of type `T`. There is no need to manually construct each member separately because the `Node` constructor takes care of constructing all of its data members.

During insertion and deletion, I carefully considered several edge cases, including inserting into an empty list and deleting the only node in the list. After analyzing these cases, I correctly updated both the `head` and `tail` pointers to maintain the integrity of the list.

---

## Section 3 — Work Completed

**Work Completed**

- Learned about multi-file C++ project organization.
- Learned the purpose of header guards.
- Set up the project using CMake.
- Implemented the Dynamic Array.
- Implemented the Rule of Three.
- Implemented `append()`, resizing logic, and `operator[]`.
- Started and completed the Linked List implementation.
- Organized template implementation using `.tpp` files.
- Reorganized the project using the CMake directory structure.
- Handled insertion and deletion edge cases correctly.

---

## Section 4 — Learning Reflection

Today I learned how multiple concepts in C++ work together when building a reusable library. Before today, I had mostly written programs in a single source file, but I now understand how header files, implementation files, header guards, template definitions, and CMake combine to create a well-structured project.

I also developed a deeper understanding of **references** in C++. Returning references from the copy assignment operator and `operator[]` is not simply a language convention—it allows objects to behave naturally, supports assignment chaining, and enables direct modification of stored elements without creating unnecessary copies.

Finally, I learned that implementing data structures requires careful handling of edge cases. Operations such as inserting into an empty list or deleting the last remaining node require updating both the `head` and `tail` pointers correctly. Thinking through these scenarios before writing the code helped me understand why robust data structure implementations must account for every possible state of the container.