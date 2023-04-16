#include "VD.h"
Game::Game()
{}
Game::~Game() {}
#include "var.h"

void Game::rec_move(int x_pos, int y_pos, int y_end,std::string value) {
    save_state = false;

    
    while (y_pos>=y_end)
    {
        makeRectangle(x_pos, y_pos, 100, 45, value, 23, "Blue", false, false, true);
        if (y_pos-95>=0)
        makeLine(x_pos + 50, y_pos, x_pos + 50, y_pos - (y_pos - 95),"Black");
        SDL_Delay(20);
        txtinp = true;
        makeRectangle(x_pos, y_pos, 100, 45, value, 23, "White", false, false, true);
        txtinp = false;
        y_pos -= 5;
    }
    save_state = true;
}
int  Game::messbox(std::string title, std::string content, int num_button, std:: string name_btn1, std::string name_btn2) {
    SDL_MessageBoxButtonData buttons[] = {
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, name_btn2.c_str() },
        { 0, 1,name_btn1.c_str() }
    };

    SDL_MessageBoxData messageboxdata = {
       SDL_MESSAGEBOX_INFORMATION, // Loại hộp thoại
       NULL, // Cửa sổ cha (NULL là cửa sổ mặc định)
       title.c_str(), // Tiêu đề (rỗng)
       content.c_str(), // Nội dung
       num_button, // Số lượng nút tùy chọn là 2
       buttons, // Mảng chứa các nút tùy chọn
       NULL // Nút mặc định (NULL là không có nút mặc định)
    };
    int buttonid;
    SDL_ShowMessageBox(&messageboxdata, &buttonid);
    return buttonid;
}
void Game::previous_stage(Uint32 *&pixels, int& stage, int width) {
    //paste
    int height = 500;
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, height);
    SDL_UpdateTexture(texture, nullptr, pixels, width * sizeof(Uint32));
    SDL_Rect destination = { 50,50,width, height };
    SDL_RenderCopy(renderer, texture, nullptr, &destination);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
    delete[] pixels;
    pixels_stage.pop_back();
    stage--;
}
void Game::draw_bound_rec(int x_pos,int y_pos,int width, int height,std::string namecolor) {
    SDL_Rect rect = {x_pos,y_pos,width,height};
    SDL_SetRenderDrawColor(renderer,color[namecolor][0],color[namecolor][1],color[namecolor][2], 0); //3 channels of color
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}
void Game::search_Step(std::string value, int stage, int x, int i, std::vector<coordinates>& linked_list)
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
                    draw_bound_rec(x, 50, 100, 45, "Orange");
                    makeLine(x + 100, 75, x + 150, 75, "Orange");
                    x += 150;
                    i++;
                    if (x == linked_list[number_node].x_begin || linked_list[i].nameID == value) {
                        int width = 1500;
                        SDL_Rect section = { 50,50,width,500 };
                        Uint32* pixels = new Uint32[width * 500];
                        SDL_RenderReadPixels(renderer, &section, SDL_PIXELFORMAT_ARGB8888, pixels, width * sizeof(Uint32));
                        pixels_stage.push_back(pixels);
                        draw_bound_rec(linked_list[i].x_begin, 50, 100, 45, "Orange");
                        stage++; back = false;
                        break;
                    }
                }
                if (e.key.keysym.sym == SDLK_LEFT)
                {
                    if (x != 50) {
                        i--;
                        x -= 150;
                        draw_bound_rec(x, 50, 100, 45, "Blue");
                        makeLine(x + 100, 75, x + 150, 75, "Black");
                    }
                }
            }

        }
    }
    if (stage == 2) {
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
                        draw_bound_rec(t, 50, 100, 45, "Blue");
                        dem++;
                        if (dem == number_node+1) break;
                        makeLine(t + 100, 75, t + 150, 75, "Black");
                        t += 150;


                    }
                    messbox("", "Finish", 1, "", "OK");
                    pixels_stage.clear();
                    break;
                }
                if (e.key.keysym.sym == SDLK_LEFT)
                {
                    back = true;
                    previous_stage(pixels_stage.back(), stage, 1500);
                    search_Step(value,stage,x,i,linked_list);
                    break;
                }
            }
        }
    }
}
void Game::insert_last_step(std::string value, int stage)
{
    int x = 50;
    if (stage == 1) {
        if (back) {
            x = number_node;
        }
        while (true)
        {
            SDL_Event e;
            SDL_PollEvent(&e);
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_RIGHT)
                {
                    if (x == linked_list[number_node].x_begin) {
                        stage++; back = false; break;
                    }
                    draw_bound_rec(x, 50, 100, 45, "Orange");
                    makeLine(x + 100, 75, x + 150, 75, "Orange");
                    x += 150;
                    if (x == linked_list[number_node].x_begin) {
                        draw_bound_rec(x, 50, 100, 45, "Orange");
                    }
                }
                if (e.key.keysym.sym == SDLK_LEFT)
                {
                    if (x != 50) {
                        x -= 150;
                        draw_bound_rec(x, 50, 100, 45, "Blue");
                        makeLine(x + 100, 75, x + 150, 75, "Black");
                    }
                }
            }

        }
    }
    if (stage == 2) {
        if (!back) {
            //copy
            int width = 1500;
            SDL_Rect section = { 50,50,width,500 };
            Uint32* pixels = new Uint32[width * 500];
            SDL_RenderReadPixels(renderer, &section, SDL_PIXELFORMAT_ARGB8888, pixels, width * sizeof(Uint32));
            pixels_stage.push_back(pixels);
            drawRec(linked_list[number_node].x_end+50,50,100, 45, true, value, 23, "Blue");
        }
        while (true) {
            SDL_Event e;
            SDL_PollEvent(&e);
            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_RIGHT)
                {
                    stage++;
                    break;
                }
                if (e.key.keysym.sym == SDLK_LEFT)
                {
                    back = true;
                    previous_stage(pixels_stage.back(), stage, 1500);
                    insert_last_step(value, stage);
                    break;
                }
            }
        }
    }
    if (stage == 3)
    {
        if (!back) {
            //copy
            int width = 1500;
            SDL_Rect section = { 50,50,width,500 };
            Uint32* pixels = new Uint32[width * 500];
            SDL_RenderReadPixels(renderer, &section, SDL_PIXELFORMAT_ARGB8888, pixels, width * sizeof(Uint32));
            pixels_stage.push_back(pixels);
            //
            draw_bound_rec(linked_list[number_node].x_end + 50, 50, 100, 45,"Orange");
            makeLine(linked_list[number_node].x_end, 75, linked_list[number_node].x_end + 50, 75, "Orange");

        }
        while (true) {
            SDL_Event e;
            SDL_PollEvent(&e);
            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_RIGHT)
                {
                    linked_list[number_node + 1].x_begin = linked_list[number_node].x_begin + 150;
                    linked_list[number_node + 1].x_end = linked_list[number_node].x_end + 150;
                    linked_list[number_node + 1].y_begin = linked_list[number_node + 1].y_end = 50;
                    linked_list[number_node + 1].nameID = value;
                    number_node++;
                    x = 50;
                    int dem = 1;
                    while (true) {
                        draw_bound_rec(x, 50, 100, 45, "Blue");
                        dem++;
                        x += 150;
                        if (dem == number_node+1) break;
                        makeLine(x + 100, 75, x + 150, 75, "Black");

                    }
                    messbox("", "Finish", 1, "", "OK");
                    pixels_stage.clear();
                    break;
                }
                if (e.key.keysym.sym == SDLK_LEFT)
                {
                    back = true;
                    previous_stage(pixels_stage.back(), stage,1500);
                    insert_last_step(value, stage);
                    break;
                }
            }
        }
    }
}
void Game::insert_middle_step(std::string value, int stage) 
{
    int x = 50;
    if (stage == 1) {
        if (back) {
            x = (number_node / 2 + 1) * 150 + 50;
        }
        while (true)
        {
            SDL_Event e;
            SDL_PollEvent(&e);
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_RIGHT)
                {
                    if (x == (number_node / 2 + 1) * 150 + 50) { stage++; back = false; break; }
                    draw_bound_rec(x, 50, 100, 45, "Orange");
                    makeLine(x+100, 75, x +150, 75, "Orange");
                    x += 150;
                }
                if (e.key.keysym.sym == SDLK_LEFT)
                {
                    if (x != 50) {
                        x -= 150;
                        draw_bound_rec(x, 50, 100, 45, "Blue");
                        makeLine(x + 100, 75, x + 150, 75, "Black");
                    }
                }
            }

        }
    }
    if (stage == 2) {
        if (!back) {
            //copy
            int width = 1500;
            SDL_Rect section = { 50,50,width,500 };
            Uint32* pixels = new Uint32[width * 500];
            SDL_RenderReadPixels(renderer, &section, SDL_PIXELFORMAT_ARGB8888, pixels, width * sizeof(Uint32));
            pixels_stage.push_back(pixels);
            drawRec(linked_list[number_node / 2 + 2].x_begin, linked_list[number_node / 2 + 2].y_end + 50, 100, 45, true, value, 23, "Blue");
            //draw line link new node to aft node
            makeLine(linked_list[number_node / 2 + 2].x_begin + 50, linked_list[number_node / 2 + 2].y_end + 50, linked_list[number_node / 2 + 2].x_begin + 50, linked_list[number_node / 2 + 2].y_end, "Orange");
            SDL_Delay(300);
            //draw line link prev node to new node
            int y = linked_list[number_node / 2 + 1].y_begin + 20;
            while (true) {
                y += 5;
                drawRec(linked_list[number_node / 2 + 1].x_end, 50, 50, 150, true, value, 23, "White");
                makeLine(linked_list[number_node / 2 + 1].x_end, linked_list[number_node / 2 + 1].y_begin + 20, linked_list[number_node / 2 + 1].x_end + 50, y, "Orange");
                if (y == linked_list[number_node / 2 + 2].y_end + 70) break;
                SDL_Delay(15);
            }
            SDL_Delay(400);
            //copy
            width = linked_list[number_node].x_end - linked_list[number_node / 2 + 2].x_begin;            
            section = { linked_list[number_node / 2 + 2].x_begin,50,width,45 };
            Uint32* pixels2 = new Uint32[width * 80];
            SDL_RenderReadPixels(renderer, &section, SDL_PIXELFORMAT_ARGB8888, pixels2, width * sizeof(Uint32));
            drawRec(linked_list[number_node / 2 + 2].x_begin, 50, width, 45, false, "", 0, "White");
            //paste
            int height = 45;
            SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, height);
            SDL_UpdateTexture(texture, nullptr, pixels2, width * sizeof(Uint32));
            SDL_Rect destination = { linked_list[number_node / 2 + 2].x_end+50,50,width, height };
            SDL_RenderCopy(renderer, texture, nullptr, &destination);
            SDL_RenderPresent(renderer);
            SDL_DestroyTexture(texture);
            delete[] pixels2;
            drawRec(linked_list[number_node / 2 + 1].x_end, 50,150, 500, false, "", 0, "White");
            drawRec(linked_list[number_node / 2 + 2].x_begin,50, 100, 45, true, value, 23, "Blue");
            makeLine(linked_list[number_node / 2 + 1].x_end,75, linked_list[number_node / 2 + 1].x_end + 50,75, "Orange");          
            makeLine(linked_list[number_node / 2 + 2].x_end, 75, linked_list[number_node / 2 + 2].x_end + 50, 75, "Orange");
            drawRec(linked_list[number_node].x_begin,105,100, 30, false, "", 0, "White");
            printText(23,0, 0, 0,"Tail", linked_list[number_node].x_end +60,105, 0, 0);


        }
        while (true) {
            SDL_Event e;
            SDL_PollEvent(&e);
            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_RIGHT)
                {
                    number_node++;
                    update_vector(number_node / 2 + 2, number_node, false, true, value);
                    //Set line color to black and rec color to blue
                    int dem = 1;
                    x = 50;
                    while (true) {
                        SDL_Rect rect = { x,50,100,45 };
                        SDL_SetRenderDrawColor(renderer, 100, 149, 237, 0); //3 channels of color
                        SDL_RenderDrawRect(renderer, &rect);
                        SDL_RenderPresent(renderer);
                        dem++;
                        makeLine(x + 100, 75, x + 150, 75, "Black");
                        x += 150;
                        if (dem == number_node) break;
                    }
                    messbox("", "Finish", 1, "", "OK");
                    pixels_stage.clear();
                    break;
                }
                if (e.key.keysym.sym == SDLK_LEFT)
                {
                    back = true;
                    previous_stage(pixels_stage.back(), stage,1500);
                    insert_middle_step(value, stage);
                    break;
                }
            }
        }
    }
}
void Game::insert_first_step(std::string value, int stage, std::vector<coordinates> &linked_list) {
    if (stage == 0) {
        while (true)
        {
            SDL_Event e;
            SDL_PollEvent(&e);

            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_RIGHT)
                {
                    stage++;
                    back = false;
                    break;
                }

            }
        }
    }
    if (stage == 1)
    {
        //copy
        if (!back) {
            int width = 100;
            int height = 500;
            SDL_Rect section = { 50,50,100,height };
            Uint32* pixels = new Uint32[width * height];
            SDL_RenderReadPixels(renderer, &section, SDL_PIXELFORMAT_ARGB8888, pixels, width * sizeof(Uint32));
            pixels_stage.push_back(pixels);
            drawRec(50, 160, 100, 45, true, value, 23, "Blue");
        }
        while (true)
        {
            SDL_Event e;
            SDL_PollEvent(&e);

            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_LEFT)
                {
                    back = true;
                    previous_stage(pixels_stage.back(), stage,100);
                    insert_first_step(value, stage,linked_list);
                    break;
                }
                else if (e.key.keysym.sym == SDLK_RIGHT) {
                    stage++;
                    back = false;
                    break;
                }
            }
        }
    }
    if (stage == 2) //draw black line link to pre node
    {
        if (!back) {
            //copy
            int width = 100;
            int height = 500;
            SDL_Rect section = { 50,50,100,height };
            Uint32* pixels = new Uint32[width * height];
            SDL_RenderReadPixels(renderer, &section, SDL_PIXELFORMAT_ARGB8888, pixels, width * sizeof(Uint32));
            pixels_stage.push_back(pixels);
                makeLine(100, 160, 100, 95, "Black");
        }
        while (true)
        {
            SDL_Event e;
            SDL_PollEvent(&e);

            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_LEFT)
                {
                    back = true;
                    previous_stage(pixels_stage.back(), stage,100);
                    insert_first_step(value, stage,linked_list);
                    break;
                }
                else if (e.key.keysym.sym == SDLK_RIGHT) {
                    stage++;
                    back = false;
                    break;
                }
            }
        }
    }
    if (stage == 3) //move node
    {
        if (!back) {
            drawRec(50, 105, 1500, 25, true, value, 23, "White");
            makeLine(100, 160, 100, 95, "Black");
            //copy
            int width = 1500;
            int height = 500;
            SDL_Rect section = { 50,50,width,height };
            Uint32* pixels = new Uint32[width * height];
            SDL_RenderReadPixels(renderer, &section, SDL_PIXELFORMAT_ARGB8888, pixels, width * sizeof(Uint32));
            pixels_stage.push_back(pixels);
            rec_move(50, 160, 95, value); //move node upward
            drawRec(50, 95, 100, 45, true, value, 23, "Blue");
            number_node++;
        }
        int x = 50;
        while (x < 200) { //move node to the right
            int width = 1500 - x;
            //copy
            SDL_Rect section = { x,50,width,45 };
            Uint32* pixels = new Uint32[width * 45];
            SDL_RenderReadPixels(renderer, &section, SDL_PIXELFORMAT_ARGB8888, pixels, width * sizeof(Uint32));
            //delete all old node
            makeRectangle(x, 50, 1500, 45, value, 23, "White", false, false, true);
            //paste
            SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, 45);
            SDL_UpdateTexture(texture, nullptr, pixels, width * sizeof(Uint32));
            SDL_Rect destination = { x + 5,50,width, 45 };
            SDL_RenderCopy(renderer, texture, nullptr, &destination);
            SDL_RenderPresent(renderer);
            SDL_DestroyTexture(texture);
            delete[] pixels;
            SDL_Delay(15);
            x += 5;
        }
        rec_move(50, 95, 50, value); //move node to y_pos = 50
        makeRectangle(50, 50, 100, 45, value, 23, "Blue", false, false, true);
        makeLine(150, 75, 200, 75, "Black");
        printText(22, 0, 0, 0, "Head", 60, 105, 0, 0);
        while (true)
        {
            SDL_Event e;
            SDL_PollEvent(&e);

            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_LEFT)
                {
                    back = true;
                    number_node--;
                    previous_stage(pixels_stage.back(), stage,1500);
                    insert_first_step(value, stage,linked_list);
                    break;
                }
                else if (e.key.keysym.sym == SDLK_RIGHT) {
                    stage++;
                    back = false;
                    coordinates newElement = { 50, 100, 50, 50,value };
                    linked_list.insert(linked_list.begin() + 1, newElement);
                    for (int i = 2; i <= number_node; i++) {
                        linked_list[i].x_begin += 150;
                        linked_list[i].x_end += 150;
                    }
                    printText(22, 0, 0, 0, "Tail", linked_list[number_node].x_begin + 25, 105, 0, 0);
                    messbox("", "Finish", 1, "", "OK");
                    pixels_stage.clear();
                    break;
                }
            }
        }
    }
}
void Game::insert_first_data(std::string value, std::vector<coordinates>& linked_list){
    if (number_node >= 1)
    {
        txtinp = true;
        save_state = false;
        drawRec(50, 105, 1500, 25, true, value, 23, "White");
        txtinp = false;
        drawRec(50, 160, 100, 45, true, value, 23, "Blue");
        SDL_Delay(300);
        makeLine(100, 160, 100, 95, "Black");
        SDL_Delay(300);
        number_node += 1;
        rec_move(50, 160, 95, value);
        drawRec(50, 95, 100, 45, true, value, 23, "Blue");
        int x = 50;
        while (x < 200) {
            int width = 1500 - x;
            //copy
            SDL_Rect section = { x,50,width,45 };
            Uint32* pixels = new Uint32[width * 45];
            SDL_RenderReadPixels(renderer, &section, SDL_PIXELFORMAT_ARGB8888, pixels, width * sizeof(Uint32));
            //delete all old node
            makeRectangle(x, 50, 1500, 45, value, 23, "White", false, false, true);
            //paste
            SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, 45);
            SDL_UpdateTexture(texture, nullptr, pixels, width * sizeof(Uint32));
            SDL_Rect destination = { x + 5,50,width, 45 };
            SDL_RenderCopy(renderer, texture, nullptr, &destination);
            SDL_RenderPresent(renderer);
            SDL_DestroyTexture(texture);
            delete[] pixels;
            SDL_Delay(15);
            x += 5;
        }
        rec_move(50, 95, 50, value);
        makeRectangle(50, 50, 100, 45, value, 23, "Blue", false, false, true);
        makeLine(150, 75, 200, 75, "Black");
        printText(22, 0, 0, 0, "Head", 60, 105, 0, 0);
        coordinates newElement = { 50, 100, 50, 50,value };
        linked_list.insert(linked_list.begin() + 1, newElement);
        for (int i = 2; i <= number_node; i++) {
            linked_list[i].x_begin += 150;
            linked_list[i].x_end += 150;
        }
        printText(22, 0, 0, 0, "Tail", linked_list[number_node].x_begin + 25, 105, 0, 0);
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
void Game::insert_last_data(std::string value)
{
    loop_node(number_node-2, "insert", false);
    drawRec(linked_list[2].x_begin, 105, linked_list[number_node].x_end - linked_list[2].x_begin,40,false,"",0,"White");
    int x = 0;
    int x_end = linked_list[number_node].x_end;
    makeRectangle(linked_list[number_node].x_end + 50, 50, 100, 45, value, 23, "Blue",false,false,true);
    SDL_Delay(500);
    while (x<50) {
        makeLine(x_end,75, x_end+5,75,"Black");
        x += 5; x_end += 5;
        SDL_Delay(50);
    }
    printText(22, 0, 0, 0, "Tail", linked_list[number_node].x_begin + 150 + 25, 105, 0, 0);
    linked_list[number_node + 1].x_begin = linked_list[number_node].x_begin+ 150;
    linked_list[number_node + 1].x_end = linked_list[number_node].x_end + 150;
    linked_list[number_node + 1].y_begin = linked_list[number_node + 1].y_end = 50;
    linked_list[number_node + 1].nameID = value;
    number_node++;
    //Set line color to black and rec color to blue
    int dem = 1;
    x = 50;
    while (true) {
        SDL_Rect rect = { x,50,100,45 };
        SDL_SetRenderDrawColor(renderer, 100, 149, 237, 0); //3 channels of color
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderPresent(renderer);
        dem++;
        makeLine(x + 100, 75, x + 150, 75, "Black");
        x += 150;
        if (dem == number_node) break;
    }

}   
void Game::loop_node(int pos, std::string task, bool del_text) {
    btn_map = false;
    txtinp = true;
    save_state = false;
    int i = 1;
    int x = 50; int x_line = 150;
    if (!del_text) {
        while (true) {
            SDL_Rect rect = { x,50,100,45 };
            SDL_SetRenderDrawColor(renderer, 255, 165, 0, 0); //3 channels of color
            SDL_RenderDrawRect(renderer, &rect);
            SDL_RenderPresent(renderer);
            int t = x_line;
            if (i == pos + 1)
            {
                rect = { x + 150,50,100,45 };
                SDL_SetRenderDrawColor(renderer, 255, 165, 0, 0); //3 channels of color
                SDL_RenderDrawRect(renderer, &rect);
                SDL_RenderPresent(renderer);
                int t = x_line;
                while (x_line < t + 50) {
                    makeLine(x_line, 75, x_line + 5, 75, "Orange");
                    x_line += 5;
                    SDL_Delay(30);
                    std::string print_text = std::to_string(i - 1) + "/pre";
                }
                std::string print_text = std::to_string(i - 1) + "/" + task;
                printText(22, 0, 0, 0, print_text, x + 10, 105, 0, 0);
                if (i != number_node - 1) {
                    print_text = std::to_string(i) + "/Aft";
                    printText(22, 0, 0, 0, print_text, x + 10 + 150, 105, 0, 0);
                }
                break;
            }
            while (x_line < t + 50) {
                makeLine(x_line, 75, x_line + 5, 75, "Orange");
                x_line += 5;
                SDL_Delay(40);
            }
            if (i >= 2) {
                std::string print_text = std::to_string(i - 1) + "/pre";
                printText(22, 0, 0, 0, print_text, x + 10, 105, 0, 0);
            }
            x_line += 100;
            x += 150;
            SDL_Delay(200);
            i++;
        }
    }
    else
    if (i != number_node - 1) {
        i = pos + 1;
        x = linked_list[i].x_begin;
            drawRec(x + 10 + 150, 100, 90, 50, false, "", 0, "White");
            std::string print_text = std::to_string(i - 1) + "/Aft";
            printText(22, 0, 0, 0, print_text, x + 10 + 150, 105, 0, 0);
        }
}
void Game::insert_middle(std::string value) {
    loop_node(number_node / 2, "pre", false);
    //draw rec in the bottom of aft node
    drawRec(linked_list[number_node / 2 + 2].x_begin, linked_list[number_node / 2 + 2].y_end + 50, 100, 45, true, value, 23, "Blue");
    //draw line link new node to aft node
    makeLine(linked_list[number_node / 2 + 2].x_begin + 50, linked_list[number_node / 2 + 2].y_end + 50, linked_list[number_node / 2 + 2].x_begin + 50, linked_list[number_node / 2 + 2].y_end, "Orange");
    SDL_Delay(500);
    //draw line link prev node to new node
    int y = linked_list[number_node / 2 + 1].y_begin + 20;
    while (true) {
        y += 5;
        drawRec(linked_list[number_node /2+1].x_end,50,50,150, true, value, 23, "White");
        makeLine(linked_list[number_node / 2 + 1].x_end, linked_list[number_node/2+1].y_begin+20, linked_list[number_node/2+1].x_end+50,y, "Orange");
        if (y == linked_list[number_node / 2 + 2].y_end + 70) break;
        SDL_Delay(15);
    }
    //move new node to upward and aft node to the right
    y = 50;
    int x = 0;
    int width = linked_list[number_node].x_end - linked_list[number_node / 2 + 2].x_begin ;
    SDL_Rect section = { linked_list[number_node / 2 + 2].x_begin,50,width,80 };
    Uint32* pixels = new Uint32[width * 80];
    SDL_RenderReadPixels(renderer, &section, SDL_PIXELFORMAT_ARGB8888, pixels, width * sizeof(Uint32));
    int y_line = 75;
    while (true) {
        //move to the right
        drawRec(linked_list[number_node / 2 + 2].x_begin + x, 50, width, 80, true, value, 23, "White");
        x += 5;
        SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, 80);
        SDL_UpdateTexture(texture, nullptr, pixels, width * sizeof(Uint32));
        SDL_Rect destination = { linked_list[number_node / 2 + 2].x_begin + x,50,width,80 };
        SDL_RenderCopy(renderer, texture, nullptr, &destination);
        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(texture);
        if (x == 150) break;
        if (y != -45) {
            y_line -= 5;
            drawRec(linked_list[number_node / 2 + 2].x_begin, linked_list[number_node / 2 + 2].y_end + y, 100, 45, true, value, 23, "White");
            drawRec(linked_list[number_node / 2 + 1].x_end, 50, 50, 150, true, value, 23, "White");
            y -= 5;
            drawRec(linked_list[number_node / 2 + 2].x_begin, linked_list[number_node / 2 + 2].y_end + y, 100, 45, true, value, 23, "Blue");
            SDL_Rect rect = { linked_list[number_node / 2 + 2].x_begin,linked_list[number_node / 2 + 2].y_end + y,100,45 };
            SDL_SetRenderDrawColor(renderer, 255, 165, 0, 0); //3 channels of color
            SDL_RenderDrawRect(renderer, &rect);
            SDL_RenderPresent(renderer);
            makeLine(linked_list[number_node / 2 + 1].x_end, linked_list[number_node / 2 + 1].y_begin + 25, linked_list[number_node / 2 + 1].x_end + 50, linked_list[number_node / 2 + 2].y_end +y_line, "Orange");

        }
        SDL_Delay(20);
    }
    drawRec(linked_list[number_node / 2 + 2].x_begin, linked_list[number_node / 2 + 2].y_end + y, 100, 45, true, value, 23, "Blue");
    SDL_Rect rect = { linked_list[number_node / 2 + 2].x_begin,linked_list[number_node / 2 + 2].y_end + y,100,45 };
    SDL_SetRenderDrawColor(renderer, 255, 165, 0, 0); //3 channels of color
    SDL_RenderDrawRect(renderer, &rect);
    delete[] pixels;
    drawRec(linked_list[2].x_begin, 95, linked_list[number_node-1].x_end - linked_list[1].x_begin, 100, false, "", 0, "White");
    makeLine(linked_list[number_node / 2 + 2].x_end, 75, linked_list[number_node / 2 + 2].x_end + 50,75, "Orange");
    number_node++;
    update_vector(number_node / 2 + 2, number_node, false, true, value);
    //Set line color to black and rec color to blue
    int dem = 1;
    x = 50;
    while (true) {
        SDL_Rect rect = { x,50,100,45 };
        SDL_SetRenderDrawColor(renderer, 100, 149, 237, 0); //3 channels of color
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderPresent(renderer);
        dem++;
        if (dem == number_node+1) break;
        makeLine(x + 100, 75, x + 150, 75, "Black");
        x += 150;
    }
    drawRec(linked_list[number_node].x_begin, 95, 100, 100, false, "", 0, "White");
    printText(22, 0, 0, 0, "Tail", linked_list[number_node].x_begin + 25, 95, 0, 0);
}
void Game::delete_first_step(int stage, std::vector<coordinates>& linked_list)
{
    if (stage == 0) {
        while (true)
        {
            SDL_Event e;
            SDL_PollEvent(&e);

            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_RIGHT)
                {
                    stage++;
                    back = false;
                    break;
                }

            }
        }
    }
    if (stage == 1)
    {
        //copy
        if (!back) {
            int width = 100;
            SDL_Rect section = { 50,50,100,500 };
            Uint32* pixels = new Uint32[width * 500];
            SDL_RenderReadPixels(renderer, &section, SDL_PIXELFORMAT_ARGB8888, pixels, width * sizeof(Uint32));
            pixels_stage.push_back(pixels);
            draw_bound_rec(50, 50, 100, 45,"Orange");
            drawRec(50, 100, 100, 45, false, "", 0, "White");
            printText(22, 0, 0, 0, "Tempt",70, 105, 0, 0);
        }
        while (true)
        {
            SDL_Event e;
            SDL_PollEvent(&e);

            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_LEFT)
                {
                    back = true;
                    previous_stage(pixels_stage.back(), stage, 100);
                    delete_first_step(stage, linked_list);
                    break;
                }
                else if (e.key.keysym.sym == SDLK_RIGHT) {
                    stage++;
                    back = false;
                    break;
                }
            }
        }
    }
    if (stage == 2) //draw black line link to pre node
    {
        if (!back) {
            //copy
            int width = 300;
            SDL_Rect section = { 50,50,width,500 };
            Uint32* pixels = new Uint32[width * 500];
            SDL_RenderReadPixels(renderer, &section, SDL_PIXELFORMAT_ARGB8888, pixels, width * sizeof(Uint32));
            pixels_stage.push_back(pixels);
            makeLine(150,75,200,75, "Orange");
            printText(22, 0, 0, 0, "Head",linked_list[1].x_end+70,105, 0, 0);
            draw_bound_rec(200, 50, 100, 45, "Orange");

        }
        while (true)
        {
            SDL_Event e;
            SDL_PollEvent(&e);

            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_LEFT)
                {
                    back = true;
                    previous_stage(pixels_stage.back(), stage,300);
                    delete_first_step(stage, linked_list);
                    break;
                }
                else if (e.key.keysym.sym == SDLK_RIGHT) {
                    stage++;
                    back = false;
                    break;
                }
            }
        }
    }
    if (stage == 3) //move node
    {
        if (!back) {
            //copy
            int width = 1500;
            SDL_Rect section = { 50,50,width,500 };
            Uint32* pixels = new Uint32[width * 500];
            SDL_RenderReadPixels(renderer, &section, SDL_PIXELFORMAT_ARGB8888, pixels, width * sizeof(Uint32));
            pixels_stage.push_back(pixels);
            //
            //move the second node to x = 50
            width = 1300;
            SDL_Rect section2 = {200,50,width,500 };
            Uint32* pixels2 = new Uint32[width * 500];
            SDL_RenderReadPixels(renderer, &section2, SDL_PIXELFORMAT_ARGB8888, pixels2, width * sizeof(Uint32));
            //paste
            drawRec(50, 50, 1500, 80, false, "", 0, "White");
            SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width,500);
            SDL_UpdateTexture(texture, nullptr, pixels2, width * sizeof(Uint32));
            SDL_Rect destination = {50,50,width,500};
            SDL_RenderCopy(renderer, texture, nullptr, &destination);
            SDL_RenderPresent(renderer);
            SDL_DestroyTexture(texture);
            delete[] pixels2;
            number_node--;
        }
        while (true)
        {
            SDL_Event e;
            SDL_PollEvent(&e);

            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_LEFT)
                {
                    back = true;
                    number_node--;
                    previous_stage(pixels_stage.back(), stage, 1500);
                    delete_first_step(stage, linked_list);
                    break;
                }
                else if (e.key.keysym.sym == SDLK_RIGHT) {
                    stage++;
                    back = false;
                    number_node--;
                    update_vector(0, number_node, true, false, "");
                    messbox("", "Finish", 1, "", "OK");
                    pixels_stage.clear();
                    draw_bound_rec(50, 50, 100, 45, "Blue");
                    break;
                }
            }
        }
    }
}
void Game::delete_last_step(int stage, std::vector<coordinates>& linked_list)
{
    int x = 50;
    if (stage == 1) {
        if (back) {
            x = number_node;
        }
        while (true)
        {
            SDL_Event e;
            SDL_PollEvent(&e);
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_RIGHT)
                {
                    if (x == linked_list[number_node].x_begin) {
                        stage++; back = false;
                        break;
                    }
                    draw_bound_rec(x, 50, 100, 45, "Orange");
                    makeLine(x + 100, 75, x + 150, 75, "Orange");
                    x += 150;
                    if (x == linked_list[number_node].x_begin) {
                        draw_bound_rec(x, 50, 100, 45, "Orange");
                        drawRec(linked_list[number_node].x_begin, 105, 100, 45, false, "", 0, "White");
                        printText(23, 0, 0, 0, "Del", linked_list[number_node].x_begin + 20, 105, 0, 0);
                    }
                }
                if (e.key.keysym.sym == SDLK_LEFT)
                {
                    if (x != 50) {
                        x -= 150;
                        draw_bound_rec(x, 50, 100, 45, "Blue");
                        makeLine(x + 100, 75, x + 150, 75, "Black");
                    }
                }
            }

        }
    }
    if (stage == 2) {
        if (!back) {
            //copy
            int width = 1500;
            SDL_Rect section = { 50,50,width,500 };
            Uint32* pixels = new Uint32[width * 500];
            SDL_RenderReadPixels(renderer, &section, SDL_PIXELFORMAT_ARGB8888, pixels, width * sizeof(Uint32));
            pixels_stage.push_back(pixels);
            drawRec(linked_list[number_node - 1].x_end, 50, 150, 80, false, "", 0, "White");
        }
        while (true) {
            SDL_Event e;
            SDL_PollEvent(&e);
            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_RIGHT)
                {
                    linked_list.erase(linked_list.begin()+number_node-1);
                    number_node--;
                    x = 50;
                    int dem = 1;
                    while (true) {
                        draw_bound_rec(x, 50, 100, 45, "Blue");
                        dem++;
                        x += 150;
                        if (dem == number_node) break;
                        makeLine(x + 100, 75, x + 150, 75, "Black");

                    }
                    messbox("", "Finish", 1, "", "OK");
                    pixels_stage.clear();
                    break;
                }
                if (e.key.keysym.sym == SDLK_LEFT)
                {
                    back = true;
                    previous_stage(pixels_stage.back(), stage, 1500);
                    delete_last_step(stage, linked_list);
                    break;
                }
            }
        }
    }
}
void Game::delete_middle_step(int stage) {
    int x = 50;
    if (stage == 1) {
        if (back) {
            x = (number_node / 2 + 1) * 150 + 50;
        }
        while (true)
        {
            SDL_Event e;
            SDL_PollEvent(&e);
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_RIGHT)
                {
                    if (x == (number_node / 2 + 1) * 150 + 50) { stage++; back = false; break; }
                    draw_bound_rec(x, 50, 100, 45, "Orange");
                    makeLine(x + 100, 75, x + 150, 75, "Orange");
                    x += 150;
                }
                if (e.key.keysym.sym == SDLK_LEFT)
                {
                    if (x != 50) {
                        x -= 150;
                        draw_bound_rec(x, 50, 100, 45, "Blue");
                        makeLine(x + 100, 75, x + 150, 75, "Black");
                    }
                }
            }

        }
    }
    if (stage == 2) {
        if (!back)
        {
            //copy
            int width = 1500;
            SDL_Rect section = { 50,50,width,500 };
            Uint32* pixels = new Uint32[width * 500];
            SDL_RenderReadPixels(renderer, &section, SDL_PIXELFORMAT_ARGB8888, pixels, width * sizeof(Uint32));
            pixels_stage.push_back(pixels);
            printText(23, 0, 0, 0, "Del", linked_list[number_node / 2 + 1].x_begin, 105, 0, 0);
            printText(23, 0, 0, 0, "Aft", linked_list[number_node / 2 + 2].x_begin, 105, 0, 0);

        }
        while (true) {
            SDL_Event e;
            SDL_PollEvent(&e);
            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_RIGHT)
                {
                    stage++;
                    back = false;
                    delete_middle_step(stage);
                    break;
                }
                if (e.key.keysym.sym == SDLK_LEFT)
                {
                    back = true;
                    previous_stage(pixels_stage.back(), stage, 1500);
                    delete_first_step(stage, linked_list);
                    break;
                }
            }
        }
    }
    if (stage == 3) {
            if (!back)
            {
                //copy
                int width = 1500;
                SDL_Rect section = { 50,50,width,500 };
                Uint32* pixels = new Uint32[width * 500];
                SDL_RenderReadPixels(renderer, &section, SDL_PIXELFORMAT_ARGB8888, pixels, width * sizeof(Uint32));
                pixels_stage.push_back(pixels);
                //copy the aft node to the del node
                width = 1500 - linked_list[number_node / 2 + 2].x_begin;
                section = section = { linked_list[number_node / 2 + 2].x_begin,50,width,500 };
                Uint32* pixels2 = new Uint32[width * 500];
                SDL_RenderReadPixels(renderer, &section, SDL_PIXELFORMAT_ARGB8888, pixels2, width * sizeof(Uint32));
                //Paste
                int height = 500;
                SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, height);
                SDL_UpdateTexture(texture, nullptr, pixels2, width * sizeof(Uint32));
                SDL_Rect destination = { linked_list[number_node / 2 + 1].x_begin,50,width, height };
                SDL_RenderCopy(renderer, texture, nullptr, &destination);
                SDL_RenderPresent(renderer);
                SDL_DestroyTexture(texture);
                delete[] pixels2;
            }
            while (true) {
                SDL_Event e;
                SDL_PollEvent(&e);
                if (e.type == SDL_KEYDOWN)
                {
                    if (e.key.keysym.sym == SDLK_RIGHT)
                    {
                        number_node--;
                        update_vector(number_node/2+1, number_node, true, false, "");
                        //Set line color to black and rec color to blue
                        int dem = 1;
                        x = 50;
                        while (true) {
                            SDL_Rect rect = { x,50,100,45 };
                            SDL_SetRenderDrawColor(renderer, 100, 149, 237, 0); //3 channels of color
                            SDL_RenderDrawRect(renderer, &rect);
                            SDL_RenderPresent(renderer);
                            dem++;
                            makeLine(x + 100, 75, x + 150, 75, "Black");
                            x += 150;
                            if (dem == number_node) break;
                        }
                        messbox("", "Finish", 1, "", "OK");
                        pixels_stage.clear();
                        break;
                    }
                    if (e.key.keysym.sym == SDLK_LEFT)
                    {
                        back = true;
                        previous_stage(pixels_stage.back(), stage, 1500);
                        delete_middle_step(stage);
                        break;
                    }
                }
            }
    }
}
void Game::random_data() {
    linked_list.clear();
    linked_list.resize(11);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    makeRectangle(50, 50, 1600,80,"",0,"White",false, false, false);
    txtinp = true;
    int random_value_node;
    edge.x = 50; edge.y = 50;
    menu_linkedlist = true;
    for (int j = 1; j <= 8; j++) {
        number_node = rand() % 9 + 2;
        txtinp = false;
        makeRectangle(50, 50, 1600, 80, "", 0, "White", false, false,false);
        txtinp = true;
        for (int i = 1; i <= number_node; i++) {
            random_value_node = rand() % 100 + 1;
            if (i == 1) head = true;
            if (i == number_node) tail = true;
            Linkedlist(std::to_string(random_value_node).c_str(),i);
            head = false; tail = false;
        }
        edge.x = 50;
        edge.y = 50;
        SDL_Delay(70);
    }
    SDL_RenderPresent(renderer);
    save_state = true;
}
void Game::Edit_data(int current_node) {
    int x = 50;
    int i = 1;
    int x_line = 150;
    int width = (current_node-1)*150+50;
    //copy
    SDL_Rect section = { x,50,width,45 };
    Uint32* pixels = new Uint32[width * 45];
    SDL_RenderReadPixels(renderer, &section, SDL_PIXELFORMAT_ARGB8888, pixels, width * sizeof(Uint32));
    //
    while (i<=current_node) {
        SDL_Rect rect = {x,50,100,45 };
        SDL_SetRenderDrawColor(renderer,255,165,0,0); //3 channels of color
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderPresent(renderer);

        if (i == current_node) break;
        int t=x_line;
        while (x_line<t+50) {
            makeLine(x_line, 75,x_line+ 5, 75, "Orange");
            x_line += 5;
            SDL_Delay(50);
        }
        x += 150;
        x_line += 100;
        i++;
        SDL_RenderPresent(renderer);
        SDL_Delay(300);
    }
    SDL_Delay(500);
    //paste
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, 45);
    SDL_UpdateTexture(texture, nullptr, pixels, width * sizeof(Uint32));
    SDL_Rect destination = {50,50,width, 45 };
    SDL_RenderCopy(renderer, texture, nullptr, &destination);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
    delete[] pixels;
}
void static update_vector(int i,int number_node, bool del, bool insert, std::string value) {
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
        coordinates newElement = {linked_list[i-1].x_begin, linked_list[i - 1].x_end,linked_list[i - 1].y_begin, linked_list[i - 1].y_end,value };
        linked_list.insert(linked_list.begin() + i, newElement);
    }
    for (; i <= number_node; i++) {
        linked_list[i].x_begin += sgn*150;
        linked_list[i].x_end += sgn*150;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::handleEvents() {
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
        if (show_menu_add && (mouseX >= 685 || mouseX <= 200|| mouseY >= 571 || mouseY <= 535))
        {
            show_menu_add = false;
            drawRec(200, 500, 500, 152, false, "", 0, "White");
            break;
        }
        for (int i = 1; i <= number_coorbtn + number_node; i++) {
            if ((mouseX >= state_btn[i].x_begin && mouseX <= state_btn[i].x_end &&
                mouseY >= state_btn[i].y_begin && mouseY <= state_btn[i].y_end) || ((i <= number_node) && ((mouseX >= linked_list[i].x_begin && mouseX <= linked_list[i].x_end &&
                    mouseY >= linked_list[i].y_begin && mouseY <= linked_list[i].y_end))))
            {
                if ((i <= number_node) && ((mouseX >= linked_list[i].x_begin && mouseX <= linked_list[i].x_end && //Edit data
                    mouseY >= linked_list[i].y_begin && mouseY <= linked_list[i].y_end))) //Edit value of linked list
                {
                    std::string current_value = linked_list[i].nameID;
                    txtinp = true;
                    save_state = false;
                    btn_map = false;
                    makeRectangle(linked_list[i].x_begin, 50, 100, 45, "", 0, "Blue", false, false, false);
                    txtinp = false;
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
                    random_data(); break;
                }
                if (state_btn[i].nameID == "Add") { 
               
                    btn_map = true;
                    txtinp = false;
                    save_state = true;
                    makeRectangle(state_btn[i].x_end + 2, state_btn[i].y_begin, 150, 32, "Insert to the first", 19, "Green", check_1st_time.menu_add, check_1st_time.menu_add, true);
                    makeRectangle(state_btn_map["Insert to the first"].x_end + 2, state_btn_map["Insert to the first"].y_begin, 180, 32, "Insert to the middle", 19, "Green", check_1st_time.menu_add, check_1st_time.menu_add, true);
                    makeRectangle(state_btn_map["Insert to the middle"].x_end + 2, state_btn_map["Insert to the middle"].y_begin, 150, 32, "Insert to the last", 19, "Green", check_1st_time.menu_add, check_1st_time.menu_add, true);
                    check_1st_time.menu_add = false;
                    btn_map = false;
                    show_menu_add = true;
                    break;
                } //insert data
                if (show_menu_add && (state_btn[i].nameID == "Insert to the first" || state_btn[i].nameID == "Insert to the middle" || state_btn[i].nameID == "Insert to the last"))
                {
                    save_state = true;
                    txtinp = false;
                    makeRectangle(state_btn[i].x_begin, state_btn[i].y_end, 150, 32, "Vertex = ", 19, "Green", false, true, true);
                    txtinp = true;
                    //create input box
                    btn_map = true;
                    makeRectangle(state_btn[i].x_end - 80, state_btn[i].y_end + 5, 40, 25, "input_box", 19, "Black", false, true, false);
                    btn_map = false;
                    save_state = false;
                    if (state_btn[i].nameID == "Insert to the first") add_position = "first";
                    if (state_btn[i].nameID == "Insert to the middle") add_position = "middle";
                    if (state_btn[i].nameID == "Insert to the last") add_position = "last";
                    makeLine(state_btn_map["input_box"].x_begin + 2, state_btn_map["input_box"].y_begin + 2, state_btn_map["input_box"].x_begin + 2, state_btn_map["input_box"].y_end - 2, "White");
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
                                    printText(15, 255, 255, 255, inputText, state_btn_map["input_box"].x_begin + 2, state_btn_map["input_box"].y_begin + 2, 0, 0);
                                    e.type = 0;
                                }
                        }
                        else if (e.type == SDL_KEYDOWN) 
                        {
                            if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0) {
                                inputText.pop_back();
                                save_state = false;
                                makeRectangle(state_btn_map["input_box"].x_begin, state_btn_map["input_box"].y_begin, 40, 25, inputText, 15, "Black", false, false, true);
                                save_state = true;
                            }
                            if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_KP_ENTER) {
                                txtinp = true;
                                makeRectangle(state_btn_map["Insert to the first"].x_begin, state_btn_map["Insert to the first"].y_begin,
                                    state_btn_map["Insert to the last"].x_end, state_btn_map["input_box"].y_end, " ", 0, "White", false, false, false);
                                if (inputText.length() > 0 && number_node < 10) {
                                    int buttonid = messbox("","Choose how to run",2,"Run step by step","Run at once");
                                    if (buttonid == 0) { //run at once
                                        if (add_position == "first")
                                            insert_first_data(inputText,linked_list);
                                        if (add_position == "last")
                                            insert_last_data(inputText);
                                        if (add_position == "middle")
                                            insert_middle(inputText);
                                    }
                                    else { //run step by step
                                        if (add_position == "first")
                                            insert_first_step(inputText,1, linked_list);
                                        if (add_position == "middle")
                                            insert_middle_step(inputText,1);
                                        if (add_position == "last")
                                            insert_last_step(inputText,1);
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
                            search_Step(text_find, 1,50,1,linked_list);
                        }
                    }
                    cancel_menu = false;

                }
                ///////////////////////////////////////////Delete data
                if (state_btn[i].nameID == "Delete") {
                    makeRectangle(state_btn[i].x_end + 2, state_btn[i].y_begin, 150, 32, "Delete at the first", 18, "Green", check_1st_time.menu_del, check_1st_time.menu_del, true);
                    makeRectangle(state_btn_map["Delete at the first"].x_end + 2, state_btn[i].y_begin, 170, 32, "Delete at the middle", 18, "Green", check_1st_time.menu_del, check_1st_time.menu_del, true);
                    makeRectangle(state_btn_map["Delete at the middle"].x_end + 2, state_btn[i].y_begin, 150, 32, "Delete at the last", 18, "Green", check_1st_time.menu_del, check_1st_time.menu_del, true);
                    check_1st_time.menu_del = false;
                    show_menu_add_del = true;
                    tempt = i;
                    break;
                }
                else
                    if (show_menu_add_del && (state_btn[i].nameID == "Delete at the first" || state_btn[i].nameID == "Delete at the middle" || state_btn[i].nameID == "Delete at the last"))
                    {
                           
                        show_menu_add_del = false;
                        drawRec(200, state_btn_map["Delete"].y_begin, state_btn_map["Delete at the last"].x_end, 50, false, "", 0, "White");
                        if (number_node >= 2)
                        {
                            int buttonid = messbox("", "Choose how to run", 2, "Run step by step", "Run at once");
                            if (buttonid == 0)
                            { //run at once
                                if (state_btn[i].nameID == "Delete at the first")
                                {
                                    save_state = false;
                                    btn_map = false;
                                    txtinp = false;
                                    save_state = false;
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
                                else if (number_node >= 3)
                                {
                                    if (state_btn[i].nameID == "Delete at the middle")
                                    {
                                        loop_node(number_node / 2, "Del", false);
                                        //dịch chuyen del node xuống
                                        i = number_node / 2 + 1;
                                        SDL_Delay(800);
                                        int y = 50;
                                        makeRectangle(linked_list[i].x_begin, 50, 150, 45, "", 0, "White", false, false, false);
                                        while (y < 160) {
                                            y += 5;
                                            if (y >= 75) makeLine(linked_list[i].x_begin, 75, linked_list[i].x_begin + 150, 75, "Orange");
                                            makeRectangle(linked_list[i].x_begin, y, 100, 45, linked_list[i].nameID, 23, "Blue", false, false, true);
                                            makeLine(linked_list[i].x_end, y + 25, linked_list[i + 1].x_begin, 75, "Orange");
                                            if (y >= 160) SDL_Delay(400);
                                            SDL_Delay(15);
                                            makeRectangle(linked_list[i].x_begin, 50, 150, y + 50, "", 25, "White", false, false, false);
                                        }
                                        //fix STT của next node xuống 1
                                        loop_node(number_node / 2, "Del", true);
                                        //move the next node and the text to the left
                                        int width = linked_list[number_node].x_end - linked_list[i + 1].x_begin;
                                        SDL_Rect section = { linked_list[i + 1].x_begin,50,width,150 };
                                        Uint32* pixels = new Uint32[1300 * 150];
                                        SDL_RenderReadPixels(renderer, &section, SDL_PIXELFORMAT_ARGB8888, pixels, width * sizeof(Uint32));
                                        int x = linked_list[i + 1].x_begin;
                                        while (x > linked_list[i].x_begin)
                                        {
                                            makeRectangle(x, 50, width, 45, "", 0, "White", false, false, false);
                                            x -= 5;
                                            SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, 150);
                                            SDL_UpdateTexture(texture, nullptr, pixels, width * sizeof(Uint32));
                                            SDL_Rect destination = { x,50,width, 150 };
                                            SDL_RenderCopy(renderer, texture, nullptr, &destination);
                                            SDL_RenderPresent(renderer);
                                            SDL_DestroyTexture(texture);
                                            makeLine(linked_list[i].x_begin, 75, x, 75, "Orange");
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
                                        drawRec(200, 100, linked_list[number_node - 1].x_begin - 200, 50, false, "", 0, "White");
                                        number_node--;
                                        update_vector(i, number_node, true, false, "");
                                        delete[] pixels;
                                    }
                                    if (state_btn[i].nameID == "Delete at the last")
                                    {
                                        drawRec(50, 105, 100, 30,false,"",0,"White");
                                        makeLine(150, 75, 200, 75, "Orange");
                                        printText(22, 0, 0, 0, "Head/prev",70, 105, 0, 0);
                                        printText(23, 0, 0, 0, "Tempt",225, 105, 0, 0);
                                        int t = 150;
                                        while (true) {
                                            t += 5;
                                            makeLine(150, 75,t, 75, "Orange");
                                            SDL_Delay(100);
                                            if (t == 200) break;    
                                        }
                                        makeLine(150, 75, 200, 75, "Black");
                                        SDL_Delay(150);
                                        int i = 3;
                                        while (true)
                                        {
                                            drawRec(linked_list[i-2].x_begin, 105, linked_list[i - 2].x_begin+250, 30, false, "", 0, "White");
                                            printText(22, 0, 0, 0,"Head",75, 105, 0, 0);
                                            printText(23, 0, 0, 0, "prev",linked_list[i - 1].x_begin+25, 105, 0, 0);
                                            if( i==number_node)
                                                printText(22, 0, 0, 0, "Tail/Tempt", linked_list[i].x_begin +20, 105, 0, 0);
                                            else
                                            printText(23, 0, 0, 0, "Tempt", linked_list[i].x_begin +25, 105, 0, 0);
                                            t = linked_list[i - 1].x_end;
                                            int z = linked_list[i - 2].x_end;
                                            while (true) {
                                                t += 5;
                                                z += 5;
                                                makeLine(linked_list[i - 1].x_end, 75,t, 75, "Orange"); // new tempt node
                                                makeLine(linked_list[i - 2].x_end, 75,z, 75, "Orange"); //redraw the prev node
                                                if (t == linked_list[i - 1].x_end + 50) break;
                                                SDL_Delay(80); 
                                            }
                                            makeLine(linked_list[i - 1].x_end, 75,t, 75, "Black");
                                            if (i == number_node) {
                                                makeLine(linked_list[number_node-1].x_end, 75, linked_list[number_node].x_begin, 75, "Orange");
                                                break;
                                            }
                                            SDL_Delay(150);
                                            i++;
                                        }
                                        drawRec(linked_list[number_node-1].x_end,50,linked_list[number_node - 1].x_end+150,45, false,"", 0,"White");
                                        drawRec(linked_list[i - 2].x_begin, 105, linked_list[i - 2].x_begin+250, 30, false, "", 0, "White");
                                        linked_list[number_node].x_begin  = 0;
                                        linked_list[number_node].x_end = 0;
                                        linked_list[number_node].y_begin = 0;
                                        linked_list[number_node].y_end = 0;
                                        linked_list[number_node].nameID = "";
                                        number_node--;
                                        printText(22, 0, 0, 0, "Tail", linked_list[number_node].x_begin +25, 105, 0, 0);
                                         //Fix color of rec to blue and color of the line to black
                                        int dem = 1;
                                        int x = 50;
                                        while (true) {
                                            SDL_Rect rect = { x,50,100,45 };
                                            SDL_SetRenderDrawColor(renderer, 100, 149, 237, 0); //3 channels of color
                                            SDL_RenderDrawRect(renderer, &rect);
                                            SDL_RenderPresent(renderer);
                                            dem++;
                                            if (dem == number_node+1) break;
                                            makeLine(x + 100, 75, x + 150, 75, "Black");
                                            x += 150;
                                        }

                                    }
                                }
                            }
                            else
                            { //run step by step
                            if (state_btn[i].nameID == "Delete at the first")
                                delete_first_step(1, linked_list);
                            if (state_btn[i].nameID == "Delete at the middle")
                                delete_middle_step(1);
                            if (state_btn[i].nameID == "Delete at the last")
                                delete_last_step(1, linked_list);
                            }
                        }
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
void Game::render(std::vector<coordinates> linkedlist) {
    //SDL_RenderClear(renderer); // Clear the screen
    linked_list = linkedlist;
    if (count == 0) {
        std::cout << "It works" << std::endl;
        for (int i = 1; i <= number_node; i++) {
            if (i == 1) head = true;

            if (i == number_node) tail = true;
            Linkedlist(linked_list[i].nameID, i);
            head = false; tail = false;
        }
        count = 1;
    }
    SDL_RenderPresent(renderer); // Show the rendered image on the screen
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
void Game::printText(int font_size, int red, int blue, int green, std::string content, int x, int y, int textWidth, int textHeight) {
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("arial.ttf", font_size);
    SDL_Color textColor = { red, blue, green, 0 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(font,content.c_str(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);
    SDL_Rect textRect = {x,y, textWidth, textHeight };
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_RenderPresent(renderer); // Show the rendered image on the screen
}
void Game::drawRec(int x_pos, int y_pos, int width_rec, int height_rec, bool printtext, std::string name, int textsize, std::string name_color)
{
    SDL_Rect rect = { x_pos, y_pos,width_rec,height_rec };
    SDL_SetRenderDrawColor(renderer, color[name_color][0], color[name_color][1], color[name_color][2], 0); //3 channels of color
    SDL_RenderFillRect(renderer, &rect);
    //name of buttn
    if (printtext)
        printText(textsize, 255, 255, 255, name.c_str(), rect.x + 10, rect.y + 10, 0, 0);
    SDL_RenderPresent(renderer); // Show the rendered image on the screen
}
void Game::makeRectangle(int x_pos, int y_pos, int width_rec, int height_rec,std::string name,int textsize,std::string name_color,bool save_state, bool btn_map, bool txtinp) {
    //draw rectangle
    SDL_Rect rect = { x_pos, y_pos,width_rec,height_rec};
    SDL_SetRenderDrawColor(renderer,color[name_color][0],color[name_color][1], color[name_color][2],0); //3 channels of color
    SDL_RenderFillRect(renderer, &rect);
    //name of buttn
    if (txtinp)
    printText(textsize, 255, 255, 255,name.c_str(), rect.x + 10, rect.y + 10, 0, 0);
    if (save_state) {
        state_btn[number_coorbtn].x_begin = x_pos;
        state_btn[number_coorbtn].x_end = x_pos + width_rec;
        state_btn[number_coorbtn].y_begin = y_pos;
        state_btn[number_coorbtn].y_end = y_pos + height_rec;
        state_btn[number_coorbtn].nameID = name;
        number_coorbtn++;
    }
    if (btn_map) {
        state_btn_map[name].x_begin = x_pos;
        state_btn_map[name].x_end = x_pos + width_rec;
        state_btn_map[name].y_begin = y_pos;
        state_btn_map[name].y_end = y_pos + height_rec;
    }
    SDL_RenderPresent(renderer); // Show the rendered image on the screen

}   
void Game::makeLine(int x_begin, int y_begin, int x_end, int y_end,std::string name_color) {
    SDL_SetRenderDrawColor(renderer,color[name_color][0], color[name_color][1], color[name_color][2],0);
    SDL_RenderDrawLine(renderer,x_begin,y_begin,x_end,y_end);
    SDL_RenderPresent(renderer); // Show the rendered image on the screen
}
void Game::Linkedlist(std::string value,int current_node) {
   
    //draw rectangle
    SDL_Rect rect = { edge.x, edge.y, 100,45 };
    SDL_SetRenderDrawColor(renderer,100,149,237, 0); //blue
    SDL_RenderFillRect(renderer, &rect);
    // Draw the text texture inside the rectangle
    printText(23,255,255,255,value.c_str(), rect.x + 10, rect.y + 10, 0, 0);
    //save liked list
    linked_list[current_node].x_begin = rect.x; linked_list[current_node].x_end = rect.x+rect.w;
    linked_list[current_node].y_begin = rect.y; linked_list[current_node].y_end = rect.y+45;
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
        makeRectangle(50, 500, 150, 38, "Random Data",20, "Green", true, true, true);
        makeRectangle(50,state_btn[number_coorbtn-1].y_end+2, 150, 38, "Add",20, "Green", true, true, true);
        makeRectangle(50, state_btn[number_coorbtn - 1].y_end+2, 150, 38, "Delete",20, "Green", true, true, true);
        makeRectangle(50, state_btn[number_coorbtn - 1].y_end+2, 150, 38, "Search",20,"Green", true, true, true);

        menu_linkedlist = true;
    }
    btn_map = false;
}
