#include <C_Layer/INCLUDE/kolibri_opendialog.h>

open_dialog *kolibri_new_open_dialog(unsigned int mode, unsigned short tlx, unsigned short tly, unsigned short x_size, unsigned short y_size)
{
    open_dialog *new_opendialog	= (open_dialog *) malloc(sizeof(open_dialog));
    od_filter *new_od_filter	= (od_filter *) malloc(sizeof(od_filter));
    char *plugin_path	= (char *) calloc(4096, sizeof(char));
	char *openfile_path	= (char *) calloc(4096, sizeof(char));
	char *proc_info	= (char *) calloc(1024, sizeof(char));
	char *filename_area	= (char *) calloc(256, sizeof(char));

	new_od_filter -> size = 0;
	new_od_filter -> end = 0;

	new_opendialog -> mode = mode;
	new_opendialog -> procinfo = proc_info;
	new_opendialog -> com_area_name =(char*) sz_com_area_name;
	new_opendialog -> com_area = 0;
	new_opendialog -> opendir_path = plugin_path;
	new_opendialog -> dir_default_path =(char*)  sz_dir_default_path;
	new_opendialog -> start_path = (char *)sz_start_path;
	new_opendialog -> draw_window = &fake_on_redraw;
	new_opendialog -> status = 0;
	new_opendialog -> openfile_path = openfile_path;
	new_opendialog -> filename_area = filename_area;
	new_opendialog -> filter_area = new_od_filter;
	new_opendialog -> x_size = x_size;
	new_opendialog -> x_start = tlx;
	new_opendialog -> y_size = y_size;
	new_opendialog -> y_start = tly;


	return new_opendialog;
}