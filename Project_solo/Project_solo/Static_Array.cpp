#include "VD.h"
static int count = 0, tempt = 0;
static bool tail1 = false, menu_linkedlist = false, show_menu_add = false, txtinp = false, btn_map = false, cancel_menu = false, show_menu_add_del;
static bool run_step = false, back = false;
coordinates state_btn_arr[50];
static lan_dau check_1st_time;
std::map<std::string, coordinates> state_btn_arr_map;
static std::vector<Uint32*>pixels_stage(1);
static int number_coorbtn = 1;
static std::string add_position;
std::vector<coordinates> static_array(1000);
std::map<std::string, int> speed = {
    {"fast", 20},
    {"low", 60}
}; 
static std::string speed_type = "low";
void static save_state_btn_arr(int x_pos, int y_pos, int width_rec, int height_rec, std::string name)
{
    state_btn_arr[number_coorbtn].x_begin = x_pos;
    state_btn_arr[number_coorbtn].x_end = x_pos + width_rec;
    state_btn_arr[number_coorbtn].y_begin = y_pos;
    state_btn_arr[number_coorbtn].y_end = y_pos + height_rec;
    state_btn_arr[number_coorbtn].nameID = name;
}
void static save_state_btn_arr_map(int x_pos, int y_pos, int width_rec, int height_rec, std::string name)
{
    state_btn_arr_map[name].x_begin = x_pos;
    state_btn_arr_map[name].x_end = x_pos + width_rec;
    state_btn_arr_map[name].y_begin = y_pos;
    state_btn_arr_map[name].y_end = y_pos + height_rec;
}
void static update_vector(int i, int number_node, bool del, bool insert, std::string value) {
    int sgn = 0;
    if (del)  sgn = -1;
    else  sgn = 1;
    if (del)
    {
        static_array.erase(static_array.begin() + i);
        coordinates new_element = {};
        static_array.push_back(new_element);
    }
    if (insert) {
        coordinates newElement = { static_array[i - 1].x_begin, static_array[i - 1].x_end,static_array[i - 1].y_begin, static_array[i - 1].y_end,value };
        static_array.insert(static_array.begin() + i, newElement);
    }
    for (; i <= number_node; i++) {
        static_array[i].x_begin += sgn * 100;
        static_array[i].x_end += sgn * 100;
    }
}
void Game::loop_node_array_insert(int pos_begin, int pos_end, std::string task, bool del_text) {
    int i = number_node;
    int x=static_array[number_node].x_end;
    drawRec(x, 50, 100, 45, true, static_array[number_node].nameID, 23, "Blue");
    if (!del_text) 
    {
        while (true) {
            SDL_Rect rect = { x,50,100,45 };
            SDL_SetRenderDrawColor(renderer, 255, 165, 0, 0); //3 channels of color
            SDL_RenderDrawRect(renderer, &rect);
            SDL_RenderPresent(renderer);
            x -= 100;
            SDL_Delay(speed[speed_type] + (speed[speed_type] * 6));
            if (number_node!=2)
            {
                drawRec(static_array[i].x_begin, 50, 100, 45, true, static_array[i - 1].nameID, 23, "Blue");
                draw_bound_rec(static_array[i].x_begin, 50, 100, 45, "Orange");
            }
            i--;
            if (number_node == 2)
            {
                if (i + 1 == pos_begin - 1) break; //means i = 1
            }
            else if (i == pos_begin-1) 
                break;
            SDL_Delay(speed[speed_type] + (speed[speed_type] * 6));

        }
    }
}
void Game::loop_node_array_del(int pos_begin, int pos_end)
{
    int i = pos_begin;
    int x = static_array[pos_begin].x_begin;
    while (true)
    {
        SDL_Rect rect = { x,50,100,45 };
        SDL_SetRenderDrawColor(renderer, 255, 165, 0, 0); //3 channels of color
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderPresent(renderer);
        SDL_Delay(speed[speed_type] + (speed[speed_type] * 6));
        if (number_node != 2)
        {
            drawRec(static_array[i].x_begin, 50, 100, 45, true, static_array[i + 1].nameID, 23, "Blue");
            draw_bound_rec(static_array[i].x_begin, 50, 100, 45, "Orange");
        }
        x += 100;
        i++;
        if (number_node == 2)
        {
            if (i + 1 == pos_begin - 1) break; //means i = 1
        }
        else if (i == number_node)
            break;
        SDL_Delay(speed[speed_type] + (speed[speed_type] * 6));
    }
}
void Game::insert_array(std::string value, int pos)
{
    loop_node_array_insert(pos+1, number_node, "", false);
    SDL_Delay(speed[speed_type] + (speed[speed_type] * 6));
    number_node++;
    //Set line color to black and rec color to blue
    int dem = 1;
    int x = 50;
    while (true) {
        draw_bound_rec(x, 50, 100, 45, "Black");
        dem++;
        if (dem == number_node + 1) break;
        x += 100;
    }
    for (int i = number_node; i >= pos+1; i--)
        static_array[i].nameID = static_array[i - 1].nameID;
    update_vector(number_node, number_node, false, true, static_array[number_node].nameID);
    drawRec(static_array[number_node - 1].x_begin, 95, 100, 45, false, "", 0, "White");
    draw_bound_rec(static_array[pos].x_begin, 50, 100, 45, "Orange");
    SDL_Delay(speed[speed_type] + (speed[speed_type] * 5));
    drawRec(static_array[pos].x_begin, 50, 100, 45, true, value, 23, "Blue");
    static_array[pos].nameID = value;
    draw_bound_rec(static_array[pos].x_begin, 50, 100, 45, "Orange");
    SDL_Delay(speed[speed_type] + (speed[speed_type] * 6));
    draw_bound_rec(static_array[pos].x_begin, 50, 100, 45, "Black");
}
void Game::insert_last_array(std::string value)
{
    int speed2 = speed[speed_type] + 150;
    number_node++;
    static_array[number_node] = { static_array[number_node-1].x_end,static_array[number_node-1].x_end+100,50,50,value};
    draw_bound_rec(static_array[number_node].x_begin, 50, 100, 45, "Orange");
    drawRec(static_array[number_node].x_begin, 50, 100, 45,true, static_array[number_node].nameID,23,"Blue");
    draw_bound_rec(static_array[number_node].x_begin, 50, 100, 45, "Orange");
    SDL_Delay(speed2+900);
    draw_bound_rec(static_array[number_node].x_begin, 50, 100, 45, "Black");

}


void Game::random_data_array() {
    static_array.clear();
    static_array.resize(11);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    drawRec(50, 50, 1600, 80,false,"",0,"White");
    txtinp = true;
    int random_value_node;
    edge.x = 50; edge.y = 50;
    menu_linkedlist = true;
    for (int j = 1; j <= 8; j++) {
        number_node = rand() % 9 + 2;
        makeRec(50, 50, 1600, 80, "", 0, "White", false, false, false);
        for (int i = 1; i <= number_node; i++) {
            random_value_node = rand() % 100 + 1;
            if (i == number_node) tail1 = true;
            stack(std::to_string(random_value_node).c_str(), i);
           tail1 = false;
        }
        edge.x = 50;
        edge.y = 50;
        SDL_Delay(70);
    }
    SDL_RenderPresent(renderer);
}
void Game::handleEvents_array() {
    SDL_Event event;
    SDL_PollEvent(&event);  
    txtinp = false;
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_MOUSEBUTTONDOWN:
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        if (show_menu_add && (mouseX >= 685 || mouseX <= 200 || mouseY >= 571 || mouseY <= 535))
        {
            show_menu_add = false;
            drawRec(200, 500, 500, 152, false, "", 0, "White");
            break;
        }
        for (int i = 1; i <= number_coorbtn + number_node; i++)
        {
            if ((mouseX >= state_btn_arr[i].x_begin && mouseX <= state_btn_arr[i].x_end &&
                mouseY >= state_btn_arr[i].y_begin && mouseY <= state_btn_arr[i].y_end) || ((i <= number_node) && ((mouseX >= static_array[i].x_begin && mouseX <= static_array[i].x_end &&
                    mouseY >= static_array[i].y_begin && mouseY <= static_array[i].y_end))))
            {
                if ((i <= number_node) && ((mouseX >= static_array[i].x_begin && mouseX <= static_array[i].x_end && //Edit data
                    mouseY >= static_array[i].y_begin && mouseY <= static_array[i].y_end))) //Edit value of linked list
                {
                    std::string current_value = static_array[i].nameID;
                    drawRec(static_array[i].x_begin, 50, 100, 45, false, "", 0, "Blue");
                    makeLine(static_array[i].x_begin + 5, 60, static_array[i].x_begin + 5, 85, "White");
                    std::string text_edit = "";
                    SDL_StartTextInput;
                    while (true) 
                    {
                        SDL_Event evt;
                        SDL_PollEvent(&evt);
                        if (evt.type == SDL_TEXTINPUT)
                            if (text_edit.length() <= 3 && isdigit(evt.text.text[0]))
                            {
                                text_edit += evt.text.text;
                                printText(23, 255, 255, 255, text_edit, static_array[i].x_begin + 10, 60, 0, 0);
                            }
                        if (evt.type == SDL_KEYDOWN) {
                            if (evt.key.keysym.sym == SDLK_BACKSPACE)
                                if (text_edit.length() > 0)
                                {
                                    txtinp = false;
                                    text_edit.pop_back();
                                    makeRec(static_array[i].x_begin, 50, 100, 45, text_edit, 23, "Blue", false, false, true);
                                    printText(23, 255, 255, 255, text_edit, static_array[i].x_begin + 10, 60, 0, 0);
                                    makeLine(static_array[i].x_begin + 5, 60, static_array[i].x_begin + 5, 85, "White");
                                }
                            if (evt.key.keysym.sym == SDLK_KP_ENTER || evt.key.keysym.sym == SDLK_RETURN)
                            {
                                if (text_edit.length() > 0) 
                                {
                                    txtinp = false;
                                    makeRec(static_array[i].x_begin, 50, 100, 45, text_edit, 23, "Blue", false, false, true);
                                    draw_bound_rec(static_array[i].x_begin, 50, 100, 45, "Orange");
                                    SDL_Delay(speed[speed_type] + (speed[speed_type] * 6));
                                    draw_bound_rec(static_array[i].x_begin, 50, 100, 45, "Black");

                                    static_array[i].nameID = text_edit.c_str();
                                    break;
                                }
                                makeRec(static_array[i].x_begin, 50, 100, 45, current_value, 23, "Blue", false, false, true);
                                break;
                            }
                        }
                        if (evt.type == SDL_MOUSEBUTTONDOWN) {
                            makeRec(static_array[i].x_begin, 50, 100, 45, current_value, 23, "Blue", false, false, true);
                            break;
                        }
                    }
                    break;
                } 
                if (state_btn_arr[i].nameID == "Random Data") {
                    random_data_stack(); break;
                }
                if (state_btn_arr[i].nameID == "Add")
                { //insert data 
                    makeRec(state_btn_arr[i].x_end + 2, state_btn_arr[i].y_begin, 150, 32, "Insert to the first", 19, "Green", check_1st_time.menu_add, check_1st_time.menu_add, true);
                    makeRec(state_btn_arr_map["Insert to the first"].x_end + 2, state_btn_arr_map["Insert to the first"].y_begin, 180, 32, "Insert to the middle", 19, "Green", check_1st_time.menu_add, check_1st_time.menu_add, true);
                    makeRec(state_btn_arr_map["Insert to the middle"].x_end + 2, state_btn_arr_map["Insert to the middle"].y_begin, 150, 32, "Insert to the last", 19, "Green", check_1st_time.menu_add, check_1st_time.menu_add, true);
                    check_1st_time.menu_add = false;
                    btn_map = false;
                    show_menu_add = true;
                    break;
                }
                if (show_menu_add && (state_btn_arr[i].nameID == "Insert to the first" || state_btn_arr[i].nameID == "Insert to the middle" || state_btn_arr[i].nameID == "Insert to the last"))
                {
                    makeRec(state_btn_arr[i].x_begin, state_btn_arr[i].y_end, 150, 32, "Vertex = ", 19, "Green", false, true, true);
                    //create input box
                    makeRec(state_btn_arr[i].x_end - 80, state_btn_arr[i].y_end + 5, 40, 25, "input_box", 19, "Black", false, true, false);
                    if (state_btn_arr[i].nameID == "Insert to the first") add_position = "first";
                    if (state_btn_arr[i].nameID == "Insert to the middle") add_position = "middle";
                    if (state_btn_arr[i].nameID == "Insert to the last") add_position = "last";
                    makeLine(state_btn_arr_map["input_box"].x_begin + 2, state_btn_arr_map["input_box"].y_begin + 2, state_btn_arr_map["input_box"].x_begin + 2, state_btn_arr_map["input_box"].y_end - 2, "White");
                    std::string inputText = "";
                    SDL_StartTextInput;
                    while (true)
                    {
                        SDL_Event e;
                        SDL_PollEvent(&e);
                        if (e.type == SDL_TEXTINPUT) {
                            if (inputText.length() <= 3)
                                if (isdigit(e.text.text[0])) {
                                    inputText += e.text.text;
                                    printText(15, 255, 255, 255, inputText, state_btn_arr_map["input_box"].x_begin + 2, state_btn_arr_map["input_box"].y_begin + 2, 0, 0);
                                    e.type = 0;
                                }
                        }
                        else if (e.type == SDL_KEYDOWN)
                        {
                            if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0) {
                                inputText.pop_back();
                                makeRec(state_btn_arr_map["input_box"].x_begin, state_btn_arr_map["input_box"].y_begin, 40, 25, inputText, 15, "Black", false, false, true);
                            }
                            if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_KP_ENTER) {
                                txtinp = true;
                                makeRec(state_btn_arr_map["Insert to the first"].x_begin, state_btn_arr_map["Insert to the first"].y_begin,
                                    state_btn_arr_map["Insert to the last"].x_end, state_btn_arr_map["input_box"].y_end, " ", 0, "White", false, false, false);
                                if (inputText.length() > 0 && number_node < 10) 
                                {
                                    int buttonid = messbox("", "Choose how to run", 2, "Run step by step", "Run at once");
                                    if (buttonid == 0) { //run at once
                                        if (add_position == "first")
                                            insert_array(inputText, 1);
                                        if (add_position == "last")
                                            insert_last_array(inputText);
                                        if (add_position == "middle")
                                            insert_array(inputText, number_node / 2 + 1);
                                    }
                                    else { //run step by step
                                        if (add_position == "first")
                                            insert_first_step(inputText, 1, static_array);
                                        if (add_position == "middle")
                                            insert_middle_step(inputText, 1);
                                        if (add_position == "last")
                                            insert_last_step(inputText, 1, static_array, 50);
                                    }
                                }
                                show_menu_add = false;
                                drawRec(static_array[2].x_begin, 95, static_array[number_node-1].x_end-static_array[2].x_begin, 50, false, "", 0, "White");
                                break;
                            }
                        }
                        if (e.type == SDL_MOUSEBUTTONDOWN)
                        {
                            show_menu_add = false;
                            drawRec(200, 500, 500, 152, false, "", 0, "White");
                            break;
                        }
                        SDL_RenderPresent(renderer);
                        makeLine(state_btn_arr_map["input_box"].x_begin + 2, state_btn_arr_map["input_box"].y_begin + 2, state_btn_arr_map["input_box"].x_begin + 2, state_btn_arr_map["input_box"].y_end - 2, "White");
                    }
                    // SDL_StopTextInput();
                    break;
                }
                if (state_btn_arr[i].nameID == "Search")
                {
                    makeRec(state_btn_arr[i].x_end + 2, state_btn_arr[i].y_begin, 150, 32, "Vertex = ", 18, "Green", false, false, true);
                    makeLine(state_btn_arr[i].x_end + 152 - 70, state_btn_arr[i].y_begin + 10, state_btn_arr[i].x_end + 152 - 70, state_btn_arr[i].y_end - 10, "White");
                    std::string text_find = "";
                    SDL_StartTextInput;
                    while (true) {
                        SDL_Event evt;
                        SDL_PollEvent(&evt);
                        if (evt.type == SDL_TEXTINPUT)
                            if (text_find.length() <= 3 && isdigit(evt.text.text[0]))
                            {
                                text_find += evt.text.text;
                                printText(18, 255, 255, 255, text_find, state_btn_arr[i].x_end + 152 - 68, state_btn_arr[i].y_begin + 10, 0, 0);
                            }
                        if (evt.type == SDL_KEYDOWN) {
                            if (evt.key.keysym.sym == SDLK_BACKSPACE)
                                if (text_find.length() > 0)
                                {
                                    txtinp = false;
                                    text_find.pop_back();
                                    makeRec(state_btn_arr[i].x_end + 2, state_btn_arr[i].y_begin, 150, 32, "Vertex = ", 18, "Green", false, false, true);
                                    printText(23, 255, 255, 255, text_find, state_btn_arr[i].x_end + 152 - 68, state_btn_arr[i].y_begin + 20, 0, 0);
                                    makeLine(state_btn_arr[i].x_end + 152 - 70, state_btn_arr[i].y_begin + 10, state_btn_arr[i].x_end + 152 - 70, state_btn_arr[i].y_end - 10, "White");
                                }
                            if (evt.key.keysym.sym == SDLK_KP_ENTER || evt.key.keysym.sym == SDLK_RETURN)
                            {
                                makeRec(state_btn_arr[i].x_end + 2, state_btn_arr[i].y_begin, 150, 32, "Vertex = ", 18, "White", false, false, true);
                                break;
                            }
                        }
                        if (evt.type == SDL_MOUSEBUTTONDOWN) {
                            makeRec(state_btn_arr[i].x_end + 2, state_btn_arr[i].y_begin, 150, 32, "Vertex = ", 18, "White", false, false, true);
                            cancel_menu = true;
                            break;
                        }
                    }
                    if (!cancel_menu) {
                        int buttonid = messbox("", "Choose how to run", 2, "Run step by step", "Run at once");
                        if (buttonid == 0)
                        { //run at once
                            int x = 50;
                            int i = 1;
                            int width = 1500;
                            while (true) {
                                SDL_Rect rect = { x,50,100,45 };
                                SDL_SetRenderDrawColor(renderer, 255, 165, 0, 0); //3 channels of color
                                SDL_RenderDrawRect(renderer, &rect);
                                SDL_RenderPresent(renderer);
                                if (i == number_node || text_find == static_array[i].nameID) break;
                                x += 100;
                                i++;
                                SDL_RenderPresent(renderer);
                                SDL_Delay(speed[speed_type] + (speed[speed_type] * 6));
                            }
                            if (i == number_node && text_find != static_array[i].nameID)
                                messbox("", "NOT FOUND :((", 1, "", "Ok");
                            SDL_Delay(800);
                            int dem = 1;
                            x = 50;
                            while (true) {
                                draw_bound_rec(x, 50, 100, 45, "Black");
                                dem++;
                                if (dem == number_node + 1) break;
                                x += 100;
                            }
                            break;
                        }
                        else
                            if (buttonid == 1) {
                                search_Step(text_find, 1, 50, 1, static_array);
                            }
                    }
                    cancel_menu = false;

                }
                ///////////////////////////////////////////Delete data
                if (state_btn_arr[i].nameID == "Delete")
                {
                    makeRec(state_btn_arr[i].x_end + 2, state_btn_arr[i].y_begin, 150, 32, "Delete at the first", 18, "Green", check_1st_time.menu_del, check_1st_time.menu_del, true);
                    makeRec(state_btn_arr_map["Delete at the first"].x_end + 2, state_btn_arr[i].y_begin, 170, 32, "Delete at the middle", 18, "Green", check_1st_time.menu_del, check_1st_time.menu_del, true);
                    makeRec(state_btn_arr_map["Delete at the middle"].x_end + 2, state_btn_arr[i].y_begin, 150, 32, "Delete at the last", 18, "Green", check_1st_time.menu_del, check_1st_time.menu_del, true);
                    check_1st_time.menu_del = false;
                    show_menu_add_del = true;
                    tempt = i;
                    break;
                }
                else
                    if (show_menu_add_del && (state_btn_arr[i].nameID == "Delete at the first" || state_btn_arr[i].nameID == "Delete at the middle" || state_btn_arr[i].nameID == "Delete at the last"))
                    {

                        show_menu_add_del = false;
                        drawRec(200, state_btn_arr_map["Delete"].y_begin, state_btn_arr_map["Delete at the last"].x_end, 50, false, "", 0, "White");
                        if (number_node >= 2)
                        {
                            int buttonid = messbox("", "Choose how to run", 2, "Run step by step", "Run at once");
                            if (buttonid == 0)
                            { //run at once
                                if (state_btn_arr[i].nameID == "Delete at the first")
                                {
                                    loop_node_array_del(1, number_node-1);
                                    SDL_Delay(speed[speed_type]+(speed[speed_type]*6));
                                    drawRec(static_array[number_node].x_begin, 50, 100, 45, false, "", 0, "Blue");
                                    draw_bound_rec(static_array[number_node].x_begin, 50, 100, 45, "Black");
                                    //Set line color to black and rec color to blue
                                    int dem = 1;
                                    int x = 50;
                                    while (true) {
                                        draw_bound_rec(x, 50, 100, 45, "Black");
                                        dem++;
                                        if (dem == number_node + 1) break;
                                        x += 100;
                                    }
                                    number_node--;
                                    for (int i = 1; i <= number_node; i++)
                                    {
                                        static_array[i].nameID = static_array[i + 1].nameID;
                                    }
                                }
                                else if (number_node >= 3)
                                {
                                    if (state_btn_arr[i].nameID == "Delete at the middle")
                                    {
                                        loop_node_array_del(number_node/2+1, number_node - 1);
                                        SDL_Delay(speed[speed_type] + (speed[speed_type] * 6));
                                        drawRec(static_array[number_node].x_begin, 50, 100, 45, false, "", 0, "Blue");
                                        draw_bound_rec(static_array[number_node].x_begin, 50, 100, 45, "Black");
                                        //Set line color to black and rec color to blue
                                        int dem = number_node/2+1;
                                        int x = static_array[number_node/2+1].x_begin;
                                        while (true) {
                                            draw_bound_rec(x, 50, 100, 45, "Black");
                                            dem++;
                                            if (dem == number_node + 1) break;
                                            x += 100;
                                        }
                                        number_node--;
                                        for (int i = 1; i <= number_node; i++)
                                        {
                                            static_array[i].nameID = static_array[i + 1].nameID;
                                        }
                                    }
                                    if (state_btn_arr[i].nameID == "Delete at the last")
                                    {
                                        drawRec(static_array[number_node].x_begin, 50, 100, 45, false, "", 0, "Blue");
                                        draw_bound_rec(static_array[number_node].x_begin, 50, 100, 45, "Orange");
                                        SDL_Delay(speed[speed_type] + (speed[speed_type] * 6));
                                        draw_bound_rec(static_array[number_node].x_begin, 50, 100, 45, "Black");
                                        number_node--;

                                    }
                                }
                            }
                            else
                            { //run step by step
                                if (state_btn_arr[i].nameID == "Delete at the first")
                                    delete_first_step(1, static_array);
                                if (state_btn_arr[i].nameID == "Delete at the middle")
                                    delete_middle_step(1);
                                if (state_btn_arr[i].nameID == "Delete at the last")
                                    delete_last_step(1, static_array);
                            }
                        }
                        if (number_node - 1 == 0)
                        {
                            number_node--;
                            draw_bound_rec(50, 50, 100, 45, "Orange");
                            SDL_Delay(300);
                            drawRec(50, 50, 100, 150, false, "", 22, "White");
                            static_array[1] = {};

                        }
                        drawRec(static_array[number_node+1].x_begin, 95, 100,50, false, "", 0, "White");
                        break;
                    }
            }
        }
            if (show_menu_add_del == true)
            {
                if (state_btn_arr[tempt].nameID != "Delete")
                {
                    drawRec(200, 500, 500, 153, false, "", 0, "White");
                    show_menu_add_del = false;
                    tempt = 0;
                }
                else tempt = 0;
            }
    default:
        break;
    }
}
void Game::render_array(std::vector<coordinates> linkedlist) {
    //SDL_RenderClear(renderer); // Clear the screen
    static_array = linkedlist;
    if (count == 0) {
        for (int i = 1; i <= number_node; i++) {
            if (i == number_node)
                tail1 = true;
            Static_Array(static_array[i].nameID, i);
            tail1 = false;
        }
        count = 1;
    }
    SDL_RenderPresent(renderer); // Show the rendered image on the screen
}
void Game::makeRec(int x_pos, int y_pos, int width_rec, int height_rec, std::string name, int textsize, std::string name_color, bool save_state, bool btn_map, bool txtinp) {
    //draw rectangle
    SDL_Rect rect = { x_pos, y_pos,width_rec,height_rec };
    SDL_SetRenderDrawColor(renderer, color[name_color][0], color[name_color][1], color[name_color][2], 0); //3 channels of color
    SDL_RenderFillRect(renderer, &rect);
    //name of buttn
    if (txtinp)
        printText(textsize, 255, 255, 255, name.c_str(), rect.x + 10, rect.y + 10, 0, 0);
    if (save_state) {
        state_btn_arr[number_coorbtn].x_begin = x_pos;
        state_btn_arr[number_coorbtn].x_end = x_pos + width_rec;
        state_btn_arr[number_coorbtn].y_begin = y_pos;
        state_btn_arr[number_coorbtn].y_end = y_pos + height_rec;
        state_btn_arr[number_coorbtn].nameID = name;
        number_coorbtn++;
    }
    if (btn_map) {
        state_btn_arr_map[name].x_begin = x_pos;
        state_btn_arr_map[name].x_end = x_pos + width_rec;
        state_btn_arr_map[name].y_begin = y_pos;
        state_btn_arr_map[name].y_end = y_pos + height_rec;
    }
    SDL_RenderPresent(renderer); // Show the rendered image on the screen

}

void Game::Static_Array(std::string value, int current_node)
{
    SDL_Rect rect = { edge.x, edge.y, 100,45 };
    SDL_SetRenderDrawColor(renderer, 100, 149, 237, 0); //blue
    SDL_RenderFillRect(renderer, &rect);
    draw_bound_rec(edge.x, edge.y, 100, 45, "Black");
    // Draw the text texture inside the rectangle
    printText(23, 255, 255, 255, value.c_str(), rect.x + 10, rect.y + 10, 0, 0);
    //save liked list
    static_array[current_node].x_begin = rect.x; static_array[current_node].x_end = rect.x + rect.w;
    static_array[current_node].y_begin = rect.y; static_array[current_node].y_end = rect.y + 45;
    static_array[current_node].nameID = value.c_str();
    // Draw line
    if (!tail1) {
        edge.x = rect.x + rect.w ;
        edge.y = rect.y;
    }
    if (tail1) {
        state_btn_arr_map["Tail"].x_begin = rect.x;
        state_btn_arr_map["Tail"].x_end = rect.x + 100;
        state_btn_arr_map["Tail"].y_begin = 50;
        state_btn_arr_map["Tail"].y_end = 95;
    }
    btn_map = true;
    if (!menu_linkedlist)
    {
        drawRec(50, 500, 150, 38, true, "Random Data", 20, "Green");
        save_state_btn_arr(50, 500, 150, 38, "Random Data");
        save_state_btn_arr_map(50, 500, 150, 38, "Random Data");
        number_coorbtn++;
        drawRec(50, state_btn_arr[number_coorbtn - 1].y_end + 2, 150, 38, true, "Add", 20, "Green");
        save_state_btn_arr(50, state_btn_arr[number_coorbtn - 1].y_end + 2, 150, 38, "Add");
        save_state_btn_arr_map(50, state_btn_arr[number_coorbtn - 1].y_end + 2, 150, 38, "Add");
        number_coorbtn++;
        drawRec(50, state_btn_arr[number_coorbtn - 1].y_end + 2, 150, 38, true, "Delete", 20, "Green");
        save_state_btn_arr(50, state_btn_arr[number_coorbtn - 1].y_end + 2, 150, 38, "Delete");
        save_state_btn_arr_map(50, state_btn_arr[number_coorbtn - 1].y_end + 2, 150, 38, "Delete");
        number_coorbtn++;
        drawRec(50, state_btn_arr[number_coorbtn - 1].y_end + 2, 150, 38, true, "Search", 20, "Green");
        save_state_btn_arr(50, state_btn_arr[number_coorbtn - 1].y_end + 2, 150, 38, "Search");
        save_state_btn_arr_map(50, state_btn_arr[number_coorbtn - 1].y_end + 2, 150, 38, "Search");
        number_coorbtn++;
        menu_linkedlist = true;
    }
}