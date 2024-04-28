# Treap(Implicit Treap)

モノイドに対し使用できるデータ構造です。

Segment Treeのように使え、区間の途中に値を挿入したり、区間反転や区間rotateなどができます。

## size

```
int treap.size()
```
現時点でのサイズを返します。
### 計算量
$O(1)$

## insert

```
void insert(int k, S v)
```

k番目の位置にvを挿入します。

### 計算量
$O(\log N)$

## erase

```
void erase(int k)
```

k番目の位置の要素を削除します。

### 計算量
$O(\log N)$

## operator[]

```
S operator[](int k)
```

k番目の要素 $a[k]$を取得します。

### 計算量
$O(\log N)$

## prod
```
S prod(int l, int r)
```

$op(a[l], \dots ,a[r-1])$を、モノイドの性質を満たしていると仮定して計算します。

$l = r$のときは $e()$を返します。

### 計算量
$O(\log N)$

## reverse
```
void reverse(int l, int r)
```
$a[l], \dots , a[r-1]$を $a[r-1], \dots, a[l]$のように更新します。

### 計算量
$O(\log N)$


## rotate
```
void rotate(int l, int m, int r)
```

$a[l], \dots,a[m],\dots, a[r-1]$を
$a[m], \dots, a[r-1], a[l], \dots, a[m-1]$のように回転します。

### 計算量
$O(\log N)$


# 使用例

reverse
https://atcoder.jp/contests/abc350/submissions/52648986?lang=ja

rotate
https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=9122358#1

上限が大きいときのセグ木
https://atcoder.jp/contests/abc351/submissions/52891838
