#include <stdio.h>

enum coordinate_type { RECTANGULAR = 1, POLAR };

int main(void)
{
	int RECTANGULAR;
	printf("%d %d\n", RECTANGULAR, POLAR);
	return 0;
}

/*好问题，这正好戳到 **C 语言里“名字空间（namespace）”** 的核心点了 👀
而且你这个例子非常经典，很多人第一次都会懵。

我们一步一步来。

---

## 先看代码里出现了几个“RECTANGULAR”

```c
enum coordinate_type { RECTANGULAR = 1, POLAR };
```

这里定义了一个 **枚举常量**：

* `RECTANGULAR`：枚举常量（本质是一个 `int` 常量）
* `POLAR`：枚举常量

---

```c
int RECTANGULAR;
```

这里又定义了一个 **普通变量**：

* `RECTANGULAR`：一个 `int` 类型的变量

---

## 关键点：C 语言有「不同的名字空间」

在 **C（不是 C++）** 里，标识符并不是全都在同一个池子里。

### C 里主要有这些名字空间（简化版）：

1. **普通标识符名字空间**

   * 变量名
   * 函数名
   * 枚举常量名（⚠️注意：枚举常量在这里）
2. **标签名字空间**

   * `struct/union/enum` 后面的名字
3. **成员名字空间**

   * `struct` / `union` 的成员

👉 **枚举常量 和 普通变量在同一个名字空间！**

所以这点非常重要：

> **`enum` 里的 `RECTANGULAR` 和 `int RECTANGULAR;` 是同一个名字空间**

---

## 那编译期是怎么判断的？

### 在这一行：

```c
printf("%d %d\n", RECTANGULAR, POLAR);
```

编译器做的事情大致是：

1. **当前作用域查找 `RECTANGULAR`**
2. 发现：

   ```c
   int RECTANGULAR;
   ```

   ——有一个**局部变量**
3. 根据 **作用域规则**：

   * 局部变量 **优先级高于** 外层定义
4. 所以：

   ```c
   RECTANGULAR → int RECTANGULAR;   // 变量
   ```

而：

```c
POLAR
```

在 `main` 里 **没有同名变量**，于是：

* 向外查找
* 找到枚举常量 `POLAR`

---

## 编译器最终的解析结果

等价于你脑子里这样理解：

```c
printf("%d %d\n", /*未初始化的变量*/ /*RECTANGULAR,*/
                  /*枚举常量*/ /*POLAR);*//*
```

⚠️ **注意一个坑**
`int RECTANGULAR;` 没初始化 → 使用它是 **未定义行为（UB）**。

---

## 如果你把变量名改一下会更清楚

```c
int r;
printf("%d %d\n", r, RECTANGULAR);
```

此时：

* `r` → 局部变量
* `RECTANGULAR` → 枚举常量

---

## 那如果我“就想”用枚举常量怎么办？

在 **C 里没办法显式区分**（不像 C++ 的 `Enum::Value`）。

👉 解决方式只有两个：

### ✅ 1. 不要起同名变量（最常见、也是推荐的）

```c
enum coordinate_type { COORD_RECTANGULAR = 1, COORD_POLAR };
```

### ✅ 2. 利用作用域（不在同一个块里）

```c
enum coordinate_type { RECTANGULAR = 1, POLAR };

void f(void) {
    printf("%d\n", RECTANGULAR); // 枚举常量
}

int main(void) {
    int RECTANGULAR;
}
```

---

## 一句话总结（很重要）

> **编译期判断规则是：**
>
> * 枚举常量和变量在同一个名字空间
> * **就近作用域优先**
> * 局部变量会“遮蔽（shadow）”枚举常量

如果你愿意，我可以帮你 **对比 C vs C++ 在 enum 这里的差异**，或者画一张「名字空间 + 作用域」的小图，理解会更牢 😄
*/