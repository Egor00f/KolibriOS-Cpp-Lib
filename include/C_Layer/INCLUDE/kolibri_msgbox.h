#ifndef KOLIBRI_MSGBOX_H
#define KOLIBRI_MSGBOX_H

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct __attribute__ ((__packed__)) {
    uint8_t     retval;  // 0 - win closed, 1 to n - button num, also default button on start
    uint8_t     reserv;
    char        texts[2048];      // must be enough ;-)
    char        msgbox_stack[1024];
    uint32_t    top_stack;
} msgbox;


typedef void (*msgbox_callback)(void);


extern void kolibri_msgbox_init();
extern void (*msgbox_create)(msgbox *, void *thread) __attribute__((__stdcall__)); // clears callbacks, ! if fix lib, we can return eax as of Fn51
extern void (*msgbox_setfunctions)(msgbox_callback*) __attribute__((__stdcall__)); // must be called immediately after create, zero-ended array
extern void (*msgbox_reinit)(msgbox *) __attribute__((__stdcall__));  // recalc sizes when structure changes, called auto when MsgBoxCreate

/// @brief 
/// @param title 
/// @param text 
/// @param def_but количество кнопок
/// @param buttons массив указателей на строки
/// @return 
static inline msgbox* kolibri_new_msgbox(const char* title, const char* text, int def_but, char ** buttons)
/// text can be multilined by code 13 = "\r"
/// def_but - highlighted and used on Enter (if zero - default is [X]), user may use Tabs or Arrows
/// last params are buttons text, max 8. last must set as NULL
{
    msgbox* box = (msgbox*) calloc(sizeof(msgbox), 1);
    box->retval = (uint8_t)def_but;
    char    *pc = box->texts;
    strcpy(pc, title);
    pc += strlen(title) + 1;
    strcpy(pc, text);
    pc += strlen(text) + 1;

    for(int i = 0; i < def_but; i++)
    {
        strcpy(pc, buttons[i]);
        pc += strlen(buttons[i]) + 1;
    }

    return box;
}

static inline void kolibri_start_msgbox(msgbox* box, msgbox_callback cb[])
{
    (*msgbox_create)(box, &box->top_stack);
    if (cb) (*msgbox_setfunctions)(cb);
}

#ifdef __cplusplus
}
#endif

#endif
