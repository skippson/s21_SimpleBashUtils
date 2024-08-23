#ifndef FLAGS_H
#define FLAGS_H

#define false 0
#define true 1

typedef int bool;

typedef struct flag {
  bool b;
  bool e;
  bool n;
  bool s;
  bool t;
  bool v;
  bool i;
  bool c;
  bool l;
  bool h;
  bool f;
  bool o;
} flag;

void flag_init(flag *f) {
  f->b = false;
  f->e = false;
  f->n = false;
  f->s = false;
  f->t = false;
  f->v = false;
  f->c = false;
  f->i = false;
  f->l = false;
  f->h = false;
  f->f = false;
  f->o = false;
}

#endif