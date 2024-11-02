| Memory Location   | Description                           | Initial State                          | After Execution |
|-------------------|---------------------------------------|----------------------------------------|-----------------|
| **Caller Stack**  | Holds local variables `a`, `b`, and `result` | `a = 10`, `b = 5`, `result` uninitialized | `a = 5`, `b = 10`, `result = 1` if swapped |
| **Parameter `x`** | Pointer to `a` in caller's stack     | Holds address of `a` (`0x...F8`)       | Remains unchanged; points to `a` |
| **Parameter `y`** | Pointer to `b` in caller's stack     | Holds address of `b` (`0x...F0`)       | Remains unchanged; points to `b` |
| **Local `tmp`**   | Temporary `int64_t` storage for `*x` during swap | Uninitialized                        | Holds original value of `*x` (10) if `*x > *y`, otherwise unused |
| **Dereferenced `*x`** | Value pointed to by `x` (initially `a`) | `*x = 10`                             | `*x = 5` after swap if `*x > *y` |
| **Dereferenced `*y`** | Value pointed to by `y` (initially `b`) | `*y = 5`                              | `*y = 10` after swap if `*x > *y` |
| **Return Value**  | Result of the function call          | None                                   | `1` if swap occurred, `0` if `*x == *y`, `-1` if `*x != *y` |
| **Stack Frame**   | Deallocated upon function exit       | Created upon function entry            | Deallocated on function exit      |

