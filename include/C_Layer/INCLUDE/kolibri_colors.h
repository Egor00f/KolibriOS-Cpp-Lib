#ifndef KOLIBRI_COLORS_H
#define KOLIBRI_COLORS_H



/*
  * +0: dword: frames - ���� �����
  * +4: dword: grab - ���� ���������
  * +8: dword: grab_button - ���� ������ �� ������ ���������
  * +12 = +0xC: dword: grab_button_text - ���� ������ �� ������
    �� ������ ���������
  * +16 = +0x10: dword: grab_text - ���� ������ �� ���������
  * +20 = +0x14: dword: work - ���� ������� �������
  * +24 = +0x18: dword: work_button - ���� ������ � ������� �������
  * +28 = +0x1C: dword: work_button_text - ���� ������ �� ������
    � ������� �������
  * +32 = +0x20: dword: work_text - ���� ������ � ������� �������
  * +36 = +0x24: dword: work_graph - ���� ������� � ������� �������
*/


/* typedef ksys_colors_table_t kolibri_system_colors;

kolibri_system_colors kolibri_color_table;

void kolibri_get_system_colors(kolibri_system_colors *color_table)
{
  __asm__ volatile ("int $0x40"
		    :
		    :"a"(48),"b"(3),"c"(color_table),"d"(40)
		    );

  //color_table should point to the system color table 
} */

#endif /* KOLIBRI_COLORS_H */
