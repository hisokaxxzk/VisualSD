#include "VD.h"
static std::vector<coordinates> linkedlist_1(1000);
void Game::enter_data_stack()
{
    int number_value = 0;
    int count_word = 0;
    bool generate = false;
    drawRec(50, 50, 1600, 200, false, "", 0, "White");
    draw_bound_rec(450, 50, 600, 35, "Black");
    drawRec(730, 100, 120, 45, true, "File", 22, "Yellow");
    drawRec(600, 100, 120, 45, true, "Generate", 22, "Grey");
    printText(20, color["Grey"][0], color["Grey"][1], color["Grey"][2], "Enter the value of each node in the Stack. Separated by Enter.", 450, 20, 0, 0);
    while (true)
    {
        SDL_Event e;
        SDL_PollEvent(&e);
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            if (mouseX >= 450 && mouseX <= 1050 && mouseY >= 50 && mouseY <= 85) // Enter node
            {
                std::string text_find = "";
                SDL_StartTextInput;
                makeLine(460, 55, 460, 80, "Black");
                while (true)
                {
                    SDL_Event evt;
                    SDL_PollEvent(&evt);
                    if (evt.type == SDL_TEXTINPUT)
                        if (number_value + 1 <= 10 && isdigit(evt.text.text[0]) && count_word <= 3)
                        {
                            text_find += evt.text.text;
                            printText(18, 0, 0, 0, text_find, 460, 60, 0, 0);
                            count_word++;
                        }
                    if (evt.type == SDL_KEYDOWN) {
                        if (evt.key.keysym.sym == SDLK_BACKSPACE)
                            if (text_find.length() > 0 && count_word>0)
                            {
                                count_word--;
                                drawRec(461, 55, 590, 22, false, "", 0, "White");
                                text_find.pop_back();
                                printText(18, 0, 0, 0, text_find, 460, 60, 0, 0);
                                makeLine(460, 55, 460, 70, "Black");
                            }
                        if (number_value <= 9)
                            if ((evt.key.keysym.sym == SDLK_KP_ENTER || evt.key.keysym.sym == SDLK_RETURN) && text_find.length() > 0 && isdigit(text_find[text_find.length() - 1]))
                            {
                                text_find += ',';
                                number_value++;
                                printText(18, 0, 0, 0, text_find, 460, 60, 0, 0);
                                count_word = 0;
                                if (!generate) generate = true;
                            }
                        if (generate)
                            drawRec(600, 100, 120, 45, true, "Generate", 22, "Green");

                    }
                    if (evt.type == SDL_MOUSEBUTTONDOWN)
                    {
                        SDL_GetMouseState(&mouseX, &mouseY);
                        if (mouseX >= 600 && mouseX <= 720 && mouseY >= 100 && mouseY <= 145) // Generate
                        {
                            if (generate)
                            {
                                drawRec(0, 0, 1600, 800, false, "", 0, "White");
                                int pos = 0;
                                for (int i = 0; i < number_value; i++)
                                {
                                    for (; pos <= text_find.length(); pos++)
                                    {
                                        if (text_find[pos] == ',')
                                        {
                                            pos++;
                                            break;
                                        }
                                        linkedlist_1[i + 1].nameID += text_find[pos];

                                    }

                                }
                                number_node = number_value;
                                render_stack(linkedlist_1);
                                while (true)
                                {
                                    handleEvents_stack();
                                }
                            }
                        }
                            else
                            {
                                drawRec(451, 51, 598, 33, false, "", 0, "White");
                                drawRec(600, 100, 120, 45, true, "Generate", 22, "Grey");
                                generate = false;
                                number_value = 0;
                                generate = 0;
                                break;
                            }

                    }

                }
            }
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) //Load File
        {

            if (mouseX >= 730 && mouseX <= 850 && mouseY >= 100 && mouseY <= 145)
            {
                int mess_box = messbox("", "Enter your path's file", 1, "", "Ok");
                drawRec(730, 100, 120, 45, true, "Text", 22, "Blue");
                std::string text_find = "";
                SDL_StartTextInput;
                makeLine(460, 55, 460, 80, "Black");
                drawRec(1070, 50, 100, 35, true, "Paste", 22, "Grey");
                while (true)
                {
                    makeLine(460, 55, 460, 80, "Black");
                    SDL_Event evt;
                    SDL_PollEvent(&evt);
                    if (evt.type == SDL_TEXTINPUT)
                    {
                        text_find += evt.text.text;
                        printText(15, 0, 0, 0, text_find, 460, 60, 0, 0);
                        if (!generate) generate = true;
                    }
                    if (evt.type == SDL_KEYDOWN) {
                        if (evt.key.keysym.sym == SDLK_BACKSPACE)
                            if (text_find.length() > 0)
                            {
                                drawRec(461, 55, 590, 22, false, "", 0, "White");
                                text_find.pop_back();
                                printText(15, 0, 0, 0, text_find, 460, 60, 0, 0);
                                makeLine(460, 55, 460, 70, "Black");
                            }
                        if (generate)
                            drawRec(600, 100, 120, 45, true, "Generate", 22, "Green");
                    }
                    if (evt.type == SDL_MOUSEBUTTONDOWN)
                    {
                        SDL_GetMouseState(&mouseX, &mouseY);
                        if (mouseX >= 1070 && mouseX <= 1170 && mouseY >= 50 && mouseY <= 85) //Paste
                        {
                            paste();
                            generate = true;
                            makeLine(460, 55, 460, 80, "Black");
                            text_find = SDL_GetClipboardText();
                            text_find = text_find.substr(0, text_find.length());
                            for (int i = 0; i < text_find.length(); i++) {
                                if (text_find[i] == '\\')
                                    text_find[i] = '/';
                            }
                        }
                        else
                            if (mouseX >= 600 && mouseX <= 720 && mouseY >= 100 && mouseY <= 145) // Generate
                            {
                                if (generate)
                                {
                                    std::ifstream file(text_find);
                                    // Kiểm tra xem file có tồn tại hay không
                                    if (!file.is_open()) {
                                        mess_box = messbox("Error", "Cannot open this file", 1, "", "Ok");
                                    }
                                    else
                                    {
                                        file >> text_find;
                                        drawRec(0, 0, 1600, 800, false, "", 0, "White");
                                        int pos = 0;
                                        int m = 0;
                                        while (true)
                                        {
                                            m++;
                                            for (; pos <= text_find.length(); pos++)
                                            {
                                                if (text_find[pos] == ',')
                                                {
                                                    pos++;
                                                    break;
                                                }
                                                linkedlist_1[m].nameID += text_find[pos];
                                            }
                                            if (pos > text_find.length()) break;
                                        }
                                        number_node = m;
                                        render(linkedlist_1);
                                        while (true)
                                        {
                                            handleEvents();
                                        }
                                    }
                                }
                            }
                            else
                                if (mouseX >= 730 && mouseX <= 850 && mouseY >= 100 && mouseY <= 145) // text
                                {
                                    drawRec(730, 100, 120, 45, true, "File", 22, "Yellow");
                                    drawRec(451, 51, 598, 33, false, "", 0, "White");
                                    drawRec(600, 100, 120, 45, true, "Generate", 22, "Grey");
                                    generate = false;
                                    drawRec(451, 51, 598, 33, false, "", 0, "White");
                                    drawRec(1070, 50, 100, 35, false, "", 22, "White");
                                    break;
                                }

                                else
                                {
                                    drawRec(451, 51, 598, 33, false, "", 0, "White");
                                    drawRec(600, 100, 120, 45, true, "Generate", 22, "Grey");
                                    text_find = "";
                                    generate = false;
                                }
                    }
                }
            }
        }
    }
}
