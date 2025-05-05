コンテスト中は↓を使いましょう、自分の実装は遅いです

https://lorent-kyopro.hatenablog.com/entry/2021/03/12/025644

# dynamic_segtree

モノイドに対し使用できるデータ構造です。

Segment Treeのように使え、キーの上限を1e9オーダーにできます。

## set

```
void set(size_t p, S x)
```
p番目の位置をxに変更します。

### 計算量
$O(\log N)$

## get
```
S get(size_t p)
```
p番目の位置の値を返します。

### 計算量
$O(\log N)$

## prod
```
S prod(size_t l, size_t r)
```
$op(a[l], a[l+1], \dots, a[r-1])$を、モノイドの性質を満たしていると仮定して計算します。
l = rのときは単位元を返します。

### 計算量
$O(\log N)$

## 使用例
- https://atcoder.jp/contests/abc403/submissions/65522198
