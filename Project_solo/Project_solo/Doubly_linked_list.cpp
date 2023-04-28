﻿#include "VD.h"
static int count = 0, tempt = 0;
static bool head = false, tail = false, menu_linkedlist = false, show_menu_add = false, txtinp = false, btn_map = false, save_state = true, cancel_menu = false, show_menu_add_del;
static bool run_step = false, back = false;
coordinates state_btn_dll[50];
static lan_dau check_1st_time;
std::map<std::string, coordinates> state_btn_dll_map;
static std::vector<Uint32*>pixels_stage(1);
static int number_coorbtn = 1;
static std::string add_position;
std::vector<coordinates> dll_linkedlist(1000);
static std::string speed_type = "low";
void update_vector_dll(int i, int number_node, bool del, bool insert, std::string value);
void update_vector_dll(int i, int number_node, bool del, bool insert, std::string value) {
    int sgn = 0;
    if (del)  sgn = -1;
    else  sgn = 1;
    if (del)
    {
        dll_linkedlist.erase(dll_linkedlist.begin() + i);
        coordinates new_element = {};
        dll_linkedlist.push_back(new_element);
    }
    if (insert) {
        coordinates newElement = { dll_linkedlist[i - 1].x_begin, dll_linkedlist[i - 1].x_end,dll_linkedlist[i - 1].y_begin, dll_linkedlist[i - 1].y_end,value };
        dll_linkedlist.insert(dll_linkedlist.begin() + i, newElement);
    }
    for (; i <= number_node; i++) {
        dll_linkedlist[i].x_begin += sgn * 150;
        dll_linkedlist[i].x_end += sgn * 150;
    }
}
void Game::drawLine_animation(int x_begin, int y_begin, int x_end, int y_end, std::string color_name)
{
    while (x_begin < x_end) {
        makeLine(x_begin, 75, x_begin + 5, 75, color_name);
        x_begin += 5;
        SDL_Delay(50);
    }
}
void Game::insert_first_dll(std::string value, std::vector<coordinates>& linked_list) {
    if (number_node >= 1)
    {
        drawRec(50, 160, 100, 45, true, value, 23, "Blue");
        draw_bound_rec(50, 160, 100, 45, "Orange");
        drawArrow(95, 160, 95, 95, "Black",1);
        drawArrow(105, 95, 105,160, "Black", 1);
        int y_begin = 160;
        while (y_begin > 95) 
        {
            makeLine(95, y_begin, 95, y_begin-5, "Orange");
            y_begin -= 5;
            SDL_Delay(50);
        }        
        SDL_Delay(speed[speed_type] + (speed[speed_type] * 6));
        y_begin = 95;
        while (y_begin < 160)
        {
            makeLine(105, y_begin, 105, y_begin + 5, "Orange");
            y_begin += 5;
            SDL_Delay(50);
        }
        coordinates newElement = { 50,150, 50, 50,value };
        number_node += 1;
        linked_list.insert(linked_list.begin() + 1, newElement);
        for (int i = 2; i <= number_node; i++) {
            linked_list[i].x_begin += 150;
            linked_list[i].x_end += 150;
        }
        SDL_Delay(speed[speed_type] + (speed[speed_type] * 6));
        menu_linkedlist = false;
        drawRec(50, 50, 1550, 500, false, "", 0, "White");
        render_dll(dll_linkedlist);
    }
    else
    {
        drawRec(50, 50, 100, 45, true, value, 23, "Blue");
        draw_bound_rec(50, 50, 100, 45, "Orange");
        SDL_Delay(350);
        draw_bound_rec(50, 50, 100, 45, "Blue");
        number_node++;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::handleEvents_DLL() {
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
        for (int i = 1; i <= number_coorbtn + number_node; i++) {
            if ((mouseX >= state_btn_dll[i].x_begin && mouseX <= state_btn_dll[i].x_end &&
                mouseY >= state_btn_dll[i].y_begin && mouseY <= state_btn_dll[i].y_end) || ((i <= number_node) && ((mouseX >= dll_linkedlist[i].x_begin && mouseX <= dll_linkedlist[i].x_end &&
                    mouseY >= dll_linkedlist[i].y_begin && mouseY <= dll_linkedlist[i].y_end))))
            {
                if ((i <= number_node) && ((mouseX >= dll_linkedlist[i].x_begin && mouseX <= dll_linkedlist[i].x_end && //Edit data
                    mouseY >= dll_linkedlist[i].y_begin && mouseY <= dll_linkedlist[i].y_end))) //Edit value of linked list
                {
                    std::string current_value = dll_linkedlist[i].nameID;
                    makeRec_DLL(dll_linkedlist[i].x_begin, 50, 100, 45, "", 0, "Blue", false, false, false);
                    txtinp = false;
                    makeLine(dll_linkedlist[i].x_begin + 5, 60, dll_linkedlist[i].x_begin + 5, 85, "White");
                    std::string text_edit = "";
                    SDL_StartTextInput;
                    while (true) {
                        SDL_Event evt;
                        SDL_PollEvent(&evt);
                        if (evt.type == SDL_TEXTINPUT)
                            if (text_edit.length() <= 3 && isdigit(evt.text.text[0]))
                            {
                                text_edit += evt.text.text;
                                printText(23, 255, 255, 255, text_edit, dll_linkedlist[i].x_begin + 10, 60, 0, 0);
                            }
                        if (evt.type == SDL_KEYDOWN) {
                            if (evt.key.keysym.sym == SDLK_BACKSPACE)
                                if (text_edit.length() > 0)
                                {
                                    txtinp = false;
                                    text_edit.pop_back();
                                    makeRec_DLL(dll_linkedlist[i].x_begin, 50, 100, 45, text_edit, 23, "Blue", false, false, true);
                                    printText(23, 255, 255, 255, text_edit, dll_linkedlist[i].x_begin + 10, 60, 0, 0);
                                    makeLine(dll_linkedlist[i].x_begin + 5, 60, dll_linkedlist[i].x_begin + 5, 85, "White");
                                }
                            if (evt.key.keysym.sym == SDLK_KP_ENTER || evt.key.keysym.sym == SDLK_RETURN)
                            {
                                if (text_edit.length() > 0) {
                                    txtinp = false;
                                    makeRec_DLL(dll_linkedlist[i].x_begin, 50, 100, 45, current_value, 23, "Blue", false, false, true);
                                    Edit_data(i);
                                    makeRec_DLL(dll_linkedlist[i].x_begin, 50, 100, 45, text_edit, 23, "Blue", false, false, true);
                                    dll_linkedlist[i].nameID = text_edit.c_str();
                                    break;
                                }
                                makeRec_DLL(dll_linkedlist[i].x_begin, 50, 100, 45, current_value, 23, "Blue", false, false, true);
                                break;
                            }
                        }
                        if (evt.type == SDL_MOUSEBUTTONDOWN) {
                            makeRec_DLL(dll_linkedlist[i].x_begin, 50, 100, 45, current_value, 23, "Blue", false, false, true);
                            break;
                        }
                    }
                    break;
                } //Edit data
                if (state_btn_dll[i].nameID == "Random Data") {
                    random_data(); break;
                }
                if (state_btn_dll[i].nameID == "Add")
                { //insert data
                    makeRec_DLL(state_btn_dll[i].x_end + 2, state_btn_dll[i].y_begin, 150, 32, "Insert to the first", 19, "Green", check_1st_time.menu_add, check_1st_time.menu_add, true);
                    makeRec_DLL(state_btn_dll_map["Insert to the first"].x_end + 2, state_btn_dll_map["Insert to the first"].y_begin, 180, 32, "Insert to the middle", 19, "Green", check_1st_time.menu_add, check_1st_time.menu_add, true);
                    makeRec_DLL(state_btn_dll_map["Insert to the middle"].x_end + 2, state_btn_dll_map["Insert to the middle"].y_begin, 150, 32, "Insert to the last", 19, "Green", check_1st_time.menu_add, check_1st_time.menu_add, true);
                    check_1st_time.menu_add = false;
                    btn_map = false;
                    show_menu_add = true;
                    break;
                }
                if (show_menu_add && (state_btn_dll[i].nameID == "Insert to the first" || state_btn_dll[i].nameID == "Insert to the middle" || state_btn_dll[i].nameID == "Insert to the last"))
                {
                    save_state = true;
                    txtinp = false;
                    makeRec_DLL(state_btn_dll[i].x_begin, state_btn_dll[i].y_end, 150, 32, "Vertex = ", 19, "Green", false, true, true);
                    txtinp = true;
                    //create input box
                    btn_map = true;
                    makeRec_DLL(state_btn_dll[i].x_end - 80, state_btn_dll[i].y_end + 5, 40, 25, "input_box", 19, "Black", false, true, false);
                    btn_map = false;
                    save_state = false;
                    if (state_btn_dll[i].nameID == "Insert to the first") add_position = "first";
                    if (state_btn_dll[i].nameID == "Insert to the middle") add_position = "middle";
                    if (state_btn_dll[i].nameID == "Insert to the last") add_position = "last";
                    makeLine(state_btn_dll_map["input_box"].x_begin + 2, state_btn_dll_map["input_box"].y_begin + 2, state_btn_dll_map["input_box"].x_begin + 2, state_btn_dll_map["input_box"].y_end - 2, "White");
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
                                    printText(15, 255, 255, 255, inputText, state_btn_dll_map["input_box"].x_begin + 2, state_btn_dll_map["input_box"].y_begin + 2, 0, 0);
                                    e.type = 0;
                                }
                        }
                        else if (e.type == SDL_KEYDOWN)
                        {
                            if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0) {
                                inputText.pop_back();
                                save_state = false;
                                makeRec_DLL(state_btn_dll_map["input_box"].x_begin, state_btn_dll_map["input_box"].y_begin, 40, 25, inputText, 15, "Black", false, false, true);
                                save_state = true;
                            }
                            if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_KP_ENTER) {
                                txtinp = true;
                                makeRec_DLL(state_btn_dll_map["Insert to the first"].x_begin, state_btn_dll_map["Insert to the first"].y_begin,
                                    state_btn_dll_map["Insert to the last"].x_end, state_btn_dll_map["input_box"].y_end, " ", 0, "White", false, false, false);
                                if (inputText.length() > 0 && number_node < 10) {
                                    int buttonid = messbox("", "Choose how to run", 2, "Run step by step", "Run at once");
                                    if (buttonid == 0) { //run at once
                                        if (add_position == "first")
                                            insert_first_dll(inputText, dll_linkedlist);
                                        if (add_position == "last")
                                            insert_last_data(inputText, dll_linkedlist);
                                        if (add_position == "middle")
                                            insert_middle(inputText);
                                    }
                                    else { //run step by step
                                        if (add_position == "first")
                                            insert_first_step(inputText, 1, dll_linkedlist);
                                        if (add_position == "middle")
                                            insert_middle_step(inputText, 1);
                                        if (add_position == "last")
                                            insert_last_step(inputText, 1, dll_linkedlist, 50);
                                    }
                                }
                                show_menu_add = false;
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
                        makeLine(state_btn_dll_map["input_box"].x_begin + 2, state_btn_dll_map["input_box"].y_begin + 2, state_btn_dll_map["input_box"].x_begin + 2, state_btn_dll_map["input_box"].y_end - 2, "White");
                    }
                    // SDL_StopTextInput();
                    break;
                }
                if (state_btn_dll[i].nameID == "Search")
                {
                    makeRec_DLL(state_btn_dll[i].x_end + 2, state_btn_dll[i].y_begin, 150, 32, "Vertex = ", 18, "Green", false, false, true);
                    makeLine(state_btn_dll[i].x_end + 152 - 70, state_btn_dll[i].y_begin + 10, state_btn_dll[i].x_end + 152 - 70, state_btn_dll[i].y_end - 10, "White");
                    std::string text_find = "";
                    SDL_StartTextInput;
                    while (true) {
                        SDL_Event evt;
                        SDL_PollEvent(&evt);
                        if (evt.type == SDL_TEXTINPUT)
                            if (text_find.length() <= 3 && isdigit(evt.text.text[0]))
                            {
                                text_find += evt.text.text;
                                printText(18, 255, 255, 255, text_find, state_btn_dll[i].x_end + 152 - 68, state_btn_dll[i].y_begin + 10, 0, 0);
                            }
                        if (evt.type == SDL_KEYDOWN) {
                            if (evt.key.keysym.sym == SDLK_BACKSPACE)
                                if (text_find.length() > 0)
                                {
                                    txtinp = false;
                                    text_find.pop_back();
                                    makeRec_DLL(state_btn_dll[i].x_end + 2, state_btn_dll[i].y_begin, 150, 32, "Vertex = ", 18, "Green", false, false, true);
                                    printText(23, 255, 255, 255, text_find, state_btn_dll[i].x_end + 152 - 68, state_btn_dll[i].y_begin + 20, 0, 0);
                                    makeLine(state_btn_dll[i].x_end + 152 - 70, state_btn_dll[i].y_begin + 10, state_btn_dll[i].x_end + 152 - 70, state_btn_dll[i].y_end - 10, "White");
                                }
                            if (evt.key.keysym.sym == SDLK_KP_ENTER || evt.key.keysym.sym == SDLK_RETURN)
                            {
                                makeRec_DLL(state_btn_dll[i].x_end + 2, state_btn_dll[i].y_begin, 150, 32, "Vertex = ", 18, "White", false, false, true);
                                break;
                            }
                        }
                        if (evt.type == SDL_MOUSEBUTTONDOWN) {
                            makeRec_DLL(state_btn_dll[i].x_end + 2, state_btn_dll[i].y_begin, 150, 32, "Vertex = ", 18, "White", false, false, true);
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
                            int x_line = 150;
                            int width = 1500;
                            //copy
                            SDL_Rect section = { x,50,width,45 };
                            Uint32* pixels = new Uint32[width * 45];
                            SDL_RenderReadPixels(renderer, &section, SDL_PIXELFORMAT_ARGB8888, pixels, width * sizeof(Uint32));
                            //
                            while (true) {
                                SDL_Rect rect = { x,50,100,45 };
                                SDL_SetRenderDrawColor(renderer, 255, 165, 0, 0); //3 channels of color
                                SDL_RenderDrawRect(renderer, &rect);
                                SDL_RenderPresent(renderer);
                                int t = x_line;
                                if (i == number_node || text_find == dll_linkedlist[i].nameID) break;
                                while (x_line < t + 50) {
                                    makeLine(x_line, 75, x_line + 5, 75, "Orange");
                                    x_line += 5;
                                    SDL_Delay(50);
                                }
                                x += 150;
                                x_line += 100;
                                i++;
                                SDL_RenderPresent(renderer);
                                SDL_Delay(300);
                            }
                            if (i == number_node && text_find != dll_linkedlist[i].nameID)
                                messbox("", "NOT FOUND :((", 1, "", "Ok");
                            SDL_Delay(500);
                            //paste
                            SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, 45);
                            SDL_UpdateTexture(texture, nullptr, pixels, width * sizeof(Uint32));
                            SDL_Rect destination = { 50,50,width, 45 };
                            SDL_RenderCopy(renderer, texture, nullptr, &destination);
                            SDL_RenderPresent(renderer);
                            SDL_DestroyTexture(texture);
                            delete[] pixels;
                            break;
                        }
                        else
                            if (buttonid == 1) {
                                search_Step(text_find, 1, 50, 1, dll_linkedlist);
                            }
                    }
                    cancel_menu = false;

                }
                ///////////////////////////////////////////Delete data
                if (state_btn_dll[i].nameID == "Delete") {
                    makeRec_DLL(state_btn_dll[i].x_end + 2, state_btn_dll[i].y_begin, 150, 32, "Delete at the first", 18, "Green", check_1st_time.menu_del, check_1st_time.menu_del, true);
                    makeRec_DLL(state_btn_dll_map["Delete at the first"].x_end + 2, state_btn_dll[i].y_begin, 170, 32, "Delete at the middle", 18, "Green", check_1st_time.menu_del, check_1st_time.menu_del, true);
                    makeRec_DLL(state_btn_dll_map["Delete at the middle"].x_end + 2, state_btn_dll[i].y_begin, 150, 32, "Delete at the last", 18, "Green", check_1st_time.menu_del, check_1st_time.menu_del, true);
                    check_1st_time.menu_del = false;
                    show_menu_add_del = true;
                    tempt = i;
                    break;
                }
                else
                    if (show_menu_add_del && (state_btn_dll[i].nameID == "Delete at the first" || state_btn_dll[i].nameID == "Delete at the middle" || state_btn_dll[i].nameID == "Delete at the last"))
                    {

                        show_menu_add_del = false;
                        drawRec(200, state_btn_dll_map["Delete"].y_begin, state_btn_dll_map["Delete at the last"].x_end, 50, false, "", 0, "White");
                        if (number_node >= 2)
                        {
                            int buttonid = messbox("", "Choose how to run", 2, "Run step by step", "Run at once");
                            if (buttonid == 0)
                            { //run at once
                                if (state_btn_dll[i].nameID == "Delete at the first")
                                {
                                    //copy rec
                                    SDL_Rect section = { 200,50,1300,45 };
                                    Uint32* pixels = new Uint32[1300 * 45];
                                    SDL_RenderReadPixels(renderer, &section, SDL_PIXELFORMAT_ARGB8888, pixels, 1300 * sizeof(Uint32));
                                    //
                                    SDL_Rect rect = { 50,50,100,45 };
                                    SDL_SetRenderDrawColor(renderer, 255, 165, 0, 0); //color orange
                                    SDL_RenderDrawRect(renderer, &rect);
                                    SDL_RenderPresent(renderer);
                                    int x_line = 150;
                                    makeRec_DLL(50, 105, 150, 45, "", 0, "White", false, false, false);
                                    printText(22, 0, 0, 0, "Temp", 60, 105, 0, 0);
                                    while (x_line < 200) {
                                        makeLine(x_line, 75, x_line + 5, 75, "Orange");
                                        x_line += 5;
                                        SDL_Delay(50);
                                    }
                                    printText(22, 0, 0, 0, "Head", 210, 105, 0, 0);
                                    SDL_Delay(200);
                                    makeRec_DLL(50, 50, 150, 45, "", 0, "White", false, false, false);
                                    SDL_RenderPresent(renderer);
                                    SDL_Delay(300);
                                    int x_move_rec = 195, x_move_text = 205;
                                    //copy text
                                    SDL_Rect section_text = { 210,105,1300,45 };
                                    Uint32* pixel_text = new Uint32[1300 * 45];
                                    SDL_RenderReadPixels(renderer, &section_text, SDL_PIXELFORMAT_ARGB8888, pixel_text, 1300 * sizeof(Uint32));
                                    //move rec to the left

                                    while (x_move_rec >= 50)
                                    {
                                        //rec
                                        makeRec_DLL(50, 50, 1500, 150, "", 0, "White", false, false, false);
                                        SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 1300, 45);
                                        SDL_UpdateTexture(texture, nullptr, pixels, 1300 * sizeof(Uint32));
                                        SDL_Rect destination = { x_move_rec,50,1300, 45 };
                                        SDL_RenderCopy(renderer, texture, nullptr, &destination);
                                        SDL_RenderPresent(renderer);
                                        SDL_DestroyTexture(texture);
                                        //text
                                        SDL_Texture* texture_text = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 1300, 45);
                                        SDL_UpdateTexture(texture_text, nullptr, pixel_text, 1300 * sizeof(Uint32));
                                        SDL_Rect destination_text = { x_move_text,105,1300, 45 };
                                        SDL_RenderCopy(renderer, texture_text, nullptr, &destination_text);
                                        SDL_RenderPresent(renderer);
                                        SDL_DestroyTexture(texture_text);
                                        SDL_Delay(20);
                                        x_move_rec -= 5;
                                        x_move_text -= 5;

                                    }
                                    delete[] pixels;
                                    delete[] pixel_text;
                                    number_node--;
                                    update_vector_dll(0, number_node, true, false, "");
                                }
                                else if (number_node >= 3)
                                {
                                    if (state_btn_dll[i].nameID == "Delete at the middle")
                                    {
                                        loop_node(1, number_node / 2, "Del", false);
                                        //dịch chuyen del node xuống
                                        i = number_node / 2 + 1;
                                        SDL_Delay(800);
                                        int y = 50;
                                        makeRec_DLL(dll_linkedlist[i].x_begin, 50, 150, 45, "", 0, "White", false, false, false);
                                        while (y < 160) {
                                            y += 5;
                                            if (y >= 75) makeLine(dll_linkedlist[i].x_begin, 75, dll_linkedlist[i].x_begin + 150, 75, "Orange");
                                            makeRec_DLL(dll_linkedlist[i].x_begin, y, 100, 45, dll_linkedlist[i].nameID, 23, "Blue", false, false, true);
                                            makeLine(dll_linkedlist[i].x_end, y + 25, dll_linkedlist[i + 1].x_begin, 75, "Orange");
                                            if (y >= 160) SDL_Delay(400);
                                            SDL_Delay(15);
                                            makeRec_DLL(dll_linkedlist[i].x_begin, 50, 150, y + 50, "", 25, "White", false, false, false);
                                        }
                                        //fix STT của next node xuống 1
                                        loop_node(1, number_node / 2, "Del", true);
                                        //move the next node and the text to the left
                                        int width = dll_linkedlist[number_node].x_end - dll_linkedlist[i + 1].x_begin;
                                        SDL_Rect section = { dll_linkedlist[i + 1].x_begin,50,width,150 };
                                        Uint32* pixels = new Uint32[1300 * 150];
                                        SDL_RenderReadPixels(renderer, &section, SDL_PIXELFORMAT_ARGB8888, pixels, width * sizeof(Uint32));
                                        int x = dll_linkedlist[i + 1].x_begin;
                                        while (x > dll_linkedlist[i].x_begin)
                                        {
                                            makeRec_DLL(x, 50, width, 45, "", 0, "White", false, false, false);
                                            x -= 5;
                                            SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, 150);
                                            SDL_UpdateTexture(texture, nullptr, pixels, width * sizeof(Uint32));
                                            SDL_Rect destination = { x,50,width, 150 };
                                            SDL_RenderCopy(renderer, texture, nullptr, &destination);
                                            SDL_RenderPresent(renderer);
                                            SDL_DestroyTexture(texture);
                                            makeLine(dll_linkedlist[i].x_begin, 75, x, 75, "Orange");
                                            SDL_Delay(15);
                                        }
                                        SDL_Delay(300);
                                        //Fix color of rec to blue and color of the line to black
                                        int dem = 1;
                                        x = 50;
                                        while (true) {
                                            SDL_Rect rect = { x,50,100,45 };
                                            SDL_SetRenderDrawColor(renderer, 100, 149, 237, 0); //3 channels of color
                                            SDL_RenderDrawRect(renderer, &rect);
                                            SDL_RenderPresent(renderer);
                                            dem++;
                                            if (dem == number_node) break;
                                            makeLine(x + 100, 75, x + 150, 75, "Black");
                                            x += 150;
                                        }
                                        //Delete prev and aft text
                                        drawRec(200, 100, dll_linkedlist[number_node - 1].x_begin - 200, 50, false, "", 0, "White");
                                        number_node--;
                                        update_vector_dll(i, number_node, true, false, "");
                                        delete[] pixels;
                                    }
                                    if (state_btn_dll[i].nameID == "Delete at the last")
                                    {
                                        drawRec(50, 105, 100, 30, false, "", 0, "White");
                                        makeLine(150, 75, 200, 75, "Orange");
                                        printText(22, 0, 0, 0, "Head/prev", 70, 105, 0, 0);
                                        printText(23, 0, 0, 0, "Tempt", 225, 105, 0, 0);
                                        int t = 150;
                                        while (true) {
                                            t += 5;
                                            makeLine(150, 75, t, 75, "Orange");
                                            SDL_Delay(100);
                                            if (t == 200) break;
                                        }
                                        makeLine(150, 75, 200, 75, "Black");
                                        SDL_Delay(150);
                                        int i = 3;
                                        while (true)
                                        {
                                            drawRec(dll_linkedlist[i - 2].x_begin, 105, dll_linkedlist[i - 2].x_begin + 250, 30, false, "", 0, "White");
                                            printText(22, 0, 0, 0, "Head", 75, 105, 0, 0);
                                            printText(23, 0, 0, 0, "prev", dll_linkedlist[i - 1].x_begin + 25, 105, 0, 0);
                                            if (i == number_node)
                                                printText(22, 0, 0, 0, "Tail/Tempt", dll_linkedlist[i].x_begin + 20, 105, 0, 0);
                                            else
                                                printText(23, 0, 0, 0, "Tempt", dll_linkedlist[i].x_begin + 25, 105, 0, 0);
                                            t = dll_linkedlist[i - 1].x_end;
                                            int z = dll_linkedlist[i - 2].x_end;
                                            while (true) {
                                                t += 5;
                                                z += 5;
                                                makeLine(dll_linkedlist[i - 1].x_end, 75, t, 75, "Orange"); // new tempt node
                                                makeLine(dll_linkedlist[i - 2].x_end, 75, z, 75, "Orange"); //redraw the prev node
                                                if (t == dll_linkedlist[i - 1].x_end + 50) break;
                                                SDL_Delay(80);
                                            }
                                            makeLine(dll_linkedlist[i - 1].x_end, 75, t, 75, "Black");
                                            if (i == number_node) {
                                                makeLine(dll_linkedlist[number_node - 1].x_end, 75, dll_linkedlist[number_node].x_begin, 75, "Orange");
                                                break;
                                            }
                                            SDL_Delay(150);
                                            i++;
                                        }
                                        drawRec(dll_linkedlist[number_node - 1].x_end, 50, dll_linkedlist[number_node - 1].x_end + 150, 45, false, "", 0, "White");
                                        drawRec(dll_linkedlist[i - 2].x_begin, 105, dll_linkedlist[i - 2].x_begin + 250, 30, false, "", 0, "White");
                                        dll_linkedlist[number_node].x_begin = 0;
                                        dll_linkedlist[number_node].x_end = 0;
                                        dll_linkedlist[number_node].y_begin = 0;
                                        dll_linkedlist[number_node].y_end = 0;
                                        dll_linkedlist[number_node].nameID = "";
                                        number_node--;
                                        printText(22, 0, 0, 0, "Tail", dll_linkedlist[number_node].x_begin + 25, 105, 0, 0);
                                        //Fix color of rec to blue and color of the line to black
                                        int dem = 1;
                                        int x = 50;
                                        while (true) {
                                            SDL_Rect rect = { x,50,100,45 };
                                            SDL_SetRenderDrawColor(renderer, 100, 149, 237, 0); //3 channels of color
                                            SDL_RenderDrawRect(renderer, &rect);
                                            SDL_RenderPresent(renderer);
                                            dem++;
                                            if (dem == number_node + 1) break;
                                            makeLine(x + 100, 75, x + 150, 75, "Black");
                                            x += 150;
                                        }

                                    }
                                }
                            }
                            else
                            { //run step by step
                                if (state_btn_dll[i].nameID == "Delete at the first")
                                    delete_first_step(1, dll_linkedlist);
                                if (state_btn_dll[i].nameID == "Delete at the middle")
                                    delete_middle_step(1);
                                if (state_btn_dll[i].nameID == "Delete at the last")
                                    delete_last_step(1, dll_linkedlist);
                            }
                        }
                        if (number_node - 1 == 0)
                        {
                            number_node--;
                            draw_bound_rec(50, 50, 100, 45, "Orange");
                            SDL_Delay(300);
                            drawRec(50, 50, 100, 150, false, "", 22, "White");
                            dll_linkedlist[1] = {};

                        }

                        break;
                    }


            }
        }
        if (show_menu_add_del == true)
        {
            if (state_btn_dll[tempt].nameID != "Delete")
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
void Game::render_dll(std::vector<coordinates> dll) {
    //SDL_RenderClear(renderer); // Clear the screen
    dll_linkedlist = dll;
    if (count == 0) {
        for (int i = 1; i <= number_node; i++) {
            if (i == 1) head = true;
            if (i == number_node) tail = true;
            DL_Linkedlist(dll_linkedlist[i].nameID, i);
            head = false; tail = false;
        }
        count = 0;
        edge.x = 50; edge.y = 50;
    }
    SDL_RenderPresent(renderer); // Show the rendered image on the screen
}
void Game::drawArrow(int x1, int y1, int x2, int y2, std::string color_name, short int direction) 
{

    SDL_SetRenderDrawColor(renderer, color[color_name][0], color[color_name][1], color[color_name][2], 0); //3 channels of color
    // Vẽ đường thẳng từ (x1, y1) đến (x2, y2)
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

    // Tính toán tọa độ tam giác
    int arrowSize = 10; // Kích thước của mũi tên
    double angle = atan2(y2 - y1, x2 - x1);
    int x3 = x2 - arrowSize * cos(angle - M_PI / 6);
    int y3 = y2 - arrowSize * sin(angle - M_PI / 6);
    int x4 = x2 - arrowSize * cos(angle + M_PI / 6);
    int y4 = y2 - arrowSize * sin(angle + M_PI / 6);

    // Vẽ tam giác
    SDL_RenderDrawLine(renderer, x2, y2, x3, y3);
    SDL_RenderDrawLine(renderer, x2, y2, x4, y4);
    SDL_RenderPresent(renderer);
    if (direction == 2)
    {
        drawArrow(x2, y1+7, x1, y2+7, color_name, 1);
    }
}
void Game::makeRec_DLL(int x_pos, int y_pos, int width_rec, int height_rec, std::string name, int textsize, std::string name_color, bool save_state, bool btn_map, bool txtinp) {
    //draw rectangle
    SDL_Rect rect = { x_pos, y_pos,width_rec,height_rec };
    SDL_SetRenderDrawColor(renderer, color[name_color][0], color[name_color][1], color[name_color][2], 0); //3 channels of color
    SDL_RenderFillRect(renderer, &rect);
    //name of buttn
    if (txtinp)
        printText(textsize, 255, 255, 255, name.c_str(), rect.x + 10, rect.y + 10, 0, 0);
    if (save_state) {
        state_btn_dll[number_coorbtn].x_begin = x_pos;
        state_btn_dll[number_coorbtn].x_end = x_pos + width_rec;
        state_btn_dll[number_coorbtn].y_begin = y_pos;
        state_btn_dll[number_coorbtn].y_end = y_pos + height_rec;
        state_btn_dll[number_coorbtn].nameID = name;
        number_coorbtn++;
    }
    if (btn_map) {
        state_btn_dll_map[name].x_begin = x_pos;
        state_btn_dll_map[name].x_end = x_pos + width_rec;
        state_btn_dll_map[name].y_begin = y_pos;
        state_btn_dll_map[name].y_end = y_pos + height_rec;
    }
    SDL_RenderPresent(renderer); // Show the rendered image on the screen

}
void Game::DL_Linkedlist(std::string value, int current_node) {

    //draw rectangle
    SDL_Rect rect = { edge.x, edge.y, 100,45 };
    SDL_SetRenderDrawColor(renderer, 100, 149, 237, 0); //blue
    SDL_RenderFillRect(renderer, &rect);
    // Draw the text texture inside the rectangle
    printText(23, 255, 255, 255, value.c_str(), rect.x + 10, rect.y + 10, 0, 0);
    //save liked list
    dll_linkedlist[current_node].x_begin = rect.x; dll_linkedlist[current_node].x_end = rect.x + rect.w;
    dll_linkedlist[current_node].y_begin = rect.y; dll_linkedlist[current_node].y_end = rect.y + 45;
    dll_linkedlist[current_node].nameID = value.c_str();
    // Draw line
    if (!tail) {
        drawArrow(rect.x + rect.w, rect.y + 22, rect.x + rect.w+50, rect.y + 22, "Black",2);
        edge.x = rect.x + rect.w + 50;
        edge.y = rect.y;
    }

    if (tail) {
        state_btn_dll_map["Tail"].x_begin = rect.x;
        state_btn_dll_map["Tail"].x_end = rect.x + 100;
        state_btn_dll_map["Tail"].y_begin = 50;
        state_btn_dll_map["Tail"].y_end = 95;
    }
    btn_map = true;
    if (!menu_linkedlist)
    {
        makeRec_DLL(50, 500, 150, 38, "Random Data", 20, "Green", true, true, true);
        makeRec_DLL(50, state_btn_dll[number_coorbtn - 1].y_end + 2, 150, 38, "Add", 20, "Green", true, true, true);
        makeRec_DLL(50, state_btn_dll[number_coorbtn - 1].y_end + 2, 150, 38, "Delete", 20, "Green", true, true, true);
        makeRec_DLL(50, state_btn_dll[number_coorbtn - 1].y_end + 2, 150, 38, "Search", 20, "Green", true, true, true);

        menu_linkedlist = true;
    }
    btn_map = false;
}
