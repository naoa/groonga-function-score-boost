#include <string.h>
#include <stdlib.h>
#include <groonga/plugin.h>

#ifdef __GNUC__
# define GNUC_UNUSED __attribute__((__unused__))
#else
# define GNUC_UNUSED
#endif

typedef struct {
  double score;
  int n_subrecs;
  int subrecs[1];
} grn_rset_recinfo;

static grn_rc
selector_score_boost(grn_ctx *ctx, GNUC_UNUSED grn_obj *table, GNUC_UNUSED grn_obj *index,
                     GNUC_UNUSED int nargs, grn_obj **args,
                     grn_obj *res, GNUC_UNUSED grn_operator op)
{
  grn_obj *boost;
  if (nargs != 2) {
    GRN_PLUGIN_ERROR(ctx, GRN_INVALID_ARGUMENT,
                     "score_boost(): wrong number of arguments (%d for 1)",
                     nargs - 1);
    return GRN_INVALID_ARGUMENT;
  }
  boost = args[1];

  if (!(boost->header.type == GRN_BULK &&
        ((boost->header.domain == GRN_DB_FLOAT)))) {
    GRN_PLUGIN_ERROR(ctx, GRN_INVALID_ARGUMENT,
                     "score_boost(): 1st argument must be FLOAT");
    return GRN_INVALID_ARGUMENT;
  }

  {
    grn_table_cursor *cur;
    grn_id id;
    grn_rset_recinfo *ri;

    cur = grn_table_cursor_open(ctx, res, NULL, 0, NULL, 0, 0, -1,
                                GRN_CURSOR_BY_ID);
    if (!cur) {
      GRN_PLUGIN_ERROR(ctx,
                       GRN_NO_MEMORY_AVAILABLE,
                       "[score_boost] couldn't open cursor");
      grn_table_cursor_close(ctx, cur);
      goto exit;
    }
    while ((id = grn_table_cursor_next(ctx, cur)) != GRN_ID_NIL) {
      grn_hash_cursor_get_value(ctx, (grn_hash_cursor *)cur, (void **)&ri);
      ri->score *= GRN_FLOAT_VALUE(boost);
    }
    grn_table_cursor_close(ctx, cur);
  }

exit :
  
  return GRN_SUCCESS;
}

grn_rc
GRN_PLUGIN_INIT(GNUC_UNUSED grn_ctx *ctx)
{
  return GRN_SUCCESS;
}

grn_rc
GRN_PLUGIN_REGISTER(grn_ctx *ctx)
{
  {
    grn_obj *selector_proc;

    selector_proc = grn_proc_create(ctx, "score_boost", -1, GRN_PROC_FUNCTION,
                                    NULL, NULL, NULL, 0, NULL);
    grn_proc_set_selector(ctx, selector_proc, selector_score_boost);
  }


  return ctx->rc;
}

grn_rc
GRN_PLUGIN_FIN(GNUC_UNUSED grn_ctx *ctx)
{
  return GRN_SUCCESS;
}
