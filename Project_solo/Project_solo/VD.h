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
	#include "SDL_clipboard.h"
	#include <map>
	#include <cstring>
	#include <chrono>
	#include <string>
#include <fstream>
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
	struct feature {
		int low;
		int fast;
	};

		class Game {
		public:
			
			Game();
			~Game();
			void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
			void handleEvents();
			void update();
			void render(std::vector<coordinates> linkedlist);
			void clean();
			void printText(int font_size, int red, int blue, int green, std::string content, int x, int y, int textWidth, int textHeight);
			void makeRectangle(int x_pos, int y_pos, int width_rec, int height_rec, std::string name, int textsize, std::string name_color, bool save_state, bool btn_map, bool txtinp);
			void drawRec(int x_pos, int y_pos, int width_rec, int height_rec, bool printtext, std::string name, int textsize, std::string name_color);
			void previous_stage(Uint32*&pixels, int& stage, int width);
			void make_txt_input(int x_pos, int y_pos, int width_txtinp, int height_txtinp, std::string name, int textsize);
			void makeLine(int x_begin, int y_begin, int x_end, int y_end, std::string name_color);
			void Linkedlist(std::string value, int curren_node);
			void random_data();
			void insert_first_data(std::string value, std::vector<coordinates>& linked_list);
			void insert_first_step(std::string value, int stage, std::vector<coordinates>& linked_list);
			void insert_last_data(std::string value, std::vector<coordinates>& linked_list);
			void insert_last_step(std::string value, int stage, std::vector<coordinates>& linked_list,int x);
			void delete_first_step (int stage, std::vector<coordinates>& linked_list);
			void delete_middle_step(int stage);
			void delete_last_step(int stage, std::vector<coordinates>& linked_list);
			void loop_node(int pos_begin,int pos_end, std::string task, bool del_text);
			void insert_middle_step(std::string value, int stage);
			void search_Step(std::string value,int stage, int x, int i, std::vector<coordinates>& linked_list);
			void draw_bound_rec(int x_pos, int y_pos, int width, int height, std::string namecolor);
			void insert_middle(std::string value);
			void rec_move(int x_pos,int y_pos, int y_end,std::string value);
			void Edit_data(int current_node);
			void home(Game *home1);
			void enter_data();
			void enter_data_stack();
			void enter_data_queue();
			void enter_data_static_array();
			void paste();
			int messbox(std::string title, std::string content, int num_button, std::string name_btn1, std::string name_btn2);
			void render_stack(std::vector<coordinates> linkedlist);
			void handleEvents_stack();
			void stack(std::string value, int current_node);
			void random_data_stack();
			void render_queue(std::vector<coordinates> linkedlist);
			void queue(std::string value, int current_node);
			void random_data_queue();
			void handleEvents_queue();
			void Static_Array(std::string value, int current_node);
			void render_array(std::vector<coordinates> linkedlist);
			void handleEvents_array();
			void random_data_array();
			void makeRec(int x_pos, int y_pos, int width_rec, int height_rec, std::string name, int textsize, std::string name_color, bool save_state, bool btn_map, bool txtinp);
			void insert_middle_array(std::string value);
			void insert_array(std::string value, int pos);
			void insert_last_array(std::string value);
			void loop_node_array_insert(int pos_begin, int pos_end, std::string task, bool del_text);
			void loop_node_array_del(int pos_begin, int pos_end);
			void insert_step_array(std::string value, int stage, std::vector<coordinates>& linked_list, int x, int pos);
			void delete_step_array(int stage, std::vector<coordinates>& linked_list, int x,int pos_end, int pos_begin);
			void previous_stage_array(Uint32*& pixels, int& stage, int width);
			void search_Step_array(std::string value, int stage, int x, int i, std::vector<coordinates>& linked_list);
			void enter_data_dynamic_array();
			void render_dynamic_array(std::vector<coordinates> linkedlist);
			void Dynamic_Arrary(std::string value, int current_node);
			void handleEvents_dynamic_array();
			void random_data_dynamic_array();
			void makeRec_dynamic(int x_pos, int y_pos, int width_rec, int height_rec, std::string name, int textsize, std::string name_color, bool save_state, bool btn_map, bool txtinp);
			void insert_dynamic_array(std::string value, int pos);
			void loop_node_dynamic_array_insert(int pos_begin, int pos_end, std::string task, bool del_text);
			void loop_node_dynamic_array_del(int pos_begin, int pos_end);
			void search_Step_dynamic_array(std::string value, int stage, int x, int i, std::vector<coordinates>& linked_list);
			void delete_step_dynamic_array(int stage, std::vector<coordinates>& array, int x, int pos_begin, int pos_end);
			void drawArrow(int x1, int y1, int x2, int y2, std::string color_name, short int direction);
			void enter_DLL();
			void DL_Linkedlist(std::string value, int current_node);
			void makeRec_DLL(int x_pos, int y_pos, int width_rec, int height_rec, std::string name, int textsize, std::string name_color, bool save_state, bool btn_map, bool txtinp);
			void render_dll(std::vector<coordinates> dll);
			void handleEvents_DLL();
			void insert_first_dll(std::string value, std::vector<coordinates>& linked_list);
			void drawLine_animation(int x_begin, int y_begin, int x_end, int y_end, std::string color_name);
			void insert_middle_dll(std::string value, std::vector<coordinates>& linked_list);
			void insert_last_dll(std::string value, std::vector<coordinates>& linked_list);
			void delete_dll(int pos, std::vector<coordinates>& linked_list);
			bool running() { return isRunning; }
			rect_connect edge;
			int number_node;
			std::map<std::string, int> speed =
			{
				{"fast", 20},
				{"low", 60}
			};
			std::string speed_type = "low";
	private:
		std::map<std::string, std::vector<int>> color;
		SDL_Renderer* renderer;
		bool isRunning;
		SDL_Window* window;
	
	};

	#endif /*game_h*/
