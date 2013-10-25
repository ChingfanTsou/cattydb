#include "select_where.h"

tuple_buffer* dat_file;
tuple_buffer* new_file;

void select_where_on_open(const char* file, const char* file_new)
{
        char tb_m[TABLE_NAME_LEN];
        char tb_m_s[TABLE_NAME_LEN];
        char tb_d[TABLE_NAME_LEN];
        char tb_d_s[TABLE_NAME_LEN];
        strcpy(tb_m, file);
        strcat(tb_m, ".m");
        strcpy(tb_d, file);
        strcat(tb_d, ".dat");

        strcpy(tb_m_s, file_new);
        strcat(tb_m_s, ".m");
        strcpy(tb_d_s, file_new);
        strcat(tb_d_s, ".dat");

        table_set(file);
        dat_file = update_buf_create(tb_d);
        new_file = out_buf_create(tb_d_s, "wb");
        create_table(file_new);
        int i;
        for (i = 0; i < item_num; ++i)
                create_col(item_arr[i].item_name, item_arr[i].item_type, item_arr[i].item_byte, item_arr[i].is_pr);
        create_table_on_close();
}
void select_where(const char* pro)
{
        char item[2][STRING_LENGTH];
        sscanf(pro, "%s = %s", item[0], item[1]);
        while (!eobuf(dat_file)) {
                if (where_equal1(dat_file, item[0], item[1])) {
                        buf_move_backward(dat_file, get_tot_bytes());
                        int i;
                        for (i = 0; i < item_num; ++i) {
                                if (item_arr[i].item_type[0] == 'I') {
                                        int val = buf_get_int(dat_file);
                                        buf_push_int(new_file, val);
                                } else {
                                        int k = 0;
                                        for (; k < item_arr[i].item_byte; ++k) {
                                                char val = buf_get_char(dat_file);
                                                buf_push_char(new_file, val);
                                        }
                                }
                        }
                }
        }
}

void select_where_on_close()
{
        out_buf_remove(new_file);
        update_buf_remove(dat_file);
}/*
int main()
{
        select_where_on_open("product","tmp");
        select_where("ID = 123");
        select_where_on_close();
        show_table("tmp");
        return 0;
}*/
