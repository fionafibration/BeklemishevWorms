#include <stdlib.h>
#define N NULL

struct Z {
	int d;
	struct Z* n;
};

typedef struct Z* n;

n K() {
	n T;
	T = (n)malloc(sizeof(struct Z));

	T->n = N;

	return T;
}

n A(n e, int o) {
	n T, p;
	T = K();
	T->d = o;
	if (e == N) {
		e = T;
	}
	else {
		p = e;
		while (p->n != N) {
			p = p->n;
		}
		p->n = T;
	}
	return e;
}

int L(n e) {
	int o = 1;
	n T = e;
	while (T->n != N) {
		T = T->n;
		o++;
	}
	return o;
}

n r(n e, int o) {
	int T = L(e);
	n d = e;
	n h;
	if (o < T) {
		for (int i = 0; i < o; i++) {
			h = d;
			d = d->n;
			free(h);
		}
		return d;
	}
	else {
		return N;
	}
}

n R(n e) {
	int o = L(e);

	n T = e;

	for (int i = 0; i < o - 2; i++) {
		T = T->n;
	}
	T->n = N;
	return e;
}


int S(n e, int o) {
	int g = L(e);
	n T = e;
	if (o < g) {
		for (int i = 0; i < o; i++) {
			T = T->n;
		}
		return T->d;
	}

}


n P(n e, int o) {
	n d;
	d = K();
	d->d = o;
	d->n = e;
	return d;
}

n E(n e, n o) {
	for (int i = L(o) - 1; i >= 0; i--) {
		e = P(e, S(o, i));
	}
	return e;
}


int main(int c, char* f[]) {
	n w;
	if (c <= 1) {
		return 0;
	}
	else {
		w = A(N, atoi(f[1]));
		for (int i = 2; i < c; i++) {
			w = P(w, atoi(f[i]));
		}
	}
	int l = 0;
	while (w != N && L(w)) {
		l += 1;
		if (S(w, 0)) {
			int i = 1;

			n v;
			v = A(N, S(w, 0));

			for (int i = 1; i < L(w) && S(w, i) >= S(w, 0); i++) {
				v = A(v, S(w, i));
			}

			v = P(r(v, 1), S(v, 0) - 1);

			n t;

			w = r(w, L(v));

			t = A(N, 0);

			for (int j = 0; j <= l; j++) {
				t = E(t, v);
			}

			t = R(t);

			if (w != N) {
				t = E(w, t);
			}

			w = t;
		}
		else {
			w = r(w, 1);
		}
	}
	printf("%d", l);
	return l;
}