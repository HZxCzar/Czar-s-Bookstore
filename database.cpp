#include "database.hpp"
#include "Accountssystem.hpp"
#include "booksystem.hpp"

template <class data>
void database<data>::Set(const string &Aname, const string &Bname) {
  Afile.Setfile(Aname);
  Bfile.Setfile(Bname);
  empt = false;
  if (Afile.IS_NEW()) {
    empt = true;
    Afile.initialise();
    Bfile.initialise();
  }
}

template <class data>
void database<data>::BREAK(const long long &p, B<data> &V) {
  A<data> K;
  Afile.readA(K, p);
  A<data> nextK;
  B<data> nextV;
  nextV.size = 0;
  nextK.next = K.next;
  data tmp;
  long long num = V.size - BLOCKSIZE / 2;
  for (long long i = 0; i < BLOCKSIZE / 2; i++) {
    nextV.elem[i] = V.elem[num + i];
    V.elem[num + i] = tmp;
    V.size--;
    nextV.size++;
  }
  nextK.first = nextV.elem[0];
  nextK.pos = Bfile.writeA(nextV);
  K.next = Afile.writeA(nextK);
  Afile.updateA(K, p);
  Bfile.updateA(V, K.pos);
}
template <class data>
long long database<data>::BinarySearch(const B<data> &block, const data &targ) {
  long long l = 0, r = block.size - 1, mid;
  if (block.size == 0) {
    r = 0;
  }
  if_find = true;
  while (l < r) {
    mid = (l + r) / 2;
    if (targ > block.elem[mid]) {
      l = mid + 1;
    } else {
      r = mid;
    }
  }
  if (block.elem[l] < targ || block.elem[l] > targ) {
    if_find = false;
  }
  return r;
}

template <class data>
bool database<data>::Scan(const A<data> &check, const data &targ) {
  if (check.next == -1) {
    return false;
  }
  if (check.first < targ) {
    A<data> nextKey;
    Afile.readA(nextKey, check.next);
    if (nextKey.first > targ) {
      return false;
    } else {
      return true;
    }
  }
  return false;
}

template <class data>
bool database<data>::Scan2(const A<data> &check, const data &targ) {
  if (check.next == -1) {
    return false;
  }
  if (check.first < targ) {
    A<data> nextKey;
    Afile.readA(nextKey, check.next);
    if (nextKey.first == targ) {
      return false;
    }
    if (nextKey.first > targ) {
      return false;
    } else {
      return true;
    }
  }
  return false;
}

template <class data>
long long database<data>::GetBound(const data &targ, const long long &p) {
  if_find = true;
  A<data> K;
  B<data> V;
  Afile.readA(K, p);
  Bfile.readA(V, K.pos);
  if (V.size == 0) {
    std::cout << "Wrong\n";
  }
  long long l = 0, r = V.size - 1, mid;
  while (l < r) {
    mid = (l + r) / 2;
    if (V.elem[mid] < targ) {
      l = mid + 1;
    } else {
      r = mid;
    }
  }
  if (!(V.elem[l] == targ)) {
    if_find = false;
  }
  return l;
}

template <class data>
long long database<data>::GetUp(const data &targ, const long long &p) {
  if_find = true;
  A<data> K;
  B<data> V;
  Afile.readA(K, p);
  Bfile.readA(V, K.pos);
  if (V.size == 0) {
    std::cout << "Wrong\n";
  }
  int l = 0, r = V.size - 1, mid;
  while (l < r) {
    mid = (l + r + 1) / 2;
    if (V.elem[mid] > targ) {
      r = mid - 1;
    } else {
      l = mid;
    }
  }
  if (!(V.elem[r] == targ)) {
    if_find = false;
  }
  return r;
}

template <class data>
void database<data>::FindRange(const data &targ, long long &beg,
                               long long &end) {
  if_find = false;
  if (empt) {
    beg = 0;
    end = 0;
  } else {
    A<data> stream;
    long long p = sizeof(long long), lastp = p;
    Afile.readA(stream, p);
    while (Scan2(stream, targ)) {
      lastp = p;
      p = stream.next;
      Afile.readA(stream, p);
    }
    beg = p;
    p = stream.next;
    if (p == -1) {
      end = -1;
      if_find = true;
      return;
    }
    Afile.readA(stream, p);
    while (stream.first == targ) {
      lastp = p;
      p = stream.next;
      if (p == -1) {
        end = -1;
        if_find = true;
        return;
      }
      Afile.readA(stream, p);
    }
    end = p;
    if_find = true;
  }
}

template <class data>
void database<data>::FindOnly(const data &targ, long long &p,
                              long long &lastp) {
  if (empt) {
    if_find = false;
    p = 0;
  } else {
    A<data> stream;
    p = sizeof(long long);
    lastp = p;
    Afile.readA(stream, p);
    while (Scan(stream, targ)) {
      lastp = p;
      p = stream.next;
      Afile.readA(stream, p);
    }
    if_find = true;
  }
}

template <class data>
void database<data>::Find(const data &targ, long long &p, long long &pos) {
  excute = false;
  if (empt) {
    return;
  } else {
    A<data> stream;
    p = sizeof(long long);
    long long lastp = p;
    Afile.readA(stream, p);
    while (Scan(stream, targ)) {
      lastp = p;
      p = stream.next;
      Afile.readA(stream, p);
    }
    B<data> V;
    Bfile.readA(V, stream.pos);
    pos = BinarySearch(V, targ);
    if (V.elem[pos] < targ) {
      pos++;
    }
    excute = false;
    if (!(V.elem[pos] < targ) && !(V.elem[pos] > targ)) {
      excute = true;
    }
  }
}

template <class data>
long long database<data>::GetInPos(const data &targ, const long long &p) {
  excute = false;
  A<data> K;
  B<data> V;
  Afile.readA(K, p);
  Bfile.readA(V, K.pos);
  long long pos = BinarySearch(V, targ);
  if (V.elem[pos] < targ) {
    pos++;
  }
  excute = false;
  if (!(V.elem[pos] < targ) && !(V.elem[pos] > targ)) {
    excute = true;
  }
  return pos;
}

template <class data> long long database<data>::GO(const long long &p) {
  A<data> K;
  Afile.readA(K, p);
  return K.next;
}

template <class data>
data database<data>::Get(const long long &p, const long long &pos) {
  A<data> K;
  B<data> V;
  Afile.readA(K, p);
  Bfile.readA(V, K.pos);
  return V.elem[pos];
}

template <class data>
void database<data>::Update(const data &elem, const long long &p,
                            const long long &pos) {
  A<data> K;
  B<data> V;
  Afile.readA(K, p);
  Bfile.readA(V, K.pos);
  V.elem[pos] = elem;
  Bfile.updateA(V, K.pos);
}

template <class data> void database<data>::ADD(const data &input) {
  excute = false;
  if (empt) {
    empt = false;
    excute = true;
    A<data> K;
    B<data> V;
    V.size = 1;
    V.elem[0] = input;
    K.first = input;
    K.next = -1;
    K.pos = sizeof(long long);
    Bfile.writeA(V);
    Afile.writeA(K);
  } else {
    long long p, lastp;
    FindOnly(input, p, lastp);
    A<data> K;
    B<data> V;
    Afile.readA(K, p);
    Bfile.readA(V, K.pos);
    long long pos = BinarySearch(V, input);
    if (if_find) {
      return;
    }
    excute = true;
    if (V.elem[pos] < input) {
      pos++;
    }
    for (long long i = V.size; i > pos; i--) {
      V.elem[i] = V.elem[i - 1];
    }
    V.size++;
    V.elem[pos] = input;
    if (pos == 0) {
      K.first = V.elem[0];
      Afile.updateA(K, p);
    }
    Bfile.updateA(V, K.pos);
    if (V.size >= BLOCKSIZE) {
      BREAK(p, V);
    }
  }
}

template <class data> void database<data>::DELETE(const data &input) {
  excute = false;
  if (empt) {
    return;
  } else {
    long long p, lastp;
    FindOnly(input, p, lastp);
    A<data> K;
    B<data> V;
    Afile.readA(K, p);
    Bfile.readA(V, K.pos);
    long long pos = BinarySearch(V, input);
    if (if_find) {
      excute = true;
      for (long long i = pos; i < V.size; i++) {
        V.elem[i] = V.elem[i + 1];
      }
      V.size--;
      if (pos == 0) {
        K.first = V.elem[0];
        Afile.updateA(K, p);
      }
      Bfile.updateA(V, K.pos);
      if (V.size <= 0) {
        if (p != sizeof(long long)) {
          A<data> lastK;
          Afile.readA(lastK, lastp);
          lastK.next = K.next;
          Afile.updateA(lastK, lastp);
        } else {
          if (K.next == -1) {
            Afile.write_info(0);
            Bfile.write_info(0);
            empt = true;
            Afile.initialise();
            Bfile.initialise();
          } else {
            A<data> nextK;
            Afile.readA(nextK, K.next);
            K = nextK;
            Afile.updateA(K, p);
          }
        }
      }
    }
  }
}
template <class data>
inline void database<data>::PRINT(const long long &begpos,
                                  const long long &endpos, const long long &beg,
                                  const long long &end) {
  if (empt) {
    std::cout << "\n";
    return;
  }
  if (begpos == -1 && endpos == -1) {
    A<data> K;
    B<data> V;
    long long p = sizeof(long long);
    while (p != -1) {
      Afile.readA(K, p);
      Bfile.readA(V, K.pos);
      for (int i = 0; i < V.size; i++) {
        V.elem[i].print();
      }
      p = K.next;
    }
  } else if (beg == -1 && end == -1) {
    A<data> K;
    B<data> V;
    long long p = begpos;
    while (p != endpos) {
      Afile.readA(K, p);
      Bfile.readA(V, K.pos);
      for (long long i = 0; i < V.size; i++) {
        V.elem[i].print();
      }
      p = K.next;
    }
    Afile.readA(K, p);
    Bfile.readA(V, K.pos);
    for (long long i = 0; i < V.size; i++) {
      V.elem[i].print();
    }
    p = K.next;
  } else {
    A<data> K;
    B<data> V;
    long long p = begpos;
    Afile.readA(K, p);
    Bfile.readA(V, K.pos);
    for (long long i = beg; i < end; i++) {
      V.elem[i].print();
    }
  }
}

template <class data> data database<data>::GetTail() {
  excute = false;
  if (empt) {
    return 0;
  } else {
    excute = true;
    A<data> K;
    long long p = sizeof(long long);
    while (p != -1) {
      Afile.readA(K, p);
      p = K.next;
    }
    B<data> V;
    Bfile.readA(V, K.pos);
    return V.elem[V.size - 1];
  }
}

template <class data>
void database<data>::PUT(const long long &p, const long long &start,
                         const long long &end, std::set<string> &u) {
  A<data> K;
  B<data> V;
  Afile.readA(K, p);
  Bfile.readA(V, K.pos);
  for (long long i = start; i < end; i++) {
    string message;
    V.elem[i].givemessage(message);
    u.insert(message);
  }
}