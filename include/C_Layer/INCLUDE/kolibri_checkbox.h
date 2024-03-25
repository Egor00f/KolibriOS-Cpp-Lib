#ifndef KOLIBRI_CHECKBOX_H
#define KOLIBRI_CHECKBOX_H


#include <kos32sys.h>
#include <kolibriLib/system/os.hpp>

extern "C"
{
/*
ch_flag_en - ���� �������������� ��� �����
ch_flag_top - ���� ������������ ������ ������
ch_flag_middle - ���� ������������ ������ � ������
ch_flag_bottom - ���� ������������ ������ � ���� �.�. �� ��������� ����������� �������� �����
*/

enum CHECKBOX_FLAGS {
     CHECKBOX_IS_SET = 0x00000002
     /* Add more flags later */
};

typedef struct {
    unsigned int left_s;
    unsigned int top_s;
    unsigned int ch_text_margin;
    unsigned int color;
    unsigned int border_color;
    unsigned int text_color;
    char *text;
    unsigned int flags;

    /* Users can use members above this */
    unsigned int size_of_str;
}check_box;

extern void (*check_box_draw2)(check_box *) __attribute__((__stdcall__));
extern void (*check_box_mouse2)(check_box *)__attribute__((__stdcall__));
extern void (*init_checkbox2)(check_box *)__attribute__((__stdcall__));

check_box* kolibri_new_check_box(unsigned int tlx, unsigned int tly, unsigned int sizex, unsigned int sizey, char *label_text)
{
     check_box* new_checkbox        = (check_box *)malloc(sizeof(check_box));
     new_checkbox -> left_s         = (tlx << 16) + sizex;
     new_checkbox -> top_s          = (tly << 16) + sizey;
     new_checkbox -> ch_text_margin = 10;
     new_checkbox -> color          = KolibriLib::OS::GetSystemColors().work_area | 0x80000000; // 0xFFFFFFFF; // 0x80AABBCC, 31-bit mus be set asciiz
     new_checkbox -> border_color   = KolibriLib::OS::GetSystemColors().work_graph;
     new_checkbox->text_color       = KolibriLib::OS::GetSystemColors().work_text;
     new_checkbox -> text           = label_text;
     new_checkbox -> flags          = 0x00000008;

     (*init_checkbox2)(new_checkbox); // count text width for mouse action and set flags

     return new_checkbox;
}

}

#endif /* KOLIBRI_CHECKBOX_H */
