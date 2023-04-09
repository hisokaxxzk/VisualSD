#pragma once
#ifndef VD_h
#define VD_h
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>
#include <iostream>
#include <random>
#include <ctype.h>
#include <vector>
#include <map>
#include <cstring>
#include <chrono>
#include <string>
struct lan_dau {
	bool menu_add = true;
	bool menu_del = true;
};
struct rect_connect {
	float  x;
	int y;
};
struct coordinates {
	int x_begin;
	int x_end;
	int y_begin;
	int y_end;
	std::string nameID;
};
void update_vector(int i, int number_node);
class Game {
public:
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	void printText(int font_size, int red, int blue, int green, std::string content, int x, int y, int textWidth, int textHeight);
	void makeRectangle(int x_pos, int y_pos, int width_rec, int height_rec, std::string name, int textsize, std::string name_color, bool save_state, bool btn_map, bool txtinp);
	void drawRec(int x_pos, int y_pos, int width_rec, int height_rec, bool printtext, std::string name, int textsize, std::string name_color);
	void previous_stage(Uint32*&pixels, int& stage, int width);
	void make_txt_input(int x_pos, int y_pos, int width_txtinp, int height_txtinp, std::string name, int textsize);
	void makeLine(int x_begin, int y_begin, int x_end, int y_end, std::string name_color);
	void Linkedlist(std::string value, int curren_node);
	void random_data();
	void insert_first_data(std::string value);
	void insert_first_step(std::string value, int stage);
	void insert_last_data(std::string value);
	void insert_last_step(std::string value, int stage);
	void delete_first_step (int stage);
	void delete_middle_step(int stage);
	void delete_last_step(int stage);
	void loop_node(int pos, std::string task, bool del_text);
	void insert_middle_step(std::string value, int stage);
	void search_Step(std::string value,int stage, int x, int i);
	void draw_bound_rec(int x_pos, int y_pos, int width, int height, std::string namecolor);
	void insert_middle(std::string value);
	void rec_move(int x_pos,int y_pos, int y_end,std::string value);
	void Edit_data(int current_node);
	void home();
	bool running() { return isRunning; }
	rect_connect edge;
	int number_node = 7;

private:
	std::map<std::string, std::vector<int>> color;
	SDL_Renderer* renderer;
	bool isRunning;
	SDL_Window* window;
	
};
#endif /*game_h*/
