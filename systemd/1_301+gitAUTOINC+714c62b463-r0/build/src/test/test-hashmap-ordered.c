/* GENERATED FILE */
#define ORDERED
/***
  This file is part of systemd

  Copyright 2013 Daniel Buch

  systemd is free software; you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation; either version 2.1 of the License, or
  (at your option) any later version.

  systemd is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with systemd; If not, see <http://www.gnu.org/licenses/>.
***/

#include "alloc-util.h"
#include "hashmap.h"
#include "string-util.h"
#include "strv.h"
#include "util.h"

void test_ordered_hashmap_funcs(void);

static void test_ordered_hashmap_replace(void) {
        OrderedHashmap *m;
        char *val1, *val2, *val3, *val4, *val5, *r;

        m = ordered_hashmap_new(&string_hash_ops);

        val1 = strdup("val1");
        assert_se(val1);
        val2 = strdup("val2");
        assert_se(val2);
        val3 = strdup("val3");
        assert_se(val3);
        val4 = strdup("val4");
        assert_se(val4);
        val5 = strdup("val5");
        assert_se(val5);

        ordered_hashmap_put(m, "key 1", val1);
        ordered_hashmap_put(m, "key 2", val2);
        ordered_hashmap_put(m, "key 3", val3);
        ordered_hashmap_put(m, "key 4", val4);

        ordered_hashmap_replace(m, "key 3", val1);
        r = ordered_hashmap_get(m, "key 3");
        assert_se(streq(r, "val1"));

        ordered_hashmap_replace(m, "key 5", val5);
        r = ordered_hashmap_get(m, "key 5");
        assert_se(streq(r, "val5"));

        free(val1);
        free(val2);
        free(val3);
        free(val4);
        free(val5);
        ordered_hashmap_free(m);
}

static void test_ordered_hashmap_copy(void) {
        OrderedHashmap *m, *copy;
        char *val1, *val2, *val3, *val4, *r;

        val1 = strdup("val1");
        assert_se(val1);
        val2 = strdup("val2");
        assert_se(val2);
        val3 = strdup("val3");
        assert_se(val3);
        val4 = strdup("val4");
        assert_se(val4);

        m = ordered_hashmap_new(&string_hash_ops);

        ordered_hashmap_put(m, "key 1", val1);
        ordered_hashmap_put(m, "key 2", val2);
        ordered_hashmap_put(m, "key 3", val3);
        ordered_hashmap_put(m, "key 4", val4);

        copy = ordered_hashmap_copy(m);

        r = ordered_hashmap_get(copy, "key 1");
        assert_se(streq(r, "val1"));
        r = ordered_hashmap_get(copy, "key 2");
        assert_se(streq(r, "val2"));
        r = ordered_hashmap_get(copy, "key 3");
        assert_se(streq(r, "val3"));
        r = ordered_hashmap_get(copy, "key 4");
        assert_se(streq(r, "val4"));

        ordered_hashmap_free_free(copy);
        ordered_hashmap_free(m);
}

static void test_ordered_hashmap_get_strv(void) {
        OrderedHashmap *m;
        char **strv;
        char *val1, *val2, *val3, *val4;

        val1 = strdup("val1");
        assert_se(val1);
        val2 = strdup("val2");
        assert_se(val2);
        val3 = strdup("val3");
        assert_se(val3);
        val4 = strdup("val4");
        assert_se(val4);

        m = ordered_hashmap_new(&string_hash_ops);

        ordered_hashmap_put(m, "key 1", val1);
        ordered_hashmap_put(m, "key 2", val2);
        ordered_hashmap_put(m, "key 3", val3);
        ordered_hashmap_put(m, "key 4", val4);

        strv = ordered_hashmap_get_strv(m);

#ifndef ORDERED
        strv = strv_sort(strv);
#endif

        assert_se(streq(strv[0], "val1"));
        assert_se(streq(strv[1], "val2"));
        assert_se(streq(strv[2], "val3"));
        assert_se(streq(strv[3], "val4"));

        strv_free(strv);

        ordered_hashmap_free(m);
}

static void test_ordered_hashmap_move_one(void) {
        OrderedHashmap *m, *n;
        char *val1, *val2, *val3, *val4, *r;

        val1 = strdup("val1");
        assert_se(val1);
        val2 = strdup("val2");
        assert_se(val2);
        val3 = strdup("val3");
        assert_se(val3);
        val4 = strdup("val4");
        assert_se(val4);

        m = ordered_hashmap_new(&string_hash_ops);
        n = ordered_hashmap_new(&string_hash_ops);

        ordered_hashmap_put(m, "key 1", val1);
        ordered_hashmap_put(m, "key 2", val2);
        ordered_hashmap_put(m, "key 3", val3);
        ordered_hashmap_put(m, "key 4", val4);

        assert_se(ordered_hashmap_move_one(n, NULL, "key 3") == -ENOENT);
        assert_se(ordered_hashmap_move_one(n, m, "key 5") == -ENOENT);
        assert_se(ordered_hashmap_move_one(n, m, "key 3") == 0);
        assert_se(ordered_hashmap_move_one(n, m, "key 4") == 0);

        r = ordered_hashmap_get(n, "key 3");
        assert_se(r && streq(r, "val3"));
        r = ordered_hashmap_get(n, "key 4");
        assert_se(r && streq(r, "val4"));
        r = ordered_hashmap_get(m, "key 3");
        assert_se(!r);

        assert_se(ordered_hashmap_move_one(n, m, "key 3") == -EEXIST);

        ordered_hashmap_free_free(m);
        ordered_hashmap_free_free(n);
}

static void test_ordered_hashmap_move(void) {
        OrderedHashmap *m, *n;
        char *val1, *val2, *val3, *val4, *r;

        val1 = strdup("val1");
        assert_se(val1);
        val2 = strdup("val2");
        assert_se(val2);
        val3 = strdup("val3");
        assert_se(val3);
        val4 = strdup("val4");
        assert_se(val4);

        m = ordered_hashmap_new(&string_hash_ops);
        n = ordered_hashmap_new(&string_hash_ops);

        ordered_hashmap_put(n, "key 1", strdup(val1));
        ordered_hashmap_put(m, "key 1", val1);
        ordered_hashmap_put(m, "key 2", val2);
        ordered_hashmap_put(m, "key 3", val3);
        ordered_hashmap_put(m, "key 4", val4);

        assert_se(ordered_hashmap_move(n, NULL) == 0);
        assert_se(ordered_hashmap_move(n, m) == 0);

        assert_se(ordered_hashmap_size(m) == 1);
        r = ordered_hashmap_get(m, "key 1");
        assert_se(r && streq(r, "val1"));

        r = ordered_hashmap_get(n, "key 1");
        assert_se(r && streq(r, "val1"));
        r = ordered_hashmap_get(n, "key 2");
        assert_se(r && streq(r, "val2"));
        r = ordered_hashmap_get(n, "key 3");
        assert_se(r && streq(r, "val3"));
        r = ordered_hashmap_get(n, "key 4");
        assert_se(r && streq(r, "val4"));

        ordered_hashmap_free_free(m);
        ordered_hashmap_free_free(n);
}

static void test_ordered_hashmap_update(void) {
        OrderedHashmap *m;
        char *val1, *val2, *r;

        m = ordered_hashmap_new(&string_hash_ops);
        val1 = strdup("old_value");
        assert_se(val1);
        val2 = strdup("new_value");
        assert_se(val2);

        ordered_hashmap_put(m, "key 1", val1);
        r = ordered_hashmap_get(m, "key 1");
        assert_se(streq(r, "old_value"));

        assert_se(ordered_hashmap_update(m, "key 2", val2) == -ENOENT);
        r = ordered_hashmap_get(m, "key 1");
        assert_se(streq(r, "old_value"));

        assert_se(ordered_hashmap_update(m, "key 1", val2) == 0);
        r = ordered_hashmap_get(m, "key 1");
        assert_se(streq(r, "new_value"));

        free(val1);
        free(val2);
        ordered_hashmap_free(m);
}

static void test_ordered_hashmap_put(void) {
        OrderedHashmap *m = NULL;
        int valid_ordered_hashmap_put;
        void *val1 = (void*) "val 1";
        void *val2 = (void*) "val 2";
        _cleanup_free_ char* key1 = NULL;

        assert_se(ordered_hashmap_ensure_allocated(&m, &string_hash_ops) >= 0);
        assert_se(m);

        valid_ordered_hashmap_put = ordered_hashmap_put(m, "key 1", val1);
        assert_se(valid_ordered_hashmap_put == 1);
        assert_se(ordered_hashmap_put(m, "key 1", val1) == 0);
        assert_se(ordered_hashmap_put(m, "key 1", val2) == -EEXIST);
        key1 = strdup("key 1");
        assert_se(ordered_hashmap_put(m, key1, val1) == 0);
        assert_se(ordered_hashmap_put(m, key1, val2) == -EEXIST);

        ordered_hashmap_free(m);
}

static void test_ordered_hashmap_remove(void) {
        _cleanup_ordered_hashmap_free_ OrderedHashmap *m = NULL;
        char *r;

        r = ordered_hashmap_remove(NULL, "key 1");
        assert_se(r == NULL);

        m = ordered_hashmap_new(&string_hash_ops);
        assert_se(m);

        r = ordered_hashmap_remove(m, "no such key");
        assert_se(r == NULL);

        ordered_hashmap_put(m, "key 1", (void*) "val 1");
        ordered_hashmap_put(m, "key 2", (void*) "val 2");

        r = ordered_hashmap_remove(m, "key 1");
        assert_se(streq(r, "val 1"));

        r = ordered_hashmap_get(m, "key 2");
        assert_se(streq(r, "val 2"));
        assert_se(!ordered_hashmap_get(m, "key 1"));
}

static void test_ordered_hashmap_remove2(void) {
        _cleanup_ordered_hashmap_free_free_free_ OrderedHashmap *m = NULL;
        char key1[] = "key 1";
        char key2[] = "key 2";
        char val1[] = "val 1";
        char val2[] = "val 2";
        void *r, *r2;

        r = ordered_hashmap_remove2(NULL, "key 1", &r2);
        assert_se(r == NULL);

        m = ordered_hashmap_new(&string_hash_ops);
        assert_se(m);

        r = ordered_hashmap_remove2(m, "no such key", &r2);
        assert_se(r == NULL);

        ordered_hashmap_put(m, strdup(key1), strdup(val1));
        ordered_hashmap_put(m, strdup(key2), strdup(val2));

        r = ordered_hashmap_remove2(m, key1, &r2);
        assert_se(streq(r, val1));
        assert_se(streq(r2, key1));
        free(r);
        free(r2);

        r = ordered_hashmap_get(m, key2);
        assert_se(streq(r, val2));
        assert_se(!ordered_hashmap_get(m, key1));
}

static void test_ordered_hashmap_remove_value(void) {
        _cleanup_ordered_hashmap_free_ OrderedHashmap *m = NULL;
        char *r;

        char val1[] = "val 1";
        char val2[] = "val 2";

        r = ordered_hashmap_remove_value(NULL, "key 1", val1);
        assert_se(r == NULL);

        m = ordered_hashmap_new(&string_hash_ops);
        assert_se(m);

        r = ordered_hashmap_remove_value(m, "key 1", val1);
        assert_se(r == NULL);

        ordered_hashmap_put(m, "key 1", val1);
        ordered_hashmap_put(m, "key 2", val2);

        r = ordered_hashmap_remove_value(m, "key 1", val1);
        assert_se(streq(r, "val 1"));

        r = ordered_hashmap_get(m, "key 2");
        assert_se(streq(r, "val 2"));
        assert_se(!ordered_hashmap_get(m, "key 1"));

        r = ordered_hashmap_remove_value(m, "key 2", val1);
        assert_se(r == NULL);

        r = ordered_hashmap_get(m, "key 2");
        assert_se(streq(r, "val 2"));
        assert_se(!ordered_hashmap_get(m, "key 1"));
}

static void test_ordered_hashmap_remove_and_put(void) {
        _cleanup_ordered_hashmap_free_ OrderedHashmap *m = NULL;
        int valid;
        char *r;

        m = ordered_hashmap_new(&string_hash_ops);
        assert_se(m);

        valid = ordered_hashmap_remove_and_put(m, "invalid key", "new key", NULL);
        assert_se(valid == -ENOENT);

        valid = ordered_hashmap_put(m, "key 1", (void*) (const char *) "val 1");
        assert_se(valid == 1);

        valid = ordered_hashmap_remove_and_put(NULL, "key 1", "key 2", (void*) (const char *) "val 2");
        assert_se(valid == -ENOENT);

        valid = ordered_hashmap_remove_and_put(m, "key 1", "key 2", (void*) (const char *) "val 2");
        assert_se(valid == 0);

        r = ordered_hashmap_get(m, "key 2");
        assert_se(streq(r, "val 2"));
        assert_se(!ordered_hashmap_get(m, "key 1"));

        valid = ordered_hashmap_put(m, "key 3", (void*) (const char *) "val 3");
        assert_se(valid == 1);
        valid = ordered_hashmap_remove_and_put(m, "key 3", "key 2", (void*) (const char *) "val 2");
        assert_se(valid == -EEXIST);
}

static void test_ordered_hashmap_remove_and_replace(void) {
        _cleanup_ordered_hashmap_free_ OrderedHashmap *m = NULL;
        int valid;
        void *key1 = UINT_TO_PTR(1);
        void *key2 = UINT_TO_PTR(2);
        void *key3 = UINT_TO_PTR(3);
        void *r;
        int i, j;

        m = ordered_hashmap_new(&trivial_hash_ops);
        assert_se(m);

        valid = ordered_hashmap_remove_and_replace(m, key1, key2, NULL);
        assert_se(valid == -ENOENT);

        valid = ordered_hashmap_put(m, key1, key1);
        assert_se(valid == 1);

        valid = ordered_hashmap_remove_and_replace(NULL, key1, key2, key2);
        assert_se(valid == -ENOENT);

        valid = ordered_hashmap_remove_and_replace(m, key1, key2, key2);
        assert_se(valid == 0);

        r = ordered_hashmap_get(m, key2);
        assert_se(r == key2);
        assert_se(!ordered_hashmap_get(m, key1));

        valid = ordered_hashmap_put(m, key3, key3);
        assert_se(valid == 1);
        valid = ordered_hashmap_remove_and_replace(m, key3, key2, key2);
        assert_se(valid == 0);
        r = ordered_hashmap_get(m, key2);
        assert_se(r == key2);
        assert_se(!ordered_hashmap_get(m, key3));

        /* Repeat this test several times to increase the chance of hitting
         * the less likely case in ordered_hashmap_remove_and_replace where it
         * compensates for the backward shift. */
        for (i = 0; i < 20; i++) {
                ordered_hashmap_clear(m);

                for (j = 1; j < 7; j++)
                        ordered_hashmap_put(m, UINT_TO_PTR(10*i + j), UINT_TO_PTR(10*i + j));
                valid = ordered_hashmap_remove_and_replace(m, UINT_TO_PTR(10*i + 1),
                                                   UINT_TO_PTR(10*i + 2),
                                                   UINT_TO_PTR(10*i + 2));
                assert_se(valid == 0);
                assert_se(!ordered_hashmap_get(m, UINT_TO_PTR(10*i + 1)));
                for (j = 2; j < 7; j++) {
                        r = ordered_hashmap_get(m, UINT_TO_PTR(10*i + j));
                        assert_se(r == UINT_TO_PTR(10*i + j));
                }
        }
}

static void test_ordered_hashmap_ensure_allocated(void) {
        OrderedHashmap *m;
        int valid_ordered_hashmap;

        m = ordered_hashmap_new(&string_hash_ops);

        valid_ordered_hashmap = ordered_hashmap_ensure_allocated(&m, &string_hash_ops);
        assert_se(valid_ordered_hashmap == 0);

        assert_se(m);
        ordered_hashmap_free(m);
}

static void test_ordered_hashmap_foreach_key(void) {
        OrderedHashmap *m;
        Iterator i;
        bool key_found[] = { false, false, false, false };
        const char *s;
        const char *key;
        static const char key_table[] =
                "key 1\0"
                "key 2\0"
                "key 3\0"
                "key 4\0";

        m = ordered_hashmap_new(&string_hash_ops);

        NULSTR_FOREACH(key, key_table)
                ordered_hashmap_put(m, key, (void*) (const char*) "my dummy val");

        ORDERED_HASHMAP_FOREACH_KEY(s, key, m, i) {
                assert(s);
                if (!key_found[0] && streq(key, "key 1"))
                        key_found[0] = true;
                else if (!key_found[1] && streq(key, "key 2"))
                        key_found[1] = true;
                else if (!key_found[2] && streq(key, "key 3"))
                        key_found[2] = true;
                else if (!key_found[3] && streq(key, "fail"))
                        key_found[3] = true;
        }

        assert_se(m);
        assert_se(key_found[0] && key_found[1] && key_found[2] && !key_found[3]);

        ordered_hashmap_free(m);
}

static void test_ordered_hashmap_foreach(void) {
        OrderedHashmap *m;
        Iterator i;
        bool value_found[] = { false, false, false, false };
        char *val1, *val2, *val3, *val4, *s;
        unsigned count;

        val1 = strdup("my val1");
        assert_se(val1);
        val2 = strdup("my val2");
        assert_se(val2);
        val3 = strdup("my val3");
        assert_se(val3);
        val4 = strdup("my val4");
        assert_se(val4);

        m = NULL;

        count = 0;
        ORDERED_HASHMAP_FOREACH(s, m, i)
                count++;
        assert_se(count == 0);

        m = ordered_hashmap_new(&string_hash_ops);

        count = 0;
        ORDERED_HASHMAP_FOREACH(s, m, i)
                count++;
        assert_se(count == 0);

        ordered_hashmap_put(m, "Key 1", val1);
        ordered_hashmap_put(m, "Key 2", val2);
        ordered_hashmap_put(m, "Key 3", val3);
        ordered_hashmap_put(m, "Key 4", val4);

        ORDERED_HASHMAP_FOREACH(s, m, i) {
                if (!value_found[0] && streq(s, val1))
                        value_found[0] = true;
                else if (!value_found[1] && streq(s, val2))
                        value_found[1] = true;
                else if (!value_found[2] && streq(s, val3))
                        value_found[2] = true;
                else if (!value_found[3] && streq(s, val4))
                        value_found[3] = true;
        }

        assert_se(m);
        assert_se(value_found[0] && value_found[1] && value_found[2] && value_found[3]);

        ordered_hashmap_free_free(m);
}

static void test_ordered_hashmap_merge(void) {
        OrderedHashmap *m;
        OrderedHashmap *n;
        char *val1, *val2, *val3, *val4, *r;

        val1 = strdup("my val1");
        assert_se(val1);
        val2 = strdup("my val2");
        assert_se(val2);
        val3 = strdup("my val3");
        assert_se(val3);
        val4 = strdup("my val4");
        assert_se(val4);

        n = ordered_hashmap_new(&string_hash_ops);
        m = ordered_hashmap_new(&string_hash_ops);

        ordered_hashmap_put(m, "Key 1", val1);
        ordered_hashmap_put(m, "Key 2", val2);
        ordered_hashmap_put(n, "Key 3", val3);
        ordered_hashmap_put(n, "Key 4", val4);

        assert_se(ordered_hashmap_merge(m, n) == 0);
        r = ordered_hashmap_get(m, "Key 3");
        assert_se(r && streq(r, "my val3"));
        r = ordered_hashmap_get(m, "Key 4");
        assert_se(r && streq(r, "my val4"));

        assert_se(n);
        assert_se(m);
        ordered_hashmap_free(n);
        ordered_hashmap_free_free(m);
}

static void test_ordered_hashmap_contains(void) {
        OrderedHashmap *m;
        char *val1;

        val1 = strdup("my val");
        assert_se(val1);

        m = ordered_hashmap_new(&string_hash_ops);

        assert_se(!ordered_hashmap_contains(m, "Key 1"));
        ordered_hashmap_put(m, "Key 1", val1);
        assert_se(ordered_hashmap_contains(m, "Key 1"));
        assert_se(!ordered_hashmap_contains(m, "Key 2"));

        assert_se(!ordered_hashmap_contains(NULL, "Key 1"));

        assert_se(m);
        ordered_hashmap_free_free(m);
}

static void test_ordered_hashmap_isempty(void) {
        OrderedHashmap *m;
        char *val1;

        val1 = strdup("my val");
        assert_se(val1);

        m = ordered_hashmap_new(&string_hash_ops);

        assert_se(ordered_hashmap_isempty(m));
        ordered_hashmap_put(m, "Key 1", val1);
        assert_se(!ordered_hashmap_isempty(m));

        assert_se(m);
        ordered_hashmap_free_free(m);
}

static void test_ordered_hashmap_size(void) {
        OrderedHashmap *m;
        char *val1, *val2, *val3, *val4;

        val1 = strdup("my val");
        assert_se(val1);
        val2 = strdup("my val");
        assert_se(val2);
        val3 = strdup("my val");
        assert_se(val3);
        val4 = strdup("my val");
        assert_se(val4);

        assert_se(ordered_hashmap_size(NULL) == 0);
        assert_se(ordered_hashmap_buckets(NULL) == 0);

        m = ordered_hashmap_new(&string_hash_ops);

        ordered_hashmap_put(m, "Key 1", val1);
        ordered_hashmap_put(m, "Key 2", val2);
        ordered_hashmap_put(m, "Key 3", val3);
        ordered_hashmap_put(m, "Key 4", val4);

        assert_se(m);
        assert_se(ordered_hashmap_size(m) == 4);
        assert_se(ordered_hashmap_buckets(m) >= 4);
        ordered_hashmap_free_free(m);
}

static void test_ordered_hashmap_get(void) {
        OrderedHashmap *m;
        char *r;
        char *val;

        val = strdup("my val");
        assert_se(val);

        r = ordered_hashmap_get(NULL, "Key 1");
        assert_se(r == NULL);

        m = ordered_hashmap_new(&string_hash_ops);

        ordered_hashmap_put(m, "Key 1", val);

        r = ordered_hashmap_get(m, "Key 1");
        assert_se(streq(r, val));

        r = ordered_hashmap_get(m, "no such key");
        assert_se(r == NULL);

        assert_se(m);
        ordered_hashmap_free_free(m);
}

static void test_ordered_hashmap_get2(void) {
        OrderedHashmap *m;
        char *r;
        char *val;
        char key_orig[] = "Key 1";
        void *key_copy;

        val = strdup("my val");
        assert_se(val);

        key_copy = strdup(key_orig);
        assert_se(key_copy);

        r = ordered_hashmap_get2(NULL, key_orig, &key_copy);
        assert_se(r == NULL);

        m = ordered_hashmap_new(&string_hash_ops);

        ordered_hashmap_put(m, key_copy, val);
        key_copy = NULL;

        r = ordered_hashmap_get2(m, key_orig, &key_copy);
        assert_se(streq(r, val));
        assert_se(key_orig != key_copy);
        assert_se(streq(key_orig, key_copy));

        r = ordered_hashmap_get2(m, "no such key", NULL);
        assert_se(r == NULL);

        assert_se(m);
        ordered_hashmap_free_free_free(m);
}

static void crippled_ordered_hashmap_func(const void *p, struct siphash *state) {
        return trivial_hash_func(INT_TO_PTR(PTR_TO_INT(p) & 0xff), state);
}

static const struct hash_ops crippled_ordered_hashmap_ops = {
        .hash = crippled_ordered_hashmap_func,
        .compare = trivial_compare_func,
};

static void test_ordered_hashmap_many(void) {
        OrderedHashmap *h;
        unsigned i, j;
        void *v, *k;
        static const struct {
                const struct hash_ops *ops;
                unsigned n_entries;
        } tests[] = {
                { .ops = NULL,                  .n_entries = 1 << 20 },
                { .ops = &crippled_ordered_hashmap_ops, .n_entries = 1 << 14 },
        };


        for (j = 0; j < ELEMENTSOF(tests); j++) {
                assert_se(h = ordered_hashmap_new(tests[j].ops));

                for (i = 1; i < tests[j].n_entries*3; i+=3) {
                        assert_se(ordered_hashmap_put(h, UINT_TO_PTR(i), UINT_TO_PTR(i)) >= 0);
                        assert_se(PTR_TO_UINT(ordered_hashmap_get(h, UINT_TO_PTR(i))) == i);
                }

                for (i = 1; i < tests[j].n_entries*3; i++)
                        assert_se(ordered_hashmap_contains(h, UINT_TO_PTR(i)) == (i % 3 == 1));

                log_info("%u <= %u * 0.8 = %g", ordered_hashmap_size(h), ordered_hashmap_buckets(h), ordered_hashmap_buckets(h) * 0.8);

                assert_se(ordered_hashmap_size(h) <= ordered_hashmap_buckets(h) * 0.8);
                assert_se(ordered_hashmap_size(h) == tests[j].n_entries);

                while (!ordered_hashmap_isempty(h)) {
                        k = ordered_hashmap_first_key(h);
                        v = ordered_hashmap_remove(h, k);
                        assert_se(v == k);
                }

                ordered_hashmap_free(h);
        }
}

static void test_ordered_hashmap_first(void) {
        _cleanup_ordered_hashmap_free_ OrderedHashmap *m = NULL;

        m = ordered_hashmap_new(&string_hash_ops);
        assert_se(m);

        assert_se(!ordered_hashmap_first(m));
        assert_se(ordered_hashmap_put(m, "key 1", (void*) "val 1") == 1);
        assert_se(streq(ordered_hashmap_first(m), "val 1"));
        assert_se(ordered_hashmap_put(m, "key 2", (void*) "val 2") == 1);
#ifdef ORDERED
        assert_se(streq(ordered_hashmap_first(m), "val 1"));
        assert_se(ordered_hashmap_remove(m, "key 1"));
        assert_se(streq(ordered_hashmap_first(m), "val 2"));
#endif
}

static void test_ordered_hashmap_first_key(void) {
        _cleanup_ordered_hashmap_free_ OrderedHashmap *m = NULL;

        m = ordered_hashmap_new(&string_hash_ops);
        assert_se(m);

        assert_se(!ordered_hashmap_first_key(m));
        assert_se(ordered_hashmap_put(m, "key 1", NULL) == 1);
        assert_se(streq(ordered_hashmap_first_key(m), "key 1"));
        assert_se(ordered_hashmap_put(m, "key 2", NULL) == 1);
#ifdef ORDERED
        assert_se(streq(ordered_hashmap_first_key(m), "key 1"));
        assert_se(ordered_hashmap_remove(m, "key 1") == NULL);
        assert_se(streq(ordered_hashmap_first_key(m), "key 2"));
#endif
}

static void test_ordered_hashmap_steal_first_key(void) {
        _cleanup_ordered_hashmap_free_ OrderedHashmap *m = NULL;

        m = ordered_hashmap_new(&string_hash_ops);
        assert_se(m);

        assert_se(!ordered_hashmap_steal_first_key(m));
        assert_se(ordered_hashmap_put(m, "key 1", NULL) == 1);
        assert_se(streq(ordered_hashmap_steal_first_key(m), "key 1"));

        assert_se(ordered_hashmap_isempty(m));
}

static void test_ordered_hashmap_steal_first(void) {
        _cleanup_ordered_hashmap_free_ OrderedHashmap *m = NULL;
        int seen[3] = {};
        char *val;

        m = ordered_hashmap_new(&string_hash_ops);
        assert_se(m);

        assert_se(ordered_hashmap_put(m, "key 1", (void*) "1") == 1);
        assert_se(ordered_hashmap_put(m, "key 2", (void*) "22") == 1);
        assert_se(ordered_hashmap_put(m, "key 3", (void*) "333") == 1);

        while ((val = ordered_hashmap_steal_first(m)))
                seen[strlen(val) - 1]++;

        assert_se(seen[0] == 1 && seen[1] == 1 && seen[2] == 1);

        assert_se(ordered_hashmap_isempty(m));
}

static void test_ordered_hashmap_clear_free_free(void) {
        _cleanup_ordered_hashmap_free_ OrderedHashmap *m = NULL;

        m = ordered_hashmap_new(&string_hash_ops);
        assert_se(m);

        assert_se(ordered_hashmap_put(m, strdup("key 1"), NULL) == 1);
        assert_se(ordered_hashmap_put(m, strdup("key 2"), NULL) == 1);
        assert_se(ordered_hashmap_put(m, strdup("key 3"), NULL) == 1);

        ordered_hashmap_clear_free_free(m);
        assert_se(ordered_hashmap_isempty(m));
}

static void test_ordered_hashmap_reserve(void) {
        _cleanup_ordered_hashmap_free_ OrderedHashmap *m = NULL;

        m = ordered_hashmap_new(&string_hash_ops);

        assert_se(ordered_hashmap_reserve(m, 1) == 0);
        assert_se(ordered_hashmap_buckets(m) < 1000);
        assert_se(ordered_hashmap_reserve(m, 1000) == 0);
        assert_se(ordered_hashmap_buckets(m) >= 1000);
        assert_se(ordered_hashmap_isempty(m));

        assert_se(ordered_hashmap_put(m, "key 1", (void*) "val 1") == 1);

        assert_se(ordered_hashmap_reserve(m, UINT_MAX) == -ENOMEM);
        assert_se(ordered_hashmap_reserve(m, UINT_MAX - 1) == -ENOMEM);
}

void test_ordered_hashmap_funcs(void) {
        test_ordered_hashmap_copy();
        test_ordered_hashmap_get_strv();
        test_ordered_hashmap_move_one();
        test_ordered_hashmap_move();
        test_ordered_hashmap_replace();
        test_ordered_hashmap_update();
        test_ordered_hashmap_put();
        test_ordered_hashmap_remove();
        test_ordered_hashmap_remove2();
        test_ordered_hashmap_remove_value();
        test_ordered_hashmap_remove_and_put();
        test_ordered_hashmap_remove_and_replace();
        test_ordered_hashmap_ensure_allocated();
        test_ordered_hashmap_foreach();
        test_ordered_hashmap_foreach_key();
        test_ordered_hashmap_contains();
        test_ordered_hashmap_merge();
        test_ordered_hashmap_isempty();
        test_ordered_hashmap_get();
        test_ordered_hashmap_get2();
        test_ordered_hashmap_size();
        test_ordered_hashmap_many();
        test_ordered_hashmap_first();
        test_ordered_hashmap_first_key();
        test_ordered_hashmap_steal_first_key();
        test_ordered_hashmap_steal_first();
        test_ordered_hashmap_clear_free_free();
        test_ordered_hashmap_reserve();
}
