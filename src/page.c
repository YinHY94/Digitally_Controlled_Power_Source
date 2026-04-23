#include "page.h"
#include <stddef.h>
#include "oled.h"
#include "output_control.h"

page* current_page=NULL;




void page_init(){
    main_menu_page_init();
    constant_votage_page_init();
    constant_current_page_init();
    constant_power_page_init();
    input_page_init();
    current_page=&main_menu_page;
};

void route_to_menu(){
    Output_Stop();
	current_page=&main_menu_page;
};

void set_data(){
    if(output_state==0){
        input_page.parent=current_page;
        current_page=&input_page;
    }
}

