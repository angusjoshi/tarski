package main

import "fmt"

var f func([]int) []int
var x []int
var y []int
var a []int
var b []int
var s []int
var u []int
var d []int


func allCoordinatesMatch(a []int, b []int, predicate func(int, int) bool) bool {
  for i := 0; i < len(a) && i < len(b); i++ {
    if !predicate(a[i], b[i]) {
      return false;
    }
  }
  return true;
}

func anyCoordinatesMatch(a []int, b []int, predicate func(int, int) bool) bool {
  for i := 0; i < len(a) && i < len(b); i++ {
    if predicate(a[i], b[i]) {
      return true;
    }
  }
  return false;
}

func latticeLe(a []int, b []int) bool {
  return allCoordinatesMatch(a, b, func(a int, b int) bool { return a <= b })
} 

func latticeEq(a []int, b []int) bool {
  return allCoordinatesMatch(a, b, func(a int, b int) bool { return a == b })
}

func solveWhenPMapsOutside(p []int) []int {
  if p[0] == b[0] && p[0] < f(p)[0] {
    if latticeEq(d, b) || d[1] == b[1] {
      // VOP
    }
    if d[0] > f(d)[0] {
      // VOP
    }
    return d
  }

  if p[1] == b[1] && p[1] < f(p)[1] {
    if latticeEq(d, b) || d[0] == b[0] {
      // VOP
    }
    if d[1] > f(d)[1] {
      // VOP
    }
    return d
  }

  if p[0] == a[0] && p[0] < f(p)[0] {
    if latticeEq(a, u) || d[1] == b[1] {
      // VOP
    }
    if d[0] > f(d)[0] {
      // VOP
    }
    return d
  }

	return []int{}
}

func innerAlgorithm() []int {
	copy(a, x)
	copy(b, y)
	a[2] = s[2]
	b[2] = s[2]
  u, d = a, b

	bot := []int{(a[0] + b[0]) / 2, a[1], s[2]}
	left := []int{a[0], (a[1] + b[1]) / 2, s[2]}
	top := []int{(a[0] + b[0]) / 2, b[1], s[2]}
	right := []int{b[0], (a[1] + b[1]) / 2, s[2]}
	mid := []int{(a[0] + b[0]) / 2, (a[1] + b[1]) / 2, s[2]}

  if !latticeEq(b, d) {
    // depending on down-set witness
    if(b[1] == d[1]) {
      // top-boundary down-set witness
      if latticeLe(top, d) {
        // no need to do anything
      }

      if top[0] > f(top)[0] {
        // VOP
      }

      if top[0] > f(top)[0] {
        // replace (d, b) dsw with (d, top), move to instance L_{a,top}
        b = top
      } else {
        // replace (d, b) dsw with (top, b), guarantees top <= d
        d = top
      } 
    } else {
      // right-boundary down-set witness
      if latticeLe(right, d) {
        // no need to do anything
      }
      if right[2] > f(right)[2] {
        // VOP
      }
      if right[1] < f(right)[1] {
        // replace (d, b) dsw with (d, right), move to instance L_{a, right}
        b = right
      } else {
        // replace (d, b) dsw with (right, b), guarantees right <= d
        d = right
      }
    }
  }

  if !latticeEq(a, u) {
    // depending on up-set witness
    if(a[1] == u[1]) {
      // bottom-boundary down-set witness
      if latticeLe(u, bot) {
        // no need to do anything
      }
      if bot[2] < f(bot)[2] {
        // VOP
      }
      if bot[0] < f(bot)[0] {
        // replace (a, u) usw with (bot, u), move to instance L_{bot, b}
        a = bot
      } else {
        // replace (a, u) usw with (a, bot), guarantees u <= bot
        u = bot
      }
    } else {
      // left-boundary down-set witness
      if latticeLe(u, left) {
        // no need to do anything
      }
      if left[2] < f(left)[2] {
        // VOP
      }
      if left[1] < f(left)[1] {
        // replace (a, u) usw with (left, u), move to instance L_{left,u}
        a = left
      } else {
        // replace (a, u) usw with (a, left), guarantees u <= left
        u = left
      }
    }
  }
  
  if mid[0] <= f(mid)[0] && mid[1] <= f(mid)[1] {
    // mid is in Up(f_s), move to instance L_{mid,b}
    a = mid
  }

  if mid[0] >= f(mid)[0] && mid[1] >= f(mid)[1] {
    // mid is in Down(f_s), move to instance L_{a,mid}
    b = mid
  }

  if mid[0] <= f(mid)[0] && mid[1] > f(mid)[1] {
    if mid[2] <= f(mid)[2] {
      // case 3.a
      if right[2] > f(right)[2] {
        // VOP
      }
      if right[0] < f(right)[0] {
        // solve with lemma 12
      } else {
        // replace (d, b) dsw with (mid, right), move to instance L_{a, right}
        d, b = mid, right
      }
    } else {
      // case 3.b
      if bot[2] < f(bot)[2] {
        // VOP
      }
      if bot[1] > f(bot)[1] {
        // solve with lemma 12
      } else {
        // replace (a, u) usw with (bot, mid), move to instance L_{bot,b}
        a, u = bot, mid
      }
    }
  } else {
    // case 4
    if mid[2] <= f(mid)[2] {
      if top[2] > f(top)[2] {
        // VOP
      }
      if top[1] < f(top)[1] {
        // solve with lemma 12
      } else {
        // replace (d, b) dsw with (mid, top), move to instance L_{a, top}
        d, b = mid, top
      }
    } else {
      if left[2] < f(left)[2] {
        // VOP
      }
      if left[0] > f(left)[0] {
        // solve with lemma 12
      } else {
        // replace usw (a, u) with (left, mid), move to instance L_{left,b}
        a, u = left, mid
      }
    }
  }


	return []int{}
}

func main() {
	f = func(x []int) []int {
		return x
	}

	x = []int{1, 1, 1}
	y = []int{10, 10, 10}

	// s[i] == -1 <=> ith coordinate is free in our slice
	s = []int{-1, -1, 5}

	// u == a iff not using an up-set witness, symmetrical for d == b.
	copy(u, a)
	copy(d, b)

	// hope that x in Up(f) or x in Down(f)!
	x := innerAlgorithm()
	fmt.Println(x)
}
