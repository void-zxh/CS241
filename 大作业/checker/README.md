# checker.cpp使用方法

* 输入

图文件`in.txt`，每行格式如下(二选一)

```
<(int)from, (int)to, (double)weight>
<(int)ver>
```

子图文件`output.txt`，每行一个子图的点集，不可重复或遗漏

* 报错

```cpp
"open file error" // 打开文件出错
"format error" // 输入格式出错
"double node" // 结点重复出现
"node don't exist" // 有遗漏的结点
```

* 输出

```
loss / total = $loss / $total
max subGraph size = $max_size
```

\$loss指损失边权和，\$total指原图边权和，\$max_size指子图最多结点个数