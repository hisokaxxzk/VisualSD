#include "VD.h"
static int count = 0, tempt = 0;
static bool tail1 = false, menu_linkedlist = false, show_menu_add = false, txtinp = false, btn_map = false, cancel_menu = false, show_menu_add_del;
static bool run_step = false, back = false;
coordinates state_btn_dynamic_arr[50];
static lan_dau check_1st_time;
std::map<std::string, coordinates> state_btn_dynamic_arr_map;
static std::vector<Uint32*>pixels_stage(1);
static int number_coorbtn = 1;
static std::string add_position;
//coordinates* dynamic_array = new coordinates[1000];
std::vector<coordinates> dynamic_array(1000);
static std::string speed_type = "low";
void Game::search_Step_dynamic_array(std::string value, int stage, int x, int i, std::vector<coordinates>& linked_list)
{
    if (stage == 1) {
        if (!back)
        {
            i = 1;
            x = 50;
        }
        while (true)
        {
            SDL_Event e;
            SDL_PollEvent(&e);
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_RIGHT)
                {
                    if (x == linked_list[number_node].x_begin || linked_list[i].nameID == value) {
                        stage++;
                        back = false;
                        break;
                    }
                    draw_bound_rec(x, 50, 100, 45, "Orange");
                    x += 100;
                    i++;
                }
                if (e.key.keysym.sym == SDLK_LEFT)
                {
                    if (x != 50) {
                        i--;
                        x -= 100;
                        draw_bound_rec(x, 50, 100, 45, "Black");
                    }
                }
            }

        }
    }
    if (stage == 2) {
        if (!back)
        {
            int width = 1500;
            int height = 300;
            SDL_Rect section = { 50,50,width,height };
            Uint32* pixels = new Uint32[width * height];
            SDL_RenderReadPixels(renderer, &section, SDL_PIXELFORMAT_ARGB8888, pixels, width * sizeof(Uint32));
            pixels_stage.push_back(pixels);
            draw_bound_rec(x, 50, 100, 45, "Orange");
        }
        while (true) {
            SDL_Event e;
            SDL_PollEvent(&e);
            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_RIGHT)
                {
                    int t = 50;
                    int dem = 1;
                    while (true) {
                        draw_bound_rec(t, 50, 100, 45, "Black");
                        dem++;
                        if (dem == number_node + 1) break;
                        t += 100;


                    }
                    if (i == number_node && dynamic_array[number_node].nameID != value)
                        messbox("", "Not Found", 1, "", "OK");
                    else messbox("", "Found at index = " + std::to_string(i), 1, "", "OK");
                    pixels_stage.clear();
                    break;
                }
                if (e.key.keysym.sym == SDLK_LEFT)
                {
                    back = true;
                    previous_stage_array(pixels_stage.back(), stage, 1500);
                    search_Step_array(value, stage, x, i, linked_list);
                    break;
                }
            }
        }
    }
}
void Game::delete_step_dynamic_array(int stage, std::vector<coordinates>& array, int x, int pos_begin, int pos_end)
{
    if (stage == 1) {
        x--;
        while (true)
        {
            SDL_Event e;
            SDL_PollEvent(&e);
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_RIGHT)
                {
                    x++;
                    if (x == number_node)
                    {
                        stage++;
                        back = false;
                        break;
                    }
                    drawRec(array[x].x_begin, 50, 100, 45, true, array[x + 1].nameID, 23, "Blue");
                    draw_bound_rec(array[x].x_begin, 50, 100, 45, "Orange");
                }
                if (e.key.keysym.sym == SDLK_LEFT)
                {
                    if (x != pos_begin - 1)
                    {
                        drawRec(array[x].x_begin, 50, 100, 45, true, array[x].nameID, 23, "Blue");
                        draw_bound_rec(array[x].x_begin, 50, 100, 45, "Black");
                        x--;
                    }
                }
            }

        }
    }
    if (stage == 2) {
        if (!back) {
            //copy
            int width = 1500;
            int height = 300;
            SDL_Rect section = { 50,50,width,height };
            Uint32* pixels = new Uint32[width * height];
            SDL_RenderReadPixels(renderer, &section, SDL_PIXELFORMAT_ARGB8888, pixels, width * sizeof(Uint32));
            pixels_stage.push_back(pixels);
            drawRec(array[number_node].x_begin, 50, 100, 45, true, "", 23, "White");
        }
    }
    while (true)
    {
        SDL_Event e;
        SDL_PollEvent(&e);
        if (e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.sym == SDLK_RIGHT)
            {
                int dem = 1;
                int t = 50;
                while (true)
                {
                    draw_bound_rec(t, 50, 100, 45, "Black");
                    dem++;
                    if (dem == number_node) break;
                    t += 100;
                }
                number_node--;
                for (int i = pos_begin; i <= pos_end + 1; i++)
                    array[i].nameID = array[i + 1].nameID;
                messbox("", "Finish", 1, "", "OK");

                break;
            }
            if (e.key.keysym.sym == SDLK_LEFT)
            {
                back = true;
                previous_stage_array(pixels_stage.back(), stage, 1500);
                delete_step_array(stage, array, x, pos_begin, pos_end);
                break;
            }
        }
    }
}
void  save_state_btn_dynamic_arr(int x_pos, int y_pos, int width_rec, int height_rec, std::string name)
{
    state_btn_dynamic_arr[number_coorbtn].x_begin = x_pos;
    state_btn_dynamic_arr[number_coorbtn].x_end = x_pos + width_rec;
    state_btn_dynamic_arr[number_coorbtn].y_begin = y_pos;
    state_btn_dynamic_arr[number_coorbtn].y_end = y_pos + height_rec;
    state_btn_dynamic_arr[number_coorbtn].nameID = name;
}
void  save_state_btn_dynamic_arr_map(int x_pos, int y_pos, int width_rec, int height_rec, std::string name)
{
    state_btn_dynamic_arr_map[name].x_begin = x_pos;
    state_btn_dynamic_arr_map[name].x_end = x_pos + width_rec;
    state_btn_dynamic_arr_map[name].y_begin = y_pos;
    state_btn_dynamic_arr_map[name].y_end = y_pos + height_rec;
}
void Game::random_data_dynamic_array() {
    dynamic_array.clear();
    dynamic_array.resize(1000);
    //coordinates* dynamic_array = new coordinates[1000];
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    drawRec(50, 50, 1600, 80, false, "", 0, "White");
    txtinp = true;
    int random_value_node;
    edge.x = 50; edge.y = 50;
    menu_linkedlist = true;
    for (int j = 1; j <= 8; j++) {
        number_node = rand() % 13 + 2;
        makeRec_dynamic(50, 50, 1600, 80, "", 0, "White", false, false, false);
        for (int i = 1; i <= 14; i++)
        {
            if (i <= number_node)
            {
                random_value_node = rand() % 100 + 1;
                Static_Array(std::to_string(random_value_node).c_str(), i);
            }
            else Static_Array("", i);

        }
        edge.x = 50;
        edge.y = 50;
        SDL_Delay(50);
    }
    SDL_RenderPresent(renderer);
}
void Game::loop_node_dynamic_array_del(int pos_begin, int pos_end)
{
    int i = pos_begin;
    int x = dynamic_array[pos_begin].x_begin;
    while (true)
    {
        SDL_Rect rect = { x,50,100,45 };
        SDL_SetRenderDrawColor(renderer, 255, 165, 0, 0); //3 channels of color
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderPresent(renderer);
        SDL_Delay(speed[speed_type] + (speed[speed_type] * 6));
        if (number_node != 2)
        {
            drawRec(dynamic_array[i].x_begin, 50, 100, 45, true, dynamic_array[i + 1].nameID, 23, "Blue");
            draw_bound_rec(dynamic_array[i].x_begin, 50, 100, 45, "Orange");
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

void Game::loop_node_dynamic_array_insert(int pos_begin, int pos_end, std::string task, bool del_text) {
    int i = number_node;
    int x = dynamic_array[number_node].x_end;
    drawRec(x, 50, 100, 45, true, dynamic_array[number_node].nameID, 23, "Blue");
    if (!del_text)
    {
        while (true) {
            SDL_Rect rect = { x,50,100,45 };
            SDL_SetRenderDrawColor(renderer, 255, 165, 0, 0); //3 channels of color
            SDL_RenderDrawRect(renderer, &rect);
            SDL_RenderPresent(renderer);
            x -= 100;
            SDL_Delay(speed[speed_type] + (speed[speed_type] * 6));
            if (number_node != 2)
            {
                drawRec(dynamic_array[i].x_begin, 50, 100, 45, true, dynamic_array[i - 1].nameID, 23, "Blue");
                draw_bound_rec(dynamic_array[i].x_begin, 50, 100, 45, "Orange");
            }
            i--;
            if (number_node == 2)
            {
                if (i + 1 == pos_begin - 1) break; //means i = 1
            }
            else if (i == pos_begin - 1)
                break;
            SDL_Delay(speed[speed_type] + (speed[speed_type] * 6));

        }
    }
}
void Game::insert_dynamic_array(std::string value, int pos)
{
    loop_node_dynamic_array_insert(pos + 1, number_node, "", false);
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
    for (int i = number_node; i >= pos + 1; i--)
        dynamic_array[i].nameID = dynamic_array[i - 1].nameID;
    drawRec(dynamic_array[number_node - 1].x_begin, 95, 100, 45, false, "", 0, "White");
    draw_bound_rec(dynamic_array[pos].x_begin, 50, 100, 45, "Orange");
    SDL_Delay(speed[speed_type] + (speed[speed_type] * 5));
    drawRec(dynamic_array[pos].x_begin, 50, 100, 45, true, value, 23, "Blue");
    dynamic_array[pos].nameID = value;
    draw_bound_rec(dynamic_array[pos].x_begin, 50, 100, 45, "Orange");
    SDL_Delay(speed[speed_type] + (speed[speed_type] * 6));
    draw_bound_rec(dynamic_array[pos].x_begin, 50, 100, 45, "Black");
}
void Game::handleEvents_dynamic_array() {
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
        for (int i = 1; i <= number_coorbtn + 15; i++)
        {
            if ((mouseX >= state_btn_dynamic_arr[i].x_begin && mouseX <= state_btn_dynamic_arr[i].x_end &&
                mouseY >= state_btn_dynamic_arr[i].y_begin && mouseY <= state_btn_dynamic_arr[i].y_end) || ((i <= 14) && ((mouseX >= dynamic_array[i].x_begin && mouseX <= dynamic_array[i].x_end &&
                    mouseY >= dynamic_array[i].y_begin && mouseY <= dynamic_array[i].y_end))))
            {
                if ((i <= 14) && ((mouseX >= dynamic_array[i].x_begin && mouseX <= dynamic_array[i].x_end && //Edit data
                    mouseY >= dynamic_array[i].y_begin && mouseY <= dynamic_array[i].y_end))) //Edit value of linked list
                {
                    std::string current_value = dynamic_array[i].nameID;
                    drawRec(dynamic_array[i].x_begin, 50, 100, 45, false, "", 0, "Blue");
                    makeLine(dynamic_array[i].x_begin + 5, 60, dynamic_array[i].x_begin + 5, 85, "White");
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
                                printText(23, 255, 255, 255, text_edit, dynamic_array[i].x_begin + 10, 60, 0, 0);
                            }
                        if (evt.type == SDL_KEYDOWN) {
                            if (evt.key.keysym.sym == SDLK_BACKSPACE)
                                if (text_edit.length() > 0)
                                {
                                    txtinp = false;
                                    text_edit.pop_back();
                                    makeRec_dynamic(dynamic_array[i].x_begin, 50, 100, 45, text_edit, 23, "Blue", false, false, true);
                                    printText(23, 255, 255, 255, text_edit, dynamic_array[i].x_begin + 10, 60, 0, 0);
                                    makeLine(dynamic_array[i].x_begin + 5, 60, dynamic_array[i].x_begin + 5, 85, "White");
                                }
                            if (evt.key.keysym.sym == SDLK_KP_ENTER || evt.key.keysym.sym == SDLK_RETURN)
                            {
                                if (text_edit.length() > 0)
                                {
                                    txtinp = false;
                                    makeRec_dynamic(dynamic_array[i].x_begin, 50, 100, 45, text_edit, 23, "Blue", false, false, true);
                                    draw_bound_rec(dynamic_array[i].x_begin, 50, 100, 45, "Orange");
                                    SDL_Delay(speed[speed_type] + (speed[speed_type] * 6));
                                    draw_bound_rec(dynamic_array[i].x_begin, 50, 100, 45, "Black");
                                    number_node = i;
                                    dynamic_array[i].nameID = text_edit.c_str();
                                    break;
                                }
                            }
                        }
                        if (evt.type == SDL_MOUSEBUTTONDOWN)
                        {
                            makeRec_dynamic(dynamic_array[i].x_begin, 50, 100, 45, current_value, 23, "Blue", false, false, true);
                            draw_bound_rec(dynamic_array[i].x_begin, 50, 100, 45, "Black");
                            break;
                        }
                    }
                    break;
                }
                if (state_btn_dynamic_arr[i].nameID == "Random Data") {
                    random_data_array(); break;
                }
                if (state_btn_dynamic_arr[i].nameID == "Add")
                { //insert data 
                    makeRec_dynamic(state_btn_dynamic_arr[i].x_end + 2, state_btn_dynamic_arr[i].y_begin, 150, 32, "Insert to the first", 19, "Green", check_1st_time.menu_add, check_1st_time.menu_add, true);
                    makeRec_dynamic(state_btn_dynamic_arr_map["Insert to the first"].x_end + 2, state_btn_dynamic_arr_map["Insert to the first"].y_begin, 180, 32, "Insert to the middle", 19, "Green", check_1st_time.menu_add, check_1st_time.menu_add, true);
                    makeRec_dynamic(state_btn_dynamic_arr_map["Insert to the middle"].x_end + 2, state_btn_dynamic_arr_map["Insert to the middle"].y_begin, 150, 32, "Insert to the last", 19, "Green", check_1st_time.menu_add, check_1st_time.menu_add, true);
                    check_1st_time.menu_add = false;
                    btn_map = false;
                    show_menu_add = true;
                    break;
                }
                if (show_menu_add && (state_btn_dynamic_arr[i].nameID == "Insert to the first" || state_btn_dynamic_arr[i].nameID == "Insert to the middle" || state_btn_dynamic_arr[i].nameID == "Insert to the last"))
                {
                    makeRec_dynamic(state_btn_dynamic_arr[i].x_begin, state_btn_dynamic_arr[i].y_end, 150, 32, "Vertex = ", 19, "Green", false, true, true);
                    //create input box
                    makeRec_dynamic(state_btn_dynamic_arr[i].x_end - 80, state_btn_dynamic_arr[i].y_end + 5, 40, 25, "input_box", 19, "Black", false, true, false);
                    if (state_btn_dynamic_arr[i].nameID == "Insert to the first") add_position = "first";
                    if (state_btn_dynamic_arr[i].nameID == "Insert to the middle") add_position = "middle";
                    if (state_btn_dynamic_arr[i].nameID == "Insert to the last") add_position = "last";
                    makeLine(state_btn_dynamic_arr_map["input_box"].x_begin + 2, state_btn_dynamic_arr_map["input_box"].y_begin + 2, state_btn_dynamic_arr_map["input_box"].x_begin + 2, state_btn_dynamic_arr_map["input_box"].y_end - 2, "White");
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
                                    printText(15, 255, 255, 255, inputText, state_btn_dynamic_arr_map["input_box"].x_begin + 2, state_btn_dynamic_arr_map["input_box"].y_begin + 2, 0, 0);
                                    e.type = 0;
                                }
                        }
                        else if (e.type == SDL_KEYDOWN)
                        {
                            if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0) {
                                inputText.pop_back();
                                makeRec_dynamic(state_btn_dynamic_arr_map["input_box"].x_begin, state_btn_dynamic_arr_map["input_box"].y_begin, 40, 25, inputText, 15, "Black", false, false, true);
                            }
                            if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_KP_ENTER) {
                                txtinp = true;
                                makeRec_dynamic(state_btn_dynamic_arr_map["Insert to the first"].x_begin, state_btn_dynamic_arr_map["Insert to the first"].y_begin,
                                    state_btn_dynamic_arr_map["Insert to the last"].x_end, state_btn_dynamic_arr_map["input_box"].y_end, " ", 0, "White", false, false, false);
                                if (inputText.length() > 0 && number_node < 14)
                                {
                                    int buttonid = messbox("", "Choose how to run", 2, "Run step by step", "Run at once");
                                    if (buttonid == 0) { //run at once
                                        if (add_position == "first")
                                            insert_dynamic_array(inputText, 1);
                                        if (add_position == "last")
                                        {
                                            int speed2 = speed[speed_type] + 150;
                                            number_node++;
                                            dynamic_array[number_node] = { dynamic_array[number_node - 1].x_end,dynamic_array[number_node - 1].x_end + 100,50,50,inputText };
                                            draw_bound_rec(dynamic_array[number_node].x_begin, 50, 100, 45, "Orange");
                                            drawRec(dynamic_array[number_node].x_begin, 50, 100, 45, true, dynamic_array[number_node].nameID, 23, "Blue");
                                            draw_bound_rec(dynamic_array[number_node].x_begin, 50, 100, 45, "Orange");
                                            SDL_Delay(speed2 + 900);
                                            draw_bound_rec(dynamic_array[number_node].x_begin, 50, 100, 45, "Black");
                                        }
                                        if (add_position == "middle")
                                            insert_dynamic_array(inputText, number_node / 2 + 1);
                                    }
                                    else { //run step by step
                                        if (add_position == "first")
                                            insert_step_array(inputText, 1, dynamic_array, number_node + 1, 1);
                                        if (add_position == "middle")
                                            insert_step_array(inputText, 1, dynamic_array, number_node + 1, number_node / 2 + 1);
                                        if (add_position == "last")
                                            insert_step_array(inputText, 1, dynamic_array, number_node + 1, number_node + 1);
                                    }
                                }
                                show_menu_add = false;
                                drawRec(dynamic_array[2].x_begin, 95, dynamic_array[number_node - 1].x_end - dynamic_array[2].x_begin, 50, false, "", 0, "White");
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
                        makeLine(state_btn_dynamic_arr_map["input_box"].x_begin + 2, state_btn_dynamic_arr_map["input_box"].y_begin + 2, state_btn_dynamic_arr_map["input_box"].x_begin + 2, state_btn_dynamic_arr_map["input_box"].y_end - 2, "White");
                    }
                    // SDL_StopTextInput();
                    break;
                }
                if (state_btn_dynamic_arr[i].nameID == "Search")
                {
                    makeRec_dynamic(state_btn_dynamic_arr[i].x_end + 2, state_btn_dynamic_arr[i].y_begin, 150, 32, "Vertex = ", 18, "Green", false, false, true);
                    makeLine(state_btn_dynamic_arr[i].x_end + 152 - 70, state_btn_dynamic_arr[i].y_begin + 10, state_btn_dynamic_arr[i].x_end + 152 - 70, state_btn_dynamic_arr[i].y_end - 10, "White");
                    std::string text_find = "";
                    SDL_StartTextInput;
                    while (true) {
                        SDL_Event evt;
                        SDL_PollEvent(&evt);
                        if (evt.type == SDL_TEXTINPUT)
                            if (text_find.length() <= 3 && isdigit(evt.text.text[0]))
                            {
                                text_find += evt.text.text;
                                printText(18, 255, 255, 255, text_find, state_btn_dynamic_arr[i].x_end + 152 - 68, state_btn_dynamic_arr[i].y_begin + 10, 0, 0);
                            }
                        if (evt.type == SDL_KEYDOWN) {
                            if (evt.key.keysym.sym == SDLK_BACKSPACE)
                                if (text_find.length() > 0)
                                {
                                    txtinp = false;
                                    text_find.pop_back();
                                    makeRec_dynamic(state_btn_dynamic_arr[i].x_end + 2, state_btn_dynamic_arr[i].y_begin, 150, 32, "Vertex = ", 18, "Green", false, false, true);
                                    printText(23, 255, 255, 255, text_find, state_btn_dynamic_arr[i].x_end + 152 - 68, state_btn_dynamic_arr[i].y_begin + 20, 0, 0);
                                    makeLine(state_btn_dynamic_arr[i].x_end + 152 - 70, state_btn_dynamic_arr[i].y_begin + 10, state_btn_dynamic_arr[i].x_end + 152 - 70, state_btn_dynamic_arr[i].y_end - 10, "White");
                                }
                            if (evt.key.keysym.sym == SDLK_KP_ENTER || evt.key.keysym.sym == SDLK_RETURN)
                            {
                                makeRec_dynamic(state_btn_dynamic_arr[i].x_end + 2, state_btn_dynamic_arr[i].y_begin, 150, 32, "Vertex = ", 18, "White", false, false, true);
                                break;
                            }
                        }
                        if (evt.type == SDL_MOUSEBUTTONDOWN) {
                            makeRec_dynamic(state_btn_dynamic_arr[i].x_end + 2, state_btn_dynamic_arr[i].y_begin, 150, 32, "Vertex = ", 18, "White", false, false, true);
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
                                if (i == number_node || text_find == dynamic_array[i].nameID) break;
                                x += 100;
                                i++;
                                SDL_RenderPresent(renderer);
                                SDL_Delay(speed[speed_type] + (speed[speed_type] * 6));
                            }
                            if (i == number_node && text_find != dynamic_array[i].nameID)
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
                                search_Step_dynamic_array(text_find, 1, 50, 1, dynamic_array);
                            }
                    }
                    cancel_menu = false;

                }
                ///////////////////////////////////////////Delete data
                if (state_btn_dynamic_arr[i].nameID == "Delete")
                {
                    makeRec_dynamic(state_btn_dynamic_arr[i].x_end + 2, state_btn_dynamic_arr[i].y_begin, 150, 32, "Delete at the first", 18, "Green", check_1st_time.menu_del, check_1st_time.menu_del, true);
                    makeRec_dynamic(state_btn_dynamic_arr_map["Delete at the first"].x_end + 2, state_btn_dynamic_arr[i].y_begin, 170, 32, "Delete at the middle", 18, "Green", check_1st_time.menu_del, check_1st_time.menu_del, true);
                    makeRec_dynamic(state_btn_dynamic_arr_map["Delete at the middle"].x_end + 2, state_btn_dynamic_arr[i].y_begin, 150, 32, "Delete at the last", 18, "Green", check_1st_time.menu_del, check_1st_time.menu_del, true);
                    check_1st_time.menu_del = false;
                    show_menu_add_del = true;
                    tempt = i;
                    break;
                }
                else
                    if (show_menu_add_del && (state_btn_dynamic_arr[i].nameID == "Delete at the first" || state_btn_dynamic_arr[i].nameID == "Delete at the middle" || state_btn_dynamic_arr[i].nameID == "Delete at the last"))
                    {

                        show_menu_add_del = false;
                        drawRec(200, state_btn_dynamic_arr_map["Delete"].y_begin, state_btn_dynamic_arr_map["Delete at the last"].x_end, 50, false, "", 0, "White");
                        if (number_node >= 2)
                        {
                            int buttonid = messbox("", "Choose how to run", 2, "Run step by step", "Run at once");
                            if (buttonid == 0)
                            { //run at once
                                if (state_btn_dynamic_arr[i].nameID == "Delete at the first")
                                {
                                    loop_node_dynamic_array_del(1, number_node - 1);
                                    SDL_Delay(speed[speed_type] + (speed[speed_type] * 6));
                                    drawRec(dynamic_array[number_node].x_begin, 50, 100, 45, false, "", 0, "White");
                                    //Set line color to black and rec color to blue
                                    int dem = 1;
                                    int x = 50;
                                    while (true) {
                                        draw_bound_rec(x, 50, 100, 45, "Black");
                                        dem++;
                                        if (dem == number_node) break;
                                        x += 100;
                                    }
                                    number_node--;
                                    for (int i = 1; i <= number_node; i++)
                                    {
                                        dynamic_array[i].nameID = dynamic_array[i + 1].nameID;
                                    }
                                }
                                else if (number_node >= 3)
                                {
                                    if (state_btn_dynamic_arr[i].nameID == "Delete at the middle")
                                    {
                                        loop_node_dynamic_array_del(number_node / 2 + 1, number_node - 1);
                                        SDL_Delay(speed[speed_type] + (speed[speed_type] * 6));
                                        drawRec(dynamic_array[number_node].x_begin, 50, 100, 45, false, "", 0, "White");
                                        //Set line color to black and rec color to blue
                                        int dem = number_node / 2 + 1;
                                        int x = dynamic_array[number_node / 2 + 1].x_begin;
                                        while (true) {
                                            draw_bound_rec(x, 50, 100, 45, "Black");
                                            dem++;
                                            if (dem == number_node) break;
                                            x += 100;
                                        }
                                        for (int i = number_node / 2 + 1; i <= number_node; i++)
                                        {
                                            dynamic_array[i].nameID = dynamic_array[i + 1].nameID;
                                        }
                                        number_node--;

                                    }
                                    if (state_btn_dynamic_arr[i].nameID == "Delete at the last")
                                    {
                                        draw_bound_rec(dynamic_array[number_node].x_begin, 50, 100, 45, "Orange");
                                        SDL_Delay(speed[speed_type] + (speed[speed_type] * 6));
                                        drawRec(dynamic_array[number_node].x_begin, 50, 100, 45, false, "", 0, "White");
                                        number_node--;

                                    }
                                }
                            }
                            else
                            { //run step by step
                                if (state_btn_dynamic_arr[i].nameID == "Delete at the first")
                                {
                                    delete_step_dynamic_array(1, dynamic_array, 1, 1, number_node - 1);
                                }
                                if (state_btn_dynamic_arr[i].nameID == "Delete at the middle")
                                {
                                    delete_step_dynamic_array(1, dynamic_array, number_node / 2 + 1, number_node / 2 + 1, number_node - 1);
                                }
                                if (state_btn_dynamic_arr[i].nameID == "Delete at the last")
                                {
                                    delete_step_dynamic_array(1, dynamic_array, number_node, number_node, number_node);
                                }
                            }
                        }
                        if (number_node - 1 == 0)
                        {
                            number_node--;
                            draw_bound_rec(50, 50, 100, 45, "Orange");
                            SDL_Delay(300);
                            drawRec(50, 50, 100, 150, false, "", 22, "White");
                            dynamic_array[1] = {};

                        }
                        drawRec(dynamic_array[number_node + 1].x_begin, 95, 100, 50, false, "", 0, "White");
                        break;
                    }
            }
        }
        if (show_menu_add_del == true)
        {
            if (state_btn_dynamic_arr[tempt].nameID != "Delete")
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
void Game::render_dynamic_array(std::vector<coordinates> linkedlist) {
    //SDL_RenderClear(renderer); // Clear the screen
    dynamic_array = linkedlist;
    if (count == 0) {
        for (int i = 1; i <=14; i++) {
            if (i == number_node)
                tail1 = true;
            Dynamic_Arrary(dynamic_array[i].nameID, i);
            tail1 = false;
        }
        count = 1;
    }
    SDL_RenderPresent(renderer); // Show the rendered image on the screen
}
void Game::makeRec_dynamic(int x_pos, int y_pos, int width_rec, int height_rec, std::string name, int textsize, std::string name_color, bool save_state, bool btn_map, bool txtinp) {
    //draw rectangle
    SDL_Rect rect = { x_pos, y_pos,width_rec,height_rec };
    SDL_SetRenderDrawColor(renderer, color[name_color][0], color[name_color][1], color[name_color][2], 0); //3 channels of color
    SDL_RenderFillRect(renderer, &rect);
    //name of buttn
    if (txtinp)
        printText(textsize, 255, 255, 255, name.c_str(), rect.x + 10, rect.y + 10, 0, 0);
    if (save_state) {
        state_btn_dynamic_arr[number_coorbtn].x_begin = x_pos;
        state_btn_dynamic_arr[number_coorbtn].x_end = x_pos + width_rec;
        state_btn_dynamic_arr[number_coorbtn].y_begin = y_pos;
        state_btn_dynamic_arr[number_coorbtn].y_end = y_pos + height_rec;
        state_btn_dynamic_arr[number_coorbtn].nameID = name;
        number_coorbtn++;
    }
    if (btn_map) {
        state_btn_dynamic_arr_map[name].x_begin = x_pos;
        state_btn_dynamic_arr_map[name].x_end = x_pos + width_rec;
        state_btn_dynamic_arr_map[name].y_begin = y_pos;
        state_btn_dynamic_arr_map[name].y_end = y_pos + height_rec;
    }
    SDL_RenderPresent(renderer); // Show the rendered image on the screen

}

void Game::Dynamic_Arrary(std::string value, int current_node)
{
    SDL_Rect rect = { edge.x, edge.y, 100,45 };
    if (current_node <= number_node)
    {
        SDL_SetRenderDrawColor(renderer, 100, 149, 237, 0); //blue
        SDL_RenderFillRect(renderer, &rect);
        draw_bound_rec(edge.x, edge.y, 100, 45, "Black");
        // Draw the text texture inside the rectangle
        printText(23, 255, 255, 255, value.c_str(), rect.x + 10, rect.y + 10, 0, 0);
    }
    //save liked list
    dynamic_array[current_node].x_begin = rect.x; dynamic_array[current_node].x_end = rect.x + rect.w;
    dynamic_array[current_node].y_begin = rect.y; dynamic_array[current_node].y_end = rect.y + 45;
    dynamic_array[current_node].nameID = value.c_str();
    edge.x = rect.x + rect.w;
    edge.y = rect.y;
    if (!menu_linkedlist)
    {
        drawRec(50, 500, 150, 38, true, "Random Data", 20, "Green");
        save_state_btn_dynamic_arr(50, 500, 150, 38, "Random Data");
        save_state_btn_dynamic_arr_map(50, 500, 150, 38, "Random Data");
        number_coorbtn++;
        drawRec(50, state_btn_dynamic_arr[number_coorbtn - 1].y_end + 2, 150, 38, true, "Add", 20, "Green");
        save_state_btn_dynamic_arr(50, state_btn_dynamic_arr[number_coorbtn - 1].y_end + 2, 150, 38, "Add");
        save_state_btn_dynamic_arr_map(50, state_btn_dynamic_arr[number_coorbtn - 1].y_end + 2, 150, 38, "Add");
        number_coorbtn++;
        drawRec(50, state_btn_dynamic_arr[number_coorbtn - 1].y_end + 2, 150, 38, true, "Delete", 20, "Green");
        save_state_btn_dynamic_arr(50, state_btn_dynamic_arr[number_coorbtn - 1].y_end + 2, 150, 38, "Delete");
        save_state_btn_dynamic_arr_map(50, state_btn_dynamic_arr[number_coorbtn - 1].y_end + 2, 150, 38, "Delete");
        number_coorbtn++;
        drawRec(50, state_btn_dynamic_arr[number_coorbtn - 1].y_end + 2, 150, 38, true, "Search", 20, "Green");
        save_state_btn_dynamic_arr(50, state_btn_dynamic_arr[number_coorbtn - 1].y_end + 2, 150, 38, "Search");
        save_state_btn_dynamic_arr_map(50, state_btn_dynamic_arr[number_coorbtn - 1].y_end + 2, 150, 38, "Search");
        number_coorbtn++;
        menu_linkedlist = true;
    }
}