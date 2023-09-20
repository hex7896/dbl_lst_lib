#ifndef DBL_LST_PRIV_H
# define DBL_LST_PRIV_H

typedef struct dbl_lst_s dbl_lst_t;

struct dbl_lst_s {
    dbl_lst_t   *prev;
    dbl_lst_t   *next;
};

#endif
