# RollingHash

文字列に対するデータ構造です。

文字列の任意の部分文字列のハッシュを高速に求めることができます。

## get

```
ll rh.get(int l, int r)
```
文字列$S$の部分列$S[l, r)$のハッシュを求めます。
### 計算量
$O(1)$

## getrev

```
ll getrev(int l, int r)
```

文字列$S$の部分列$S[l, r)$を反転した後、ハッシュを求めます。

### 計算量
$O(1)$

## merge

```
ll merge(int l1, int r1, int l2, int r2)
```

文字列$S$の二つの部分文字列$S[l1, r1), S[l2, r2)$に対して、この順番で結合した文字列のハッシュを求めます。


### 計算量
$O(1)$

## lcp
```
int lcp(int i, int j)
```

二つの部分文字列$S[i, n), S[j, n)$のLCP(最長共通接頭辞の長さ)を求めます。

### 計算量
$O(\log N)$


# 使用例

https://atcoder.jp/contests/abc398/submissions/64122606
