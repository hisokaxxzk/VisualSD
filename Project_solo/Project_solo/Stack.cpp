#include "VD.h"
static int count = 0, tempt = 0;
static bool head = false, tail = false, menu_linkedlist = false, show_menu_add = false, txtinp = false, btn_map = false, cancel_menu = false, show_menu_add_del;
static bool run_step = false, back = false;
static coordinates state_btn[50]; 
static lan_dau check_1st_time;
static std::map<std::string, coordinates> state_btn_map;
static std::vector<Uint32*>pixels_stage(1);
static int number_coorbtn = 1;
static std::string add_position;
static std::vector<coordinates> linked_list(1000);
void static save_state_btn(int x_pos, int y_pos, int width_rec, int height_rec, std::string name)
{
    state_btn[number_coorbtn].x_begin = x_pos;
    state_btn[number_coorbtn].x_end = x_pos + width_rec;
    state_btn[number_coorbtn].y_begin = y_pos;
    state_btn[number_coorbtn].y_end = y_pos + height_rec;
    state_btn[number_coorbtn].nameID = name;
}
void static save_state_btn_map(int x_pos, int y_pos, int width_rec, int height_rec, std::string name)
{
    state_btn_map[name].x_begin = x_pos;
    state_btn_map[name].x_end = x_pos + width_rec;
    state_btn_map[name].y_begin = y_pos;
    state_btn_map[name].y_end = y_pos + height_rec;
}
void static update_vector(int i, int number_node, bool del, bool insert, std::string value) {
    int sgn = 0;
    if (del)  sgn = -1;
    else  sgn = 1;
    if (del)
    {
        linked_list.erase(linked_list.begin() + i);
        coordinates new_element = {};
        linked_list.push_back(new_element);
    }
    if (insert) {
        coordinates newElement = { linked_list[i - 1].x_begin, linked_list[i - 1].x_end,linked_list[i - 1].y_begin, linked_list[i - 1].y_end,value };
        linked_list.insert(linked_list.begin() + i, newElement);
    }
    for (; i <= number_node; i++) {
        linked_list[i].x_begin += sgn * 150;
        linked_list[i].x_end += sgn * 150;
    }
}
void Game::random_data_stack() {
    linked_list.clear();
    linked_list.resize(11);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    makeRectangle(50, 50, 1600, 80, "", 0, "White", false, false, false);
    txtinp = true;
    int random_value_node;
    edge.x = 50; edge.y = 50;
    menu_linkedlist = true;
    for (int j = 1; j <= 8; j++) {
        number_node = rand() % 9 + 2;
        makeRectangle(50, 50, 1600, 80, "", 0, "White", false, false, false);
        for (int i = 1; i <= number_node; i++) {
            random_value_node = rand() % 100 + 1;
            if (i == 1) head = true;
            if (i == number_node) tail = true;
            stack(std::to_string(random_value_node).c_str(), i);
            head = false; tail = false;
        }
        edge.x = 50;
        edge.y = 50;
        SDL_Delay(70);
    }
    SDL_RenderPresent(renderer);
}
void Game::handleEvents_stack() {
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
            if ((mouseX >= state_btn[i].x_begin && mouseX <= state_btn[i].x_end &&
                mouseY >= state_btn[i].y_begin && mouseY <= state_btn[i].y_end) || ((i <= number_node) && ((mouseX >= linked_list[i].x_begin && mouseX <= linked_list[i].x_end &&
                    mouseY >= linked_list[i].y_begin && mouseY <= linked_list[i].y_end))))
            {
                if ((i <= number_node) && ((mouseX >= linked_list[i].x_begin && mouseX <= linked_list[i].x_end && //Edit data
                    mouseY >= linked_list[i].y_begin && mouseY <= linked_list[i].y_end))) //Edit value of linked list
                {
                    std::string current_value = linked_list[i].nameID;
                    drawRec(linked_list[i].x_begin, 50, 100, 45, false, "", 0, "Blue");
                    makeLine(linked_list[i].x_begin + 5, 60, linked_list[i].x_begin + 5, 85, "White");
                    std::string text_edit = "";
                    SDL_StartTextInput;
                    while (true) {
                        SDL_Event evt;
                        SDL_PollEvent(&evt);
                        if (evt.type == SDL_TEXTINPUT)
                            if (text_edit.length() <= 3 && isdigit(evt.text.text[0]))
                            {
                                text_edit += evt.text.text;
                                printText(23, 255, 255, 255, text_edit, linked_list[i].x_begin + 10, 60, 0, 0);
                            }
                        if (evt.type == SDL_KEYDOWN) {
                            if (evt.key.keysym.sym == SDLK_BACKSPACE)
                                if (text_edit.length() > 0)
                                {
                                    txtinp = false;
                                    text_edit.pop_back();
                                    makeRectangle(linked_list[i].x_begin, 50, 100, 45, text_edit, 23, "Blue", false, false, true);
                                    printText(23, 255, 255, 255, text_edit, linked_list[i].x_begin + 10, 60, 0, 0);
                                    makeLine(linked_list[i].x_begin + 5, 60, linked_list[i].x_begin + 5, 85, "White");
                                }
                            if (evt.key.keysym.sym == SDLK_KP_ENTER || evt.key.keysym.sym == SDLK_RETURN)
                            {
                                if (text_edit.length() > 0) {
                                    txtinp = false;
                                    makeRectangle(linked_list[i].x_begin, 50, 100, 45, current_value, 23, "Blue", false, false, true);
                                    Edit_data(i);
                                    makeRectangle(linked_list[i].x_begin, 50, 100, 45, text_edit, 23, "Blue", false, false, true);
                                    linked_list[i].nameID = text_edit.c_str();
                                    break;
                                }
                                makeRectangle(linked_list[i].x_begin, 50, 100, 45, current_value, 23, "Blue", false, false, true);
                                break;
                            }
                        }
                        if (evt.type == SDL_MOUSEBUTTONDOWN) {
                            makeRectangle(linked_list[i].x_begin, 50, 100, 45, current_value, 23, "Blue", false, false, true);
                            break;
                        }
                    }
                    break;
                } //Edit data
                if (state_btn[i].nameID == "Random Data") {
                    random_data_stack(); break;
                }
                if (state_btn[i].nameID == "Push") //Push data
                {
                    check_1st_time.menu_add = false;
                    show_menu_add = true;
                    makeRectangle(202, state_btn_map["Push"].y_begin, 150, 32, "Vertex = ", 19, "Green", false, false, true);
                    //create input box
                    makeRectangle(272, state_btn_map["Push"].y_begin + 5, 40, 25, "input_box", 19, "Black", false, false, false);
                    save_state_btn_map(272, state_btn_map["Push"].y_begin + 5, 40, 25, "input_box");
                    makeLine(272 + 2, state_btn_map["Push"].y_begin + 5 + 2, 272 + 2, state_btn_map["Push"].y_begin + 7 + 20, "White");
                    std::string inputText = "";
                    SDL_StartTextInput;
                    while (true) {
                        SDL_Event e;
                        SDL_PollEvent(&e);
                        if (e.type == SDL_TEXTINPUT) {
                            if (inputText.length() <= 3)
                                if (isdigit(e.text.text[0])) {
                                    inputText += e.text.text;
                                    printText(15, 255, 255, 255, inputText, 272 + 2, state_btn_map["Push"].y_begin + 5 + 2, 0, 0);
                                    e.type = 0;
                                }
                        }
                        else if (e.type == SDL_KEYDOWN)
                        {
                            if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0) {
                                inputText.pop_back();
                                makeRectangle(state_btn_map["input_box"].x_begin, state_btn_map["input_box"].y_begin, 40, 25, inputText, 15, "Black", false, false, true);
                            }
                            if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_KP_ENTER) {
                                txtinp = true;
                                makeRectangle(200, 500, 500, 152, "", 0, "White", false, false, false);
                                if (inputText.length() > 0 && number_node < 10) {
                                    int buttonid = messbox("", "Choose how to run", 2, "Run step by step", "Run at once");
                                    if (buttonid == 0) { //run at once
                                        insert_first_data(inputText, linked_list);
                                    }
                                    else { //run step by step
                                        insert_first_step(inputText, 1, linked_list);
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
                        makeLine(state_btn_map["input_box"].x_begin + 2, state_btn_map["input_box"].y_begin + 2, state_btn_map["input_box"].x_begin + 2, state_btn_map["input_box"].y_end - 2, "White");
                    }
                    // SDL_StopTextInput();
                    break;
                }
                if (state_btn[i].nameID == "Search")
                {
                    makeRectangle(state_btn[i].x_end + 2, state_btn[i].y_begin, 150, 32, "Vertex = ", 18, "Green", false, false, true);
                    makeLine(state_btn[i].x_end + 152 - 70, state_btn[i].y_begin + 10, state_btn[i].x_end + 152 - 70, state_btn[i].y_end - 10, "White");
                    std::string text_find = "";
                    SDL_StartTextInput;
                    while (true) {
                        SDL_Event evt;
                        SDL_PollEvent(&evt);
                        if (evt.type == SDL_TEXTINPUT)
                            if (text_find.length() <= 3 && isdigit(evt.text.text[0]))
                            {
                                text_find += evt.text.text;
                                printText(18, 255, 255, 255, text_find, state_btn[i].x_end + 152 - 68, state_btn[i].y_begin + 10, 0, 0);
                            }
                        if (evt.type == SDL_KEYDOWN) {
                            if (evt.key.keysym.sym == SDLK_BACKSPACE)
                                if (text_find.length() > 0)
                                {
                                    txtinp = false;
                                    text_find.pop_back();
                                    makeRectangle(state_btn[i].x_end + 2, state_btn[i].y_begin, 150, 32, "Vertex = ", 18, "Green", false, false, true);
                                    printText(23, 255, 255, 255, text_find, state_btn[i].x_end + 152 - 68, state_btn[i].y_begin + 20, 0, 0);
                                    makeLine(state_btn[i].x_end + 152 - 70, state_btn[i].y_begin + 10, state_btn[i].x_end + 152 - 70, state_btn[i].y_end - 10, "White");
                                }
                            if (evt.key.keysym.sym == SDLK_KP_ENTER || evt.key.keysym.sym == SDLK_RETURN)
                            {
                                makeRectangle(state_btn[i].x_end + 2, state_btn[i].y_begin, 150, 32, "Vertex = ", 18, "White", false, false, true);
                                break;
                            }
                        }
                        if (evt.type == SDL_MOUSEBUTTONDOWN) {
                            makeRectangle(state_btn[i].x_end + 2, state_btn[i].y_begin, 150, 32, "Vertex = ", 18, "White", false, false, true);
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
                                if (i == number_node || text_find == linked_list[i].nameID) break;
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
                            if (i == number_node && text_find != linked_list[i].nameID)
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
                                search_Step(text_find, 1, 50, 1, linked_list);
                            }
                    }
                    cancel_menu = false;

                }
                ///////////////////////////////////////////Delete data
                if (state_btn[i].nameID == "Pop") 
                {
                    check_1st_time.menu_del = false;
                    show_menu_add_del = true;
                    tempt = i;
                    show_menu_add_del = false;
                    drawRec(200,500,200, 152, false, "", 0, "White");
                        if (number_node >= 2)
                        {
                            int buttonid = messbox("", "Choose how to run", 2, "Run step by step", "Run at once");
                            if (buttonid == 0)
                            { //run at once

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
                                makeRectangle(50, 105, 150, 45, "", 0, "White", false, false, false);
                                printText(22, 0, 0, 0, "Temp", 60, 105, 0, 0);
                                while (x_line < 200) {
                                    makeLine(x_line, 75, x_line + 5, 75, "Orange");
                                    x_line += 5;
                                    SDL_Delay(50);
                                }
                                if (number_node - 1 == 1)
                                {
                                    drawRec(210, 105, 100, 45, false, "", 22, "White");
                                    printText(22, 0, 0, 0, "Head", 210, 105, 0, 0);
                                }
                                printText(22, 0, 0, 0, "Head", 210, 105, 0, 0);
                                SDL_Delay(200);
                                makeRectangle(50, 50, 150, 45, "", 0, "White", false, false, false);
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
                                    makeRectangle(50, 50, 1500, 150, "", 0, "White", false, false, false);
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
                                update_vector(0, number_node, true, false, "");
                            }
                                else
                                { //run step by step
                                    delete_first_step(1, linked_list);
                                }
                        }
                        else
                            if (number_node - 1 == 0)
                            {
                                number_node--;
                                draw_bound_rec(50, 50, 100, 45, "Orange");
                                SDL_Delay(300);
                                drawRec(50, 50, 100, 150, false, "", 22, "White");
                                linked_list[1] = {};
                            }                         
                        break;
                }
            }
        }
        if (show_menu_add_del == true)
        {
            if (state_btn[tempt].nameID != "Delete")
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
void Game::render_stack(std::vector<coordinates> linkedlist) {
    //SDL_RenderClear(renderer); // Clear the screen
    linked_list = linkedlist;
    if (count == 0) {
        std::cout << "It works" << std::endl;
        for (int i = 1; i <= number_node; i++) {
            if (i == 1) head = true;

            if (i == number_node) tail = true;
            stack(linked_list[i].nameID, i);
            head = false; tail = false;
        }
        count = 1;
    }
    SDL_RenderPresent(renderer); // Show the rendered image on the screen
}
void Game::stack(std::string value, int current_node) 
{
    SDL_Rect rect = { edge.x, edge.y, 100,45 };
    SDL_SetRenderDrawColor(renderer, 100, 149, 237, 0); //blue
    SDL_RenderFillRect(renderer, &rect);
    // Draw the text texture inside the rectangle
    printText(23, 255, 255, 255, value.c_str(), rect.x + 10, rect.y + 10, 0, 0);
    //save liked list
    linked_list[current_node].x_begin = rect.x; linked_list[current_node].x_end = rect.x + rect.w;
    linked_list[current_node].y_begin = rect.y; linked_list[current_node].y_end = rect.y + 45;
    linked_list[current_node].nameID = value.c_str();
    // Draw line
    if (!tail) {
        makeLine(rect.x + rect.w, rect.y + 25, rect.x + rect.w + 50, rect.y + 25, "Black");
        edge.x = rect.x + rect.w + 50;
        edge.y = rect.y;
    }
    if (head) {
        printText(22, 0, 0, 0, "Head", rect.x + 10, rect.y + rect.h + 10, 0, 0);
    }
    if (tail) {
        state_btn_map["Tail"].x_begin = rect.x;
        state_btn_map["Tail"].x_end = rect.x + 100;
        state_btn_map["Tail"].y_begin = 50;
        state_btn_map["Tail"].y_end = 95;
        printText(22, 0, 0, 0, "Tail", rect.x + 25, rect.y + rect.h + 10, 0, 0);
    }
    btn_map = true;
    if (!menu_linkedlist)
    {
        drawRec(50, 500, 150, 38, true,"Random Data",20,"Green");
        save_state_btn(50, 500, 150, 38, "Random Data");
        save_state_btn_map(50, 500, 150, 38, "Random Data");
        number_coorbtn++;
        drawRec(50, state_btn[number_coorbtn - 1].y_end + 2, 150, 38, true, "Push", 20, "Green");
        save_state_btn(50, state_btn[number_coorbtn - 1].y_end + 2, 150, 38, "Push");
        save_state_btn_map(50, state_btn[number_coorbtn - 1].y_end + 2, 150, 38, "Push");
        number_coorbtn++;
        drawRec(50, state_btn[number_coorbtn - 1].y_end + 2, 150, 38, true, "Pop", 20, "Green");
        save_state_btn(50, state_btn[number_coorbtn - 1].y_end + 2, 150, 38, "Pop");
        save_state_btn_map(50, state_btn[number_coorbtn - 1].y_end + 2, 150, 38, "Pop");
        number_coorbtn++;
        drawRec(50, state_btn[number_coorbtn - 1].y_end + 2, 150, 38, true, "Search", 20, "Green");
        save_state_btn(50, state_btn[number_coorbtn - 1].y_end + 2, 150, 38, "Search");
        save_state_btn_map(50, state_btn[number_coorbtn - 1].y_end + 2, 150, 38, "Search");
        number_coorbtn++;
        menu_linkedlist = true;
    }
}